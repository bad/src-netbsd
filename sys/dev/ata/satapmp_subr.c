/*	$NetBSD: satapmp_subr.c,v 1.15 2018/10/22 20:13:47 jdolecek Exp $	*/

/*
 * Copyright (c) 2012 Manuel Bouyer.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <sys/cdefs.h>
__KERNEL_RCSID(0, "$NetBSD: satapmp_subr.c,v 1.15 2018/10/22 20:13:47 jdolecek Exp $");

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/kernel.h>
#include <sys/device.h>
#include <sys/conf.h>
#include <sys/fcntl.h>
#include <sys/proc.h>
#include <sys/errno.h>
#include <sys/kmem.h>
#include <sys/intr.h>

#include <dev/ata/ataconf.h>
#include <dev/ata/atareg.h>
#include <dev/ata/atavar.h>

#include <dev/ata/satapmpvar.h>
#include <dev/ata/satapmpreg.h>
#include <dev/ata/satavar.h>
#include <dev/ata/satareg.h>

static int
satapmp_read_8(struct ata_channel *chp, int port, int reg, uint64_t *value,
    struct ata_xfer *xfer)
{
	struct atac_softc *atac = chp->ch_atac;
	struct ata_drive_datas *drvp;
	int error = 0;

	KASSERT(port < PMP_MAX_DRIVES);
	KASSERT(reg < PMP_GSCR_NREGS);
	KASSERT(chp->ch_ndrives >= PMP_MAX_DRIVES);
	drvp = &chp->ch_drive[PMP_PORT_CTL];
	KASSERT(drvp->drive == PMP_PORT_CTL);
	ata_channel_lock_owned(chp);

	memset(xfer, 0, sizeof(*xfer));
	xfer->c_ata_c.r_command = PMPC_READ_PORT;
	xfer->c_ata_c.r_features = reg;
	xfer->c_ata_c.r_device = port;
	xfer->c_ata_c.timeout = 3000; /* 3s */
	xfer->c_ata_c.r_st_bmask = 0;
	xfer->c_ata_c.r_st_pmask = WDCS_DRDY;
	xfer->c_ata_c.flags = AT_LBA48 | AT_READREG | AT_WAIT;

	ata_channel_unlock(chp);
	if ((*atac->atac_bustype_ata->ata_exec_command)(drvp,
	    xfer) != ATACMD_COMPLETE) {
		aprint_error_dev(chp->atabus,
		    "PMP port %d register %d read failed\n", port, reg);
		error = EIO;
		goto out;
	}
	if (xfer->c_ata_c.flags & (AT_TIMEOU | AT_DF)) {
		aprint_error_dev(chp->atabus,
		    "PMP port %d register %d read failed, flags 0x%x\n",
		    port, reg, xfer->c_ata_c.flags);
		error = EIO;
		goto out;
	}
	if (xfer->c_ata_c.flags & AT_ERROR) {
		aprint_verbose_dev(chp->atabus,
		    "PMP port %d register %d read failed, error 0x%x\n",
		    port, reg, xfer->c_ata_c.r_error);
		error = EIO;
		goto out;
	}

	*value = ((uint64_t)((xfer->c_ata_c.r_lba >> 24) & 0xffffff) << 40) |
		((uint64_t)((xfer->c_ata_c.r_count >> 8) & 0xff) << 32) |
		((uint64_t)((xfer->c_ata_c.r_lba >> 0) & 0xffffff) << 8) |
		((uint64_t)((xfer->c_ata_c.r_count >> 0) & 0xff) << 0);

out:
	ata_channel_lock(chp);
	return error;
}

static inline int
satapmp_read(struct ata_channel *chp, int port, int reg, uint32_t *value,
    struct ata_xfer *xfer)
{
	uint64_t value64;
	int ret;

	ret = satapmp_read_8(chp, port, reg, &value64, xfer);
	if (ret)
		return ret;

	*value = value64 & 0xffffffff;
	return ret;
}

