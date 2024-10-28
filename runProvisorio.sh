#!/bin/bash
sudo chmod -R 777 *
qemu-system-x86_64 -hda Image/x64BareBonesImage.qcow2 -m 512

