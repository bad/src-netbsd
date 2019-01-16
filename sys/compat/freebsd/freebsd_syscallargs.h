/* $NetBSD: freebsd_syscallargs.h,v 1.92 2018/08/10 21:47:14 pgoyette Exp $ */

/*
 * System call argument lists.
 *
 * DO NOT EDIT-- this file is automatically generated.
 * created from	NetBSD: syscalls.master,v 1.72 2018/01/06 16:41:23 kamil Exp
 */

#ifndef _FREEBSD_SYS_SYSCALLARGS_H_
#define	_FREEBSD_SYS_SYSCALLARGS_H_

/* Forward declaration */
struct lwp;

#define	FREEBSD_SYS_MAXSYSARGS	8

#undef	syscallarg
#define	syscallarg(x)							\
	union {								\
		register_t pad;						\
		struct { x datum; } le;					\
		struct { /* LINTED zero array dimension */		\
			int8_t pad[  /* CONSTCOND */			\
				(sizeof (register_t) < sizeof (x))	\
				? 0					\
				: sizeof (register_t) - sizeof (x)];	\
			x datum;					\
		} be;							\
	}

#undef check_syscall_args
#define check_syscall_args(call) /*LINTED*/ \
	typedef char call##_check_args[sizeof (struct call##_args) \
		<= FREEBSD_SYS_MAXSYSARGS * sizeof (register_t) ? 1 : -1];

struct sys_exit_args;

struct sys_read_args;

struct sys_write_args;

struct sys_open_args;

struct sys_close_args;

struct compat_50_sys_wait4_args;

struct compat_43_sys_creat_args;

struct sys_link_args;

struct sys_unlink_args;

struct sys_chdir_args;

struct sys_fchdir_args;

struct compat_50_sys_mknod_args;

struct sys_chmod_args;

struct sys_chown_args;

struct sys_obreak_args;

struct compat_20_sys_getfsstat_args;

struct compat_43_sys_lseek_args;

struct freebsd_sys_mount_args {
	syscallarg(int) type;
	syscallarg(const char *) path;
	syscallarg(int) flags;
	syscallarg(void *) data;
};
check_syscall_args(freebsd_sys_mount)

struct sys_unmount_args;

struct sys_setuid_args;

struct freebsd_sys_ptrace_args {
	syscallarg(int) req;
	syscallarg(pid_t) pid;
	syscallarg(void *) addr;
	syscallarg(int) data;
};
check_syscall_args(freebsd_sys_ptrace)

struct sys_recvmsg_args;

struct sys_sendmsg_args;

struct sys_recvfrom_args;

struct sys_accept_args;

struct sys_getpeername_args;

struct sys_getsockname_args;

struct sys_access_args;

struct sys_chflags_args;

struct sys_fchflags_args;

struct sys_kill_args;

struct compat_43_sys_stat_args;

struct compat_43_sys_lstat_args;

struct sys_dup_args;

struct sys_profil_args;
#ifdef KTRACE

struct sys_ktrace_args;
#else
#endif

struct compat_13_sys_sigaction_args;

struct compat_13_sys_sigprocmask_args;

struct sys___getlogin_args;

struct sys___setlogin_args;

struct sys_acct_args;

struct compat_13_sys_sigaltstack_args;

struct freebsd_sys_ioctl_args {
	syscallarg(int) fd;
	syscallarg(u_long) com;
	syscallarg(void *) data;
};
check_syscall_args(freebsd_sys_ioctl)

struct sys_reboot_args;

struct sys_revoke_args;

struct sys_symlink_args;

struct sys_readlink_args;

struct sys_execve_args;

struct sys_umask_args;

struct sys_chroot_args;

struct compat_43_sys_fstat_args;

struct compat_43_sys_getkerninfo_args;

struct freebsd_sys_msync_args {
	syscallarg(void *) addr;
	syscallarg(size_t) len;
	syscallarg(int) flags;
};
check_syscall_args(freebsd_sys_msync)

struct compat_43_sys_mmap_args;

struct sys_ovadvise_args;

struct sys_munmap_args;

struct sys_mprotect_args;

struct sys_madvise_args;

struct sys_mincore_args;

struct sys_getgroups_args;

struct sys_setgroups_args;

struct sys_setpgid_args;

struct compat_50_sys_setitimer_args;

struct compat_12_sys_swapon_args;

struct compat_50_sys_getitimer_args;

struct compat_43_sys_gethostname_args;

struct compat_43_sys_sethostname_args;

struct sys_dup2_args;

struct sys_fcntl_args;

struct compat_50_sys_select_args;

struct sys_fsync_args;

struct sys_setpriority_args;

struct compat_30_sys_socket_args;

struct sys_connect_args;

