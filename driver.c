#include <stdio.h>
#include "intersect_bst.h"


int main(int argc, char *argv[])
{
    if(argc > 2)
    {
        Node *tree = getWords(argc, argv);
        printTree(tree);
//        printf("Depth: %d\n", maxDepth);
//        printf("Rebalance: %d\n", rebalance);
    }
	else
	{
		printf("Usage: %s filename1 filename2 [filename 3 ...]\n", argv[0]);
	}
}

