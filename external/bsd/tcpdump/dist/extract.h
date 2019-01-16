/*
 * Copyright (c) 1992, 1993, 1994, 1995, 1996
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that: (1) source code distributions
 * retain the above copyright notice and this paragraph in its entirety, (2)
 * distributions including binary code include the above copyright notice and
 * this paragraph in its entirety in the documentation or other materials
 * provided with the distribution, and (3) all advertising materials mentioning
 * features or use of this software display the following acknowledgement:
 * ``This product includes software developed by the University of California,
 * Lawrence Berkeley Laboratory and its contributors.'' Neither the name of
 * the University nor the names of its contributors may be used to endorse
 * or promote products derived from this software without specific prior
 * written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */

#ifdef __NetBSD__
#include <string.h>

/*
 * Do it the portable way and let the compiler optimize the code
 */
static inline uint16_t EXTRACT_16BITS(const void *p)
{
	uint16_t t;
	memcpy(&t, p, sizeof(t));
	return ntohs(t);
}

static inline uint32_t EXTRACT_24BITS(const void *p)
{
	uint8_t t[3];
	memcpy(t, p, sizeof(t));
	return
	    ((uint32_t)t[0] << 16) |
	    ((uint32_t)t[1] << 8) |
	    t[2];
}

static inline uint32_t EXTRACT_32BITS(const void *p)
{
	uint32_t t;
	memcpy(&t, p, sizeof(t));
	return ntohl(t);
}


static inline uint64_t EXTRACT_48BITS(const void *p)
{
	uint8_t t[6];
	memcpy(t, p, sizeof(t));
	return
	    ((uint64_t)t[0] << 40) |
	    ((uint64_t)t[1] << 32) |
	    ((uint64_t)t[2] << 24) |
	    ((uint64_t)t[3] << 16) |
	    ((uint64_t)t[4] <<  8) |
	    t[5];
}

static inline uint64_t EXTRACT_64BITS(const void *p)
{
	uint32_t t[2];
	memcpy(&t[0], p, sizeof(t[0]));
	memcpy(&t[1], (const uint8_t *)p + sizeof(t[0]), sizeof(t[1]));
	return ((uint64_t)ntohl(t[0]) << 32) | ntohl(t[1]);
}

static inline uint8_t EXTRACT_LE_8BITS(const void *p)
{
	uint8_t t[1];
	memcpy(t, p, sizeof(t));
	return t[0];
}

static inline uint16_t EXTRACT_LE_16BITS(const void *p)
{
	uint8_t t[2];
	memcpy(t, p, sizeof(t));
	return
	    ((uint16_t)t[1] << 8) |
	    t[0];
}

static inline uint32_t EXTRACT_LE_24BITS(const void *p)
{
	uint8_t t[3];
	memcpy(t, p, sizeof(t));
	return
	    ((uint32_t)t[2] << 16) |
	    ((uint32_t)t[1] << 8) |
	    t[0];
}

static inline uint32_t EXTRACT_LE_32BITS(const void *p)
{
	uint8_t t[4];
	memcpy(t, p, sizeof(t));
	return
	    ((uint32_t)t[3] << 24) |
	    ((uint32_t)t[2] << 16) |
	    ((uint32_t)t[1] << 8) |
	    t[0];
}

static inline uint64_t EXTRACT_LE_64BITS(const void *p)
{
	uint8_t t[8];
	memcpy(&t, p, sizeof(t));
	return
	    ((uint64_t)t[7] << 56) |
	    ((uint64_t)t[6] << 48) |
	    ((uint64_t)t[5] << 40) |
	    ((uint64_t)t[4] << 32) |
	    ((uint64_t)t[3] << 24) |
	    ((uint64_t)t[2] << 16) |
	    ((uint64_t)t[1] << 8) |
	    t[0];
}

#define EXTRACT_8BITS(p)	EXTRACT_LE_8BITS(p)

#else /* Fast & Loose */
/*
 * For 8-bit values; provided for the sake of completeness.  Byte order
 * isn't relevant, and alignment isn't an issue.
 */
#define EXTRACT_8BITS(p)	(*(p))
#define EXTRACT_LE_8BITS(p)	(*(p))

/*
 * Inline functions or macros to extract possibly-unaligned big-endian
 * integral values.
 */
#include "funcattrs.h"

