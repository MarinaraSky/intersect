#include <stdio.h>
#include "intersect_bst.h"


int main(int argc, char *argv[])
{
    FILE *source;
    if(argc > 1)
    {
        source = fopen(argv[1], "r");   
        if(source == NULL)
        {
            printf("Cannont Find File %s\n", argv[1]);
        }
        Node *tree = getNums(source);
        printTree(tree);
//        printf("Depth: %d\n", maxDepth);
 //       printf("Rebalance: %d\n", rebalance);
    }
}

