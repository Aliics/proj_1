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
#include <stdbool.h>
#include <string.h>

#define HELP_OPTION '?'
#define ADD_OPTION '+'
#define SUB_OPTION '-'
#define MLT_OPTION '*'
#define DIV_OPTION '/'
#define EQL_OPTION '='
#define BCK_OPTION '<'
#define FWD_OPTION '>'
#define CLR_OPTION '!'
#define EXT_OPTION '.'

#define COLOR_RESET "\x1b[0m"
#define COLOR_RED "\x1b[31m"
#define COLOR_GREEN "\x1b[32m"
#define COLOR_YELLOW "\x1b[33m"
#define COLOR_BLUE "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN "\x1b[36m"

int main() {
	int programExitCode = 0;
	
	bool exitProgram;

	char optionInput;
	float numberInput;
	
	char operations[1024];
	float backlist[1024];
	int currentOperation = 0;
	double currentNumber = 0;

	printf(COLOR_YELLOW "%s\n%s%c%s\n" COLOR_RESET, 
		"Welcome to the basic console calculator!", 
		"Type '", HELP_OPTION, "' for help."
	);

	backlist[0] = currentNumber;

	while (!exitProgram) {
		scanf("%1s", &optionInput);

		switch (optionInput) {
			case HELP_OPTION:
				printf("\n\t||%s||\n", "Execute a command with their INPUT and PARAMS");
				printf("\n\t||%s||\n", "      keys that are listed in the table      ");
				printf("\n\t|%s\t|%s\t\t|%s\t\t|\n", "COMMAND", "INPUT", "PARAMS");
				printf("\t=================================================\n");
				printf("\t|%s\t|%c\t\t|%s\t|\n", "Addition", ADD_OPTION, "[float]");
				printf("\t|%s\t|%c\t\t|%s\t|\n", "Subtraction", SUB_OPTION, "[float]");
				printf("\t|%s\t|%c\t\t|%s\t|\n", "Multiplication", MLT_OPTION, "[float]");
				printf("\t|%s\t|%c\t\t|%s\t|\n", "Division", DIV_OPTION, "[float]");
				printf("\t|%s|%c\t\t|%s\t\t|\n", "Calculate Total", EQL_OPTION, "[null]");
				printf("\t|%s\t|%c\t\t|%s\t\t|\n", "Go Back", BCK_OPTION, "[null]");
				printf("\t|%s\t|%c\t\t|%s\t\t|\n", "Go Forward", FWD_OPTION, "[null]");
				printf("\t|%s|%c\t\t|%s\t\t|\n", "Clear Operation", CLR_OPTION, "[null]");
				printf("\t|%s\t|%c\t\t|%s\t\t|\n\n", "Exit Program", EXT_OPTION, "[null]");
				break;
			case ADD_OPTION: case SUB_OPTION: case MLT_OPTION: case DIV_OPTION:
				scanf("%f", &numberInput);

				if (optionInput == ADD_OPTION) {
					printf(COLOR_GREEN "%s[%.2f]to[%.2f]\n" COLOR_RESET, "Added number", numberInput, currentNumber);
					currentNumber += numberInput;
				} else if (optionInput == SUB_OPTION) {
					printf(COLOR_GREEN "%s[%.2f]for[%.2f]\n" COLOR_RESET, "Subtracted number", numberInput, currentNumber);
					currentNumber -= numberInput;
				} else if (optionInput == MLT_OPTION) {
					printf(COLOR_GREEN "%s[%.2f]to[%.2f]\n" COLOR_RESET, "Multiplied number", numberInput, currentNumber);
					currentNumber *= numberInput;
				} else if (optionInput == DIV_OPTION) {
					printf(COLOR_GREEN "%s[%.2f]from[%.2f]\n" COLOR_RESET, "Divided number", numberInput, currentNumber);
					currentNumber /= numberInput;
				}

				operations[currentOperation] = optionInput;
				backlist[currentOperation + 1] = currentNumber;
				currentOperation++;

				operations[currentOperation] = '\0';
				backlist[currentOperation + 1] = '\0';
				break;
			case EQL_OPTION:
				printf("%s[%.2f]\n", "Total", currentNumber);
				break;
			case BCK_OPTION:
				if (currentOperation == 0) {
					printf(COLOR_RED "%s\n" COLOR_RESET, "No operations to undo");
					break;
				}

				currentOperation--;

				printf(COLOR_GREEN "%s[%c]%s[%.2f]\n" COLOR_RESET, "Undid", operations[currentOperation], "total is now", backlist[currentOperation]);

				currentNumber = backlist[currentOperation];
				break;
			case FWD_OPTION:
				if (operations[currentOperation] == '\0') {
					printf(COLOR_RED "%s\n" COLOR_RESET, "No more operations");
					break;
				}

				currentOperation++;

				printf(COLOR_GREEN "%s[%c]%s[%.2f]\n" COLOR_RESET, "Redid", operations[currentOperation - 1], "total is now", backlist[currentOperation]);

				currentNumber = backlist[currentOperation];
				break;
			case CLR_OPTION: {
				bool clearOperation = false;
				bool inputValid = false;
				bool nextLineEntered = false;

				while (!inputValid) {
					if (!nextLineEntered)
						printf(COLOR_BLUE "%s \n" COLOR_RESET, "Would you like to clear all operations? [Y\\N]");

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
						printf(COLOR_RED "%s\n" COLOR_RESET, "Invalid input!");
					} else if (clearInput == '\n')
						nextLineEntered = true;
				}

				if (!clearOperation) {
					printf(COLOR_RED "%s\n" COLOR_RESET, "No operations have been cleared.");
					break;
				}
				
				printf(COLOR_GREEN "%s[%.2f]\n" COLOR_RESET, "Cleared number", currentNumber);
				
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

	printf(COLOR_CYAN "%s[%d]\n" COLOR_RESET, "Exit code", programExitCode);

	return programExitCode;
}