/*
==========================================================================

mastermind.c - a simple text-based C program which simulates the game "mastermind"

Copyright (c) 2022 by Znaidi M. Anas.

Github repo: https://github.com/Zeta-Naidi/Mastermind-in-C

==========================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include <string.h>

#define WIDTH 4
#define NUMCOLS 6
#define MAXGUESSES 10

char colour[NUMCOLS+1];
int invalid;
char inputline[161];
char inputstring[WIDTH+1];

int numexact;
int nummissed;
int i,j;
int MAXNUMTRIES;

int playerguess();
int computerguess();
int convert(char string[WIDTH+1], int result[WIDTH]);
int countmatches(int data1[WIDTH], int data2[WIDTH]);
int randcode(int result[WIDTH]);
char output(int therow[WIDTH]);
int showcolours();
int min(int aa, int bb);
int IntfloorReturn(double x);
int seedrand();

int main()
{
    int true[WIDTH];
    int guess[WIDTH];
    int guessnum;
    char c;

    seedrand();

    colour[0] = 'R';
    colour[1] = 'G';
    colour[2] = 'B';
    colour[3] = 'Y';
    colour[4] = 'O';
    colour[5] = 'P';

    MAXNUMTRIES = 12000;
    MAXNUMTRIES = 1000 * pow(NUMCOLS, WIDTH);

    printf("\n***********************************\n");
      printf("WELCOME TO MASTERMIND, made by ZETA.");
    printf("\n___________________________________\n");

    while (1) {
        printf("\nChoose [p]layer or [c]omputer to guess the secret code: ");
	fgets(inputline, 160, stdin);
	if ( (sscanf(inputline, "%c", &c)) > 0 ) {
	    if ( (c=='p') || (c=='P') )
		playerguess();
	    else if ( (c=='c') || (c=='C') )
		computerguess();
	    else
		printf("Invalid response!\n");
        }
    }

    exit(0);

}


int playerguess()
{
    int true[WIDTH];
    int guess[WIDTH];
    int guessnum = 0;

    /* Make up random true. */
    randcode(true);
    /* output(true);  REMOVE THIS LATER! */
    printf("\nOkay, I've made up a secret code with length -> %d .  ", WIDTH);
    showcolours();

    numexact=-1;
    while (numexact<WIDTH) {

	guessnum++;
	invalid = 1;
	
	/* Ends when you guess the code */
	while (invalid==1) {
	    fflush(stdin);
	    printf("\nYour guess #%d:  ", guessnum);
	    fgets(inputline, 160, stdin);
	    strncpy(inputstring, inputline, WIDTH+1);
	    convert(inputstring, guess);
	}
	printf("\nYour attempt #%d is: ", guessnum);
	output(guess);

	countmatches(true, guess);
	printf(".     AllExact = %d;  ExactNumWrongPlace = %d.\n", numexact, nummissed);

    }

    printf("\nYou win in %d guesses!\n\n", guessnum);

}


/*togliere se non riesco a capirlo*/
int computerguess()
{
    int guesses[MAXGUESSES][WIDTH];
    int guessnum = 0;
    int compnum;
    int matchhistory[MAXGUESSES][2];
    int possible;
    int numtries;
    char inputchar;
    int giveup = 0;
    
    fflush(stdin);
    printf("\nMake up a string of %d colours (without repetition), and write it down\n", WIDTH);
    printf("somewhere [DO NOT TYPE IT IN!].  ");
    showcolours();
    printf("Then press return [AND ONLY RETURN!]:  ");
    fgets(inputline, 160, stdin);

    numexact=-1;
    while ( (numexact<WIDTH) && (giveup==0) ) {
        guessnum++;
	possible = numtries = 0;
	while (possible==0) {
	    numtries++;
	    if (numtries >= MAXNUMTRIES) {
	        printf("\nHm ... I think you're lying ... I give up!\n\n");
		giveup = 1;
                break;
	    }
	    randcode(guesses[guessnum]);
	    possible = 1;
	    if (guessnum>1) {
	        for(compnum=1; compnum<guessnum; compnum++) {
		    countmatches(guesses[guessnum], guesses[compnum]);
		    if ( (numexact!=matchhistory[compnum][0]) ||
		            (nummissed!=matchhistory[compnum][1]) ) {
			possible = 0;
			break;
		    }
		}
	    }
	}

if (giveup==0) {
	printf("\nMy guess #%d is:  ", guessnum);
	output(guesses[guessnum]);
	printf("\n");
	numexact = nummissed = -1;
	while ( (numexact<0) || (numexact>WIDTH) ) {
	    printf("Input number matching exactly (followed by return):  ");
	    fgets(inputline, 160, stdin);
	    if ( (sscanf(inputline, "%d", &numexact) == 0) || 
				(numexact<0) || (numexact>WIDTH) )
		    printf("\nInvalid response!\n\n");
	}
	while ( (numexact<WIDTH) && ((nummissed<0) || (nummissed>WIDTH)) ) {
	    printf("Input number matching colour but not position (followed by return): ");
	    fgets(inputline, 160, stdin);
	    if ( (sscanf(inputline, "%d", &nummissed) == 0) || 
	    			(nummissed<0) || (nummissed>WIDTH) )
                printf("\nInvalid response!\n\n");
	}
    printf("Thank you.\n");
	matchhistory[guessnum][0] = numexact;
	matchhistory[guessnum][1] = nummissed;
}

    }

    if (giveup==0)
	printf("\nI win, in %d guesses!\n\n", guessnum);

}


