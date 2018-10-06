#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include "intersect_bst.h"

enum { BUFF = 258 };

typedef struct Node
{
    struct Node *leftNode;
    struct Node *rightNode;

    char *word;
	int count;
} Node;

static Node *newNode(char *word);
static Node *insertNode(Node *input, char *word, int file_num);

Node *getWords(int *files_opened, int argc, char *argv[])
{
    Node *tree = NULL;
	for(int i = 1; i < argc; i++)
	{
		FILE *source;
		if(i == 1 && strcmp(argv[i], "-") == 0)
		{
			source = stdin;	
		}
		else
		{
			source = fopen(argv[i], "r");
		}
		if(!source)
		{
			fprintf(stderr, "%s can't be opened.\n", argv[i]);
			continue; 
		}
		(*files_opened)++;
   		char *line = calloc(BUFF, 1);
		char *word;
	    long unsigned buffSize = BUFF;
	    int isFirst = 0;
    	while(getline(&line, &buffSize, source) != -1)
    	{
			word = strtok(line, " \t\r\n\f\v");
			while(word)
			{
       	 		if(isFirst == 0)
       	 		{
           			tree = insertNode(tree, word, *files_opened);     
           	 		isFirst++;
        		}
        		else
        		{
           			insertNode(tree, word, *files_opened);     
        		}
				word = strtok(NULL, " \t\r\n\f\v");
    		}
		}
		free(line);
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
		return NULL;
    }
	new->count = 1;

    new->leftNode = new->rightNode = NULL;
    return new;
}

static Node *insertNode(Node *tree, char *word, int file_num)
{
    if(tree == NULL)
    {
		if(file_num == 1)
		{
        	return newNode(word);    
		}
		else
		{
			return tree;
		}
    }       
	int compare = ignorePuncCmp(tree->word, word);
    if(compare < 0)
    {
    	tree->rightNode = insertNode(tree->rightNode, word, file_num);
    }
    else if(compare > 0)
    {
        tree->leftNode = insertNode(tree->leftNode, word, file_num);
    }
	else
	{
		if(file_num != 1 && tree->count == file_num - 1)
		{
			tree->count = file_num;
		}

	}
    return tree;    
}

void printTree(Node *tree, int files_opened)
{
    if(tree != NULL)
    {
        printTree(tree->leftNode, files_opened);
		if(files_opened != 1 && tree->count == files_opened)
		{
        	printf("%s\n", tree->word);
		}
        printTree(tree->rightNode, files_opened);     
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

int ignorePuncCmp(const char *tree_word, const char *word)
{
	int return_code = 0;
	bool symbols = false;
	char *tmp_a = calloc(strlen(tree_word) + 1, 1);
	char *tmp_b = calloc(strlen(word) + 1, 1);
	if(tmp_a == NULL || tmp_b == NULL)
	{
		fprintf(stderr, "Unable to allocate memory.\n");
		return -1;
	}
	stripPunct(tree_word, tmp_a, &symbols);
	stripPunct(word, tmp_b, &symbols);
	return_code = strcasecmp(tmp_a, tmp_b);
	if(symbols == true)
	{
		return_code = -1;
	}
	free(tmp_a);
	free(tmp_b);
		
	return return_code;
}

void stripPunct(const char *word, char *tmp, bool *symbols)
{
	int start = 0;
	int end = strlen(word);
	int j = 0;
	while(ispunct(word[j]) != 0)
	{
		j++;
	}
	start = j;
	j = end;
	while(j >= 0 && isalpha(word[j]) == 0)
	{
		j--;
	}
	end = j;
	if(end - start < 0)
	{
		*symbols = true;
	}
	for(int i = 0; start <= end; i++)
	{
		tmp[i] = word[start++];	
	}

}
