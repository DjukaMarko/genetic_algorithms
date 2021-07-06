#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define ARR_SIZE 7
#define POP_NUM 100
#define MAX_PARENTS 10
#define MUTATION_RATE 0.01

typedef struct DNA {
	char sequence[ARR_SIZE];
	int fitness;
	float relative_fitness;

} chromosome;

chromosome *generate_random_pop(char *result);
int calculate_fitness(chromosome *pop, char *result);
chromosome mate_parents(chromosome *fstparent, chromosome *scndparent);
chromosome *genetic_mutation(chromosome *child);
chromosome tournament_selection(chromosome *pop, int sum_fitness);
char generate_rand_char();

chromosome *generate_random_pop(char *result) {
	const char *SAMPLE = "1234567890qwertyuiopasdfghjklzxcvbnm  [];'=-./,?!";
	
	chromosome *pop = malloc(sizeof(chromosome) * POP_NUM);
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
		printf("FITNESS AND REL FITNESS %d %f\n",pop[i].fitness, pop[i].relative_fitness);
	}

	int sum_fitness = 0;
	for(int k = 0; k < POP_NUM; k++) {
		sum_fitness += pop[k].fitness;
	}
	printf("SUM OF ALL FITNESSES %d\n", sum_fitness);
	return sum_fitness;
}
chromosome tournament_selection(chromosome *pop, int sum_fitness) {
	int num_comps = (rand() % POP_NUM)-1;
	chromosome comps[num_comps];
	for(int i = 0; i < num_comps; i++) {
		int index = (rand() % POP_NUM)-1;
		comps[i] = pop[index];
	}
	chromosome parent = comps[0];
	for(int j = 1; j < num_comps; j++) {
		if(comps[j].fitness >= parent.fitness) {
			parent = comps[j];
		}
	}
	printf("CHOSEN PARENT FITNESS IS %d(num comps = %d)\n", parent.fitness, num_comps);
	return parent;
}


chromosome mate_parents(chromosome *fstparent, chromosome *scndparent) {
	printf("SEQUENCE OF FIRST PARENT: %s and SECOND: %s\n", fstparent->sequence, scndparent->sequence);
	int split_index = rand() % ARR_SIZE;
	chromosome child;
	for(int i = 0; i < ARR_SIZE; i++) {
		if(i < split_index) {
			 child.sequence[i] = fstparent->sequence[i];
		}
		else {
			child.sequence[i] = scndparent->sequence[i];
		}
	}
	printf("CHILD SEQUENCE %s\n", child.sequence);

	return child;
}

chromosome *genetic_mutation(chromosome *child) {
	chromosome *new_pop = malloc(sizeof(chromosome) * POP_NUM);
	int arr_size = 0;
	for(int i = 0; i < POP_NUM; i++) {
		if((rand() % 100) == MUTATION_RATE*100) {
			int prob = rand() % ARR_SIZE;
			for(int j = 0; i < prob; i++) {
				int index = rand() % ARR_SIZE;
				child->sequence[index] = generate_rand_char();
				printf("PROB %d, INDEX %d", prob, index);
				new_pop[j] = *child;
				arr_size++;
			}
		}
	}
	return new_pop;
}
char generate_rand_char() {
	const char *SAMPLE = "1234567890qwertyuiopasdfghjklzxcvbnm  [];'=-./,?!";
	char ret = SAMPLE[rand() % 47];
	printf("RANDOM CHAR %c\n", ret);
	return ret;
}




int main(int argc, char *argv[]) {

	srand(time(0));
	printf("STARTING GENETIC ALGORITHM\n");
	generate_random_pop("unicorn");
	return 0;
}
