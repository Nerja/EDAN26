#include <assert.h>
#include <limits.h>
#include <pthread.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/times.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define MAX_SPLITS 2

//https://stackoverflow.com/questions/20483534/clock-gettime-still-not-monotonic-alternatives
static double sec(void)
{
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	return ts.tv_sec + (ts.tv_nsec / 1000000000.0);
}

void merge(void* base, size_t n, size_t s, int left_size) {
	double* new_base = malloc(n * s);
	int left_index = 0, right_index = 0;
	while(left_index < left_size && right_index < (n - left_size)) {
		double left_value = ((double*)base)[left_index];
		double right_value = ((double*)base)[right_index + left_size];
		if(left_value > right_value)
			new_base[left_index + right_index++] = right_value;
		else
			new_base[left_index++ + right_index] = left_value;
	}
	if(left_index < left_size)
		memmove(new_base + (left_index + right_index), base + s*left_index, s*(left_size - left_index));
	else
		memmove(new_base + left_size + right_index, base + s*(left_size + right_index), s*(n - (left_size + right_index)));
	memmove(base, (void*)new_base, n*s);
}

struct Params {
		void* base;
		size_t n;
		size_t s;
		int		(*cmp)(const void*, const void*);
		int nbr_splits;
};

void par_sort_rec(
	void*		base,	// Array to sort.
	size_t		n,	// Number of elements in base.
	size_t		s,	// Size of each element.
	int		(*cmp)(const void*, const void*),
	int nbr_splits);

void* pack_func(void* s) {
	struct Params* p = (struct Params*)s;
	par_sort_rec(p->base, p->n, p->s, p->cmp, p->nbr_splits);
}

void par_sort_rec(
	void*		base,	// Array to sort.
	size_t		n,	// Number of elements in base.
	size_t		s,	// Size of each element.
	int		(*cmp)(const void*, const void*),
	int nbr_splits) // Behaves like strcmp
{
	if(nbr_splits >= MAX_SPLITS) {
		qsort(base, n, s, cmp);
	} else {
		int left_size = n / 2;

		pthread_t left_thread;
		struct Params left_params = {base, left_size, s, cmp, nbr_splits+1};
		pthread_create(&left_thread, NULL, pack_func, &left_params);

		pthread_t right_thread;
		struct Params right_params = {base + s*left_size, n - left_size, s, cmp, nbr_splits+1};
		pthread_create(&right_thread, NULL, pack_func, &right_params);

		pthread_join(left_thread, NULL);
		pthread_join(right_thread, NULL);

		merge(base, n, s, left_size);
	}
}

void par_sort(
	void*		base,	// Array to sort.
	size_t		n,	// Number of elements in base.
	size_t		s,	// Size of each element.
	int		(*cmp)(const void*, const void*)) // Behaves like strcmp
{
	par_sort_rec(base, n, s, cmp, 0);
}

static int cmp(const void* ap, const void* bp)
{
	return *(double*)ap - *(double*)bp;
}

int main(int ac, char** av)
{
	int		n = 10000000;
	int		i;
	double*		a;
	double*		b;
	double		par_start, par_end, seq_start, seq_end;

	if (ac > 1)
		sscanf(av[1], "%d", &n);

	srand(getpid());

	a = malloc(n * sizeof a[0]);
	b = malloc(n * sizeof a[0]);
	for (i = 0; i < n; i++) {
		double x = rand();
		a[i] = x;
		b[i] = x;
	}

	par_start = sec();
	par_sort(b, n, sizeof b[0], cmp);
	par_end = sec();

	seq_start = sec();
	qsort(a, n, sizeof a[0], cmp);
	seq_end = sec();


	for(i = 0; i < n; i++)
		assert(a[i] == b[i]);

	printf("Sequential version: \t%lfs\n", (seq_end - seq_start));
	printf("Parallel version: \t%lfs\n", (par_end - par_start));


	free(a);
	free(b);

	return 0;
}
