/*	$NetBSD: rumpnet_syscalls.c,v 1.4 2016/01/26 23:12:18 pooka Exp $	*/

/* AUTOMATICALLY GENERATED BY makerumpsyscalls.sh */

#include <sys/cdefs.h>
__KERNEL_RCSID(0, "$NetBSD: rumpnet_syscalls.c,v 1.4 2016/01/26 23:12:18 pooka Exp $");

#include <sys/param.h>

#include <rump-sys/kern.h>

extern sy_call_t sys_recvmsg;
extern sy_call_t sys_sendmsg;
extern sy_call_t sys_recvfrom;
extern sy_call_t sys_accept;
extern sy_call_t sys_getpeername;
extern sy_call_t sys_getsockname;
extern sy_call_t sys_connect;
extern sy_call_t sys_bind;
extern sy_call_t sys_setsockopt;
extern sy_call_t sys_listen;
extern sy_call_t sys_getsockopt;
extern sy_call_t sys_sendto;
extern sy_call_t sys_shutdown;
extern sy_call_t sys_socketpair;
extern sy_call_t sys___socket30;
extern sy_call_t sys_paccept;
extern sy_call_t sys_recvmmsg;
extern sy_call_t sys_sendmmsg;

static const struct rump_onesyscall mysys[] = {
	{ 27,	sys_recvmsg },
	{ 28,	sys_sendmsg },
	{ 29,	sys_recvfrom },
	{ 30,	sys_accept },
	{ 31,	sys_getpeername },
	{ 32,	sys_getsockname },
	{ 98,	sys_connect },
	{ 104,	sys_bind },
	{ 105,	sys_setsockopt },
	{ 106,	sys_listen },
	{ 118,	sys_getsockopt },
	{ 133,	sys_sendto },
	{ 134,	sys_shutdown },
	{ 135,	sys_socketpair },
	{ 394,	sys___socket30 },
	{ 456,	sys_paccept },
	{ 475,	sys_recvmmsg },
	{ 476,	sys_sendmmsg },
};

RUMP_COMPONENT(RUMP_COMPONENT_SYSCALL)
{

	rump_syscall_boot_establish(mysys, __arraycount(mysys));
}
