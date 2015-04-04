cc = g++
inc = core.h regsiter.h memory.h util.h state.h
src = main.cpp core.cpp register.cpp memory.cpp util.cpp state.cpp
flag = -o
dflag = -D DEBUG -o
sflag = -D DEBUG STEP -o
out = main
dout = main_dbg

all: $(src)
	$(cc) $(flag) $(out) $(src)
	$(cc) $(dflag) $(dout) $(src)

