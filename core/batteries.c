#include "pod.h"
#include "i2cfunc.h"

void read_batteries(pod_t *pod, int bus) {
  int handle;
  handle = i2c_open(bus, 0x0b);

  if (handle < 0) {
    debug("Failed to connect to bus %d", bus);
    return;
  }

  int voltage = get_pack_voltage(handle);
  if (voltage >= 0) {
    update_sensor(&(pod->battery[bus].voltage), (float)voltage);
  }

  int current = get_pack_current(handle);
  if (current >= 0) {
    update_sensor(&(pod->battery[bus].current), (float)current);
  }

  i2c_close(handle);
}

int16_t get_pack_voltage(int handle)
{
  char buf[2];

  if (i2c_write_byte(handle, 0x09) < 0) {
    return -1;
  }

  if (i2c_read(handle, &buf[0], 2) < 0) {
    return -1;
  }

  return ((buf[1] << 8) | buf[0]);
}

int16_t get_pack_current(int handle)
{
  char buf[2];

  if (i2c_write_byte(handle, 0x0A) < 0) {
    return -1;
  }

  if (i2c_read(handle, &buf[0], 2) < 0) {
    return -1;
  }

  return ((buf[1] << 8) | buf[0]);
}

int
is_pack_enabled(int handle)
{
  if (i2c_write_byte(handle, 0x54) < 0) {
    return -1;
  }

  char buf[4];
  if (i2c_read(handle, &buf[0], 4) < 0) {
    return -1;
  }

  return ((buf[3] & 0x6) == 6);
}

int
toggle_pack(int handle)
{
  char buf[4] = { 0x00, 0x22, 0x00 };

  if (i2c_write(handle, &buf[0], 3) < 0) {
    return -1;
  }

  return 0;
}