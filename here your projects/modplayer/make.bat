gcc -dumpmachine
gcc  -c -I /minigp32/include/gpinclude -mtune=arm920 *.c
gcc -o example3.elf -L /minigp32/lib/gplib  gpstart.o  gpmain.o -lgpstdlib -lgpos -lgpgraphic -lgpstdio -lgpsound -lgpmem -lgpfont -Tlnkscript -Wl
objcopy -O binary example3.elf example3.gxb
del *.o
del *.elf

b2fxec example3.gxb example3.fxe

