#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/neighbors.h"
#include "../include/movies.h"

NeighborList * construct_neighbors_list()
{
    NeighborList * l = (NeighborList *)malloc(sizeof(NeighborList));
    l->size = 0;
    l->head = NULL;

    return l;
}

Neighbor * construct_neighbor(int movie_id, int movie_index)
{
    Neighbor * n = (Neighbor *)malloc(sizeof(Neighbor));
    n->movie_id = movie_id;
    n->movie_index = movie_index;
    n->next = NULL;

    return n;
}

void append_neighbors_list(NeighborList * l, Neighbor * n)
{
    if(!l->head && l->size == 0)
    {
        l->head = n;
        l->size = 1;
        n->next = NULL;
        return;
    }

    Neighbor * aux = l->head;
	if(!aux) return;

    while(aux->next != NULL)
    {
        aux = aux->next;
    }

    aux->next = n;
    n->next = NULL;
    l->size++;
}

void find_neighbors(ActorsArray * a, MoviesArray * m)
{
    for(int i = 0; i < a->size; i++)
    {
        Actor aux = a->data[i];
        NeighborList * n = construct_neighbors_list();

//		..creates linked list with the selected actor's movies..
        fill_neighbors_list(n, m, aux);

//		..for each movie in the new neighbors linked list..
        Neighbor * node = n->head;
        while(node != NULL) {
            Movie * movie = get_movie_by_id(node->movie_id, m);

            if(movie == NULL)
            {
                node = node->next;
                continue;
            }

//			..if the movie doesn't have a list of neighbors yet..
            if(movie->neighbors == NULL)
            {
//				..constructs list and inserts itself in each movie..
                movie->neighbors = construct_neighbors_list();
                insert_neighbors(n, movie);
                node = node->next;
                continue;
            }

            insert_neighbors(n, movie);
            node = node->next;
        }
    }
}

void fill_neighbors_list(NeighborList * n, MoviesArray * m, Actor a)
{
//	..takes tokens in between commas..
    char * token = strtok(a.movies, ",");
    while(token)
    {
        int size = strlen(token);
        char * string_id = strip_movie_id(token, size);
        int id = atoi(string_id);

        int index = get_movie_index(id, m);

//		..builds neighbor with collected data..
        Neighbor * node = construct_neighbor(id, index);
        append_neighbors_list(n, node);

        token = strtok(NULL, ",");
    }
}

//..its necessary 'cause it needs to create a new neighbor with
//the same data for each movie, otherwise, when a neighbor's data
//is updated in the list of one movie, it will be updated in all
// movies' lists..
void insert_neighbors(NeighborList * new_l, Movie * m)
{

//	..if the neighbors list is empty..
    if(m->neighbors->head == NULL)
    {
//		..gives a head to the list..
        Neighbor * aux = new_l->head;
        while(aux != NULL)
        {
//			..skips if the movie is already inside the list..
            if(aux->movie_id == m->id)
            {
                aux = aux->next;
                continue;
            }

//			..created new neighbor with the data..
            Neighbor * n = construct_neighbor(aux->movie_id, aux->movie_index);

//			..inserts in movie's neighbor list..
            append_neighbors_list(m->neighbors, n);
			printf("inserted neighbor: %d\n", n->movie_id);
            aux = aux->next;
        }

        return;
    }

//	..starts to run the list from the head..
    Neighbor * aux1 = new_l->head;
    while(aux1 != NULL)
    {
        int found = 0;
        Neighbor * aux2 = m->neighbors->head;

//		..runs the neighbors list inside the movie from the head..
        while(aux2 != NULL)
        {
//			..checks if the movie is already inside the list..
            if(aux2->movie_id == aux1->movie_id || aux1->movie_id == m->id)
            {
                found = 1;
                break;
            }

            aux2 = aux2->next;
        }

//		..inserts in list if not found..
        if(!found)
        {
            append_neighbors_list(m->neighbors, aux1);
            found = 0;
        }

        aux1 = aux1->next;
    }
}

void create_graph(ActorsArray * a, MoviesArray * m, FILE * file)
{
	printf("..creating graph..\n");

	find_neighbors(a, m);

//	..writes this command that indicates the creation of a graph in dot language..
	fprintf(file, "graph { concentrate=true\n");

//	..for each movie of the list..
	for(int i = 0; i < m->size / 2; i++)
	{
		Movie movie = m->data[i];
		if(!movie.neighbors) continue;

//		..for each neighbor inside the movie's neighbors' list..
		Neighbor * n = movie.neighbors->head;
		while(n)
		{
			Movie * m_neighbor = get_movie_by_id(n->movie_id, m);
			if(!m_neighbor)
			{
				n = n->next;
				continue;
			}

//			..writes the name of the movie and its neighbor..
			fprintf(file, "\"%s\"--\"%s\";\n", movie.title, m_neighbor->title);
			n = n->next;
		}
	}

//	..ends command..
	fprintf(file, "}");
	fclose(file);

	printf("graph created,\n");
	printf("your .dot file is ready!\n");
}