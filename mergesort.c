#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "simpleCSVsorter.h"


/* sorts the linked list by changing next pointers (not data) */
void merge_sort(CSVrecord** headRef) {
    CSVrecord* head = *headRef;
    CSVrecord* a;
    CSVrecord* b;

    /* Base case -- length 0 or 1 */
    if ((head == NULL) || (head->next == NULL))
    {
        return;
    }

    /* Split head into 'a' and 'b' sublists */
    FrontBackSplit(head, &a, &b);

    /* Recursively sort the sublists */
    merge_sort(&a);
    merge_sort(&b);

    /* answer = merge the two sorted lists together */
    *headRef = SortedMerge(a, b);
}

/* See https://www.geeksforgeeks.org/?p=3622 for details of this
function */
struct CSVrecord* SortedMerge(CSVrecord* a, CSVrecord* b) {
    CSVrecord* result = NULL;

    /* Base cases */
    if (a == NULL)
        return(b);
    else if (b==NULL)
        return(a);

    /* Pick either a or b, and recur */
    if (a->data <= b->data)
    {
        result = a;
        result->next = SortedMerge(a->next, b);
    }
    else
    {
        result = b;
        result->next = SortedMerge(a, b->next);
    }
    return(result);
}



/*is_digit(): decides if its a digit/string/decimal */

int is_digit(char*str){

	int i;
	int isDec = 0;

	for(i = 0; i < strlen(str); i++){
		
		if((!isdigit(str[i])) && str[i] != '.'){
			//printf("the string is not a number. \n");
			return 0;		//string is a word
		}
		
		if(str[i] == '.'){
			//printf("the string has a period in it. \n");
			isDec = 1;
		}

		if(isdigit(str[i])){
			//printf("str[%d] val is: %c\n", i, str[i]);
			continue;
		}

	}
	
	if(isDec == 1){
		//printf("the string is a decimal. \n");
		return 2;		//string is decimal value
	}
	else if(isDec == 0){
		//printf("the string is an int. \n");
		return 1;		//integer
	}
}









/* UTILITY FUNCTIONS */
/* Split the nodes of the given list into front and back halves,
    and return the two lists using the reference parameters.
    If the length is odd, the extra node should go in the front list.
    Uses the fast/slow pointer strategy. */
void FrontBackSplit(CSVrecord* source, CSVrecord** frontRef, CSVrecord** backRef){
    CSVrecord* fast;
    CSVrecord* slow;
    slow = source;
    fast = source->next;

    /* Advance 'fast' two nodes, and advance 'slow' one node */
    while (fast != NULL){
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    /* 'slow' is before the midpoint in the list, so split it in two
    at that point. */
    *frontRef = source;
    *backRef = slow->next;
    slow->next = NULL;
    
    printf("<front list>\n\n");
    printAllRecords(*frontRef);
    printf("-------------------------------------------------\n<back list>\n\n");
	printAllRecords(*backRef);
	printf("-------------------------------------------------\n");
}


