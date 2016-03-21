/**
 * Types for communication and storage with the bootloader and programmer
 */

#ifndef LOADER_TYPES_H
#define LOADER_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define MAX_DESCRIPTION 16

enum loader_packet_e {
  LOADER_PACKET_CONTROL,
  LOADER_PACKET_DATA_REQ,
  LOADER_PACKET_DATA_RESP,
};

enum loader_result_e {
  LOADER_RES_OK = 0,
  LOADER_RES_ERR = -1
};

enum loader_command_e {
  LOADER_CMD_NOP,
  LOADER_CMD_WRITE_APP = 1,
  LOADER_CMD_WRITE_USER = 2,
  LOADER_CMD_ERASE = 3,
  LOADER_CMD_CHECK = 4,
  LOADER_CMD_REBOOT = 5
};

// Device feature flags
#define DEVICE_FLAG_NONE    0
#define DEVICE_FLAG_CRC     (1 << 1)  //!< Device supports application CRC
#define DEVICE_FLAG_SHA     (1 << 2)  //!< Device supports SHA256 checksums
#define DEVICE_FLAG_SIG     (1 << 3)  //!< Device supports application signatures

/**
 * @brief Device information structure
 * Use to transfer and store information about a given device
 * Type is intended for use matching different devices to differing application binaries.
 * This can be split as required by the implementation (for example, 16 bit family, 16 bit variant, 32 bit skew). 
 * Note that devices will already be filtered by the protocol (ie. VID and PID with USB).
 */
struct dev_info_s {
  uint64_t serial;      //!< Device serial number
  uint64_t type;        //!< Device type identifier (matching is implementation specific)
  
  uint32_t page_size;   //!< Device flash page size (bytes)
  uint32_t flash_size;  //!< Device total flash size (bytes)
  uint32_t user_size;   //!< User data size (bytes)
  
  uint32_t flags;       //!< Device support flags
} __attribute((packed));

typedef dev_info_s dev_info_t;

/**
 * @brief Application information structure
 * Use to transfer and store information about the current application
 * See http://semver.org/ for versioning information
 * Discription is intended to store the output of `git describe --dirty` where the repo 
 * uses semantic version style tags, so that an application can be traced back to a specific
 * commit version.
 */
struct app_info_s {
  uint16_t version_major;   
  uint16_t version_minor;
  uint16_t version_patch;
  
  uint32_t size;          //!< Application size (bytes)
  uint32_t crc;           //!< Application CRC
  
  uint8_t description[MAX_DESCRIPTION];
} __attribute((packed));

typedef app_info_s app_info_t;

#ifdef __cplusplus
}
#endif

#endif
