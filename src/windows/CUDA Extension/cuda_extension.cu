#define DLL
#include "cuda_extension.cuh"
using namespace std;

int SelectedCudaDeviceId;

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
	bool device_select_successfully;
	for (int i = 0; i < cuda_device_count; i++)
	{
		cudaDeviceProp current_device_properties;
		if (cudaGetDeviceProperties(&current_device_properties, i) != cudaSuccess)
			return GET_DEVICE_PROPERTIES_FAILED;
		else
			if (current_device_properties.major > 3)
				if (!SetCudaDevice(i))
					return SET_DEVICE_FAILED;
				else
				{
					device_select_successfully = true;
					SelectedCudaDeviceId = i;
					break;
				}
	}
	if (!device_select_successfully)
		return NO_DEVICE_SUPPORTED_LOWEST_VERSION_CUDA;
	return INIT_SUCCESSFULLY;
}

DLLAPI __device__ void CudaAddByte(__global__ char* dest, unsigned short count, ...)
{
	va_list args;
	va_start(args, count);
	__device__ char result = 0;
	for (unsigned short i = 0; i < count; i++)
		result += va_arg(args, char);
	*dest = result;
}

DLLAPI __device__ void CudaAddWord(__global__ short* dest, unsigned short count, ...)
{
	va_list args;
	va_start(args, count);
	__device__ short result = 0;
	for (unsigned short i = 0; i < count; i++)
		result += va_arg(args, short);
	*dest = result;
}

DLLAPI __device__ void CudaAddDword(__global__ int* dest, unsigned short count, ...)
{
	va_list args;
	va_start(args, count);
	__device__ int result = 0;
	for (unsigned short i = 0; i < count; i++)
		result += va_arg(args, int);
	*dest = result;
}

DLLAPI __device__ void CudaAddQword(__global__ long long* dest, unsigned short count, ...)
{
	va_list args;
	va_start(args, count);
	__device__ long long result = 0;
	for (unsigned short i = 0; i < count; i++)
		result += va_arg(args, long long);
	*dest = result;
}

DLLAPI __device__ void CudaAddFloat(__global__ float* dest, unsigned short count, ...)
{
	va_list args;
	va_start(args, count);
	__device__ float result = 0;
	for (unsigned short i = 0; i < count; i++)
		result += va_arg(args, float);
	*dest = result;
}

DLLAPI __device__ void CudaAddDouble(__global__ double* dest, unsigned short count, ...)
{
	va_list args;
	va_start(args, count);
	__device__ double result = 0;
	for (unsigned short i = 0; i < count; i++)
		result += va_arg(args, double);
	*dest = result;
}

DLLAPI __device__ void CudaAddLongDouble(__global__ long double* dest, unsigned short count, ...)
{
	va_list args;
	va_start(args, count);
	__device__ long double result = 0;
	for (unsigned short i = 0; i < count; i++)
		result += va_arg(args, long double);
	*dest = result;
}

DLLAPI __device__ void CudaAddByteList(__global__ char* dest, unsigned short count, __global__ char* lst)
{
	__device__ char result = 0;
	for (__device__ unsigned short i = 0; i < count; i++)
		result += lst[i];
	*dest = result;
}

DLLAPI __device__ void CudaAddWordList(__global__ short* dest, unsigned short count, __global__ short* lst)
{
	__device__ short result = 0;
	for (__device__ short i = 0; i < count; i++)
		result += lst[i];
	*dest = result;
}

DLLAPI __device__ void CudaAddDwordList(__global__ int* dest, unsigned short count, __global__ int* lst)
{
	__device__ int result = 0;
	for (__device__ short i = 0; i < count; i++)
		result += lst[i];
	*dest = result;
}

DLLAPI __device__ void CudaAddQwordList(__global__ long long* dest, unsigned short count, __global__ long long* lst)
{
	__device__ long long result = 0;
	for (__device__ short i = 0; i < count; i++)
		result += lst[i];
	*dest = result;
}

