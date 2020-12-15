
// DataStructues.cpp : Defines the entry point for the console application.
//
#include<stdlib.h>
#include<stdio.h>

///////////////////////////////
// Static Queue
const int StaticQueueSize = 1000; //max length=999
struct StaticQueue { int head, tail, buffer[StaticQueueSize]; };

void StaticQueue_Init(StaticQueue* q)
{
    q->head = q->tail = 0;
}

int StaticQueue_Length(StaticQueue* q)
{
    if (q->head <= q->tail)
        return q->tail - q->head;
    else return StaticQueueSize - q->head + q->tail - 1;
}

bool StaticQueue_Empty(StaticQueue* q)
{
    return q->head == q->tail;
}

bool StaticQueue_Full(StaticQueue* q)
{
    return StaticQueue_Length(q) == StaticQueueSize - 1;
}

bool StaticQueue_Enqueue(StaticQueue* q, int item)
{
    if (StaticQueue_Full(q))
        return false;
    q->buffer[q->tail] = item;
    q->tail++;
    if (q->tail == StaticQueueSize) // wrap around the array boundary
        q->tail = 0;
    return true;
}

bool StaticQueue_Dequeue(StaticQueue* q, int* item)
{
    if (StaticQueue_Empty(q))
        return false;
    *item = q->buffer[q->head];
    q->head++;
    if (q->head == StaticQueueSize) // wrap around the array boundary
        q->head = 0;
    return true;
}
// End of Static Queue
///////////////////////////////

///////////////////////////////
// Static Stack
const int StaticStackSize = 1000; //max length=1000
struct StaticStack { int top, buffer[StaticStackSize]; };

void StaticStack_Init(StaticStack* s)
{
    s->top = 0;
}

int StaticStack_Length(StaticStack* s)
{
    return s->top;
}

bool StaticStack_Empty(StaticStack* s)
{
    return StaticStack_Length(s) == 0;
}

bool StaticStack_Full(StaticStack* s)
{
    return StaticStack_Length(s) == StaticStackSize;
}

bool StaticStack_Push(StaticStack* s, int item)
{
    if (StaticStack_Full(s))
        return false;
    s->buffer[s->top] = item;
    s->top++;
    return true;
}

bool StaticStack_Pop(StaticStack* s, int* item)
{
    if (StaticStack_Empty(s))
        return false;
    s->top--;
    *item = s->buffer[s->top];
    return true;
}
// End of Static Stack
///////////////////////////////

///////////////////////////////
// Static List
const int StaticListSize = 1000; //max length=1000
struct StaticList { int length, buffer[StaticListSize]; };

void StaticList_Init(StaticList* l)
{
    l->length = 0;
}

int StaticList_Length(StaticList* l)
{
    return l->length;
}

bool StaticList_Empty(StaticList* l)
{
    return StaticList_Length(l) == 0;
}

bool StaticList_Full(StaticList* l)
{
    return StaticList_Length(l) == StaticListSize;
}

bool StaticList_Insert(StaticList* l, int item, int index)
{
    int i;

    if (StaticList_Full(l)
        || index < 0
        || index >= StaticListSize
        )
        return false;
    for (i = l->length; i > index; i++) // move items to make room for item at index
    {
        l->buffer[i] = l->buffer[i - 1];
    }
    l->buffer[i] = item; // place item at l->buffer[index]
    l->length++; // inc length
    return true;
}

bool StaticList_Delete(StaticList* l, int* item, int index)
{
    int i;

    if (StaticList_Empty(l)
        || index < 0
        || index >= StaticListSize
        )
        return false;
    *item = l->buffer[index];
    l->length--; // dec length
    for (i = index; i < l->length; i++) // move items to overwrite item at index
    {
        l->buffer[i] = l->buffer[i + 1];
    }
    return true;
}

bool StaticList_Append(StaticList* l, int item)
{
    if (StaticList_Full(l))
        return false;
    l->buffer[l->length] = item; // place item at then end of list
    l->length++; // inc length
    return true;
}