struct compat_43_sys_accept_args;

struct sys_getpriority_args;

struct compat_43_sys_send_args;

struct compat_43_sys_recv_args;

struct freebsd_sys_sigreturn_args {
	syscallarg(struct freebsd_sigcontext *) scp;
};
check_syscall_args(freebsd_sys_sigreturn)

struct sys_bind_args;

struct sys_setsockopt_args;

struct sys_listen_args;

struct compat_43_sys_sigvec_args;

struct compat_43_sys_sigblock_args;

struct compat_43_sys_sigsetmask_args;

struct compat_13_sys_sigsuspend_args;

struct compat_43_sys_sigstack_args;

struct compat_43_sys_recvmsg_args;

struct compat_43_sys_sendmsg_args;
#ifdef TRACE

struct sys_vtrace_args;
#else
#endif

struct compat_50_sys_gettimeofday_args;

struct compat_50_sys_getrusage_args;

struct sys_getsockopt_args;

struct sys_readv_args;

struct sys_writev_args;

struct compat_50_sys_settimeofday_args;

struct sys_fchown_args;

struct sys_fchmod_args;

struct compat_43_sys_recvfrom_args;

struct sys_setreuid_args;

struct sys_setregid_args;

struct sys_rename_args;

struct compat_43_sys_truncate_args;

struct compat_43_sys_ftruncate_args;

struct sys_flock_args;

struct sys_mkfifo_args;

struct sys_sendto_args;

struct sys_shutdown_args;

struct sys_socketpair_args;

struct sys_mkdir_args;

struct sys_rmdir_args;

struct compat_50_sys_utimes_args;

struct compat_50_sys_adjtime_args;

struct compat_43_sys_getpeername_args;

struct compat_43_sys_sethostid_args;

struct compat_43_sys_getrlimit_args;

struct compat_43_sys_setrlimit_args;

struct compat_43_sys_killpg_args;

struct compat_50_sys_quotactl_args;

struct compat_43_sys_getsockname_args;

struct compat_43_sys_getdirentries_args;

struct compat_20_sys_statfs_args;

struct compat_20_sys_fstatfs_args;

struct compat_30_sys_getfh_args;

struct compat_09_sys_getdomainname_args;

struct compat_09_sys_setdomainname_args;

struct compat_09_sys_uname_args;

struct sys_sysarch_args;

struct freebsd_sys_rtprio_args {
	syscallarg(int) function;
	syscallarg(pid_t) pid;
	syscallarg(struct freebsd_rtprio *) rtp;
};
check_syscall_args(freebsd_sys_rtprio)
#if defined(SYSVSEM) && !defined(_LP64)

struct freebsd_sys_semsys_args {
	syscallarg(int) which;
	syscallarg(int) a2;
	syscallarg(int) a3;
	syscallarg(int) a4;
	syscallarg(int) a5;
};
check_syscall_args(freebsd_sys_semsys)
#else
#endif
#if defined(SYSVMSG) && !defined(_LP64)

struct freebsd_sys_msgsys_args {
	syscallarg(int) which;
	syscallarg(int) a2;
	syscallarg(int) a3;
	syscallarg(int) a4;
	syscallarg(int) a5;
	syscallarg(int) a6;
};
check_syscall_args(freebsd_sys_msgsys)
#else
#endif
#if defined(SYSVSHM) && !defined(_LP64)

struct freebsd_sys_shmsys_args {
	syscallarg(int) which;
	syscallarg(int) a2;
	syscallarg(int) a3;
	syscallarg(int) a4;
};
check_syscall_args(freebsd_sys_shmsys)
#else
#endif

struct sys_pread_args;

struct sys_pwrite_args;
#ifdef NTP

struct freebsd_ntp_adjtime_args {
	syscallarg(struct freebsd_timex *) tp;
};
check_syscall_args(freebsd_ntp_adjtime)
#else
#endif

struct sys_setgid_args;

struct sys_setegid_args;

struct sys_seteuid_args;

struct compat_12_sys_stat_args;

struct compat_12_sys_fstat_args;

struct compat_12_sys_lstat_args;

struct sys_pathconf_args;

struct sys_fpathconf_args;

struct sys_getrlimit_args;

struct sys_setrlimit_args;

struct compat_12_sys_getdirentries_args;

struct freebsd_sys_mmap_args {
	syscallarg(void *) addr;
	syscallarg(size_t) len;
	syscallarg(int) prot;
	syscallarg(int) flags;
	syscallarg(int) fd;
	syscallarg(long) pad;
	syscallarg(off_t) pos;
};
check_syscall_args(freebsd_sys_mmap)

struct sys_lseek_args;

struct sys_truncate_args;

struct sys_ftruncate_args;

