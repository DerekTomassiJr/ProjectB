void printString(char*);
char* readString(char*);
void readSector(char* buffer, int sector);
void handleInterrupt21(int ax, int bx, int cx, int dx);

void main() {
	//Testing Step #1
	//char* c = "Hello";
	//printString(c);

	//Testing Step #2
	//char* line[80];
	//printString("Enter a line: ");
	//readString(line);
	//printString(line);

	//Testing Step #3
	//char* buffer[512];
	//readSector(buffer, 30);
	//printString(buffer);

	//Testing Step #4
	//makeInterrupt21();
	//interrupt(0x21, 0, 0, 0, 0);

	//Testing Step #5
	char* line[80];
	makeInterrupt21();
	interrupt(0x21, 1, line, 0, 0);
	interrupt(0x21, 0, line, 0, 0);

	while(1);
}

//Function takes in string and prints to the screen
void printString(char* chars) {
	int i = 0;
	while (chars[i] != 0x0) {
		interrupt(0x10, 0xe*256+chars[i], 0, 0, 0);
		i++;
	}
}

//function takes 80 character input and reads it in as input
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

//function takes in 512 character array and sector number to read desired disk sector
void readSector(char* buffer, int sector) {
	int ah = 2;
	int al = 1;
	int ax = ah * 256 + al;

	int ch = 0;
	int cl = sector + 1;
	int cx = ch * 256 + cl;

	int dh = 0;
	int dl = 0x80;
	int dx = dh * 256 + dl;

	interrupt(0x13, ax, buffer, cx, dx);
}

//Interrupt function that will run  printString, readString, and readSector functions
void handleInterrupt21(int ax, int bx, int cx, int dx) {
	if (ax == 0) {
		printString(bx);
	} else if (ax == 1) {
		readString(bx);
	} else if (ax == 2) {
		readSector(bx, cx);
	} else if (ax >= 3) {
		printString("ERROR INTERRUPT 21 INCORRECT INPUT");
	}
}
