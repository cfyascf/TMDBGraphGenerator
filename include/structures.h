#ifndef _STRUCTURES_H_
#define _STRUCTURES_H_

typedef struct Actor
{
    int id;
    char * name;
    char * movies;

} Actor;

typedef struct ActorsArray
{
    int size;
    int capacity;
    Actor * data;

} ActorsArray;

typedef struct Movie
{
    int id;
    char * title;
    struct NeighborList * neighbors;

} Movie;

typedef struct MoviesArray
{
    int size;
    int capacity;
    Movie * data;

} MoviesArray;

typedef struct Neighbor
{
    int movie_id;
    int movie_index;
    struct Neighbor * next;

} Neighbor;

typedef struct NeighborList
{
    int size;
    Neighbor * head;

} NeighborList;

#endif