struct freebsd_sys_sysctl_args {
	syscallarg(int *) name;
	syscallarg(u_int) namelen;
	syscallarg(void *) old;
	syscallarg(size_t *) oldlenp;
	syscallarg(void *) new;
	syscallarg(size_t) newlen;
};
check_syscall_args(freebsd_sys_sysctl)

struct sys_mlock_args;

struct sys_munlock_args;
#ifdef FREEBSD_BASED_ON_44LITE_R2

struct freebsd_sys_undelete_args {
	syscallarg(char *) path;
};
check_syscall_args(freebsd_sys_undelete)
#else
#endif

struct compat_50_sys_futimes_args;

struct sys_getpgid_args;
#if 0

struct sys_reboot_args;
#else
#endif

struct sys_poll_args;
#ifdef SYSVSEM

struct compat_14_sys___semctl_args;

struct sys_semget_args;

struct sys_semop_args;

struct sys_semconfig_args;
#else
#endif
#ifdef SYSVMSG

struct compat_14_sys_msgctl_args;

struct sys_msgget_args;

struct sys_msgsnd_args;

struct sys_msgrcv_args;
#else
#endif
#ifdef SYSVSHM

struct sys_shmat_args;

struct compat_14_sys_shmctl_args;

struct sys_shmdt_args;

struct sys_shmget_args;
#else
#endif

struct compat_50_sys_clock_gettime_args;

struct compat_50_sys_clock_settime_args;

struct compat_50_sys_clock_getres_args;

struct compat_50_sys_nanosleep_args;

struct sys_minherit_args;

struct freebsd_sys_rfork_args {
	syscallarg(int) flags;
};
check_syscall_args(freebsd_sys_rfork)

struct sys_lchown_args;

struct compat_30_sys_getdents_args;

struct sys_lchmod_args;

struct sys_lchown_args;

struct compat_50_sys_lutimes_args;

struct sys___msync13_args;

struct compat_30_sys___stat13_args;

struct compat_30_sys___fstat13_args;

struct compat_30_sys___lstat13_args;

struct compat_20_sys_fhstatfs_args;

struct compat_30_sys_fhopen_args;

struct compat_30_sys_fhstat_args;

struct sys_getsid_args;

struct sys_mlockall_args;

struct sys___getcwd_args;

struct freebsd_sys_sched_setparam_args {
	syscallarg(pid_t) pid;
	syscallarg(const struct freebsd_sched_param *) sp;
};
check_syscall_args(freebsd_sys_sched_setparam)

struct freebsd_sys_sched_getparam_args {
	syscallarg(pid_t) pid;
	syscallarg(struct freebsd_sched_param *) sp;
};
check_syscall_args(freebsd_sys_sched_getparam)

struct freebsd_sys_sched_setscheduler_args {
	syscallarg(pid_t) pid;
	syscallarg(int) policy;
	syscallarg(const struct sched_param *) sp;
};
check_syscall_args(freebsd_sys_sched_setscheduler)

struct freebsd_sys_sched_getscheduler_args {
	syscallarg(pid_t) pid;
};
check_syscall_args(freebsd_sys_sched_getscheduler)

struct freebsd_sys_sched_get_priority_max_args {
	syscallarg(int) policy;
};
check_syscall_args(freebsd_sys_sched_get_priority_max)

struct freebsd_sys_sched_get_priority_min_args {
	syscallarg(int) policy;
};
check_syscall_args(freebsd_sys_sched_get_priority_min)

struct freebsd_sys_utrace_args {
	syscallarg(void *) addr;
	syscallarg(size_t) len;
};
check_syscall_args(freebsd_sys_utrace)

struct sys___sigprocmask14_args;

struct sys___sigsuspend14_args;

struct freebsd_sys_sigaction4_args {
	syscallarg(int) signum;
	syscallarg(const struct freebsd_sigaction4 *) nsa;
	syscallarg(struct freebsd_sigaction4 *) osa;
};
check_syscall_args(freebsd_sys_sigaction4)

struct sys___sigpending14_args;

struct sys_lchflags_args;

struct sys_uuidgen_args;

struct sys__ksem_close_args;

struct sys__ksem_post_args;

struct sys__ksem_wait_args;

struct sys__ksem_trywait_args;

struct sys__ksem_unlink_args;

struct sys__ksem_getvalue_args;

struct sys__ksem_destroy_args;

/*
 * System call prototypes.
 */

int	sys_nosys(struct lwp *, const void *, register_t *);

int	sys_exit(struct lwp *, const struct sys_exit_args *, register_t *);

int	sys_fork(struct lwp *, const void *, register_t *);

int	sys_read(struct lwp *, const struct sys_read_args *, register_t *);

int	sys_write(struct lwp *, const struct sys_write_args *, register_t *);

