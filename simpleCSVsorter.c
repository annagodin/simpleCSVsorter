#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "simpleCSVsorter.h"

int main(int argc, char *argv[] ){ //-----------------MAIN----------------------
	
	FILE *file;
	file = stdin;
	
	char* str;
	str = (char*)malloc(sizeof(char)*1000); //string buffer
	char* token;
	fgets(str, 500 , file);
	printf("string: %s\n",str);
   	char* rest = str;
   	//table headers array
   	char** headers = (char**)malloc(sizeof(char*)*28);
   	int count = 0;
   	
   	//tokenizes the headers
	while ((token = strtok_r(rest, ",", &rest))){ 
        	//loads headers into array
        	headers[count] = malloc((strlen(token)+1)*sizeof(char));
        	if (token[strlen(token)-1] == '\n'){ 
				token=stripNewLineChar(token,strlen(token));
		    } 
        	strcpy(headers[count],token);
        	count++;
       }
   
   	//printing test
   	for (count=0; count<28; count++){
   		printf("%s\n", headers[count]);
   	}
   	
   	
   
    printf("\n");
    
	int i;
	for (i=0; i<6; i++){
		fgets(str, 500 , file);
			count=0;
			CSVRecord *rec;
			printf("line: %s\n", str);
			//uses delimiter (',') to tokenize each line
			rest = str;
			while ((token = strtok_r(rest, ",", &rest))){ 
				int tokLen = strlen(token);
				//last token check - has new line character, we dont want to include that when we store
		    	if (token[strlen(token)-1] == '\n'){ 
					token=stripNewLineChar(token,tokLen);
					tokLen--;
		    	}
		    	printf("next char: %c\n",rest[0]);
		    	printf("%s:\ntoken:'%s', strlen:%d\n", headers[count], token, tokLen, token[tokLen-1]);
				count++;
				printf("------------\n");
	}
	
			printf("----------------------------------------------\n");
		
		
		

	} 
	return 0;
}//-----------------------------------END MAIN--------------------------------

//converts a string to an integer
int stringToInt (char* str){
	
	int dec = 0, i, j, len;
	len = strlen(str);
	for(i=0; i<len; i++){
		dec = dec * 10 + ( str[i] - '0' );
	}
	return dec;
}

//strips new line character off a string
char* stripNewLineChar (char* token,int tokLen){
	char* replace = (char*)malloc((tokLen-1)*sizeof(char));
	int i;
	for (i=0; i<tokLen-1; i++){
		replace[i]=token[i];
	}
	
	return replace;

}
