## WORKSATION SETUP

### U-BOOT:
  * sudo apt update
    sudo apt install build-essential gcc-arm-linux-gnueabihf swig libgnutls28-dev libncurses-dev\
    u-boot-tools device-tree-compiler git python3

  * git clone https://source.denx.de/u-boot/u-boot.git
    cd u-boot

### SETUP H3:
 * make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- bananapi_m2_zero_defconfig

### BUILD:
 * make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -j$(nproc)

### INSTALL:
 * sudo sunxi-fel uboot u-boot-sunxi-with-spl.bin

### ACTIVATE PERMISION:
 * sudo nano /etc/udev/rules.d/50-sunxi-fel.rules
 * PAST: SUBSYSTEM=="usb", ATTR{idVendor}=="1f3a", ATTR{idProduct}=="efe8", MODE="0666"
 * sudo udevadm control --reload-rules
   sudo udevadm trigger
 * PLUG IN DEVICE -> RUN -> sunxi-fel version

### SCREEN:
* 


