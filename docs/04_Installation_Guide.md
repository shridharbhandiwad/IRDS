```
┌─────────────────────────────────────────────────────────────────────────────┐
│                                                                             │
│  ███████╗ ██████╗ ██████╗ ██████╗ ██╗     ███████╗██████╗                 │
│  ╚══███╔╝██╔═══██╗██╔══██╗██╔══██╗██║     ██╔════╝██╔══██╗                │
│    ███╔╝ ██║   ██║██████╔╝██████╔╝██║     █████╗  ██████╔╝                │
│   ███╔╝  ██║   ██║██╔═══╝ ██╔═══╝ ██║     ██╔══╝  ██╔══██╗                │
│  ███████╗╚██████╔╝██║     ██║     ███████╗███████╗██║  ██║                │
│  ╚══════╝ ╚═════╝ ╚═╝     ╚═╝     ╚══════╝╚══════╝╚═╝  ╚═╝                │
│                                                                             │
│                     Z O P P L E R   S Y S T E M S                          │
│                   Advanced Radar Display Solutions                         │
│                                                                             │
└─────────────────────────────────────────────────────────────────────────────┘
```

# **INSTALLATION GUIDE**
## Integrated Radar Display System (IRDS)

---

**Document Information**

| Field | Value |
|-------|-------|
| **Document Title** | Installation Guide |
| **Product Name** | Integrated Radar Display System (IRDS) |
| **Version** | 1.0.0 |
| **Date** | October 13, 2025 |
| **Status** | Approved |
| **Classification** | For Official Use |
| **Organization** | Zoppler Systems |
| **Prepared By** | Installation Team |
| **Target Audience** | System Administrators, IT Staff |

---

## TABLE OF CONTENTS

