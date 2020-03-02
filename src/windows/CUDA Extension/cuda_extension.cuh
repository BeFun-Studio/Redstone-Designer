#pragma once
#include <Windows.h>
#include <cuda_runtime.h>
#include <stdarg.h>
#include <stdbool.h>

#ifndef DLLAPI
#ifdef DLL
#define DLLAPI __declspec(dllexport)
#else
#define DLLAPI __declspec(dllimport)
#endif
#endif

typedef enum
{
	INIT_SUCCESSFULLY,
	NO_DEVICE,
	GET_DEVICE_PROPERTIES_FAILED,
	NO_DEVICE_SUPPORTED_LOWEST_VERSION_CUDA,
	SET_DEVICE_FAILED
}INIT_CUDA_RETURN_VALUES;

#ifdef __cplusplus
extern "C" {
#endif

DLLAPI __global__ bool SetCudaDevice(int device_id);
DLLAPI __global__ INIT_CUDA_RETURN_VALUES InitializationCuda();
DLLAPI __global__ long long CudaAdd(unsigned short count, ...);
DLLAPI __global__ long long CudaSubtract(unsigned short count, long long original_num, ...);
DLLAPI __global__ long long CudaMultiply(unsigned short count, ...);
DLLAPI __global__ long long CudaDivide(unsigned short count, long long original_num, ...);

#ifdef __cplusplus
}
#endif