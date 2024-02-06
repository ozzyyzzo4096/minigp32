# Generated automatically by Visual-MinGW.
# http://visual-mingw.sourceforge.net/

CC = gcc
WRES = windres
DLLWRAP = dllwrap
CPPFLAGS = 
LDBASEFLAGS =  
INCDIRS = 
OPTIMIZ = -O2
STRIP = -s

ifeq ($(MAKECMDGOALS),debug)
CFLAGS = -W -Wall -pedantic $(INCDIRS) -g 
LDFLAGS = $(LDBASEFLAGS)
else
CFLAGS = -W -Wall -pedantic $(INCDIRS) $(OPTIMIZ) 
LDFLAGS = $(STRIP) $(LDBASEFLAGS)
endif

SRCDIR = .
BINDIR = .
LIBDIRS = 

%.o : %.rc
	$(WRES) $(CPPFLAGS) $< $@

OBJS	=\
	load_mod.o

TARGET =	$(BINDIR)\lib.exe

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
	$(CC) -o $(BINDIR)\lib.exe $(OBJS) $(INCDIRS) $(LIBDIRS) $(LDFLAGS)


