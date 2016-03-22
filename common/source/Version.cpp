
#include "Version.hpp"

#include <string.h>

namespace Freyja {

Version::Version(int major, int minor, int patch, char* description) {
	_major = major;
	_minor = minor;
	_patch = patch;
	strncpy(_description, description, DESCRIPTION_MAX-1);
}
	
};
