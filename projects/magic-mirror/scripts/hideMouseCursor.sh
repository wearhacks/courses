
export DISPLAY=:0

# Place cursor at the bottom right corner
echo "Hiding mouse cursor..."
xdotool mousemove `xdotool getdisplaygeometry`

# FIXME: Still see one pixel
