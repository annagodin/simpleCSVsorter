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



//Suggestion: define a struct that mirrors a record (row) of the data set


//Suggestion: prototype a mergesort function

#endif
