include stack.inc

extrn GetStdHandle:proc,
WriteConsoleA :proc, 
ReadConsoleA :proc, 
lstrlenA:proc

STD_OUTPUT_HANDLE = -11 
STD_INPUT_HANDLE = -10 

.data
hStdInput dq ? 
hStdOutput dq ?
anyKey db 0Ah, 'Press any key to exit...', 0

.code
InitConsole proc uses RAX RCX RDX R8 R9 R10 R11
STACKALLOC 1
mov RCX, STD_OUTPUT_HANDLE 
call GetStdHandle 
mov hStdOutput, RAX 
mov RCX, STD_INPUT_HANDLE 
call GetStdHandle 
mov hStdInput, RAX
STACKFREE
ret
InitConsole endp

PrintString proc uses RAX RCX RDX R8 R9 R10 R11, string: qword
local bytesWritten: qword 
STACKALLOC 1
mov RCX, string 
call lstrlenA ;
mov RCX, hStdOutput 
mov RDX, string
mov R8, RAX
lea R9, bytesWritten
NULL_FIFTH_ARG 
call WriteConsoleA 
STACKFREE
ret 8 
PrintString endp


WaitAndTerminate proc uses RAX RCX RDX R8 R9 R10 R11
local readStr   :byte,
      bytesRead :dword
STACKALLOC 1 
lea RAX, anyKey
push RAX
call PrintString
mov RCX, hStdInput
lea RDX, readStr
mov R8, 1
lea R9, bytesRead
NULL_FIFTH_ARG
call ReadConsoleA
STACKFREE 
ret
WaitAndTerminate endp
