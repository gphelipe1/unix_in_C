#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<dirent.h>
#include<unistd.h>

<<<<<<< HEAD
//AUX STRUCTURES ======================================================================================================

int look_fork(char* str){
    char*pointer=NULL;
    
    pointer=strstr(str," |");
    if(pointer!=NULL){
        return 1;
    }
    return 0;
}

int numbers_of_forks(char *input){
	int i=0,cont=0;
	while(input[i]!='\0'){
		if(input[i]==' | '){
			cont++;
		}
		i++;
	}
	return cont;
}

void remove_command(char *string, char *substring) { //Remove the command (substring) from the string
=======
void remove_command(char *string, char *substring) { //Remove the command from the string
>>>>>>> 1bea972ccd587d378a2f312966b97928364ad79e
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
<<<<<<< HEAD
}

int search(char *str,char *searched){ //look for some string 
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
=======

}

void ls(){
>>>>>>> 1bea972ccd587d378a2f312966b97928364ad79e
	struct dirent *d;
	DIR *dir;
	int cat;

	if((dir=opendir(".")) == NULL){
		return NULL;
	}
	if(flag==0){
		while((d=readdir(dir))){
			printf("%s\n", d->d_name);
		}
	}else{
		while((d=readdir(dir))){
			cat=search(d->d_name, grep);
			if(cat==1){
				printf("%s\n", d->d_name);
			}
		}
	}
}

void more(char* filename, char *grep, int flag){ // flag => 1 means we have a fork in the sentence
	FILE *fp;
	char line[100];
	int cat;
	
	if(access(filename,F_OK)!= -1){ // access is a function from <unistd.h> and it verifies if the file exists
    	fp=fopen(filename,"r");
    	while(!feof(fp)){
    		if(flag==1){
    			fgets(line, sizeof(line), fp);
    			cat = search(line,grep);
    			if(cat==1){
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

char* get_grep(char* str){
	int tam;
	char* cpy;

	tam=strlen(str);
	cpy=(char*)malloc(sizeof(char)*tam);
	strcpy(cpy,str);
	remove_command(cpy,"grep");
	return cpy;
}
//======================================================================================================


<<<<<<< HEAD
//= = = = = = = = = = = =  M A I N = = = = = = = = = = = = M A I N = = = = = = = = = = = = = M A I N = = 
=======
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

>>>>>>> 1bea972ccd587d378a2f312966b97928364ad79e

int main(int argc, char *argv){
	//~~~~~~~~VARIABLES~~~~~~~~

	char input[1024];
	char cpy[1024];
	char *first_patth,*curl_path;
<<<<<<< HEAD
	char*buf, *pathdir, *aux, *grep=NULL, *grep_path;
	int fork, cat;
=======
	char*buf, *pathdir;
>>>>>>> 1bea972ccd587d378a2f312966b97928364ad79e

	system("clear");
	first_patth=(char*)get_current_dir_name(); //taking the code's directory
	

	while(1){ 				//~~~~~~~~~~~~~~~~~~~~~~> type "EXIT" or "exit" to leave the program
		setbuf(stdin,NULL); 					 //-> solving the "Enter" problem (set buf = NULL)
		curl_path=(char*)get_current_dir_name(); //-> get the curl path
		printf("[ %s ]$User: ", curl_path);
		scanf("%[^\n]",input); 					 //-> read user's command
		fork=look_fork(input); 					 //-> check a fork existance
		system("clear");
		strcpy(cpy,input); 						 //-> Copying user's input to "cpy"
		buf=strtok(input, " "); 				 //-> taking the first argument


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
<<<<<<< HEAD
			if(fork==1){
				grep=strstr(cpy,"|")+1;
				grep_path=get_grep(grep);
				ls(grep_path,1);
			}else{
				printf("\n\t\tListing directories\n");
				ls("",0);
			}

=======
			printf("\n\t\tListing directories\n");
			ls();




		}else if(strcmp(buf,"pwd")==0){//================> FUNCTION CALL - "PWD" COMMAND
			printf("\n%s\n\n", get_current_dir_name());
>>>>>>> 1bea972ccd587d378a2f312966b97928364ad79e

		}else if(strcmp(buf,"pwd")==0){//================> FUNCTION CALL - "PWD" COMMAND
			if(fork==1){
				grep=strstr(cpy,"|")+1;
				grep_path=get_grep(grep);
				cat=search(get_current_dir_name(), grep_path);
				if(cat==1){
					printf("\nYOU ARE IN: \n%s\n\n", get_current_dir_name());
				}
			}else{
				printf("\nYOU ARE IN: \n%s\n\n", get_current_dir_name());
			}

		}else if(strcmp(buf,"more")==0){//================> FUNCTION CALL - "MORE" COMMAND
<<<<<<< HEAD
				if(fork==1){
					remove_command(cpy, "more");				
					grep=strstr(cpy," |");
					*grep='\0';
					grep=grep+strlen(" |");
					grep_path=get_grep(grep);
					more(cpy,grep_path,1);
				}else{	
					remove_command(cpy, "more");
					printf("CPY: %s\n", cpy);
					more(cpy,"",0);
				}
=======
			remove_command(cpy, "more");
			more(cpy);
>>>>>>> 1bea972ccd587d378a2f312966b97928364ad79e

		}else{
			printf("ERROR: COMMAND UNKNOWN\n");
		}
		
	}
<<<<<<< HEAD
	free(grep_path);
}
=======
}
>>>>>>> 1bea972ccd587d378a2f312966b97928364ad79e
