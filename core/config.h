/*****************************************************************************
 * Copyright (c) Paradigm Hyperloop, 2017
 *
 * This material is proprietary intellectual property of Paradigm Hyperloop.
 * All rights reserved.
 *
 * The methods and techniques described herein are considered proprietary
 * information. Reproduction or distribution, in whole or in part, is
 * forbidden without the express written permission of Paradigm Hyperloop.
 *
 * Please send requests and inquiries to:
 *
 *  Software Engineering Lead - Eddie Hurtig <hurtige@ccs.neu.edu>
 *
 * Source that is published publicly is for demonstration purposes only and
 * shall not be utilized to any extent without express written permission of
 * Paradigm Hyperloop.
 *
 * Please see http://www.paradigm.team for additional information.
 *
 * THIS SOFTWARE IS PROVIDED BY PARADIGM HYPERLOOP ''AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL PARADIGM HYPERLOOP BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 ****************************************************************************/

#include "config_inventory.h"
#include "config_scores.h"

#ifndef _OPENLOOP_POD_CONFIG_
#define _OPENLOOP_POD_CONFIG_

// --------------------------
// Branding
// --------------------------
#define POD_COPY_OWNER "Paradigm - Controls Team"
#define POD_COPY_YEAR "2016"
#define POD_CREDITS                                                            \
  "Eddie Hurtig - Software Engineering Lead\n"                                 \
  "Upen Naidoo - Embedded Systems Engineer\n"

// Error Thresholds
#define A_ERR_X 0.02
#define A_ERR_Y 0.02
#define A_ERR_Z 0.02
#define V_ERR_X 0.1
#define V_ERR_Y 0.1
#define V_ERR_Z 0.1

#define HEARTBEAT_TIMEOUT 1000 // (ms)
// Signals
#define POD_SIGPANIC SIGUSR1

// IMU Device
#define IMU_DEVICE "/dev/ttyUSB0"
#define IMU_MESSAGE_SIZE 32

// Defines how much filtering should be done in the Exponential Moving Average
// filter for the IMU input.
// The formula used is:
//   (new_accel = (1.0-IMU_EMA_ALPHA)*old_accel + IMU_EMA_ALPHA*accel_reading)
#define IMU_EMA_ALPHA 0.01f

// -------------------------
// Subsystem Identifiers
// -------------------------
// The Main Thread
#define POD_MAIN_SUBSYSTEM 1
// The Core Processing Loop
#define POD_CORE_SUBSYSTEM 2
// The Command Server
#define POD_COMMAND_SUBSYSTEM 4
// The Logging Client
#define POD_LOGGING_SUBSYSTEM 8

// ----------------------
// Thread Sleep Intervals
// --------------------------------------------------------------------------
// Each thread is a loop, how long should the thread sleep for each iteration
// --------------------------------------------------------------------------
#define CORE_THREAD_SLEEP 0
#define CORE_PERIOD_USEC (USEC_PER_SEC / 1000)
#define LOGGING_THREAD_SLEEP 5000

// --------------
// Debug Printing
// --------------
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wgnu-zero-variadic-macro-arguments"

