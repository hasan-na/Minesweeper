#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
/*
 * project1.c
 *
 *  Created on: May 29, 2020
 *      Author: Hasan Nassar
 *      UCID: 30099862
 */

//global variables for use
double updatedScore = 0;
int counter = 0;
int negativeCounter = 0;
int winCounter = 0;
int losecounter = 0;

//logfile function is used to write a message into another file
//Parameters:
//char *message: This is used to display a message into the logfile

void logfile(char *message){

	// initialize variable
	FILE *logfile;

	// open the log file
	logfile = fopen("project1.log", "a");

	// print the contents inside by appending it
	fprintf(logfile, "%s", message);
	//close the file
	fclose(logfile);
}

//randomnum function is used to generate random numbers for each index in the 2d array
//Parameters:
//double low: this is used to represent the low point of the random number generator
//double high: this is used to represent the high point of the random number generator
//int neg: checks if a number is negative
//int size: the size of the board

double randomnum(double low, double high, int neg, int size){
	//generate random numbers
	double random = (double)rand() / RAND_MAX*high-low;

	// random num cannot be 0
	if(random == 0.0){
		random = (double)rand() / RAND_MAX*high-low;
	}
	//make sure random negative numbers do not exceed 20% of board
	if(random < 0.0){
	negativeCounter++;
		if(negativeCounter > ((size*size)*0.2)){
			random = (double)rand() / RAND_MAX*low;
		}
	}
	return random;
}

//initialize function is used to generate random numbers for each index in the 2d array
//Parameters:
//float *board: the 2d array used to play the game
//int size: the dimensions of the game board

void initializeGame(float *board, int size){

	//initialize variables
	double low = 15.0;
	double high = 30.0;
	int boolean = 0;

	//error handling
	if(size < 5){
		printf("Size of board is too small");
		exit(1);
	}

	//error handling
	if(size > 20){
		printf("Size of board is too big");
		exit(1);
	}

	//nested for loop to populate the array
	 for (int i = 0 ; i <= size ; i++){
	  	for (int k = 0; k <= size ; k++){
	  		*(board + i * (size+1) + k) = randomnum(low, high, boolean, size);
	  		//many if statements to populate the board with some surprises
	  		//32 = good reward
	  		if((i == 3) &&(k == 1)){
	  		*(board + i * (size+1) + k) = 32;
	  		}
	  		if((i == 2) &&(k == 3)){
	  		*(board + i * (size+1) + k) = 32;
	  		}
	  		//-32 = bad reward
	  		if((i == 3) &&(k == 4)){
	  		*(board + i * (size+1) + k) = -32;
	  		}
	  		if((i == 2) &&(k == 4)){
	  		*(board + i * (size+1) + k) = -32;
	  	  }
	  		//60 = time bonus
	  		if((i == 2) &&(k == 2)){
	  	    *(board + i * (size+1) + k) = 60;
	  	  }
	  	}
	  }
	}

//display function is used to generate random numbers for each index in the 2d array
//Parameters:
//float *board: 2d array used to play the game
//int size: the dimensions of the board
//int x: x value of the user input
//int y: y value of the user input
//float value: the value of the random number at the specified (x,y) location

