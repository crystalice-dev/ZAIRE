#!/bin/bash

# --- CONFIG ---
PORT=/dev/ttyS2
BAUD=115200
# --------------

esptool.py --chip esp32s3 --port $PORT --baud $BAUD write_flash -z \
  --flash_mode dio --flash_size 2MB --flash_freq 80m \
  0x0 bootloader.bin \
  0x8000 partition-table.bin \
  0x10000 S3_HUB.bin

