#!/bin/bash

pkill tco_* # Kill all current tco jobs. NOTE that mission_control is on __tco regex

pushd $HOME
    ./tco-utils/shmem_mgr/build/tco_shmem_mgr.bin -d > /dev/null
    ./tco-utils/shmem_mgr/build/tco_shmem_mgr.bin -c > /dev/null
popd

