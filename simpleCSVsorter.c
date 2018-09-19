#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "simpleCSVsorter.h"

int main(int argc, char *argv[] ){ //--------------------------MAIN---------------------------------------
	//testedit
	FILE *file;
	file = stdin;
	
	char* str;
	str = (char*)malloc(sizeof(char)*2000); //string buffer
	char* token;
	token = (char*)malloc(sizeof(char)*2000);
	fgets(str, 500 , file);
	printf("string: %s\n",str);
   	char* rest = (char*)malloc(sizeof(char)*1000);
   	rest = str;
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
   	//smallerdata.csv = 12 columns
   	//smalldata.csv/reg = 28 cols
   	printf("headers:\n");
   	for (count=0; count<12; count++){
   		printf("%s\n", headers[count]);
   	}
   	
   	
    
	int i;
	for (i=0; i<3; i++){
		//printf("\theyyyyyyyy\t%d\n",i);
		fgets(str, 500 , file);
		printf("LINE %d: '%s'\n", i+1, str);
		count=0;
		
		int tokLen;// = strlen(token);
	
		
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
		    		printf("\n\nstarting token:\t'%s'\n", token);
		    		char* append = (char*)malloc(2000*sizeof(char));	
		    		strcpy(append, token);		
		    		token = strsep(&parseStr, ",");
	    			if (token[strlen(token)-1] == '\n'){ 
						token=stripNewLineChar(token,strlen(token));
					}  		
					append[strlen(append)]=',';
					//end first token in quote
					
					//following tokens in quote;
		    		do{		    			
		    			strcat(append,token);
		    			printf("append so far: '%s'\n", append);
		    			
		    			token = strsep(&parseStr, ",");	
		    			printf("fresh token: %s\n", token);	
		    			if (token==NULL){
		    				break;
		    			} 
		    			append[strlen(append)]=',';
		    			if (token[strlen(token)-1] == '\n'){ 
							token=stripNewLineChar(token,strlen(token));
						}								    			    		
		    		} while (searchForQuote(token)==0); 
		   			
		   			token = append;		   
		   			token = stripLastChar(token);			   				   					   					   			
		    	} //END QUOTE CASE
		    	
				printf("%s:\n'%s'\n", headers[index], token);
				index++;
				
				
				//*****TODO: THIS IS WHERE THE TOKEN SHOULD BE LOADED INTO A STRUCT
				
		  	 } //END LINE (RECORD)
		printf("\n");
			
			//******TODO: HERE THE RECORD SHOULD BE COMPLETE
			//******TODO: ADD RECORD TO LL HERE			
	
		printf("-----------------------------------------------------------------------\n");
		
		
		

	} 
	return 0;
}//----------------------------------------END MAIN---------------------------------------------------------

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
	//printf("inside function BEFORE str: '%s'\n", token);
	char* replace = (char*)malloc((tokLen-1)*sizeof(char));
	int i;
	for (i=0; i<tokLen-1; i++){
		replace[i]=token[i];
	}
	//printf("inside function str: '%s'\n", replace);

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
		if (token[i]=='"')
			return 1;
	}
	return 0;
}
