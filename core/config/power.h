
#ifndef _OPENLOOP_POD_CONFIG_POWER_
#define _OPENLOOP_POD_CONFIG_POWER_

// --------------------------
// Power Board
// --------------------------

#define N_POWER_THERMO 3
#define POWER_THERMO_MUX THERMO_MUX_0
#define POWER_THERMO_INPUTS                                                    \
  { 13, 12, 11 }

// --------------------------
// Batteries
// --------------------------

#define N_BATTERIES 3
#define BATTERY_I2C_ADDRESSES                                                  \
  { 0x0b, 0x0b, 0x0b }

// --------------------------
// Frame Thermocouple
// --------------------------
#define N_FRAME_THERMO 1
#define FRAME_THERMO_MUX THERMO_MUX_0
#define FRAME_THERMO_INPUTS                                                    \
  { 10 }

#endif
