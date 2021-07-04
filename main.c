#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define ARR_SIZE 17
#define POP_NUM 100
#define MAX_PARENTS 10
#define MUTATION_RATE 0.01

typedef struct DNA {
	char sequence[ARR_SIZE];
	int fitness;
	float relative_fitness;

} chromosome;
void generate_random_pop(char *result);
void calculate_fitness(chromosome *pop, char *result);
void genetic_crossover(chromosome *parents, int size);
void mate_parents(chromosome *fstparent, chromosome *scndparent);
void genetic_mutation(chromosome *child);
char generate_rand_char();

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

	chromosome parents[MAX_PARENTS] = {0};
	int num_elements = 0;
	int d = 0;
	int l = 0;
	for(int k = 0; k < POP_NUM; k++) {
		for(l = d; l < ((int)ceil((pop[k].relative_fitness*10))); l++) {
			parents[l] = pop[k];
			num_elements++;
			printf("%d, rel*10 = %d and sequence %s\n", parents[l].fitness, (int)ceil(pop[k].relative_fitness*10), parents[l].sequence);
		}
		d = l;
	}
	printf("SIZE OF 1 CHROMOSOME %ld and SIZE OF PARENTS %ld\n", sizeof(chromosome), sizeof(parents));
	for(int o = 0; o < MAX_PARENTS; o++) {
		printf("%s\n", parents[o].sequence);
	}
	genetic_crossover(parents, num_elements);

}
void genetic_crossover(chromosome *parents, int size) {
	if(size) {
		int fstindex = rand() % size;
		int scndindex = rand() % size;
		printf("FIRST INDEX: %d, SECOND INDEX: %d and SIZE: %d\n", fstindex,scndindex, size);
		printf("SEQUENCES: %s       %s\n", parents[fstindex].sequence, parents[scndindex].sequence);
		mate_parents(&parents[fstindex], &parents[scndindex]);
	}
}

void mate_parents(chromosome *fstparent, chromosome *scndparent) {
	printf("SEQUENCE OF FIRST PARENT: %s and SECOND: %s\n", fstparent->sequence, scndparent->sequence);
	int split_index = rand() % ARR_SIZE;
	chromosome child;
	for(int i = 0; i < ARR_SIZE; i++) {
		if(i < split_index) child.sequence[i] = fstparent->sequence[i];
		else child.sequence[i] = scndparent->sequence[i];
	}
	printf("CHILD SEQUENCE %s\n", child.sequence);

	genetic_mutation(&child);
}

void genetic_mutation(chromosome *child) {
	if((rand() % 10) == MUTATION_RATE*100) {
		int prob = rand() % ARR_SIZE;
		for(int i = 0; i < prob; i++) {
			int index = rand() % ARR_SIZE;
			child->sequence[index] = generate_rand_char();
		}
	}
	printf("MUTATED CHILD %s\n", child->sequence);
}
char generate_rand_char() {
	const char *SAMPLE = "1234567890qwertyuiopasdfghjklzxcvbnm  [];'=-./,?!";
	char ret = SAMPLE[rand() % 49];
	return ret;
}




int main(int argc, char *argv[]) {

	srand(time(0));
	printf("STARTING GENETIC ALGORITHM\n");
	char *result = "unicorn";
	printf("LENGTH OF THE RESULT %ld\n", strlen(result));
	generate_random_pop(result);
	return 0;
}
