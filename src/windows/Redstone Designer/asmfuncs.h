#pragma once
enum MMX_REGISTERS
{
	MM0=0,
	MM1,
	MM2,
	MM3,
	MM4,
	MM5,
	MM6,
	MM7
};
extern "C" char* __stdcall GetCpuVendorString();
extern "C" bool __stdcall MMX_movd_reg(MMX_REGISTERS, int);
extern "C" bool __stdcall MMX_movd_var(MMX_REGISTERS, int*);
extern "C" bool __stdcall MMX_movq_reg(MMX_REGISTERS, long long);
extern "C" bool __stdcall MMX_movq_var(MMX_REGISTERS, long long*);
extern "C" void __stdcall MMX_emms();