int convert(char string[WIDTH+1], int result[WIDTH])
{
    invalid = 0;

    for (i=0; i<WIDTH; i++) {
	result[i] = -1;
        if ( (string[i] >= '0') && (string[i] < '0'+NUMCOLS) ) {
	    result[i] = string[i] - '0';
	} else {
	    for (j=0; j<NUMCOLS; j++) {
		if ( (string[i] == colour[j]) || 
				(string[i] == colour[j] + 'a' - 'A') ) {
	            result[i] = j;
		}
	    }
	}
	if (result[i]==-1) {
	    invalid = 1;
        }
    }
    if (invalid==1) {
	printf("\nInvalid guess!  ");
	showcolours();
    }
}


int countmatches(int data1[WIDTH], int data2[WIDTH])
{
    int counts1[NUMCOLS];
    int counts2[NUMCOLS];

    for (i=0; i<NUMCOLS; i++) {
        counts1[i] = counts2[i] = 0;
    }

    for (i=0; i<WIDTH; i++) {
        counts1[data1[i]]++;
        counts2[data2[i]]++;
    }

    numexact = nummissed = 0;

    for (i=0; i<WIDTH; i++) {
        if (data1[i] == data2[i])
	    numexact++;
    }

    for (j=0; j<NUMCOLS; j++) {
        nummissed = nummissed + min(counts1[j], counts2[j]);
    }
    nummissed = nummissed - numexact;

}

int randcode(int result[WIDTH])
{
    int match;

    for (i=0; i<WIDTH; i++) {
	match = 1;
	while (match==1) {
	    result[i] = IntfloorReturn( NUMCOLS * drand48() );
	    match = 0;
	    if (i>0) {
	        for (j=0; j<i; j++) {
		    if (result[j]==result[i]) {
		        match=1;
		    }
		}
	    }
	}
    }
}


char output(int therow[WIDTH])
{
    for (i=0; i<WIDTH; i++) {
        printf("%c", colour[therow[i]]);
    }
    /* printf("\n"); */
}


int showcolours()
{
    printf("Colours are: [");
    for (j=0; j<NUMCOLS; j++){
        if(j == NUMCOLS-1)
            printf("%c]", colour[j]);
        else
            printf("%c, ", colour[j]);
    }
	
    printf("\n");
}


int min(int aa, int bb)
{
    if (aa<bb)
        return(aa);
    return(bb);
}


/* IFLOOR */
int IntfloorReturn(double x)  /* returns floor(x) as an integer */
{
    return((int)floor(x));
}
    
    
/* SEEDRAND: SEED RANDOM NUMBER GENERATOR. */
int seedrand()
{
    int i, seed;
    struct timeval tmptv;
    gettimeofday (&tmptv, (struct timezone *)NULL);
    /* seed = (int) (tmptv.tv_usec - 1000000 *
                (int) ( ((double)tmptv.tv_usec) / 1000000.0 ) ); */
    seed = (int) tmptv.tv_usec;
    srand48(seed);
    (void)drand48();  /* Spin it once. */
    return(0);
}
