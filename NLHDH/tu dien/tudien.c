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

node* insertNext(node* head, char data[], int page, int line){
    node* current = newNode(data, page, line);
    if (head == NULL) return current;
    node* last = head;
    while (last->next != NULL)
        last = last->next;
    last->next = current;
    return head;
}

node* insertDown(node* head, char data[], int page, int line){
    node* current = newNode(data, page, line);
    if (head == NULL) return current;
    head->down = current;
    return current;
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

node* findNode(node* head, char data[]){
    node* current = head;
    while (current != NULL)
    {
        if (current->data == data)
            return current;
        current = current->down;
    }
    return NULL;
}

int main(){
    FILE *fp = NULL;
    char text[12] = {0};
    fopen_s(&fp, "TestFile.txt", "r");

    node* head = NULL, head2 = NULL;
    int k = 1;
    while (fscanf(fp, "%s", &text) != EOF && k < 10)
    {
        if (text[strlen(text)-1] == ',' || text[strlen(text)-1] == '.')
            text[strlen(text)-1] = '\0';
        strlwr(text);

        if (findNode(head, text) == NULL)
        {
            
        }
        
        k++;
    }

    // *** test ***
    // node* aa = newNode("A", 1, 1);
    // node* ab = newNode("A", 7, 8);
    // node* ac = newNode("A", 1, 1);
    // node* ba = newNode("B", 5, 2);
    // node* bb = newNode("B", 1, 1);
    // node* ca = newNode("C", 1, 1);
    // aa->next = ab; 
    // ab->next = ac;
    // aa->down = ba;
    // ba->next = bb;
    // ba->down = ca;



    printList(aa);

    fclose(fp);
    return 0;
}