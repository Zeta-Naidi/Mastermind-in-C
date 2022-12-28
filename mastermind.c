/*		Librerie		*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

/*		MACRO		*/
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_BLUE    "\x1b[34m"





#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

/*		Variabili Globali		*/
char secretCode[4];
char rows[8][4];
char tries[8][4];
char hiden[4];

/*		Prototipo delle Funzioni		*/
void title(void);
void generateSecretCode(void);
void printBoard(void);
void instructions(void);
void good_bye(void);
void initializeBoard(void);
void startGame(void);
void motor(int chances);
int check_input(char *number);
void combo(void);
void lose(void);
void compare(int chances, char *number);
void congratulations(void);
void fill_rows(int chances, int black, int white);

/*		Main		*/
int main(void)
{
	title();
	instructions();
	return (0);
}
/**
 * title - funzione per stampare il titolo del gioco
 */
void title(void)
{
	char *title1 = ANSI_COLOR_GREEN ".___  ___.      ___           _______.___________. _______ .______      .___  ___.  __  .__   __.  _______       _______      ___      .___  ___.  _______ \n" ANSI_COLOR_RESET;
	char *title2 = ANSI_COLOR_GREEN "|   \\/   |     /   \\         /       |           ||   ____||   _  \\     |   \\/   | |  | |  \\ |  | |       \\     /  _____|    /   \\     |   \\/   | |   ____|\n" ANSI_COLOR_RESET;
	char *title3 = ANSI_COLOR_GREEN "|  \\  /  |    /  ^  \\       |   (----`---|  |----`|  |__   |  |_)  |    |  \\  /  | |  | |   \\|  | |  .--.  |   |  |  __     /  ^  \\    |  \\  /  | |  |__   \n" ANSI_COLOR_RESET;
	char *title4 = ANSI_COLOR_GREEN "|  |\\/|  |   /  /_\\  \\       \\   \\       |  |     |   __|  |      /     |  |\\/|  | |  | |  . `  | |  |  |  |   |  | |_ |   /  /_\\  \\   |  |\\/|  | |   __|  \n" ANSI_COLOR_RESET;
	char *title5 = ANSI_COLOR_GREEN "|  |  |  |  /  _____  \\  .----)   |      |  |     |  |____ |  |\\  \\----.|  |  |  | |  | |  |\\   | |  '--'  |   |  |__| |  /  _____  \\  |  |  |  | |  |____ \n" ANSI_COLOR_RESET;
	char *title6 = ANSI_COLOR_GREEN "|__|  |__| /__/     \\__\\ |_______/       |__|     |_______|| _| `._____||__|  |__| |__| |__| \\__| |_______/     \\______| /__/     \\__\\ |__|  |__| |_______|\n" ANSI_COLOR_RESET;
	char *title7 = ANSI_COLOR_GREEN "\t\t\t\t\t             _   _     _                                     _                         \n" ANSI_COLOR_RESET;
	char *title8 = ANSI_COLOR_GREEN "\t\t\t\t\t __      __ (_) | |_  | |__      _ __    _   _   _ __ ___   | |__     ___   _ __   ___ \n" ANSI_COLOR_RESET;
	char *title9 = ANSI_COLOR_GREEN "\t\t\t\t\t \\ \\ /\\ / / | | | __| | '_ \\    | '_ \\  | | | | | '_ ` _ \\  | '_ \\   / _ \\ | '__| / __|\n" ANSI_COLOR_RESET;
	char *title10 = ANSI_COLOR_GREEN "\t\t\t\t\t  \\ V  V /  | | | |_  | | | |   | | | | | |_| | | | | | | | | |_) | |  __/ | |    \\__ \\\n" ANSI_COLOR_RESET;
	char *title11 = ANSI_COLOR_GREEN "\t\t\t\t\t   \\_/\\_/   |_|  \\__| |_| |_|   |_| |_|  \\__,_| |_| |_| |_| |_.__/   \\___| |_|    |___/" ANSI_COLOR_RESET;

	system("clear");
	printf("%s%s%s%s%s%s%s%s%s%s%s\n\n\n", title1, title2, title3, title4, title5, title6, title7, title8, title9, title10, title11);
}
/**
 * instructions - funzione per stamapare la istruzioni
 * Return: void
 */
