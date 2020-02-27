include asmfuncs.inc

.code
GetCpuVendorString proc
	xor rax,rax
	cpuid
	mov rax,offset cpuid_buffer
	mov dword ptr [rax],ebx
	add rax,4
	mov dword ptr [rax],edx
	add rax,4
	mov dword ptr [rax],ecx
	mov rax,offset cpuid_buffer
	ret
GetCpuVendorString endp

MMX_movd_reg proc
	pop rbx
	pop rax
	cmp rax,0
	je mov_mm0_movd_reg
	cmp rax,1
	je mov_mm1_movd_reg
	cmp rax,2
	je mov_mm2_movd_reg
	cmp rax,3
	je mov_mm3_movd_reg
	cmp rax,4
	je mov_mm4_movd_reg
	cmp rax,5
	je mov_mm5_movd_reg
	cmp rax,6
	je mov_mm6_movd_reg
	cmp rax,7
	je mov_mm7_movd_reg
	xor rax,rax
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
	or rax,rax
	ret
MMX_movd_reg endp

MMX_movd_var proc
	pop rbx
	pop rax
	cmp rax,0
	je mov_mm0_movd_var
	cmp rax,1
	je mov_mm1_movd_var
	cmp rax,2
	je mov_mm2_movd_var
	cmp rax,3
	je mov_mm3_movd_var
	cmp rax,4
	je mov_mm4_movd_var
	cmp rax,5
	je mov_mm5_movd_var
	cmp rax,6
	je mov_mm6_movd_var
	cmp rax,7
	je mov_mm7_movd_var
	xor rax,rax
	ret
	mov_mm0_movd_var:
	movd dword ptr [rbx],mm0
	jmp mov_movd_var_completed
	mov_mm1_movd_var:
	movd dword ptr [rbx],mm1
	jmp mov_movd_var_completed
	mov_mm2_movd_var:
	movd dword ptr [rbx],mm2
	jmp mov_movd_var_completed
	mov_mm3_movd_var:
	movd dword ptr [rbx],mm3
	jmp mov_movd_var_completed
	mov_mm4_movd_var:
	movd dword ptr [rbx],mm4
	jmp mov_movd_var_completed
	mov_mm5_movd_var:
	movd dword ptr [rbx],mm5
	jmp mov_movd_var_completed
	mov_mm6_movd_var:
	movd dword ptr [rbx],mm6
	jmp mov_movd_var_completed
	mov_mm7_movd_var:
	movd dword ptr [rbx],mm7
	mov_movd_var_completed:
	or rax,rax
	ret
MMX_movd_var endp

MMX_movq_reg proc
	pop rbx
	pop rax
	cmp rax,0
	je mov_mm0_movq_reg
	cmp rax,1
	je mov_mm1_movq_reg
	cmp rax,2
	je mov_mm2_movq_reg
	cmp rax,3
	je mov_mm3_movq_reg
	cmp rax,4
	je mov_mm4_movq_reg
	cmp rax,5
	je mov_mm5_movq_reg
	cmp rax,6
	je mov_mm6_movq_reg
	cmp rax,7
	je mov_mm7_movq_reg
	xor rax,rax
	ret
	mov_mm0_movq_reg:
	movq mm0,rbx
	jmp mov_movq_reg_completed
	mov_mm1_movq_reg:
	movq mm1,rbx
	jmp mov_movq_reg_completed
	mov_mm2_movq_reg:
	movq mm2,rbx
	jmp mov_movq_reg_completed
	mov_mm3_movq_reg:
	movq mm3,rbx
	jmp mov_movq_reg_completed
	mov_mm4_movq_reg:
	movq mm4,rbx
	jmp mov_movq_reg_completed
	mov_mm5_movq_reg:
	movq mm5,rbx
	jmp mov_movq_reg_completed
	mov_mm6_movq_reg:
	movq mm6,rbx
	jmp mov_movq_reg_completed
	mov_mm7_movq_reg:
	movq mm7,rbx
	jmp mov_movq_reg_completed
	mov_movq_reg_completed:
	or rax,rax
	ret
MMX_movq_reg endp

MMX_movq_var proc
	pop rbx
	pop rax
	cmp rax,0
	je mov_mm0_movq_var
	cmp rax,1
	je mov_mm1_movq_var
	cmp rax,2
	je mov_mm2_movq_var
	cmp rax,3
	je mov_mm3_movq_var
	cmp rax,4
	je mov_mm4_movq_var
	cmp rax,5
	je mov_mm5_movq_var
	cmp rax,6
	je mov_mm6_movq_var
	cmp rax,7
	je mov_mm7_movq_var
	xor rax,rax
	ret
	mov_mm0_movq_var:
	movq qword ptr [rbx],mm0
	jmp mov_movq_var_completed
	mov_mm1_movq_var:
	movq qword ptr [rbx],mm1
	jmp mov_movq_var_completed
	mov_mm2_movq_var:
	movq qword ptr [rbx],mm2
	jmp mov_movq_var_completed
	mov_mm3_movq_var:
	movq qword ptr [rbx],mm3
	jmp mov_movq_var_completed
	mov_mm4_movq_var:
	movq qword ptr [rbx],mm4
	jmp mov_movq_var_completed
	mov_mm5_movq_var:
	movq qword ptr [rbx],mm5
	jmp mov_movq_var_completed
	mov_mm6_movq_var:
	movq qword ptr [rbx],mm6
	jmp mov_movq_var_completed
	mov_mm7_movq_var:
	movq qword ptr [rbx],mm7
	jmp mov_movq_var_completed
	mov_movq_var_completed:
	or rax,rax
	ret
MMX_movq_var endp

MMX_emms proc
	emms
MMX_emms endp

end