# Security module Whitelist using LSM framework
## Description
The simple LSM module. This module an attr-based access control. Binaries with a particular xattr setting will be permitted to be executed by non-root users. 
Also in the catalog `/security/whitelist/util` to be util which provides simple way to changing xattr of files and check files with that attribute - `security.whitelisted`, where attribute value should to be great than 0 (zero).
## Using 
For grant access to execute binary file by non-root users you should run in the terminal next command:
```
sudo setfattr -n security.whitelisted -v 1 [filename]
```
For deny you should run:
```
sudo setfattr -x security.whitelisted [filename]
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
## Installing
TODO
