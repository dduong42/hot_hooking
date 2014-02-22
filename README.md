How to hook a function on a process that is currently running:

$ gdb ./target
GNU gdb (GDB) 7.4.1-debian
Copyright (C) 2012 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "x86_64-linux-gnu".
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>...
Reading symbols from /home/dbourbaki/share_debian/coding/c/ptrace_hook/target...(no debugging symbols found)...done.
(gdb) disass write
Dump of assembler code for function write@plt:
   0x00000000004004d0 <+0>:     jmpq   *0x2005da(%rip)        # 0x600ab0 <write@got.plt>
   0x00000000004004d6 <+6>:     pushq  $0x0
   0x00000000004004db <+11>:    jmpq   0x4004c0
End of assembler dump.

--> hook.c
#define ADDR_WRITE (void *)0x600ab0

-->
Injector side:
$ ./hook 12159
[*] The payload is located at 0x7f20aca84000

Target side:
$ ./target
I am the target and my pid is: 12159
First call

Hooked !
Second call