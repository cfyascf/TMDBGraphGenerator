#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/actors.h"

ActorsArray * construct_actors_array(int capacity) {
    ActorsArray * v = (ActorsArray *)malloc(sizeof(ActorsArray));
    v->size = 0;
    v->capacity = capacity;
    v->data = (Actor *)malloc(capacity * sizeof(Actor));

    return v;
}

void append_actors_array(ActorsArray * v, Actor a) {
    if (!v) {
        return;
    }

    if (v->size == v->capacity - 1) {
        v->capacity += v->capacity / 2;
        v->data = (Actor *)realloc(v->data, v->capacity * sizeof(a));
    }

    ((Actor *)v->data)[v->size] = a;
    v->size++;
}

char * strip_actor_id(const char * v, int size) {
//	..string to store the stripped id..
	char * aux = (char *)malloc(size - 1 * sizeof(char));

	int j = 0;
//	..skips the first two characters by starting by 2..
	for (int i = 2; i < size; i++) {
//		..pastes each character in new string..
		aux[j] = v[i];
		j++;
	}

//	..adds an end to the string..
	aux[j] = '\0';

	return aux;
}

void fill_actors_array(ActorsArray * v, FILE * file) {
	printf("..filling actors array..\n");

    char line[255];

    int x = 0;
    while (fgets(line, sizeof(line), file)) {
        x++;

//      ..skips first line of the file 'cause it's the header..
        if(x == 1) continue;

//		..takes tokens between tabs..
        char * token = strtok(line, "\t");
		if(!token) continue;

//		..array to store data as strings..
        char tokens[2][255];

//		..stores the first two columns of the file..
        for(int i = 0; i < 2; i++) {
            if(token) strcpy(tokens[i], token);
            token = strtok(NULL, "\t");
        }

//		..build actor with the collected data..
        Actor * a = (Actor *)malloc(sizeof(Actor));

        char * stripped = strip_actor_id(tokens[0], strlen(tokens[0]));
        a->id = atoi(stripped);
        free(stripped);

        a->name = (char *)malloc(strlen(tokens[1]) + 1);
        strcpy(a->name, tokens[1]);

//		..skips columns that we don't want to reach movies column..
        for(int i = 0; i < 3; i++) token = strtok(NULL, "\t");

        token[strlen(token) - 1] = '\0';
        a->movies = (char *)malloc(strlen(token) + 1);
        strcpy(a->movies, token);

        append_actors_array(v, *a);
    }

	printf("done!\n");
}

void destruct_actors_array(ActorsArray * v) {
    free(v->data);
    free(v);
}