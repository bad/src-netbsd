/*	$NetBSD: nouveau_nvkm_engine_disp_oimmgk104.c,v 1.2 2018/08/27 04:58:31 riastradh Exp $	*/

/*
 * Copyright 2012 Red Hat Inc.
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
__KERNEL_RCSID(0, "$NetBSD: nouveau_nvkm_engine_disp_oimmgk104.c,v 1.2 2018/08/27 04:58:31 riastradh Exp $");

#include "channv50.h"
#include "rootnv50.h"

#include <nvif/class.h>

const struct nv50_disp_pioc_oclass
gk104_disp_oimm_oclass = {
	.base.oclass = GK104_DISP_OVERLAY,
	.base.minver = 0,
	.base.maxver = 0,
	.ctor = nv50_disp_oimm_new,
	.func = &gf119_disp_pioc_func,
	.chid = 9,
};
