# Calculator_application_data_structures
I developed a calculator application named mycalc to evaluate multiple arithmetic expressions. The expressions are to be processed for correctness and finally get evaluated. 

My application is invoked as follows:

 ./mycalc -i <inputfile> -o <outfile>

where the flag -i indicates that the lexeme that follows is the file name containing the expressions to be evaluated and the -o flag indicates the name of the file where the outcome should be written into. If there is no -o flag provided, the outcome of the evaluation should appear on the tty (standard output).

To evaluate the expressions, I used the stack data structure which runs in linear time to first convert the given infix expression to a postfix expression and then evaluate the postfix expression. For the design of my program, we decided to have two separate cpp files. The first cpp file titled mycalc2.cpp contains the main program which is responsible for the flow of the program. The second cpp file titled functions.cpp contains all the functions I have created to process and evaluate the arithmetic expressions.
  
My program starts by reading from the file specified by the user when invoking the application. Each line of the txt file is read. However, because reading each line consists of reading the variable name of the expression followed by the arithmetic expression itself, I need to separate them into a right value and left value. The left value consisting of the variable name of the arithmetic expression and the right value containing the expression to tokenize or process later on. To do that I created a position variable to store the position of the “=”. Then I was able to set the left value to the start of the string until the position of
the “=” using the substr built in function which is a built-in function that returns a substring from a string. I also created a trim function to trim the trailing and preceding spaces. To do that I also used two C++ built-in functions the find_first_not_of(“ “) and the find_last_not_of(“ “). This finds the first and last strings that are not spaces. I also specify the Right value to be whatever comes after the “=” sign.

After extracting the left and right values I had to pass the right value for tokenization. In this step we identify each token of the expression. To do that I also created a separate function that deals with the Right Value arithmetic expressions. This function takes care of identifying the tokens of the expression. I also modified the mod operator to another name so that it is not mixed up with another variable name. I also created a temporary variable to store the recognized elements/variables to later on push to the tokenized vector. I identify the units of the arithmetic expression with the help of the functions I created to recognize
whether an element is a digit or an alphabet. I also recognize the unary operators in this function. I also make sure we take all cases into consideration (for example, we are only allowed to have a maximum of one dot). The function at last returns the tokenized expression as a vector of strings.
  
Then the tokenized expression is passed to the infix to postfix function which converts the tokenized vector of strings to a postfix vector of strings. This is done through a stack. I also create a vector of strings to store the postfix expression in. The function returns the postfix expression in the end after implementing the conversion from infix to postfix algorithm.

Then, I have a function which evaluates the final postfix expression using a stack also. I pass the values of the postfix from the map by reference because I want to modify the values. I have also added a final total evaluate function which loops through the postfix map. It evaluates the value of the postfix Map by passing the function which evaluates on the name of the variable and its corresponding arithmetic expression. Later on, after evaluating the arithmetic expression by calling the total evaluate function which takes the key of the postfix Map and its values as arguments. After evaluation, if the outputfile name was specified by the user, I print the arithmetic expression in the textfile. I print the arithmetic expressions in order. Otherwise, if the user does not specify the
outputfile name, we print the arithmetic expressions on the main terminal.
  
  
