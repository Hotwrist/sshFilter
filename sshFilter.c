/* Author: John Ebinyi Odey aka Hotwrist aka Redhound aka Giannis
 * DESCRIPTION: This is the source code for a simple packet filter firewall
 *              that filters and blocks all outgoing packets to port number 22 (SSH)
 * DATE: Wednesday 15th January, 2025.
*/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h> 
#include <linux/ip.h> 
#include <linux/tcp.h> 

#define SSH_FILTER_HOOK_REG_FAILED -1
#define SSH_FILTER_HOOK_REG_SUCCESS 0

MODULE_AUTHOR("John Ebinyi Odey");
MODULE_DESCRIPTION("A simple packet filter firewall that filters and stops (block) all outgoing packets destined for port 22 (SSH)");
MODULE_LICENSE("Dual MIT/GPL");
MODULE_VERSION("0.1");

static struct nf_hook_ops sshFilterHook; 

// The parameters of this function are what will be passed to this function when it is called.
// @priv: a private data pointer that is passed to this function when it is called. It can be used to 
//        pass custom data to this function (callback function). @priv is often NULL if no private data is needed.
// @state: is used to pass state information.
// @skb: represents the packet i.e the packet content or information.
unsigned int sshFilter(void *priv, struct sk_buff *skb, const struct nf_hook_state *state)
{
    struct iphdr *iph; 
    struct tcphdr *tcph; 
    iph = ip_hdr(skb); 
    tcph = (void *)iph+iph->ihl*4; 

    // if the packet is destined for port number 22 (SSH), please block it...smiles....
    if (iph->protocol == IPPROTO_TCP && tcph->dest == htons(22)) 
    { 
        printk(KERN_INFO "Dropping SSH packet to %d.%d.%d.%d\n", 
        ((unsigned char *)&iph->daddr) [0], 
        ((unsigned char *)&iph->daddr ) [1], 
        ((unsigned char *)&iph->daddr) [2], 
        ((unsigned char *) &iph->daddr) [3]); 
    
        return NF_DROP; 
    }
    else
    {
        // let the packet flow through the stack (except packets to port number 22)
        return NF_ACCEPT;
    }
}

static int __init sshFilter_init(void)
{
    printk(KERN_INFO "Registering an SSH filter. \n") ; 
    sshFilterHook.hook = sshFilter; // this is a pointer to the hook function we defined above (sshFilter())
    sshFilterHook.hooknum = NF_INET_POST_ROUTING;   // NF_INET_POST_ROUTING: because we are filtering and blocking outgoing packets on port number 22.
    sshFilterHook.pf = PF_INET; // this is the protocol family of netfilter (PF_INET)
    sshFilterHook.priority = NF_IP_PRI_FIRST;   // this determines the order of the hook in the list, let it be the FIRST.

    // Register the hook. 
    int rc = nf_register_net_hook(&init_net, &sshFilterHook); 

    if(rc < 0) 
    {
        printk("ERROR: sshFilterHook registration failed!"); 
        return SSH_FILTER_HOOK_REG_FAILED;   
    }
    

    return SSH_FILTER_HOOK_REG_SUCCESS;
}

static void __exit sshFilter_exit(void)
{
    printk (KERN_INFO "SSH filter is being removed. \n"); 

    nf_unregister_net_hook(&init_net, &sshFilterHook); 

    return;
}

module_init(sshFilter_init);
module_exit(sshFilter_exit);
