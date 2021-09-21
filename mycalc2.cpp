#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <vector>
#include <map>
#include "functions.h"
#include "mycalc2.h"

using namespace std; 

//main function 
int main(int argc, char** argv) //command line arguments 
{
	//this is the filename that the user will choose to invoke  
	string filename = "";

	//this is the output filename that the user will specify if he/she wants to write the evaluated arithmetic expressions in a text file 
	string outputfile ="";

	//command line arguments 
	for (int i=1; i<argc; i++)
	{
		if(string(argv[i])=="-i" && i+1 < argc)
			filename=argv[i+1]; //if the command line argument is "i", this indicates that the following argument is the tested file name 

		if (string(argv[i])=="-o" && i+1 < argc)
			outputfile=argv[i+1]; //after the command line argument "o", the name of the file the user specifies is identified
	}

	ifstream fin(filename); //opening the file

	if(fin.fail())//if file cannot be opened
	{
		cout<<"File"<<filename<<" cannot be opened"<<endl;
		return EXIT_FAILURE; //if the file cannot be opened we return an error
	}

	//declaring a string named str 
	string str;
	string LeftValue; //we need to divide the arithmetic expression into a left and right value because we need to pass the right value for tokenization 
	string RightValue; // declaring a string to store the right value in 
	map <string, vector<string> > postfixMap; //creating a map that will store the variable name as a key and the posfix expression as a value  
	map <string, string> valueMap;  
	vector<string> names_in_order; //creating a vector of strings for the variable names in order(left values)

	//while reading from the file occurs (we read line by line)
	while (getline(fin,str)) 
	{
		size_t pos = str.find("="); //finding the position of the equal sign 
		LeftValue = trim(str.substr(0, pos)); //triming the left value up to the "=" and call the trim function we created
		names_in_order.push_back(LeftValue); // this assigns the left value which the variable name of the expression to names in order
		RightValue = str.substr(pos+1,string::npos); //the right value is the value after the found space till the end

		vector <string> tokens= Tokenize(RightValue); //we create a vector of strings named tokens and then call the tokenize function. We pass the right value to be tokenized 
		vector <string> postfix=infixtoPostfix(tokens); //call the infix to postfix function on the tokens (tokenized expressions) and assign them to a vector of strings titled postfix 
		postfixMap[LeftValue] = postfix; //here we assign the posfix value to the postfix map as a value
		valueMap[LeftValue] = "U"; //first we define the value of the map as unknown 
	}

	
	totalEvaluate(postfixMap, valueMap);

	//if the outputfile name was specified by the user, then we print the evaluated arithmatic expressions in the text file
	if (outputfile.length() > 0){
		ofstream fon (outputfile);

		for (int i=0; i< names_in_order.size();i++){
			fon<<names_in_order[i]<<" = ";
			string value = valueMap[names_in_order[i]];
			if(value[0]=='U'){
				fon<<"Undefined";
			}
			else{
				fon<<value;
			}
			fon << " ;\n";
		}
		fon.close();
	} else{ //else, if the user does not specify the output file name, then we print the evaluated arithmetic expressions on the terminal
		for (int i=0; i< names_in_order.size();i++){
			cout<<names_in_order[i]<<" = "; //we print the names(left values) followed by an "="
			string value = valueMap[names_in_order[i]]; 
			if(value[0]=='U'){
				cout<<"Undefined"; //if the value cannot be computed, then we print undefined 
			}
			else{
				cout<<value; 
			}
			cout << " ;\n";
		}
	}
	//close the file 
	fin.close();
}