1. [Introduction](#1-introduction)
2. [System Requirements](#2-system-requirements)
3. [Pre-Installation](#3-pre-installation)
4. [Installation Procedures](#4-installation-procedures)
5. [Post-Installation](#5-post-installation)
6. [Configuration](#6-configuration)
7. [Verification](#7-verification)
8. [Troubleshooting](#8-troubleshooting)
9. [Uninstallation](#9-uninstallation)

---

## 1. INTRODUCTION

### 1.1 Purpose

This Installation Guide provides step-by-step instructions for installing the Integrated Radar Display System (IRDS) on Linux systems.

### 1.2 Scope

This guide covers:
- System requirements verification
- Software dependency installation
- IRDS application installation
- Configuration and setup
- Installation verification

### 1.3 Prerequisites

Before beginning installation, you should have:
- Administrative (sudo) access to the target system
- Basic Linux command-line knowledge
- Network access for downloading packages
- Installation media or source repository access

---

## 2. SYSTEM REQUIREMENTS

### 2.1 Hardware Requirements

#### Minimum Configuration

| Component | Requirement |
|-----------|-------------|
| **Processor** | Intel Core i5 or AMD equivalent |
| **Cores** | 4 cores |
| **Clock Speed** | 2.4 GHz |
| **RAM** | 8 GB |
| **Storage** | 500 GB HDD |
| **Graphics** | Intel HD Graphics or equivalent with OpenGL 3.3+ |
| **Network** | 1 Gigabit Ethernet |
| **Display** | 1920x1080 resolution |

#### Recommended Configuration

| Component | Requirement |
|-----------|-------------|
| **Processor** | Intel Core i7 or AMD Ryzen 7 |
| **Cores** | 8 cores |
| **Clock Speed** | 3.0 GHz or higher |
| **RAM** | 16 GB DDR4 |
| **Storage** | 1 TB SSD |
| **Graphics** | Dedicated GPU (NVIDIA/AMD) with 2GB+ VRAM |
| **Network** | 1 Gigabit Ethernet (dedicated interface) |
| **Display** | Dual monitors, 2560x1440 resolution |

### 2.2 Software Requirements

#### Operating System

| OS | Version | Architecture |
|----|---------|--------------|
| **Ubuntu** | 20.04 LTS or later | x86_64 |
| **Debian** | 11 (Bullseye) or later | x86_64 |
| **CentOS/RHEL** | 8 or later | x86_64 |
| **Fedora** | 35 or later | x86_64 |

#### Kernel Requirements

- Linux Kernel 5.4 or later
- Real-time kernel patches (optional, for improved performance)

#### Required Software

| Software | Version | Purpose |
|----------|---------|---------|
| **Qt** | 5.12 or later | GUI framework |
| **QGIS** | 3.x | Mapping libraries |
| **GCC/G++** | 7.5 or later | Compiler (if building from source) |
| **Make** | 4.2 or later | Build system |
| **CMake** | 3.10 or later | Build configuration |

---

## 3. PRE-INSTALLATION

### 3.1 System Preparation

#### 3.1.1 Check System Specifications

```bash
# Check CPU information
lscpu

# Check memory
free -h

# Check disk space
df -h

# Check kernel version
uname -r

# Check graphics capabilities
glxinfo | grep "OpenGL version"
```

#### 3.1.2 Update System

```bash
# Ubuntu/Debian
sudo apt update
sudo apt upgrade -y

# CentOS/RHEL
sudo yum update -y

# Fedora
sudo dnf update -y
```

#### 3.1.3 Check Network Connectivity

```bash
# Test internet connection
ping -c 4 8.8.8.8

# Check network interfaces
ip addr show
```

### 3.2 Dependency Installation

#### 3.2.1 Ubuntu/Debian Installation

```bash
# Install Qt 5 development packages
sudo apt install -y \
    qt5-default \
    qtbase5-dev \
    qtchooser \
    qt5-qmake \
    qtbase5-dev-tools \
    qtdeclarative5-dev \
    qtquickcontrols2-5-dev \
    libqt5charts5-dev \
    libqt5network5

# Install QGIS libraries
sudo apt install -y \
    qgis \
    libqgis-dev \
    qgis-plugin-grass

# Install spatial libraries
sudo apt install -y \
    libgeos-dev \
    libproj-dev \
    libspatialindex-dev

# Install build tools
sudo apt install -y \
    build-essential \
    cmake \
    git

# Install additional dependencies
sudo apt install -y \
    libgl1-mesa-dev \
    libglu1-mesa-dev
```

#### 3.2.2 CentOS/RHEL Installation

```bash
# Enable EPEL repository
sudo yum install -y epel-release

# Install Qt 5
sudo yum install -y \
    qt5-qtbase-devel \
    qt5-qtdeclarative-devel \
    qt5-qtquickcontrols2-devel \
    qt5-qtcharts-devel

# Install QGIS
sudo yum install -y \
    qgis \
    qgis-devel

# Install spatial libraries
sudo yum install -y \
    geos-devel \
    proj-devel \
    spatialindex-devel

# Install build tools
sudo yum groupinstall -y "Development Tools"
sudo yum install -y cmake git
```

#### 3.2.3 Fedora Installation

```bash
# Install Qt 5
sudo dnf install -y \
    qt5-qtbase-devel \
    qt5-qtdeclarative-devel \
    qt5-qtquickcontrols2-devel \
    qt5-qtcharts-devel

# Install QGIS
sudo dnf install -y \
    qgis \
    qgis-devel

# Install spatial libraries
sudo dnf install -y \
    geos-devel \
    proj-devel \
    spatialindex-devel

# Install build tools
sudo dnf groupinstall -y "Development Tools"
sudo dnf install -y cmake git
```

### 3.3 Verify Dependencies

```bash
# Check Qt installation
qmake --version

# Check QGIS libraries
pkg-config --modversion qgis

# Check compiler
g++ --version

# Check make
make --version

# Check cmake
cmake --version
```

---

## 4. INSTALLATION PROCEDURES

### 4.1 Installation from Pre-Built Package

#### 4.1.1 Download Package

```bash
# Create installation directory
mkdir -p ~/Downloads/IRDS
cd ~/Downloads/IRDS

# Download package (example URL)
wget https://releases.zopplersystems.com/irds/1.0.0/irds-1.0.0-linux-x86_64.tar.gz

# Verify checksum
sha256sum irds-1.0.0-linux-x86_64.tar.gz
# Compare with published checksum
```

#### 4.1.2 Extract Package

```bash
# Extract archive
tar -xzvf irds-1.0.0-linux-x86_64.tar.gz

# Navigate to extracted directory
cd irds-1.0.0-linux-x86_64
```

#### 4.1.3 Install Application

```bash
# Run installation script
sudo ./install.sh

# Or manual installation
sudo mkdir -p /opt/irds
sudo cp -r * /opt/irds/
sudo ln -s /opt/irds/bin/RadarDisplay /usr/local/bin/irds
```

#### 4.1.4 Create Desktop Entry

```bash
# Create desktop file
sudo tee /usr/share/applications/irds.desktop > /dev/null <<EOF
[Desktop Entry]
Version=1.0
Type=Application
Name=IRDS
Comment=Integrated Radar Display System
Exec=/opt/irds/bin/RadarDisplay
Icon=/opt/irds/resources/icons/irds.png
Terminal=false
Categories=Science;Education;
Keywords=radar;display;tracking;
EOF

# Update desktop database
sudo update-desktop-database
```

### 4.2 Installation from Source

#### 4.2.1 Clone Repository

```bash
# Clone from repository
git clone https://github.com/zopplersystems/irds.git
cd irds

# Checkout stable version
git checkout v1.0.0
```

#### 4.2.2 Configure Build

```bash
# Create build directory
mkdir build
cd build

# Configure with CMake
cmake .. \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/opt/irds

# Or configure with qmake
cd ..
qmake RadarDisplay.pro \
    -spec linux-g++ \
    CONFIG+=release
```

#### 4.2.3 Compile

```bash
# Using CMake
cd build
make -j$(nproc)

# Or using qmake
make -j$(nproc)
```

#### 4.2.4 Install

```bash
# Install system-wide
sudo make install

# Or install to custom location
make INSTALL_ROOT=/opt/irds install
```

#### 4.2.5 Set Permissions

```bash
# Set executable permissions
sudo chmod +x /opt/irds/bin/RadarDisplay

# Create symlink
sudo ln -s /opt/irds/bin/RadarDisplay /usr/local/bin/irds
```

### 4.3 Docker Installation (Optional)

#### 4.3.1 Install Docker

```bash
# Ubuntu/Debian
sudo apt install -y docker.io
sudo systemctl start docker
sudo systemctl enable docker

# Add user to docker group
sudo usermod -aG docker $USER
```

#### 4.3.2 Pull IRDS Image

```bash
# Pull from registry
docker pull zopplersystems/irds:1.0.0

# Or build from Dockerfile
docker build -t zopplersystems/irds:1.0.0 .
```

#### 4.3.3 Run Container

```bash
# Run with X11 forwarding
docker run -it \
    --name irds \
    --net=host \
    -e DISPLAY=$DISPLAY \
    -v /tmp/.X11-unix:/tmp/.X11-unix \
    -v $HOME/RadarRecordings:/home/irds/RadarRecordings \
    zopplersystems/irds:1.0.0
```

---

## 5. POST-INSTALLATION

### 5.1 Create Directories

```bash
# Create recording directory
mkdir -p ~/RadarRecordings

# Create configuration directory
mkdir -p ~/.irds/config

# Create logs directory
mkdir -p ~/.irds/logs

# Set permissions
chmod 755 ~/RadarRecordings
chmod 755 ~/.irds
```

### 5.2 Initial Configuration

#### 5.2.1 Create Configuration File

```bash
# Create default configuration
cat > ~/.irds/config/irds.conf <<EOF
[Network]
UdpPort=2025
NetworkInterface=eth0

[Display]
DefaultZoom=12
MapProvider=OpenStreetMap

[Recording]
AutoSaveInterval=60
CompressionEnabled=false

[Performance]
MaxTracks=50
UpdateRate=1000
EOF
```

#### 5.2.2 Set Environment Variables

```bash
# Add to ~/.bashrc or ~/.profile
echo 'export IRDS_HOME=/opt/irds' >> ~/.bashrc
echo 'export IRDS_CONFIG=$HOME/.irds/config' >> ~/.bashrc
echo 'export IRDS_LOGS=$HOME/.irds/logs' >> ~/.bashrc

# Reload profile
source ~/.bashrc
```

### 5.3 Configure Firewall

```bash
# UFW (Ubuntu)
sudo ufw allow 2025/udp
sudo ufw reload

# firewalld (CentOS/Fedora)
sudo firewall-cmd --permanent --add-port=2025/udp
sudo firewall-cmd --reload

# iptables
sudo iptables -A INPUT -p udp --dport 2025 -j ACCEPT
sudo iptables-save > /etc/iptables/rules.v4
```

### 5.4 Configure Network

#### 5.4.1 Set Static IP (Optional)

```bash
# Edit netplan (Ubuntu 20.04+)
sudo nano /etc/netplan/01-netcfg.yaml

# Example configuration:
# network:
#   version: 2
#   ethernets:
#     eth0:
#       addresses: [192.168.1.100/24]
#       gateway4: 192.168.1.1
#       nameservers:
#         addresses: [8.8.8.8, 8.8.4.4]

# Apply configuration
sudo netplan apply
```

#### 5.4.2 Configure UDP Multicast (if needed)

```bash
# Add multicast route
sudo route add -net 239.0.0.0 netmask 255.0.0.0 dev eth0

# Make persistent
echo "route add -net 239.0.0.0 netmask 255.0.0.0 dev eth0" | \
    sudo tee -a /etc/network/if-up.d/multicast
sudo chmod +x /etc/network/if-up.d/multicast
```

---

## 6. CONFIGURATION

### 6.1 System Configuration

#### 6.1.1 Increase File Descriptors

```bash
# Edit limits.conf
sudo nano /etc/security/limits.conf

# Add lines:
* soft nofile 65536
* hard nofile 65536

# Verify after reboot
ulimit -n
```

#### 6.1.2 Configure Shared Memory

```bash
# Edit sysctl.conf
sudo nano /etc/sysctl.conf

# Add lines:
kernel.shmmax = 68719476736
kernel.shmall = 4294967296

# Apply changes
sudo sysctl -p
```

#### 6.1.3 Optimize Network Stack

```bash
# Edit sysctl.conf
sudo nano /etc/sysctl.conf

# Add lines for UDP optimization:
net.core.rmem_max = 134217728
net.core.rmem_default = 67108864
net.core.wmem_max = 134217728
net.core.wmem_default = 67108864
net.core.netdev_max_backlog = 5000

# Apply changes
sudo sysctl -p
```

### 6.2 Graphics Configuration

#### 6.2.1 NVIDIA Driver Installation (if applicable)

```bash
# Ubuntu
sudo add-apt-repository ppa:graphics-drivers/ppa
sudo apt update
sudo apt install nvidia-driver-525

# Reboot system
sudo reboot
```

#### 6.2.2 AMD Driver Installation (if applicable)

```bash
# Ubuntu 20.04+
sudo add-apt-repository ppa:oibaf/graphics-drivers
sudo apt update
sudo apt upgrade

# Reboot system
sudo reboot
```

### 6.3 User Permissions

```bash
# Add user to necessary groups
sudo usermod -aG video $USER
sudo usermod -aG dialout $USER

# Create IRDS user group
sudo groupadd irds-users
sudo usermod -aG irds-users $USER

# Set directory permissions
sudo chown -R :irds-users /opt/irds
sudo chmod -R g+rw /opt/irds
```

---

## 7. VERIFICATION

### 7.1 Basic Functionality Test

```bash
# Launch IRDS
irds

# Or from installation directory
/opt/irds/bin/RadarDisplay
```

**Verify:**
- [ ] Application launches without errors
- [ ] Main window appears
- [ ] Track Table is visible by default
- [ ] Map display renders correctly
- [ ] No error messages in console

### 7.2 Component Tests

#### 7.2.1 Test Simulation

1. Press `S` to open Simulation widget
2. Click **Start** button
3. Verify simulated tracks appear on map
4. Check status bar shows track count
5. Click **Stop** button

#### 7.2.2 Test Recording

1. Press `R` to open Recording widget
2. Click **Record** button
3. Wait 10 seconds
4. Click **Stop** button
5. Verify file appears in `~/RadarRecordings/`
6. Check file size is > 0 bytes

#### 7.2.3 Test Replay

1. In Recording widget, select a recording
2. Click **Play** button
3. Verify tracks appear during replay
4. Click **Stop** button

#### 7.2.4 Test Health Monitor

1. Press `M` to open Health Monitor
2. Verify all module cards display
3. Check overall health percentage shows
4. Click **Run Diagnostics** button
5. Verify diagnostics complete

#### 7.2.5 Test Predictive Maintenance

1. Press `P` to open Predictive Maintenance
2. Verify component list displays
3. Check maintenance schedule table
4. Verify recommendations appear

### 7.3 Network Test

```bash
# Test UDP reception
# Terminal 1: Start IRDS simulation
irds

# Terminal 2: Monitor UDP traffic
sudo tcpdump -i lo -n udp port 2025

# Verify packets are being sent/received
```

### 7.4 Performance Test

```bash
# Monitor resource usage
htop

# Or with detailed info
top -p $(pgrep RadarDisplay)
```

**Expected resource usage:**
- CPU: 15-30% with 50 simulated tracks
- Memory: 500MB - 1.5GB
- Disk I/O: Minimal (except during recording)

### 7.5 Log Verification

```bash
# Check application logs
tail -f ~/.irds/logs/irds.log

# Check system logs
journalctl -u irds -f

# Check for errors
grep ERROR ~/.irds/logs/irds.log
```

---

## 8. TROUBLESHOOTING

### 8.1 Common Installation Issues

#### Issue: Qt libraries not found

**Error:**
```
error while loading shared libraries: libQt5Core.so.5: cannot open shared object file
```

**Solution:**
```bash
# Update library cache
sudo ldconfig

# Or set LD_LIBRARY_PATH
export LD_LIBRARY_PATH=/usr/lib/x86_64-linux-gnu:$LD_LIBRARY_PATH
```

#### Issue: QGIS libraries not found

**Error:**
```
error while loading shared libraries: libqgis_core.so: cannot open shared object file
```

**Solution:**
```bash
# Install QGIS libraries
sudo apt install libqgis-dev

# Or add to library path
export LD_LIBRARY_PATH=/usr/lib/qgis:$LD_LIBRARY_PATH
```

#### Issue: OpenGL errors

**Error:**
```
Could not initialize OpenGL
```

**Solution:**
```bash
# Check OpenGL support
glxinfo | grep "OpenGL version"

# Install Mesa libraries
sudo apt install mesa-utils libgl1-mesa-glx libglu1-mesa

# Update graphics drivers
```

#### Issue: Permission denied errors

**Error:**
```
Permission denied: /opt/irds/bin/RadarDisplay
```

**Solution:**
```bash
# Set executable permission
sudo chmod +x /opt/irds/bin/RadarDisplay

# Check ownership
sudo chown -R $USER:$USER /opt/irds
```

### 8.2 Build Issues

#### Issue: Make fails with Qt errors

**Solution:**
```bash
# Ensure Qt development packages are installed
sudo apt install qt5-default qtbase5-dev

# Clean and rebuild
make clean
qmake RadarDisplay.pro
make -j$(nproc)
```

#### Issue: QGIS headers not found

**Solution:**
```bash
# Install QGIS development headers
sudo apt install qgis-dev

# Specify QGIS include path
qmake RadarDisplay.pro \
    INCLUDEPATH+=/usr/include/qgis
```

### 8.3 Runtime Issues

#### Issue: Application crashes on startup

**Solution:**
```bash
# Run with debug output
QT_DEBUG_PLUGINS=1 irds

# Check logs
cat ~/.irds/logs/irds.log

# Verify all dependencies
ldd /opt/irds/bin/RadarDisplay
```

#### Issue: Network connectivity problems

**Solution:**
```bash
# Check firewall
sudo ufw status
sudo ufw allow 2025/udp

# Test UDP port
nc -ul 2025

# Check network interface
ip addr show
```

---

## 9. UNINSTALLATION

### 9.1 Remove Application

```bash
# Remove installed files
sudo rm -rf /opt/irds
sudo rm /usr/local/bin/irds
sudo rm /usr/share/applications/irds.desktop

# Update desktop database
sudo update-desktop-database
```

### 9.2 Remove User Data

```bash
# Remove recordings (backup first if needed)
rm -rf ~/RadarRecordings

# Remove configuration
rm -rf ~/.irds
```

### 9.3 Remove Dependencies (Optional)

⚠️ **Warning:** Only remove dependencies if they are not used by other applications.

```bash
# Ubuntu/Debian
sudo apt remove --purge \
    qt5-default \
    qtbase5-dev \
    qgis \
    libqgis-dev

sudo apt autoremove
```

### 9.4 Remove Firewall Rules

```bash
# UFW
sudo ufw delete allow 2025/udp

# firewalld
sudo firewall-cmd --permanent --remove-port=2025/udp
sudo firewall-cmd --reload

# iptables
sudo iptables -D INPUT -p udp --dport 2025 -j ACCEPT
```

---

## APPENDIX A: Installation Checklist

### Pre-Installation
- [ ] System meets minimum hardware requirements
- [ ] Operating system is supported version
- [ ] System is fully updated
- [ ] Internet connectivity verified
- [ ] Administrative access available

### Installation
- [ ] Dependencies installed successfully
- [ ] IRDS application installed
- [ ] Desktop entry created
- [ ] Required directories created
- [ ] Configuration file created

### Post-Installation
- [ ] Environment variables set
- [ ] Firewall configured
- [ ] Network settings configured
- [ ] User permissions set
- [ ] Graphics drivers installed

### Verification
- [ ] Application launches successfully
- [ ] All widgets accessible
- [ ] Simulation works
- [ ] Recording/replay works
- [ ] Network communication functional
- [ ] Performance acceptable
- [ ] No errors in logs

---

## APPENDIX B: Quick Installation

For experienced administrators, minimal installation steps:

```bash
# Update system
sudo apt update && sudo apt upgrade -y

# Install dependencies
sudo apt install -y qt5-default qtbase5-dev qtdeclarative5-dev \
    qtquickcontrols2-5-dev libqt5charts5-dev qgis libqgis-dev \
    libgeos-dev libproj-dev libspatialindex-dev build-essential cmake

# Download and extract
wget https://releases.zopplersystems.com/irds/1.0.0/irds-1.0.0-linux-x86_64.tar.gz
tar -xzvf irds-1.0.0-linux-x86_64.tar.gz

# Install
cd irds-1.0.0-linux-x86_64
sudo ./install.sh

# Configure
mkdir -p ~/RadarRecordings ~/.irds/{config,logs}
sudo ufw allow 2025/udp

# Run
irds
```

---

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                                                                             │
│                          ZOPPLER SYSTEMS                                    │
│                      Integrated Radar Display System                        │
│                                                                             │
│  Document: Installation Guide                                               │
│  Version: 1.0.0                                                            │
│  Date: October 13, 2025                                                    │
│  Classification: For Official Use                                           │
│                                                                             │
│  © 2025 Zoppler Systems. All rights reserved.                             │
│  For installation support, contact: support@zopplersystems.com             │
│                                                                             │
└─────────────────────────────────────────────────────────────────────────────┘
```

**END OF DOCUMENT**
