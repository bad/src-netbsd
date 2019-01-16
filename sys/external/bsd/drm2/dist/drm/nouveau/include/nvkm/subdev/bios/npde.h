/*	$NetBSD: npde.h,v 1.2 2018/08/27 04:58:30 riastradh Exp $	*/

#ifndef __NVBIOS_NPDE_H__
#define __NVBIOS_NPDE_H__
struct nvbios_npdeT {
	u32 image_size;
	bool last;
};

u32 nvbios_npdeTe(struct nvkm_bios *, u32);
u32 nvbios_npdeTp(struct nvkm_bios *, u32, struct nvbios_npdeT *);
#endif
