#!/bin/bash
gcc 1942.c \
    -o1942 \
    -I/usr/local/include \
    -L/usr/local/lib \
    -Wl,-rpath,/usr/local/lib \
    -Wl,--enable-new-dtags \
    -lSDL3 \
    -lSDL3_image \

./1942