#include <stdio.h>

void remove_spaces(char* s) {
	const char* d = s;
	do {
		while (*d == ' ') {
			++d;
		}
	} while (*s++ = *d++);
}

int main() {

	char line[128] = { "\n p2'\nr-o@g_ram \t84iz./\t" };

	for (int i = 0, j; line[i] != '\0'; ++i) {

		// enter the loop if the character is not an alphabet
		// and not the null character
		while (
			!(line[i] >= 'a' && line[i] <= 'z') && !(line[i] >= 'A' && line[i] <= 'Z')    // alphabet
			&& !(line[i] >= 48 && line[i] <= 57)                                          // numbers
			&& !(line[i] == '-') && !(line[i] == '_') && !(line[i] == '.')                // clean characters
			&& !(line[i] == ' ')                                                          // spaces
			&& !(line[i] == '\0')
		) {
			for (j = i; line[j] != '\0'; ++j) {

			// if jth element of line is not an alphabet,
			// assign the value of (j+1)th element to the jth element
			line[j] = line[j + 1];
			}
			line[j] = '\0';
		}
	}

	printf("\nOutput String: %s\n", line);

	remove_spaces (line);

	printf("\nText after removing blanks: %s\n\n", line);

	puts(line);
	return 0;

}