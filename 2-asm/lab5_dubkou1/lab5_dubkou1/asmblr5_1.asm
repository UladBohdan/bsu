.386
PUBLIC @ppp@8
.model flat
.code
@ppp@8	proc
	mov ebx, 1
	mov eax, ecx
	mov ecx, edx
	rep1:
	imul ebx, eax
	loop rep1
	mov eax, ebx
	ret
@ppp@8	endp
end