bool StaticList_Enqueue(StaticList* l, int item)
{
    return StaticList_Append(l, item);
}

bool StaticList_Dequeue(StaticList* l, int* item)
{
    return StaticList_Delete(l, item, 0);
}
// End of Static List
///////////////////////////////

///////////////////////////////
// Linked versions
typedef struct _node { int item; _node* next; } node;
typedef node* LinkedList;

///////////////////////////////
// Linked List

node* NewNode()
{
    node* n;

    n = (node*)malloc(sizeof(node));
    n->next = NULL;
    return n;
}

void DeleteNode(node* n)
{
    free(n);
}

void LinkedList_Init(LinkedList* l)
{
    *l = NULL;
}

void DeleteList(LinkedList* l)
{
    node* n = NULL;

    while ((*l)->next != NULL) // delete all nodes
    {
        n = *l;
        *l = (*l)->next;
        DeleteNode(n);
    }
}

int LinkedList_Length(LinkedList l)
{
    int i;

    for (i = 0; l != NULL; i++)
        l = l->next;

    return i;
}

bool LinkedList_Empty(LinkedList l)
{
    return l == NULL;
}

bool LinkedList_Insert(LinkedList* l, int item, int index)
{
    int i;
    node* n = NULL, * p = NULL;

    if (index == 0    // ading at the first position
        || *l == NULL) // ading to an empty list
    {
        n = NewNode();
        n->next = *l;
        n->item = item;
        *l = n;
        return true;
    }
    p = *l;
    for (i = 0; i < index - 1; i++) // go to position index-1
        if (p->next == NULL)
            return false;
        else p = p->next;

    n = NewNode();
    n->next = p->next;
    n->item = item;
    p->next = n;

    return true;
}

bool LinkedList_Delete(LinkedList* l, int* item, int index)
{
    int i;
    node* n = NULL, * p = NULL;

    if (LinkedList_Empty(*l) || index < 0)
        return false;

    for (i = 0; i < index - 1; i++) // go to position index-1
        if (p->next == NULL)
            return false;
        else p = p->next;

    n = p->next;       // n is node at position index
    *item = n->item;   // retrieve item at index
    p->next = n->next; // unlist n (bypass n)
    DeleteNode(n);     // delete n

    return true;
}

void LinkedList_Append(LinkedList* l, int item)
{
    node* n, * p;

    n = NewNode();

    if (*l == NULL) // an empty list
    {
        *l = n;
        return;
    }
    for (p = *l; p->next != NULL; p = p->next) // go to last position
    {
    }
    p->next = n;
    return;
}

void LinkedList_Enqueue(LinkedList* l, int item)
{
    LinkedList_Append(l, item);
}

bool LinkedList_Dequeue(LinkedList* l, int* item)
{
    return LinkedList_Delete(l, item, 0);
}
// End of Linked List
///////////////////////////////

// Linked Queue
struct LinkedQueue { node* head, * tail; int length; };
void LinkedQueue_Init(LinkedQueue* q)
{
    q->head = q->tail = NULL;
    q->length = 0;
}

int LinkedQueue_Length(LinkedQueue* q)
{
    return q->length;
}

bool LinkedQueue_Empty(LinkedQueue* q)
{
    return q->length == 0;
}

void LinkedQueue_Enqueue(LinkedQueue* q, int item)
{
    node* n;

    n = NewNode();
    n->item = item;
    if (LinkedQueue_Empty(q))
    {
        q->head = q->tail = n;
    }
    else
    {
        q->tail->next = n;
        q->tail = n;
    }
    q->length++;
}

bool LinkedQueue_Dequeue(LinkedQueue* q, int* item)
{
    node* n = NULL;

    if (LinkedQueue_Empty(q))
        return false;
    *item = q->head->item;
    n = q->head;
    q->head = q->head->next;
    q->length--;
    DeleteNode(n);
    return true;
}
// End of Linked Queue
///////////////////////////////

