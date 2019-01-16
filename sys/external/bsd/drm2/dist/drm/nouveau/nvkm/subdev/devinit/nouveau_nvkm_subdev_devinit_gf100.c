/*	$NetBSD: nouveau_nvkm_subdev_devinit_gf100.c,v 1.2 2018/08/27 04:58:33 riastradh Exp $	*/

/*
 * Copyright 2013 Red Hat Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: Ben Skeggs
 */
#include <sys/cdefs.h>
__KERNEL_RCSID(0, "$NetBSD: nouveau_nvkm_subdev_devinit_gf100.c,v 1.2 2018/08/27 04:58:33 riastradh Exp $");

#include "nv50.h"

#include <subdev/bios.h>
#include <subdev/bios/init.h>
#include <subdev/bios/pll.h>
#include <subdev/clk/pll.h>

int
gf100_devinit_pll_set(struct nvkm_devinit *init, u32 type, u32 freq)
{
	struct nvkm_subdev *subdev = &init->subdev;
	struct nvkm_device *device = subdev->device;
	struct nvbios_pll info;
	int N, fN, M, P;
	int ret;

	ret = nvbios_pll_parse(device->bios, type, &info);
	if (ret)
		return ret;

	ret = gt215_pll_calc(subdev, &info, freq, &N, &fN, &M, &P);
	if (ret < 0)
		return ret;

	switch (info.type) {
	case PLL_VPLL0:
	case PLL_VPLL1:
	case PLL_VPLL2:
	case PLL_VPLL3:
		nvkm_mask(device, info.reg + 0x0c, 0x00000000, 0x00000100);
		nvkm_wr32(device, info.reg + 0x04, (P << 16) | (N << 8) | M);
		nvkm_wr32(device, info.reg + 0x10, fN << 16);
		break;
	default:
		nvkm_warn(subdev, "%08x/%dKhz unimplemented\n", type, freq);
		ret = -EINVAL;
		break;
	}

	return ret;
}

static u64
gf100_devinit_disable(struct nvkm_devinit *init)
{
	struct nvkm_device *device = init->subdev.device;
	u32 r022500 = nvkm_rd32(device, 0x022500);
	u64 disable = 0ULL;

	if (r022500 & 0x00000001)
		disable |= (1ULL << NVKM_ENGINE_DISP);

	if (r022500 & 0x00000002) {
		disable |= (1ULL << NVKM_ENGINE_MSPDEC);
		disable |= (1ULL << NVKM_ENGINE_MSPPP);
	}

	if (r022500 & 0x00000004)
		disable |= (1ULL << NVKM_ENGINE_MSVLD);
	if (r022500 & 0x00000008)
		disable |= (1ULL << NVKM_ENGINE_MSENC);
	if (r022500 & 0x00000100)
		disable |= (1ULL << NVKM_ENGINE_CE0);
	if (r022500 & 0x00000200)
		disable |= (1ULL << NVKM_ENGINE_CE1);

	return disable;
}

static const struct nvkm_devinit_func
gf100_devinit = {
	.preinit = nv50_devinit_preinit,
	.init = nv50_devinit_init,
	.post = nv04_devinit_post,
	.pll_set = gf100_devinit_pll_set,
	.disable = gf100_devinit_disable,
};

int
gf100_devinit_new(struct nvkm_device *device, int index,
		struct nvkm_devinit **pinit)
{
	return nv50_devinit_new_(&gf100_devinit, device, index, pinit);
}
