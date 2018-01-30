#include <dlfcn.h>
#include <iostream>
#include <vector>
#include <signal.h>
#include "CommonData.h"
#include "qm.h"

CommonData initCommonData() {
    CommonData commonData;
    commonData.input = 42;
    return commonData;
}

static void convert_segfault_to_runtime_error(int sig, siginfo_t *dont_care, void *dont_care_either) {
    throw std::runtime_error("");
}

void prevent_segfault() {
    struct sigaction sa;

    sigemptyset(&sa.sa_mask);

    sa.sa_flags = SA_NODEFER;
    sa.sa_sigaction = convert_segfault_to_runtime_error;

    sigaction(SIGSEGV, &sa, NULL);
}

int main() {
    const auto commonData = initCommonData();
    CommonResult commonResult;
    std::vector<std::string> libs = {"./libqm1.so", "./libqm2.so"};
    prevent_segfault();
    for (const auto &lib : libs) {
        auto dl = dlopen(lib.c_str(), RTLD_LAZY);
        entry_point_t entryPoint = (entry_point_t) dlsym(dl, "entry_point");
        try {
            entryPoint(&commonData, &commonResult);
            std::cout << commonResult.output << '\n';
        } catch (...) {
            std::cout << "exception caught" << '\n';
        }
        dlclose(dl);
    }
    return 0;
}