void instructions(void)
{
	char next;

	printf("\n\n\t\t\t\t\t\tREGOLAMENTO: Il computer genererà un Codice Segreto di 4 numeri.\n");
	puts("\t\t\t\t\t\tLo scopo del gioco è scoprire questo codice, sarà composto da numeri tra 1 e 6\n");
	puts("\t\t\t\t\tPer ogni tentativo verrà stampato il numero di 'numeri' che sono presenti nel Codice Segreto");
	puts("\t\t\t\t\t Ti verrà anche detto quante delle cifre sono nella posizione corretta nel numero segreto.");
	puts("\t\t\t\tAttraverso un processo di eliminazione, dovresti essere in grado di dedurre i numeri corretti utilizzando la logica.");
	printf("\n\t\t\t\t\t\t\t    X --> POSIZIONE CORRETTA      O --> POSIZIONE SBAGLIATA");
	printf("\n\t\t\t\t\t\tAvrai a disposizione soltanto 8 possibilità. Premi ENTER per iniziare il gioco!");
	printf("\n\n\t\t\t\t\t\t\t\t[ Premi Ctrl + D per uscire in qualsiasi momento ]\n");
	next = getchar();
	//EOF = End Of File -- End Of Line
	if (next == EOF)
	{
		system("clear");
		good_bye();
		sleep(2);
		exit(EXIT_SUCCESS);
	}
	else if (next == 10)
		startGame();
}
/**
 * startGame - funzione (main) con il loop del gioco
 */
void startGame(void)
{
    // max num tries+1 (in questo caso 8 chances)
	int chances = 7;

	generateSecretCode();
	initializeBoard();
	while (1 && chances >= 0)
	{
		system("clear");
		title();
		printBoard();
		motor(chances);
		chances--;
	}
	lose();
}
/**
 * generateSecretCode - genera il codice segreto
 */
void generateSecretCode(void)
{
	int i, n;

	srand(time(0));
	for (i = 0; i < 4; i++)
	{
		n = (rand() % 6) + 49;
		
		// genera codice SENZA ripetizioni
		
		/*if (secretCode[0] == n || secretCode[1] == n
		|| secretCode[2] == n || secretCode[3] == n)
			i--;
		else*/
		
		secretCode[i] = n;
	}
}
/**
 * initializeBoard - funzione per inizializzare la console
 */
void initializeBoard(void)
{
	int i, j;

	for (j = 0; j < 4; j++)
		hiden[j] = '?';
	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 4; j++)
		{
			rows[i][j] = '_';
			tries[i][j] = '_';
		}
	}
}
/**
 * check_input - funzione per evitare input diversi da numeri
 * ritorna 0 se tutti i 'caratteri' sono numeri, se no ritorna -1
 */
int check_input(char *number)
{
	int i;

	for (i = 0; i < 4; i++)
		if (!isdigit(number[i]))
			return (0);
	return (1);
}
/**
 * motor - funzione per prendere l'input dell'utente
 * compreso di controlli sul tipo e sulla lunghezza
 */
void motor(int chances)
{
	char *number = NULL;
	size_t size = 0;
	int c, length;

	if (number)
		free(number);
	c = getline(&number, &size, stdin);
	if (c == EOF)
	{
		free(number);
		good_bye();
	}
	length = strlen(number);
	if (length > 5)
	{
		combo();
		printf(ANSI_COLOR_RED "\t\t\t\t\t\t\t\t\tMassimo 4 cifre\n" ANSI_COLOR_RED);
		motor(chances);
	}
	else if (length < 5)
	{
		combo();
		printf(ANSI_COLOR_RED "\t\t\t\t\t\t\t\t\tMinimo 4 cifre\n" ANSI_COLOR_RED);
		motor(chances);
	}
	else
		if (check_input(number))
			compare(chances, number);
		else
		{
			combo();
			printf(ANSI_COLOR_RED "\t\t\t\t\t\t\t\tSono ammessi solo numeri\n" ANSI_COLOR_RED);
			motor(chances);
		}
	free(number);
}
/**
 * combo - funzione per pulire la console, stampa il titolo e la tavola
 */
