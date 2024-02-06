# Generated automatically by Visual-MinGW.
# http://visual-mingw.sourceforge.net/

LD = ld
CC = gcc
WRES = windres
DLLWRAP = dllwrap
CPPFLAGS = 
LDBASEFLAGS = -Tlnkscript -lgpfont -lafm -lgpstdlib -lgpos -lgpgraphic -lgpstdio -lgpsound -lgpmem 
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
	gpstart.o\
	main.o

TARGET =	$(BINDIR)\example3.exe

# Targets
all:	$(TARGET)

debug:	$(TARGET)

cleanobjs:
	rm -f $(OBJS)

cleanbin:
	rm -f $(TARGET)

clean:	cleanobjs cleanbin

# Dependency rules
$(TARGET): $(OBJS)
	$(LD) -A elf32-littlearm --format binary --oformat elf32-littlearm test.mod -o zak.o -r -EL -T bin2obj.x
	$(CC) -o $(BINDIR)\example3.exe $(OBJS) $(INCDIRS) $(LIBDIRS) $(LDFLAGS)