static int
satapmp_write_8(struct ata_channel *chp, int port, int reg, uint64_t value,
    struct ata_xfer *xfer)
{
	struct atac_softc *atac = chp->ch_atac;
	struct ata_drive_datas *drvp;
	int error = 0;

	KASSERT(port < PMP_MAX_DRIVES);
	KASSERT(reg < PMP_GSCR_NREGS);
	KASSERT(chp->ch_ndrives >= PMP_MAX_DRIVES);
	drvp = &chp->ch_drive[PMP_PORT_CTL];
	KASSERT(drvp->drive == PMP_PORT_CTL);
	ata_channel_lock_owned(chp);

	memset(xfer, 0, sizeof(*xfer));
	xfer->c_ata_c.r_command = PMPC_WRITE_PORT;
	xfer->c_ata_c.r_features = reg;
	xfer->c_ata_c.r_device = port;
	xfer->c_ata_c.r_lba = (((value >> 40) & 0xffffff) << 24) |
		      (((value >>  8) & 0xffffff) <<  0);
	xfer->c_ata_c.r_count = (((value >> 32) & 0xff) << 8) |
			(((value >>  0) & 0xff) << 0);
	xfer->c_ata_c.timeout = 3000; /* 3s */
	xfer->c_ata_c.r_st_bmask = 0;
	xfer->c_ata_c.r_st_pmask = WDCS_DRDY;
	xfer->c_ata_c.flags = AT_LBA48 | AT_WAIT;

	ata_channel_unlock(chp);
	if ((*atac->atac_bustype_ata->ata_exec_command)(drvp,
	    xfer) != ATACMD_COMPLETE) {
		aprint_error_dev(chp->atabus,
		    "PMP port %d register %d write failed\n", port, reg);
		error = EIO;
		goto out;
	}
	if (xfer->c_ata_c.flags & (AT_TIMEOU | AT_DF)) {
		aprint_error_dev(chp->atabus,
		    "PMP port %d register %d write failed, flags 0x%x\n",
		    port, reg, xfer->c_ata_c.flags);
		error = EIO;
		goto out;
	}
	if (xfer->c_ata_c.flags & AT_ERROR) {
		aprint_verbose_dev(chp->atabus,
		    "PMP port %d register %d write failed, error 0x%x\n",
		    port, reg, xfer->c_ata_c.r_error);
		error = EIO;
		goto out;
	}

out:
	ata_channel_lock(chp);
	return error;
}

static inline int
satapmp_write(struct ata_channel *chp, int port, int reg, uint32_t value,
    struct ata_xfer *xfer)
{
	return satapmp_write_8(chp, port, reg, value, xfer);
}

/*
 * Reset one port's PHY and bring it online
 * XXX duplicate of sata_reset_interface()
 */
static uint32_t
satapmp_reset_device_port(struct ata_channel *chp, int port,
    struct ata_xfer *xfer)
{
	uint32_t scontrol, sstatus;
	int i;

	ata_channel_lock_owned(chp);

	/* bring the PHY online */
	scontrol = SControl_IPM_NONE | SControl_SPD_ANY | SControl_DET_INIT;
	if (satapmp_write(chp, port, PMP_PSCR_SControl, scontrol, xfer) != 0)
		return 0;

	ata_delay(chp, 50, "sataup", AT_WAIT);
	scontrol &= ~SControl_DET_INIT;
	if (satapmp_write(chp, port, PMP_PSCR_SControl, scontrol, xfer) != 0)
		return 0;
	ata_delay(chp, 50, "sataup", AT_WAIT);

	/* wait up to 1s for device to come up */
	for (i = 0; i < 100; i++) {
		
		if (satapmp_read(chp, port, PMP_PSCR_SStatus, &sstatus,
		    xfer) != 0)
			return 0;
		if ((sstatus & SStatus_DET_mask) == SStatus_DET_DEV)
			break;
		ata_delay(chp, 10, "sataup", AT_WAIT);
	}

