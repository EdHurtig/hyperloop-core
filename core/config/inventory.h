#ifndef _OPENLOOP_POD_CONFIG_INVENTORY_
#define _OPENLOOP_POD_CONFIG_INVENTORY_

#include "airsupply.h"
#include "power.h"
#include "photo.h"
#include "overrides.h"

/// MISC Sensors and other constants.
#define TUBE_LENGTH 1600
#define STOP_MARGIN 100
#define START_BRAKING 1100
#define BRAKING_TIMER 15.8 * USEC_PER_SEC//
#define EMERGENCY_TIMER 19.0 * USEC_PER_SEC // 4.9 + 10.9 + some
/*

Phase
Distance Travelled (m)
Velocity Range (m/s)
Acceleration (G’s)
Time (s)
Acceleration
202
0  →  82
1.70
4.9
Coasting
895
82
0
10.9
Braking
412
82 → 0
0.83
10.4
*/

#define PUSHER_PLATE_PIN 48
#define PUSHER_PLATE_DELAY 3*USEC_PER_SEC

// --------------------------
// Relay
// --------------------------
#define N_RELAY_CHANNELS 16

// --------------------------
// MUX
// --------------------------
#define N_MUXES 7
#define N_MUX_INPUTS 16
#define THERMO_MUX_0 5
#define THERMO_MUX_1 THERMO_MUX_0
#define PRESSURE_MUX 4
#define DISTANCE_MUX 6
#define PHOTO_MUX 1
#define SPARE_MUX_0 2
#define SPARE_MUX_1 3
#endif
