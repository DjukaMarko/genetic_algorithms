#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define ARR_SIZE 12
#define POP_NUM 1000
#define MUTATION_RATE 0.01
#define NUM_GENERATIONS 50

typedef struct DNA {
	char sequence[ARR_SIZE];
	int fitness;
	float relative_fitness;

} chromosome;

chromosome *generate_random_pop(char *result, const char *SAMPLE);
int calculate_fitness(chromosome *pop, char *result);
chromosome mate_parents(chromosome *fstparent, chromosome *scndparent);
chromosome genetic_mutation(chromosome *child, const char *SAMPLE);
chromosome tournament_selection(chromosome *pop);
char generate_rand_char();

chromosome *generate_random_pop(char *result, const char *SAMPLE) {
	
	chromosome *pop = malloc(sizeof(chromosome) * POP_NUM);
	int rand_num = 0;
	for(int i = 0; i < POP_NUM; i++) {
		for(int j = 0; j < ARR_SIZE; j++) {
			rand_num = rand() % (strlen(SAMPLE));
			pop[i].sequence[j] += SAMPLE[rand_num];
		}
	}
	return pop;
}

int calculate_fitness(chromosome *pop, char *result) {
	for(int i = 0; i < POP_NUM; i++) {
		for(int j = 0; j < ARR_SIZE; j++) {
			if(pop[i].sequence[j] == result[j]) {
				pop[i].fitness++;
			}
		}
		pop[i].relative_fitness = (float)pop[i].fitness/strlen(result);
	}

	int sum_fitness = 0;
	for(int k = 0; k < POP_NUM; k++) {
		sum_fitness += pop[k].fitness;
	}
	return sum_fitness;
}
chromosome tournament_selection(chromosome *pop) {
	int num_comps = (rand() % POP_NUM + 1);
	chromosome comps[num_comps];
	for(int i = 0; i < num_comps; i++) {
		int index = (rand() % (POP_NUM-1));
		comps[i] = pop[index];
	}
	chromosome parent = comps[0];
	for(int j = 1; j < num_comps; j++) {
		if(comps[j].fitness >= parent.fitness) {
			parent = comps[j];
		}
	}
	return parent;
}


chromosome mate_parents(chromosome *fstparent, chromosome *scndparent) {
	int split_index = rand() % (ARR_SIZE-1);
	chromosome child;
	for(int i = 0; i < ARR_SIZE; i++) {
		if(i < split_index) {
			 child.sequence[i] = fstparent->sequence[i];
		}
		else {
			child.sequence[i] = scndparent->sequence[i];
		}
	}
	return child;
}

chromosome genetic_mutation(chromosome *child, const char *SAMPLE) {
	for(int i = 0; i < POP_NUM; i++) {
		if((rand() % 100) == MUTATION_RATE*100) {
			int prob = rand() % ARR_SIZE;
			for(int j = 0; i < prob; i++) {
				int index = rand() % (ARR_SIZE-1);
				child->sequence[index] = generate_rand_char(SAMPLE);
			}
		}
	}
	return *child;
}
char generate_rand_char(const char *SAMPLE) {
	return SAMPLE[rand() % (strlen(SAMPLE)-1)];
}

int main(int argc, char *argv[]) {

	srand(time(0));
	printf("STARTING GENETIC ALGORITHM\n");
	char *result = "deeznutsbruh";
	const char *SAMPLE = "1234567890qwertyuiopasdfghjklzxcvbnm  [];'=-./,?!";
	chromosome *pop = generate_random_pop(result, SAMPLE);
	for(int i = 0; i < NUM_GENERATIONS; i++) {
		int check = 0;
		chromosome new_pop[POP_NUM];
		calculate_fitness(pop, result);
		for(int j = 0; j < POP_NUM; j++) {
			chromosome first_parent = tournament_selection(pop);
			chromosome second_parent = tournament_selection(pop);
			chromosome child = mate_parents(&first_parent, &second_parent);
			chromosome mut_child = genetic_mutation(&child, SAMPLE);
			new_pop[j] = mut_child;

			printf("%s\n", mut_child.sequence);
			if(!strcmp(mut_child.sequence, result)) {
				check = 1;
				printf("FOUND THE RESULT: %s\n", mut_child.sequence);
				break;
			}
		}
		if(check) {
			break;
		}
		pop = new_pop;
	}
	printf("LENGTH OF THE SAMPLE IS %ld\n", strlen(SAMPLE));
	return 0;
}