DLLAPI __device__ void CudaAddFloatList(__global__ float* dest, unsigned short count, __global__ float* lst)
{
	__device__ float result = 0;
	for (__device__ short i = 0; i < count; i++)
		result += lst[i];
	*dest = result;
}

DLLAPI __device__ void CudaAddDoubleList(__global__ double* dest, unsigned short count, __global__ double* lst)
{
	__device__ double result = 0;
	for (__device__ short i = 0; i < count; i++)
		result += lst[i];
	*dest = result;
}

DLLAPI __device__ void CudaAddLongDoubleList(__global__ long double* dest, unsigned short count, __global__ long double* lst)
{
	__device__ long double result = 0;
	for (__device__ short i = 0; i < count; i++)
		result += lst[i];
	*dest = result;
}

DLLAPI __device__ void CudaSubtractByte(__global__ char* dest, unsigned short count, ...)
{
	va_list args;
	va_start(args, count);
	__device__ char result = *dest;
	for (unsigned short i = 0; i < count; i++)
		result -= va_arg(args, char);
	*dest = result;
}

DLLAPI __device__ void CudaSubtractWord(__global__ short* dest, unsigned short count, ...)
{
	va_list args;
	va_start(args, count);
	__device__ short result = *dest;
	for (unsigned short i = 0; i < count; i++)
		result -= va_arg(args, short);
	*dest = result;
}

DLLAPI __device__ void CudaSubtractDword(__global__ int* dest, unsigned short count, ...)
{
	va_list args;
	va_start(args, count);
	__device__ int result = *dest;
	for (unsigned short i = 0; i < count; i++)
		result -= va_arg(args, int);
	*dest = result;
}

DLLAPI __device__ void CudaSubtractQword(__global__ long long* dest, unsigned short count, ...)
{
	va_list args;
	va_start(args, count);
	__device__ long long result = *dest;
	for (unsigned short i = 0; i < count; i++)
		result -= va_arg(args, long long);
	*dest = result;
}

DLLAPI __device__ void CudaSubtractLongDouble(__global__ long double* dest, unsigned short count, ...)
{
	va_list args;
	va_start(args, count);
	__device__ long double result = *dest;
	for (unsigned short i = 0; i < count; i++)
		result -= va_arg(args, long double);
	*dest = result;
}

DLLAPI __device__ void CudaSubtractDouble(__global__ double* dest, unsigned short count, ...)
{
	va_list args;
	va_start(args, count);
	__device__ double result = *dest;
	for (unsigned short i = 0; i < count; i++)
		result -= va_arg(args, double);
	*dest = result;
}

DLLAPI __device__ void CudaSubtractFloat(__global__ float* dest, unsigned short count, ...)
{
	va_list args;
	va_start(args, count);
	__device__ float result = *dest;
	for (unsigned short i = 0; i < count; i++)
		result -= va_arg(args, float);
	*dest = result;
}


DLLAPI __device__ void CudaSubtractByteList(__global__ char* dest, unsigned short count, __global__ char* lst)
{
	__device__ char result = *dest;
	for (__device__ short i = 0; i < count; i++)
		result -= lst[i];
	*dest = result;
}

DLLAPI __device__ void CudaSubtractWordList(__global__ short* dest, unsigned short count, __global__ short* lst)
{
	__device__ short result = *dest;
	for (__device__ short i = 0; i < count; i++)
		result -= lst[i];
	*dest = result;
}

DLLAPI __device__ void CudaSubtractDwordList(__global__ int* dest, unsigned short count, __global__ int* lst)
{
	__device__ int result = *dest;
	for (__device__ short i = 0; i < count; i++)
		result -= lst[i];
	*dest = result;
}

DLLAPI __device__ void CudaSubtractQwordList(__global__ long long* dest, unsigned short count, __global__ long long* lst)
{
	__device__ long long result = *dest;
	for (__device__ short i = 0; i < count; i++)
		result -= lst[i];
	*dest = result;
}

