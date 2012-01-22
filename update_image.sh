#!/bin/bash

sudo losetup /dev/loop0 floppy.img && mkdir -p ./.tmp && sudo mount /dev/loop0 ./.tmp && sudo cp src/kernel ./.tmp/kernel 
sudo umount /dev/loop0 2>/dev/null
sudo losetup -d /dev/loop0 2>/dev/null
