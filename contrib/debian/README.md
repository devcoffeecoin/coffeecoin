
Debian
====================
This directory contains files used to package coffeecoind/coffeecoin-qt
for Debian-based Linux systems. If you compile coffeecoind/coffeecoin-qt yourself, there are some useful files here.

## coffeecoin: URI support ##


coffeecoin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install coffeecoin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your coffeecoinqt binary to `/usr/bin`
and the `../../share/pixmaps/coffeecoin128.png` to `/usr/share/pixmaps`

coffeecoin-qt.protocol (KDE)

