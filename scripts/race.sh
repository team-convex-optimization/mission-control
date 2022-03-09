#!/bin/bash

bash ~/mission-control/scripts/clean.sh

pushd ~/ 
    ./tco-actuationd/build/tco_actuationd.bin &
    ./tco-pland/build/tco_pland.bin -c &
    ./tco-pland/build/tco_pland.bin -pr &
    ./tco-sensord/build/tco_sensord.bin &
    ./tco-controld/build/tco_controld.bin & 
popd

wall "[Mission Control] Started racing pipeline..."
