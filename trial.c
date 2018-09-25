#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



int is_digit(char*str){
	printf("now we are in is_digit()\n");

        int i;
        int isDec = 0;

        for(i = 0; i < strlen(str); i++){
		printf("WE ARE NOW IN FOR LOOP\n");

                if((!isdigit(str[i])) && str[i] != '.'){
                        printf("the string is not a number. \n");
			return 0;       //the string is not a number
		}	
                if(str[i] == '.'){
			printf("the string has a period in it\n");
                        isDec = 1;
        	}
		if(isdigit(str[i])){
			printf("str[%d] val is: %c\n", i, str[i]);
			continue;
		}
	}

        if(isDec == 1){
		printf("the string is a decimal. \n");
                return 2;       //the string is a decimal
        }
	else if(isDec != 1){
		printf("the string is an integer. \n");
                return 1;       //integer
        }


	printf("this failed lol\n");
	return -1;
}


int main(){

	/*testing to see if a string*/
	char str[20] = "shrek 2";
	char* ptrtostr = str;
	printf("the string is: %s\n", ptrtostr);
	is_digit(ptrtostr);
	
	/*testing to see if an int*/
	//char str2[10] = "153.80";
	//char* ptrtostr2 = str2;
	//printf("the string is: %s\n", ptrtostr2);
	//is_digit(ptrtostr2);
	
	
	return 0;

}
