#!/bin/bash

#Load Device Tree Overlay to Enable PRU
#GPIO selection pins mux
echo "PRU-GPIO-EXAMPLE" > /sys/devices/bone_capemgr.*/slots

echo "BB-BONE-PRU-01" > /sys/devices/bone_capemgr.*/slots

#Load Device Tree Overlay to Enable ADs

#GPIO selection pins mux
echo "cape-bone-iio" > /sys/devices/bone_capemgr.*/slots

/usr/share/openloop/hyperloop-core/core/BUILD/obj/core
