#Rehan Javaid, rj3dxu, 11/17/2020, Makefile

a.out: traveling.cpp middleearth.cpp
	clang++ -O2 traveling.cpp middleearth.cpp
	doxygen
