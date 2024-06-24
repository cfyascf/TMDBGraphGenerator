#include "../include/actors.h"
#include "../include/movies.h"
#include "../include/neighbors.h"

int main() {
    FILE * file_a = fopen("name.basics.tsv", "r");
    FILE * file_m = fopen("title.basics.tsv", "r");
	FILE * file_g = fopen("input.dot", "w");

    ActorsArray * a = construct_actors_array(3);
    MoviesArray * m = construct_movies_array(3);

    fill_actors_array(a, file_a);
    fill_movies_array(m, file_m);
	create_graph(a, m, file_g);
    destruct_actors_array(a);
    destruct_movies_array(m);

    return 0;
}

