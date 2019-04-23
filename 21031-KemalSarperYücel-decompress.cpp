#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

string getInput(const string &filename)
{
	ifstream text;
	string line, in = "";
	text.open(filename.c_str());
	while (getline(text, line))
		in = in + line;
	text.close();
	return in;
}
int main()
{
	string input;
	input = getInput("compout");//input file//edited(.txt removed)
	stringstream istream(input);//to get each code seperately and to eliminate spaces between them
	ofstream output;
	output.open("decompout");//output file//edited(.txt removed)
	//create dictionary as an array of strings
	string  dict[4096];
	for (int i = 0; i < 256; i++)
		dict[i] = (char)i;
	for (int i = 256; i < 4096; i++)
		dict[i] = "";

	string p, original = "";
	int index = 256, code;
	istream >> code;//get the first code
	p = (char)code;//we know that it is a single letter
	output << p;
	cout << p;
	while (istream >> code)
	{
		if (dict[code].length() != 0)//if the following code is in the dictionary
			original = dict[code];
		else//if the following code is not in the dictionary
			original = p + p.at(0);//p is the previous output,previous output + its first letter
		output << original;
		cout << original;
		if (index < 4097)
		{
			dict[index] = p + original.at(0);//add the preceeding output + the first letter of the current output to the dictionary
			index++;
		}
		p = original;//restore p
	}
	output.close();
	cout << endl;
	system("pause");
	return 0;
}
