#include <iostream>
#include<fstream>
#include<string>
using namespace std;


struct LEX{
	string TOKEN;
	string LEXEME;
};
string ids;

//Function to make Token - Lexeme Pairs
bool TOKEN_MAKER(string& lex, LEX& TOK_LEX){
	
	bool r_val = false;
	string WORD[] = { "int", "char", "+", "-", "*", "/", "=", "<", "<=", ">", ">=", "==", "{", "}", "[", "]", "def", "while", "if", "else", "(", ")", "," };
	string TOKENS[] = { "INT", "CHAR", "+", "-", "*", "/", "=", "RO", "RO", "RO", "RO", "RO", "{", "}", "[", "]", "DEF", "WHILE", "IF", "ELSE", "(", ")", "," };
	string LEXEMES[] = { "null", "null", "null", "null","null", "null", "null", "LT", "LE", "GT", "GE", "EE", "null", "null", "null", 
		"null", "null", "null", "null", "null", "null", "null", "null"};
	for (int i = 0; i < 23 ; i++){
		if (lex == WORD[i]){
			TOK_LEX.LEXEME = LEXEMES[i];
			TOK_LEX.TOKEN = TOKENS[i];
			r_val =  true;
			break;
		}
	}
	return r_val;
}

//Function to identify Symbols
bool SYMBOL_IDENTIFIER(string lex){
	string KEYWORDS[7] = {"def", "if", "else", "while", "return", "print", "get"};
	int checker = 0;
	int i = 0;
	for (int i = 0; i < 7; ++i){
		if (lex == KEYWORDS[i]){
			return true;
		}
	}
	return false;
}

bool IS_IN(string a, string b[], int l){
	for (int i = 0; i < l; i++){
		if (a == b[i]){
			return true;
		}
	}
	return false;
}

bool IS_IN_NL(char a){
	string NONLETTERS[17] = { "=", ",", "+", "-", "*", "/", "<", "<=", ">", ">=", "==", "{", "}", "[", "]", "(", ")"};
	for (int i = 0; i < 17; i++){
		for (int j = 0; j < NONLETTERS[i].size(); j++){
			if (a == NONLETTERS[i][j]){
				return true;
			}
		}
	}
	return false;
}

bool IS_IN_D(char a){
	if (a > 48 && a < 59){
		return true;
	}
	return false;
}

bool IS_IN_D(string& s){
	bool has_only_digits = true;
	for (size_t n = 0; n < s.length(); n++)
	{
		if (!isdigit(s[n]))
		{
			has_only_digits = false;
			return false;
		}
	}
	return true;
}

bool IS_IN_DT(string st){
	string WORD[] = { "int", "char" };
	for (int i = 0; i < 2; i++){
		if (st == WORD[i]){
			return true;
		}
	}
	return false;
}

