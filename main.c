/* ----------------------------------------

ALL OF THE CODE WILL BE IN THIS SOURCE FILE

-------------------------------------------

This was all coded entirely by me, Aliics.
It's very sloppy, but it's not supposed to
be very readable. In fact, it's suppose to
be the exact opposite to be sort of a test
of my C abilities to read code. Which is
entirely the point because I have no done
C in essentially years. Although it's very
familiar due to the large amount of Java &
C# experience that I have obtained.

---------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define HELP_OPTION '?'
#define ADD_OPTION '+'
#define SUB_OPTION '-'
#define MLT_OPTION '*'
#define DIV_OPTION '/'
#define PWR_OPTION '^'
#define EQL_OPTION '='
#define BCK_OPTION '<'
#define FWD_OPTION '>'
#define CLR_OPTION '!'
#define EXT_OPTION '.'

#ifdef __unix__
#define COLOUR_RESET "\x1b[0m"
#define COLOUR_RED "\x1b[31m"
#define COLOUR_GREEN "\x1b[32m"
#define COLOUR_YELLOW "\x1b[33m"
#define COLOUR_BLUE "\x1b[34m"
#define COLOUR_MAGENTA "\x1b[35m"
#define COLOUR_CYAN "\x1b[36m"
#elif _WIN64
#define COLOUR_RESET "^[[0;30;40m"
#define COLOUR_RED "^[[0;31;41m"
#define COLOUR_GREEN "^[[0;32;42m"
#define COLOUR_YELLOW "^[[0;33;43m"
#define COLOUR_BLUE "^[[0;34;44m"
#define COLOUR_MAGENTA "^[[0;35;45m"
#define COLOUR_CYAN "^[[0;36;46m"
#endif

int main() {
	int programExitCode = 0;
	
	bool exitProgram;

	char optionInput;
	float numberInput;
	
	char* operations = (char*) malloc(1024 * sizeof(char));
	float* backlist = (float*) malloc(1024 * sizeof(float));
	int currentOperation = 0;
	double currentNumber = 0;

	printf(COLOUR_YELLOW "%s\n%s%c%s\n" COLOUR_RESET, 
		"Welcome to the basic console calculator!", 
		"Type '", HELP_OPTION, "' for help."
	);

	backlist[0] = currentNumber;

	while (!exitProgram) {
		scanf("%1s", &optionInput);

		switch (optionInput) {
			case HELP_OPTION:
				printf("\n||%s||\n", "Execute a command with their INPUT and PARAMS");
				printf("\n||%s||\n", "      keys that are listed in the table      ");
				printf("\n|%s\t|%s\t\t|%s\t\t|\n", "COMMAND", "INPUT", "PARAMS");
				printf("=================================================\n");
				printf("|%s\t|%c\t\t|%s\t|\n", "Addition", ADD_OPTION, "[float]");
				printf("|%s\t|%c\t\t|%s\t|\n", "Subtraction", SUB_OPTION, "[float]");
				printf("|%s\t|%c\t\t|%s\t|\n", "Multiplication", MLT_OPTION, "[float]");
				printf("|%s\t|%c\t\t|%s\t|\n", "Division", DIV_OPTION, "[float]");
				printf("|%s\t|%c\t\t|%s\t|\n", "Power To", PWR_OPTION, "[integer]");
				printf("|%s|%c\t\t|%s\t\t|\n", "Calculate Total", EQL_OPTION, "[null]");
				printf("|%s\t|%c\t\t|%s\t\t|\n", "Go Back", BCK_OPTION, "[null]");
				printf("|%s\t|%c\t\t|%s\t\t|\n", "Go Forward", FWD_OPTION, "[null]");
				printf("|%s|%c\t\t|%s\t\t|\n", "Clear Operation", CLR_OPTION, "[null]");
				printf("|%s\t|%c\t\t|%s\t\t|\n\n", "Exit Program", EXT_OPTION, "[null]");
				break;
			case ADD_OPTION: case SUB_OPTION: case MLT_OPTION: case DIV_OPTION: case PWR_OPTION:
				scanf("%f", &numberInput);

				if (optionInput == ADD_OPTION) {
					printf(COLOUR_GREEN "%s[%.2f]to[%.2f]\n" COLOUR_RESET, "Added number", numberInput, currentNumber);
					currentNumber += numberInput;
				} else if (optionInput == SUB_OPTION) {
					printf(COLOUR_GREEN "%s[%.2f]for[%.2f]\n" COLOUR_RESET, "Subtracted number", numberInput, currentNumber);
					currentNumber -= numberInput;
				} else if (optionInput == MLT_OPTION) {
					printf(COLOUR_GREEN "%s[%.2f]to[%.2f]\n" COLOUR_RESET, "Multiplied number", numberInput, currentNumber);
					currentNumber *= numberInput;
				} else if (optionInput == DIV_OPTION) {
					printf(COLOUR_GREEN "%s[%.2f]from[%.2f]\n" COLOUR_RESET, "Divided number", numberInput, currentNumber);
					currentNumber /= numberInput;
				} else if (optionInput == PWR_OPTION) {
					printf(COLOUR_GREEN "[%.2f]%s[%.0f]\n" COLOUR_RESET, currentNumber, "to the power of", numberInput);
					int inputAsInt = (int) numberInput;

					for (int pwr = 1; pwr < inputAsInt; pwr++) {
						currentNumber *= currentNumber;
					}
				}

				operations[currentOperation] = optionInput;
				backlist[currentOperation + 1] = currentNumber;
				currentOperation++;

				operations[currentOperation] = '\0';
				backlist[currentOperation + 1] = '\0';
				break;
			case EQL_OPTION:
				printf(COLOUR_GREEN "%s[%.2f]\n" COLOUR_RESET, "Total", currentNumber);
				break;
			case BCK_OPTION:
				if (currentOperation == 0) {
					printf(COLOUR_RED "%s\n" COLOUR_RESET, "No operations to undo");
					break;
				}

				currentOperation--;

				printf(COLOUR_GREEN "%s[%c]%s[%.2f]\n" COLOUR_RESET, "Undid", operations[currentOperation], "total is now", backlist[currentOperation]);

				currentNumber = backlist[currentOperation];
				break;
			case FWD_OPTION:
				if (operations[currentOperation] == '\0') {
					printf(COLOUR_RED "%s\n" COLOUR_RESET, "No more operations");
					break;
				}

				currentOperation++;

				printf(COLOUR_GREEN "%s[%c]%s[%.2f]\n" COLOUR_RESET, "Redid", operations[currentOperation - 1], "total is now", backlist[currentOperation]);

				currentNumber = backlist[currentOperation];
				break;
			case CLR_OPTION: {
				bool clearOperation = false;
				bool inputValid = false;
				bool nextLineEntered = false;

				while (!inputValid) {
					if (!nextLineEntered)
						printf(COLOUR_BLUE "%s \n" COLOUR_RESET, "Would you like to clear all operations? [Y\\N]");

					char clearInput;

					scanf("%c", &clearInput);

					switch (clearInput) {
						case 'Y': case 'y':
							clearOperation = true;
							inputValid = true;
							break;
						case 'N': case 'n':
							inputValid = true;
							break;
						default:
							break;
					}

					if (!inputValid && clearInput != '\n') {
						nextLineEntered = false;
						printf(COLOUR_RED "%s\n" COLOUR_RESET, "Invalid input!");
					} else if (clearInput == '\n')
						nextLineEntered = true;
				}

				if (!clearOperation) {
					printf(COLOUR_RED "%s\n" COLOUR_RESET, "No operations have been cleared.");
					break;
				}
				
				printf(COLOUR_GREEN "%s[%.2f]\n" COLOUR_RESET, "Cleared number", currentNumber);
				
				memset(&operations[0], 0, sizeof(operations));
				memset(&backlist[0], 0, sizeof(backlist));

				currentOperation = 0;
				currentNumber = 0;
				break;
			}
			case EXT_OPTION:
				exitProgram = true;
				break;
			default:
				break;
		}
	}

	free(operations);
	free(backlist);

	printf(COLOUR_CYAN "%s[%d]\n" COLOUR_RESET, "Exit code", programExitCode);

	return programExitCode;
}