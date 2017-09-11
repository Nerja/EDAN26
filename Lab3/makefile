all: merge quick
.PHONY : all


merge:
	cc -D_POSIX_C_SOURCE=199309 -std=c11 -pthread -lpthread merge_sort.c 
	./a.out

quick:
	cc -D_POSIX_C_SOURCE=199309 -std=c11 -pthread -lpthread quick_sort.c 
	./a.out

clean:
	rm -f *.out
