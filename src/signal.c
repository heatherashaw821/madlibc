////////////////////////////////////////////////////////////////////////////////
// THE SCOTCH-WARE LICENSE (Revision 0):
// <aaronryool/gmail.com> wrote this file. As long as you retain this notice you
// can do whatever you want with this stuff. If we meet some day, and you think
// this stuff is worth it, you can buy me a shot of scotch in return
////////////////////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>

#define HAVE_SA_RESTORER
// This is the sigaction structure from the Linux 2.1.20 kernel.  
struct old_kernel_sigaction {
    __sighandler_t k_sa_handler;
    unsigned long sa_mask;
    unsigned long sa_flags;
    void (*sa_restorer) (void);
};
// This is the sigaction structure from the Linux 2.1.68 kernel.  
struct kernel_sigaction {
    __sighandler_t k_sa_handler;
    unsigned long sa_flags;
    void (*sa_restorer) (void);
    sigset_t sa_mask;
};

#define SA_RESTORER	0x04000000
void __default_sa_restorer(void)
{
    
}
void __default_rt_sa_restorer(void)
{
    
}

// When RT signals are in use we need to use a different return stub.  
#ifdef __NR_rt_sigreturn
#define choose_restorer(flags) \
  (flags & SA_SIGINFO) ? __default_rt_sa_restorer : __default_sa_restorer
#else
#define choose_restorer(flags) __default_sa_restorer
#endif

// If ACT is not NULL, change the action for SIG to *ACT.
//   If OACT is not NULL, put the old action for SIG in *OACT.  
int sigaction(int sig, const struct sigaction *act, struct sigaction *oact)
{
    int result;
    struct kernel_sigaction kact, koact;

    if(act)
    {
        kact.k_sa_handler = act->sa_handler;
        memcpy(&kact.sa_mask, &act->sa_mask, sizeof(sigset_t));
        kact.sa_flags = act->sa_flags;
    
# ifdef HAVE_SA_RESTORER
        if(kact.sa_flags & SA_RESTORER) 
        {
            kact.sa_restorer = act->sa_restorer;
        }
        else
        {
            kact.sa_restorer = choose_restorer (kact.sa_flags);
            kact.sa_flags |= SA_RESTORER;
        }
# endif
    }

//     XXX The size argument hopefully will have to be changed to the
//       real size of the user-level sigset_t.  
    result = syscall(__NR_rt_sigaction, sig, (act ? &kact : NULL),
	    (oact ? &koact : NULL), _NSIG / 8);
    if (oact && result >= 0)
    {
        oact->sa_handler = koact.k_sa_handler;
        memcpy(&oact->sa_mask, &koact.sa_mask, sizeof (sigset_t));
        oact->sa_flags = koact.sa_flags;
    
# ifdef HAVE_SA_RESTORER
        oact->sa_restorer = koact.sa_restorer;
# endif
    }
    return result;
}


//int sigfillset(sigset_t *set);
//int sigdelset(sigset_t *set, int signum);
//int sigismember(const sigset_t *set, int signum);

/*
int sigaddset(sigset_t *set, int signum)
{
    int i;
    for(i=0;set->__val[i] != 0 && i <= _SIGSET_NWORDS;i++);
        set->__val[i] = signum;
    return 0;
}

*/

int sigemptyset(sigset_t *set)
{
    memset(&set, 0, sizeof(sigset_t));
    return 0;
}

__sighandler_t signal(int signum, __sighandler_t handler)
{
    struct sigaction sa, sao;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = handler;
    sa.sa_flags = SA_RESTART;
    
    sigaction(signum, NULL, &sao);
    
    if (sao.sa_handler != SIG_IGN)
        sigaction(signum, &sa, NULL);
    else
        return SIG_ERR;
    return sao.sa_handler;
}