// Linked Stack
struct LinkedStack { node* top; int length; };

void LinkedStack_Init(LinkedStack* s)
{
    s->top = NULL;
    s->length = 0;
}

int LinkedStack_Length(LinkedStack* s)
{
    return s->length;
}

bool LinkedStack_Empty(LinkedStack* s)
{
    return s->length == 0;
}

void LinkedStack_Push(LinkedStack* s, int item)
{
    node* n = NULL;

    n = NewNode();
    n->item = item;
    n->next = s->top;
    s->top = n;
    s->length++;
}

bool LinkedStack_Pop(LinkedStack* s, int* item)
{
    node* n = NULL;

    if (LinkedStack_Empty(s))
        return false;
    *item = s->top->item;
    n = s->top;
    s->top = s->top->next;
    DeleteNode(n);
    return true;
}
// End of Linked Stack
///////////////////////////////

int main(int argc, char* argv[])
{
    int i, n, item ;
    StaticQueue queue;
    StaticStack stack;
    StaticList list;
    LinkedQueue lqueue;
    LinkedStack lstack;
    LinkedList llist;

    FILE* fi, * fo;
    const char* InputFileName = "DataStructures_Input.txt",
        * OutputFileName = "DataStructures_Output.txt";

    if (NULL != fopen_s(&fi, InputFileName, "rt"))
    {
        printf_s("Failed to open input file: %s\n", InputFileName);
        printf_s("Press any key to exit...");
        getchar();
        return 1;
    }
    if (NULL != fopen_s(&fo, OutputFileName, "wt"))
    {
        printf_s("Failed to open output file: %s\n", OutputFileName);
        printf_s("Press any key to exit...");
        getchar();
        fclose(fi);
        return 1;
    }

    StaticQueue_Init(&queue);
    StaticStack_Init(&stack);
    StaticList_Init(&list);

    LinkedQueue_Init(&lqueue);
    LinkedStack_Init(&lstack);
    LinkedList_Init(&llist);

    n = 0;

    while (1 == fscanf_s(fi, "%i", &item))
    {
        StaticQueue_Enqueue(&queue, item);
        //LinkedQueue_Enqueue(&lqueue, item);
        n++;
    }
    fclose(fi);
    printf_s("Original data: ( ");
    fprintf_s(fo, "Original data: ( ");
    for (i = 0; i < n; i++)
    {
        StaticQueue_Dequeue(&queue, &item);
        //LinkedQueue_Dequeue(&lqueue, &item);

        printf_s("%i ", item);
        fprintf_s(fo, "%i ", item);

        StaticQueue_Enqueue(&queue, item);
        StaticStack_Push(&stack, item);
        //LinkedQueue_Enqueue(&lqueue, item);
        //LinkedStack_Push(&lstack, item);

    }
    printf_s(")\n");
    fprintf_s(fo, ")\n");
    printf_s("Mirrored data: ( ");
    fprintf_s(fo, "Mirrored data: ( ");
    for (i = 0; i < n; i++)
    {
        StaticStack_Pop(&stack, &item);
        //LinkedStack_Pop(&lstack, &item);

        printf_s("%i ", item);
        fprintf_s(fo, "%i ", item);
    }
    printf_s(")\n");
    fprintf_s(fo, ")\n");
    fclose(fo);
    printf_s("Press any key to end...");
    getchar();

    return 0;
}

/////////////////////////////////////
//// To read and load a dataset
/////////////////////////////////////////
//char buf[4096];
//int nSamples;
//int row, col;
//row=0;
//double Data[10000][200];
//while(!feof(fi))
//     {
//       fgets(buf, sizeof(buf), fi);
//       for(col=0; col<nSamples; col++)
//           sscanf(buf, "%f", &Data[row][col]);
//       row++;
//     }
/////////////////////////////////////
