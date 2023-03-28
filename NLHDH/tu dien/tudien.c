#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Node
{
    char data[12];
    int page, line;
    struct _Node *next, *down;

} node;

node* newNode(char data[], int page, int line){
    node* p = NULL;
    p = (node*)malloc(sizeof(node));
    strcpy(p->data, data);
    p->page = page;
    p->line = line;
    p->next = NULL;
    p->down = NULL;
    return p;
}

void printList(node* head){
    node* pnext;
    node* pdown = head;
    while (pdown)
    {
        pnext = pdown;
        while (pnext)
        {
            printf("%s ",pnext->data);
            pnext = pnext->next;
        }
        printf("\n");
        pdown = pdown->down;
    }
}




int main(){
    FILE *fp = NULL;
    char text[12] = {0};
    fopen_s(&fp, "TestFile.txt", "r");

    // int k = 1;
    // while (fscanf(fp, "%s", &text) != EOF && k < 10)
    // {
    //     if (text[strlen(text)-1] == ',' || text[strlen(text)-1] == '.')
    //         text[strlen(text)-1] = '\0';
    //     strlwr(text);
    //     if (strlen(text) > k)
    //     {
    //         k = strlen(text);
    //     }
        
    //     printf("%s  ", text);
    // }

    // *** test ***




    printList(aa);

    fclose(fp);
    return 0;
}