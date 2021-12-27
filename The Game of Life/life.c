#include "universe.h"

#include <ncurses.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OPTIONS "i:o:tsn:"
#define DELAY   50000

int main(int argc, char **argv) {
    int opt = 0;
    int g = 100;
    bool t = false;
    bool s = false;
    FILE *infile = stdin;
    FILE *outfile = stdout;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'i': infile = fopen(optarg, "r"); break;
        case 'o':
            outfile = fopen(optarg, "w");
            /*if(outfile == NULL){
				stderr;
				exit;*/
            break;
        case 't': t = true; break;
        case 's': s = true; break;
        case 'n': g = atoi(optarg); break;
        }
    }

    int rows = 0;
    int cols = 0;
    fscanf(infile, "%d %d\n", &rows, &cols);
    Universe *a = uv_create(rows, cols, t);
    Universe *b = uv_create(rows, cols, t);
    uv_populate(a, infile);
    if (s != true) {
        initscr();
        noecho();
        curs_set(FALSE);
    }
    int counter = 0;
    for (int x = 0; x < g; x++) {
        if (s != true) {
            clear();
        }
        for (int y = 0; y < rows; y++) {
            for (int z = 0; z < cols; z++) {
                counter = uv_census(a, y, z);
                /*fprintf(outfile,"%d", counter);*/
                if (uv_get_cell(a, y, z) == true && (counter == 2 || counter == 3)) {
                    uv_live_cell(b, y, z);
                    if (s != true) {
                        mvprintw(y, z, "o");
                    }
                } else if (uv_get_cell(a, y, z) == false && counter == 3) {
                    uv_live_cell(b, y, z);
                    if (s != true) {
                        mvprintw(y, z, "o");
                    }
                } else {
                    uv_dead_cell(b, y, z);
                }
            }
        }
        Universe *temp = a;
        a = b;
        b = temp;
        if (s != true) {
            refresh();
            usleep(DELAY);
        }
    }
    if (s != true) {
        endwin();
    }
    uv_print(a, outfile);
    uv_delete(a);
    uv_delete(b);
    return 0;
}