#ifdef POD_DEBUG
#define FLINE __FILE__ ":" __XSTR__(__LINE__)
#define output(prefix_, fmt_, ...)                                             \
  pod_log((prefix_ "[%s] {" FLINE "} " fmt_ "\n"), __FUNCTION__, ##__VA_ARGS__)
#else
#define output(prefix_, fmt_, ...) pod_log((prefix_ fmt_ "\n"), ##__VA_ARGS__)
#endif

#ifdef POD_DEBUG
#define debug(fmt_, ...) output("[DEBUG] ", fmt_, ##__VA_ARGS__)
#else
#define debug(fmt_, ...)
#endif

#define warn(fmt_, ...) output("[WARN]  ", fmt_, ##__VA_ARGS__)
#define error(fmt_, ...) output("[ERROR]  ", fmt_, ##__VA_ARGS__)
#define info(fmt_, ...) output("[INFO]  ", fmt_, ##__VA_ARGS__)
#define note(fmt_, ...) output("[NOTE]  ", fmt_, ##__VA_ARGS__)
#define fatal(fmt_, ...) output("[FATAL] ", fmt_, ##__VA_ARGS__)
#define panic(subsystem, notes, ...)                                           \
  pod_panic(subsystem, __FILE__, __LINE__, notes, ##__VA_ARGS__)

// Helper that wraps set_pod_mode but adds file and line number
// REVIEW: Probably should remove
#define DECLARE_EMERGENCY(message, ...)                                        \
  set_pod_mode(Emergency, __FILE__ ":" __XSTR__(LINE__) message, ##__VA_ARGS__)

#pragma clang diagnostic pop

// ------------------
// Primary Braking Thresholds
// ------------------

/// 0.8 G = 0.8 * 9.8 m/s/s * 1000 mm / m
#define PRIMARY_BRAKING_ACCEL_X_MIN -5.88 // -0.6 G => mm/s/s
#define PRIMARY_BRAKING_ACCEL_X_NOM -7.84 // -0.8 G => mm/s/s
#define PRIMARY_BRAKING_ACCEL_X_MAX -24.5 // -2.5 G => mm/s/s

/// TODO: Need Real Values
/// NOMINAL: 100N /// REVIEW: Guess
#define PRIMARY_BRAKING_ENGAGED_MIN_F 80
#define PRIMARY_BRAKING_ENGAGED_NOM_F 100
#define PRIMARY_BRAKING_ENGAGED_MAX_F 150

// ------------------
// Emergency Braking Thresholds
// ------------------
/// NOMINAL: 1.2 G = 1.2 * 9.8 m/s/s * 1000 mm / m
#define CLAMP_BRAKING_ACCEL_X_MIN -7.84  // -0.8 G => mm/s/s
#define CLAMP_BRAKING_ACCEL_X_NOM -11.76 // -1.2 G => mm/s/s
#define CLAMP_BRAKING_ACCEL_X_MAX -49.00 // -5.0 G => mm/s/s

/// TODO: Need Real Values
/// NOMINAL: 1000N /// REVIEW: Guess
#define CLAMP_ENGAGED_MIN_F 800
#define CLAMP_ENGAGED_NOM_F 1000
#define CLAMP_ENGAGED_MAX_F 1500

//----------------------
// Pushing Thresholds
//----------------------

// If the accell drops to below this value, the pod will change to Coasting
// This value should indicate when the pusher has fully detached
#define PUSHING_MIN_ACCEL 0.2
// If the accell drops to below this value, the pod will change to Coasting
// This value should indicate when the pusher has fully detached
#define COASTING_MIN_ACCEL_TRIGGER -0.1

// ---------------------
// Lateral Sensor Config
// ---------------------
#define LATERAL_MIN 5.0
#define LATERAL_MAX 7.0

// ---------------------
// Skate config
// ---------------------
#define REG_THERMO_MIN 5.0
#define HEIGHT_MIN 2.0
#define HEIGHT_MAX 16.0

// ---------------------
// Logging Configuration
// ---------------------
#define LOG_FILE_PATH "./hyperloop-core.log"
#define LOG_FILE_MODE S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH
#define MAX_PACKET_SIZE 1024
#define LOG_SVR_NAME "pod-server.openloopalliance.com"
#define LOG_SVR_PORT 7778
#define MAX_LOG_LINE 512
#define LOG_BUF_SIZE MAX_LOG_LINE * 50

// ---------------
// Command Control
// ---------------
#define POD_CLI_VERSION "0.0.1-alpha"
#define CMD_SVR_PORT 7779
#define CMD_MAX_ARGS 32
#define POD_ETOOMANYCLIENTS_TXT "Too Many Clients are connected"

// static buffer that is written to by each of the command functions
#define CMD_OUT_BUF 4096

#define MAX_CMD_CLIENTS 16

// Misc
#define POD_BOOT_SEM "/openloop.pod.boot"
#define MAX_NAME 63
#endif
