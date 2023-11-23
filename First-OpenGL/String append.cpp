
/*

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>

using namespace std;





int main(int argc, char* argv[])
{
	
	string File = "v 0.1553 0.6543 -0.2305";
	int offpointer = 0, length = 0, vecPointer = 0;
	float x =0, y=0, z=0;

	for(int i = 0; i<=File.length();i++)
	{
		length++;
		if(File[i] == ' ' || i == File.length())
		{

			if(offpointer!=0 )
			{
				float output = stof(File.substr(offpointer, length));
				//determine which part of the vector the value should be stored
				switch(vecPointer)
				{
				case 0: x = output; vecPointer++;break;
				case 1: y = output; vecPointer++;break;
				case 2: z = output; vecPointer++; break;
				}
			}

			offpointer = i;
			length = 0;
			
		}
		cout << File[i] << endl;
	}
	
	cout << x << " " << y << " " << z;

	return 0;
}
/**/

