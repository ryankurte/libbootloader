
#include "Application.hpp"

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "Version.hpp"

namespace Freyja {

Application::Application(int major, int minor, int patch, char* description, uint8_t *data, size_t size)
{
	_version = new Version(major, minor, patch, description);
	_size = size;
	_data = (uint8_t*)malloc(size);
	memcpy(_data, data, size);
}

Application::~Application()
{
	delete _version;
	free(_data);
	_size = 0;
}

int Application::GetData(size_t offset, size_t size, uint8_t* data)
{
	size_t count = ((offset + size) < _size) ? size : _size;

	memcpy(data, _data + offset, size);

	return count;
}

Version* Application::GetVersion()
{
	return _version;
}

uint32_t Application::GetChecksum() {
	//TODO: calculate checksum
	return 0;
}

}
