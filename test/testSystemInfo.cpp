#include <iostream>
#include <string>
#include <vector>

#include "../include/SystemInfo.h"


int main() {
    std::cout << "CPU: " << getCpuName() << std::endl;

    std::vector<std::string> gpus = getGpuNames();
    std::cout << "GPUs: " << std::endl;
    for (const auto &gpu : gpus) {
        std::cout << gpu << std::endl;
    }

    return 0;
}