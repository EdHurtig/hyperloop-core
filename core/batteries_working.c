#include <stdio.h>
#include "i2cfunc.h"

#define I2CBUS 1

int main(int argc, char *argv[]) {
  int handle;
  handle = i2c_open(1, 0x0b);
  char buf[2];
  if (i2c_write_byte(handle, 0x0A) < 0) {
    return -1;
  }

  if (i2c_read(handle, &buf[0], 2) < 0) {
    return -1;
  }

  printf("Current: %dmA", ((buf[0] << 8) | buf[1]));

  if (argc > 1) {

    if (toggle_pack(handle) == 0) {
      printf("Pack has been toggled");
    } else {
      printf("Failed to communicate with pack");
    }
  } else {
    int enabled = is_pack_enabled(handle);
    printf("STATE=%d", enabled);
    if (enabled == 1) {
      printf("Enabled\n");
    } else {
      printf("Disabled\n");
    }
  }
  i2c_close(handle);
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

  printf("Response %X%X%X%X\n", buf[0], buf[1], buf[2], buf[3]);

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
