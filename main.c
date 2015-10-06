#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <poll.h>
#include <signal.h>

/* main helper functions */

char** parse(const char *s, char* split) {
	char* token; 
	char* count_cpy = strdup(s);
	char* tok_cpy = strdup(s);

	int count = 0;
	for (token = strtok(count_cpy, split); token != NULL; 
		token = strtok(NULL, split)) { 
		count++;
	} 

	int size = sizeof(char*);
	char** tokens = malloc((count+1) * size);

	int i = 0;
	for (token = strtok(tok_cpy, split); token != NULL; 
		token = strtok(NULL, split)) { 
		tokens[i] = strdup(token);
		i++;
	}
	tokens[count] = NULL;
	free(count_cpy);
	free(tok_cpy);
	return tokens;
}

void print_tokens(char *tokens[]) {
    int i = 0;
    while (tokens[i] != NULL) {
        printf("Token %d: %s\n", i+1, tokens[i]);
        i++;
    }
}

void free_tokens(char **tokens) {
    int i = 0;
    while (tokens[i] != NULL) {
        free(tokens[i]); // free each string
        i++;
    }
    free(tokens); // then free the array
}



/* MAIN */ 

int main(int argc, char **argv) {

	// mode settings
	//sequential = 0;
	//parallel = 1; 
	int mode = 0;
	int change = 0;
	char mode_arr[] = {"sequential", "parallel"};

	// command prompt loop
	char * prompt = "Prompt: ";
	printf("%s", prompt);
	fflush(stdout); //prints immediately 

    char buffer[1024];
	while (fgets(buffer, 1024, stdin) != NULL) {
		/*parse input --> array of pointers filled with arrays of 
		pointers */

		char** command_chunks = parse(buffer, ';'); //parse by ';'
		
		// while loop to get size of command_chunks
		chunk_count = 0;
		while (command_chunks[chunk_count] != NULL) {
			chunk_count++;
		}

		char*** command_list = malloc((chunk_count+1)*(sizeof(char**));
    		char* whitespace = " \t\n";
		for (int i = 0; i < chunk_count; i++) {
			command_list[i] = parse(command_chunks[i], 
			whitespace);
		}
		command_list[chunk_count] = NULL;

		if (mode == 0) {       // sequential mode
			int i = 0;
	  	    while (command_list[i] != NULL) {
				int j = 0;
  				if (strcmp(command_list[i][j], "exit")) {
			    	printf("Exit called. Goodbye.");
			    	fflush(stdout);
			    	exit(); 
				}
				else if (strcmp(command_list[i][j], "mode")) {
		   	    	j++;
			    	if (*command_list[i][j] == NULL) {
						printf("Current mode: %s\n", mode_arr[mode]);
			    	}
			    	else if (*command_list[i][j] == 's') {
						change = 0;
			    	}
			    	else if (*command_list[i][j] == 'p') {
						change = 1;
			    	}
				}
				else {
			    	pid_t p = fork(); 
			    	if (p == 0) {
						if (execv(command_list[i][j], command_list[i]) < 0) {
			           		fprintf(stderr, "execv failed: %s\n", strerror(errno));
						}
			    	}
			    	else if (p > 0) {
						wait(&p);
			    	}
				}
				i++;
			}

		else if (mode == 1) { //parallel
			int i = 0;
			while (command_list[i] != NULL) {
				int j = 0;
  				if (strcmp(command_list[i][j], "exit")) {
			    	printf("Exit called. Goodbye.");
			    	fflush(stdout);
			    	exit(); 
				}
				else if (strcmp(command_list[i][j], "mode")) {
		   	    	j++;
			    	if (*command_list[i][j] == NULL) {
						printf("Current mode: %s\n", mode_arr[mode]);
			    	}
			    	else if (*command_list[i][j] == 's') {
						change = 0;
			    	}
			    	else if (*command_list[i][j] == 'p') {
						change = 1;
			    	}
				}
				else {
					pid_t pid_array[chunk_count+1];// last idx == NULL?
					int arr_idx = 0;
					int k = 0;	
					int worked = 0; //Kt
					while (k < chunk_count) {
						pid_t p = fork(); 
						if (p == 0) {
							if (execv(command_list[i][j], command_list[i]) < 0) {
			           			fprintf(stderr, "execv failed: %s\n", strerror(errno));	
								/*worked = 0; //Kt's crap 
							}
							else {
								worked = 1; */
							}	
						}
						else if (p > 0) {
						}
						k++;
					}
				}
		}	
			
		 
		/*- if mode change, set boolean */

		/* check for exit command. If present, exit. */

		/* mode change bool == 1, mode change */
	}


	

	return 0;
}


