#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
#include "functions.h" //including the header file
#include "mycalc2.h"

using namespace std; 

//function that will check if a character is a digit 
bool isDigit(char ch)
{
	return ('0' <= ch && ch <= '9') || ch=='.'; //allowed conditions for a digit 
}

//function that will check if a character is an alphabet 
bool isAlpha(char ch)
{
	return ('a' <= ch && ch<='z') ||('A' <= ch && ch <= 'Z'); //allowed conditions for alphabets 
}

//function that will check if a string is an operand
bool isOperand(string y){

	return isDigit(y[0]) || isAlpha(y[0]); //allowed conditions of operands: may be an alphabet or a digit 
}


//function that converts the precedency of the operators to integers for them to be compared 
int getPrec(string s)
{
	if(s.length()==2){ //unary operator
		string ss = "!!++--**"; //unary operators have higher precedency 
		if (ss.find(s) != string::npos){
			return 4; // return 4 for higher precendency 
		} else{
			return -1;//return nothing
		}
	}
	else if(s.length()==1){ //binary operators because the length is 1
		if (s[0]=='+'|| s[0]=='-'){ // + and - have the same precedency and we return 1
			return 1;
		}
		else if(s[0]=='%'){  
			return 2; 
		}
		else if (s[0]=='*' || s[0]=='#' || s[0]=='/'){ //all other operators have same precedency, which is 3)
			return 3;
		}
		else{
			return -1;
		}

	}
	return -1;
}

// the trim function is responsible for removing trailing space and preceding space
string trim(string x)
{
	size_t pos1=x.find_first_not_of(" ");
	size_t pos2=x.find_last_not_of(" ");
	return x.substr(pos1,pos2-pos1+1);
}

//tokenizing function, takes input of the RightValue as a string
vector<string> Tokenize(string RightValue)
{
	RightValue = "(" + RightValue + ")";
	vector <string> tokenized; //vector of strings for the final tokenized function
	int cnt1 = count(RightValue.begin(), RightValue.end(), '(');
	int cnt2=count(RightValue.begin(),RightValue.end(), ')');
	if(cnt1!=cnt2){
		return tokenized;
	}
	size_t pos = RightValue.find(" mod ");
	while (pos !=string::npos){
		RightValue.replace(pos, 5, "#"); 
		pos = RightValue.find(" mod ");
	}
	pos = RightValue.find(" ");
	while (pos != string::npos){
		RightValue.replace(pos, 1, "");
		pos = RightValue.find(" ");
	}
	
	for (int i=0;i<RightValue.length();i++) //loop through the right values
	{
		if(RightValue[i]==' '){ //if we encounter space, we continue
			continue;
		}
		else if(RightValue[i]==';'){ //if we encounter ";" we break 
			break;	
		}
		string temp=""; //creation of a temp variable
		//recognize if its a digit
		if (isDigit(RightValue[i])){
			while (isDigit(RightValue[i])){
				temp+=RightValue[i]; //append the right value to temp
				i++; //increment i to move to the next string
			}
			i--; 
		} else if (isAlpha(RightValue[i])){ //in case it is a variable name; 2 cases
			int count=0;
			while (isAlpha(RightValue[i]) || isDigit(RightValue[i])){ //can contain a digit and can contain alpha
				if(RightValue[i]=='.'){ //if we encounter a dot, we increase the count
					count++;
				}
				temp+=RightValue[i]; //append the RightValue to the temp
				i++;
			}
			if(count>1){ 
				return vector <string>(); //we return an empty string
			}
			i--;
		} else if (RightValue[i]=='-'){ //if we encouter a - sign 
			if (RightValue[i+1] == '-'){ //if we encounter another - sign 
				if (RightValue[i-1] == '('){ //if there's an opening bracket before the two -- signs  
					temp += "--"; //then we append -- to temp
					i ++;
				} else{
					temp += "-"; // if theres only one minus sign we append one minus 
				}
			} else{
				if (RightValue[i-1] == '('){ 
					temp += "!!";
				} else{
					temp += "-";
				}
			}
		} else if(RightValue[i]=='+' && RightValue[i+1]=='+'){ //if we encounter the unary operator "++" we append it to the temp variable 
			temp+="++";
			i++;
		}
		else if(RightValue[i]=='*' && RightValue[i+1]=='*'){ //if we encounter the unary operator "**", then we add it into the temp variable 
			temp+="**";
			i++;
		}
		else if(RightValue[i]=='-' && RightValue[i+1]=='-'){ //if we encounter the unary operator "--", then we add it into the temp variable 
			temp+="!!";
			i++;
		}
		 else{
			temp+=RightValue[i]; //else if its not any of the above we just append it into the temp value
		}

		tokenized.push_back(temp); //pushing temp into the tokenized vector
	}
	return tokenized; //the function returns tokenized value 
}