void display(float *board, int size, int x, int y, float value){

	//print statements for if a random number is above or below 0 and print statements for surprises
	if((x >= 0) && (y >= 0)){
		//negative number is less than 0
		if((value < 0) && (value > -15)){
				printf("\nBang!! you lost %0.2f points\n", value);
			}
		//positive number is greater than 0
		if((value > 0) && (value < 15)){
				printf("\nUncovered a reward of %0.2f points\n", value);
			}
		//good reward
		if(value == 32){
				printf("\nUncovered a reward good surprise, your score has been multiplied by 2!\n");
			}
		//bad reward
		if(value == -32){
				printf("\nUncovered a reward bad surprise, your score has been divided by 2!\n");
			}
		//time bonus
		if (value == 60){
				printf("\nYou Uncovered a time bonus, you recieved 20 extra seconds!\n");
			}
	}

	// nested for loop to acces each index in the 2d array
		 for (int i = 0 ; i < size ; i++){
			 // print statement for formatting
		    printf("\n");
		  	for (int k = 0; k < size ; k++){
		  		// print the array by each index
		  		// if random number was positive print "+"
		  		if(*(board + i * size + k) == 16){
		  		printf("+");
		  		}
		  		// if random number was negative print "-"
		  		else if(*(board + i * size + k) == -16){
		  		printf("-");
		  		}
		  		// if it was a good surprise print "$"
		  		else if (*(board + i * size + k) == 31){
		  		printf("$");
		  		}
		  		// if it was a bad surprise print "!"
		  		else if (*(board + i * size + k) == -31){
		  		printf("!");
		  		}
		  		// if it was a time bonus print "@"
		  		else if (*(board + i * size + k) == 59){
		  		printf("@");
		  		}
		  		//if it is none of the above then print "X"
		  		else {
		  		printf("X");
		  		}
		  	}
		  }
		 // formatting
		 printf("\n");
	}

//calculateScore is used to update and keep the score maintained
//Parameters:
//double value: the value of the index that the user chose

void calculateScore(double value){

	//if value is a good surprise divide value by 2
	if (value == 32){
		updatedScore = (int)updatedScore << 1;
		//make value 0 so it has no other affect on updatedScore
		value = 0;
	}
	//if value is a bad surprise divide score by 2
	if (value == -32){
			updatedScore = (int)updatedScore >> 1;
			//make value 0 so it has no other affect on updatedScore
			value = 0;
	}
	//if value is a time bonus then make value 0 so it has no affect on score
	if (value == 60){
			value = 0;
		}
	//update the score
	updatedScore += value;
	printf("Score: %0.2f\n", updatedScore);
	counter++;
}

//checkspot is used to check the value of the index the user chose
//Parameters:
//float *board: the 2d array used to play the game
//int size: the dimensions of the array
//int x: the x value of the user input
//int y: the y value of the user input

int checkspot(float *board, int size, int x, int y){

	//initialize variable
	double spotvalue = *(board + x * size + y);
	//if user inputs the same cell it will tell them they already chose that cell
	if ((*(board + x * size + y) == -16) || (*(board + x * size + y) == 16) || (*(board + x * size + y) == 31) || (*(board + x * size + y) == -31) ||(*(board + x * size + y) == -31)){
		printf("You already chose this cell!\n");
		return 0;
	}
	//check if the index had a negative number
	if((spotvalue < 0) && (spotvalue > -15)){
		//make the index value -16 so the display function can print a "-"
		*(board + x * size + y) = -16;
		display(board, size, x, y, spotvalue);
		calculateScore(spotvalue);
	}
	//check if the index had a positive number
	if((spotvalue > 0) && (spotvalue < 15)){
		//make the index value 16 so the display function can print a "+"
		*(board + x * size + y) = 16;
		display(board, size, x, y, spotvalue);
		calculateScore(spotvalue);
	}
	//check if the index was a good surprise
	if((spotvalue == 32)){
		//make the index value 31 so the display function can print a "$"
		*(board + x * size + y) = 31;
		display(board, size, x, y, spotvalue);
		calculateScore(spotvalue);
	}
	//check if the index was a bad surprise
	if((spotvalue == -32)){
		//make the index value -31 so the display function can print a "!"
		*(board + x * size + y) = -31;
		display(board, size, x, y, spotvalue);
		calculateScore(spotvalue);
	}
	//check if the index was a time bonus
	if((spotvalue == 60)){
		//make the index value 59 so the display function can print a "@"
		*(board + x * size + y) = 59;
		display(board, size, x, y, spotvalue);
		calculateScore(spotvalue);
	}
	return 0;
}

//exitgame is used to exit the game when the user desires
//Parameters:
//float *board: the 2d array used to play the game
//int size: the dimensions of the array
//int actualTime: the time remaining
//int elapsedTime: the time the user has spent playing the game
//int x: the x value of the user input
//int y: the y value of the user input

