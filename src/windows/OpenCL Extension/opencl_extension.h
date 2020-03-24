#ifndef _OPENCL_EXTENSION_H_
#define _OPENCL_EXTENSION_H_

#include <Windows.h>
#include <CL/cl.h>
#include <stdbool.h>

#ifndef DLLAPI
#ifdef DLL
#define DLLAPI __declspec(dllexport)
#else
#define DLLAPI __declspec(dllimport)
#endif
#endif

DLLAPI void OpenCLAdd(unsigned short count, ...);

#endif