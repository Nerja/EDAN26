all:
	gcc swim_opt.c -O3 -lf2c -lm -fopenmp -o swim_opt.out
	./swim_opt.out < input > output
	diff output correct
	rm swim_opt.out
