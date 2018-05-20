
set INCDIRS="-Id:\mkl\include" -IC:/Programs/Octave-4.0.0/include/octave-4.0.0 -IC:/Programs/Octave-4.0.0/include/octave-4.0.0/octave

set LIBS=-LC:/Programs/Octave-4.0.0/lib64/octave/4.0.0 -LD:/projects/myLinsolve -lmkl_rt
mkoctfile %INCDIRS% %LIBS% myLinsolve.cpp