DLLAPI __device__ void CudaSubtractFloatList(__global__ float* dest, unsigned short count, __global__ float* lst)
{
	__device__ float result = *dest;
	for (__device__ short i = 0; i < count; i++)
		result -= lst[i];
	*dest = result;
}

DLLAPI __device__ void CudaSubtractDoubleList(__global__ double* dest, unsigned short count, __global__ double* lst)
{
	__device__ double result = *dest;
	for (__device__ short i = 0; i < count; i++)
		result -= lst[i];
	*dest = result;
}

DLLAPI __device__ void CudaSubtractLongDoubleList(__global__ long double* dest, unsigned short count, __global__ long double* lst)
{
	__device__ long double result = *dest;
	for (__device__ short i = 0; i < count; i++)
		result -= lst[i];
	*dest = result;
}

DLLAPI __device__ void CudaMultiplyByte(__global__ char* dest, unsigned short count, ...)
{
	va_list args;
	va_start(args, count);
	__device__ char result = 0;
	for (unsigned short i = 0; i < count; i++)
		result *= va_arg(args, char);
	*dest = result;
}

DLLAPI __device__ void CudaMultiplyWord(__global__ short* dest, unsigned short count, ...)
{
	va_list args;
	va_start(args, count);
	__device__ short result = 0;
	for (unsigned short i = 0; i < count; i++)
		result *= va_arg(args, short);
	*dest = result;
}

DLLAPI __device__ void CudaMultiplyDword(__global__ int* dest, unsigned short count, ...)
{
	va_list args;
	va_start(args, count);
	__device__ int result = 0;
	for (unsigned short i = 0; i < count; i++)
		result *= va_arg(args, int);
	*dest = result;
}

DLLAPI __device__ void CudaMultiplyQword(__global__ long long* dest, unsigned short count, ...)
{
	va_list args;
	va_start(args, count);
	__device__ long long result = 0;
	for (unsigned short i = 0; i < count; i++)
		result *= va_arg(args, long long);
	*dest = result;
}

DLLAPI __device__ void CudaMultiplyFloat(__global__ float* dest, unsigned short count, ...)
{
	va_list args;
	va_start(args, count);
	__device__ float result = 0;
	for (unsigned short i = 0; i < count; i++)
		result *= va_arg(args, float);
	*dest = result;
}

DLLAPI __device__ void CudaMultiplyDouble(__global__ double* dest, unsigned short count, ...)
{
	va_list args;
	va_start(args, count);
	__device__ double result = 0;
	for (unsigned short i = 0; i < count; i++)
		result *= va_arg(args, double);
	*dest = result;
}

DLLAPI __device__ void CudaMultiplyLongDouble(__global__ long double* dest, unsigned short count, ...)
{
	va_list args;
	va_start(args, count);
	__device__ long double result = 0;
	for (unsigned short i = 0; i < count; i++)
		result *= va_arg(args, long double);
	*dest = result;
}


DLLAPI __device__ void CudaMultiplyByteList(__global__ char* dest, unsigned short count, __global__ char* lst)
{
	__device__ char result = lst[0];
	for (__device__ unsigned short i = 1; i < count; i++)
		result *= lst[i];
	*dest = result;
}

DLLAPI __device__ void CudaMultiplyWordList(__global__ short* dest, unsigned short count, __global__ short* lst)
{
	__device__ short result = lst[0];
	for (__device__ unsigned short i = 1; i < count; i++)
		result *= lst[i];
	*dest = result;
}

DLLAPI __device__ void CudaMultiplyDwordList(__global__ int* dest, unsigned short count, __global__ int* lst)
{
	__device__ int result = lst[0];
	for (__device__ unsigned short i = 1; i < count; i++)
		result *= lst[i];
	*dest = result;
}

DLLAPI __device__ void CudaMultiplyQwordList(__global__ long long* dest, unsigned short count, __global__ long long* lst)
{
	__device__ long long result = lst[0];
	for (__device__ unsigned short i = 1; i < count; i++)
		result *= lst[i];
	*dest = result;
}

