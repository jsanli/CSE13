#include "universe.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Universe {
    int rows;
    int cols;
    bool **grid;
    bool toroidal;
};

Universe *uv_create(int rows, int cols, bool toroidal) {
    Universe *u = (Universe *) calloc(1, sizeof(Universe));
    u->rows = rows;
    u->cols = cols;
    u->toroidal = toroidal;
    u->grid = (bool **) calloc(rows, sizeof(bool *));
    for (int r = 0; r < rows; r += 1) {
        u->grid[r] = (bool *) calloc(cols, sizeof(bool));
    }
    return u;
}

void uv_delete(Universe *u) {
    for (int r = 0; r < u->rows; r += 1) {
        free(u->grid[r]);
    }
    free(u->grid);
    free(u);
    return;
}

int uv_rows(Universe *u) {
    return u->rows;
}

int uv_cols(Universe *u) {
    return u->cols;
}

void uv_live_cell(Universe *u, int r, int c) {
    u->grid[r][c] = true;
    return;
}

void uv_dead_cell(Universe *u, int r, int c) {
    u->grid[r][c] = false;
    return;
}

bool uv_get_cell(Universe *u, int r, int c) {
    return u->grid[r][c];
}

bool uv_populate(Universe *u, FILE *infile) {
    int r = 0;
    int c = 0;
    while (fscanf(infile, "%d %d\n", &r, &c) != EOF) {
        if (r < 0 || c < 0 || r > u->rows - 1 || c > u->cols - 1) {
            return false;
        }
        u->grid[r][c] = true;
    }
    return true;
}

