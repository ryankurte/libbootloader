

#pragma once

#include <stdint.h>
#include <stddef.h>

namespace Freyja
{

#define DESCRIPTION_MAX 	32

class Version
{
public:
    Version(int major, int minor, int patch, char* description);

    int GetMajor() { return _major; }
    int GetMinor() { return _minor; }
    int GetPatch() { return _patch; }
    char* GetDescription() { return _description; }

private:
    int _major;
    int _minor;
    int _patch;
    char _description[DESCRIPTION_MAX];
};

}
