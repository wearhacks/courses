

PID="`pidof iceweasel`"

if [ -z "$PID" ]; then
  echo
  echo "WARNING! iceweasel is not running"
  echo
else
  export DISPLAY=:0
  WIN_ID="$(xdotool search --sync --all --onlyvisible --name iceweasel)"
  xdotool key --window ${WIN_ID} "F5"
  echo "Refresh send to iceweasel"
fi
  
