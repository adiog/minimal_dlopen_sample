#include <chrono>
#include <thread>
#include "CommonData.h"

extern "C" {
void entry_point(const CommonData* commonData, CommonResult * commonResult) {
    commonResult->output = commonData->input + 123;
    std::this_thread::sleep_for(std::chrono::seconds(10));
}
}
