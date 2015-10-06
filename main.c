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
	int sequential = 0;
	int parallel = 1; 
	int mode = 0;

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

		/* check that commands and option arguments are valid 
			- includes looking at list(?) of commands
			- checking that the command options are valid 
			(another little lib? more arrays of pointers? 
			- if mode change, set boolean */

		/* check for exit command. If present, exit. */

		/* mode change bool == 1, mode change */
	}


	

	return 0;
}


