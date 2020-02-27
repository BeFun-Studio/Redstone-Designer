#pragma once
#include <Windows.h>
#include <cuda_runtime.h>
#include <stdarg.h>
#include <stdbool.h>

#ifndef DLLAPI
#ifdef DLL
#define DLLAPI __declspec(dllexport)
#else
#define DLLAPI __declspec(dllexport)
#endif
#endif

enum INIT_CUDA_RETURN_VALUES
{
	NO_DEVICE=1,
	GET_DEVICE_PROPERTIES_FAILED,
	NO_DEVICE_SUPPORTED_LOWEST_VERSION_CUDA,
	SET_DEVICE_FAILED
};

#ifdef __cplusplus
extern "C" {
#endif
DLLAPI __global__ INIT_CUDA_RETURN_VALUES InitializationCuda();
DLLAPI __global__ long long CudaAdd(unsigned short count, ...);
DLLAPI __global__ long long CudaSubtract(unsigned short count, long long original_num, ...);
DLLAPI __global__ long long CudaMultiply(unsigned short count, ...);
#ifdef __cplusplus
}
#endif