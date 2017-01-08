Allwinner bootloader
====================

Bootloader sources for Allwinner SOCs

Main target of this repo is add ability to build
boot0 by GNU ARM toolchain (arm-none-eabi) under linux environment.

Since i have A20 and A31 chips only, pull requests
for other chips are welcome.

Prerequisites
=============
- Lichee-tools: https://github.com/allwinner-ics/lichee_tools
- wine
- arm-none-eabi- toolchain
- make

Usage
=====

1. modify Lichee-tools path if needed: WORKTOOLS variable in basic_loader/config/ARMCC_CROSSTOOL.CFG
2. modify board settings accordingly (file boot0/boot0_head.c)
3. open terminal and cd to basic_loader/boot0 directory
4. run make -f make_aXX , where aXX is you chip name: e.g. a31.
