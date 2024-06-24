#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/movies.h"
#include "../include/structures.h"

MoviesArray * construct_movies_array(int capacity)
{
    MoviesArray * v = (MoviesArray *)malloc(sizeof(MoviesArray));
    v->size = 0;
    v->capacity = capacity;
    v->data = (Movie *)malloc(capacity * sizeof(Movie));

    return v;
}

void append_movies_array(MoviesArray * v, Movie m)
{
    if (!v) return;

    if (v->size == v->capacity - 1)
    {
        v->capacity += v->capacity / 2;
        v->data = (Movie *)realloc(v->data, v->capacity * sizeof(m));
    }

    ((Movie *)v->data)[v->size] = m;
    v->size++;
}

//..same strip as the actors one..
char * strip_movie_id(const char * v, int size)
{
	char * aux = (char *)malloc(size - 1 * sizeof(char));

	int j = 0;
	for (int i = 2; i < size; i++)
	{
		aux[j] = v[i];
		j++;
	}
	aux[j] = '\0';

	return aux;
}

void fill_movies_array(MoviesArray * v, FILE * file) {
	printf("..filling movies array..\n");

    char line[255];
    int x = 0;
    while (fgets(line, sizeof(line), file))
    {
        x++;

//		..skips first column..
        if(x == 1) continue;

        char * token = strtok(line, "\t");
        char tokens[3][255];

//		..stores first 3 columns..
        for(int i = 0; i < 3; i++)
        {
			if(token) strcpy(tokens[i], token);
            token = strtok(NULL, "\t");
        }

//		..if it's not classified as movie or has quotes in title, skips line..
        if(!strstr(tokens[1], "movie") || has_quote(tokens[2]) == 1)
        {
            continue;
        }

//		..build movie with the collected data..
        Movie * m = (Movie *)malloc(sizeof(Movie));

        char * stripped = strip_movie_id(tokens[0], strlen(tokens[0]));
        m->id = atoi(stripped);
        free(stripped);

        m->title = (char *)malloc(strlen(tokens[2]) + 1);
        strcpy(m->title, tokens[2]);

        m->neighbors = NULL;

        append_movies_array(v, * m);
    }

	printf("done!\n");
}

int has_quote(char * string)
{
	int size = strlen(string);

//	..looks for single and double quotes in string..
	for(int i = 0; i < size; i++)
	{
		if(string[i] == '\'' || string[i] == '\"') {
			return 1;
		}
	}

	return 0;
}

int get_movie_index(int movie_id, MoviesArray * v)
{
    int e = -1;
    int size = v->size;

//	..binary search to look for movie index in movie array..
    while(e < size - 1)
    {
        int index = (e + size) / 2;
        Movie m = v->data[index];
        if(m.id < movie_id) e = index;
        else size = index;
    }

    return size;
}

Movie * get_movie_by_id(int movie_id, MoviesArray * v)
{
	int e = -1;
	int size = v->size;

//	 ..binary search to look for movie index in movie array..
	while(e < size - 1)
	{
		int index = (e + size) / 2;
		Movie * m = &v->data[index];
		if(m->id < movie_id) e = index;
		else size = index;
	}

//	..checks if the movie in the found index matches the id..
	if(size < v->size && v->data[size].id == movie_id)
	{
		return &v->data[size];
	}

	return NULL;
}

void destruct_movies_array(MoviesArray * v)
{
    free(v->data);
    free(v);
}