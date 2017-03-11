SendMode Input
SetTitleMatchMode, 2

IfWinExist system32
{
	WinActivate
	WinClose
}

send {LWin}
sleep 200
send cmd
sleep 200
send {Enter}
sleep 200

send cd C:\Git\is\Task 4 DS
send {Enter}
sleep 200
send make
send {Enter}
sleep 200
send cd C:\Programs\mspdebug
send {Enter}
sleep 200
send mspdebug.exe tilib
send {Enter}
sleep 200
send prog C:\Git\is\Task 4 DS\msp430g2553.out
send {Enter}
sleep 200
send run
send {Enter}