//infix to postfix function. we pass the tokenized vector of string to the infix to postfix function
vector <string> infixtoPostfix(vector <string> tokenized)
{
	stack <string> mystack; //create a stack of strings 
	vector <string> postfix; //we create a vector of strings to store the postfix expression 

	mystack.push("("); //we push an open bracket into the stack 
	tokenized.push_back(")"); 

	for (int i=0;i<tokenized.size();i++){ //loop through the tokenized expression 
		if (mystack.empty()){
			return vector<string>(); //if the stack is empty then we return an empty vector of strings 
		}
		string token=tokenized[i]; //assigning each element of the tokenized expression to a string called token 
		//cout<<token<<endl;
		if (isOperand(token)) // if we enounter an operand 
		{
			postfix.push_back(token); // we push it to the postfix 
		}
		else{
			if(token[0]=='('){
				mystack.push("("); //else if we encounter an opening bracket as the first elements then we push it in the stack 
			}
			else if(token[0]==')'){ 
				while(mystack.top()[0]!='('){ //while the top of the stack is not an opening brace 
					postfix.push_back(mystack.top()); 
					mystack.pop();
				}
				mystack.pop(); //keep poping from the stack

			}else{
				int prec = getPrec(token); //get the precedence of the token
				if (prec == -1){ //invalid precedence 
					return vector<string>(); //return an empty string of vectors 
				}

				int stack_prec=getPrec(mystack.top());

				if (prec>stack_prec){ // if the precedence of the token is greater than the stack's top operator (existing opearator)
					mystack.push(token); //then we push the token into the stack 

				}
				else{
					while(stack_prec>=prec){ //if the precedence of the top operator is greater than or equal to the precedence of the token
						postfix.push_back(mystack.top()); // we push it to the postfix 
						mystack.pop(); //we pop it from the stack 
						stack_prec=getPrec(mystack.top());
					}
					mystack.push(token);
				}
			}
		} 
	}
	//for (int i=0;i<postfix.size();i++)
		//{
		//cout<<postfix[i]<<" ";
		//}
		//cout<<endl;/*
	return postfix; //this function return the postfix value 
}

// this function evaluates the final postfix expression using a stack also
//pass by reference because we want to modify the values 
string evaluate(vector<string> postfix, map <string, string>& valueMap){ //we pass the postfix expression and the map which has the variable names and corresponding values
	/*for(auto & x:postfix){
		printf("%s ", x.c_str());
	}
	printf("\n");*/
	stack <string> mystack; // a stack used for evaluating the postfix 
	for(int i=0;i<postfix.size();i++){ //loop through the postfix 
		string token=postfix[i]; //assign the postfix elements to token as a string 
		int prec = getPrec(token); //we get the precedence of the tokens by calling the function and assigning the precedency values to an int prec variable
		if (prec > 0){ 
			if(prec==4){ //higher precedency
				if(mystack.empty()){ //if the stack is empty we return undefined 
					return "U";
				}

				string strtop = mystack.top();
				double top=stod(strtop); //convert the string to a double 
				mystack.pop();
				//unary conditions
				if(token[0]=='!'){
					top=-top; //negation 
				}
				else if(token[0]=='+'){
					top++; //incrementation 

				}
				else if(token[0]=='-'){ //decrementing
					top--;
				}
				else if(token[0]=='*'){
					top*=top; //to the power 
				}
				mystack.push(to_string(top)); //convert back to string 
			}
			else{
				if(mystack.size()<=1){ // cases for error 
					return "U";
				}  
				double a = stod(mystack.top()); //converting into a double 
				mystack.pop(); //poping from the stack
				double b=stod(mystack.top());
				mystack.pop(); //poping from the stack 
				double res;
				swap(b,a);

				//binary conditions 
				if(token[0]=='+'){ // if its addition we return a+b
					res=a+b;
				}
				else if(token[0]=='-'){ //apply the subtraction 
					res=a-b;
				}
				else if(token[0]=='*'){ //apply multiplication 
					res=a*b;
				}
				else if(token[0]=='/'){ //apply the division 
					if(b==0){
						return "U";
					}
					res=a/b;
				}
				else if(token[0]=='%'){ //apply the integer division 
					if(b==0){
						return "U";
					}
					res=floor(a/b);
				}
				else if(token[0]=='#'){ //apply mod 
					if(b==0){
						return "U";
					}	
					res=a-floor(a/b)*b;
				}
				mystack.push(to_string(res));
			}
		} else{
			// operand
			if(isDigit(token[0])){
				mystack.push(token);
			}
			else if(isAlpha(token[0])){
				if (valueMap.find(token) == valueMap.end()){
					return "U";
				}
				else{
					string value = valueMap[token];
					if (value[0]=='U'){
						return "U";
					}
					else{
						mystack.push(value); //otherwise push value to stack 
					}
				}
			}
		}
	}
	if(mystack.size()!=1){ //if the size of the stack is not equal to 1(more than one), return undefined 
		return "U";
	}
	else{
		return mystack.top(); //else we return the top of the stack (answer)
	}
}

//total evaluation function 
void totalEvaluate(map <string, vector<string> >& postfixMap, map <string, string>& valueMap)
{
	for(int i=0;i<postfixMap.size();i++){ //loops through the postfix map 
		for (auto& ptr : postfixMap){
			string name = ptr.first;
			valueMap[name] = evaluate(postfixMap[name], valueMap); //evaluates the value of the arithmetic expression from the map 
		} 
	}	
}