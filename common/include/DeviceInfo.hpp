
#pragma once

#include <stdint.h>

#include "deviceinfo.h"

namespace Freyja {

class DeviceInfo {
public:
	DeviceInfo(IReaderWriter* rw) {
		_rw = rw;
	}

	uint64_t GetSerial() {
		return _device_info.serial;
	};
	void SetSerial(uint64_t serial) {
		_device_info.serial = serial;
	};

	uint64_t GetType() {
		return _device_info.type;
	};
	void SetType(uint64_t type) {
		_device_info.type = type;
	};

private:
	IReaderWriter _rw;
	device_info_t _device_info;

};

}