DLLAPI __device__ void CudaMultiplyFloatList(__global__ float* dest, unsigned short count, __global__ float* lst)
{
	__device__ float result = lst[0];
	for (__device__ unsigned short i = 1; i < count; i++)
		result *= lst[i];
	*dest = result;
}

DLLAPI __device__ void CudaMultiplyDoubleList(__global__ double* dest, unsigned short count, __global__ double* lst)
{
	__device__ double result = lst[0];
	for (__device__ unsigned short i = 1; i < count; i++)
		result *= lst[i];
	*dest = result;
}

DLLAPI __device__ void CudaMultiplyLongDoubleList(__global__ long double* dest, unsigned short count, __global__ long double* lst)
{
	__device__ long double result = lst[0];
	for (__device__ unsigned short i = 1; i < count; i++)
		result *= lst[i];
	*dest = result;
}

DLLAPI __device__ void CudaDivideByte(__global__ char* dest, unsigned short count, ...)
{
	va_list args;
	va_start(args, count);
	__device__ char result = *dest;
	for (unsigned short i = 0; i < count; i++)
		result /= va_arg(args, char);
	*dest = result;
}

DLLAPI __device__ void CudaDivideWord(__global__ short* dest, unsigned short count, ...)
{
	va_list args;
	va_start(args, count);
	__device__ short result = *dest;
	for (unsigned short i = 0; i < count; i++)
		result /= va_arg(args, short);
	*dest = result;
}

DLLAPI __device__ void CudaDivideDword(__global__ int* dest, unsigned short count, ...)
{
	va_list args;
	va_start(args, count);
	__device__ int result = *dest;
	for (unsigned short i = 0; i < count; i++)
		result /= va_arg(args, int);
	*dest = result;
}

DLLAPI __device__ void CudaDivideQword(__global__ long long* dest, unsigned short count, ...)
{
	va_list args;
	va_start(args, count);
	__device__ long long result = *dest;
	for (unsigned short i = 0; i < count; i++)
		result /= va_arg(args, long long);
	*dest = result;
}

DLLAPI __device__ void CudaDivideFloat(__global__ float* dest, unsigned short count, ...)
{
	va_list args;
	va_start(args, count);
	__device__ float result = *dest;
	for (unsigned short i = 0; i < count; i++)
		result /= va_arg(args, float);
	*dest = result;
}

DLLAPI __device__ void CudaDivideDouble(__global__ double* dest, unsigned short count, ...)
{
	va_list args;
	va_start(args, count);
	__device__ double result = *dest;
	for (unsigned short i = 0; i < count; i++)
		result /= va_arg(args, double);
	*dest = result;
}

DLLAPI __device__ void CudaDivideLongDouble(__global__ long double* dest, unsigned short count, ...)
{
	va_list args;
	va_start(args, count);
	__device__ long double result = *dest;
	for (unsigned short i = 0; i < count; i++)
		result /= va_arg(args, long double);
	*dest = result;
}

DLLAPI __device__ void CudaDivideByteList(__global__ char* dest, unsigned short count, __global__ char* lst)
{
	__device__ char result = *dest;
	for (__device__ unsigned short i = 0; i < count; i++)
		result *= lst[i];
	*dest = result;
}

DLLAPI __device__ void CudaDivideWordList(__global__ short* dest, unsigned short count, __global__ short* lst)
{
	__device__ short result = *dest;
	for (__device__ unsigned short i = 0; i < count; i++)
		result *= lst[i];
	*dest = result;
}

DLLAPI __device__ void CudaDivideDwordList(__global__ int* dest, unsigned short count, __global__ int* lst)
{
	__device__ int result = *dest;
	for (__device__ unsigned short i = 0; i < count; i++)
		result *= lst[i];
	*dest = result;
}

DLLAPI __device__ void CudaDivideQwordList(__global__ long long* dest, unsigned short count, __global__ long long* lst)
{
	__device__ long long result = *dest;
	for (__device__ unsigned short i = 0; i < count; i++)
		result *= lst[i];
	*dest = result;
}

