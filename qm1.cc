#include "CommonData.h"

extern "C" {
void entry_point(const CommonData* commonData, CommonResult * commonResult) {
    commonResult->output = commonData->input + 7;
}
}
