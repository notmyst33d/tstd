.global sys_write
sys_write:
	mov x8, 64
	svc 0
	ret

.global sys_exit
sys_exit:
	mov x8, 93
	svc 0
	ret
