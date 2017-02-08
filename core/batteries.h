#ifndef OPENLOOP_BATTERIES_H
#define OPENLOOP_BATTERIES_H
#include "pod.h"
#include "i2cfunc.h"

#define BATTERY_0_ADDRESS 0x0b

void read_batteries(pod_t *pod, int bus);

int16_t get_pack_voltage(int handle);

int16_t get_pack_current(int handle);

int is_pack_enabled(int handle);

int toggle_pack(int handle);
#endif