int	sys_open(struct lwp *, const struct sys_open_args *, register_t *);

int	sys_close(struct lwp *, const struct sys_close_args *, register_t *);

int	compat_50_sys_wait4(struct lwp *, const struct compat_50_sys_wait4_args *, register_t *);

int	compat_43_sys_creat(struct lwp *, const struct compat_43_sys_creat_args *, register_t *);

int	sys_link(struct lwp *, const struct sys_link_args *, register_t *);

int	sys_unlink(struct lwp *, const struct sys_unlink_args *, register_t *);

int	sys_chdir(struct lwp *, const struct sys_chdir_args *, register_t *);

int	sys_fchdir(struct lwp *, const struct sys_fchdir_args *, register_t *);

int	compat_50_sys_mknod(struct lwp *, const struct compat_50_sys_mknod_args *, register_t *);

int	sys_chmod(struct lwp *, const struct sys_chmod_args *, register_t *);

int	sys_chown(struct lwp *, const struct sys_chown_args *, register_t *);

int	sys_obreak(struct lwp *, const struct sys_obreak_args *, register_t *);

int	compat_20_sys_getfsstat(struct lwp *, const struct compat_20_sys_getfsstat_args *, register_t *);

int	compat_43_sys_lseek(struct lwp *, const struct compat_43_sys_lseek_args *, register_t *);

int	sys_getpid_with_ppid(struct lwp *, const void *, register_t *);

int	freebsd_sys_mount(struct lwp *, const struct freebsd_sys_mount_args *, register_t *);

int	sys_unmount(struct lwp *, const struct sys_unmount_args *, register_t *);

int	sys_setuid(struct lwp *, const struct sys_setuid_args *, register_t *);

int	sys_getuid_with_euid(struct lwp *, const void *, register_t *);

int	sys_geteuid(struct lwp *, const void *, register_t *);

int	freebsd_sys_ptrace(struct lwp *, const struct freebsd_sys_ptrace_args *, register_t *);

int	sys_recvmsg(struct lwp *, const struct sys_recvmsg_args *, register_t *);

int	sys_sendmsg(struct lwp *, const struct sys_sendmsg_args *, register_t *);

int	sys_recvfrom(struct lwp *, const struct sys_recvfrom_args *, register_t *);

int	sys_accept(struct lwp *, const struct sys_accept_args *, register_t *);

int	sys_getpeername(struct lwp *, const struct sys_getpeername_args *, register_t *);

int	sys_getsockname(struct lwp *, const struct sys_getsockname_args *, register_t *);

int	sys_access(struct lwp *, const struct sys_access_args *, register_t *);

int	sys_chflags(struct lwp *, const struct sys_chflags_args *, register_t *);

int	sys_fchflags(struct lwp *, const struct sys_fchflags_args *, register_t *);

int	sys_sync(struct lwp *, const void *, register_t *);

int	sys_kill(struct lwp *, const struct sys_kill_args *, register_t *);

int	compat_43_sys_stat(struct lwp *, const struct compat_43_sys_stat_args *, register_t *);

int	sys_getppid(struct lwp *, const void *, register_t *);

int	compat_43_sys_lstat(struct lwp *, const struct compat_43_sys_lstat_args *, register_t *);

int	sys_dup(struct lwp *, const struct sys_dup_args *, register_t *);

int	sys_pipe(struct lwp *, const void *, register_t *);

int	sys_getegid(struct lwp *, const void *, register_t *);

int	sys_profil(struct lwp *, const struct sys_profil_args *, register_t *);

#ifdef KTRACE
int	sys_ktrace(struct lwp *, const struct sys_ktrace_args *, register_t *);

#else
#endif
int	compat_13_sys_sigaction(struct lwp *, const struct compat_13_sys_sigaction_args *, register_t *);

int	sys_getgid_with_egid(struct lwp *, const void *, register_t *);

int	compat_13_sys_sigprocmask(struct lwp *, const struct compat_13_sys_sigprocmask_args *, register_t *);

int	sys___getlogin(struct lwp *, const struct sys___getlogin_args *, register_t *);

int	sys___setlogin(struct lwp *, const struct sys___setlogin_args *, register_t *);

int	sys_acct(struct lwp *, const struct sys_acct_args *, register_t *);

int	compat_13_sys_sigpending(struct lwp *, const void *, register_t *);

int	compat_13_sys_sigaltstack(struct lwp *, const struct compat_13_sys_sigaltstack_args *, register_t *);

int	freebsd_sys_ioctl(struct lwp *, const struct freebsd_sys_ioctl_args *, register_t *);

int	sys_reboot(struct lwp *, const struct sys_reboot_args *, register_t *);

int	sys_revoke(struct lwp *, const struct sys_revoke_args *, register_t *);

