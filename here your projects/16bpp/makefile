# Generated automatically by Visual-MinGW.
# http://visual-mingw.sourceforge.net/

CC = gcc
WRES = windres
DLLWRAP = dllwrap
CPPFLAGS = 
LDBASEFLAGS = -Tlnkscript -lgpfont -lgpfont16 -lm -lgpstdlib -lgpos -lgpgraphic -lgpgraphic16 -lgpstdio -lgpsound -lgpmem
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
	gpmain.o\
	gpstart.o
	
TARGET =	$(BINDIR)\defineIt.exe

# Targets
all:	$(TARGET)
		objcopy -O binary defineIt.exe defineIt.gxb
		b2fxe defineIt.gxb defineIt.fxe

debug:	$(TARGET)

cleanobjs:
	rm -f $(OBJS)

cleanbin:
	rm -f $(TARGET)

clean:	cleanobjs cleanbin

# Dependency rules
$(TARGET): $(OBJS)
	$(CC) -o $(BINDIR)\defineIt.exe $(OBJS) $(INCDIRS) $(LIBDIRS) $(LDFLAGS)

