/*	$NetBSD: gr.h,v 1.2 2018/08/27 04:58:30 riastradh Exp $	*/

#ifndef __NVKM_GR_H__
#define __NVKM_GR_H__
#include <core/engine.h>

struct nvkm_gr {
	const struct nvkm_gr_func *func;
	struct nvkm_engine engine;
};

u64 nvkm_gr_units(struct nvkm_gr *);
int nvkm_gr_tlb_flush(struct nvkm_gr *);

int nv04_gr_new(struct nvkm_device *, int, struct nvkm_gr **);
int nv10_gr_new(struct nvkm_device *, int, struct nvkm_gr **);
int nv15_gr_new(struct nvkm_device *, int, struct nvkm_gr **);
int nv17_gr_new(struct nvkm_device *, int, struct nvkm_gr **);
int nv20_gr_new(struct nvkm_device *, int, struct nvkm_gr **);
int nv25_gr_new(struct nvkm_device *, int, struct nvkm_gr **);
int nv2a_gr_new(struct nvkm_device *, int, struct nvkm_gr **);
int nv30_gr_new(struct nvkm_device *, int, struct nvkm_gr **);
int nv34_gr_new(struct nvkm_device *, int, struct nvkm_gr **);
int nv35_gr_new(struct nvkm_device *, int, struct nvkm_gr **);
int nv40_gr_new(struct nvkm_device *, int, struct nvkm_gr **);
int nv44_gr_new(struct nvkm_device *, int, struct nvkm_gr **);
int nv50_gr_new(struct nvkm_device *, int, struct nvkm_gr **);
int g84_gr_new(struct nvkm_device *, int, struct nvkm_gr **);
int gt200_gr_new(struct nvkm_device *, int, struct nvkm_gr **);
int mcp79_gr_new(struct nvkm_device *, int, struct nvkm_gr **);
int gt215_gr_new(struct nvkm_device *, int, struct nvkm_gr **);
int mcp89_gr_new(struct nvkm_device *, int, struct nvkm_gr **);
int gf100_gr_new(struct nvkm_device *, int, struct nvkm_gr **);
int gf104_gr_new(struct nvkm_device *, int, struct nvkm_gr **);
int gf108_gr_new(struct nvkm_device *, int, struct nvkm_gr **);
int gf110_gr_new(struct nvkm_device *, int, struct nvkm_gr **);
int gf117_gr_new(struct nvkm_device *, int, struct nvkm_gr **);
int gf119_gr_new(struct nvkm_device *, int, struct nvkm_gr **);
int gk104_gr_new(struct nvkm_device *, int, struct nvkm_gr **);
int gk110_gr_new(struct nvkm_device *, int, struct nvkm_gr **);
int gk110b_gr_new(struct nvkm_device *, int, struct nvkm_gr **);
int gk208_gr_new(struct nvkm_device *, int, struct nvkm_gr **);
int gk20a_gr_new(struct nvkm_device *, int, struct nvkm_gr **);
int gm107_gr_new(struct nvkm_device *, int, struct nvkm_gr **);
int gm204_gr_new(struct nvkm_device *, int, struct nvkm_gr **);
int gm206_gr_new(struct nvkm_device *, int, struct nvkm_gr **);
int gm20b_gr_new(struct nvkm_device *, int, struct nvkm_gr **);
#endif