int	sys_symlink(struct lwp *, const struct sys_symlink_args *, register_t *);

int	sys_readlink(struct lwp *, const struct sys_readlink_args *, register_t *);

int	sys_execve(struct lwp *, const struct sys_execve_args *, register_t *);

int	sys_umask(struct lwp *, const struct sys_umask_args *, register_t *);

int	sys_chroot(struct lwp *, const struct sys_chroot_args *, register_t *);

int	compat_43_sys_fstat(struct lwp *, const struct compat_43_sys_fstat_args *, register_t *);

int	compat_43_sys_getkerninfo(struct lwp *, const struct compat_43_sys_getkerninfo_args *, register_t *);

int	compat_43_sys_getpagesize(struct lwp *, const void *, register_t *);

int	freebsd_sys_msync(struct lwp *, const struct freebsd_sys_msync_args *, register_t *);

int	sys_vfork(struct lwp *, const void *, register_t *);

int	compat_43_sys_mmap(struct lwp *, const struct compat_43_sys_mmap_args *, register_t *);

int	sys_ovadvise(struct lwp *, const struct sys_ovadvise_args *, register_t *);

int	sys_munmap(struct lwp *, const struct sys_munmap_args *, register_t *);

int	sys_mprotect(struct lwp *, const struct sys_mprotect_args *, register_t *);

int	sys_madvise(struct lwp *, const struct sys_madvise_args *, register_t *);

int	sys_mincore(struct lwp *, const struct sys_mincore_args *, register_t *);

int	sys_getgroups(struct lwp *, const struct sys_getgroups_args *, register_t *);

int	sys_setgroups(struct lwp *, const struct sys_setgroups_args *, register_t *);

int	sys_getpgrp(struct lwp *, const void *, register_t *);

int	sys_setpgid(struct lwp *, const struct sys_setpgid_args *, register_t *);

int	compat_50_sys_setitimer(struct lwp *, const struct compat_50_sys_setitimer_args *, register_t *);

int	compat_43_sys_wait(struct lwp *, const void *, register_t *);

int	compat_12_sys_swapon(struct lwp *, const struct compat_12_sys_swapon_args *, register_t *);

int	compat_50_sys_getitimer(struct lwp *, const struct compat_50_sys_getitimer_args *, register_t *);

int	compat_43_sys_gethostname(struct lwp *, const struct compat_43_sys_gethostname_args *, register_t *);

int	compat_43_sys_sethostname(struct lwp *, const struct compat_43_sys_sethostname_args *, register_t *);

int	compat_43_sys_getdtablesize(struct lwp *, const void *, register_t *);

int	sys_dup2(struct lwp *, const struct sys_dup2_args *, register_t *);

int	sys_fcntl(struct lwp *, const struct sys_fcntl_args *, register_t *);

int	compat_50_sys_select(struct lwp *, const struct compat_50_sys_select_args *, register_t *);

int	sys_fsync(struct lwp *, const struct sys_fsync_args *, register_t *);

int	sys_setpriority(struct lwp *, const struct sys_setpriority_args *, register_t *);

int	compat_30_sys_socket(struct lwp *, const struct compat_30_sys_socket_args *, register_t *);

int	sys_connect(struct lwp *, const struct sys_connect_args *, register_t *);

int	compat_43_sys_accept(struct lwp *, const struct compat_43_sys_accept_args *, register_t *);

int	sys_getpriority(struct lwp *, const struct sys_getpriority_args *, register_t *);

int	compat_43_sys_send(struct lwp *, const struct compat_43_sys_send_args *, register_t *);

int	compat_43_sys_recv(struct lwp *, const struct compat_43_sys_recv_args *, register_t *);

int	freebsd_sys_sigreturn(struct lwp *, const struct freebsd_sys_sigreturn_args *, register_t *);

int	sys_bind(struct lwp *, const struct sys_bind_args *, register_t *);

int	sys_setsockopt(struct lwp *, const struct sys_setsockopt_args *, register_t *);

int	sys_listen(struct lwp *, const struct sys_listen_args *, register_t *);

int	compat_43_sys_sigvec(struct lwp *, const struct compat_43_sys_sigvec_args *, register_t *);

int	compat_43_sys_sigblock(struct lwp *, const struct compat_43_sys_sigblock_args *, register_t *);

int	compat_43_sys_sigsetmask(struct lwp *, const struct compat_43_sys_sigsetmask_args *, register_t *);

int	compat_13_sys_sigsuspend(struct lwp *, const struct compat_13_sys_sigsuspend_args *, register_t *);

int	compat_43_sys_sigstack(struct lwp *, const struct compat_43_sys_sigstack_args *, register_t *);

