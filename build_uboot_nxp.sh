#!/bin/bash
echo "清理工程"
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- distclean
echo "配置uboot"
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- mx6ull_14x14_evk_emmc_defconfig
echo "编译uboot"
read -p "精简信息“0” or 详细信息“1”:"  cmd
make V=${cmd}  ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -j16
