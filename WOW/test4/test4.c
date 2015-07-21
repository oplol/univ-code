#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[]) {

	FILE *fp;
	fp = fopen("input.txt", "r");
	
	int i, j, max_process;
	int detection_starter;
	int connectivity_matrix[10][10], single_matrix[100];
	int pid1, pid2;
	char *read_track;
	char strline[999]; // each line of the string
	
	// initialize the connectivity matrix
	for (i = 0; i < 10; i++) {
		for (j = 0; j < 10; j++) {
			connectivity_matrix[i][j] = 0;
		}	
	}
	
	while(fgets(strline,sizeof(strline),fp) != NULL) {
		
		
		// strip trailing '\n' if it exists
		if(strline[strlen(strline)-1] == '\n') 
			strline[strlen(strline)-1] = 0;
			
		read_track = strtok (strline, "-");
		if(read_track!=NULL)
		{
			int pid1 = atoi(read_track);
			read_track = strtok (NULL," ");
			if(read_track != NULL) 		//detect an edge
			{
				int pid2 = atoi(read_track);
				// if(pid1> 9 || pid2> 9)
				// {
					// int tmp = pid1>pid2?pid1:pid2;
					// printf("input file contains error, there should be at least %d processes.\n", tmp + 1);
					// exit(1);
				// }
				//fill the edge in the connectivity matrix;
				connectivity_matrix[pid1][pid2] = 1;
				single_matrix[pid1*10+pid2] = 1;
			}
			else // detect the initializer
				detection_starter = pid1;	
		}
		
		/* if(strline[strlen(strline)-1] == '\n') 
			strline[strlen(strline)-1] = 0;
		
		// read the sending process number	
		read_track = strtok(strline, "-");
		if (read_track != NULL) {
			pid1 = atoi(read_track); // assign it to pid1
			// read the recving process number
			read_track = strtok(NULL, " ");
			if (read_track == NULL) {
				detection_starter = pid1;
			} else {
					pid2 = atoi(read_track); // assign it to pid2
					
					// if there is a connection between two processes, then assign the corresponding value to 1 in the maxtrix
					connectivity_matrix[pid1][pid2] = 1;
			}
		} */
	}
	
	fclose(fp);
	
	for (i = 0; i < 10; i++) {
		for (j = 0; j < 10; j++) {
			single_matrix[i*10+j] = connectivity_matrix[i][j];
		}
	}
	
	for (i = 0; i < 10; i++) {
		for (j = 0; j < 10; j++) {
			if (j != 0) printf("  ");
			printf("%d", connectivity_matrix[i][j]);
		}
		printf("\n");
	}
	
	printf("detection_starter is %d \n", detection_starter);
	
	for (i = 0; i < 100; i++) {
		printf("%d ", single_matrix[i]);
	}

}

