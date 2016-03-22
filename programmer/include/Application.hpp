

#pragma once

#include <stdint.h>
#include <stddef.h>

#include "Version.hpp"

namespace Freyja {

class Application {
public:
	Application(int major, int minor, int patch, char* description, uint8_t *data, size_t size);
	~Application();

	int GetData(size_t offset, size_t size, uint8_t* data);
	Version* GetVersion();
	uint32_t GetChecksum();

private:
	Version *_version;
	uint8_t* _data;
	size_t _size;
};

}
