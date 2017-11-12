#!/bin/sh

for size in 256 128 64 32 16; do
    convert onex.png -resize "${size}x${size}" "onex${size}.png"
    convert onex.png -resize "${size}x${size}" "onex${size}.xpm"
done
