#ifndef _ACTORS_H_
#define _ACTORS_H_

#include <stdio.h>
#include "structures.h"

ActorsArray * construct_actors_array(int capacity);
char * strip_actor_id(const char * v, int size);
void append_actors_array(ActorsArray * v, Actor a);
void fill_actors_array(ActorsArray * v, FILE * file);
void destruct_actors_array(ActorsArray * v);

#endif