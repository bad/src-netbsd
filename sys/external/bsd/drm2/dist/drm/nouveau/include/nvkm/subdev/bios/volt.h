/*	$NetBSD: volt.h,v 1.2 2018/08/27 04:58:30 riastradh Exp $	*/

#ifndef __NVBIOS_VOLT_H__
#define __NVBIOS_VOLT_H__

enum nvbios_volt_type {
	NVBIOS_VOLT_GPIO = 0,
	NVBIOS_VOLT_PWM,
};

struct nvbios_volt {
	enum nvbios_volt_type type;
	u32 min;
	u32 max;
	u32 base;

	/* GPIO mode */
	u8  vidmask;
	s16 step;

	/* PWM mode */
	u32 pwm_freq;
	u32 pwm_range;
};

u16 nvbios_volt_table(struct nvkm_bios *, u8 *ver, u8 *hdr, u8 *cnt, u8 *len);
u16 nvbios_volt_parse(struct nvkm_bios *, u8 *ver, u8 *hdr, u8 *cnt, u8 *len,
		      struct nvbios_volt *);

struct nvbios_volt_entry {
	u32 voltage;
	u8  vid;
};

u16 nvbios_volt_entry(struct nvkm_bios *, int idx, u8 *ver, u8 *len);
u16 nvbios_volt_entry_parse(struct nvkm_bios *, int idx, u8 *ver, u8 *len,
			    struct nvbios_volt_entry *);
#endif