/*
 * If we have versions of GCC or Clang that support an __attribute__
 * to say "if we're building with unsigned behavior sanitization,
 * don't complain about undefined behavior in this function", we
 * label these functions with that attribute - we *know* it's undefined
 * in the C standard, but we *also* know it does what we want with
 * the ISA we're targeting and the compiler we're using.
 *
 * For GCC 4.9.0 and later, we use __attribute__((no_sanitize_undefined));
 * pre-5.0 GCC doesn't have __has_attribute, and I'm not sure whether
 * GCC or Clang first had __attribute__((no_sanitize(XXX)).
 *
 * For Clang, we check for __attribute__((no_sanitize(XXX)) with
 * __has_attribute, as there are versions of Clang that support
 * __attribute__((no_sanitize("undefined")) but don't support
 * __attribute__((no_sanitize_undefined)).
 *
 * We define this here, rather than in funcattrs.h, because we
 * only want it used here, we don't want it to be broadly used.
 * (Any printer will get this defined, but this should at least
 * make it harder for people to find.)
 */
#if defined(__GNUC__) && ((__GNUC__ * 100 + __GNUC_MINOR__) >= 409)
#define UNALIGNED_OK	__attribute__((no_sanitize_undefined))
#elif __has_attribute(no_sanitize)
#define UNALIGNED_OK	__attribute__((no_sanitize("undefined")))
#else
#define UNALIGNED_OK
#endif

#ifdef LBL_ALIGN
/*
 * The processor doesn't natively handle unaligned loads.
 */
#if defined(__GNUC__) && defined(HAVE___ATTRIBUTE__) && \
    (defined(__alpha) || defined(__alpha__) || \
     defined(__mips) || defined(__mips__))

/*
* This is a GCC-compatible compiler and we have __attribute__, which
 * we assume that mean we have __attribute__((packed)), and this is
 * MIPS or Alpha, which has instructions that can help when doing
 * unaligned loads.
 *
 * Declare packed structures containing a uint16_t and a uint32_t,
 * cast the pointer to point to one of those, and fetch through it;
 * the GCC manual doesn't appear to explicitly say that
 * __attribute__((packed)) causes the compiler to generate unaligned-safe
 * code, but it apppears to do so.
 *
 * We do this in case the compiler can generate code using those
 * instructions to do an unaligned load and pass stuff to "ntohs()" or
 * "ntohl()", which might be better than than the code to fetch the
 * bytes one at a time and assemble them.  (That might not be the
 * case on a little-endian platform, such as DEC's MIPS machines and
 * Alpha machines, where "ntohs()" and "ntohl()" might not be done
 * inline.)
 *
 * We do this only for specific architectures because, for example,
 * at least some versions of GCC, when compiling for 64-bit SPARC,
 * generate code that assumes alignment if we do this.
 *
 * XXX - add other architectures and compilers as possible and
 * appropriate.
 *
 * HP's C compiler, indicated by __HP_cc being defined, supports
 * "#pragma unaligned N" in version A.05.50 and later, where "N"
 * specifies a number of bytes at which the typedef on the next
 * line is aligned, e.g.
 *
 *	#pragma unalign 1
 *	typedef uint16_t unaligned_uint16_t;
 *
 * to define unaligned_uint16_t as a 16-bit unaligned data type.
 * This could be presumably used, in sufficiently recent versions of
 * the compiler, with macros similar to those below.  This would be
 * useful only if that compiler could generate better code for PA-RISC
 * or Itanium than would be generated by a bunch of shifts-and-ORs.
 *
 * DEC C, indicated by __DECC being defined, has, at least on Alpha,
 * an __unaligned qualifier that can be applied to pointers to get the
 * compiler to generate code that does unaligned loads and stores when
 * dereferencing the pointer in question.
 *
 * XXX - what if the native C compiler doesn't support
 * __attribute__((packed))?  How can we get it to generate unaligned
 * accesses for *specific* items?
 */
typedef struct {
	uint16_t	val;
} __attribute__((packed)) unaligned_uint16_t;

typedef struct {
	uint32_t	val;
} __attribute__((packed)) unaligned_uint32_t;

UNALIGNED_OK static inline uint16_t
EXTRACT_16BITS(const void *p)
{
	return ((uint16_t)ntohs(((const unaligned_uint16_t *)(p))->val));
}

UNALIGNED_OK static inline uint32_t
EXTRACT_32BITS(const void *p)
{
	return ((uint32_t)ntohl(((const unaligned_uint32_t *)(p))->val));
}

