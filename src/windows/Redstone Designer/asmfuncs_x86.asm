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

MMX_movd_reg proc
	pop ebx
	pop eax
	cmp eax,0
	je mov_mm0_movd_reg
	cmp eax,1
	je mov_mm1_movd_reg
	cmp eax,2
	je mov_mm2_movd_reg
	cmp eax,3
	je mov_mm3_movd_reg
	cmp eax,4
	je mov_mm4_movd_reg
	cmp eax,5
	je mov_mm5_movd_reg
	cmp eax,6
	je mov_mm6_movd_reg
	cmp eax,7
	je mov_mm7_movd_reg
	xor eax,eax
	ret
	mov_mm0_movd_reg:
	movd mm0,eax
	jmp mov_movd_reg_completed
	mov_mm1_movd_reg:
	movd mm1,eax
	jmp mov_movd_reg_completed
	mov_mm2_movd_reg:
	movd mm2,eax
	jmp mov_movd_reg_completed
	mov_mm3_movd_reg:
	movd mm3,eax
	jmp mov_movd_reg_completed
	mov_mm4_movd_reg:
	movd mm4,eax
	jmp mov_movd_reg_completed
	mov_mm5_movd_reg:
	movd mm5,eax
	jmp mov_movd_reg_completed
	mov_mm6_movd_reg:
	movd mm6,eax
	jmp mov_movd_reg_completed
	mov_mm7_movd_reg:
	movd mm7,eax
	mov_movd_reg_completed:
	or eax,eax
	ret
MMX_movd_reg endp

MMX_movd_var proc
	pop ebx
	pop eax
	cmp eax,0
	je mov_mm0_movd_var
	cmp eax,1
	je mov_mm1_movd_var
	cmp eax,2
	je mov_mm2_movd_var
	cmp eax,3
	je mov_mm3_movd_var
	cmp eax,4
	je mov_mm4_movd_var
	cmp eax,5
	je mov_mm5_movd_var
	cmp eax,6
	je mov_mm6_movd_var
	cmp eax,7
	je mov_mm7_movd_var
	xor eax,eax
	ret
	mov_mm0_movd_var:
	movd dword ptr [ebx],mm0
	jmp mov_movd_var_completed
	mov_mm1_movd_var:
	movd dword ptr [ebx],mm1
	jmp mov_movd_var_completed
	mov_mm2_movd_var:
	movd dword ptr [ebx],mm2
	jmp mov_movd_var_completed
	mov_mm3_movd_var:
	movd dword ptr [ebx],mm3
	jmp mov_movd_var_completed
	mov_mm4_movd_var:
	movd dword ptr [ebx],mm4
	jmp mov_movd_var_completed
	mov_mm5_movd_var:
	movd dword ptr [ebx],mm5
	jmp mov_movd_var_completed
	mov_mm6_movd_var:
	movd dword ptr [ebx],mm6
	jmp mov_movd_var_completed
	mov_mm7_movd_var:
	movd dword ptr [ebx],mm7
	mov_movd_var_completed:
	or eax,eax
	ret
MMX_movd_var endp

MMX_movq_reg proc
	pop eax
	pop ecx
	mov ebx,offset _64bit_data_buffer
	mov dword ptr [ebx],eax
	add ebx,4
	mov dword ptr [ebx],ecx
	pop eax
	cmp eax,0
	je mov_mm0_movq_reg
	cmp eax,1
	je mov_mm1_movq_reg
	cmp eax,2
	je mov_mm2_movq_reg
	cmp eax,3
	je mov_mm3_movq_reg
	cmp eax,4
	je mov_mm4_movq_reg
	cmp eax,5
	je mov_mm5_movq_reg
	cmp eax,6
	je mov_mm6_movq_reg
	cmp eax,7
	je mov_mm7_movq_reg
	xor eax,eax
	ret
	mov_mm0_movq_reg:
	movq mm0,_64bit_data_buffer
	jmp mov_movq_reg_completed
	mov_mm1_movq_reg:
	movq mm1,_64bit_data_buffer
	jmp mov_movq_reg_completed
	mov_mm2_movq_reg:
	movq mm2,_64bit_data_buffer
	jmp mov_movq_reg_completed
	mov_mm3_movq_reg:
	movq mm3,_64bit_data_buffer
	jmp mov_movq_reg_completed
	mov_mm4_movq_reg:
	movq mm4,_64bit_data_buffer
	jmp mov_movq_reg_completed
	mov_mm5_movq_reg:
	movq mm5,_64bit_data_buffer
	jmp mov_movq_reg_completed
	mov_mm6_movq_reg:
	movq mm6,_64bit_data_buffer
	jmp mov_movq_reg_completed
	mov_mm7_movq_reg:
	movq mm7,_64bit_data_buffer
	jmp mov_movq_reg_completed
	mov_movq_reg_completed:
	or eax,eax
	ret
MMX_movq_reg endp

MMX_movq_var proc
	pop eax
	pop ecx
	mov ebx,offset _64bit_data_buffer
	mov dword ptr [ebx],eax
	add ebx,4
	mov dword ptr [ebx],ecx
	pop eax
	cmp eax,0
	je mov_mm0_movq_var
	cmp eax,1
	je mov_mm1_movq_var
	cmp eax,2
	je mov_mm2_movq_var
	cmp eax,3
	je mov_mm3_movq_var
	cmp eax,4
	je mov_mm4_movq_var
	cmp eax,5
	je mov_mm5_movq_var
	cmp eax,6
	je mov_mm6_movq_var
	cmp eax,7
	je mov_mm7_movq_var
	xor eax,eax
	ret
	mov_mm0_movq_var:
	movq qword ptr [_64bit_data_buffer],mm0
	jmp mov_movq_var_completed
	mov_mm1_movq_var:
	movq qword ptr [_64bit_data_buffer],mm1
	jmp mov_movq_var_completed
	mov_mm2_movq_var:
	movq qword ptr [_64bit_data_buffer],mm2
	jmp mov_movq_var_completed
	mov_mm3_movq_var:
	movq qword ptr [_64bit_data_buffer],mm3
	jmp mov_movq_var_completed
	mov_mm4_movq_var:
	movq qword ptr [_64bit_data_buffer],mm4
	jmp mov_movq_var_completed
	mov_mm5_movq_var:
	movq qword ptr [_64bit_data_buffer],mm5
	jmp mov_movq_var_completed
	mov_mm6_movq_var:
	movq qword ptr [_64bit_data_buffer],mm6
	jmp mov_movq_var_completed
	mov_mm7_movq_var:
	movq qword ptr [_64bit_data_buffer],mm7
	jmp mov_movq_var_completed
	mov_movq_var_completed:
	or eax,eax
	ret
MMX_movq_var endp

MMX_emms proc
	emms
MMX_emms endp

end