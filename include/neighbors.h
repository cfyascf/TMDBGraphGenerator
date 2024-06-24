#ifndef _NEIGHBORS_H_
#define _NEIGHBORS_H_

#include <stdio.h>
#include "structures.h"

NeighborList * construct_neighbors_list();
Neighbor * construct_neighbor(int movie_id, int movie_index);
void append_neighbors_list(NeighborList * l, Neighbor * n);
void find_neighbors(ActorsArray * a, MoviesArray * m);
void fill_neighbors_list(NeighborList * n, MoviesArray * m, Actor a);
void insert_neighbors(NeighborList * new_l, Movie * m);
void create_graph(ActorsArray * a, MoviesArray * m, FILE * file);

#endif