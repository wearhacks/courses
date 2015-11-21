#!/usr/bin/env bash

// Finally, We prefer to manually open the WebBrower
// sinc this way the browser stay open when we restart this script
// ./scripts/openHomePage.sh &

./scripts/screenSaverOff.sh
./scripts/hideMouseCursor.sh

exec node bootstrap.js
