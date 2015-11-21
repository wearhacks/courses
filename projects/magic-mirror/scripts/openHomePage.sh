
export DISPLAY=:0

PID="`pidof iceweasel`"

if [ -z "$PID" ]; then
  # exec iceweasel --display=:0 localhost:8080
  # Now open with default home page, which is localhost:8080
  echo "Starting iceweasel. Opening default home page."
  exec iceweasel
else
  echo
  echo "WARNING! iceweasel already running with PID $PID"
  echo
fi
  