int	compat_43_sys_recvmsg(struct lwp *, const struct compat_43_sys_recvmsg_args *, register_t *);

int	compat_43_sys_sendmsg(struct lwp *, const struct compat_43_sys_sendmsg_args *, register_t *);

#ifdef TRACE
int	sys_vtrace(struct lwp *, const struct sys_vtrace_args *, register_t *);

#else
#endif
int	compat_50_sys_gettimeofday(struct lwp *, const struct compat_50_sys_gettimeofday_args *, register_t *);

int	compat_50_sys_getrusage(struct lwp *, const struct compat_50_sys_getrusage_args *, register_t *);

int	sys_getsockopt(struct lwp *, const struct sys_getsockopt_args *, register_t *);

int	sys_readv(struct lwp *, const struct sys_readv_args *, register_t *);

int	sys_writev(struct lwp *, const struct sys_writev_args *, register_t *);

int	compat_50_sys_settimeofday(struct lwp *, const struct compat_50_sys_settimeofday_args *, register_t *);

int	sys_fchown(struct lwp *, const struct sys_fchown_args *, register_t *);

int	sys_fchmod(struct lwp *, const struct sys_fchmod_args *, register_t *);

int	compat_43_sys_recvfrom(struct lwp *, const struct compat_43_sys_recvfrom_args *, register_t *);

int	sys_setreuid(struct lwp *, const struct sys_setreuid_args *, register_t *);

int	sys_setregid(struct lwp *, const struct sys_setregid_args *, register_t *);

int	sys_rename(struct lwp *, const struct sys_rename_args *, register_t *);

int	compat_43_sys_truncate(struct lwp *, const struct compat_43_sys_truncate_args *, register_t *);

int	compat_43_sys_ftruncate(struct lwp *, const struct compat_43_sys_ftruncate_args *, register_t *);

int	sys_flock(struct lwp *, const struct sys_flock_args *, register_t *);

int	sys_mkfifo(struct lwp *, const struct sys_mkfifo_args *, register_t *);

int	sys_sendto(struct lwp *, const struct sys_sendto_args *, register_t *);

int	sys_shutdown(struct lwp *, const struct sys_shutdown_args *, register_t *);

int	sys_socketpair(struct lwp *, const struct sys_socketpair_args *, register_t *);

int	sys_mkdir(struct lwp *, const struct sys_mkdir_args *, register_t *);

int	sys_rmdir(struct lwp *, const struct sys_rmdir_args *, register_t *);

int	compat_50_sys_utimes(struct lwp *, const struct compat_50_sys_utimes_args *, register_t *);

int	compat_50_sys_adjtime(struct lwp *, const struct compat_50_sys_adjtime_args *, register_t *);

int	compat_43_sys_getpeername(struct lwp *, const struct compat_43_sys_getpeername_args *, register_t *);

int	compat_43_sys_gethostid(struct lwp *, const void *, register_t *);

int	compat_43_sys_sethostid(struct lwp *, const struct compat_43_sys_sethostid_args *, register_t *);

int	compat_43_sys_getrlimit(struct lwp *, const struct compat_43_sys_getrlimit_args *, register_t *);

int	compat_43_sys_setrlimit(struct lwp *, const struct compat_43_sys_setrlimit_args *, register_t *);

int	compat_43_sys_killpg(struct lwp *, const struct compat_43_sys_killpg_args *, register_t *);

int	sys_setsid(struct lwp *, const void *, register_t *);

int	compat_50_sys_quotactl(struct lwp *, const struct compat_50_sys_quotactl_args *, register_t *);

int	compat_43_sys_quota(struct lwp *, const void *, register_t *);

int	compat_43_sys_getsockname(struct lwp *, const struct compat_43_sys_getsockname_args *, register_t *);

int	compat_43_sys_getdirentries(struct lwp *, const struct compat_43_sys_getdirentries_args *, register_t *);

int	compat_20_sys_statfs(struct lwp *, const struct compat_20_sys_statfs_args *, register_t *);

int	compat_20_sys_fstatfs(struct lwp *, const struct compat_20_sys_fstatfs_args *, register_t *);

int	compat_30_sys_getfh(struct lwp *, const struct compat_30_sys_getfh_args *, register_t *);

int	compat_09_sys_getdomainname(struct lwp *, const struct compat_09_sys_getdomainname_args *, register_t *);

int	compat_09_sys_setdomainname(struct lwp *, const struct compat_09_sys_setdomainname_args *, register_t *);

int	compat_09_sys_uname(struct lwp *, const struct compat_09_sys_uname_args *, register_t *);

int	sys_sysarch(struct lwp *, const struct sys_sysarch_args *, register_t *);

int	freebsd_sys_rtprio(struct lwp *, const struct freebsd_sys_rtprio_args *, register_t *);

