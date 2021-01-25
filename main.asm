include console.inc

extrn GetLocalTime  :proc
extrn GetStdHandle  :proc
extrn WriteConsoleA :proc
extrn ReadConsoleA  :proc
extrn lstrlenA      :proc
extrn wsprintfA     :proc
extrn ExitProcess   :proc
extrn SetConsoleTitleA : proc

.data
SYSTEMTIME struct
    wYear word ?
    wMonth word ?
    wDayOfWeek word ?
    wDay word ?
    wHour word ?
    wMinute word ?
    wSecond word ?
    wMilliseconds word ?
SYSTEMTIME ends

strWinAPItime db 'The WinAPI time is: %02i:%02i:%02i', 0Ah, 0
strWinAPIdate db 'The WinAPI date is: %02i.%02i.%04i', 0Ah, 0

.const
first db 'Console GetLocalTime ', 0

.code
Start proc 
local systime         :SYSTEMTIME,
     outputData[256]  :byte
STACKALLOC 1
call InitConsole

lea RCX, first
call SetConsoleTitleA

lea RCX, systime
call GetLocalTime

lea RCX, outputData
lea RDX, strWinAPItime
movzx R8, systime.wHour
movzx R9, systime.wMinute
movzx RAX, systime.wSecond
MOV [RSP + 20H], RAX 
call wsprintfA

lea RAX, outputData
push RAX
call PrintString

lea RCX, outputData
lea RDX, strWinAPIdate
movzx R8, systime.wDay
movzx R9, systime.wMonth
movzx RAX, systime.wYear
MOV [RSP + 20H], RAX 
call wsprintfA

lea RAX, outputData
push RAX
call PrintString

call WaitAndTerminate
xor RCX,RCX
call ExitProcess
ret
Start endp

end