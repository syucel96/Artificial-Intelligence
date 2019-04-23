#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class BinarySearchTree;

class Node	//This class is implemented using the lecture slides. It has been modified for the purposes of this assignment.
{
	string original;//original string
	int code;
	Node* left;
	Node* right;

	Node(const string &Element, const int &i, Node* lt, Node* rt) : original(Element), code(i), left(lt), right(rt) {}
	friend class BinarySearchTree;
};

class BinarySearchTree	//This class is implemented using the lecture slides.
{// Some functions of this class have been removed because of redundance. Some have been modified.
public:
	BinarySearchTree() : root(NULL) {}//constructor
	Node *find(const string &x) const
	{
		return find(x, root);
	}
	int getCode(const string &x)const
	{
		if (x.length() == 1)//since single letter strings are not to be assigned to the BST, 
			return x[0];//return the ascii value of the string.
		return find(x)->code;
	}
	void makeEmpty()
	{
		makeEmpty(root);
	}
	void insert(const int &x, const string &str)
	{//Iterative
		Node *ptr = root;//ptr will find the proper place to assign the new node
		if (ptr == NULL)//If the root is empty
		{
			root = new Node(str, x, NULL, NULL);
			return;
		}
		Node *temp = ptr;//temp will be the parent of ptr
		bool left = false;//Keeps track of the last iteration
		while (ptr != NULL && (ptr->original != str))
		{
			temp = ptr;
			if (str.compare(ptr->original) < 0)
			{
				ptr = ptr->left;
				left = true;
			}
			else if (str.compare(ptr->original) > 0)
			{
				ptr = ptr->right;
				left = false;
			}
		}
		if (ptr != NULL)//Do nothing if the string is already a member of the tree.
			return;
		if (left == true)//The new node should be the left child of temp
			temp->left = new Node(str, x, NULL, NULL);
		else
			temp->right = new Node(str, x, NULL, NULL);
		return;
	}
	~BinarySearchTree()
	{
		makeEmpty();
	}
private:
	Node *root;

	Node *find(const string &x, Node *ptr) const
	{
		while (ptr != NULL)
		{
			if (x.compare(ptr->original) < 0)
				ptr = ptr->left;
			else if (x.compare(ptr->original) > 0)
				ptr = ptr->right;
			else
				return ptr;
		}
		return NULL;
	}
	void makeEmpty(Node *ptr)
	{
		if (ptr != NULL)
		{
			makeEmpty(ptr->left);
			makeEmpty(ptr->right);
			delete ptr;
		}
		ptr = NULL;
	}
	//functions such as findMin, findMax and delete didn't serve any purpose for this implementation
};


string getInput(const string &filename)
{//get the input file and return it as a string
	ifstream text;
	string line, in = "", prevline = "";//edited(string prevline added to keep track if an ENTER key is pressed, bool could have also been used.)
	text.open(filename.c_str());
	while (getline(text, line))
	{	if (prevline != "")line = (char)10 + line;//edited((char)10 added at the beginning of the line if there is a previous line.)
		in = in + line;
		prevline = line;}//edited(to keep track of previous lines)
	text.close();
	return in;
}
int main()
{
	string input;
	input = getInput("compin");//input file//edited(.txt removed)
	ofstream output;
	output.open("compout");//output file//edited(.txt removed)
	BinarySearchTree tree;
	string p = "", pc;
	char c;
	int codePC, index = 256;
	for (int i = 0; i < input.length(); i++)
	{
		c = input.at(i);
		pc = p + c;//p is the previous string that is contained in the dictionary, c is the new letter
		codePC = index;
		if (pc.length() == 1)
			p = pc;
		else if (tree.find(pc) == NULL)
		{
			if (index < 4097)
				tree.insert(codePC, pc);//every pc pair is inserted to the dictionary
			cout << tree.getCode(p) << " ";
			output << tree.getCode(p) << " ";
			index++;
			p = c;//restore p
		}
		else
			p = pc;
		if (i == input.length() - 1)//If it is the last element
		{
			cout << tree.getCode(p);
			output << tree.getCode(p);
		}
	}
	output.close();
	cout << endl;
	system("pause");
	return 0;
}