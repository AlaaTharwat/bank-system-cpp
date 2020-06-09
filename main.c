#include <stdio.h>
#include <stdlib.h>
#include<ITI.h>
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
        printf("code %d\n", pdisplay->data.code);
        printf("arrival time %d\n", pdisplay->data.arrivalTime);
        printf("transaction time %d\n", pdisplay->data.transactionTime);
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

Node * deleteN(Node *pdelete , LinkedList *list){
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
    pdelete->next = pdelete->prev = NULL;
    list->numberOfClients--;
    return pdelete;
 //   free(pdelete);
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
    }else
    return teller1;

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





void enqueueClients(LinkedList *teller1, LinkedList *teller2 , LinkedList *teller3, LinkedList *clientsList ,int time){

    Node * client = clientsList->first;
    LinkedList *shortestTeller;
    Node * deleted ;
    Node * temp;

    while(client != NULL){
        if(client->data.arrivalTime == time){
            shortestTeller = getShortestTeller(teller1,teller2,teller3);
            temp = client;
            client = client->next;
            deleted = deleteN(temp, clientsList);
            add(deleted,shortestTeller);
        }
       else client = client->next;
    }
}

void calculateWorkingTime(LinkedList *teller){

    if(teller->first == NULL) return;

    teller->first->data.transactionTime--;
    teller->totalWorkingTime++;

    if(teller->first->data.transactionTime <= 0){
        teller->totalWaitingTime += teller->first->data.clientWaitingTime;
        teller->numberOfFinishedClient++;
        deleteN(teller->first,teller);
    }
}

void calculateWaitingTime(LinkedList *teller){

    Node * temp;
    if(teller->first == NULL) return;
    temp = teller->first->next;

    while(temp != NULL){
            temp->data.clientWaitingTime++;
            temp = temp->next;
    }


}




int main()
{
      Node ** node;
    node = (Node**)malloc(sizeof(Node*));
    int numberOfClientsEntered;
    Client *clients;
    clients = malloc(sizeof(Client));


    LinkedList *list;
    list = malloc(sizeof(LinkedList));
    initialize(list);

    printf("Enter Number of clients\n");
    scanf("%d",&numberOfClientsEntered);

    clrscr();

    int i = 0;
 while(i != numberOfClientsEntered){

        clients->clientWaitingTime = 0;

        printf("client no %d \n", i+1);
        printf("code: ");
        scanf("%d", &clients->code);

        printf("Arival time: ");
        scanf("%d", &clients->arrivalTime);

        printf("transaction time: ");
        scanf("%d", &clients->transactionTime);
        //scanf("%d", &clients[i].transactionTime);

        node[i] = createNode(*clients);
        add(node[i],list);

        printf("\n");
        i++;
    }



    LinkedList *teller1;
    LinkedList *teller2;
    LinkedList *teller3;

    teller1 = malloc(sizeof(LinkedList));
    teller2 = malloc(sizeof(LinkedList));
    teller3 = malloc(sizeof(LinkedList));

    initialize(teller1);
    initialize(teller2);
    initialize(teller3);

    int time = 0;


    while(teller1->first != NULL || teller2->first != NULL || teller3 ->first != NULL || list->first != NULL){
         enqueueClients(teller1 , teller2 ,teller3 , list , time);
         calculateWaitingTime(teller1);
         calculateWaitingTime(teller2);
         calculateWaitingTime(teller3);

         calculateWorkingTime(teller1);
         calculateWorkingTime(teller2);
         calculateWorkingTime(teller3);

         time++;
    }






    int totalWorkingTimeTeller1 = teller1->totalWorkingTime;
    int numberOfFinishedClientTeller1 = teller1->numberOfFinishedClient;
    int totalWaitingTimeTeller1 = teller1->totalWaitingTime;

    if(numberOfFinishedClientTeller1 > 0){
    printf("Avg working time for teller1: %d\n",totalWorkingTimeTeller1/numberOfFinishedClientTeller1);
    printf("Avg Waiting time for teller1: %d\n",totalWaitingTimeTeller1/numberOfFinishedClientTeller1);
    printf("-------------\n");
    }

    int totalWorkingTimeTeller2 = teller2->totalWorkingTime;
    int numberOfFinishedClientTeller2 = teller2->numberOfFinishedClient;
    int totalWaitingTimeTeller2 = teller2->totalWaitingTime;
    if(numberOfFinishedClientTeller2 > 0){
    printf("Avg working time for teller2: %d\n",totalWorkingTimeTeller2/numberOfFinishedClientTeller2);
    printf("Avg Waiting time for teller2: %d\n",totalWaitingTimeTeller2/numberOfFinishedClientTeller2);
    printf("-------------\n");
    }

    int totalWorkingTimeTeller3 = teller3->totalWorkingTime;
    int numberOfFinishedClientTeller3 = teller3->numberOfFinishedClient;
    int totalWaitingTimeTeller3 = teller3->totalWaitingTime;
    if(numberOfFinishedClientTeller3 > 0){
    printf("Avg working time for teller3: %d\n",totalWorkingTimeTeller3/numberOfFinishedClientTeller3);
    printf("Avg Waiting time for teller3: %d\n",totalWaitingTimeTeller3/numberOfFinishedClientTeller3);
    printf("-------------\n");
    }


    return 0;
}
