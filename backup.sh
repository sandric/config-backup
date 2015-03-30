#!/bin/bash

echo "Starting to copy config files and directories"

cp ~/.bashrc .
cp ~/.bash_profile .
cp ~/.profile .
cp ~/.gitconfig .
cp ~/.jshintrc .
cp ~/net-conf-usb .
cp ~/net-conf-wlan .
cp ~/net-up.sh .
cp ~/.rtorrent.rc .
cp ~/synergy.conf .
cp ~/.vimrc .
cp ~/.xinitrc .
cp ~/.xmodmap .

cp ~/sketchbook/USBHIDBootKbd-with-emulation/USBHIDBootKbd-with-emulation.ino .

mkdir -p xmonad
cp ~/.xmonad/xmonad.hs xmonad/.
cp ~/.xmonad/xmobar.hs xmonad/.
cp -R ~/.xmonad/bin xmonad/.

mkdir -p fish/functions
cp ~/.config/fish/config.fish fish/.
cp -R ~/.config/fish/functions fish/.

mkdir -p bin
cp ~/bin/cmus bin/.

mkdir -p vimfootswitch
cp -R ~/vimfootswitch/* vimfootswitch/.
