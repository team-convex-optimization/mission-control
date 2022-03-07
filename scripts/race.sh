#!/bin/bash

sh clean.sh

pushd $HOME
    ./tco-utils/shmem_mgr/build/tco_shmem_mgr -c
    ./tco-actuationd/build/tco_actuationd &
    ./tco-pland/build/tco_pland -c &
    ./tco-pland/build/tco_pland -pr &
    ./tco-controld/build/tco_controld &
    ./tco-sensord/build/tco_sensord &
popd
