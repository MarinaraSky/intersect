#include <stdio.h>
#include "intersect_bst.h"


int
main(
    int argc,
    char *argv[])
{
    if (argc > 2)
    {
        int             files_opened = 0;
        Node           *tree = getWords(&files_opened, argc, argv);

        printTree(tree, files_opened);
        destroyTree(tree);
    }
    else
    {
        printf("Usage: %s filename1 filename2 [filename 3 ...]\n", argv[0]);
    }
}
