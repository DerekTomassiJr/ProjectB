void printString(char*);
char* readString(char*);

void main() {
	//Testing Step #1
	//char* c = "Hello";
	//printString(c);

	//Testing Step #2
	char* line[80];
	printString("Enter a line: ");
	readString(line);
	printString(line);

	while(1);
}

void printString(char* chars) {
	int i = 0;
	while (chars[i] != 0x0) {
		interrupt(0x10, 0xe*256+chars[i], 0, 0, 0);
		i++;
	}
}

char* readString(char* line) {
	int i = 0;
	char chars = interrupt(0x16, 0, 0, 0, 0);
	while(chars != 0xd) {
		line[i] = chars;
		i++;
		chars = interrupt(0x16, 0, 0, 0, 0);
		if (chars == 0x8 && i > 0) {
                        printString(chars);
                } else if (i < 1) {
                        printString("Array Out of Bounds Error!");
                }

	}

	line[i] = 0xa;
	line[i+1] = 0x0;
	return line;
}
