STACKALLOC macro arg
  push R15
  mov R15, RSP
  sub RSP, 8*4
  if arg
    sub RSP, 8*arg
  endif
  and SPL, 0F0h
endm

STACKFREE macro arg
	mov RSP,R15
	pop R15
endm
NULL_FIFTH_ARG macro arg
mov qword ptr [RSP + 32], 0
endm