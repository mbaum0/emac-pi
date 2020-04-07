#!/usr/bin/env bash

# display resolution width
RES_WIDTH=1280

# display resolution height
RES_HEIGHT=960

# display frequency
FREQ=72

# set this to whatever you'd like
MODE_NAME="emac_0"

# get VESA CVT modelines for use with X
cvt_out=$(cvt $RES_WIDTH $RES_HEIGHT $FREQ)

# get the last 11 elements from cvt output (these are the  configs)
cvt_configs=$(echo $cvt_out | rev | cut -d' ' -f1-11 | rev)

# delete existing mode
xrandr --rmmode $MODE_NAME

# create new mode
xrandr --newmode $MODE_NAME $cvt_configs

# list monitors to select from
x_mon_out=$(xrandr --listmonitors)

avail_monitors=$(xrandr --listmonitors | cut -d' ' -f3- | cut -d$'\n' -f2-)

# just get names of available monitors
for i in "${!avail_monitors[@]}"
do
    avail_monitors[$i]=$(echo ${avail_monitors[$i]} | rev | cut -d' ' -f1 | rev)
done

# ask user which display this is for
PROMPT='Select which display output to configure'

echo $PROMPT
select opt in "${avail_monitors[@]}"
do
    DISPLAY_OUT=$opt
    break
done

# add mode to display
xrandr --addmode $DISPLAY_OUT $MODE_NAME

# set mode output
xrandr --output $DISPLAY_OUT --mode $MODE_NAME

echo "Done!"
