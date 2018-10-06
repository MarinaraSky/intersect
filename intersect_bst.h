#ifndef INTERSECT_BST_H
#define INTERSECT_BST_H

#include <stdbool.h>

/* Node for BST */
typedef struct Node Node;

/* Taking a list of arguments, opens the first file and creates
 * a BST. Subsequent files are compared to the BST and count is 
 * updated if appropriate */
Node           *getWords(
    int *files_opened,
    int argc,
    char *argv[]);

/* Takes a word and a buffer for a temp variable to use for
 * removing leading and trailing punctuation */
int             ignorePuncCmp(
    const char *tree_word,
    const char *word);

/* Function that does the stripping of punctuation for ignorePuncCmp */
void            stripPunct(
    const char *word,
    char *tmp,
    bool * symbols);

/* Generic BST Print function */
void            printTree(
    Node * tree,
    int argc);

/* Generic BST Destroy function */
void            destroyTree(
    Node * tree);

#endif
