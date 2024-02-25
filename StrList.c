#include "StrList.h"
#include <stdio.h>
#include <string.h>

typedef struct Node{
    char* data;
    struct Node* next;
} Node;

struct _StrList{
    Node* head;
    size_t size;
};

StrList* newList;


static Node* createNode(const char* data){
    Node* newNode = (Node*)malloc(sizeof(Node));
        if(newNode){ //if allocation was successful
        newNode->data = strdup(data);
        newNode->next = NULL;
        }
        return newNode;
}

//Free a node and its data
static void freeNode(Node* node){
    if(node){
        free(node->data);
        free(node);
    }
}

//Find the last node in the list
static Node* getLastNode(StrList* StrList){
    if(StrList->head == NULL){
        return NULL;
    }
    Node* current = StrList->head;
    while(current->next != NULL){
        current = current->next;
    }
    return current;
}

//initialize an empty list
StrList* StrList_alloc(){
    StrList* newList = (StrList*)malloc(sizeof(StrList));

        if(newList){//if allocation was successful
        newList->head = NULL;
        newList->size = 0;
        }
        return newList;
}

void StrList_free(StrList* StrList){
    if(StrList == NULL){
        return;
    }
    Node* current = StrList->head;
    while(current != NULL){
        Node* next = current->next;
        freeNode(current); //both its data and the node itself 
        current = next;
    }
    free(StrList); //Free memory for the StrList structure itself
}

size_t StrList_size(const StrList* StrList){
    return StrList ? StrList->size : 0;
}

void StrList_insertLast(StrList* StrList, const char* data){
    Node* newNode = createNode(data);
    if(newNode == NULL){
        return;
    }

    if(StrList->head == NULL){
       StrList->head = newNode; 
    }else{
        Node* lastNode = getLastNode(StrList);
        lastNode->next = newNode;
    }
    StrList->size++; // updating the new size
}

void StrList_insertAt(StrList* StrList, const char* data,int index){
      if (index < 0 || index > StrList->size) {
        printf("Invalid index.\n");
        return;
    }
    Node* newNode = createNode(data);
    if (newNode == NULL) {
        return; // Memory allocation failed
    }
    if (index == 0) {
        newNode->next = StrList->head;
        StrList->head = newNode;
    } else {
        Node* current = StrList->head;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
    StrList->size++; // updating the new size
}

char* StrList_firstData(const StrList* StrList){
    if(StrList->head != NULL){
        return StrList->head->data;
    }
    return NULL;
}


// void StrList_print(const StrList* StrList){
// Node* current = StrList->head;
// while(current != NULL){
//     printf("%s ", current->data);
//     current = current->next;
// }
// printf("\n");
// }

void StrList_print(const StrList* StrList) {
    Node* current = StrList->head;
    while (current != NULL) {
        printf("%s", current->data);
        if (current->next != NULL) {
            printf(" "); // Print space only if there is a next node
        }
        current = current->next;
    }
    printf("\n");
}

void StrList_printAt(const StrList* StrList, int index){
    Node* current = StrList->head;
    int i = 0;
    while(current != NULL && i < index){
        current = current->next;
        i++;
    }

    if(current != NULL){
        printf("%s\n", current->data);
    }else{
        printf("Index out of range\n");
    }
}

int StrList_printLen(const StrList* StrList){
    int totalLen = 0;
    Node* current = StrList->head;
    while(current != NULL){
        totalLen += strlen(current->data);
        current = current->next;
    }
    return totalLen;
}

int StrList_count(StrList* StrList, const char* data){
    int count = 0;
    Node* current = StrList->head;
    while(current != NULL){
        if(strcmp(current->data, data) == 0){ //the string exists in the list
            count++;
        }
        current = current->next;
    }
    return count;
}

void StrList_remove(StrList* StrList, const char* data){
    Node* current = StrList->head;
    Node* prev = NULL;
    while(current != NULL){
        if(strcmp(current->data, data) == 0){
            if(prev == NULL){
                StrList->head = current->next;//remove head of the list
            }else{
                prev->next = current->next;//remove not the head of the list
            }

            freeNode(current);
            StrList->size--; //update after removal of the node
            return;
        }
        prev = current;
        current = current->next;
    }
}

void StrList_removeAt(StrList* StrList, int index){
    if(index < 0 || index >= StrList->size){
        printf("index out of range");
        return;
    }

    Node* current = StrList->head;
    Node* prev = NULL;
    int i = 0;
    while(current != NULL && i < index){
    prev = current;
    current = current->next;
    i++;
    }  

    if(prev == NULL){
    StrList->head = current->next;//remove head of the list
    }else{
    prev->next = current->next;//remove not the head of the list
    }
    freeNode(current);
    StrList->size--; //update after removal of the node
 }

int StrList_isEqual(const StrList* StrList1, const StrList* StrList2){
    if(StrList_size(StrList1) != StrList_size(StrList2)){
        return 0;
    }
    Node* current1 = StrList1->head;
    Node* current2 = StrList2->head;
    
    while(current1 != NULL){
        if(strcmp(current1->data,current2->data) != 0){
            return 0;
        }
        current1 = current1->next;
        current2 = current2->next;
    }
    return 1;
}

StrList* StrList_clone(const StrList* originalList){
    StrList* newList = StrList_alloc();
    if(newList == NULL){ //Memory allocation failed
        return NULL;
    }
    Node* current = originalList->head;

    while(current != NULL){
        StrList_insertLast(newList,current->data);
        current = current->next;
    }
    return newList;
}

// StrList* StrList_clone(const StrList* StrList){
//     StrList* newList = StrList_alloc();
//     if(newList == NULL){ //Memory allocation failed
//         return NULL;
//     }
//     Node* current = StrList->head;

//     while(current != NULL){
//         StrList_insertLast(newList,current->data);
//         current = current->next;
//     }
//     return newList;
// }



void StrList_reverse(StrList* StrList){
    Node* prev = NULL;
    Node* current = StrList->head;
    Node* next = NULL;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    StrList->head = prev;
}

int compareStrings(const void* a, const void* b){
    return strcmp(*(const char**)a, *(const char**)b);
}

void StrList_sort( StrList* StrList){
    int len = StrList_size(StrList);
    char** arr = (char**)malloc(len*sizeof(char*));
    if(arr == NULL){ //Memory allocation failed
        return;
    }

    //Update the array with list data
    Node* current = StrList->head;
    for(int i = 0; i < len; i++){
        arr[i] = current->data;
        current = current->next;
    }

    //Quick sort on the array
    qsort(arr, len, sizeof(char*), compareStrings);

    //Update the list with the sorted array
    current = StrList->head;
    for(int i = 0; i < len; i++){
        current->data = arr[i];
        current = current->next;
    }
    free(arr);
}



int StrList_isSorted(StrList* StrList){
    Node* current = StrList->head;
    while(current != NULL && current->next != NULL){
        if(strcmp(current->data,current->next->data) > 0){
            return 0;
        }
        current = current->next;
    }
    return 1; //Is sorted
}
