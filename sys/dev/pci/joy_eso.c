/*	$NetBSD: joy_eso.c,v 1.16 2019/05/08 13:40:19 isaki Exp $	*/

/*
 * Copyright (c) 1998, 2008 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * This code is derived from software contributed to The NetBSD Foundation
 * by Lennart Augustsson (augustss@NetBSD.org).
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
 * THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <sys/cdefs.h>
__KERNEL_RCSID(0, "$NetBSD: joy_eso.c,v 1.16 2019/05/08 13:40:19 isaki Exp $");

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/kernel.h>
#include <sys/errno.h>
#include <sys/device.h>
#include <sys/malloc.h>
#include <sys/proc.h>
#include <sys/conf.h>
#include <sys/select.h>
#include <sys/audioio.h>

#include <sys/bus.h>

#include <dev/audio/audio_if.h>

#include <dev/pci/pcireg.h>
#include <dev/pci/pcivar.h>

#include <dev/pci/esovar.h>

#include <dev/ic/joyvar.h>

static int
joy_eso_match(device_t parent, cfdata_t match, void *aux)
{
	struct audio_attach_args *aa = aux;

	if (aa->type != AUDIODEV_TYPE_AUX)
		return 0;
	return 1;
}

static void
joy_eso_attach(device_t parent, device_t self, void *aux)
{
	struct eso_softc *esc = device_private(parent);
	struct joy_softc *sc = device_private(self);

	aprint_normal("\n");

	sc->sc_ioh = esc->sc_game_ioh;
	sc->sc_iot = esc->sc_game_iot;
	sc->sc_dev = self;
	sc->sc_lock = &esc->sc_lock;

	joyattach(sc);
}

CFATTACH_DECL_NEW(joy_eso, sizeof (struct joy_softc),
    joy_eso_match, joy_eso_attach, NULL, NULL);