int exitGame(float *board, int size, int actualTime, int elapsedTime, int x, int y){

	//initialize variables
	char termination;
	int time1 = 10*(size+1);

	//see if the user input was where the time bonus was to increment the time by the bonus
	if ((x == 2) && (y == 4)){
	actualTime += 20;
	}

	//calculate time
	actualTime = time1 - elapsedTime;
	//if time is up then they lose
	if(actualTime <= 0){
		printf("GAMEOVER, Time has ran out!\n");
		return 1;
	}
	//constantly ask for user  input to see if they want to quit the game
	printf("If you desire to quit press q, if you desire to keep playing press any other character: ");
	scanf(" %c", &termination);

	//if they quit the game then exit
	if (termination == 'q'){
		return 1;
	}
	//if not the resume playing
	else{
		//when use enters an index counter increments until all pieces on the board are no longer "X", then the user wins
		if((*(board + x * size + y) == -16) || (*(board + x * size + y) == 16) || (*(board + x * size + y) == 31) || (*(board + x * size + y) == -31) ||(*(board + x * size + y) == 59)){
			winCounter += 1;
       		if(winCounter == (size*size)){
		  		printf("GAME OVER! YOU WIN!\n");
		  		return 1;
			  	 }
			   }
			 }
	return 0;
}

//displayTopScores is used to display the top n amount of scores out of all games played
//Parameters:
//int n: user inputs the amount of high scores they want to see

int displayTopScores(int n){
	//initialize variables
	char confirmation;
	char char1[1000];
	//prompt user
	printf("Would you like to see the top scores? (press y for yes or press any other character for no): ");
	//scan answer
	scanf(" %c", &confirmation);
	printf("\n");
	//show top scores if they answered yes
	if(confirmation == 'y'){
		//prompt user
		printf("How many of the top scores would you like to see: ");
		////scan input
		scanf("%d", &n);
		printf("\n");

		// declare file
		FILE * topscores;
		// read log file
		topscores = fopen("project1.log", "r");
		// try to get n amount of lines and print them
		while(fgets(char1, sizeof(char1), topscores)){
		}
		//it doesnt work and i give up :)
		for(int i = 0; i < n; i++){
			printf("%s", char1);
		}

	}
	return 0;
}