int uv_census(Universe *u, int r, int c) {
    int count = 0;
    if (u->grid[r][c] == true) {
        count--;
    }
    int rlimit;
    int climit;
    if (u->toroidal == true) {
        if (r == 0 && c == 0) {
            if (u->grid[u->rows - 1][u->cols - 1] == true) {
                count++;
            }
            for (int x = 0; x < 2; x++) {
                if (u->grid[u->rows - 1][x] == true) {
                    count++;
                }
                if (u->grid[x][u->cols - 1] == true) {
                    count++;
                }
            }
            rlimit = r + 1;
            climit = c + 1;
            for (int j = r; j <= rlimit; j++) {
                for (int k = c; k <= climit; k++) {
                    if (u->grid[j][k] == true) {
                        count++;
                    }
                }
            }

        } else if (r == 0 && c == u->cols - 1) {
            if (u->grid[u->rows - 1][0] == true) {
                count++;
            }
            for (int x = 0; x < 2; x++) {
                if (u->grid[u->rows - 1][u->cols - 1 - x] == true) {
                    count++;
                }
                if (u->grid[x][0] == true) {
                    count++;
                }
            }
            c -= 1;
            rlimit = r + 1;
            climit = c + 1;
            for (int j = r; j <= rlimit; j++) {
                for (int k = c; k <= climit; k++) {
                    if (u->grid[j][k] == true) {
                        count++;
                    }
                }
            }

        } else if (r == u->rows - 1 && c == 0) {
            if (u->grid[0][u->cols - 1] == true) {
                count++;
            }
            for (int x = 0; x < 2; x++) {
                if (u->grid[u->rows - 1 - x][u->cols - 1] == true) {
                    count++;
                }
                if (u->grid[0][x] == true) {
                    count++;
                }
            }
            r -= 1;
            rlimit = r + 1;
            climit = c + 1;
            for (int j = r; j <= rlimit; j++) {
                for (int k = c; k <= climit; k++) {
                    if (u->grid[j][k] == true) {
                        count++;
                    }
                }
            }

        } else if (r == u->rows - 1 && c == u->cols - 1) {
            if (u->grid[0][0] == true) {
                count++;
            }
            for (int x = 0; x < 2; x++) {
                if (u->grid[u->rows - 1 - x][0] == true) {
                    count++;
                }
                if (u->grid[0][u->cols - 1 - x] == true) {
                    count++;
                }
            }
            r -= 1;
            c -= 1;
            rlimit = r + 1;
            climit = c + 1;
            for (int j = r; j <= rlimit; j++) {
                for (int k = c; k <= climit; k++) {
                    if (u->grid[j][k] == true) {
                        count++;
                    }
                }
            }

        } else if (r == 0) {
            for (int x = -1; x < 2; x++) {
                if (u->grid[u->rows - 1][c + x] == true) {
                    count++;
                }
            }
            c -= 1;
            rlimit = r + 1;
            climit = c + 2;
            for (int j = r; j <= rlimit; j++) {
                for (int k = c; k <= climit; k++) {
                    if (u->grid[j][k] == true) {
                        count++;
                    }
                }
            }

        } else if (c == 0) {
            for (int x = -1; x < 2; x++) {
                if (u->grid[r + x][u->cols - 1] == true) {
                    count++;
                }
            }
            r -= 1;
            rlimit = r + 2;
            climit = c + 1;
            for (int j = r; j <= rlimit; j++) {
                for (int k = c; k <= climit; k++) {
                    if (u->grid[j][k] == true) {
                        count++;
                    }
                }
            }
        } else if (r == u->rows - 1) {
            for (int x = -1; x < 2; x++) {
                if (u->grid[0][c + x] == true) {
                    count++;
                }
            }
            c -= 1;
            r -= 1;
            rlimit = r + 1;
            climit = c + 2;
            for (int j = r; j <= rlimit; j++) {
                for (int k = c; k <= climit; k++) {
                    if (u->grid[j][k] == true) {
                        count++;
                    }
                }
            }
        } else if (c == u->cols - 1) {
            for (int x = -1; x < 2; x++) {
                if (u->grid[r + x][0] == true) {
                    count++;
                }
            }
            c -= 1;
            r -= 1;
            rlimit = r + 2;
            climit = c + 1;
            for (int j = r; j <= rlimit; j++) {
                for (int k = c; k <= climit; k++) {
                    if (u->grid[j][k] == true) {
                        count++;
                    }
                }
            }

        } else {
            r--;
            c--;
            rlimit = r + 2;
            climit = c + 2;
            for (int j = r; j <= rlimit; j++) {
                for (int k = c; k <= climit; k++) {
                    if (u->grid[j][k] == true) {
                        count++;
                    }
                }
            }
        }
    } else {
        if (r == 0 && c == 0) {
            rlimit = r + 1;
            climit = c + 1;
            for (int j = r; j <= rlimit; j++) {
                for (int k = c; k <= climit; k++) {
                    if (u->grid[j][k] == true) {
                        count++;
                    }
                }
            }

        } else if (r == 0 && c == u->cols - 1) {
            c -= 1;
            rlimit = r + 1;
            climit = c + 1;
            for (int j = r; j <= rlimit; j++) {
                for (int k = c; k <= climit; k++) {
                    if (u->grid[j][k] == true) {
                        count++;
                    }
                }
            }

        } else if (r == u->rows - 1 && c == 0) {
            r -= 1;
            rlimit = r + 1;
            climit = c + 1;
            for (int j = r; j <= rlimit; j++) {
                for (int k = c; k <= climit; k++) {
                    if (u->grid[j][k] == true) {
                        count++;
                    }
                }
            }

        } else if (r == u->rows - 1 && c == u->cols - 1) {
            r -= 1;
            c -= 1;
            rlimit = r + 1;
            climit = c + 1;
            for (int j = r; j <= rlimit; j++) {
                for (int k = c; k <= climit; k++) {
                    if (u->grid[j][k] == true) {
                        count++;
                    }
                }
            }

        } else if (r == 0) {
            c -= 1;
            rlimit = r + 1;
            climit = c + 2;
            for (int j = r; j <= rlimit; j++) {
                for (int k = c; k <= climit; k++) {
                    if (u->grid[j][k] == true) {
                        count++;
                    }
                }
            }

        } else if (c == 0) {
            r -= 1;
            rlimit = r + 2;
            climit = c + 1;
            for (int j = r; j <= rlimit; j++) {
                for (int k = c; k <= climit; k++) {
                    if (u->grid[j][k] == true) {
                        count++;
                    }
                }
            }
        } else if (r == u->rows - 1) {
            c -= 1;
            r -= 1;
            rlimit = r + 1;
            climit = c + 2;
            for (int j = r; j <= rlimit; j++) {
                for (int k = c; k <= climit; k++) {
                    if (u->grid[j][k] == true) {
                        count++;
                    }
                }
            }
        } else if (c == u->cols - 1) {
            c -= 1;
            r -= 1;
            rlimit = r + 2;
            climit = c + 1;
            for (int j = r; j <= rlimit; j++) {
                for (int k = c; k <= climit; k++) {
                    if (u->grid[j][k] == true) {
                        count++;
                    }
                }
            }

        } else {
            r--;
            c--;
            for (int j = 0; j <= 2; j++) {
                for (int k = 0; k <= 2; k++) {
                    if (u->grid[j + r][k + c] == true) {
                        count += 1;
                    }
                }
            }
        }
    }
    return count;
}

void uv_print(Universe *u, FILE *outfile) {
    for (int c = 0; c < u->cols; c++) {
        if (u->grid[0][c] == false) {
            fprintf(outfile, ".");
        } else {
            fprintf(outfile, "o");
        }
    }
    for (int r = 1; r < u->rows; r++) {
        fprintf(outfile, "\n");
        for (int c = 0; c < u->cols; c++) {
            if (u->grid[r][c] == false) {
                fprintf(outfile, ".");
            } else {
                fprintf(outfile, "o");
            }
        }
    }
    fprintf(outfile, "\n");
}