#if defined(SYSVSEM) && !defined(_LP64)
int	freebsd_sys_semsys(struct lwp *, const struct freebsd_sys_semsys_args *, register_t *);

#else
#endif
#if defined(SYSVMSG) && !defined(_LP64)
int	freebsd_sys_msgsys(struct lwp *, const struct freebsd_sys_msgsys_args *, register_t *);

#else
#endif
#if defined(SYSVSHM) && !defined(_LP64)
int	freebsd_sys_shmsys(struct lwp *, const struct freebsd_sys_shmsys_args *, register_t *);

#else
#endif
int	sys_pread(struct lwp *, const struct sys_pread_args *, register_t *);

int	sys_pwrite(struct lwp *, const struct sys_pwrite_args *, register_t *);

#ifdef NTP
int	freebsd_ntp_adjtime(struct lwp *, const struct freebsd_ntp_adjtime_args *, register_t *);

#else
#endif
int	sys_setgid(struct lwp *, const struct sys_setgid_args *, register_t *);

int	sys_setegid(struct lwp *, const struct sys_setegid_args *, register_t *);

int	sys_seteuid(struct lwp *, const struct sys_seteuid_args *, register_t *);

int	compat_12_sys_stat(struct lwp *, const struct compat_12_sys_stat_args *, register_t *);

int	compat_12_sys_fstat(struct lwp *, const struct compat_12_sys_fstat_args *, register_t *);

int	compat_12_sys_lstat(struct lwp *, const struct compat_12_sys_lstat_args *, register_t *);

int	sys_pathconf(struct lwp *, const struct sys_pathconf_args *, register_t *);

int	sys_fpathconf(struct lwp *, const struct sys_fpathconf_args *, register_t *);

int	sys_getrlimit(struct lwp *, const struct sys_getrlimit_args *, register_t *);

int	sys_setrlimit(struct lwp *, const struct sys_setrlimit_args *, register_t *);

int	compat_12_sys_getdirentries(struct lwp *, const struct compat_12_sys_getdirentries_args *, register_t *);

int	freebsd_sys_mmap(struct lwp *, const struct freebsd_sys_mmap_args *, register_t *);

int	sys_lseek(struct lwp *, const struct sys_lseek_args *, register_t *);

int	sys_truncate(struct lwp *, const struct sys_truncate_args *, register_t *);

int	sys_ftruncate(struct lwp *, const struct sys_ftruncate_args *, register_t *);

int	freebsd_sys_sysctl(struct lwp *, const struct freebsd_sys_sysctl_args *, register_t *);

int	sys_mlock(struct lwp *, const struct sys_mlock_args *, register_t *);

int	sys_munlock(struct lwp *, const struct sys_munlock_args *, register_t *);

#ifdef FREEBSD_BASED_ON_44LITE_R2
int	freebsd_sys_undelete(struct lwp *, const struct freebsd_sys_undelete_args *, register_t *);

#else
#endif
int	compat_50_sys_futimes(struct lwp *, const struct compat_50_sys_futimes_args *, register_t *);

int	sys_getpgid(struct lwp *, const struct sys_getpgid_args *, register_t *);

#if 0
#else
#endif
int	sys_poll(struct lwp *, const struct sys_poll_args *, register_t *);

#ifdef SYSVSEM
int	compat_14_sys___semctl(struct lwp *, const struct compat_14_sys___semctl_args *, register_t *);

int	sys_semget(struct lwp *, const struct sys_semget_args *, register_t *);

int	sys_semop(struct lwp *, const struct sys_semop_args *, register_t *);

int	sys_semconfig(struct lwp *, const struct sys_semconfig_args *, register_t *);

#else
#endif
#ifdef SYSVMSG
int	compat_14_sys_msgctl(struct lwp *, const struct compat_14_sys_msgctl_args *, register_t *);

int	sys_msgget(struct lwp *, const struct sys_msgget_args *, register_t *);

int	sys_msgsnd(struct lwp *, const struct sys_msgsnd_args *, register_t *);

int	sys_msgrcv(struct lwp *, const struct sys_msgrcv_args *, register_t *);

#else
#endif
#ifdef SYSVSHM
int	sys_shmat(struct lwp *, const struct sys_shmat_args *, register_t *);

int	compat_14_sys_shmctl(struct lwp *, const struct compat_14_sys_shmctl_args *, register_t *);

int	sys_shmdt(struct lwp *, const struct sys_shmdt_args *, register_t *);

int	sys_shmget(struct lwp *, const struct sys_shmget_args *, register_t *);

#else
#endif
int	compat_50_sys_clock_gettime(struct lwp *, const struct compat_50_sys_clock_gettime_args *, register_t *);

