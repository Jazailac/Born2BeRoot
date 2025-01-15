# Born2beRoot

This project aims to introduce you to the fascinating world of virtualization by creating your first machine in VirtualBox under specific instructions. By the end of this project, you will be able to set up your own operating system while implementing strict rules.

## 📝 Project Overview

Born2beRoot is a system administration project that requires setting up a server following specific rules and guidelines. The main objectives include:

- Setting up a Virtual Machine using VirtualBox
- Installing and configuring Debian/CentOS
- Implementing strong password policies and security rules
- Setting up partitions using LVM
- Configuring SSH and UFW
- Setting up a functional WordPress website with lighttpd, MariaDB, and PHP
- Creating a monitoring script with specific requirements

## 🔧 Requirements

- Oracle VirtualBox or UTM (for MacOS)
- Debian or CentOS ISO file
- Basic understanding of command line interface
- Knowledge of system administration concepts

## 🚀 Installation Guide

1. **Virtual Machine Setup**
   - Download and install VirtualBox
   - Create a new Virtual Machine with the following specifications:
     - Type: Linux
     - Version: Debian 64-bit
     - Memory size: 1024MB minimum
     - Create a virtual hard disk (minimum 8GB)

2. **Partition Setup**
   - Follow the specific partition scheme using LVM
   - Create required partitions as per subject guidelines

3. **System Configuration**
   ```bash
   # Update system packages
   sudo apt update
   sudo apt upgrade

   # Install required packages
   sudo apt install vim
   sudo apt install ufw
   sudo apt install libpam-pwquality
   ```

## ⚙️ Configuration Steps

### SSH Configuration
```bash
# Edit SSH configuration
sudo vim /etc/ssh/sshd_config

# Change default port to 4242
Port 4242

# Disable root login
PermitRootLogin no
```

### UFW Configuration
```bash
# Enable UFW
sudo ufw enable

# Allow port 4242
sudo ufw allow 4242
```

### Password Policy
```bash
# Edit password quality configuration
sudo vim /etc/pam.d/common-password

# Add password policy rules
password requisite pam_pwquality.so retry=3 minlen=10 ucredit=-1 dcredit=-1 maxrepeat=3 reject_username difok=7 enforce_for_root
```

## 📊 Monitoring Script

Create a script that displays system information every 10 minutes:
```bash
#!/bin/bash
# Architecture
arch=$(uname -a)
# CPU physical
cpuf=$(grep "physical id" /proc/cpuinfo | wc -l)
# CPU virtual
cpuv=$(grep "processor" /proc/cpuinfo | wc -l)
# RAM
ram_total=$(free -m | awk '$1 == "Mem:" {print $2}')
ram_use=$(free -m | awk '$1 == "Mem:" {print $3}')
ram_percent=$(free | awk '$1 == "Mem:" {printf("%.2f"), $3/$2*100}')
# Disk
disk_total=$(df -BG | grep '^/dev/' | grep -v '/boot$' | awk '{ft += $2} END {print ft}')
disk_use=$(df -BM | grep '^/dev/' | grep -v '/boot$' | awk '{ut += $3} END {print ut}')
disk_percent=$(df -BM | grep '^/dev/' | grep -v '/boot$' | awk '{ut += $3} {ft+= $2} END {printf("%d"), ut/ft*100}')
# CPU load
cpul=$(top -bn1 | grep '^%Cpu' | cut -c 9- | xargs | awk '{printf("%.1f%%"), $1 + $3}')
# Last boot
lb=$(who -b | awk '$1 == "system" {print $3 " " $4}')
# LVM use
lvmu=$(if [ $(lsblk | grep "lvm" | wc -l) -eq 0 ]; then echo no; else echo yes; fi)
# TCP Connections
tcpc=$(ss -neopt state established | wc -l)
# User log
ulog=$(users | wc -w)
# Network
ip=$(hostname -I)
mac=$(ip link | grep "link/ether" | awk '{print $2}')
# Sudo
cmds=$(journalctl _COMM=sudo | grep COMMAND | wc -l)

wall "    #Architecture: $arch
    #CPU physical: $cpuf
    #vCPU: $cpuv
    #Memory Usage: $ram_use/${ram_total}MB ($ram_percent%)
    #Disk Usage: $disk_use/${disk_total}Gb ($disk_percent%)
    #CPU load: $cpul
    #Last boot: $lb
    #LVM use: $lvmu
    #Connections TCP: $tcpc ESTABLISHED
    #User log: $ulog
    #Network: IP $ip ($mac)
    #Sudo: $cmds cmd"
```

## 🔍 Evaluation

During the evaluation, be prepared to:
- Explain the choice between Debian and CentOS
- Show the different partition system
- Demonstrate that UFW service is running
- Demonstrate that SSH service is running
- Demonstrate that the chosen operating system is Debian or CentOS
- Explain advantages and disadvantages of the chosen operating system
- Verify that the monitoring script runs every 10 minutes
- Make the script run every minute for the evaluation
- Explain how the script works
- Create a new user and assign it to groups
- Explain password policy and implement a change

## 📚 Resources

- [Debian Documentation](https://www.debian.org/doc/)
- [UFW Documentation](https://help.ubuntu.com/community/UFW)
- [SSH Documentation](https://www.ssh.com/academy/ssh/config)
- [LVM Documentation](https://wiki.debian.org/LVM)

## ⚠️ Disclaimer

This project is part of the 42 School curriculum. The requirements might change over time, so make sure to always refer to the official subject for the most up-to-date information.

## 📝 License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details.