bool IS_COMMENT(string st){
	if (st[0] == '#'){
		return true;
	}
	return false;
}
int main(int argc, char* argv[]){
	//if (argc != 1){ // argc should be 2 for correct execution
//		ifstream cm(".\Debug\Assignment - LEX.exe"); //opening LEX file.
	
		
	if (argc == 0)
	{
		cout << "You have not given command line arguments";
		system("pause");
		return 0;
	}
		string input_file = argv[1];
		ifstream prog(input_file); //the RUBY++ code
		ofstream lex("Token-Lexeme.txt");
		ofstream s_table("SymbolTable.txt");
		
		s_table << "All the Symbols are here: \n \n";
		lex << "Token \t \t Lexeme \n" << endl;
		LEX LEX_TOK;
		
		string DIGITS[10] = {"1", "2", "3", "4", "5", "6", "7", "8","9", "0"};
		string DATA, temp = "", temp2 = "";
		
		LEX Lex;
		
		if (!prog.is_open()){
			cout << "Could not open file(s) \n" << endl;
		}
		else {

			while (!prog.eof()){
				getline(prog, DATA);
				//is_done = false;
				//loop for extracting Symbol Table & LEX-TOK file
				for (int i = 0; i < DATA.size(); i++){
					if (DATA[i] == ' ' && SYMBOL_IDENTIFIER(temp)){
						TOKEN_MAKER(temp, LEX_TOK);
						lex << LEX_TOK.TOKEN << "\t \t" << LEX_TOK.LEXEME << endl;
						while (DATA[i] == ' '){
							i++;
						}
						if (temp2[0] < 48 && temp2[0] > 57){
							while (!IS_IN_NL(temp2[i])){
								temp2 += DATA[i];
								i++;
							}
							i--;
							s_table << temp2 << endl;
							lex << "ID" << "\t \t" << temp2 << endl;
						}
						else{
//							cout << " This is an error bro" << endl;
							lex << "NUM" << "\t \t" << temp2 << endl;
						}
						LEX_TOK.TOKEN.clear();
						LEX_TOK.LEXEME.clear();
						temp.clear();
						temp2.clear();
					}
					else if (DATA[i] == '=' || DATA[i] == '<' || DATA[i] == '>'){
						if (DATA[i + 1] == '='){
							temp += DATA[i];
							temp += DATA[++i];
							TOKEN_MAKER(temp, LEX_TOK);
							lex << LEX_TOK.TOKEN << "\t \t" << LEX_TOK.LEXEME << endl;
							LEX_TOK.TOKEN.clear();
							LEX_TOK.LEXEME.clear();
							temp.clear();
						}
						else{
							temp += DATA[i];
							TOKEN_MAKER(temp, LEX_TOK);
							lex << LEX_TOK.TOKEN << "\t \t" << LEX_TOK.LEXEME << endl;
							LEX_TOK.TOKEN.clear();
							LEX_TOK.LEXEME.clear();
							temp.clear();
						}
					}
					else if (DATA[i] == ' '){
						temp.clear();
					}
					else if (DATA[i] == '#'){ //checks if comment, rejects the whole string ahead
						i++;
						while (i < DATA.size()){
							temp += DATA[i];
							i++;
						}
						break;
					}
					else{
						temp += DATA[i];
						int tr = 0;
						int x = i + 1;
						while (x < DATA.size() && DATA[i] == ' ' || DATA[i] == '\t'){
							if (DATA[x] == '#'){
								tr = 3;
					//			isComment = true;
								string temp2;
								x++;
								while (x < DATA.size()){
									temp2 += DATA[x];
									x++;
								}
								lex << "# \t \t" << temp2 << endl;
								i = x;
								break;
							}
							x++;
						}
						if (tr != 3){
							if (temp == "'"){
								string t2;
								if (i + 2 < DATA.size()){
									t2 += DATA[i + 2];
									if (t2 == "'"){
										temp += DATA[++i];
										temp += DATA[++i];
										lex << "LTR" << "\t \t" << temp << endl;
										temp.clear();
									}
								}
							}
							else if (TOKEN_MAKER(temp, LEX_TOK)){

								lex << LEX_TOK.TOKEN << "\t \t" << LEX_TOK.LEXEME << endl;
								LEX_TOK.TOKEN.clear();
								LEX_TOK.LEXEME.clear();
								temp.clear();
							}
							else{
								int j = i + 1;
								int truth = 0;
								bool isComment = false;
								if (temp[0] == ','){
									TOKEN_MAKER(temp, LEX_TOK);
									lex << LEX_TOK.TOKEN << "\t \t" << LEX_TOK.LEXEME << endl;
									LEX_TOK.TOKEN.clear();
									LEX_TOK.LEXEME.clear();
									temp.clear();
								}
								else if (temp[0] == '#'){
									isComment = true;
									string temp2 = "";
									i++;
									while (i < DATA.size()){
										temp2 += DATA[i];
										i++;
									}
									lex << "# \t \t" << temp2 << endl;
								}
								else if (!IS_IN_D(temp[0])){

									if (j < DATA.size()){
										while (j < DATA.size() && !IS_IN_NL(DATA[j])){
											if (DATA[j] == ' ' && TOKEN_MAKER(temp, LEX_TOK) && (SYMBOL_IDENTIFIER(temp) || IS_IN_DT(temp))){
												lex << LEX_TOK.TOKEN << "\t \t" << LEX_TOK.LEXEME << endl;
												while (DATA[j] == ' ' || DATA[j] =='\t'){
													j++;
												}
												if (DATA[j] == '#'){
													string temp3 = "";
													while (j < DATA.size()){
														temp3 += DATA[j];
														j++;
													}
													lex << "# \t \t" << temp3 << endl;
													isComment = true;
												}
												temp2 += DATA[j++];
												if (!IS_IN_D(temp2)){
													while (!IS_IN_NL(DATA[j])){
														temp2 += DATA[j];
														j++;
													}
													j--;
													if (DATA[j] == '#'){
														string temp3 = "";
														while (j < DATA.size()){
															temp3 += DATA[j];
															j++;
														}
														lex << "# \t \t" << temp3 << endl;
														isComment = true;
													}

													s_table << temp2 << endl;
													lex << "ID" << "\t \t" << temp2 << endl;
													temp2.clear();
												}

												truth = 1;
												break;

											}
											else if (DATA[j] == ' ' && IS_IN_D(temp)){
												lex << "NUM" << "\t \t" << temp << endl;
												//s_table << temp << endl;

												truth = 1;
												break;
											}
											else if (DATA[j] == '#'){
												if (truth == 2){
													lex << "ID" << "\t \t" << temp << endl;
													truth = 1;
												}
												string temp3 = "";
												while (j < DATA.size()){
													temp3 += DATA[j];
													j++;
												}
												lex << "# \t \t" << temp3 << endl;
												isComment = true;
												break;
											}
											truth = 2;
											temp += DATA[j];
											j++;
										}
										i = j;
									}
									if (IS_IN_DT(temp) && truth == 0){
										TOKEN_MAKER(temp, LEX_TOK);
										lex << LEX_TOK.TOKEN << "\t \t" << LEX_TOK.LEXEME << endl;
										truth = 1;
										i--;
									}
									if (truth == 2){
										lex << "ID" << "\t \t" << temp << endl;
										i--;
									}
									else if (truth == 0){
										lex << "ID" << "\t \t" << temp << endl;
									}
									LEX_TOK.TOKEN.clear();
									LEX_TOK.LEXEME.clear();
									temp.clear();
								}
								else{
									while (DATA[j] != ' ' && j < DATA.size() && !IS_IN_NL(DATA[j])){
										temp += DATA[j];
										j++;
									}
									if (IS_IN_D(temp)){
										lex << "NUM" << "\t \t" << temp << endl;
									}
								}
							}
						}
					}
				}
				temp.clear();
			}

			cout << DATA << endl;
			prog.close();
		}

		cout << "The token lexeme and symbol file is created" << endl;
	/*}
	else {

		ifstream cm(argv[0]); //opening LEX file.

		ifstream prog(argv[1]); //the RUBY++ code
		// Always check to see if file opening succeeded
	
		if (!cm.is_open() || !prog.is_open())
			cout << "Could not open file(s) \n";
		else {


			//closing files
			cm.close();
			prog.close();
		}
	}*/
}