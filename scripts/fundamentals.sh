#!/bin/bash

bash ~/mission-control/scripts/clean.sh

pushd ~/
    ./tco-actuationd/build/tco_actuationd.bin &
    echo 1 > /sys/module/ov5645_camera_mipi_v2/parameters/ov5645_af
    ./tco-pland/build/tco_pland.bin -c &
    echo 1 > /sys/module/ov5645_camera_mipi_v2/parameters/ov5645_af
    ./tco-sensord/build/tco_sensord.bin &
popd

echo " `date` [Mission Control] Started fundamentals..." >> /home/mendel/log.txt
