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
static Node *insertNode(Node *input, char *word);

static int curDepth = 0;
static int maxDepth = 0;
//static int rebalance = 0;

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
           			tree = insertNode(tree, word);                
           	 		isFirst++;
        		}
        		else
        		{
           			insertNode(tree, word);                       
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
    printf("Node Value: %s\n", new->word);
    return new;
}

static Node *insertNode(Node *tree, char *word)
{
    if(tree == NULL)
    {
        return newNode(word);    
    }       
    if(strcmp(tree->word, word) < 0)
    {
        printf("right\n");
		/*
        curDepth++;
        if(tree->rightNode != NULL && tree->rightNode->rightNode != NULL && 
                tree->rightNode->leftNode == NULL)
         {
             rebalance++;
             if(tree->rightNode->rightNode->value < num)
             {
                char *tmp = tree->rightNode->word;
                tree->rightNode->value = tree->rightNode->rightNode->value;
                tree->rightNode->leftNode = tree->rightNode->rightNode;
                tree->rightNode->rightNode = NULL;
                tree->rightNode->leftNode->value = tmp; 
             }
             else
             {
                int tmp = tree->rightNode->value;
                tree->rightNode->value = num;
                num = tmp;
             }
         }
		 */
         tree->rightNode = insertNode(tree->rightNode, word);
    }
    else if(strcmp(tree->word, word) > 0)
    {
        printf("left\n");
		/*
        curDepth++;
        if(tree->leftNode != NULL && tree->leftNode->leftNode != NULL && 
                tree->leftNode->rightNode == NULL)
        {
            rebalance++;
            if(tree->leftNode->leftNode->value > num)
            {
                int tmp = tree->leftNode->value;
                tree->leftNode->value = tree->leftNode->leftNode->value;
                tree->leftNode->rightNode = tree->leftNode->leftNode;
                tree->leftNode->leftNode = NULL;
                tree->leftNode->rightNode->value = tmp;
            }
            else
            {
                int tmp = tree->leftNode->value;
                tree->leftNode->value = num;
                num = tmp;
            }
        }
		*/
        tree->leftNode = insertNode(tree->leftNode, word);
    }
	else
	{
		tree->count++;
	}
	
    if(curDepth > maxDepth)
    {
        maxDepth = curDepth;
    }       
    curDepth = 0;
    return tree;    
}

void printTree(Node *tree)
{
    if(tree != NULL)
    {
        printTree(tree->leftNode);
        printf("Word: %s Count: %d\n", tree->word, tree->count);
        printTree(tree->rightNode);     
    }       
    free(tree);
}