UNALIGNED_OK static inline uint64_t
EXTRACT_64BITS(const void *p)
{
	return ((uint64_t)(((uint64_t)ntohl(((const unaligned_uint32_t *)(p) + 0)->val)) << 32 |
		((uint64_t)ntohl(((const unaligned_uint32_t *)(p) + 1)->val)) << 0));
}

#else /* have to do it a byte at a time */
/*
 * This isn't a GCC-compatible compiler, we don't have __attribute__,
 * or we do but we don't know of any better way with this instruction
 * set to do unaligned loads, so do unaligned loads of big-endian
 * quantities the hard way - fetch the bytes one at a time and
 * assemble them.
 */
#define EXTRACT_16BITS(p) \
	((uint16_t)(((uint16_t)(*((const uint8_t *)(p) + 0)) << 8) | \
	            ((uint16_t)(*((const uint8_t *)(p) + 1)) << 0)))
#define EXTRACT_32BITS(p) \
	((uint32_t)(((uint32_t)(*((const uint8_t *)(p) + 0)) << 24) | \
	            ((uint32_t)(*((const uint8_t *)(p) + 1)) << 16) | \
	            ((uint32_t)(*((const uint8_t *)(p) + 2)) << 8) | \
	            ((uint32_t)(*((const uint8_t *)(p) + 3)) << 0)))
#define EXTRACT_64BITS(p) \
	((uint64_t)(((uint64_t)(*((const uint8_t *)(p) + 0)) << 56) | \
	            ((uint64_t)(*((const uint8_t *)(p) + 1)) << 48) | \
	            ((uint64_t)(*((const uint8_t *)(p) + 2)) << 40) | \
	            ((uint64_t)(*((const uint8_t *)(p) + 3)) << 32) | \
	            ((uint64_t)(*((const uint8_t *)(p) + 4)) << 24) | \
	            ((uint64_t)(*((const uint8_t *)(p) + 5)) << 16) | \
	            ((uint64_t)(*((const uint8_t *)(p) + 6)) << 8) | \
	            ((uint64_t)(*((const uint8_t *)(p) + 7)) << 0)))
#endif /* must special-case unaligned accesses */
#else /* LBL_ALIGN */
/*
 * The processor natively handles unaligned loads, so we can just
 * cast the pointer and fetch through it.
 */
static inline uint16_t UNALIGNED_OK
EXTRACT_16BITS(const void *p)
{
	return ((uint16_t)ntohs(*(const uint16_t *)(p)));
}

static inline uint32_t UNALIGNED_OK
EXTRACT_32BITS(const void *p)
{
	return ((uint32_t)ntohl(*(const uint32_t *)(p)));
}

static inline uint64_t UNALIGNED_OK
EXTRACT_64BITS(const void *p)
{
	return ((uint64_t)(((uint64_t)ntohl(*((const uint32_t *)(p) + 0))) << 32 |
		((uint64_t)ntohl(*((const uint32_t *)(p) + 1))) << 0));

}

#endif /* LBL_ALIGN */

#define EXTRACT_24BITS(p) \
	((uint32_t)(((uint32_t)(*((const uint8_t *)(p) + 0)) << 16) | \
	            ((uint32_t)(*((const uint8_t *)(p) + 1)) << 8) | \
	            ((uint32_t)(*((const uint8_t *)(p) + 2)) << 0)))

#define EXTRACT_40BITS(p) \
	((uint64_t)(((uint64_t)(*((const uint8_t *)(p) + 0)) << 32) | \
	            ((uint64_t)(*((const uint8_t *)(p) + 1)) << 24) | \
	            ((uint64_t)(*((const uint8_t *)(p) + 2)) << 16) | \
	            ((uint64_t)(*((const uint8_t *)(p) + 3)) << 8) | \
	            ((uint64_t)(*((const uint8_t *)(p) + 4)) << 0)))

#define EXTRACT_48BITS(p) \
	((uint64_t)(((uint64_t)(*((const uint8_t *)(p) + 0)) << 40) | \
	            ((uint64_t)(*((const uint8_t *)(p) + 1)) << 32) | \
	            ((uint64_t)(*((const uint8_t *)(p) + 2)) << 24) | \
	            ((uint64_t)(*((const uint8_t *)(p) + 3)) << 16) | \
	            ((uint64_t)(*((const uint8_t *)(p) + 4)) << 8) | \
	            ((uint64_t)(*((const uint8_t *)(p) + 5)) << 0)))