int	compat_50_sys_clock_settime(struct lwp *, const struct compat_50_sys_clock_settime_args *, register_t *);

int	compat_50_sys_clock_getres(struct lwp *, const struct compat_50_sys_clock_getres_args *, register_t *);

int	compat_50_sys_nanosleep(struct lwp *, const struct compat_50_sys_nanosleep_args *, register_t *);

int	sys_minherit(struct lwp *, const struct sys_minherit_args *, register_t *);

int	freebsd_sys_rfork(struct lwp *, const struct freebsd_sys_rfork_args *, register_t *);

int	sys_issetugid(struct lwp *, const void *, register_t *);

int	sys_lchown(struct lwp *, const struct sys_lchown_args *, register_t *);

int	compat_30_sys_getdents(struct lwp *, const struct compat_30_sys_getdents_args *, register_t *);

int	sys_lchmod(struct lwp *, const struct sys_lchmod_args *, register_t *);

int	compat_50_sys_lutimes(struct lwp *, const struct compat_50_sys_lutimes_args *, register_t *);

int	sys___msync13(struct lwp *, const struct sys___msync13_args *, register_t *);

int	compat_30_sys___stat13(struct lwp *, const struct compat_30_sys___stat13_args *, register_t *);

int	compat_30_sys___fstat13(struct lwp *, const struct compat_30_sys___fstat13_args *, register_t *);

int	compat_30_sys___lstat13(struct lwp *, const struct compat_30_sys___lstat13_args *, register_t *);

int	compat_20_sys_fhstatfs(struct lwp *, const struct compat_20_sys_fhstatfs_args *, register_t *);

int	compat_30_sys_fhopen(struct lwp *, const struct compat_30_sys_fhopen_args *, register_t *);

int	compat_30_sys_fhstat(struct lwp *, const struct compat_30_sys_fhstat_args *, register_t *);

int	sys_getsid(struct lwp *, const struct sys_getsid_args *, register_t *);

int	freebsd_sys_yield(struct lwp *, const void *, register_t *);

int	sys_mlockall(struct lwp *, const struct sys_mlockall_args *, register_t *);

int	sys_munlockall(struct lwp *, const void *, register_t *);

int	sys___getcwd(struct lwp *, const struct sys___getcwd_args *, register_t *);

int	freebsd_sys_sched_setparam(struct lwp *, const struct freebsd_sys_sched_setparam_args *, register_t *);

int	freebsd_sys_sched_getparam(struct lwp *, const struct freebsd_sys_sched_getparam_args *, register_t *);

int	freebsd_sys_sched_setscheduler(struct lwp *, const struct freebsd_sys_sched_setscheduler_args *, register_t *);

int	freebsd_sys_sched_getscheduler(struct lwp *, const struct freebsd_sys_sched_getscheduler_args *, register_t *);

int	freebsd_sys_sched_yield(struct lwp *, const void *, register_t *);

int	freebsd_sys_sched_get_priority_max(struct lwp *, const struct freebsd_sys_sched_get_priority_max_args *, register_t *);

int	freebsd_sys_sched_get_priority_min(struct lwp *, const struct freebsd_sys_sched_get_priority_min_args *, register_t *);

int	freebsd_sys_utrace(struct lwp *, const struct freebsd_sys_utrace_args *, register_t *);

int	sys___sigprocmask14(struct lwp *, const struct sys___sigprocmask14_args *, register_t *);

int	sys___sigsuspend14(struct lwp *, const struct sys___sigsuspend14_args *, register_t *);

int	freebsd_sys_sigaction4(struct lwp *, const struct freebsd_sys_sigaction4_args *, register_t *);

int	sys___sigpending14(struct lwp *, const struct sys___sigpending14_args *, register_t *);

int	sys_lchflags(struct lwp *, const struct sys_lchflags_args *, register_t *);

int	sys_uuidgen(struct lwp *, const struct sys_uuidgen_args *, register_t *);

int	sys__ksem_close(struct lwp *, const struct sys__ksem_close_args *, register_t *);

int	sys__ksem_post(struct lwp *, const struct sys__ksem_post_args *, register_t *);

int	sys__ksem_wait(struct lwp *, const struct sys__ksem_wait_args *, register_t *);

int	sys__ksem_trywait(struct lwp *, const struct sys__ksem_trywait_args *, register_t *);

int	sys__ksem_unlink(struct lwp *, const struct sys__ksem_unlink_args *, register_t *);

int	sys__ksem_getvalue(struct lwp *, const struct sys__ksem_getvalue_args *, register_t *);

int	sys__ksem_destroy(struct lwp *, const struct sys__ksem_destroy_args *, register_t *);

#endif /* _FREEBSD_SYS_SYSCALLARGS_H_ */
