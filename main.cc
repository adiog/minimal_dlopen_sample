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

using sa_sigaction_t = void (*)(int, siginfo_t *, void *);

void register_signal_hendler(int signal, sa_sigaction_t sigaction_callback) {
    struct sigaction sa;

    sigemptyset(&sa.sa_mask);

    sa.sa_flags = SA_NODEFER;
    sa.sa_sigaction = sigaction_callback;

    sigaction(signal, &sa, NULL);
}

class reload_library {};

static void convert_sigterm_to_reload_library(int sig, siginfo_t *dont_care, void *dont_care_either) {
    throw reload_library();
}

void prevent_segfault() {
    register_signal_hendler(SIGSEGV, convert_segfault_to_runtime_error);
}

void continue_loop_on_sigterm() {
    register_signal_hendler(SIGTERM, convert_sigterm_to_reload_library);
}

int main() {
    const auto commonData = initCommonData();
    CommonResult commonResult;

    const char *lib = "./libqm-cont-load.so";

    prevent_segfault();
    continue_loop_on_sigterm();

    bool isRunning = true;

    while (isRunning) {
        auto dl = dlopen(lib, RTLD_LAZY);
        entry_point_t entryPoint = (entry_point_t) dlsym(dl, "entry_point");
        try {
            try {
                entryPoint(&commonData, &commonResult);
                std::cout << commonResult.output << '\n';
            } catch (std::runtime_error &runtimeError) {
                std::cout << "exception caught: " << runtimeError.what() << '\n';
            }
            std::cout << "finished execution; press x to stop, or any other key to continue" << '\n';
            if (getchar() == 'x') {
                isRunning = false;
            }
        } catch (reload_library &) {
            std::cout << "receiving signal - interrupting execution - reloading lib" << '\n';
        }
        dlclose(dl);
    }

    return 0;
}
