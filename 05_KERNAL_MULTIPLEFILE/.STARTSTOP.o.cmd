savedcmd_STARTSTOP.o := ld -m elf_x86_64 -z noexecstack --no-warn-rwx-segments   -r -o STARTSTOP.o @STARTSTOP.mod 
