#!/bin/bash

# Simple autostart script for gnu_rapl_header module
# This script sets up automatic loading after reboot

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
MODULE_PATH="$SCRIPT_DIR/gnu_rapl_header.ko"

echo "Setting up gnu_rapl_header module autostart..."

# Check if running as root
if [ "$EUID" -ne 0 ]; then
    echo "This script must be run as root (use sudo)"
    exit 1
fi

# Check if module exists
if [ ! -f "$MODULE_PATH" ]; then
    echo "Error: gnu_rapl_header.ko not found in $SCRIPT_DIR"
    echo "Please build the module first with 'make'"
    exit 1
fi

# Create systemd service file
cat > /etc/systemd/system/gnu-rapl-header.service << EOF
[Unit]
Description=GNU RAPL Header Module
After=multi-user.target

[Service]
Type=oneshot
ExecStart=/sbin/insmod $MODULE_PATH
ExecStop=/sbin/rmmod gnu_rapl_header
RemainAfterExit=yes
StandardOutput=null
StandardError=null

[Install]
WantedBy=multi-user.target
EOF

# Enable and start the service
systemctl daemon-reload
systemctl enable gnu-rapl-header.service

# Create rc.local entry as backup
if [ -f /etc/rc.local ]; then
    # Remove existing entry if present
    sed -i '/insmod.*gnu_rapl_header\.ko/d' /etc/rc.local
    # Add new entry before exit 0
    sed -i '/^exit 0/i /sbin/insmod '"$MODULE_PATH"' 2>/dev/null' /etc/rc.local
else
    # Create rc.local if it doesn't exist
    cat > /etc/rc.local << EOF
#!/bin/bash
/sbin/insmod $MODULE_PATH 2>/dev/null
exit 0
EOF
    chmod +x /etc/rc.local
fi

echo "Autostart setup completed!"
echo ""
echo "The module will now automatically load after reboot using:"
echo "1. Systemd service: gnu-rapl-header.service"
echo "2. rc.local: Load on boot as backup"
echo ""
echo "To manually control the service:"
echo "  Start:   systemctl start gnu-rapl-header"
echo "  Stop:    systemctl stop gnu-rapl-header"
echo "  Status:  systemctl status gnu-rapl-header"
echo ""
echo "To remove autostart:"
echo "  systemctl disable gnu-rapl-header"
echo "  rm /etc/systemd/system/gnu-rapl-header.service"
echo "  sed -i '/insmod.*gnu_rapl_header\.ko/d' /etc/rc.local"
