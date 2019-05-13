# Security module Whitelist using LSM framework
## Description
The simple LSM module. This module an attr-based access control. Binaries with a particular xattr setting will be permitted to be executed by non-root users. 
Also in the catalog `/security/whitelist/util` to be util which provides simple way to changing xattr of files and check files with that attribute - `security.whitelisted`, where attribute value should to be great than 0 (zero).
## Using 
For grant access to execute binary file by non-root users you should run in the terminal next command:
```
sudo setfattr -n security.whitelisted -v 1 <filename>
```
For deny you should run:
```
sudo setfattr -x security.whitelisted <filename>
```
## Using /security/whitelist/util
For grant access to execute binary file by non-root users you should run in the terminal next command:
```
sudo util --add <filename>
```
For deny you should run:
```
sudo util --del <filename>
```
If you want to see files with `security.whitelisted` attribute in the current catalog you should run:
```
util --list
#or just
util
```
## Installation
The code has been tested upon kernels as recent as 4.15.48

Copy the contents of `security/` and `include/` into your local Kernel-tree, and run `make menuconfig` to enable the appropriate options.

If you want to build Kernel on Ubuntu you can follow this guide:
https://wiki.ubuntu.com/Kernel/BuildYourOwnKernel

NOTE: Over time the two files security/Kconfig & security/Makefile might need resyncing with the base versions installed with the Linux source-tree, you can look for mentions of WHITELIST to see what I've done to add the modules.

For a Debian GNU/Linux host, building a recent kernel, these are the dependencies you'll need to install:
```
apt-get install flex bison bc libelf-dev libssl-dev \
    build-essential make libncurses5-dev \
    git-core
```
