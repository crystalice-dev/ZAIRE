## WORKSATION SETUP

### U-BOOT:
  * sudo apt update
    sudo apt install build-essential gcc-arm-linux-gnueabihf swig libgnutls28-dev\
    u-boot-tools device-tree-compiler git python3

  * git clone https://source.denx.de/u-boot/u-boot.git
    cd u-boot

### SETUP H3:
 * make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- bananapi_m2_zero_defconfig

### BUILD:
 * make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -j$(nproc)

### INSTALL:
 * sudo sunxi-fel uboot u-boot-sunxi-with-spl.bin

### SCREEN:
* 


