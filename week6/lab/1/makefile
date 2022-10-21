cc = g++
lib = libswap
target = main
libarg = -shared -fPIC

$(lib).so: $(lib).cpp
	$(cc) $(lib).cpp $(libarg) -o $(lib).so

$(target): $(target).cpp $(lib).so
	$(cc) $(target).cpp -o $(target) -L. -l$(lib)