	switch (sstatus & SStatus_DET_mask) {
	case SStatus_DET_NODEV:
		/* No Device; be silent.  */
		break;
	case SStatus_DET_DEV_NE:
		aprint_error("%s PMP port %d: device connected, but "
		    "communication not established\n",
		    device_xname(chp->atabus), port);
		break;
	case SStatus_DET_OFFLINE:
		aprint_error("%s PMP port %d: PHY offline\n",
		    device_xname(chp->atabus), port);
		break;
	case SStatus_DET_DEV:
		aprint_normal("%s PMP port %d: device present, speed: %s\n",
		    device_xname(chp->atabus), port, sata_speed(sstatus));
		break;
	default:
		aprint_error("%s PMP port %d: unknown SStatus: 0x%08x\n",
		    device_xname(chp->atabus), port, sstatus);
	}
	return(sstatus & SStatus_DET_mask);
}

static void __noinline
satapmp_rescan(struct ata_channel *chp, struct ata_xfer *xfer)
{
	int i;
	uint32_t sig;

	KASSERT(chp->ch_satapmp_nports <= PMP_PORT_CTL);
	KASSERT(chp->ch_satapmp_nports <= chp->ch_ndrives);
	ata_channel_lock_owned(chp);

	for (i = 0; i < chp->ch_satapmp_nports; i++) {
		if (chp->ch_drive[i].drive_type != ATA_DRIVET_NONE ||
		    satapmp_reset_device_port(chp, i, xfer)
		    != SStatus_DET_DEV) {
			continue;
		}
		if (satapmp_write(chp, i, PMP_PSCR_SError, 0xffffffff, xfer)
		    != 0) {
			aprint_error("%s PMP port %d: can't write SError\n",
			    device_xname(chp->atabus), i);
			continue;
		}

		ata_channel_lock_owned(chp);
		chp->ch_atac->atac_bustype_ata->ata_reset_drive(
		    &chp->ch_drive[i], AT_WAIT, &sig);

		sata_interpret_sig(chp, i, sig);
	}
}

void
satapmp_attach(struct ata_channel *chp)
{
	uint32_t id, rev, inf;
	struct ata_xfer *xfer;

	xfer = ata_get_xfer(chp, false);
	if (xfer == NULL) {
		aprint_normal_dev(chp->atabus, "no available xfer\n");
		return;
	}

	ata_channel_lock(chp);

	if (satapmp_read(chp, PMP_PORT_CTL, PMP_GSCR_ID, &id, xfer) != 0 ||
	    satapmp_read(chp, PMP_PORT_CTL, PMP_GSCR_REV, &rev, xfer) != 0 ||
	    satapmp_read(chp, PMP_PORT_CTL, PMP_GSCR_INF, &inf, xfer) != 0) {
		aprint_normal_dev(chp->atabus, "can't read PMP registers\n");
		goto out;
	}

	aprint_normal("%s at %s channel %d: SATA port multiplier, %d ports\n",
	    device_xname(chp->atabus),
	    device_xname(chp->ch_atac->atac_dev), chp->ch_channel,
	    PMP_INF_NPORTS(inf));
	aprint_verbose_dev(chp->atabus,
	    "vendor 0x%04x, product 0x%04x",
	    PMP_ID_VEND(id), PMP_ID_DEV(id));
	if (rev & PMP_REV_SPEC_11) {
		aprint_verbose(", revision 1.1");
	} else if (rev & PMP_REV_SPEC_10) {
		aprint_verbose(", revision 1.0");
	} else {
		aprint_verbose(", unknown revision 0x%x", rev & 0x0f);
	}
	aprint_verbose(", level %d\n", PMP_REV_LEVEL(rev));

	chp->ch_satapmp_nports = PMP_INF_NPORTS(inf);

	/* reset and bring up PHYs */
	satapmp_rescan(chp, xfer);

out:
	ata_channel_unlock(chp);
	ata_free_xfer(chp, xfer);
}
