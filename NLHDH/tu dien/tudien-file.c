#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct _Node
{
    char data[13];
    int page, line;
    struct _Node *next, *down;
} node;

// mergesort
node* merge(node* firstNode, node* secondNode)
{
	node* merged = (node*)malloc(sizeof(node));
	node* temp = (node*)malloc(sizeof(node));

	// merged is equal to temp so in the end we have the top
	// node.
	merged = temp;

	// while either firstNode or secondNode becomes NULL
	while (firstNode != NULL && secondNode != NULL) {

		if (strcmp(firstNode->data, secondNode->data) < 0) {
			temp->down = firstNode;
			firstNode = firstNode->down;
		}

		else {
			temp->down = secondNode;
			secondNode = secondNode->down;
		}
		temp = temp->down;
	}

	// any remaining node in firstNode or secondNode gets
	// inserted in the temp List
	while (firstNode != NULL) {
		temp->down = firstNode;
		firstNode = firstNode->down;
		temp = temp->down;
	}

	while (secondNode != NULL) {
		temp->down = secondNode;
		secondNode = secondNode->down;
		temp = temp->down;
	}
	// return the head of the sorted list
	return merged->down;
}

// function to calculate the middle Element
node* middle(node* head)
{
	node* slow = head;
	node* fast = head->down;

	while (!slow->down && (!fast && !fast->down)) {
		slow = slow->down;
		fast = fast->down->down;
	}
	return slow;
}

// function to sort the given list
node* sort(node* head)
{

	if (head->down == NULL) {
		return head;
	}

	node* mid = (node*)malloc(sizeof(node));
	node* head2 = (node*)malloc(sizeof(node));
	mid = middle(head);
	head2 = mid->down;
	mid->down = NULL;
	// recursive call to sort() hence diving our problem,
	// and then merging the solution
	node* finalhead = merge(sort(head), sort(head2));
	return finalhead;
}

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
    node* last = head;
    while (last->down != NULL)
        last = last->down;
    last->down = current;
    return head;
}

node* findNode(node* head, char data[]){
    node* current = head;
    while (current != NULL)
    {
        if (strcmp(current->data, data) == 0)
            return current;
        current = current->down;
    }
    return NULL;
}

void lowerCase(char data[]){
    if (data[0] < 97)
        data[0] = tolower(data[0]);
}

int main(){
    FILE *fi = NULL;
    FILE *fo = NULL;
    char text[13] = {0};
    fopen_s(&fi, "TestFile.txt", "r");

    node* head = NULL;
    int k = 1;
    while (fscanf(fi, "%s", &text) != EOF)
    {
        if (text[strlen(text)-1] == ',' || text[strlen(text)-1] == '.')
            text[strlen(text)-1] = '\0';
        lowerCase(text);

        node* temp = NULL;
        temp = findNode(head, text);
        if (temp == NULL) {
            head = insertDown(head, text, k / 375 + 1, (k - (k / 375) * 375) / 25 + 1);
        }
        else {
            temp = insertNext(temp, "hehe", k / 375 + 1, (k - (k / 375) * 375) / 25 + 1);
        }
        
        k++;
    }

    head = sort(head);

    // print 
    fopen_s(&fo, "TuDien.txt", "w");
    node* pnext;
    node* pdown = head;
    k = 1;
    while (pdown)
    {
        pnext = pdown;
        fprintf(fo, "%13s : page %-3d line %-2d", pnext->data, pnext->page, pnext->line);
        pnext = pnext->next;
        while (pnext)
        {
            fprintf(fo, ", page %-3d line %-2d", pnext->page, pnext->line);
            pnext = pnext->next;
        }
        fprintf(fo, "\n");
        k++;
        pdown = pdown->down;
    }
    fprintf(fo, "Co tong cong %d tu", k);

    fclose(fi);
    fclose(fo);
    return 0;
}