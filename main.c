#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<dirent.h>
#include<unistd.h>

//AUX STRUCTURES ======================================================================================================

int look_fork(char* str){
    char*pointer=NULL;
    
    pointer=strstr(str," |");
    if(pointer!=NULL){
        return 1;
    }
    return 0;
}

void remove_command(char *string, char *substring) { //Remove the command (substring) from the string
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

int search(char *str,char *searched){ //look for some string - can be use on GREP
	char *pointer;
	pointer=NULL;
	pointer=strstr(str,searched);
	if(pointer!=NULL){
		return 1;
	}
	return 0;
}


// MAIN FUNCTIONS STRUCTURES======================================================================================================

void ls(char* grep, int flag){// flag => 1 means we have a fork in the sentence
	struct dirent *d;
	DIR *dir;
	char* cat=NULL;

	if((dir=opendir(".")) == NULL){
		return NULL;
	}
	if(flag==0){
		while((d=readdir(dir))){
			printf("%s\n", d->d_name);
		}
	}else{
		cat=strstr(d->d_name, grep);
		while((d=readdir(dir))){
			cat=strstr(d->d_name, grep);
			if(cat != NULL){
				printf("%s\n", d->d_name);
			}
			cat=NULL;
		}
	}
}

void more(char* filename, char *grep, int flag){ // flag => 1 means we have a fork in the sentence
	FILE *fp;
	char line[100],*cat;
	cat=NULL;
	
	if(access(filename,F_OK)!= -1){ // access is a function from <unistd.h> and it verifies if the file exists
    	fp=fopen(filename,"r");
    	while(!feof(fp)){
    		if(flag==1){
    			fgets(line, sizeof(line), fp);
    			cat=strstr(line,grep);
    			if(cat!=NULL){
    				puts(line);
    			}
    		}else{
				fgets(line, sizeof(line), fp);
				puts(line);
			}
		}
		fclose(fp);

	} else {
	    printf("\nFile doesn't exist\n\n");
	}
}

char* get_grep(char* str){ //it takes the grep-search-string and returns it without the "grep"
	int tam;
	char* cpy;

	tam=strlen(str);
	cpy=(char*)malloc(sizeof(char)*tam);
	strcpy(cpy,str);
	remove_command(cpy,"grep");
	return cpy;
}

void check_shell_command_fork_grep(char *input,char *cpy){
	char*buf, *pathdir, *aux, *grep=NULL, *grep_path;
	strcpy(cpy,input); 						 //-> Copying user's input to "cpy"
	buf=strtok(input, " "); 				 //-> taking the first argument

	if(strcmp(buf,"ls")==0){ //================> FUNCTION CALL - "LS" COMMAND
			grep=strstr(cpy,"|")+1;
			grep_path=get_grep(grep);
			printf("\n\t\tListing directories\n");
			ls(grep_path,1);


	}else if(strcmp(buf,"pwd")==0){//================> FUNCTION CALL - "PWD" COMMAND
			aux=NULL;
			grep=strstr(cpy,"|")+1;
			grep_path=get_grep(grep);
			aux=strstr(get_current_dir_name(), grep_path);
			if(aux!=NULL){
				printf("\n%s\n\n", get_current_dir_name());
			}

	}else if(strcmp(buf,"more")==0){//================> FUNCTION CALL - "MORE" COMMAND
			remove_command(cpy, "more");				
			grep=strstr(cpy," |");
			*grep='\0';
			grep=grep+strlen(" |");
			grep_path=get_grep(grep);
			more(cpy,grep_path,1);

	}else{
		printf("ERROR: COMMAND UNKNOWN\n");
	}
	free(grep_path);
}

void check_shell_command(char *command){
	char*buf;
	char*cpy;
	cpy=(char*)malloc(sizeof(char)*1024);
	strcpy(cpy,command);
	buf=strtok(command, " ");

	if(strcmp(buf,"cd")==0 ){ //================> FUNCTION CALL- "CD" COMMAND
		remove_command(cpy,"cd ");
		int i=chdir(cpy);
		printf("\nChanged to:[ %s ]\n\n", get_current_dir_name());


	}else if(strcmp(buf,"ls")==0){ //================> FUNCTION CALL - "LS" COMMAND
			printf("\n\t\tListing directories\n");
			ls("",0);


	}else if(strcmp(buf,"pwd")==0){//================> FUNCTION CALL - "PWD" COMMAND
			printf("\nYOU ARE IN: \n%s\n\n", get_current_dir_name());

	}else if(strcmp(buf,"more")==0){//================> FUNCTION CALL - "MORE" COMMAND
				remove_command(cpy, "more");
				printf("CPY: %s\n", cpy);
				more(cpy,"",0);
	}else{
		printf("ERROR: COMMAND UNKNOWN\n");
	}
	free(cpy);
}

void divide_shell_command_fork(char* input, char*cpy){
	char *fork;
	fork=strstr(input," |");
	*fork='\0';
	fork=fork+strlen(" |");
	strcpy(cpy,fork);
}


//======================================================================================================

int main(int argc, char *argv){
	//~~~~~~~~VARIABLES~~~~~~~~

	char input[1024];
	char cpy[1024];
	char *curl_path;
	int fork, have_grep;

	system("clear");
	

	while(1){ 				//~~~~~~~~~~~~~~~~~~~~~~> type "EXIT" or "exit" to leave the program
		
		setbuf(stdin,NULL); 					 //-> solving the "Enter" problem (set buf = NULL)
		curl_path=(char*)get_current_dir_name(); //-> get the curl path
		printf("[ %s ]$User: ", curl_path);
		scanf("%[^\n]",input); 					 //-> read user's command
		fork=look_fork(input); 					 //-> check a fork existance
		system("clear");
		have_grep=search(input, "grep");		 //-> check if the command line have the "grep"


		if(strcmp(input,"exit" )==0 || strcmp(input,"EXIT")==0){ //- - - - - - - - >"exit" the program
			break;

		}else if(strcmp(input, "clear")==0){//- - - - - - - - - - - - - - - - - -s >"clear" the program
			system("clear");


		}else if(fork==1 && have_grep==1){
			check_shell_command_fork_grep(input,cpy);
		}else if(fork==1 && have_grep==0){
			divide_shell_command_fork(input,cpy);
			check_shell_command(input);
			check_shell_command(cpy);
		}else{
			check_shell_command(input);
		}
		
	}
}
