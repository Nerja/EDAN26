CC		= gcc

CFLAGS		= -Wall -pedantic -std=c99 -m32 -g
CFLAGS		= -m64 -g -Wall -pedantic -Werror -std=c99
CFLAGS		= -O3 -g -maltivec -Wall -pedantic -std=c99
CFLAGS		= -O3 -g -Wall -pedantic -std=c99

OBJS		= main.o list.o error.o random.o set.o dataflow.o

OUT		= live

LDFLAGS		= -lpthread

S=10000
V=1000
U=4
A=1000
T=4
P=1

all: $(OBJS)	
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(OUT)
	valgrind --tool=helgrind ./$(OUT) $(S) $(V) $(U) $(A) $(T) 0 $(L)
	./$(OUT) $(S) $(V) $(U) $(A) $(T) $(P) > out_c
	tail -n +12 out_c > out_c_tmp; mv out_c_tmp out_c
	#cd ../Lab1/ && javac Dataflow.java && java -Xmx2048M Dataflow $(S) $(V) $(U) $(A) 1 1 > ../Proj/out_java
	#tail -n +9 out_java > out_java_tmp; mv out_java_tmp out_java
	cmp out_c out_java

measuretime: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(OUT)
	./$(OUT) 100000 100000 4 1000 4 0

clean:
	rm -f $(OUT) $(OBJS) cfg.dot
