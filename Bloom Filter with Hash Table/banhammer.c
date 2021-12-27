#include "bf.h"
#include "bv.h"
#include "hash.h"
#include "ll.h"
#include "node.h"
#include "parser.h"
#include "speck.h"

#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define WORD    "[a-zA-z0-9_]+(('|-)[a-zA-Z0-9_]+)*"
#define BF_SIZE 1 << 20
#define HT_SIZE 10000
#define OPTIONS "hfm"

int main(int argc, char **argv) {
    bool mtf = false;
    int opt = 0;
    uint32_t hash_size = HT_SIZE;
    uint32_t bloom_size = BF_SIZE;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h': hash_size = atoi(optarg); break;
        case 'f': bloom_size = atoi(optarg); break;
        case 'm': mtf = true; break;
        }
    }

    BloomFilter *bf = bf_create(bloom_size);
    if (!bf) {
        fprintf(stderr, "%s\n", "Empty Bloomfilter");
        return 1;
    }

    HashTable *ht = ht_create(hash_size, mtf);
    if (!ht) {
        fprintf(stderr, "%s\n", "Empty Hash Table");
        return 1;
    }

    char badspeak[14395];
    char oldspeak[285];
    char newspeak[285];

    FILE *infile_one = fopen("badspeak.txt", "r");
    while (fscanf(infile_one, "%s\n", badspeak) != EOF) {
        bf_insert(bf, badspeak);
        ht_insert(ht, badspeak, NULL);
    }

    FILE *infile_two = fopen("newspeak.txt", "r");
    while (fscanf(infile_two, "%s %s\n", oldspeak, newspeak) != EOF) {
        bf_insert(bf, oldspeak);
        ht_insert(ht, oldspeak, newspeak);
    }

    LinkedList *forbidden = ll_create(mtf);
    LinkedList *corrected = ll_create(mtf);

    regex_t re;
    if (regcomp(&re, WORD, REG_EXTENDED)) {
        fprintf(stderr, "Failed to compile regex.\n");
        return 1;
    }

    char *word = NULL;
    char *word_lower = NULL;
    char *upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char *lower = "abcdefghijklmnopqrstuvwxyz";
    Node *temp = NULL;

    while ((word = next_word(stdin, &re)) != NULL) {
        word_lower = word;
        for (uint64_t j = 0; j < strlen(word); j++) {
            for (uint64_t a = 0; a < strlen(upper); a++) {
                if (word[j] == upper[a]) {
                    word_lower[j] = lower[a];
                }
            }
        }
        temp = ht_lookup(ht, word_lower);
        if (bf_probe(bf, word_lower) == 1 && temp != NULL) {
            if (temp->newspeak == NULL) {
                ll_insert(forbidden, temp->oldspeak, NULL);
            } else {
                ll_insert(corrected, temp->oldspeak, temp->newspeak);
            }
        }
        word_lower = "";
    }

    clear_words();
    regfree(&re);

    if (ll_length(forbidden) != 0 && ll_length(corrected) != 0) {
        printf("%s\n\n%s\n%s\n%s\n%s\n%s\n\n%s\n\n", "Dear Comrade,",
            "You have chosen to use degenerate words that may cause hurt",
            "feelings or cause your comrades to think unpleasant thoughts.",
            "This is doubleplus bad. To correct your wrongthink and",
            "preserve community consensus we will be sending you to joycamp",
            "administered by Medellin's Miniluv. Beware of the hippos.", "Your errors:");
        ll_print(forbidden);
        printf("\n%s\n\n", "Think of these words on you vacation!");
        ll_print(corrected);
    } else if (ll_length(forbidden) != 0) {
        printf("%s\n\n%s\n%s\n%s\n%s\n%s\n\n%s\n\n", "Dear Comrade,",
            "You have chosen to use degenerate words that may cause hurt",
            "feelings or cause your comrades to think unpleasant thoughts.",
            "This is doubleplus bad. To correct your wrongthink and",
            "preserve community consensus we will be sending you to joycamp",
            "administered by Medellin's Miniluv. Beware of the hippos.", "Your errors:");
        ll_print(forbidden);
    } else if (ll_length(corrected) != 0) {
        printf("%s\n\n%s\n%s\n%s\n\n", "Dear Comrade,",
            "Submitting your text helps to preserve feelings and prevent",
            "badthink. Some of the words that you used are not goodspeak.",
            "The list shows how to turn the oldspeak words into newspeak.");
        ll_print(corrected);
    }

    ll_delete(&forbidden);
    ll_delete(&corrected);
    bf_delete(&bf);
    ht_delete(&ht);
    fclose(infile_one);
    fclose(infile_two);

    return 0;
}
