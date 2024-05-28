#!/bin/bash

# Detectar el sistema operativo
OS=$(uname)

if [ "$OS" == "Darwin" ]; then
    # macOS - usa CoreAudio
    AUDIO_DRIVER="coreaudio"
elif [ "$OS" == "Linux" ]; then
    # Linux - usa PulseAudio o ALSA
    if command -v pulseaudio >/dev/null 2>&1; then
        AUDIO_DRIVER="pa"
    else
        AUDIO_DRIVER="alsa"
    fi
else
    echo "Sistema operativo no soportado"
    exit 1
fi

# Ejecutar QEMU con el controlador de audio adecuado
qemu-system-x86_64 -hda Image/x64BareBonesImage.qcow2 -m 512 -audiodev ${AUDIO_DRIVER},id=audio0 -machine pcspk-audiodev=audio0
