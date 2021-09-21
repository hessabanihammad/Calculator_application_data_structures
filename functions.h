std::vector<std::string> Tokenize(std::string RightValue);
bool isDigit(char ch);
bool isAlpha(char ch);
int getPrec(std::string s);
std::string trim(std::string x);
std:: vector <std::string> infixtoPostfix(std:: vector <std::string> tokenized);
bool isOperand(std::string y);
void totalEvaluate(std::map <std::string, std::vector<std::string> >& postfixMap, std::map <std::string, std::string>& valueMap);
std:: string evaluate(std::vector <std::string> postfix, std::map <std::string, std::string>& valueMap);