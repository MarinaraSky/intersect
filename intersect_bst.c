#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "intersect_bst.h"

enum { BUFF = 256 };

typedef struct Node
{
    struct Node *leftNode;
    struct Node *rightNode;

    char *word;
	int count;
} Node;

static Node *newNode(char *word);
static Node *insertNode(Node *input, char *word, int file_num);

Node *getWords(int argc, char *argv[])
{
    Node *tree = NULL;
	for(int i = 1; i < argc; i++)
	{
		FILE *source = fopen(argv[i], "r");
   		char line[BUFF];
		char *word;
	    int buffSize = BUFF;
	    int isFirst = 0;
    	while(fgets(line, buffSize, source) != NULL)
    	{
			word = strtok(line, " \t\r\n\f\v");
			while(word)
			{
       	 		if(isFirst == 0)
       	 		{
           			tree = insertNode(tree, word, i);                
           	 		isFirst++;
        		}
        		else
        		{
           			insertNode(tree, word, i);                       
        		}
				word = strtok(NULL, " \t\r\n\f\v");
    		}
		}
    	fclose(source);
	}
    return tree;
}


static Node *newNode(char *word)
{
    Node *new = malloc(sizeof(Node));       
    new->word = strdup(word);
    if(!new || !new->word)
    {
        printf("Error\n");
    }
	new->count = 1;

    new->leftNode = new->rightNode = NULL;
    return new;
}


static Node *insertNode(Node *tree, char *word, int file_num)
{
    if(tree == NULL)
    {
        return newNode(word);    
    }       
    if(strcasecmp(tree->word, word) < 0)
    {
         tree->rightNode = insertNode(tree->rightNode, word, file_num);
    }
    else if(strcasecmp(tree->word, word) > 0)
    {
        tree->leftNode = insertNode(tree->leftNode, word, file_num);
    }
	else
	{
		if(tree->count < file_num)
		{
			tree->count++;
		}
	}
    return tree;    
}

void printTree(Node *tree, int argc)
{
    if(tree != NULL)
    {
        printTree(tree->leftNode, argc);
		if(tree->count == argc - 1)
		{
        	printf("%s\n", tree->word);
		}
        printTree(tree->rightNode, argc);     
    }       
}

void destroyTree(Node *tree)
{
    if(tree != NULL)
    {
        destroyTree(tree->leftNode);
		free(tree->word);
        destroyTree(tree->rightNode);     
		free(tree);
    }       
}
