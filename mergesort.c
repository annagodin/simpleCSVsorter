#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "simpleCSVsorter.h"

int compareFields(char* a, char*b){
	if(isDigit(a)!=0 && isDigit(b)!=0) { //not a string
		if(isDigit(a)==1 && isDigit(b)==1){ //integer
			int numA = atoi(a);
			int numB = atoi(b);
			if (numA<numB)
				return -1
			else
				return 1;
		} else { //decimal
			char *ptr;
			double numA = strtod(a,&ptr);
			double numB = strtod(b,&ptr);
			if (numA<numB)
				return -1
			else
				return 1;
			//strtod(str,&ptr)
		}
	} else{//string
		a=trimWhiteSpace(a);
		b=trimWhiteSpace(b);
		if(strcmp(a,b)==-1){
			return -1;
		} else{
			return 1;
		}
	}
}

/* sorts the linked list by changing next pointers (not data) */
void mergesort(CSVrecord** headRef) {
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
    mergesort(&a);
    mergesort(&b);

    /* answer = merge the two sorted lists together */
    *headRef = SortedMerge(a, b);
}

//TODO 
CSVrecord* SortedMerge(CSVrecord* a, CSVrecord* b) {
    
    CSVrecord* result = NULL;

    /* Base cases */
    if (a == NULL)
        return(b);
    else if (b==NULL)
        return(a);

    /* Pick either a or b, and recur */
    if (compareFields(a->sortVal, b->sortVal)==-1){
        result = a;
        result->next = SortedMerge(a->next, b);
    }
    else {
        result = b;
        result->next = SortedMerge(a, b->next);
    }
    return(result);
}


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


