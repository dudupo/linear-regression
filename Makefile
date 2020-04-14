CC = g++  -std=c++2a
CCFLAGS = -c
#LDFLAGS = -lm -L/usr/lib/ -l boost_system -l boost_filesystem
INCLDEFLAGS = -I./tabulate/include  -I./spdlog/include

CLASSES = matrix svd

OBJS = $(patsubst %, %.o,  $(CLASSES))


# c++ -O3 -Wall -shared -std=c++11 -fPIC `python3 -m pybind11 --includes` example.cpp -o example`python3-config --extension-suffix`


matrix: matrix.cpp matrix.h
	g++ -std=c++2a $(INCLDEFLAGS) matrix.cpp  -o matrix.o

svd:
	g++ -std=c++2a $(INCLDEFLAGS) -o svdlib svd.cpp matrix.cpp 



depend:
	makedepend -- $(CCFLAGS) -- $(SRCS)

clean:
	rm -rf *.o

prod:
	make svd
	rm -rf *.o *.h *.cpp Makefile
	chmod 755 svdlib
tar:
	tar cvf tars/svdlib svd.cpp svd.h
