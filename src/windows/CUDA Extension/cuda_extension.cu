#define DLL
#include "cuda_extension.cuh"
using namespace std;

DLLAPI __global__ bool SetCudaDevice(int device_id)
{
	if (cudaSetDevice(device_id) == cudaErrorInvalidDevice)
		return false;
	return true;
}

DLLAPI __global__ INIT_CUDA_RETURN_VALUES InitializationCuda()
{
	int cuda_device_count;
	cudaGetDeviceCount(&cuda_device_count);
	if (cuda_device_count == 0)
		return NO_DEVICE;
	int j = 0;
	for (int i = 0; i < cuda_device_count; i++)
	{
		cudaDeviceProp current_device_properties;
		if (cudaGetDeviceProperties(&current_device_properties, i) != cudaSuccess)
			return GET_DEVICE_PROPERTIES_FAILED;
		else
			if (current_device_properties.major > 3)
				if (!SetCudaDevice(i))
					return SET_DEVICE_FAILED;
	}
	if ( j == 0)
		return NO_DEVICE_SUPPORTED_LOWEST_VERSION_CUDA;
	return INIT_SUCCESSFULLY;
}

DLLAPI __global__ long long CudaAdd(unsigned short count, ...)
{
	va_list args;
	va_start(args, count);
	long long result=0;
	for (unsigned short i = 0; i < count; i++)
		result += va_arg(args, long long);
	return result;
}

DLLAPI __global__ long long CudaSubtract(unsigned short count, long long original_num, ...)
{
	va_list args;
	va_start(args, count);
	long long result = original_num;
	for (unsigned short i = 0; i < count; i++)
		result -= va_arg(args, long long);
	return result;
}

DLLAPI __global__ long long CudaMultiply(unsigned short count, ...)
{
	va_list args;
	va_start(args, count);
	long long result = 0;
	for (unsigned short i = 0; i < count; i++)
		result *= va_arg(args, long long);
	return result;
}

DLLAPI __global__ long long CudaDivide(unsigned short count, long long original_num, ...)
{
	va_list args;
	va_start(args, count);
	long long result = original_num;
	for (unsigned short i = 0; i < count; i++)
		result /= va_arg(args, long long);
	return result;
}

INT APIENTRY DllMain(HMODULE hModule, DWORD fdwReason, LPVOID lpvReserved)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	}
}