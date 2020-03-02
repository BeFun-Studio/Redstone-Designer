include asmfuncs.inc

.code
GetCpuVendorString proc
	xor rax,rax
	cpuid
	mov rax,offset cpuid_buffer
	mov qword ptr [rax],rbx
	add rax,4
	mov dword ptr [rax],edx
	add rax,4
	mov dword ptr [rax],ecx
	mov rax,offset cpuid_buffer
	ret
GetCpuVendorString endp

MMX_emms proc
	emms
MMX_emms endp

MMX_movd_mm0_reg proc
	pop rax
	movd mm0,rax
	ret
MMX_movd_mm0_reg endp

MMX_movd_mm1_reg proc
	pop rax
	movd mm1,rax
	ret
MMX_movd_mm1_reg endp

MMX_movd_mm2_reg proc
	pop rax
	movd mm2,rax
	ret
MMX_movd_mm2_reg endp

MMX_movd_mm3_reg proc
	pop rax
	movd mm3,rax
	ret
MMX_movd_mm3_reg endp

MMX_movd_mm4_reg proc
	pop rax
	movd mm4,rax
	ret
MMX_movd_mm4_reg endp

MMX_movd_mm5_reg proc
	pop rax
	movd mm5,rax
	ret
MMX_movd_mm5_reg endp

MMX_movd_mm6_reg proc
	pop rax
	movd mm6,rax
	ret
MMX_movd_mm6_reg endp

MMX_movd_mm7_reg proc
	pop rax
	movd mm7,rax
	ret
MMX_movd_mm7_reg endp

MMX_movd_mm0_var proc
	pop rbx
	movd qword ptr [rbx],mm0
	ret
MMX_movd_mm0_var endp

MMX_movd_mm1_var proc
	pop rbx
	movd qword ptr [rbx],mm1
	ret
MMX_movd_mm1_var endp

MMX_movd_mm2_var proc
	pop rbx
	movd qword ptr [rbx],mm2
	ret
MMX_movd_mm2_var endp

MMX_movd_mm3_var proc
	pop rbx
	movd qword ptr [rbx],mm3
	ret
MMX_movd_mm3_var endp

MMX_movd_mm4_var proc
	pop rbx
	movd qword ptr [rbx],mm4
	ret
MMX_movd_mm4_var endp

MMX_movd_mm5_var proc
	pop rbx
	movd qword ptr [rbx],mm5
	ret
MMX_movd_mm5_var endp

MMX_movd_mm6_var proc
	pop rbx
	movd qword ptr [rbx],mm6
	ret
MMX_movd_mm6_var endp

MMX_movd_mm7_var proc
	pop rbx
	movd qword ptr [rbx],mm7
	ret
MMX_movd_mm7_var endp

end