#!/bin/bash
sudo chmod -R 777 *
qemu-system-x86_64 -hda Image/x64BareBonesImage.qcow2 -m 512 -audiodev pa,id=audio0 -machine pcspk-audiodev=audio0

