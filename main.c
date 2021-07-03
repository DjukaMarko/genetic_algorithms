#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define ARR_SIZE 17
#define POP_NUM 10
#define MAX_PARENTS 10

typedef struct DNA {
	char sequence[ARR_SIZE];
	int fitness;
	float relative_fitness;

} chromosome;
void generate_random_pop(char *result);
void calculate_fitness(chromosome *pop, char *result);
void genetic_crossover(chromosome *parents);
void generate_random_pop(char *result) {
	const char *SAMPLE = "1234567890qwertyuiopasdfghjklzxcvbnm  [];'=-./,?!";
	
	chromosome pop[POP_NUM] = {0,0};
	int rand_num = 0;
	for(int i = 0; i < POP_NUM; i++) {
		for(int j = 0; j < ARR_SIZE; j++) {
			rand_num = rand() % strlen(SAMPLE);
			pop[i].sequence[j] += SAMPLE[rand_num];
		}
	}

	for(int k = 0; k < POP_NUM; k++) {
		for(int l = 0; l < ARR_SIZE; l++) {
			printf("%c", pop[k].sequence[l]);
		}
		printf("\n");
	}

	calculate_fitness(pop, result);
}

void calculate_fitness(chromosome *pop, char *result) {
	for(int i = 0; i < POP_NUM; i++) {
		for(int j = 0; j < ARR_SIZE; j++) {
			if(pop[i].sequence[j] == result[j]) {
				pop[i].fitness++;
			}
		}
		pop[i].relative_fitness = (float)pop[i].fitness/strlen(result);
		printf("FITNESS AND REL FITNESS %d %f\n",pop[i].fitness, pop[i].relative_fitness);
	}

	chromosome parents[MAX_PARENTS];

	for(int k = 0; k < POP_NUM; k++) {
		for(int l = 0; l < ((int)ceil((pop[k].relative_fitness*10))); l++) {
			parents[l] = pop[k];
			printf("%d, rel*10 = %d \n", parents[l].fitness, (int)ceil(pop[k].relative_fitness*10));
		}
	}

	genetic_crossover(parents);

}
void genetic_crossover(chromosome *parents) {
	
}




int main(int argc, char *argv[]) {

	srand(time(0));
	printf("STARTING GENETIC ALGORITHM\n");
	char *result = "unicorn";
	printf("LENGTH OF THE RESULT %ld\n", strlen(result));
	generate_random_pop(result);
	return 0;
}