void combo(void)
{
	system("clear");
	title();
	printBoard();
}
/**
 * compare - funzione per controlllare che la combinazione inserita dall'utente corrisponda con il codice segreto
 * @chances: contatore del numero di chances del giocatore
 * @number: the number from the input of the player
 * Return: void
 */
void compare(int chances, char *number)
{
	int i, j, k, black_asserts = 0, white_asserts = 0;
	char *copy = NULL;

	copy = strdup(secretCode);
	/* compare black key pegs */
	for (i = 0; i < 4; i++)
		if (number[i] == copy[i])
		{
			black_asserts++;
			copy[i] = '0';
		}
	if (black_asserts == 4)
		congratulations();
	/* compare white key pegs */
	for (j = 0; j < 4; j++)
	{
		for (k = 0; k < 4; k++)
		{
			if (copy[j] == number[k] && copy[j] != '0')
			{
				white_asserts++;
				copy[j] = '0';
				break;
			}
		}
	}
	for (i = 0; i < 4; i++)
		tries[chances][i] = number[i];
	free(copy);
	fill_rows(chances, black_asserts, white_asserts);
}
/**
 * fill_rows - funzione per riemire la tavola
 * @chances: counter for the amount of chances that the player has
 * @black: the amount of correct matches that the player made
 * @white: the amount of numbers in the secret code but does not matche
 * Return: void
 */
void fill_rows(int chances, int black, int white)
{
	int i, j;

	for (i = 0; i < black; i++)
		rows[chances][i] = 'X';
	for (j = 0; j < white; i++, j++)
		rows[chances][i] = 'O';
}
/**
 * printBoard - funzione per stamapare la tavola
 * Return: void
 */
void printBoard(void)
{
	int i, j;

	printf("\t\t\t\t\t\t\t\t");
	for (j = 0; j < 4; j++)
		printf("%c	 ", hiden[j]);
	putchar(10);
	for (i = 0; i < 8; i++)
	{
		printf("\t\t\t\t\t\t\t\t");
		for (j = 0; j < 4; j++)
			printf("%c	 ", rows[i][j]);
		putchar(10);
		printf("\t\t\t\t\t\t\t\t");
		for (j = 0; j < 4; j++)
			printf(ANSI_COLOR_CYAN "%c	 " ANSI_COLOR_RESET, tries[i][j]);
		putchar(10);
	}
	printf("\n\t\t\t\t\t\tOgni X indica che uno dei numeri è nella posizione giusta,\n");
	printf("\t\t\t\te ogni O indica che uno dei numeri è all'interno del Codice segreto ma nella posizione sbagliata\n");
	printf("\n\t\t\t\t\t\t    X --> POSIZIONE CORRETTA      O --> POSIZIONE SBAGLIATA");
	printf("\n\n\t\t\t\t\t\t\t      Scrivi un numero di 4 cifre\n");
}
/**
 * congratulations - funzione "congratulations" per la vincita del giocatore
 * Return: void
 */
void congratulations(void)
{
	char *cgrts1 = ANSI_COLOR_RED "\t  ______   ______   .__   __.   _______ .______           ___      .___________. __    __   __           ___      .___________. __    ______   .__   __.      _______.\n" ANSI_COLOR_RESET;
	char *cgrts2 = ANSI_COLOR_RED "\t /      | /  __  \\  |  \\ |  |  /  _____||   _  \\         /   \\     |           ||  |  |  | |  |         /   \\     |           ||  |  /  __  \\  |  \\ |  |     /       |\n" ANSI_COLOR_RESET;
	char *cgrts3 = ANSI_COLOR_RED "\t|  ,----'|  |  |  | |   \\|  | |  |  __  |  |_)  |       /  ^  \\    `---|  |----`|  |  |  | |  |        /  ^  \\    `---|  |----`|  | |  |  |  | |   \\|  |    |   (----`\n" ANSI_COLOR_RESET;
	char *cgrts4 = ANSI_COLOR_RED "\t|  |     |  |  |  | |  . `  | |  | |_ | |      /       /  /_\\  \\       |  |     |  |  |  | |  |       /  /_\\  \\       |  |     |  | |  |  |  | |  . `  |     \\   \\    \n" ANSI_COLOR_RESET;
	char *cgrts5 = ANSI_COLOR_RED "\t|  `----.|  `--'  | |  |\\   | |  |__| | |  |\\  \\----. /  _____  \\      |  |     |  `--'  | |  `----. /  _____  \\      |  |     |  | |  `--'  | |  |\\   | .----)   |   \n" ANSI_COLOR_RESET;
	char *cgrts6 = ANSI_COLOR_RED "\t \\______| \\______/  |__| \\__|  \\______| | _| `._____|/__/     \\__\\     |__|      \\______/  |_______|/__/     \\__\\     |__|     |__|  \\______/  |__| \\__| |_______/    \n" ANSI_COLOR_RESET;

	system("clear");
	printf("%s%s%s%s%s%s", cgrts1, cgrts2, cgrts3, cgrts4, cgrts5, cgrts6);
	exit(EXIT_SUCCESS);
}
/**
 * good_bye - funzione per salutare il giocatore
 * Return: void
 */
