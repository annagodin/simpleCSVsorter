#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "simpleCSVsorter.h"


//COMMAND TO REDIRECT STDOUT TO A FILE:
//cat small.csv | ./simpleCSVsorter -c food > sorted.csv


void freeLL(CSVrecord *frontRec){
	CSVrecord *curr = NULL;
	while ((curr=frontRec)!=NULL){
		frontRec=frontRec->next;
		free(curr);
	}
}

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
	token[tokLen-1]='\0';
	return token;
	/*char* replace = (char*)malloc((tokLen-1)*sizeof(char));
	int i;
	for (i=0; i<tokLen-1; i++){
		replace[i]=token[i];
	}

	return replace;*/
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
	char* trimmed = malloc(sizeof(char)*strlen(token));
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

void addhNodeToEnd(hNode** head, hNode *node){
	hNode *last = *head;
	
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

//prints in csv format
void printCSV (CSVrecord *frontRec){
	CSVrecord *ptr = frontRec;
	//ptr=ptr->next;
	while(ptr!=NULL){
		int i;
		for(i=0;i<ptr->numCols; i++){		
			if(ptr->data[i]==NULL){
				printf("");
			}else {
				printf("%s",ptr->data[i]);
			}
			
			if(i<ptr->numCols-1){
				printf(",");
			}
		}
		printf("\n");
		ptr=ptr->next;
	}

}



int main(int argc, char *argv[] ){ //--------------------MAIN---------------------------------------
	if(argc<3){
		printf("error, must specify column to search by\n");
		return 1;
	}
	
	char* colToSort = (char*)malloc(sizeof(char)*(strlen(argv[2]+1)));
	strcpy(colToSort, argv[2]);
	

	

	FILE *file;
	file = stdin;
	
	
	int sortPos=0;
	char* str;
	str = (char*)malloc(sizeof(char)*800); //string buffer
	
	char* token;
	token = (char*)malloc(sizeof(char)*200);
	

	//get headers
	fgets(str, 900 , file);
	str=stripNewLineChar(str,strlen(str));
	

	
   	char* rest = (char*)malloc(sizeof(char)*800);
   	rest = str;
   	
   	hNode *headersFront = NULL;

   	int count = 0;
   	
   	//tokenizes the headers
   	while ((token = strsep(&rest, ",")) != NULL){
	
        	//loads headers into array
        	char* data = malloc((strlen(token)+1)*sizeof(char));
        	
        	hNode *node = malloc(sizeof(hNode));
        	if (token[strlen(token)-1] == '\n'){
        		//printf("stripping newline"); 
				token=stripNewLineChar(token,strlen(token));
		    } 
        	//strcpy(headers[count],token);
        	strcpy(data,token);
        	node->data=data;
        	addhNodeToEnd(&headersFront, node);

        	
        	//finds col pos to sort by
        	if(strcmp(token,colToSort)==0){
        		sortPos=count;
        	
        	}
        	
        	count++;
       }
  
   


      //sets the number of columns
   int numCols = count;
   
   	
   	CSVrecord * frontRec = NULL;
    
	int i=0;
	
	while(fgets(str,900,file)!=NULL){ //EACH ITERATION IS READING ONE LINE	
		
		CSVrecord *record = malloc(sizeof(CSVrecord));
		record->next=NULL;
		record->data=malloc(numCols*sizeof(char*)); 
		
		count=0;
		
			
		char* parseStr = (char*)malloc((strlen(str)+1)*sizeof(char));
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
		    		char* append = (char*)malloc(strlen(parseStr)*sizeof(char));	
		    		strcpy(append, token);		
	    			if (token[strlen(token)-1] == '\n'){ 
						token=stripNewLineChar(token,strlen(token));
					}  		
					//end first token in quote
					
					//following tokens in quote;
					int counting=1;
					
		    		do{		    			
		    				    			
		    			token = strsep(&parseStr, ",");	
		    			if (token==NULL){
		    				break;
		    			} 
		    			append[strlen(append)]=',';
		    			
		    			if (token[strlen(token)-1] == '\n'){ 
							token=stripNewLineChar(token,strlen(token));
						}								 
						counting++;   
						strcat(append,token);				    		
		    		} while (searchForQuote(token)==0); 
		   			
		   			token = append;		   
		   			   				   					   					   			
		    	} //END QUOTE CASE
		    	
		    	
		    	if (strcmp(token,"")==0){		    		
		    		token = NULL;
		    	}		    	
				
				
				//*****TOKEN LOADED INTO A STRUCT
				if(index==sortPos){
					if (token==NULL){
						record->sortVal=NULL;					
					} else{
						record->sortVal=malloc(strlen(token)*sizeof(char));
						strcpy(record->sortVal,token);
					}
				}
				if(token!=NULL){
					record->data[index] = malloc(strlen(token)*sizeof(char));
					strcpy(record->data[index], token);
				} else {
					record->data[index]=NULL;
				}
				
				index++;
				
		  	 } //END LINE (RECORD)
			
			record->numCols=numCols;
			
			addRecToEnd(&frontRec,record);
			
			//HERE THE RECORD SHOULD BE COMPLETE
			//ADD RECORD TO LL HERE			
	
		i++;
	} //END FILE
	
	
	//printAllRecords(frontRec);
	
	
	
	mergesort(&frontRec);
	
	 int c=0;
   	//prints headers
   	hNode *ptr = headersFront;
   	while (ptr!=NULL){
   		printf("%s",ptr->data);
   		ptr=ptr->next;
   		if(c<numCols-1){
   			printf(",");
   		}
   		c++;
   	}

   	printf("\n");

   	/*
   	for (count=0; count<numCols; count++){
   		printf("%s", headers[count]);
   		if(count<numCols-1){
   			printf(",");
   		}
   	}*/
   	
   	//printf("\n");
	printCSV(frontRec);
	
	
	


	free(frontRec);
	
	fclose(file);
	
	return 0;
} //--------------------------------------------END MAIN---------------------------------------------------------


