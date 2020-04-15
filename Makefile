CC = g++  -std=c++2a
CCFLAGS = -c
#LDFLAGS = -lm -L/usr/lib/ -l boost_system -l boost_filesystem
INCLDEFLAGS =   -I./spdlog/include
#-I./tabulate/include
CLASSES = matrix svd

OBJS = $(patsubst %, %.o,  $(CLASSES))


# c++ -O3 -Wall -shared -std=c++11 -fPIC `python3 -m pybind11 --includes` example.cpp -o example`python3-config --extension-suffix`


# matrix: matrix.cpp matrix.h
# 	g++ -std=c++2a $(INCLDEFLAGS) matrix.cpp  -o matrix.o

# matrix.o : matrix.cpp matrix.h
# 	g++ -std=c++2a -c matrix.cpp $(INCLDEFLAGS) -Wall

# svd.o : matrix.o svd.cpp svd.h
# 	g++ -o svd.cpp -std=c++2a $(INCLDEFLAGS)

svd: #matrix.ttp matrix.h svd.cpp svd.h
	g++ -o svdlib ./svd.cpp -I./spdlog/include/ -Wall
	# g++ -c matrix.cpp -std=c++2a $(INCLDEFLAGS)
	# g++ -c svd.cpp -std=c++2a $(INCLDEFLAGS)
	#g++ -std=c++2a -g -o svdlib.exe svd.cpp  $(INCLDEFLAGS) -Wall -lm matrix.o
	# g++ -o svdlib matrix.o svd.o



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