void good_bye(void)
{
	char *bye1 = ANSI_COLOR_BLUE "\t\t                              _     _                      _ \n" ANSI_COLOR_RESET;
	char *bye2 = ANSI_COLOR_BLUE "\t\t   __ _    ___     ___     __| |   | |__    _   _    ___  | |\n" ANSI_COLOR_RESET;
	char *bye3 = ANSI_COLOR_BLUE "\t\t  / _` |  / _ \\   / _ \\   / _` |   | '_ \\  | | | |  / _ \\ | |\n" ANSI_COLOR_RESET;
	char *bye4 = ANSI_COLOR_BLUE "\t\t | (_| | | (_) | | (_) | | (_| |   | |_) | | |_| | |  __/ |_|\n" ANSI_COLOR_RESET;
	char *bye5 = ANSI_COLOR_BLUE "\t\t  \\__, |  \\___/   \\___/   \\__,_|   |_.__/   \\__, |  \\___| (_)\n" ANSI_COLOR_RESET;
	char *bye6 = ANSI_COLOR_BLUE "\t\t  |___/                                     |___/            " ANSI_COLOR_RESET;

	system("clear");
	printf("%s%s%s%s%s%s\n\n\n\n\n", bye1, bye2, bye3, bye4, bye5, bye6);
	exit(EXIT_SUCCESS);
}
/**
 * lose - funzione che mostra 'Try again' quando il giocatore perde
 * Return: void
 */
void lose(void)
{
	char *try1 = ANSI_COLOR_RED "\t\t\t\t     _____                                            _           _ \n" ANSI_COLOR_RESET;
	char *try2 = ANSI_COLOR_RED "\t\t\t\t    |_   _|  _ __   _   _      __ _    __ _    __ _  (_)  _ __   | |\n" ANSI_COLOR_RESET;
	char *try3 = ANSI_COLOR_RED "\t\t\t\t      | |   | '__| | | | |    / _` |  / _` |  / _` | | | | '_ \\  | |\n" ANSI_COLOR_RESET;
	char *try4 = ANSI_COLOR_RED "\t\t\t\t      | |   | |    | |_| |   | (_| | | (_| | | (_| | | | | | | | |_|\n" ANSI_COLOR_RESET;
	char *try5 = ANSI_COLOR_RED "\t\t\t\t      |_|   |_|     \\__, |    \\__,_| \\__,  |  \\__,_| |_| |_| |_| (_)\n" ANSI_COLOR_RESET;
	char *try6 = ANSI_COLOR_RED "\t\t\t\t                    |___/             |___/                         " ANSI_COLOR_RESET;
	char next;
	int i;

	system("clear");
	printf("%s%s%s%s%s%s\n", try1, try2, try3, try4, try5, try6);
	printf("\n\t\t\t\t\t\t\tIl codice segreto era: ");
	for (i = 0; i < 4; i++)
		printf("%c", secretCode[i]);
	printf("\n\t\t\t\tPremi Ctrl + D per uscire oppure ENTER per iniziare una nuova partita!\n");
	next = getchar();
	if (next == EOF)
	{
		system("clear");
		good_bye();
		sleep(2);
		exit(EXIT_SUCCESS);
	}
	else
		startGame();
}
