#pragma once

#include "CommonData.h"

using entry_point_t = void(*)(const CommonData*, CommonResult *);
extern "C" void entry_point(const CommonData* commonData, CommonResult * commonResult);
