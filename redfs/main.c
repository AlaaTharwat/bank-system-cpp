#include <stdio.h>
#include <stdlib.h>
//#include <ITI.h>
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

    setbuf(stdout, 0);
    printf("Enter Number of clients\n");
    scanf("%d",&numberOfClientsEntered);

    system("cls");

    printf("Enter Clients data\n");
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



    system("cls");



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

/*
#include <stdlib.h>
#include <stdio.h>a

//#include <ctype.h>
//#include <conio.h>
//#include <stddef.h>

typedef struct Client Client;
typedef struct LinkedList LinkedList;
typedef struct Node Node;

struct Client
{
    int id , finishtime ;
    int arrivalTime;
    int transactionTime ;
    int waitingTime;
};

struct Node
{
    Client data;
    Node* next;
    Node* prev;
};

struct LinkedList
{
    Node *first, *last;
    int length;
    int numberOfClients;
    int totalTransactionTime;
    int totalWaitingTime;
};

Node* Create(Client c)
{
    Node* new_node = (Node*)malloc(sizeof( Node));
    new_node->data = c;
    new_node->data.finishtime= 0;
    new_node->next = new_node->prev = NULL;
    return new_node;
}

void Add( Node* new_node, LinkedList* l)
{
    if(new_node ==NULL)
        return ;
    if(l->first == NULL)
    {
        l->first = l->last = new_node;

    }
    else
    {
        new_node->prev = l->last;
        l->last->next = new_node;
        l->last = new_node;
    }
    l->length++;
}

void DisplayAll(LinkedList* l)
{
    // printf("list displayed");
    Node *Pdisplay = l->first;
    while(Pdisplay != NULL)
    {

        printf("Client ID: %d \n",Pdisplay->data.id);
        printf("Client Arrival Time: %d \n",Pdisplay->data.arrivalTime);
        printf("Client Transaction time: %d \n",Pdisplay->data.transactionTime);
        Pdisplay = Pdisplay->next;
    }
}

Node* Delete ( Node* pDelete, LinkedList* l)
{
    if(pDelete == l->first)
    {
        if(pDelete == l->last)
        {
            l->first = l->last = NULL;

        }

        else
        {
            l->first = pDelete->next;
            l->first->prev = NULL;

        }
    }
    else if(pDelete == l->last)
    {
        l->last = pDelete->prev;
        l->last->next = NULL;

    }
    else
    {
        pDelete->next->prev = pDelete->prev;
        pDelete->prev->next = pDelete->next;

    }
    pDelete->prev = pDelete->next = NULL;
    l->length--;

//     free(pDelete);
    return pDelete;
}

void InsertAfter( Node* pAfter, Node* pNew, LinkedList* l)
{

    pNew->prev = pAfter;
    if(pAfter->next != NULL)
    {
        pNew->next = pAfter->next;
        pAfter->next->prev = pNew;
    }
    else
    {
        pNew->next = NULL;
        l->last = pNew;
    }
    pAfter->next = pNew;
}

void InsertBefore( Node* pBefore,  Node* pNew,  LinkedList* l)
{
    if(pBefore ==l->first)
    {
        l->first = pNew;
        pNew->next = pBefore;
        pNew->prev = NULL;
        pBefore->prev = pNew;
    }
    else
    {

        pNew->prev = pBefore->prev;
        pNew ->next = pBefore;
        pBefore->prev ->next = pNew;
        pBefore->prev = pNew;
        //pNew->next->prev = pnew;
    }
}
Node* swap( Node *a,  Node *b,  LinkedList* l)
{
    Client aValue  = a->data;
    Client bValue  = b->data;

    Node* aNode = Create(aValue);
    Node* bNode = Create(bValue);

    if(a->prev != NULL)
    {
        Node *temp = a->prev;
        Delete(a,l);
        Delete(b,l);
        InsertAfter(temp, aNode, l);
        InsertAfter(temp, bNode, l);

    }
    else
    {
        Node *temp = b->next;
        Delete(a,l);
        Delete(b,l);
        InsertBefore(temp, bNode, l);
        InsertBefore(temp, aNode, l);
    }
    return bNode;
}

void bubbleSort( LinkedList* l)
{
    int swapped;
    Node *ptr1;
    Node *lptr = NULL;

    if (l->first == NULL)
        return;

    do
    {
        swapped = 0;
        ptr1 = l->first;

        while (ptr1->next != lptr)
        {
            if (ptr1->data.arrivalTime > ptr1->next->data.arrivalTime)
            {
                ptr1 = swap(ptr1, ptr1->next, l);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
    while (swapped);
}


LinkedList* ShortestQueue(LinkedList* q1, LinkedList *q2, LinkedList *q3)
{
//    if(q1->length >= q2->length)
//    {
//        if(q1->length >= q3->length )
//            return q1;
//        else
//            return q3;
//    }
//
//    else if (q1->length<=q2->length)
//    {
//        if(q1->length <= q3->length)
//            return q1;
//        else
//            return q3;
//    }
//    else if (q1->length== q2->length&& q2->length == q3->length && q1->length == q3->length)
//        return q1;

    if(q1->length <= q2->length
       && q1->length <= q3->length)
        return q1;
    else if (q2->length <= q1->length
             && q2->length <=q3->length)
        return q2;
    else if (q3->length <= q2->length
             &&q3->length <= q1->length)
        return q3;
    else if (q1->length == q2->length && q2->length == q3->length && q1->length == q3->length)
        return q1;
}

LinkedList* longestQueue(LinkedList *q1 , LinkedList  *q2 , LinkedList *q3){

    if(q1->length >= q2->length && q1->length >= q3->length)
        return q1;
    else if (q2->length >= q1->length && q2->length >= q3->length)
        return q2;
    else if (q3->length >= q1->length && q3->length >= q2->length)
        return q3;
    else if (q1->length == q2->length && q1->length == q3->length)
        return q1;

}


void AddClients(LinkedList *list, Client clientData)
{
    char input;
    setbuf(stdout, 0);
    printf("A-Client\n E-Exit\n");
    setbuf(stdout, 0);
    scanf("%c", &input);
    if(input =='a')
    {
    }
    do
    {
        if( input =='a')
        {setbuf(stdout, 0);
            printf("enter client's  id: ");
            setbuf(stdout, 0);
            scanf("%d", &clientData.id );
            setbuf(stdout, 0);
            printf("\nenter client's  arrivalTime: ");
            setbuf(stdout, 0);
            scanf("%d", &clientData.arrivalTime);
            setbuf(stdout, 0);
            printf("\nenter client's transactionTime: ");
            setbuf(stdout, 0);
            scanf("%d", &clientData.transactionTime);
            setbuf(stdout, 0);
            Node* node = Create(clientData);
            Add(node, list);
        }
        printf("\nA- Client\n E-Exit\n");
        scanf("%c", &input);

    }
    while (input !='e');
}

void AddClientsToQueue(LinkedList *people, LinkedList *q1, LinkedList *q2, LinkedList *q3)
{
    Node *pNode  = people->first;
    Node *temp = pNode;
    int diffOfLength=0 ;
    LinkedList * shortQueue , *longQueue ;
    while(pNode != NULL)
    {

        temp = pNode;
        pNode=pNode->next;

//
//        if (temp->data.arrivalTime ==currentTime)
//        {
            printf("%x \n", ShortestQueue(q1, q2, q3));
            Add(Delete(temp, people), ShortestQueue(q1, q2, q3));

            shortQueue = ShortestQueue(q1 ,q2 ,q3);
            //    longQueue= longestQueue(q1 ,q2 ,q3);
//                diffOfLength  =longQueue->length - shortQueue->length;
//                if(diffOfLength >=2)
//                {
//                    Add(Delete(longQueue->last , longQueue)  , shortQueue);
//
//                }

//        }

    }

//        Add(Delete(temp, people),ShortestQueue(q1, q2, q3) );
//        if(shortQueue->q ==1)
//            pNode->data.qNumber =1;
//        else if (shortQueue -> q ==2)
//            pNode->data.qNumber =2;
//        else if (shortQueue->q ==3)
//            pNode->data.qNumber =3;

    //  shortQueue->length++;

    //temp->prev = temp->next =NULL;
    // pNode = pNode->next;


}


void WaitingTime(LinkedList *queue)
{
    int finishTime = queue->first->data.arrivalTime + queue->first->data.transactionTime;
    queue->first->data.finishtime = finishTime;

    Node* temp = (Node*) malloc(sizeof(Node));
            temp =  queue->first->next;
    if( temp == NULL)
    {
        return;
    }else
    {
        int waiting = 0 ;

        while(temp != NULL){
//            temp = temp->next;
            waiting = finishTime - temp->data.arrivalTime;
            queue->totalWaitingTime += waiting;
            finishTime +=  temp->data.transactionTime;
            temp->data.finishtime = finishTime;
            printf(" w %d : f %d : n %x\n",waiting, finishTime, temp );
            temp = temp->next;
        }
    }

//    Node*  pNode;
//
//    if(queue->first !=NULL)
//    {
//        pNode= queue->first->next;
//
//
//        while(pNode !=NULL)
//        {
//            pNode->data.waitingTime++;
//            printf("\nwaiting Time : %d\n", pNode->data.waitingTime);
//            pNode = pNode->next;
//        }
//    }
//    else
//        return;

}

void CalculateTransactionTime (LinkedList *q, int timer)
{   setbuf(stdout, 0);
    printf("%d\n",timer);
    if(q->first !=NULL)
    {
//        q->first->data.transactionTime--;
//        q->totalTransactionTime++;
//        if(q->first->data.transactionTime ==0)
        if(q->first->data.finishtime == timer)
        {
            q->totalWaitingTime += q->first->data.waitingTime;
            Node *pn = Delete(q->first, q);
            setbuf(stdout, 0);
            printf("%x : \n", pn);
            q->numberOfClients++;
        }
    }
}


int main()
{
    int bankTimer =0;

    Client data;
    LinkedList list,q1,q2, q3;


    ///set length to zero for each list///
    list.length=0;
    q1.length =0;
    q2.length =0;
    q3.length =0;

    ///set initial value for each queue number of finished clients ///
    q1.numberOfClients=0;
    q2.numberOfClients=0;
    q3.numberOfClients=0;

    ///set total transaction time for each queue to zero ///
    q1.totalTransactionTime =0;
    q2.totalTransactionTime =0;
    q3.totalTransactionTime =0;


    q1.totalWaitingTime=0;
    q2.totalWaitingTime=0;
    q3.totalWaitingTime=0;


    data.waitingTime =0;
    data.transactionTime=0;

    list.first = list.last =NULL;
    q1.first = q1.last =NULL;
    q2.first = q2.last=NULL;
    q3.first = q3.last =NULL;



    AddClients(&list,data);
    bubbleSort(&list);
    DisplayAll(&list);

//    WaitingTime(&list);


//    DisplayAll(&q1);
//    WaitingTime(&q1);
//    WaitingTime(&q2);
//    WaitingTime(&q3);
//    while(list.first!=NULL ||q1.first !=NULL || q2.first !=NULL || q3.first !=NULL)
//    {
//        AddClientsToQueue(&list, &q1, &q2, &q3);
//
//        WaitingTime(&q1);
//        WaitingTime(&q2);
//        WaitingTime(&q3);
//
////
////        CalculateTransactionTime(&list , bankTimer);
//        CalculateTransactionTime(&q1 , bankTimer);
//        CalculateTransactionTime(&q2 , bankTimer);
//        CalculateTransactionTime(&q3 , bankTimer);
//        bankTimer++;
//        _sleep(1000);
//
//    }
//

//        DisplayAll(&q1);
//        DisplayAll(&q2);
//        DisplayAll(&q3);
//
//
//            printf("______________________QUEUE 1_______________________");
//    printf("\nqueue 1 total transaction %d", q1.totalTransactionTime);
//    printf("\nqueue 1 totalwaiting time %d", q1.totalWaitingTime);
//    printf("\nqueue 1 number of clients %d", q1.numberOfClients);
//
//    printf("\n______________________QUEUE 2_______________________");
//    printf("\nqueue 2 total transaction %d", q2.totalTransactionTime);
//    printf("\nqueue 2 totalwaiting time %d", q2.totalWaitingTime);
//    printf("\nqueue 2 number of clients %d", q2.numberOfClients);
//
//    printf("\n______________________QUEUE 3_______________________");
//    printf("\nqueue 3 total transaction %d", q3.totalTransactionTime);
//    printf("\nqueue 3 totalwaiting time %d", q3.totalWaitingTime);
//    printf("\nqueue 3 number of clients %d", q3.numberOfClients);
//
//    printf("\n__________________________________________________________________");
//    printf("\n queue 1 avg transaction time: %d " , q1.totalTransactionTime/q1.numberOfClients);
//    printf("\n queue 2 avg transaction time: %d " , q2.totalTransactionTime/q2.numberOfClients);
//    printf("\n queue 3 avg transaction time: %d " , q3.totalTransactionTime/q3.numberOfClients);


//    LinkedList* list2= ShortestQueue(&q1,&q2,&q3);
//    printf("%d",list2->length);
//    LinkedList *longest = longestQueue(&q1 , &q2  ,&q3);
//    printf("\nlongest queue length is %d"  , longest->length);
    printf("hello World !");

    return 0;
}
*/
