#ifndef INTERSECT_BST_H
#define INTERSECT_BST_H

#include <stdbool.h>

typedef struct Node Node;

Node *getWords(int *files_opened, int argc, char *argv[]);
int ignorePuncCmp(const char *tree_word, const char *word);
void stripPunct(const char *word, char *tmp, bool *symbols);
void printTree(Node *tree, int argc);
void destroyTree(Node *tree);

#endif
