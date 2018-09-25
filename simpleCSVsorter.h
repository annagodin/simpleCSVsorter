/*****
*
*	Define structures and function prototypes for your sorter
*
*
*
******/
#ifndef SIMPLECSVSORTER_H     
#define SIMPLECSVSORTER_H

//the struct will be an array, where each array entry will hold a string token.
typedef struct CSVrecord {
  char* sortVal;
  char** data;
  int numCols;
  struct CSVrecord *next;
} CSVrecord;

int stringToInt (char* str);
char* stripNewLineChar (char* token,int tokLen);
char* stripFirstChar (char* token, int tokLen);
char* stripLastChar (char* token);
char* trimWhiteSpace(char* token);
void printAllRecords (CSVrecord * frontRec);
void printRecNode(CSVrecord *rec);
void addRecToEnd(CSVrecord** head, CSVrecord *node);


struct CSVrecord* SortedMerge(CSVrecord* a, CSVrecord* b);
int compareFields(char* a, char*b);
void FrontBackSplit(CSVrecord* source, CSVrecord** frontRef, CSVrecord** backRef);
void mergesort(CSVrecord** headRef);

//void mergesort(CSVrecord *source);
//void partition (CSVrecord *head, CSVrecord *front, CSVrecord *back){



#endif
