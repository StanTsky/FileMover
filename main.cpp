/*
--------------------------------------------------------------------
* Name:       Stan Turovsky
* Class:      CPSC-35000 -- Operating Systems
* Assignment: HW 1
* File:       main.cpp
* Purpose:    C++ File Move implementation using system calls in Linux
*             - Accepts 2 arguments when executed (source and 
*               destrination file names) 
*             - Usage: ./main test1.txt test2.txt      
--------------------------------------------------------------------
*/

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

int main(int argc, char * args[])
{
	int infile, outfile;    //file from, file to
	int numberOfBytesRead;
	char buffer[20];

  if( argc < 2 ) {
    puts ("Usage: ./main test1.txt test2.txt");
    puts ("First file name is the source and second is the destination.");
    return 0;
  }

	infile = open(args[1], O_RDONLY, 0700);

	if (infile == ENOENT)
	{
		printf("Could not find file!");
		return 1;
	}

	outfile = open(args[2], O_WRONLY | O_CREAT, 0700);

	while((numberOfBytesRead = read(infile, buffer, 20)))
		write(outfile, buffer, numberOfBytesRead);

  puts ("Source file copied...");
	close(infile);            // close inl file
	unlink(args[1]); // this part deletes the original file after copy
  puts ("Source file deleted...");
	close(outfile);           // close out file
  puts ("Done!");
}