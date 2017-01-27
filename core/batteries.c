#include "pod.h"
#include "i2cfunc.h"

void read_batteries(pod_t *pod) {

  int handle;
  handle = i2c_open(I2CBUS, 0x0b);

  int voltage = get_pack_voltage(handle);
  if (voltage >= 0) {
    update_sensor(&(pod->battery[0].voltage), (float)voltage);
  }

  int current = get_pack_current(handle);
  if (current >= 0) {
    update_sensor(&(pod->battery[0].current), (float)current);
  }

  int state = is_pack_enabled(handle);
  if (state > 0) {
    pod->battery[0].enabled = true;
  } else {
    pod->battery[0].enabled = false;
  }

  i2c_close(handle);
}

int
get_pack_voltage(int handle)
{
  char buf[2];

  if (i2c_write_byte(handle, 0x09) < 0) {
    return -1;
  }

  if (i2c_read(handle, &buf[0], 2) < 0) {
    return -1;
  }

  return ((buf[0] << 8) | buf[1]);
}


int
get_pack_current(int handle)
{
  char buf[2];

  if (i2c_write_byte(handle, 0x0A) < 0) {
    return -1;
  }

  if (i2c_read(handle, &buf[0], 2) < 0) {
    return -1;
  }

  return ((buf[0] << 8) | buf[1]);
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
