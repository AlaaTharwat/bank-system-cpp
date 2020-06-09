#include <stdio.h>
#include <stdlib.h>
typedef struct Node Node;
typedef struct Node Node;
typedef struct Employee Employee;
typedef struct LinkedList LinkedList;



struct LinkedList{
Node *first ;
Node *last ;
};

struct Employee{
    int code;
    int age;
    char name [21];
    float salary;
    float bonus;
    float tax;
};

struct Node{
    Employee data;
    Node *next , *prev;
};

void initialize(LinkedList *L)
{
    L->first =NULL;
    L->last = NULL;
}

Node *createNode(Employee data){
    Node * node = (Node*) malloc(sizeof(Node));
    node ->data = data;
    node ->prev = node ->next = NULL;
    return node;
}

void add(Node * newNode , LinkedList *newLinkedList){
    if(newLinkedList->first == NULL){
        newLinkedList->first = newLinkedList->last = newNode;
    }else{
        newNode ->prev = newLinkedList->last;
        newLinkedList->last->next = newNode;
        newLinkedList->last = newNode;
        newLinkedList->last->next = NULL;
    }
}

void displayAll(LinkedList *L){
    Node * pdisplay = L->first;
    while(pdisplay != NULL){
        printf("%s\n", pdisplay->data.name);
        printf("\n");
        pdisplay = pdisplay ->next;

    }
}

Node * search(Employee data , LinkedList *list){
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

    free(pdelete);
}



int main()
{
    LinkedList *list;
    initialize(&list);

    Employee E = {.age = 25, .bonus = 2500 , .code = 1 ,.name = "Alaa Tharwat" ,.salary = 5000};
    Employee E1 = {.age = 25, .bonus = 2500 , .code = 1 ,.name = "Alaa Tharwat" ,.salary = 5000};
    Employee E2 = {.age = 25, .bonus = 2500 , .code = 1 ,.name = "Alaa " ,.salary = 5000};
    Employee E3 = {.age = 25, .bonus = 2500 , .code = 1 ,.name = "Alaa " ,.salary = 5000};

    Node *pnode = createNode(E);
    Node *pnode1 = createNode(E1);
    Node *pnode2 = createNode(E2);
    Node *pnode3 = createNode(E3);


    add(pnode , &list);
    add(pnode1 , &list);
    add(pnode2 , &list);
    add(pnode3 , &list);


    displayAll(&list);



    return 0;
}
