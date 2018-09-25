#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "simpleCSVsorter.h"


// cat small.csv | ./simpleCSVsorter -c movie_title



//converts a string to an integer
int stringToInt (char* str){
	
	int dec = 0, i, len;
	len = strlen(str);
	for(i=0; i<len; i++){
		dec = dec * 10 + ( str[i] - '0' );
	}
	return dec;
}

//strips new line character off a string
char* stripNewLineChar (char* token,int tokLen){
	//printf("inside function BEFORE str: '%s'\n", token);
	char* replace = (char*)malloc((tokLen-1)*sizeof(char));
	int i;
	for (i=0; i<tokLen-1; i++){
		replace[i]=token[i];
	}

	return replace;
}

//strips last character
char* stripLastChar (char* token){
	char* replace = (char*)malloc((strlen(token))*sizeof(char));
	int i;	
	for (i=0; i<(strlen(token)-1); i++){
		replace[i]=token[i];
	}	
	return replace;
	
}

//strips the first character off a string
char* stripFirstChar (char* token, int tokLen){
	char* replace = (char*)malloc((tokLen-1)*sizeof(char));
	int i;
	int j=0;
	for (i=1; i<tokLen; i++){
		replace[j]=token[i];
		j++;
	}
	
	return replace;
}

//searches string for a quote
int searchForQuote (char* token){
	int len = strlen(token);
	int i;
	for (i=0; i<len; i++){
		if (token[i]=='"'){
			//printf("found quote in the token:\t%s\n",token);
			return 1;
		}
	}
	return 0;
}

//trims white spaces
char* trimWhiteSpace(char* token){
	int index, i;
	index=0;
	i=0;
	char* trimmed = malloc(sizeof(char)*200);
	//trim leading
	while (token[index] == ' '){
		index++;
	}
	for(i=0;i<strlen(token)-index;i++){
		trimmed[i]=token[index+i];
	}	
	//trim trailing
	index=strlen(trimmed)-1;
	while(trimmed[index] == ' '){
		index--;
	}	
	trimmed[index+1]='\0';	
    return trimmed;
}

//adds record node to end;
void addRecToEnd(CSVrecord** head, CSVrecord *node){
	CSVrecord *last = *head;
	
    if (*head == NULL){
       *head = node;
       return;
    }
    while (last->next != NULL)
        last = last->next;
 
    last->next = node;
    return;
}

//prints one Record Node
void printRecNode(CSVrecord *rec){
	printf("Record contents:\n");
	int i;
	printf("sortVal:\t%s\n",rec->sortVal);
	printf("numCols:\t%d\n",rec->numCols);
	printf("data values:\t");
	for(i=0;i<rec->numCols; i++){
			printf("'%s'\t",rec->data[i]);
	}
	printf("\n");
}

//prints entire linked list of recnodes
void printAllRecords(CSVrecord *frontRec){
	CSVrecord *ptr = frontRec;
	while (ptr!=NULL){
		printRecNode(ptr);
		printf("\n\n");
		ptr=ptr->next;
	}
	printf("\n");
}