#define EXTRACT_56BITS(p) \
	((uint64_t)(((uint64_t)(*((const uint8_t *)(p) + 0)) << 48) | \
	            ((uint64_t)(*((const uint8_t *)(p) + 1)) << 40) | \
	            ((uint64_t)(*((const uint8_t *)(p) + 2)) << 32) | \
	            ((uint64_t)(*((const uint8_t *)(p) + 3)) << 24) | \
	            ((uint64_t)(*((const uint8_t *)(p) + 4)) << 16) | \
	            ((uint64_t)(*((const uint8_t *)(p) + 5)) << 8) | \
	            ((uint64_t)(*((const uint8_t *)(p) + 6)) << 0)))

/*
 * Macros to extract possibly-unaligned little-endian integral values.
 * XXX - do loads on little-endian machines that support unaligned loads?
 */
#define EXTRACT_LE_16BITS(p) \
	((uint16_t)(((uint16_t)(*((const uint8_t *)(p) + 1)) << 8) | \
	            ((uint16_t)(*((const uint8_t *)(p) + 0)) << 0)))
#define EXTRACT_LE_32BITS(p) \
	((uint32_t)(((uint32_t)(*((const uint8_t *)(p) + 3)) << 24) | \
	            ((uint32_t)(*((const uint8_t *)(p) + 2)) << 16) | \
	            ((uint32_t)(*((const uint8_t *)(p) + 1)) << 8) | \
	            ((uint32_t)(*((const uint8_t *)(p) + 0)) << 0)))
#define EXTRACT_LE_24BITS(p) \
	((uint32_t)(((uint32_t)(*((const uint8_t *)(p) + 2)) << 16) | \
	            ((uint32_t)(*((const uint8_t *)(p) + 1)) << 8) | \
	            ((uint32_t)(*((const uint8_t *)(p) + 0)) << 0)))
#define EXTRACT_LE_64BITS(p) \
	((uint64_t)(((uint64_t)(*((const uint8_t *)(p) + 7)) << 56) | \
	            ((uint64_t)(*((const uint8_t *)(p) + 6)) << 48) | \
	            ((uint64_t)(*((const uint8_t *)(p) + 5)) << 40) | \
	            ((uint64_t)(*((const uint8_t *)(p) + 4)) << 32) | \
	            ((uint64_t)(*((const uint8_t *)(p) + 3)) << 24) | \
	            ((uint64_t)(*((const uint8_t *)(p) + 2)) << 16) | \
	            ((uint64_t)(*((const uint8_t *)(p) + 1)) << 8) | \
	            ((uint64_t)(*((const uint8_t *)(p) + 0)) << 0)))

#endif /* __NetBSD__ */

/*
 * Macros to check the presence of the values in question.
 */
#define ND_TTEST_8BITS(p) ND_TTEST2(*(p), 1)
#define ND_TCHECK_8BITS(p) ND_TCHECK2(*(p), 1)

#define ND_TTEST_16BITS(p) ND_TTEST2(*(p), 2)
#define ND_TCHECK_16BITS(p) ND_TCHECK2(*(p), 2)

#define ND_TTEST_24BITS(p) ND_TTEST2(*(p), 3)
#define ND_TCHECK_24BITS(p) ND_TCHECK2(*(p), 3)

#define ND_TTEST_32BITS(p) ND_TTEST2(*(p), 4)
#define ND_TCHECK_32BITS(p) ND_TCHECK2(*(p), 4)

#define ND_TTEST_40BITS(p) ND_TTEST2(*(p), 5)
#define ND_TCHECK_40BITS(p) ND_TCHECK2(*(p), 5)

#define ND_TTEST_48BITS(p) ND_TTEST2(*(p), 6)
#define ND_TCHECK_48BITS(p) ND_TCHECK2(*(p), 6)

#define ND_TTEST_56BITS(p) ND_TTEST2(*(p), 7)
#define ND_TCHECK_56BITS(p) ND_TCHECK2(*(p), 7)

#define ND_TTEST_64BITS(p) ND_TTEST2(*(p), 8)
#define ND_TCHECK_64BITS(p) ND_TCHECK2(*(p), 8)

#define ND_TTEST_128BITS(p) ND_TTEST2(*(p), 16)
#define ND_TCHECK_128BITS(p) ND_TCHECK2(*(p), 16)
