#include <string.h>
#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]){
	if (argc != 2){ //Makes sure that the code does not run without a single input
		cout << "ERROR - NEED SINGLE INPUT" << "\n";
		return -1;
	}

	fstream disk; //Creates our filestream and opens it to disk0
	disk.open((char *)"disk0");

	//Creates an empty char array of length 4, and reads the first 4 bytes of our file.
	char data[4];
	disk.read(data, 4);

	//Turns the read bytes (the header) into the number of bytes containing the message
	int load_len = atoi(data);
	cout << "Loading data of length " << load_len << "...\n";

	//Loads the number of bytes specified by the header, pointer has already moved to the start of the message
	char data_2[load_len];
	disk.read(data_2, load_len);
	for (int i = 0; i < load_len; i++){
		cout << data_2[i];
	}
	cout << " Loaded.\n\n";

	//Records the number of bytes needed to store the input, and moves the filestream's start to the beginning
	int input_len = strlen(argv[1]);
	disk.seekg(0);
	char buffer[sizeof(input_len)];
	sprintf (buffer, "%d", input_len);
	
	//Writes both the number of bytes needed to contain the message as an int header and the message itself
	disk.write(buffer, sizeof(input_len));
	disk.write(argv[1], input_len);

	//Simple output confirming the code has run successfully
	cout << "Saving data of length " << input_len << "...\n";
	for (int i = 0; i < input_len; i++){
		cout << argv[1][i];
	}
	cout << " Saved.\n";

	disk.close();

	return 0;
}