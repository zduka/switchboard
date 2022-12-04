#!/bin/bash
echo "Syncing source code..."
rsync -r -ssh src platformio.ini peta@10.0.0.38:/home/peta/devel/switchboard --delete
echo "Buiding avr-src"
ssh peta@10.0.0.38 "cd ~/devel/switchboard && pio run --target upload"
