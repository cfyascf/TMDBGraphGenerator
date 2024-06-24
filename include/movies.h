#ifndef _MOVIES_H_
#define _MOVIES_H_

#include <stdio.h>
#include "structures.h"

MoviesArray * construct_movies_array(int capacity);
char * strip_movie_id(const char * v, int size);
void append_movies_array(MoviesArray * v, Movie m);
void fill_movies_array(MoviesArray * v, FILE * file);
int has_quote(char * string);
int get_movie_index(int movie_id, MoviesArray * v);
Movie * get_movie_by_id(int movie_id, MoviesArray * v);
void destruct_movies_array(MoviesArray *v);

#endif