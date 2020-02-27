option casemap:none
includelib ucrt.lib
includelib legacy_stdio_definitions.lib

.data
cpuid_buffer db 13 dup(0)

.code
public GetCpuVendorString
public MMX_movd_reg
public MMX_movd_var
public MMX_movq_reg
public MMX_movq_var
public MMX_emms