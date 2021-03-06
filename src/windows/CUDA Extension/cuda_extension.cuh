#ifndef _CUDA_EXTENSION_H_
#define _CUDA_EXTENSION_H_
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
	INIT_SUCCESSFULLY=0,
	NO_DEVICE,
	GET_DEVICE_PROPERTIES_FAILED,
	NO_DEVICE_SUPPORTED_LOWEST_VERSION_CUDA,
	SET_DEVICE_FAILED
}INIT_CUDA_RETURN_VALUES;

#ifdef __cplusplus
extern "C" {
#endif

DLLAPI __global__ INIT_CUDA_RETURN_VALUES InitializationCuda();
DLLAPI __device__ void CudaAddByte(__global__ char* dest, unsigned short count, ...);
DLLAPI __device__ void CudaAddWord(__global__ short* dest, unsigned short count, ...);
DLLAPI __device__ void CudaAddDword(__global__ int* dest, unsigned short count, ...);
DLLAPI __device__ void CudaAddQword(__global__ long long* dest, unsigned short count, ...);
DLLAPI __device__ void CudaAddFloat(__global__ float* dest, unsigned short count, ...);
DLLAPI __device__ void CudaAddDouble(__global__ double* dest, unsigned short count, ...);
DLLAPI __device__ void CudaAddLongDouble(__global__ long double* dest, unsigned short count, ...);
DLLAPI __device__ void CudaAddByteList(__global__ char* dest, unsigned short count, __global__ char* lst);
DLLAPI __device__ void CudaAddWordList(__global__ short* dest, unsigned short count, __global__ short* lst);
DLLAPI __device__ void CudaAddDwordList(__global__ int* dest, unsigned short count, __global__ int* lst);
DLLAPI __device__ void CudaAddQwordList(__global__ long long* dest, unsigned short count, __global__ long long* lst);
DLLAPI __device__ void CudaAddFloatList(__global__ float* dest, unsigned short count, __global__ float* lst);
DLLAPI __device__ void CudaAddDoubleList(__global__ double* dest, unsigned short count, __global__ double* lst);
DLLAPI __device__ void CudaAddLongDoubleList(__global__ long double* dest, unsigned short count, __global__ long double* lst);
DLLAPI __device__ void CudaSubtractByte(__global__ char* dest, unsigned short count, ...);
DLLAPI __device__ void CudaSubtractWord(__global__ short* dest, unsigned short count, ...);
DLLAPI __device__ void CudaSubtractDword(__global__ int* dest, unsigned short count, ...);
DLLAPI __device__ void CudaSubtractQword(__global__ long long* dest, unsigned short count, ...);
DLLAPI __device__ void CudaSubtractByteList(__global__ char* dest, unsigned short count, __global__ char* lst);
DLLAPI __device__ void CudaSubtractWordList(__global__ short* dest, unsigned short count, __global__ short* lst);
DLLAPI __device__ void CudaSubtractDwordList(__global__ int* dest, unsigned short count, __global__ int* lst);
DLLAPI __device__ void CudaSubtractQwordList(__global__ long long* dest, unsigned short count, __global__ long long*lst);
DLLAPI __device__ void CudaSubtractFloatList(__global__ float* dest, unsigned short count, __global__ float* lst);
DLLAPI __device__ void CudaSubtractDoubleList(__global__ double* dest, unsigned short count, __global__ double* lst);
DLLAPI __device__ void CudaSubtractLongDoubleList(__global__ long double* dest, unsigned short count, __global__ long double* lst);
DLLAPI __device__ void CudaMultiplyByte(__global__ char* dest, unsigned short count, ...);
DLLAPI __device__ void CudaMultiplyWord(__global__ short* dest, unsigned short count, ...);
DLLAPI __device__ void CudaMultiplyDword(__global__ int* dest, unsigned short count, ...);
DLLAPI __device__ void CudaMultiplyQword(__global__ long long* dest, unsigned short count, ...);
DLLAPI __device__ void CudaMultiplyByteList(__global__ char* dest, unsigned short count, __global__ char* lst);
DLLAPI __device__ void CudaMultiplyWordList(__global__ short* dest, unsigned short count, __global__ short* lst);
DLLAPI __device__ void CudaMultiplyDwordList(__global__ int* dest, unsigned short count, __global__ int* lst);
DLLAPI __device__ void CudaMultiplyQwordList(__global__ long long* dest, unsigned short count, __global__ long long* lst);
DLLAPI __device__ void CudaMultiplyFloatList(__global__ float* dest, unsigned short count, __global__ float* lst);
DLLAPI __device__ void CudaMultiplyDoubleList(__global__ double* dest, unsigned short count, __global__ double* lst);
DLLAPI __device__ void CudaMultiplyLongDoubleList(__global__ long double* dest, unsigned short count, __global__ long double* lst);
DLLAPI __device__ void CudaDivideByte(__global__ char* dest, unsigned short count, ...);
DLLAPI __device__ void CudaDivideWord(__global__ short* dest, unsigned short count, ...);
DLLAPI __device__ void CudaDivideDword(__global__ int* dest, unsigned short count, ...);
DLLAPI __device__ void CudaDivideQword(__global__ long long* dest, unsigned short count, ...);
DLLAPI __device__ void CudaDivideByteList(__global__ char* dest, unsigned short count, __global__ char* lst);
DLLAPI __device__ void CudaDivideWordList(__global__ short* dest, unsigned short count, __global__ short* lst);
DLLAPI __device__ void CudaDivideDwordList(__global__ int* dest, unsigned short count, __global__ int* lst);
DLLAPI __device__ void CudaDivideQwordList(__global__ long long* dest, unsigned short count, __global__ long long* lst);
DLLAPI __device__ void CudaDivideFloatList(__global__ float* dest, unsigned short count, __global__ float* lst);
DLLAPI __device__ void CudaDivideDoubleList(__global__ double* dest, unsigned short count, __global__ double* lst);
DLLAPI __device__ void CudaDivideLongDoubleList(__global__ long double* dest, unsigned short count, __global__ long double* lst);
DLLAPI __device__ void CudaMatrixByte(__global__ char* dest);
DLLAPI __device__ void CudaMatrixWord(__global__ short* dest);
DLLAPI __device__ void CudaMatrixDword(__global__ int* dest);
DLLAPI __device__ void CudaMatrixQword(__global__ long long* dest);
DLLAPI __device__ void CudaCubeByte(__global__ char* dest);
DLLAPI __device__ void CudaCubeWord(__global__ short* dest);
DLLAPI __device__ void CudaCubeDword(__global__ int* dest);
DLLAPI __device__ void CudaCubeQword(__global__ long long* dest);
DLLAPI __device__ void CudaAddFloat(__global__ float* dest, unsigned short count, ...);
DLLAPI __device__ void CudaAddDouble(__global__ double* dest, unsigned short count, ...);
DLLAPI __device__ void CudaAddLongDouble(__global__ long double* dest, unsigned short count, ...);
DLLAPI __device__ void CudaSubtractLongDouble(__global__ long double* dest, unsigned short count, ...);
DLLAPI __device__ void CudaSubtractDouble(__global__ double* dest, unsigned short count, ...);
DLLAPI __device__ void CudaSubtractFloat(__global__ float* dest, unsigned short count, ...);
DLLAPI __device__ void CudaMultiplyFloat(__global__ float* dest, unsigned short count, ...);
DLLAPI __device__ void CudaMultiplyDouble(__global__ double* dest, unsigned short count, ...);
DLLAPI __device__ void CudaMultiplyLongDouble(__global__ long double* dest, unsigned short count, ...);
DLLAPI __device__ void CudaDivideFloat(__global__ float* dest, unsigned short count, ...);
DLLAPI __device__ void CudaDivideDouble(__global__ double* dest, unsigned short count, ...);
DLLAPI __device__ void CudaDivideLongDouble(__global__ long double* dest, unsigned short count, ...);
DLLAPI __device__ void CudaMatrixFloat(__global__ float* dest);
DLLAPI __device__ void CudaMatrixDouble(__global__ double* dest);
DLLAPI __device__ void CudaMatrixLongDouble(__global__ long double* dest);
DLLAPI __device__ void CudaCubeFloat(__global__ float* dest);
DLLAPI __device__ void CudaCubeDouble(__global__ double* dest);
DLLAPI __device__ void CudaCubeLongDouble(__global__ long double* dest);
DLLAPI __device__ void CudaPowerFloat(__global__ float* dest, unsigned int t);
DLLAPI __device__ void CudaPowerDouble(__global__ double* dest, unsigned int t);
DLLAPI __device__ void CudaPowerLongDouble(__global__ long double* dest, unsigned int t);
DLLAPI __device__ void CudaPowerByte(__global__ char* dest, unsigned int t);
DLLAPI __device__ void CudaPowerWord(__global__ short* dest, unsigned int t);
DLLAPI __device__ void CudaPowerDword(__global__ int* dest, unsigned int t);
DLLAPI __device__ void CudaPowerQword(__global__ long long* dest, unsigned int t);

#ifdef __cplusplus
}
#endif

#endif