#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<dirent.h>
#include<unistd.h>

void remove_command(char *string, char *substring) { //Remove the command from the string
    char *match;
    int i,len;
    len = strlen(substring);
    match = strstr(string, substring);

    *match = '\0';
    strcat(string, match+len);
    i=0;
    while(string[i]==' '){
        remove_command(string, " ");
        i++;
    }

}

void ls(){
	struct dirent *d;
	DIR *dir;

	if((dir=opendir(".")) == NULL){
		return NULL;
	}
	while((d=readdir(dir))){
		printf("%s\n", d->d_name);
	}

}

void more(char* filename){
	FILE *fp;
	char line[100];
	
	if( access( filename, F_OK ) != -1 ) { // access is a function from <unistd.h> and it verifies if the file exists
    	fp=fopen(filename,"r");
    	while(!feof(fp)){
			fgets(line, sizeof(line), fp);
			puts(line);
		}
		fclose(fp);

	} else {
	    printf("\nFile doesn't exist\n\n");
	}



}


int main(int argc, char *argv){
	char input[1024];
	char cpy[1024];
	char *first_patth,*curl_path;
	char*buf, *pathdir;

	system("clear");
	first_patth=(char*)get_current_dir_name(); //taking the code's directory
	

	while(1){ //type "EXIT" or "exit" to leave the program
		setbuf(stdin,NULL); // solving the "Enter" problem (set buf = NULL)
		curl_path=(char*)get_current_dir_name(); //get the curl path
		printf("[ %s ]$User: ", curl_path);
		scanf("%[^\n]",input); //read user's command
		system("clear");
		strcpy(cpy,input); //Copying user's input to "cpy"
		buf=strtok(input, " "); //taking the first argument

		if(strcmp(cpy,"exit" )==0 || strcmp(cpy,"EXIT")==0){ //- - - - - - - - >"exit" the program
			break;

		}else if(strcmp(buf,"clear")==0){//- - - - - - - - - - - - - - - - - -s >"clear" the program
			system("clear");




		}else if(strcmp(buf,"cd")==0 ){ //================> FUNCTION CALL- "CD" COMMAND
			remove_command(cpy,"cd ");
			if(strcmp(cpy, "~")==0){
				chdir("/home");
				printf("\nChanged to:[ %s ]\n\n", get_current_dir_name());
			}else{
				int i=chdir(cpy);
					printf("\nChanged to:[ %s ]\n\n", get_current_dir_name());
			}




		}else if(strcmp(buf,"ls")==0){ //================> FUNCTION CALL - "LS" COMMAND
			printf("\n\t\tListing directories\n");
			ls();




		}else if(strcmp(buf,"pwd")==0){//================> FUNCTION CALL - "PWD" COMMAND
			printf("\n%s\n\n", get_current_dir_name());


		}else if(strcmp(buf,"more")==0){//================> FUNCTION CALL - "MORE" COMMAND
			remove_command(cpy, "more");
			more(cpy);

		}else{
			printf("ERROR: COMMAND UNKNOWN\n");
		}

	}
}
