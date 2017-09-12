all: merge quick
.PHONY : all


merge:
	cc -D_POSIX_C_SOURCE=199309 -o merge_sort.out -std=c11 -pthread -lpthread merge_sort.c 
	./merge_sort.out

quick:
	cc -D_POSIX_C_SOURCE=199309 -o quick_sort.out -std=c11 -pthread -lpthread quick_sort.c 
	./quick_sort.out

clean:
	rm -f *.out
