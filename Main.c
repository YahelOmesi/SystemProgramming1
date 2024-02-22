#include <stdio.h>
#include <stdlib.h>
#include "StrList.h"

int main() {
    StrList* myList = StrList_alloc();
    if (myList == NULL) {
        printf("Memory allocation failed. Exiting.\n");
        return 1;
    }

    int choice;
    char *word = NULL; // Dynamically allocated array
    int index;

    scanf(" %d", &choice);

    while (choice <= 13 && choice >= 1) {
        // printf("\nMenu:\n");
        // printf("1- Insert strings into the list\n");
        // printf("2- Insert a string at a certain index\n");
        // printf("3- Print the list\n");
        // printf("4- Print the length of the list\n");
        // printf("5- Print a string at a certain index\n");
        // printf("6- Print the number of characters that appear in the entire list\n");
        // printf("7- Print how many times a string appears\n");
        // printf("8- Delete all occurrences of a string\n");
        // printf("9- Delete a member at a certain index\n");
        // printf("10- Reverse the list\n");
        // printf("11- Delete the entire list\n");
        // printf("12- Arrange the list in lexicographical order\n");
        // printf("13- Check whether the list is arranged in lexicographical order\n");
        // printf("0- Exit\n");

        // printf("Enter your choice: ");
        //scanf(" %d", &choice);
        
        int numWords = 0;
        switch (choice) {
            case 1:
                //printf("Enter the number of words to insert: ");
                //int numWords = 0;
                scanf("%d", &numWords);
                int numOfChar = StrList_printLen(myList);
                word = (char*)malloc(sizeof(char)*numOfChar);
                 if(word == NULL){
                    //printf("Memory allocation failed. Exiting.\n");
                    return 1;
                }

                //printf("Enter words separated by spaces: ");
                for (int i = 0; i < numWords; i++) {
                scanf("%s", word);
                StrList_insertLast(myList, word);
                }
                free(word);
                break;

            case 2:
                //printf("Enter the index: ");
                scanf("%d", &index);
                //printf("Enter the word: ");

                int numOfChars = StrList_printLen(myList);
                word = (char*)malloc(sizeof(char)*numOfChars);
                if(word == NULL){
                    //printf("Memory allocation failed. Exiting.\n");
                    return 1;
                }

                scanf("%s", word);
                StrList_insertAt(myList, word, index);
                free(word);// Free dynamically allocated memory
                break;

            case 3:
                //printf("List contents:\n");
                StrList_print(myList);
                printf("\n");
                break;

            case 4:
                //printf("Length of the list: %ld\n", StrList_size(myList)); 
                printf("%ld\n", StrList_size(myList)); 
                break;

            case 5:
                //printf("Enter the index: ");
                scanf("%d", &index);
                //printf("Word at index %d:\n", index); 
                StrList_printAt(myList, index);
                break;

            case 6:
                //printf("Total characters in the list: %d\n", StrList_printLen(myList));
                printf("%d\n", StrList_printLen(myList));
                break;

            case 7:
                //printf("Enter the word to count: ");
                scanf("%s", word);
                //printf("Occurrences of '%s' in the list: %d\n", word, StrList_count(myList, word));
                printf("%d\n", StrList_count(myList, word));
                break;

            case 8:
                //printf("Enter the word to delete: ");
                scanf("%s", word);
                StrList_remove(myList, word);
                break;

            case 9:
                //printf("Enter the index to delete: ");
                scanf("%d", &index);
                StrList_removeAt(myList, index);
                break;

            case 10:
                StrList_reverse(myList);
                //printf("List reversed.\n");
                break;
            case 11:

                StrList_free(myList);
                myList = StrList_alloc();
                //printf("List deleted.\n");
                break;

            case 12:
                StrList_sort(myList);
                //printf("List sorted in lexicographical order.\n");
                break;

            case 13:
                if (StrList_isSorted(myList))
                    printf("true\n");
                else
                    printf("false\n");
                break;

            case 0:
                StrList_free(myList);
                //printf("Exiting.\n");
                //printf(" \n");               
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
        scanf(" %d", &choice);
    }
    return 0;
}
