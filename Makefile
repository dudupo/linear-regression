CC = g++ -DPy_TRACE_DEFS
CCFLAGS = -c -Wall -shared -std=c++11
PYFLAGS = `python -m pybind11 --includes`
PYCONFIG = `python3-config --extension-suffix`
#LDFLAGS = -lm -L/usr/lib/ -l boost_system -l boost_filesystem
INCLDEFLAGS = -I./pybind11/include

CLASSES = svd

OBJS = $(patsubst %, %.o,  $(CLASSES))


# c++ -O3 -Wall -shared -std=c++11 -fPIC `python3 -m pybind11 --includes` example.cpp -o example`python3-config --extension-suffix`

#$(LDFLAGS)
svd: $(OBJS)
	$(CC) $(PYCONFIG)  $(OBJS) -o svdlib

%.o: %.cpp
	$(CC)  $(CCFLAGS) $(PYFLAGS) $*.cpp $()

depend:
	makedepend -- $(CCFLAGS) -- $(SRCS)

clean:
	rm -rf *.o

prod:
	make FractalDrawer
	rm -rf *.o *.h *.cpp Makefile
	chmod 755 svdlib
tar:
	tar cvf tars/svdlib svd.cpp svd.h
