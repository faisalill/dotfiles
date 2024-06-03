#!/usr/bin/env sh

function notify(){
  hyprctl notify -1 1000 "rgb(ffffff)" "$1"
}

function resize() {
  hyprctl dispatch resizeactive $1 $2
}

x_pos=$(hyprctl activewindow | awk '/at:/ {print $2}' | cut -d ',' -f1)
y_pos=$(hyprctl activewindow | awk '/at:/ {print $2}' | cut -d ',' -f2)
x_size=$(hyprctl activewindow | awk '/size:/ {print $2}' | cut -d ',' -f1)
y_size=$(hyprctl activewindow | awk '/size:/ {print $2}' | cut -d ',' -f2)

x_extreme=$((x_pos + x_size))
y_extreme=$((y_pos + y_size))
midline_x=964
midline_y=562

monitor_x=1920
monitor_y=1080

gap=10

if [[ $1 == "up" ]]; then
  y=$((midline_y -  y_extreme - gap)) 
  resize 0 $y
elif [[ $1 == "down" ]]; then
  y=$((monitor_y - y_extreme - gap)) 
  resize 0 $y
elif [[ $1 == "left" ]]; then
  x=$((x_extreme - midline_x + gap))
  resize "-$x" 0 
else
  x=$((monitor_x - x_extreme - gap))
  resize $x 0 
fi
