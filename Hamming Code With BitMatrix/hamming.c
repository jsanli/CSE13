#include "hamming.h"

#include "bm.h"

#include <stdio.h>
#include <stdlib.h>

BitMatrix *G;
BitMatrix *H_t;

/*typedef enum ham_rc{
	HAM_ERR = -1,
	HAM_OK = 0,
	HAM_ERR_OK = 1
} ham_rc;*/

ham_rc ham_init(void) {
    G = bm_create(4, 8);
    H_t = bm_create(8, 4);
    bm_set_bit(G, 0, 0);
    bm_set_bit(G, 1, 1);
    bm_set_bit(G, 2, 2);
    bm_set_bit(G, 3, 3);
    bm_set_bit(G, 0, 5);
    bm_set_bit(G, 0, 6);
    bm_set_bit(G, 0, 7);
    bm_set_bit(G, 1, 4);
    bm_set_bit(G, 1, 6);
    bm_set_bit(G, 1, 7);
    bm_set_bit(G, 2, 4);
    bm_set_bit(G, 2, 5);
    bm_set_bit(G, 2, 7);
    bm_set_bit(G, 3, 4);
    bm_set_bit(G, 3, 5);
    bm_set_bit(G, 3, 6);
    bm_set_bit(H_t, 4, 0);
    bm_set_bit(H_t, 5, 1);
    bm_set_bit(H_t, 6, 2);
    bm_set_bit(H_t, 7, 3);
    bm_set_bit(H_t, 0, 1);
    bm_set_bit(H_t, 0, 2);
    bm_set_bit(H_t, 0, 3);
    bm_set_bit(H_t, 1, 0);
    bm_set_bit(H_t, 1, 2);
    bm_set_bit(H_t, 1, 3);
    bm_set_bit(H_t, 2, 0);
    bm_set_bit(H_t, 2, 1);
    bm_set_bit(H_t, 2, 3);
    bm_set_bit(H_t, 3, 0);
    bm_set_bit(H_t, 3, 1);
    bm_set_bit(H_t, 3, 2);
    return HAM_OK;
}

void ham_destroy(void) {
    bm_delete(&G);
    bm_delete(&H_t);
    free(G);
    free(H_t);
    return;
}

ham_rc ham_encode(uint8_t data, uint8_t *code) {
    uint8_t binc[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    uint8_t final[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    int counter = 0;
    while (data > 0) {
        binc[counter] = data % 2;
        data /= 2;
        counter++;
    }
    if (bm_get_bit(G, 0, 0) == 0) {
        return HAM_ERR;
    } else {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 4; j++) {
                final[i] += binc[j] * bm_get_bit(G, j, i);
            }
        }
        for (int z = 0; z < 8; z++) {
            final[z] %= 2;
        }
        /*		for (int x = 7; x >= 0; x--){
			printf("%d", binc[x]);
		}
		printf("\n");
		for (int x = 7; x >= 0; x--){
			printf("%d", final[x]);
		}
		printf("\n");*/
        uint8_t decc = 0;
        uint8_t power = 1;
        int q = 0;
        for (int z = 0; z < 8; z++) {
            q = z;
            if (final[z] == 1) {
                while (q > 0) {
                    power *= 2;
                    q--;
                }
                decc += power;
            }
            power = 1;
        }
        //	printf("%d", decc);
        *code = decc;
        //	printf("\n\n");
        return HAM_OK;
    }
}

ham_rc ham_decode(uint8_t code, uint8_t *data) {
    //printf("%s %u\n", "data:", *data);
    uint8_t binc[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    uint8_t final[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    int counter = 0;
    uint8_t lookup[16] = { 0, 4, 5, HAM_ERR, 6, HAM_ERR, HAM_ERR, 3, 7, HAM_ERR, HAM_ERR, 2,
        HAM_ERR, 1, 0, HAM_ERR };
    while (code > 0) {
        binc[counter] = code % 2;
        code /= 2;
        counter++;
    }
    if (bm_get_bit(H_t, 0, 0) == 1) {
        return HAM_ERR;
    } else {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 8; j++) {
                final[i] += binc[j] * bm_get_bit(H_t, j, i);
            }
        }
        for (int z = 0; z < 4; z++) {
            final[z] %= 2;
        }
        uint8_t decc = 0;
        uint8_t power = 1;
        int q = 0;
        for (int z = 0; z < 4; z++) {
            q = z;
            if (final[z] == 1) {
                while (q > 0) {
                    power *= 2;
                    q--;
                }
                decc += power;
            }
            power = 1;
        }
        if (decc == 0) {
            *data = decc;
            return HAM_OK;
        } else if (decc == 1 || decc == 2 || decc == 4 || decc == 7 || decc == 8 || decc == 11
                   || decc == 13 || decc == 14) {
            final[lookup[decc]] = (final[lookup[decc]] + 1) % 2;
            int tdecc = 0;
            power = 1;
            for (int z = 0; z < 4; z++) {
                q = z;
                if (final[z] == 1) {
                    while (q > 0) {
                        power *= 2;
                        q--;
                    }
                    tdecc += power;
                }
                power = 1;
            }
            *data = tdecc;
            return HAM_ERR_OK;
        } else {
            *data = decc;
            //		printf("%u\n", *data);
            return HAM_ERR;
        }
    }
}
