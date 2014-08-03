BigClock
========

BigClock is a full-screen text mode clock that will run on any 80-by-25
character terminal. Though it was designed with DOS in mind, it will also run
both on Windows and any UNIX-like OS.

What does it look like?
-----------------------
The text mode UI looks like this (note that in most console fonts, the gaps
present in the block characters with GitHub's default fonts will not be
present):
```
   August 2014 Calendar             Today's date

   Su Mo Tu We Th Fr Sa  Wk
                  1  2   30         ██████  ██████  ██████  ██████  ██████
   3  4  5  6  7  8  9   31         █       █    █    ██    ██  ██      ██
   10 11 12 13 14 15 16  32         ██████  ██████    ██    ██  ██  ██████
   17 18 19 20 21 22 23  33              █  █    █    ██    ██  ██  ██
   24 25 26 27 28 29 30  34         ██████  █    █    ██    ██████  ██████
   31                    35




  Local Time


         ██████  ██████    ██    ██████  ██████    ██    ██████  ██  ██
             ██  ██  ██    ██    ██      ██  ██    ██        ██  ██  ██
         ██████  ██  ██          ██████  ██  ██          ██████  ██████
         ██      ██  ██    ██        ██  ██  ██    ██    ██          ██
         ██████  ██████    ██    ██████  ██████    ██    ██████      ██
```

At present, BigClock assumes a CP437-compliant character set, such as is found
by default on DOS and Windows. Unicode support for other OSes is in the works;
please adjust your terminal settings to use such a font in the meantime.

How it Works
------------
BigClock's main loop wakes up every one second and refreshes the time. If it
detects that the hour has rolled over from 23 to 00, it will additionally
refresh the calendar and date.

Each large-format glyph is represented as a C array of block characters
(see charset.c).

Build instructions
------------------
BigClock is ANSI C-compliant, and should compile under any compliant compiler.
It has been tested with Visual Studio on Windows, gcc on Linux, and both
Borland Turbo C++ and Digital Mars C++ on DOS.

For systems with GNU Make, a Makefile is included. Windows users with Visual
Studio can use NMake with the included NMakefile.mak. Digital Mars DOS users
can use the included build_dos.bat to compile a "clock.com", which will run on
most DOSes.

### Considerations for DOS
On a DOS-based system, it is required to load an ANSI driver such as MS-DOS's
ansi.sys, or FreeDOS's nansi.sys - otherwise, the interface's drawing routines
will only write garbage to the screen.

Additionally, in a single-tasking OS such as DOS, it's useful to side-load a
tool such as FreeDOS's fdapm, to keep the CPU in a low-power state while
BigClock sleeps.
