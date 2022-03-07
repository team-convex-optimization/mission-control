#!/bin/bash

bash scripts/clean.sh

pushd ~/
    ./tco-actuationd/build/tco_actuationd.bin &
    ./tco-pland/build/tco_pland.bin -c &
    ./tco-sensord/build/tco_sensord.bin &
popd

echo "DONE"