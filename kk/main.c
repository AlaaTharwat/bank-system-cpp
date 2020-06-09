#include <stdio.h>
#include <stdlib.h>
typedef struct Node Node;
typedef struct queue queue;
typedef struct client client;




struct client{
    int code;
    int arrivalTime;
    int transactionTime;
};



struct Node{
    client data;
    Node *next;
};



struct queue
{
    int count;
    int numberOfCustomers;
    int totalWait;
    Node *head;
    Node *tail;
};

void initialize(queue *q)
{
    q->count = 0;
    q->numberOfCustomers =0;
    q->totalWait = 0;
    q->head = NULL;
    q->tail = NULL;
}

int isempty(queue *q)
{
    return (q->tail == NULL);
}

void enqueue(queue *q, client value)
{
    Node * node = (Node*) malloc(sizeof(Node));
    node->data = value;
    node->next = NULL;
    if(!isempty(q))
    {
        q->tail->next = node;
        q->tail = node;
    }
    else
    {
        q->head = q->tail = node;
    }
    q->count++;
}

client dequeue(queue *q)
{
    Node *tmp;
    client n = q->head->data;
    tmp = q->head;
    q->head = q->head->next;
    q->count--;
    free(tmp);
    return(n);
}

void display(Node *head)
{

   while(head != NULL){
        printf("%d\n", head->data.code);
        head = head ->next;

    }
}



int main()
{



    queue *FirstQueue;
    queue *secondQueue;
    queue *thirdQueue;
    queue *fourthQueue;

    queue *ClientsQueue;
    ClientsQueue = malloc(sizeof(queue));



    FirstQueue = malloc(sizeof(queue));
    secondQueue = malloc(sizeof(queue));
    thirdQueue = malloc(sizeof(queue));
    fourthQueue = malloc(sizeof(queue));



    initialize(FirstQueue);
    initialize(secondQueue);
    initialize(thirdQueue);
    initialize(fourthQueue);


    client client1 = {.code = 1 , .arrivalTime = 0 , .transactionTime = 3};
    client client2 = {.code = 2 , .arrivalTime = 0 , .transactionTime = 5};
    client client3 = {.code = 3 , .arrivalTime = 0 , .transactionTime = 6};
    client client4 = {.code = 4 , .arrivalTime = 0 , .transactionTime = 2};



    display(ClientsQueue->head);


    return 0;
}
