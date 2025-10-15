#include "../include/SystemInfo.h"
#include <array>
#include <string>
#include <cstring>
#include <intrin.h>
#include <iostream>
#include <ostream>
#include <cuda_runtime.h>
#include <vector>

std::string getCpuName() {
    int cpuInfo[4] = { -1 };
    std::array<char, 0x40> cpuBrand = {};

    __cpuid(cpuInfo, 0x80000000);

    if (const unsigned int nExIds = cpuInfo[0]; nExIds >= 0x80000004) {
        __cpuid(cpuInfo, 0x80000002);
        memcpy(cpuBrand.data(), cpuInfo, sizeof(cpuInfo));
        __cpuid(cpuInfo, 0x80000003);
        memcpy(cpuBrand.data() + 16, cpuInfo, sizeof(cpuInfo));
        __cpuid(cpuInfo, 0x80000004);
        memcpy(cpuBrand.data() + 32, cpuInfo, sizeof(cpuInfo));
    }
    return std::string(cpuBrand.data());
}


std::vector<std::string> getGpuNames() {
    int deviceCount;
    std::vector<std::string> devices;

    if (cudaError_t error = cudaGetDeviceCount(&deviceCount); error != cudaSuccess) {
        std::cout << "Error: " << error << std::endl;
        return devices;
    }

    for (int i = 0; i < deviceCount; ++i) {
        cudaDeviceProp prop;
        cudaGetDeviceProperties(&prop, i);

        std::string name = prop.name;
        devices.push_back(name);
    }

    return devices;
}
