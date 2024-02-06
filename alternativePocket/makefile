# Generated automatically by Visual-MinGW.
# http://visual-mingw.sourceforge.net/

CC = gcc
WRES = windres
DLLWRAP = dllwrap
CPPFLAGS = 
LDBASEFLAGS = -Tlnkscript -lgpfont -lm -lgpstdlib -lgpos -lgpgraphic -lgpstdio -lgpsound -lgpmem 
INCDIRS = -I /minigp32/include/gpinclude
OPTIMIZ = 
STRIP = -s

ifeq ($(MAKECMDGOALS),debug)
CFLAGS =  $(INCDIRS) -g 
LDFLAGS = $(LDBASEFLAGS)
else
CFLAGS =  $(INCDIRS) $(OPTIMIZ) 
LDFLAGS = $(STRIP) $(LDBASEFLAGS)
endif

SRCDIR = .
BINDIR = .
LIBDIRS = -L /minigp32/lib/gplib

%.o : %.rc
	$(WRES) $(CPPFLAGS) $< $@

OBJS	=\
	images.o\
	gpstart.o\
	mars.o

TARGET =	$(BINDIR)\mars.elf

# Targets
all:	$(TARGET)
		objcopy -O binary mars.elf mars.gxb
		b2fxe mars.gxb mars.fxe
		
debug:	$(TARGET)

cleanobjs:
	rm -f $(OBJS)

cleanbin:
	rm -f $(TARGET)

clean:	cleanobjs cleanbin

# Dependency rules
$(TARGET): $(OBJS)
	$(CC) -o $(BINDIR)\mars.elf $(OBJS) $(INCDIRS) $(LIBDIRS) $(LDFLAGS)

