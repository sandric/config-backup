#!/bin/sh

# Configure PATH so that we can access our scripts below
PATH=$PATH:~/.cabal/bin:~/.xmonad/bin

# Configure X
xsetroot -cursor_name left_ptr &

# Configure Xinerama
xrandr --output DVI-0 --primary --left-of DVI-1 --output DVI-1 --auto

# Set background
sleep 1 && feh --bg-center ~/berserk.png &

# Start the system tray
tray &

# Load vimfootswitch
cd /home/sandric/vimfootswitch/ && sudo ./vimfootswitch.rb nohup > /dev/null &

# Start two terminals
terminator &

# Start synergy
#synergys --config ~/synergy.conf

# Start sound server
pulseaudio --start &
amixer sset Master unmute

#echo fs.inotify.max_user_watches=524288 | sudo tee -a /etc/sysctl.conf & sudo sysctl -p

exec dbus-launch --sh-syntax --exit-with-session xmonad
