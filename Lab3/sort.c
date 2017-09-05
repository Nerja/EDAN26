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
#define MAX_SPLITS 2

static double sec(void)
{
	struct timespec ts;
	timespec_get(&ts, TIME_UTC);
	return ts.tv_nsec;
}

void merge(void* base, size_t n, size_t s, int left_size) {
	//printf("******BEFORE*******\n");
	//printf("left_size: %d\n", left_size);
	//for(int i = 0; i < n; i++)
	//	printf("%f ", ((double*)base)[i]);
	//printf("\n");
	double* new_base = malloc(n * s);
	int left_index = 0, right_index = 0;
	while(left_index < left_size && right_index < (n - left_size)) {
		double left_value = ((double*)base)[left_index];
		double right_value = ((double*)base)[right_index + left_size];
		if(left_value > right_value) {
			new_base[left_index + right_index] = right_value;
			right_index++;
		} else {
			new_base[left_index + right_index] = left_value;
			left_index++;
		}
	}
	if(left_index < left_size) {
		//risky
		memmove(new_base + (left_index + right_index), base + s*left_index, s*(left_size - left_index));
	} else {
		memmove(new_base + left_size + right_index, base + s*(left_size + right_index), s*(n - (left_size + right_index)));
	}
	memmove(base, (void*)new_base, n*s);
	//for(int i = 0; i < n; i++)
	//	printf("%f ", new_base[i]);
	//printf("\n***********************\n");
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

		//wait for join both threads
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
	double		start, end;

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

	start = sec();

	par_sort(b, n, sizeof b[0], cmp);
	qsort(a, n, sizeof a[0], cmp);

	end = sec();

	printf("%1.2f s\n", (end - start) / 1000000000);
/*	for(i = 0; i < n; i++) {
		printf("%f\n", b[i]);
	}
	printf("\n****************\n");
*/
	int ok = 1;
	for(i = 0; i < n; i++) {
		if(a[i] != b[i]) {
			ok = 0;
			break;
		}
	}

	if(ok == 0) {
		for(i = 0; i < n; i++) {
			printf("%f --- %f \n", a[i], b[i]);
		}
	}


	free(a);
	free(b);

	return 0;
}
