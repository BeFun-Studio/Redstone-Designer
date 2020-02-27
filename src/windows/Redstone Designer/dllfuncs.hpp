#pragma once
#include <Windows.h>

enum INIT_CUDA_RETURN_VALUES
{
	NO_DEVICE = 1,
	GET_DEVICE_PROPERTIES_FAILED,
	NO_DEVICE_SUPPORTED_LOWEST_VERSION_CUDA,
	SET_DEVICE_FAILED
};

typedef INIT_CUDA_RETURN_VALUES(*InitializationCuda_PROC)();
typedef long long (*CudaAdd_PROC)(unsigned short, ...);
typedef long long (*CudaSubtract_PROC)(unsigned short, long long, ...);
typedef long long (*CudaMultiply_PROC)(unsigned short, ...);

InitializationCuda_PROC InitializationCuda;
CudaAdd_PROC CudaAdd;
CudaSubtract_PROC CudaSubtract;
CudaMultiply_PROC CudaMultiply;

HMODULE CudaExtension;

bool LoadDllFunctions()
{
	if ((CudaExtension = LoadLibrary(L"cuda_extension.dll")) == NULL)
		return false;
	InitializationCuda = (InitializationCuda_PROC)GetProcAddress(CudaExtension, "InitializationCuda");
	if (InitializationCuda == NULL)
		return false;
	CudaAdd = (CudaAdd_PROC)GetProcAddress(CudaExtension, "CudaAdd");
	if (CudaAdd == NULL)
		return false;
	CudaSubtract = (CudaSubtract_PROC)GetProcAddress(CudaExtension, "CudaSubtract");
	if (CudaSubtract == NULL)
		return false;
	CudaMultiply = (CudaMultiply_PROC)GetProcAddress(CudaExtension, "CudaMultiply");
	if (CudaMultiply == NULL)
		return false;
	return true;
}