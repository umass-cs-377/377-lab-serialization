# COMPSCI 377 LAB #7: Serialization

## Purpose
This lab is designed to cover serialization in C++, through a high-level overview and an in-depth look into methods of serialization, specifically fstream in C++. Please make sure that all of your answers to questions in these labs come from work done on the Edlab environment – otherwise, they may be inconsistent results and will not receive points.

Please submit your answers to this lab on Gradescope in the assignment marked “Lab #7’. All answers are due by the time specified on Gradescope. The TA present in your lab will do a brief explanation of the various parts of this lab, but you are expected to answer all questions by yourself. Please raise your hand if you have any questions during the lab section – TAs will be notified you are asking a question. Questions and Parts have a number of points marked next to them to signify their weight in this lab’s final grade. Labs are weighted equally, regardless of their total points.

Once you have logged in to Edlab, you can clone this repo using

```bash
git clone https://github.com/umass-cs-377/377-lab-threading.git
```

Then you can use `cd` to open the directory you just cloned:

```bash
cd 377-lab-threading
```

This repo includes a Makefile that allows you to locally compile and run all the sample code listed in this tutorial. You can compile them by running `make`. Feel free to modify the source files yourself, after making changes you can run `make` again to build new binaries from your modified files. You can also use `make clean` to remove all the built files, this command is usually used when something went wrong during the compilation so that you can start fresh.

## Part 1: Overview (5 Points)
Serialization is the method of transcribing some object into a format that can be loaded later to re-create that same object. Though many serialization methods can be used with formats like XML, JSON, etc., we will only be covering the serialization of human-readable structures into a stream of bytes that are not human-readable. All further mentions of serialization will refer to this method.

Computers function in a different manner than humans, reading information in formats such as 0s and 1s. However, this method of data storage though more space-efficient is completely unreadable by humans. Serialization uses both human-readable and computer-readable formats to read and write objects to the disk, so that we can save data and load it later while saving storage. When writing data (called serialization), human-readable objects are turned into computer-readable streams of bits. When reading data (called deserialization), these streams are then transformed back into human-readable objects. The main goal of serialization is determining how we can store data in the most space-efficient way that does not lose information when loading.

Additionally, serialization is not confined by a duration, and a correctly stored stream of bits can be used to load its respective file at a later date. However, it is generally recommended to use a header when writing files, as if the data type is changed at a later date the header can be used to load them correctly instead.
	
## Part 2: FStream (10 Points)
In C++, we can use the fstream class to read and write files onto our system using serialization. Unlike other I/O classes like istream and ostream which can read and write files respectively, fstreams can be used to both read and write files. Additionally, they inherit many functions from the istream and ostream classes to do so.

When using fstream, it becomes necessary to keep track of the stream of bits that are serialized upon writing data. The class keeps track of what position it is currently pointing to in the serialized stream, allowing us to manipulate specific data. To check our current position in the stream, we can call the tellg() command, which will return its currently position. We can modify this position via the seekg command, which takes a single parameter representing a position at which to place the pointer in the stream. If we do so, we can call a function like disk.read(data, 128) to read the subsequent 128 bytes of data. Effectively, using seekg() and read() we can read a certain number of bytes located at a specified position in the file.

For an example of fstream being used, please consult the following code. Make sure to read the comments included in the file to gain insight into how it works:

fstream.cpp
```
#include <string.h>
#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]){
	if (argc != 2){ //The code will ONLY run if it is given a single input, which is saved to the file
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
```
