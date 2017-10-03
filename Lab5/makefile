
all: a b c d e

.PHONY: all

a:
	cp a.cc a_copy.cc
	sed -i -e 's/#include "timebase.h"//g' a_copy.cc
	sed -i -e 's/init_timebase();//g' a_copy.cc
	sed -i -e 's/begin = timebase_sec();/begin = sec();/g' a_copy.cc
	sed -i -e 's/end = timebase_sec();/end = sec();/g' a_copy.cc
	g++ -O3 -std=c++11 a_copy.cc -m64 -pthread
	./a.out
	rm a_copy.cc

b:
	cp b.cc b_copy.cc
	sed -i -e 's/#include "timebase.h"//g' b_copy.cc
	sed -i -e 's/init_timebase();//g' b_copy.cc
	sed -i -e 's/begin = timebase_sec();/begin = sec();/g' b_copy.cc
	sed -i -e 's/end = timebase_sec();/end = sec();/g' b_copy.cc
	g++ -O3 -std=c++11 b_copy.cc -m64 -pthread -o b.out
	./b.out
	rm b_copy.cc

c:
	cp c.cc c_copy.cc
	sed -i -e 's/#include "timebase.h"//g' c_copy.cc
	sed -i -e 's/init_timebase();//g' c_copy.cc
	sed -i -e 's/begin = timebase_sec();/begin = sec();/g' c_copy.cc
	sed -i -e 's/end = timebase_sec();/end = sec();/g' c_copy.cc
	g++ -O3 -std=c++11 c_copy.cc -m64 -pthread -o c.out
	./c.out
	rm c_copy.cc

d:
	cp d.cc d_copy.cc
	sed -i -e 's/#include "timebase.h"//g' d_copy.cc
	sed -i -e 's/init_timebase();//g' d_copy.cc
	sed -i -e 's/begin = timebase_sec();/begin = sec();/g' d_copy.cc
	sed -i -e 's/end = timebase_sec();/end = sec();/g' d_copy.cc
	g++ -O3 -std=c++11 d_copy.cc -m64 -pthread -o d.out
	./d.out
	rm d_copy.cc

e:
	cp e.cc e_copy.cc
	sed -i -e 's/#include "timebase.h"//g' e_copy.cc
	sed -i -e 's/init_timebase();//g' e_copy.cc
	sed -i -e 's/begin = timebase_sec();/begin = sec();/g' e_copy.cc
	sed -i -e 's/end = timebase_sec();/end = sec();/g' e_copy.cc
	g++ -O3 -std=c++11 e_copy.cc -m64 -pthread -o e.out
	./e.out
	rm e_copy.cc
