
#GP32DEVROOT  =   k:/gp32/gcc/
GCCROOT      =   i:/gnu/cygwin/latest/

MAPFILE      =   main.map
DEST         =   main.elf
DESTBIN      =   demo.gxb

STDLIBS      =   -lgcc
GCCLIBVER   =   2.95.2
#LIBPATH      =   $(GP32DEVROOT)lib
#INCPATH      =   $(GP32DEVROOT)include

TARGET      =   arm-elf
AS          =   as
CC          =   gcc
LD          =   ld
OBJCOPY     =   objcopy

#ASFLAGS     =   -I$(INCPATH)

CCFLAGS     =   \
         		-mcpu=arm9tdmi \
          		-mtune=arm9tdmi \
		        -march=armv4t \
		        -mapcs \
                -msoft-float \
                -nostdlib -fno-common -ffreestanding -fno-builtin \
                -fno-sjlj-exceptions -fno-exceptions \
                -fshort-enums -mstructure-size-boundary=32 \
        		-ffast-math -fshort-double -fallow-single-precision   \
                -O3 -finline-functions -fomit-frame-pointer -fexpensive-optimizations

#                -I$(GCCROOT)usr/local/lib/gcc-lib/$(TARGET)/$(GCCLIBVER) \
#                -I$(GCCROOT)usr/local/lib/gcc-lib/$(TARGET)/$(GCCLIBVER)/include/ \
#                -I$(INCPATH)/stdlib -I$(LIBPATH)/stdlib \
#                -I$(INCPATH) -I$(LIBPATH) \
#                -Wa,-I$(INCPATH) -Wa,-I$(LIBPATH) \

LDFLAGS     =   -Map $(MAPFILE) -nostartfiles \
                --script arm-gp32bin.x \
                --library-path=/usr/local/lib/gcc-lib/$(TARGET)/$(GCCLIBVER) \

#                --library-path=$(LIBPATH) \
#                --library-path=/usr/local/$(TARGET)/lib

all:    crt0.o main.o zak.o link elf2bin

zak.o:
		$(LD) -A elf32-littlearm --format binary --oformat elf32-littlearm test.mod -o zak.o -r -EL -T bin2obj.x
main.o:
		$(CC) $(CCFLAGS) -c $*.c -o $*.o
crt0.o:
		$(CC) $(CCFLAGS) -c $*.s -o $*.o

link: crt0.o main.o zak.o
		$(LD) $(LDFLAGS) crt0.o main.o zak.o libafm.a $(STDLIBS) -o $(DEST)

elf2bin: $(DEST)
		$(OBJCOPY) -v -O binary $(DEST) $(DESTBIN)

clean:
	rm -f *.o $(MAPFILE) $(DEST) $(DESTBIN)

distclean:
	rm -f *.o $(MAPFILE) $(DEST)














