#!/usr/bin/env sh

function notify() {
  hyprctl notify -1 1000 "rgb(ffffff)" "fontsize:30 $1"
}

function move() {
  hyprctl dispatch moveactive $1 $2
}

x_pos=$(hyprctl activewindow | awk '/at:/ { print $2}' | cut -d ',' -f1)
y_pos=$(hyprctl activewindow | awk '/at:/ { print $2}' | cut -d ',' -f2)

gap_start=10
gap_mid=18
start_x=0
start_y=56
midline_x=964
midline_y=572

if [[ $1 == "left" ]]; then
  x=$((x_pos - gap_start))
  move "-$x" 0 
elif [[ $1 == "right" ]]; then
  x=$((x_pos + midline_x - gap_mid))
  move $x 0 
elif [[ $1 == "up" ]]; then
  y=$((y_pos - start_y))
  move 0 "-$y"
else 
  y=$((midline_y - y_pos ))
  move 0 $y
fi

