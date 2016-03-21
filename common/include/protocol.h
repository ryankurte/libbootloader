/**
 * Types for communication and storage with the bootloader and programmer
 */

#ifndef LOADER_PROTOCOL_H
#define LOADER_PROTOCOL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "loadertypes.h"

#define MAX_DESCRIPTION 16

enum loader_result_e {
  LOADER_RES_OK = 0,
  LOADER_RES_DONE = 1,
  LOADER_RES_ERR = -1
};

enum loader_packet_e {
  LOADER_PACKET_NOP,
  LOADER_PACKET_DEV_INFO_GET = 1,
  LOADER_PACKET_DEV_INFO_RESP = 2,
  LOADER_PACKET_APP_INFO_GET = 1,
  LOADER_PACKET_APP_INFO_RESP = 2,
  LOADER_PACKET_WRITE_APP = 3,
  LOADER_PACKET_WRITE_USER = 4,
  LOADER_PACKET_ERASE = 5,
  LOADER_PACKET_CHECK = 6,
  LOADER_PACKET_REBOOT = 7
};

// Device feature flags
#define DEVICE_FLAG_NONE    0
#define DEVICE_FLAG_CRC     (1 << 1)  //!< Device supports application CRC
#define DEVICE_FLAG_SHA     (1 << 2)  //!< Device supports SHA256 checksums
#define DEVICE_FLAG_SIG     (1 << 3)  //!< Device supports application signatures

struct loader_get

struct loader_packet_s {
  uint8_t commmand;
  
} __attribute((packed));

#ifdef __cplusplus
}
#endif

#endif
