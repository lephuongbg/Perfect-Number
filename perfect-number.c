/* Find Perfect Number */
#include <stdio.h>
#include <omp.h>
#include <math.h>

unsigned numDigits(const unsigned n) {
    if (n < 10) return 1;
    return 1 + numDigits(n / 10);
}

int main(void) {
	unsigned long int start, end, perfect_numbers[47], chk, chk_i, chk_sum, chk_max;
	int count=0,chk_len,chk_j,num_threads;
	double start_time, end_time;

	puts("             !!!Find the perfect numbers in number range!!!");
	printf("Input start number: "); scanf("%ld", &start);
	printf("Input end number: "); scanf("%ld", &end);
	printf("Input number of processing thread (should be 2): "); scanf("%d", &num_threads);
	omp_set_num_threads(num_threads); 
	start_time = omp_get_wtime();

	/*If the ending number is smaller than starting number*/	
	if (end<start) {
	chk_j = end;
	end = start;
	start = chk_j;
	}

	printf("\nChecking ");
	/*Start checking loop*/
	for (chk=start; chk<=end; chk++ ) {
		chk_sum = 0;
		chk_max = (int) floor(chk/2);

		/*Display progress*/
		printf("%ld...",chk); fflush(stdout); /*Print the number*/
		chk_len = numDigits(chk);
		for (chk_j = 1; chk_j<=chk_len; chk_j++) {
			printf("\b"); /*Delete the number*/
		}
		printf("\b\b\b"); /*Delete the "..."*/

		/*Checking-each-number loop*/
		#pragma omp parallel for default(shared) private(chk_i) reduction(+:chk_sum)
		for (chk_i = 1; chk_i <= chk_max; chk_i ++) {
			if (chk % chk_i == 0) chk_sum += chk_i;
		}
		if (chk_sum == chk) {perfect_numbers[count] = chk; count++;}
	}
	end_time = omp_get_wtime();
	printf("\nDone!!!");
	printf("\n\nFinished checking in: %f",end_time-start_time);
	if (count != 0) {
		printf("\n\nAll perfect numbers:");
		int i;
		for (i = 0; i < count; i++) {
			printf(" %ld ", perfect_numbers[i]);
		}
		printf("\n");
	} else {
		puts("\nThere isn't any perfect number!!!");
	}
	return 0;
}