DLLAPI __device__ void CudaDivideFloatList(__global__ float* dest, unsigned short count, __global__ float* lst)
{
	__device__ float result = *dest;
	for (__device__ unsigned short i = 0; i < count; i++)
		result *= lst[i];
	*dest = result;
}

DLLAPI __device__ void CudaDivideDoubleList(__global__ double* dest, unsigned short count, __global__ double* lst)
{
	__device__ double result = *dest;
	for (__device__ unsigned short i = 0; i < count; i++)
		result *= lst[i];
	*dest = result;
}

DLLAPI __device__ void CudaDivideLongDoubleList(__global__ long double* dest, unsigned short count, __global__ long double* lst)
{
	__device__ long double result = *dest;
	for (__device__ unsigned short i = 0; i < count; i++)
		result *= lst[i];
	*dest = result;
}

DLLAPI __device__ void CudaMatrixByte(__global__ char* dest)
{
	*dest *= *dest;
}

DLLAPI __device__ void CudaMatrixWord(__global__ short* dest)
{
	*dest *= *dest;
}

DLLAPI __device__ void CudaMatrixDword(__global__ int* dest)
{
	*dest *= *dest;
}

DLLAPI __device__ void CudaMatrixQword(__global__ long long* dest)
{
	*dest *= *dest;
}

DLLAPI __device__ void CudaMatrixFloat(__global__ float* dest)
{
	*dest *= *dest;
}

DLLAPI __device__ void CudaMatrixDouble(__global__ double* dest)
{
	*dest *= *dest;
}

DLLAPI __device__ void CudaMatrixLongDouble(__global__ long double* dest)
{
	*dest *= *dest;
}

DLLAPI __device__ void CudaCubeByte(__global__ char* dest)
{
	*dest *= (*dest) * (*dest);
}

DLLAPI __device__ void CudaCubeWord(__global__ short* dest)
{
	*dest *= (*dest) * (*dest);
}

DLLAPI __device__ void CudaCubeDword(__global__ int* dest)
{
	*dest *= (*dest) * (*dest);
}

DLLAPI __device__ void CudaCubeQword(__global__ long long* dest)
{
	*dest *= (*dest) * (*dest);
}

DLLAPI __device__ void CudaCubeFloat(__global__ float* dest)
{
	*dest *= (*dest) * (*dest);
}

DLLAPI __device__ void CudaCubeDouble(__global__ double* dest)
{
	*dest *= (*dest) * (*dest);
}

DLLAPI __device__ void CudaCubeLongDouble(__global__ long double* dest)
{
	*dest *= (*dest) * (*dest);
}

DLLAPI __device__ void CudaPowerByte(__global__ char* dest, unsigned int t)
{
	for (unsigned int i = 0; i < t; i++)
		*dest *= *dest;
}

DLLAPI __device__ void CudaPowerWord(__global__ short* dest, unsigned int t)
{
	for (unsigned int i = 0; i < t; i++)
		*dest *= *dest;
}

DLLAPI __device__ void CudaPowerDword(__global__ int* dest, unsigned int t)
{
	for (unsigned int i = 0; i < t; i++)
		*dest *= *dest;
}

DLLAPI __device__ void CudaPowerQword(__global__ long long* dest, unsigned int t)
{
	for (unsigned int i = 0; i < t; i++)
		*dest *= *dest;
}

DLLAPI __device__ void CudaPowerFloat(__global__ float* dest, unsigned int t)
{
	for (unsigned int i = 0; i < t; i++)
		*dest *= *dest;
}

DLLAPI __device__ void CudaPowerDouble(__global__ double* dest, unsigned int t)
{
	for (unsigned int i = 0; i < t; i++)
		*dest *= *dest;
}

DLLAPI __device__ void CudaPowerLongDouble(__global__ long double* dest, unsigned int t)
{
	for (unsigned int i = 0; i < t; i++)
		*dest *= *dest;
}

DLLAPI __device__ void CudaSquareRootQword(__global__ long long *dest)
{

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