//main is used to run the program
//Parameters:
//int argc: the amount of arguments passed in command line
//char *argv[]: specifiy the argument passed
int main(int argc, char *argv[]){

		//initialize variables
		int x, y = 0;
		char msg[100];
		char msg2[100];
		char msg3[100];
		time_t time2;

		//convert argv[1] to string to store in log file because it wouldnt work without it
		size_t len = strlen(argv[1]);
		char *name = malloc(len + 1);
		strcpy(name, argv[1]);

	// if the length of the arguments is not 3 then an error message is displayed

			if(argc != 3){
				printf("Invalid amount of arguments entered");
				return 1;
			}

			// convert the argument from char to int
			int input = atoi(argv[2]);


			// initialize the variables using the userinput from commandline
			float board[input][input];

			//initialize the amount of time the user has depending on the dimensions of the board
			int time1 = 10*(input+1);
			//make time2 equal to time(NULL) for actualTime calculation
			int actualTime = 1;

			// call functions in order for the application to run

			displayTopScores(-1);
			initializeGame(*board, input);
      		display(*board, input, -1, -1, -1);
       		calculateScore(0.0);
			printf("Time: %d\n", time1);
			//prompt user
			printf("\nEnter your move (x, y): ");
			scanf("%d %d,", &x, &y);
			//initiate timer
			time2 = time(NULL);
			//calculate time
			int elapsedTime = time(NULL) - time2;
			//create the timer which is actualTime
			actualTime = time1 - elapsedTime;
			checkspot(*board, input, x, y);
			printf("Time: %d\n", actualTime);

			//if the user input is equal to these values then add the time bonus to actualTime
			 if ((x == 2) && (y == 4)){
			 actualTime += 20;
			 }
			 exitGame(*board, input, actualTime, elapsedTime, x, y);
			//loop to keep the game continuous
			while(actualTime > 0){
				//get user input
				printf("\nEnter your move (x, y): ");
				scanf("%d %d,", &x, &y);
				int elapsedTime = time(NULL) - time2;
				//create the timer which is actualTime
				actualTime = time1 - elapsedTime;
				checkspot(*board, input, x, y);

				//if the user input is equal to these values then add the time bonus to actualTime
				if ((x == 2) && (y == 4)){
				actualTime += 20;
				}
				//Once time runs revert actualTime back to 0
				if (actualTime < 0){
					actualTime = 0;
					printf("Time: %d\n", actualTime);
				}
				//if not then continue playing
				else{
					printf("Time: %d\n", actualTime);
				}

				//if the score falls below 0 after the first move then you lose
			if((updatedScore <= 0.0) && (counter > 2)){
				printf("GAME OVER, Your Score has become less than 0!\n");
				//record all of the data into the logfile
				sprintf(msg, "Name: %s		", name);
				free(name);
				logfile(msg);
				sprintf(msg2, "Score: %0.2f		", updatedScore);
				logfile(msg2);
				//if the time bonus was found then add 20 to elapsedTime before passing it into the logfile
				if ((*(*board + 2 * input + 4) == 59)){
				int time3 = elapsedTime + 20;
				//if the time is over the limit then revert it back to the limit before passing it to the logfile
				if(time3 > (time1 + 20)){
					time3 = time1 + 20;
			    }
				sprintf(msg3, "Duration: %d\n", time3);
				logfile(msg3);
				displayTopScores(-1);
				//after everything was recorded exit application
				exit(1);
				}
				//if time pack was not found
				else{
					int time3 = elapsedTime;
					//if time was over the limit revert back to limit
					if(time3 > time1){
						time3 = time1;
					}
					sprintf(msg3, "Duration: %d\n", time3);
					logfile(msg3);
					displayTopScores(-1);
					//exit after everything was recorded
					exit(1);
     			}
			}

			//check if timer is less than or equal to 0
			else if(actualTime <= 0){
				printf("GAMEOVER, Time has ran out!\n");
				//print all information into logfile
				sprintf(msg, "Name: %s		", name);
				free(name);
				logfile(msg);
				sprintf(msg2, "Score: %0.2f		"		, updatedScore);
				logfile(msg2);
				//check time bonus
				//if timebonus was found
				if ((*(*board + 2 * input + 4) == 59)){
					int time3 = elapsedTime + 20;
					//if time is over limit revert it back to limit
					if(time3 >(time1 + 20)){
						time3 = time1 + 20;
					}
					sprintf(msg3, "Duration: %d\n", time3);
					logfile(msg3);
					displayTopScores(-1);
					//exit when info is recorded
					exit(1);
				}
				//no time bonus
				else{
					int time3 = elapsedTime;
					//if time is over limit then revert back to limit
					if(time3 > time1){
						time3 = time1;
					}
					sprintf(msg3, "Duration: %d\n", time3);
					logfile(msg3);
					displayTopScores(-1);
					//exit when info is recorded
					exit(1);
				}
			}
				//check if the user exited or won the game
				else if((exitGame(*board, input, actualTime, elapsedTime, x, y) == 1)){
				//record all info in logfile
				sprintf(msg, "Name: %s		", name);
				free(name);
				logfile(msg);
				sprintf(msg2, "Score: %0.2f		", updatedScore);
				logfile(msg2);
				//if time pack was discovered
				if ((*(*board + 2 * input + 4) == 59)){
					int time3 = elapsedTime + 20;
					// if the time elapsed is greater than the limit revert it back to the limit
					if (time3 > (time1 + 20)){
						time3 = time1 + 20;
					}
					//record time in logfile
					sprintf(msg3, "Duration: %d\n", time3);
					logfile(msg3);
					displayTopScores(-1);
					exit(1);
				}
				//if time pack was not discovered
				else{
					int time3 = elapsedTime;
					//check if elapsedTime is greater than the time limit
					if(time3 > time1){
						time3 = time1;
					}
					//record duration in logfile
					sprintf(msg3, "Duration: %d\n", time3);
					logfile(msg3);
					displayTopScores(-1);
					//exit after finishing
					exit(1);
				}
			}
		}
 }
