#!/bin/bash

# Detectar el sistema operativo
OS=$(uname)

if [ "$OS" == "Darwin" ]; then
    # macOS - usa CoreAudio
    qemu-system-x86_64 -hda Image/x64BareBonesImage.qcow2 -m 512 -audiodev coreaudio,id=audio0 -machine pcspk-audiodev=audio0 

elif [ "$OS" == "Linux" ]; then
git else
    echo "Sistema operativo no soportado"
    exit 1
fi
