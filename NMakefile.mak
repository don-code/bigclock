!include <win32.mak>

all: clock.exe

.c.obj:
  $(cc) $(cdebug) $(cflags) $(cvars) $*.c

clock.exe: clock.obj charset.obj
  $(link) $(ldebug) $(conflags) -out:clock.exe charset.obj clock.obj $(conlibs)