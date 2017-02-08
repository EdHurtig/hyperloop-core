#ifndef _OPENLOOP_POD_CONFIG_PHOTO_
#define _OPENLOOP_POD_CONFIG_PHOTO_

// OLD
// #define DISTANCE_CALIBRATION_A -30.136
// #define DISTANCE_CALIBRATION_B 183.0
// #define DISTANCE_CALIBRATION_C -259.62

#define DISTANCE_CALIBRATION_A 0.0
#define DISTANCE_CALIBRATION_B 0.0000908751
#define DISTANCE_CALIBRATION_C -0.2081114465
#define DISTANCE_CALIBRATION_D 135.37385

// --------------------------
// Vertical
// --------------------------

#define N_CORNER_DISTANCE 4
#define CORNER_DISTANCE_MUX DISTANCE_MUX
#define CORNER_DISTANCE_INPUTS                                                 \
  { 0, 1, 2, 3 }

#define N_WHEEL_DISTANCE 3
#define WHEEL_DISTANCE_MUX DISTANCE_MUX
#define WHEEL_DISTANCE_INPUTS                                                  \
  { 4, 5, 6 }

// --------------------------
// Lateral
// --------------------------

#define N_LATERAL_DISTANCE 3
#define LATERAL_DISTANCE_MUX DISTANCE_MUX
#define LATERAL_DISTANCE_INPUTS                                                \
  { 7, 8, 9 }

// --------------------------
// Shell
// --------------------------

#define N_SHELL_PHOTO 4
#define SHELL_PHOTO_MUX PHOTO_MUX
#define SHELL_PHOTO_INPUTS                                                     \
  { 0, 1, 2, 3 }

// --------------------------
// Wheels
// --------------------------

#define N_WHEEL_PHOTO 3
#define WHEEL_PHOTO_MUX PHOTO_MUX
#define WHEEL_PHOTO_INPUTS                                                     \
  { 4, 5, 6 }

#endif