int main(int argc, char *argv[] ){ //--------------------MAIN---------------------------------------
	
	if(argc<3){
		printf("error, must specify column to search by\n");
		return 1;
	}
	
	char* colToSort = (char*)malloc(sizeof(char)*(strlen(argv[2]+1)));
	strcpy(colToSort, argv[2]);
	printf("sort by: %s\n", colToSort);		
	
	FILE *file;
	file = stdin;
	
	
	int sortPos=0;
	char* str;
	str = (char*)malloc(sizeof(char)*2000); //string buffer
	char* token;
	token = (char*)malloc(sizeof(char)*2000);
	
	//get headers
	fgets(str, 500 , file);
		
   	char* rest = (char*)malloc(sizeof(char)*1000);
   	rest = str;
   	
   	//table headers array
   	//REALLOC!!!!!
   	char** headers = (char**)malloc(sizeof(char*)*50);
   	int count = 0;
   	
   	//tokenizes the headers
	while ((token = strtok_r(rest, ",", &rest))){ 
        	
        	//loads headers into array
        	headers[count] = malloc((strlen(token)+1)*sizeof(char));
        	if (token[strlen(token)-1] == '\n'){ 
				token=stripNewLineChar(token,strlen(token));
		    } 
        	strcpy(headers[count],token);
        	
        	//finds col pos to sort by
        	if(strcmp(token,colToSort)==0){
        		sortPos=count;
        		printf("arr positon of column to sort is\t%d\n",sortPos);
        	}
        	
        	count++;
       }
  
   int numCols = count;
   //printf("num columns: %d\n", numCols);
   
   	printf("headers:\n");
   	for (count=0; count<numCols; count++){
   		printf("%s\n", headers[count]);
   	}
   	
   	CSVrecord * frontRec = NULL;
    
	int i=0;
	
	while(fgets(str,500,file)!=NULL){ //EACH ITERATION IS READING ONE LINE	
		
		CSVrecord *record = malloc(sizeof(CSVrecord));
		record->next=NULL;
		record->data=malloc(30*sizeof(char*)); 
		
		printf("LINE %d: %s", i+1, str);
		count=0;
		
		//int tokLen;
			
		char* parseStr = (char*)malloc(strlen(str)*sizeof(str));
		parseStr=str;
			//printf("some testing shit\n");
			int index = 0;
			while ((token = strsep(&parseStr, ",")) != NULL) {
				if (token[strlen(token)-1] == '\n'){ 
					token=stripNewLineChar(token,strlen(token));
				} 
				
				//QUOTE CASE if theres a quote at the beginning of a token aka theres a COMMA within the field
		    	if(token[0]=='"'){
		    		//first token in quote
		    		token=stripFirstChar(token, strlen(token));
		    		//printf("token now\t'%s'\n", token);
		    		char* append = (char*)malloc(2000*sizeof(char));	
		    		strcpy(append, token);		
		    		//token = strsep(&parseStr, ",");
	    			if (token[strlen(token)-1] == '\n'){ 
						token=stripNewLineChar(token,strlen(token));
					}  		
					//end first token in quote
					
					//following tokens in quote;
					int counting=1;
					
		    		do{		    			
		    			//strcat(append,token);		    			
		    			token = strsep(&parseStr, ",");	
		    			if (token==NULL){
		    				break;
		    			} 
		    			//printf("token now %d:\t'%s'\n",counting, token);
		    			append[strlen(append)]=',';
		    			//printf("append %d:\t%s\n",counting, append);
		    			if (token[strlen(token)-1] == '\n'){ 
							token=stripNewLineChar(token,strlen(token));
						}								 
						counting++;   
						strcat(append,token);				    		
		    		} while (searchForQuote(token)==0); 
		   			
		   			token = append;		   
		   			token = stripLastChar(token);			   				   					   					   			
		    	} //END QUOTE CASE
		    	
		    	if (strcmp(token,"")==0){
		    		token = NULL;
		    	}		    	
		    	
				if(token!=NULL)
					token=trimWhiteSpace(token);
				
				
				//*****TOKEN LOADED INTO A STRUCT
				if(index==sortPos){
						//printf("here?");
						record->sortVal=malloc(strlen(token)*sizeof(char));
						strcpy(record->sortVal,token);
				}
				if(token!=NULL){
					record->data[index] = malloc(strlen(token)*sizeof(char));
					strcpy(record->data[index], token);
				} else {
					record->data[index]=NULL;
				}
				//printf("\nfield within struct:\narray entry %d:\t'%s'\n", index, record->data[index]);
				
				index++;
				
		  	 } //END LINE (RECORD)
		printf("\n");
			
			record->numCols=numCols;
			//printf("sortval is:\t%s\nnum cols is \t%d\n", record->sortVal,record->numCols);
			
			//printRecNode(record);
			addRecToEnd(&frontRec,record);
			
			//HERE THE RECORD SHOULD BE COMPLETE
			//ADD RECORD TO LL HERE			
	
		//printf("-----------------------------------------------------------------------\n");				
		i++;
	} //END FILE
	
	
	printAllRecords(frontRec);
	
	//printf("initiating mergesort");
	merge_sort(&frontRec);
	
	return 0;
} //--------------------------------------------END MAIN---------------------------------------------------------


