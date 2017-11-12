
Debian
====================
This directory contains files used to package onexd/onex-qt
for Debian-based Linux systems. If you compile onexd/onex-qt yourself, there are some useful files here.

## onex: URI support ##


onex-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install onex-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your onex-qt binary to `/usr/bin`
and the `../../share/pixmaps/onex128.png` to `/usr/share/pixmaps`

onex-qt.protocol (KDE)

