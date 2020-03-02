.686
.mmx
.model flat,stdcall

include asmfuncs.inc

.data?
_64bit_data_buffer dq ?

.code
GetCpuVendorString proc
	xor eax,eax
	cpuid
	mov eax,offset cpuid_buffer
	mov [eax],ebx
	add eax,4
	mov [eax],edx
	add eax,4
	mov [eax],ecx
	mov eax,offset cpuid_buffer
	ret
GetCpuVendorString endp

MMX_emms proc
	emms
	ret
MMX_emms endp

MMX_movd_mm0_reg proc
	pop eax
	movd mm0,eax
	ret
MMX_movd_mm0_reg endp

MMX_movd_mm1_reg proc
	pop eax
	movd mm1,eax
	ret
MMX_movd_mm1_reg endp

MMX_movd_mm2_reg proc
	pop eax
	movd mm2,eax
	ret
MMX_movd_mm2_reg endp

MMX_movd_mm3_reg proc
	pop eax
	movd mm3,eax
	ret
MMX_movd_mm3_reg endp

MMX_movd_mm4_reg proc
	pop eax
	movd mm4,eax
	ret
MMX_movd_mm4_reg endp

MMX_movd_mm5_reg proc
	pop eax
	movd mm5,eax
	ret
MMX_movd_mm5_reg endp

MMX_movd_mm6_reg proc
	pop eax
	movd mm6,eax
	ret
MMX_movd_mm6_reg endp

MMX_movd_mm7_reg proc
	pop eax
	movd mm7,eax
	ret
MMX_movd_mm7_reg endp

MMX_movd_mm0_var proc
	pop ebx
	movd dword ptr [ebx],mm0
	ret
MMX_movd_mm0_var endp

MMX_movd_mm1_var proc
	pop ebx
	movd dword ptr [ebx],mm1
	ret
MMX_movd_mm1_var endp

MMX_movd_mm2_var proc
	pop ebx
	movd dword ptr [ebx],mm2
	ret
MMX_movd_mm2_var endp

MMX_movd_mm3_var proc
	pop ebx
	movd dword ptr [ebx],mm3
	ret
MMX_movd_mm3_var endp

MMX_movd_mm4_var proc
	pop ebx
	movd dword ptr [ebx],mm4
	ret
MMX_movd_mm4_var endp

MMX_movd_mm5_var proc
	pop ebx
	movd dword ptr [ebx],mm5
	ret
MMX_movd_mm5_var endp

MMX_movd_mm6_var proc
	pop ebx
	movd dword ptr [ebx],mm6
	ret
MMX_movd_mm6_var endp

MMX_movd_mm7_var proc
	pop ebx
	movd dword ptr [ebx],mm7
	ret
MMX_movd_mm7_var endp

end