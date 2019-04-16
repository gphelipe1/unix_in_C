#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<dirent.h>
//#include<unistd.h>
//#include<errno.h>

void remove_command(char *string, char *sub) {
    char *match;
    int i,len;
    len = strlen(sub);
    match = strstr(string, sub);

    *match = '\0';
    strcat(string, match+len);
    i=0;
    while(string[i]==' '){
        remove_command(string, " ");
        i++;
    }
    
}

void ls(){ // - - - - -> OK, BUT HAVE SOME DOTS ISSUES
	struct dirent *d;
	DIR *dir;

	if((dir=opendir(".")) == NULL){
		return NULL;
	}
	while((d=readdir(dir))){
		printf("%s\n", d->d_name);
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




		}else if(strcmp(buf,"cd")==0 ){ //================> FUNCTION - "CD" COMMAND
			remove_command(cpy,"cd ");
			int i=chdir(cpy);

			if(strcmp(first_patth, get_current_dir_name())==0){
				printf("\n\tCould not change directory, something is wrong\n\n");

			}else if(strcmp(first_patth,cpy)==0){
				printf("\nChanged to:[ %s ]\n\n", first_patth);;

			}else{
				printf("\nChanged to:[ %s ]\n\n", get_current_dir_name());
			}




		}else if(strcmp(buf,"ls")==0){ //================> FUNCTION - "LS" COMMAND
			printf("\n\t\tListing directories\n");
			ls();




		}else if(strcmp(buf,"pwd")==0){
			printf("\n%s\n\n", get_current_dir_name());//================> FUNCTION - "PWD" COMMAND




		}else{
			printf("ERROR: COMMAND UNKNOWN\n");
		}

	}
}