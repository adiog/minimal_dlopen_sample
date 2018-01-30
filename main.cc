#include <dlfcn.h>
#include <iostream>
#include <vector>
#include "CommonData.h"
#include "qm.h"

CommonData initCommonData() {
    CommonData commonData;
    commonData.input = 42;
    return commonData;
}

int main() {
    const auto commonData = initCommonData();
    CommonResult commonResult;
    std::vector<std::string> libs = {"./libqm1.so", "./libqm2.so"};
    for(const auto& lib : libs) {
        auto dl = dlopen(lib.c_str(), RTLD_LAZY);
        entry_point_t entryPoint = (entry_point_t) dlsym(dl, "entry_point");
        entryPoint(&commonData, &commonResult);
        std::cout << commonResult.output << '\n';
        dlclose(dl);
    }
    return 0;
}
