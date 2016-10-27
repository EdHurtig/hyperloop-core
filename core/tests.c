/*****************************************************************************
 * Copyright (c) OpenLoop, 2016
 *
 * This material is proprietary of The OpenLoop Alliance and its members.
 * All rights reserved.
 * The methods and techniques described herein are considered proprietary
 * information. Reproduction or distribution, in whole or in part, is
 * forbidden except by express written permission of OpenLoop.
 *
 * Source that is published publicly is for demonstration purposes only and
 * shall not be utilized to any extent without express written permission of
 * OpenLoop.
 *
 * Please see http://www.opnlp.co for contact information
 ****************************************************************************/

#include "pod.h"

int selfTest(pod_state_t * state) {
  int i;

  for (i=0; i < N_SKATE_SOLONOIDS; i++) {
    warn("Activating Skate Solonoid: %d", i);
    bbb_setGpioValue(state->skate_solonoid_pins[i].gpio, 0);

    sleep(1);
  }

  for (i=0; i < N_SKATE_SOLONOIDS; i++) {
    warn("Deactiveating Skate Solonoid: %d", i);
    bbb_setGpioValue(state->skate_solonoid_pins[i].gpio, 0);

    sleep(1);
  }

  return 0;
}
