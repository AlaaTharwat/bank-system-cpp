#include <stdio.h>
#include <stdlib.h>
typedef struct Node Node;
typedef struct Node Node;
typedef struct Client Client;
typedef struct LinkedList LinkedList;


struct LinkedList{
Node *first;
Node *last;
int totalWaitingTime;
int numberOfClients;
int totalWorkingTime;
int numberOfFinishedClient;
};

struct Client{
    int code;
    int arrivalTime;
    int transactionTime;
    int clientWaitingTime;
};

struct Node{
    Client data;
    Node *next , *prev;
};

void initialize(LinkedList *L)
{

    L->totalWaitingTime = 0;
    L->numberOfClients = 0;
    L->totalWorkingTime = 0;
    L->numberOfFinishedClient = 0;
    L->first =NULL;
    L->last = NULL;
}

Node *createNode(Client data){
    Node * node = (Node*) malloc(sizeof(Node));
    node ->data = data;
    node ->prev = NULL;
    node ->next = NULL;
    return node;
}

void add(Node * newNode , LinkedList *newLinkedList){
    if(newLinkedList->first == NULL){
        newLinkedList->first = newLinkedList->last = newNode;
    }else{
        newLinkedList->last->next = newNode;
        newNode->prev = newLinkedList->last;
        newLinkedList->last = newNode;
    }
    newLinkedList->numberOfClients++;
}

void displayAll(LinkedList *L){
    Node * pdisplay = L->first;
    while(pdisplay != NULL){
        printf("%d\n", pdisplay->data.arrivalTime);
        printf("\n");
        pdisplay = pdisplay ->next;

    }
}

Node * search(Client data , LinkedList *list){
    Node *pSearch = list->first;
    while(pSearch != NULL){
        if(pSearch->data.code == data.code){
            return pSearch;
        }
        else pSearch = pSearch->next;
    }
    return NULL;
}

void deleteN(Node *pdelete , LinkedList *list){
    if(pdelete == list->first){
        if(pdelete == list->last){
            list->first = list->last = NULL;
        }else{
            list->first = pdelete->next;
            list->first ->prev = NULL;
        }
    }else if(pdelete == list->last){
            list->last = pdelete->prev;
            list->last ->next = NULL;
        }

    else{
        pdelete->next->prev = pdelete ->prev;
        pdelete ->prev ->next = pdelete ->next;
    }
    list->numberOfClients--;
    free(pdelete);
}

LinkedList *getShortestTeller(LinkedList *teller1, LinkedList *teller2 , LinkedList *teller3){

    if (teller1->numberOfClients <= teller2->numberOfClients && teller1->numberOfClients <= teller3->numberOfClients )
    {
       return teller1;
    }

    else if (teller2->numberOfClients <= teller1->numberOfClients && teller2->numberOfClients <= teller3->numberOfClients )
     {
        return teller2;
     }

    else if ( teller3->numberOfClients <= teller1->numberOfClients && teller3->numberOfClients <= teller2->numberOfClients )
    {
        return teller3;
    }

}

void removeN(Node *pdelete ,LinkedList * list){
    if(pdelete == list->first){
        if(pdelete == list->last){
            list->first = list->last = NULL;
        }else{
            list->first = pdelete->next;
            list->first ->prev = NULL;
        }
    }else if(pdelete == list->last){
            list->last = pdelete->prev;
            list->last ->next = NULL;
        }

    else{
        pdelete->next->prev = pdelete ->prev;
        pdelete ->prev ->next = pdelete ->next;
    }
    pdelete->prev = pdelete->next=NULL;
}

void insertAfter(Node *pafter , Node *pnew ,LinkedList *list){
    if(pafter == list->last){
        add(pnew,list);
        list->numberOfClients--;
    }else{
        pnew -> next = pafter ->next;
        pnew ->prev = pafter;
        pafter -> next ->prev = pnew;
        pafter -> next = pnew;
    }
}

void bubbleSort(LinkedList *clientList){
    int swapped;
    Node * p;
    do
    {
        p = clientList->first;
        swapped = 1;
        while (p != clientList->last)
        {
           if(p->data.arrivalTime > p->next->data.arrivalTime){
              swapped = 0;
               Node * pNext = p->next;
              removeN(p,clientList);

              insertAfter(pNext , p , clientList);

           }else  p = p->next;
        }

    }
    while (!swapped);
}



void enqueueClients(LinkedList *teller1, LinkedList *teller2 , LinkedList *teller3, LinkedList *clientsList){

    bubbleSort(clientsList);

    displayAll(clientsList);
    Node *firstClient;

    firstClient = clientsList->first;

    int count = 0;


    while(firstClient != clientsList->last){
        LinkedList *shortestTeller  = getShortestTeller(teller1 ,teller2 ,teller3);

        add(firstClient,shortestTeller);
        firstClient = firstClient->next;
        printf("%d\n",firstClient->data.arrivalTime);
    }



}



int main()
{
    LinkedList *list;
    list = malloc(sizeof(LinkedList));
    initialize(list);

    Client Client1 = {.code = 1 , .arrivalTime = 0 , .transactionTime = 3 , .clientWaitingTime = 0};
    Client Client2 = {.code = 2 , .arrivalTime = 0 , .transactionTime = 7 , .clientWaitingTime = 0};
    Client Client3 = {.code = 3 , .arrivalTime = 1 , .transactionTime = 1 , .clientWaitingTime = 0};
    Client Client4 = {.code = 4 , .arrivalTime = 3 , .transactionTime = 6 , .clientWaitingTime = 0};
    Client Client5 = {.code = 5 , .arrivalTime = 2 , .transactionTime = 4 , .clientWaitingTime = 0};
    Client Client6 = {.code = 6 , .arrivalTime = 5 , .transactionTime = 5 , .clientWaitingTime = 0};
    Client Client7 = {.code = 7 , .arrivalTime = 1 , .transactionTime = 1 , .clientWaitingTime = 0};
    Client Client8 = {.code = 8 , .arrivalTime = 0 , .transactionTime = 8 , .clientWaitingTime = 0};


    Node *pnode = createNode(Client1);
    Node *pnode1 = createNode(Client2);
    Node *pnode2 = createNode(Client3);
    Node *pnode3 = createNode(Client4);
    Node *pnode4 = createNode(Client5);
    Node *pnode5 = createNode(Client6);
    Node *pnode6 = createNode(Client7);
    Node *pnode7 = createNode(Client8);




    add(pnode,list);
    add(pnode1,list);
    add(pnode2,list);
  //  add(pnode3,list);
  //  add(pnode4,list);
  //  add(pnode5,list);
  //  add(pnode6,list);
    //add(pnode7,list);

    bubbleSort(list);





    LinkedList *teller1;
    LinkedList *teller2;
    LinkedList *teller3;

    teller1 = malloc(sizeof(LinkedList));
    teller2 = malloc(sizeof(LinkedList));
    teller3 = malloc(sizeof(LinkedList));

    initialize(teller1);
    initialize(teller2);
    initialize(teller3);



    enqueueClients(teller1,teller2,teller3,list);

   // displayAll(teller1);

    return 0;
}
