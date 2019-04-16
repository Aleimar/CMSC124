/*
	Name: Simple Integer-Oriented Language Interpreter 
	Author: Aleimar Villabrille
	Description: An interactive version of SIOL Intepreter project of CMSC124
*/

//preprocessors
#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <locale>


using namespace std;

//RESERVED WORDS FOR SIOL
string reserved[18] = {"SIOL", "LOIS", "INTO", "IS", "BEG", "PRINT", "MULT", "DIV", "ADD", "SUB", "MOD", "IF", "END", "BEGIN", "ITERATE", "LOOP", "ENDLOOP", "TO"};
string conds[6]={"EQUAL","NOTEQ","LESSER","GREATER","LESSEQ","GREATEQ"};

//global declaration for globally used variables
vector<string> ident;		//vector for variable names
vector<string> value;			//vector for values of each variable
vector<string> pambeg;			//vector for beg variables
vector<string> begval;			//vector for beg variable values
vector<string> prompt;
vector<string> tokens;			//for iterate function (special vector)
vector<string> iterative;


string scan, var, msg;
int i, val, index, varindex, val1, val2, iterator, prompts;
string var1, var2;
const char* var1val;
const char* var2val;
const char* vals;
string check;
bool flag;
int z, w;
	
//the following function must be defined first to execute the program properly
void start();
void selstart(int);
void iterate(int);
void iterInto(int,int &,int);

//program introduction function
void intro()
{
	cout << "--------------------------------------------------------------------------------";
	cout << "\n\t\t\tWelcome to SIOL Interpreter!\n\t    Start your source program with SIOL and end it with LOIS.\n\n";
	cout << "--------------------------------------------------------------------------------";
	cout << endl << endl;
}

//this function terminates the program
void term()
{
	getchar();
	cout << endl << endl<<"Program terminates...";
	exit(1);
}

//this function checks whether the inputted variable already exist in the vector of identifiers
bool identexist(string variable)
{
	for(int i=0;i<ident.size();i++)
	{
		if(variable.compare(ident[i])==0)
		{
			return true;	//returns true if variable name was found in the vector of identifiers
		}
	}
	
}

//this function search for the variable in the vector of BEG
bool identexistbeg(string variable)
{

	for(int i=0;i<pambeg.size();i++)
	{
		if(variable.compare(pambeg[i])==0)
		{
			return true; //returns true if variable name was found in the vector of identifiers for BEG
		}
	}
}

//this function returns the index in which the identical identifier exists 
int getvalue(string variable)
{
	for(int i=0;i<ident.size();i++)
	{
		if(variable.compare(ident[i])==0)
		{
			return i;				
			break;
		}
	}
		
	return 0;
}


//this function returns the index in which the identical identifier exists 
int getvaluebeg(string variable)
{

	for(int i=0;i<pambeg.size();i++)
	{
		if(variable.compare(pambeg[i])==0)		
		{
			return i;		//index was found
			break;
		}
	}
		
	return 0;
}

//this function determines if the inputted value is an integer
bool isnum(string scan, const char* vals)
{
	for(int i=0;i<scan.length();i++)
	{
		if(!isdigit(vals[i]))
		{
			return false;	//value set is said to be not an integer
			break; 
		}
	}
	
	return true;			//value set is said to be an integer
	
}

//this function checks if the inputted variable name is valid
bool isvalid(string varname)
{
	const char *dummy;
	
	bool ret;
	
	dummy=varname.c_str();
	
	//a short circuit evaluation 
	if(isalpha(dummy[0]))		//checks if the first character of the variable name is a letter 
	{
		for(i=0;i<varname.length();i++)
		{
			if(!isalnum(dummy[i]))		//checks if special characters in the variable name
			{
				if(dummy[i]=='_')		//connectors in the form of _ (underscore) is allowed
				{
					continue;
				}
				else
				{
					return false;		//invalid variable name
				}
			}
		}
		
			ret=true;				//valid variable name
	}
	else
	{
		ret=false;			//invalid variable name
	}
	
	return ret;
}

//commenting function
void comment()
{
	string end;
	string scan;
	
	int n=end.length()-1;
	
	do
	{
		cin >> scan;					//scans everything
		end=scan.c_str();	
		n=end.length()-1;
		
		if(end[n]=='*')		//when the * is inputted at the end of any characters commenting ends.
		{
			break;	
		}
	}while(end[n]!='*');
	
}

//this function searches the varname if it was already declared to be a string variable
bool wasBeg(string scan)
{
	for(i=0;i<pambeg.size();i++)
	{
		if(scan.compare(pambeg[i])==0)
		{
			return false;			//varname is already declared as STRING! 
		}
	}
	
	return true;				//varname is still valid
}

//this function searches the varname if it was already declared to be a integer variable
bool wasInto(string scan)
{
	for(i=0;i<ident.size();i++)
	{
		if(scan.compare(ident[i])==0)
		{
			return false;			//varname is already declared as STRING! 
		}
	}
	
	return true;				//varname is still valid
}

//changes value of an identifier (integer version)
void changeval(int index, string val)
{
	value[index]=val;
}

//changes value of an identifier (sting version)
void changevalbeg(int index, string val)
{
	begval[index]=val;
}

//checks if the varname inputted is a reserved word
bool isReserved(string scan)
{
	for(i=0;i<18;i++)
	{
		if(scan.compare(reserved[i])==0)
		{
			return false;
		}
	}
	
	return true;
}

//this function performs the operation (iteration process)
void iterperform(int oper, int val1, int val2, int varindex, int &z, int w)
{
	int answer;
	
	switch(oper)
	{
		case 1:
			if(w==0)
			{
				answer=val1+val2;						// here we add the values of two variables
				value[varindex]=to_string(answer);			
				msg="\n. . . Evaluating ADD: result is: "+value[varindex]+"\n\n";
				prompt.push_back(msg);
				z=z+1;
			}
			else if(w==2)
			{
				z=z+1;
			}
			else
			{
				answer=val1+val2;						// here we add the values of two variables
				value[varindex]=to_string(answer);			
				msg="\n. . . Evaluating ADD: result is: "+value[varindex]+"\n\n";
				iterative.push_back(msg);
				z=z+1;
			}
			
			break;
		case 2:
			if(w==0)
			{
				answer=val1-val2;							// here we subtract the values of two variables
				value[varindex]=to_string(answer);			
				msg="\n. . . Evaluating SUB: result is: "+value[varindex]+"\n\n";
				prompt.push_back(msg);
				z=z+1;
			}
			else if(w==2)
			{
				z=z+1;
			}
			else
			{
				answer=val1-val2;							// here we subtract the values of two variables
				value[varindex]=to_string(answer);			
				msg="\n. . . Evaluating SUB: result is: "+value[varindex]+"\n\n";
				iterative.push_back(msg);
				z=z+1;
			}
			
			break;
		case 3:	
			if(w==0)
			{
				answer=val1*val2;							// here we multiply the values of two variables
				value[varindex]=to_string(answer);			
				msg="\n. . . Evaluating MULT: result is: "+value[varindex]+"\n\n";
				prompt.push_back(msg);
				z=z+1;
			}
			else if(w==2)
			{
				z=z+1;
			}
			else
			{
				answer=val1*val2;							// here we multiply the values of two variables
				value[varindex]=to_string(answer);			
				msg="\n. . . Evaluating MULT: result is: "+value[varindex]+"\n\n";
				iterative.push_back(msg);
				z=z+1;
			}
			break;
		case 4:
			if(w==0)
			{
				if(val2==0)
				{	
					msg="\n. . .Error! :: Cannot be divided by zero! \n\n";
					prompt.push_back(msg);
				}
				else
				{
					answer=val1/val2;			// here we divide the values of two variables
					value[varindex]=to_string(answer);			
					msg="\n. . . Evaluating DIV: result is: "+value[varindex]+"\n\n";
					prompt.push_back(msg);
				}
				z=z+1;
			}
			else if(w==2)
			{
				if(val2==0)
				{	
					msg="\n. . .Error! :: Cannot be divided by zero! \n\n";
					prompt.push_back(msg);
				}
				z=z+1;
				
			}
			else
			{
				if(val2==0)
				{	
					msg="\n. . .Error! :: Cannot be divided by zero! \n\n";
					iterative.push_back(msg);
				}
				else
				{
					answer=val1/val2;			// here we divide the values of two variables
					value[varindex]=to_string(answer);			
					msg="\n. . . Evaluating DIV: result is: "+value[varindex]+"\n\n";
					iterative.push_back(msg);
				}
				z=z+1;
			}
			
			break;
		case 5:
			if(w==0)
			{
				if(val2==0)
				{
					msg="\n. . .Error! ::Cannot be modulo by zero! \n\\n";
					prompt.push_back(msg);
				}
				else
				{
	
					answer=val1%val2;						// here we perform modulo operation to the values of two variables
					value[varindex]=to_string(answer);	
					msg="\n. . . Evaluating MOD: result is: "+value[varindex]+"\n\n";
					prompt.push_back(msg);
				}
				z=z+1;
			}
			else if(w==2)
			{
				if(val2==0)
				{
					msg="\n. . .Error! ::Cannot be modulo by zero! \n\\n";
					prompt.push_back(msg);
				}
			}
			else
			{
				if(val2==0)
				{
					msg="\n. . .Error! ::Cannot be modulo by zero! \n\\n";
					iterative.push_back(msg);
				}
				else
				{
	
					answer=val1%val2;						// here we perform modulo operation to the values of two variables
					value[varindex]=to_string(answer);	
					msg="\n. . . Evaluating MOD: result is: "+value[varindex]+"\n\n";
					iterative.push_back(msg);
				}
				z=z+1;
			}	
			
			break;
		default:
				cout << "\t";
				msg="\n. . .Error :: Invalid operation!\n\n";
				iterative.push_back(msg);
				z=z+1;
				break;
	}
}

//this function performs the operation
void perform(int oper, int val1, int val2, int varindex, int prompts)
{
	int answer;
	
	switch(oper)
	{
		case 1:
			
			if(prompts==2)		//skip
			{
				cout <<"\t";	
			}
			
			else
			{
				answer=val1+val2;						// here we add the values of two variables
				value[varindex]=to_string(answer);
						
				if(prompts==1)			//display
				{
					cout << endl << ". . . Evaluating ADD: result is: " << value[varindex] << endl <<  endl;
				}
			
				else
				{
					cout <<"\t";
					msg=". . . Evaluating ADD: result is: "+value[varindex]+"\n\n";
					prompt.push_back(msg);
				}
			}
				break;
		case 2:
			if(prompts==2)		//skip
			{
				cout <<"\t";
			}
			else
			{
				answer=val1-val2;							// here we subtract the values of two variables
				value[varindex]=to_string(answer);			
				if(prompts==1)		//display
				{
					cout << endl << ". . . Evaluating SUB: result is: " << value[varindex] << endl <<  endl;
				}

				else
				{
					cout <<"\t";
					msg="\n. . . Evaluating SUB: result is: "+value[varindex]+"\n\n";
					prompt.push_back(msg);
				}
			}
			break;
		case 3:
			if(prompts==2)
			{
				cout << "\t";
			}
			else
			{
				answer=val1*val2;							// here we multiply the values of two variables
				value[varindex]=to_string(answer);			
				if(prompts==1)
				{
					cout << endl << ". . . Evaluating MULT: result is: " << value[varindex] << endl <<  endl;
				}
				else
				{
					cout <<"\t";
					msg="\n. . . Evaluating MULT: result is: "+value[varindex]+"\n\n";
					prompt.push_back(msg);
				}
			}
			break;
		case 4:
			if(val2==0)
			{
				if(prompts==2)		//skip
				{
					cout << "\t";
				}
				
				else
				{
					
				
					if(prompts==1)		//display
					{
						cout << endl << ". . .Error! :: Cannot be divided by zero! " << endl << endl;
					}
					else
					{
						cout <<"\t";
						msg=". . .Error! :: Cannot be divided by zero! \n\n";
						prompt.push_back(msg);
					}
				}
			}
			else
			{
				if(prompts==2)
				{
					cout <<"\t";
				}
				else
				{
					answer=val1/val2;			// here we divide the values of two variables
					value[varindex]=to_string(answer);			
					if(prompts==1)		//display
					{
						cout << endl << ". . . Evaluating DIV: result is: " << value[varindex] << endl <<  endl;
					}
					else
					{
						cout <<"\t";
						msg="\n. . . Evaluating DIV: result is: "+value[varindex]+"\n\n";
						prompt.push_back(msg);
					}
				}
			}
			break;
			case 5:
			if(val2==0)
			{
				if(prompts==2)		//skip
				{
					cout << "\t";
				}
				else
				{
					
					if(prompts==1)		//display
					{
						cout << endl << ". . .Error! ::Cannot be modulo by zero! " << endl << endl;
					}
					else
					{
						cout <<"\t";
						msg="\n. . .Error! ::Cannot be modulo by zero! \n\\n";
						prompt.push_back(msg);
					}
				}
					
			}
			else
			{
				if(prompts==2)		//skip
				{
					cout << "\t";
				}
				else
				{
					answer=val1%val2;						// here we perform modulo operation to the values of two variables
					value[varindex]=to_string(answer);	
					if(prompts==1)			//display
					{
						cout << endl << ". . . Evaluating MOD: result is: " << value[varindex] << endl <<  endl;
					}	
					else
					{
						cout <<"\t";
						msg="\n. . . Evaluating MOD: result is: "+value[varindex]+"\n\n";
						prompt.push_back(msg);
					}
				}
			}
			break;
		default:
			if(prompts==1)		//display
			{
				cout << endl << ". . .Error :: Invalid operation!" << endl <<endl;
			}
			else
			{
				cout << "\t";
				msg="\n. . .Error :: Invalid operation!\n\n";
				prompt.push_back(msg);
			}
		
	}
	
}

//this function checks if operation is valid:: are the variables int the operation defined? are they integer??
void operation(int oper, int varindex,int prompts)
{
	bool flag1, flag2, numflag;
	int answer, a, b;
	const char* val_1;
	const char* val_2;
	
	cin >> scan;		//well expect  string of a previously defined variable name or a number
	
	flag1=identexist(scan);
	
	//variable 1 must be defined
	if(flag1)
	{
	
		index=getvalue(scan); 	//we must find at what index does this variable name can be found
				
		var1=value[index];
		vals=var1.c_str();
		val1=atoi(vals);
		
		cin >> scan;				// well expect another string of a previously defined variable name
		
		flag2=identexist(scan);
		
		//variable 2 must be defined
		if(flag2)
		{		
			index=getvalue(scan);	//we must find at what index does this variable name can be found
			var2=value[index];
				
			vals=var2.c_str();
			val2=atoi(vals);

			perform(oper,val1,val2,varindex,prompts);		
		}
		
		//variable2 must be check if it is an integer
		else
		{
			val_2=scan.c_str();
			numflag=isnum(scan,val_2);
			
			//if it is an integer :: operation is valid
			if(numflag)
			{
				b=atoi(val_2);
				
				perform(oper,val1,b,varindex,prompts);
			}
			
			//semantical error
			else
			{
				if(scan.compare(reserved[1])==0)		//LOIS
				{
					getchar();
					cout << endl << endl<<"Program terminates...";
					exit(1);
				}
				else
				{
					if(prompts==1)
					{
						cout << endl << ". . .Error! :: Variable "<< scan<<" is undefined!" << endl << endl;
					}
					else
					{
						cout << "\t";
						msg="\n. . .Error! :: Variable "+scan+" is undefined!\n\n";
						prompt.push_back(msg);			
					}
					
				}
			}
			
		}
	
	}
	
	//variable must be an integer
	else
	{
		val_1=scan.c_str();
		numflag=isnum(scan,val_1);
		
		if(numflag)
		{
			a=atoi(val_1);	//a is integer 1 in the operation
		
			cin >> scan;				// well expect another string of a previously defined variable name or an integer
			
			val_2=scan.c_str();
			
			numflag=isnum(scan,val_2);
			
			if(numflag)
			{
				b=atoi(val_2);
				
				perform(oper,a,b,varindex,prompts);
			}
			
			//must be a previously defined variable if not an integer
			else
			{
				//checks if variable was previously defined
				flag2=identexist(scan);
		
				//variable 2 must be defined
				if(flag2)
				{
		
					index=getvalue(scan);	//we must find at what index does this variable name can be found
					var2=value[index];
				
					vals=var2.c_str();
					val2=atoi(vals);

	
					perform(oper,a,val2,varindex,prompts);
		
				}
					
				//semantical error
				else
				{
					if(scan.compare(reserved[1])==0)
					{
						getchar();
						cout << endl << endl<<"Program terminates...";
						exit(1);
						
					}
					else
					{
						if(prompts==1)
						{
							cout << endl << ". . .Error! :: Variable "<< scan <<" is undefined!" << endl << endl;
						}
						else
						{
							cout << "\t";
							msg="\n. . .Error! :: Variable "+ scan +" is undefined!\n\n";
							prompt.push_back(msg);
						}
					}
					
				}
				
			}
			
		}
		 
		//semantical error
		else
		{
			if(scan.compare(reserved[1])==0)
			{
				getchar();
				cout << endl << endl<<"Program terminates...";
				exit(1);
			}
			else
			{
				if(prompts==1)
				{
					cout << endl << ". . .Error! :: Variable "<< scan <<" is undefined!" << endl << endl;
				}
				else
				{
					cout <<"\t";
					msg="\n. . .Error! :: Variable "+ scan +" is undefined!\n\n";
					prompt.push_back(msg);
				}
			}
		}
	}
}

//this function checks if operation is valid:: are the variables int the operation defined? are they integer??
void iteroperation(int oper, int varindex, int &z, int w)
{
	bool flag1, flag2, numflag;
	int answer, a, b;
	const char* val_1;
	const char* val_2;
	
	z=z+1;		//well expect  string of a previously defined variable name or a number
	
	flag1=identexist(tokens[z]);
	
	//variable 1 must be defined
	if(flag1)
	{
	
		index=getvalue(tokens[z]); 	//we must find at what index does this variable name can be found
				
		var1=value[index];
		vals=var1.c_str();
		val1=atoi(vals);
		
		z=z+1;				// well expect another string of a previously defined variable name
		
		flag2=identexist(tokens[z]);
		
		//variable 2 must be defined
		if(flag2)
		{
		
			index=getvalue(tokens[z]);	//we must find at what index does this variable name can be found
			var2=value[index];
				
			vals=var2.c_str();
			val2=atoi(vals);

	
			iterperform(oper,val1,val2,varindex,z,w);
		
		}
		
		//variable2 must be check if it is an integer
		else
		{
			val_2=tokens[z].c_str();
			
			numflag=isnum(tokens[z],val_2);
			
			//if it is an integer :: operation is valid
			if(numflag)
			{
				b=atoi(val_2);
				
				iterperform(oper,val1,b,varindex,z,w);
			}
			
			//semantical error
			else
			{
				if(tokens[z].compare(reserved[1])==0)		//LOIS
				{
					term();
				}
				else
				{
					if(w==0)
					{
						msg="\n. . .Error! :: Variable "+tokens[z]+" is undefined!\n\n";
						prompt.push_back(msg);
					}
					else if(w==2)
					{
						//do nothing
					}
					else
					{
						msg="\n. . .Error! :: Variable "+tokens[z]+" is undefined!\n\n";
						iterative.push_back(msg);
					}
					
					z=z+1;			
				}
			}
			
		}
	
	}
	
	//variable must be an integer
	else
	{
		val_1=tokens[z].c_str();
		numflag=isnum(tokens[z],val_1);
		
		if(numflag)
		{
			a=atoi(val_1);	//a is integer 1 in the operation
		
			z=z+1;				// well expect another string of a previously defined variable name or an integer
			
			val_2=tokens[z].c_str();
			
			numflag=isnum(tokens[z],val_2);
			
			if(numflag)
			{
				b=atoi(val_2);
				
				iterperform(oper,a,b,varindex,z,w);
			}
			
			//must be a previously defined variable if not an integer
			else
			{
				//checks if variable was previously defined
				flag2=identexist(tokens[z]);
		
				//variable 2 must be defined
				if(flag2)
				{
		
					index=getvalue(tokens[z]);	//we must find at what index does this variable name can be found
					var2=value[index];
				
					vals=var2.c_str();
					val2=atoi(vals);

	
					iterperform(oper,a,val2,varindex,z,w);
		
				}
					
				//semantical error
				else
				{
					if(tokens[z].compare(reserved[1])==0)
					{
						term();
					}
					else
					{
						if(w==0)
						{
							msg="\n. . .Error! :: Variable "+ tokens[z] +" is undefined!\n\n";
							prompt.push_back(msg);
						}
						else if(w==2)
						{
							//do nothing
						}
						else
						{
							msg="\n. . .Error! :: Variable "+ tokens[z] +" is undefined!\n\n";
							iterative.push_back(msg);
						}
						
						z=z+1;
					}
					
				}
				
			}
			
		}
		 
		//semantical error
		else
		{
			if(tokens[z].compare(reserved[1])==0)
			{
				term();
			}
			else
			{
				if(w==0)
				{
					msg="\n. . .Error! :: Variable "+ tokens[z] +" is undefined!\n\n";
					prompt.push_back(msg);
				}
				else if(w==2)
				{
					//do nothing
				}
				else
				{
					msg="\n. . .Error! :: Variable "+ tokens[z] +" is undefined!\n\n";
					iterative.push_back(msg);
				}
				
				z=z+1;
				
			}
		}
	}
}


//function for INTO:: Declaration of variable
void isInto(int prompts)
{
	int answer;
	bool valid, beg, used;
	cin >> scan;			// well expect an variable name after the string into
	var=scan;			//we set the latest string as var
	
	valid=isvalid(var);			//checks if varname is valid
	
	beg=wasBeg(var);				//checks if varname was already declared as a string		
	
	used=isReserved(var);		//checks if varname is a reserved word
	
	if(used)
	{
		
		if(beg)
		{
		
			if(valid)
			{
				flag=identexist(scan);	//we send the vector of identifiers and variable name for searching if this inputted variable was declared before
				/*It should enter in this if condition if an identifier was declared before*/
					
				if(flag)
				{
					
					varindex=getvalue(scan);	//index of variable in which it was previously defined
					
					cin >> scan;
					if(scan.compare(reserved[3])==0) //well expect IS after a variable
					{
						cin >> scan;			// well expect either an operation reserved word or a new value for the current variable
				
						if(reserved[8].compare(scan)==0)	//if the latest string is "ADD" we enter this block
						{
							operation(1,varindex,prompts);
						}
								
						else if(reserved[9].compare(scan)==0)	//if the latest string is "SUB" we enter this block
						{
							operation(2,varindex,prompts);
						}
				
						else if(reserved[6].compare(scan)==0)	//if the latest string is "MULT" we enter this block
						{
							operation(3,varindex,prompts);
						}
						
						else if(reserved[7].compare(scan)==0)	//if the latest string is "DIV" we enter this block
						{
							operation(4,varindex,prompts);
							
						}
								
						else if(reserved[10].compare(scan)==0)	//if the latest string is "MOD" we enter this block
						{
							operation(5,varindex,prompts);
						}
							
						//if the latest scanned string isn't an operation reserved word, it is  new assignment for that previously defined variable
						else
						{
							
							vals=scan.c_str();
						
							if(isdigit(vals[0]))
							{
								if(prompts==2)		//skip
								{
									cout <<"\t";
								}
								
								else
								{
									changeval(varindex, scan);
													
									//if statement is not on block
									if(prompts==1)
									{
										cout << endl << "... Set value of " << var << " to " << scan << endl << endl;
									}
									//statement is in block
									else
									{
										cout <<"\t";
									
										msg="... Set value of "+var+" to "+scan+"\n\n";
										prompt.push_back(msg);
									}
								}	
							}
								
							
							else if(scan.compare(reserved[1])==0)
							{
								term();
							}
							
							else
							{
								if(prompts==1)
								{
									cout << endl << ". . .Error! Expects a value :: received " << vals << endl;
								}
								else
								{
									cout << "\t";
									msg="\n. . .Error! Expects a value :: received "+scan+"\n";
									prompt.push_back(msg);
								}
								
							}
						}
					}
			
					else
					{
						if(scan.compare(reserved[1])==0)
						{
							term();
						}
						else
						{
							if(prompts==1)
							{
								cout << endl << ". . .Error! Expects IS after a variable declaration :: received " << scan << endl;
							}
							else
							{
								cout << "\t";
								msg="\n. . .Error! Expects IS after a variable declaration :: received " +scan +"\n";
								prompt.push_back(msg);
							}
						}
					}
				}
						
				else
				{
					cin >> scan;
					if(scan.compare(reserved[3])==0)		//IS
					{
						cin >> scan;
						
						vals=scan.c_str();
						valid=isnum(scan,vals);
					
						if(valid)
						{
							if(prompts==2)		//skip
							{
								cout << "\t";
							}
							else
							{
								ident.push_back(var);			//we scan this new variable name and push it to our vector for identifiers
								value.push_back(scan);
								
								//if statement is not on block
								if(prompts==1)
								{
									cout << endl << "... Set value of " << var << " to " << scan << endl << endl;
								}
								//statement is in block
								else
								{
									cout <<"\t";
									msg="... Set value of "+var+" to "+scan+"\n\n";
									prompt.push_back(msg);
								}
							}
						}
					
						else
						{
							if(scan.compare(reserved[1])==0)
							{
								term();
							}
							else
							{
								if(prompts==1)
								{
									cout << endl << ". . .Error! :: Inputted value "<< scan <<" is not an integer! " << endl << endl;
								}
								else
								{
									cout << "\t";
									msg="\n. . .Error! :: Inputted value "+ scan +" is not an integer!\n\n ";
									prompt.push_back(msg);
								}
								
							}
						}
					}
			
					else
					{
						if(scan.compare(reserved[1])==0)
						{
							term();
						}
						else
						{
							if(prompts==1)
							{
								cout << endl << ". . .Error! Expects IS after a variable declaration :: received " << scan << endl;
							}
							else
							{
								cout <<"\t";
								msg="\n. . .Error! Expects IS after a variable declaration :: received " +scan + "\n";
								prompt.push_back(msg);
							}
						}
					}
					
				}	
			}
		
			else
			{
				if(scan.compare(reserved[1])==0)
				{
					term();
				}
				else
				{
					if(prompts==1)
					{
						cout << endl << ". . .Error! " << var << " is an INVALID variable name!! " << endl << endl;
					}
					else
					{
						cout <<"\t";
						msg="\n. . .Error! "+var+ " is an INVALID variable name!!\n\n ";
					}
				}
			}
			
		}
		
		//varname is already used as a string!
		else
		{
			if(prompts==1)
			{
				cout << endl << ". . .Error! :: Variable "<< var <<" is already set as a string!" << endl << endl;
			}
			else
			{
				cout << "\t";
				msg="\n. . .Error! :: Variable "+var +" is already set as a string!\n\n";
				prompt.push_back(msg);
			}
		}
	
	}
	
	//variable name can't be reserved word
	else
	{
		if(scan.compare(reserved[1])==0)
		{
			term();
		}
		else
		{
			if(prompts==1)
			{
				cout << endl << ". . .Error! :: Variable name can't be reserved word!" << endl << endl;
			}
			else
			{
				cout << "\t";
				msg="\n. . .Error! :: Variable name can't be reserved word!\n\n" ;
				prompt.push_back(msg);
			}
		}
		
	}
}	

//function for INTO:: Declaration of variable (iteration version)
void iterInto(int prompts, int &z, int w)
{
	int answer;
	bool valid, beg, used;
	z=z+1;			// well expect an variable name after the string into
	var=tokens[z];			//we set the latest string as var
	
	valid=isvalid(var);			//checks if varname is valid
	
	beg=wasBeg(var);				//checks if varname was already declared as a string		
	
	used=isReserved(var);		//checks if varname is a reserved word
	
	if(used)
	{
		if(beg)
		{	
			if(valid)
			{
				flag=identexist(tokens[z]);	//we send the vector of identifiers and variable name for searching if this inputted variable was declared before
				/*It should enter in this if condition if an identifier was declared before*/
					
				if(flag)
				{
					
					varindex=getvalue(tokens[z]);	//index of variable in which it was previously defined					
					z=z+1;
					
					if(tokens[z].compare(reserved[3])==0) //well expect IS after a variable
					{
						z=z+1;			// well expect either an operation reserved word or a new value for the current variable
				
						if(reserved[8].compare(tokens[z])==0)	//if the latest string is "ADD" we enter this block
						{
							iteroperation(1,varindex,z,w);
						}
								
						else if(reserved[9].compare(tokens[z])==0)	//if the latest string is "SUB" we enter this block
						{
							iteroperation(2,varindex,z,w);
						}
				
						else if(reserved[6].compare(tokens[z])==0)	//if the latest string is "MULT" we enter this block
						{
							iteroperation(3,varindex,z,w);
						}
						
						else if(reserved[7].compare(tokens[z])==0)	//if the latest string is "DIV" we enter this block
						{
							iteroperation(4,varindex,z,w);
						}
								
						else if(reserved[10].compare(tokens[z])==0)	//if the latest string is "MOD" we enter this block
						{
							iteroperation(5,varindex,z,w);
						}
							
						//if the latest scanned string isn't an operation reserved word, it is  new assignment for that previously defined variable
						else
						{
							vals=tokens[z].c_str();
						
							if(isdigit(vals[0]))
							{	
								if(w==0)
								{
									changeval(varindex, tokens[z]);
									//statement is in ITERATIVE block
									msg="... Set value of "+var+" to "+tokens[z]+"\n\n";
									prompt.push_back(msg);
								}
								else if(w==2)
								{
									//do nothing
								}
								else
								{
									changeval(varindex, tokens[z]);
									//statement is in ITERATIVE block
									msg="... Set value of "+var+" to "+tokens[z]+"\n\n";
									iterative.push_back(msg);
								}
								
								z=z+1;	
							}
							else if(tokens[z].compare(reserved[1])==0)
							{
								term();
							}
							
							else
							{
								if(w==0)
								{
									msg="\n. . .Error! Expects a value :: received "+tokens[z]+"\n";
									prompt.push_back(msg);
								}
								else if(w==2)
								{
									//do nothing
								}
								else
								{
									msg="\n. . .Error! Expects a value :: received "+tokens[z]+"\n";
									iterative.push_back(msg);
								}
								
								z=z+1;
							}
						}
					}
			
					else
					{
						//LOIS
						if(tokens[z].compare(reserved[1])==0)
						{
							term();
						}
						else
						{
							if(w==0)
							{
								msg="\n. . .Error! Expects IS after a variable declaration :: received " +tokens[z] +"\n";
								prompt.push_back(msg);
							}
							else if(w==2)
							{
								//do nothing
							}
							else
							{
								msg="\n. . .Error! Expects IS after a variable declaration :: received " +tokens[z] +"\n";
								iterative.push_back(msg);
							}
							
							z=z+1;
						}
					}
				}
						
				else
				{
					z=z+1;
					if(tokens[z].compare(reserved[3])==0)		//IS
					{
						z=z+1;
						
						vals=tokens[z].c_str();
						valid=isnum(tokens[z],vals);
					
						if(valid)
						{
							//statement is in block
							
							if(w==0)
							{
								ident.push_back(var);			//we scan this new variable name and push it to our vector for identifiers
								value.push_back(tokens[z]);
								msg="... Set value of "+var+" to "+tokens[z]+"\n\n";
								prompt.push_back(msg);
							}
							else if(w==2)
							{
								//do nothing
							}
							else
							{
								ident.push_back(var);			//we scan this new variable name and push it to our vector for identifiers
								value.push_back(tokens[z]);
								msg="... Set value of "+var+" to "+tokens[z]+"\n\n";
								iterative.push_back(msg);
							}
							
							z=z+1;
						}
					
						else
						{
							if(tokens[z].compare(reserved[1])==0)
							{
								term();
							}
							else
							{
								if(w==0)
								{
									msg="\n. . .Error! :: Inputted value "+ tokens[z] +" is not an integer!\n\n ";
									prompt.push_back(msg);
								}
								else if(w==2)
								{
									//do nothing
								}
								else
								{
									msg="\n. . .Error! :: Inputted value "+ tokens[z] +" is not an integer!\n\n ";
									iterative.push_back(msg);
								}
								
								z=z+1;	
							}
						}
					}
			
					else
					{
						if(tokens[z].compare(reserved[1])==0)
						{
							term();
						}
						else
						{
							if(w==0)
							{
								msg="\n. . .Error! Expects IS after a variable declaration :: received " +tokens[z] + "\n";
								prompt.push_back(msg);
							}
							else if(w==2)
							{
								//do nothing
							}
							else
							{
								msg="\n. . .Error! Expects IS after a variable declaration :: received " +tokens[z] + "\n";
								iterative.push_back(msg);
							}
							
							z=z+1;
						}
					}
					
				}	
			}
		
			else
			{
				if(tokens[z].compare(reserved[1])==0)
				{
					term();
				}
				else
				{
					if(w==0)
					{
						msg="\n. . .Error! "+var+ " is an INVALID variable name!!\n\n ";
						prompt.push_back(msg);
					}
					else if(w==2)
					{
						//do nothing
					}
					else 
					{
						msg="\n. . .Error! "+var+ " is an INVALID variable name!!\n\n ";
						iterative.push_back(msg);
					}
					
					z=z+1;
				}
			}
			
		}
		
		//varname is already used as a string!
		else
		{
			if(w==0)
			{
				msg="\n. . .Error! :: Variable "+var +" is already set as a string!\n\n";
				prompt.push_back(msg);
			}
			else if(w==2)
			{
				//do nothing
			}
			else
			{
				msg="\n. . .Error! :: Variable "+var +" is already set as a string!\n\n";
				iterative.push_back(msg);
			}
			
			z=z+1;
		}
	
	}
	
	//variable name can't be reserved word
	else
	{
		if(tokens[z].compare(reserved[1])==0)
		{
			term();
		}
		else
		{
			if(w==0)
			{
				msg="\n. . .Error! :: Variable name can't be reserved word!\n\n" ;
				prompt.push_back(msg);
			}
			else if(w==2)
			{
				//do nothing
			}
			else
			{
				msg="\n. . .Error! :: Variable name can't be reserved word!\n\n" ;
				iterative.push_back(msg);
			}
			
			z=z+1;
		}
		
	}
}	


//function for BEG :: Inputs
void isBeg(int prompts)
{
	
	string word;
	bool valid, into, used;
	cin >> scan;			// well expect an variable name after the string into
	
	var=scan;				//we set the latest string as var
	valid=isvalid(var);		//we check if varname is valid
	
	into=wasInto(var);		//checks if variable was already declared to be int
	
	used=isReserved(var);
	
	if(used)
	{
	
		if(into)		//checks if variable was already declared to be int
		{
	
			if(valid)		//we check if varname is valid
			{
				flag=identexistbeg(var);	
		
				//it already exists
				if(flag)
				{
					varindex=getvaluebeg(scan);	//index of variable in which it was previously defined
					
					switch(prompts)
					{
						case 1:							//display
							cout << endl << "INPUT (" << var << "): ";
							cin >> scan;
							getline(cin, word);
							msg=scan+word;				//string catenation
							changevalbeg(varindex,msg);
							cout << endl;
							break;
						case 2:						//skip
							cout << "\t";
							cout << endl << "INPUT (" << var << "): ";
							cin >> scan;
							getline(cin, word);
							break;
						default:					//is inside a block
							cout << "\t. . .Sorry! Input inside block(s) feature is still unavailable\n\t";
							break;
					}
					
				}
		
				//new variable
				else
				{
					switch(prompts)
					{
						case 1:							//display
							pambeg.push_back(var);
							cout << endl << "INPUT (" << var << "): ";
							cin >> scan;
							// get more than one string and save it to word for catenation later
							getline(cin, word);
							msg=scan+word;				//string catenation
							begval.push_back(msg);
							cout << endl;
							break;
						case 2:						//skip
							cout << "\t";
							cout << endl << "INPUT (" << var << "): ";
							cin >> scan;
							// get more than one string and save it to word for catenation later
							getline(cin, word);
							break;
						default:				//inside a block
							cout << "\t. . .Sorry! Input inside block(s) feature is still unavailable\n\t";
							break;
					}
				}
			}
	
	
			else
			{
				if(scan.compare(reserved[1])==0)
				{
					term();
				}
				else
				{
					if(prompts==1)
					{
						cout << endl << ". . .Error! :: Invalid varname! " << endl << endl;
					}
					else
					{
						cout << "\t";
						msg="\n. . .Error! :: Invalid varname!\n\n ";
						prompt.push_back(msg);
					}
				}
			}
		}
	
		//if variable was already declared as an int
		else
		{
			if(scan.compare(reserved[1])==0)
			{
				term();
			}
			else
			{
				if(prompts==1)
				{
					cout << endl << ". . .Error! :: Variable "<< var <<" is already set as an integer!" << endl << endl;
				}
				else
				{
					cout << "\t";
					msg="\n. . .Error! :: Variable "+ var+" is already set as an integer!\n\n" ;
					prompt.push_back(msg);
				}
			}
			
		}
	}
	
	//reserved words as variable should result to error
	else
	{
		if(scan.compare(reserved[1])==0)
		{
			term();
		}
		else
		{
			if(prompts==1)
			{
				cout << endl << ". . .Error! :: Variable name can't be reserved word!" << endl << endl;
			}
			else
			{
				cout << "\t";
				msg="\n. . .Error! :: Variable name can't be reserved word!\n\n" ;
				prompt.push_back(msg);
			}
		}
		
	}
}

//function for PRINT :: outputs
void isPrint(int prompts)
{
	bool flag2;
	
	cin >> scan;
				
	flag=identexist(scan);
	
	flag2=identexistbeg(scan);
	
	//if varname is int type
	if(flag)
	{
		if(prompts==2)		//skip
		{
			cout << "\t";
		}
		else
		{
			i=getvalue(scan);		//index of variable
		
		
			//statement isn't on block
			if(prompts==1)
			{
				cout << endl <<". . . PRINT: " << value[i] << endl << endl;
			}
			//statement is in block
			else
			{
				cout << "\t";
			
				msg="\n. . . PRINT: "+value[i]+"\n\n";
				prompt.push_back(msg);
			}
		}
			
	}
	
	//if varname is string format
	else if(flag2==true)
	{
		if(prompts==2)		//skip
		{
			cout << "\t";
		}
		else
		{
			i=getvaluebeg(scan);		//index of variable
			//statement isn't on block
			if(prompts==1)
			{
				cout << endl <<". . . PRINT: " << begval[i] << endl << endl;
			}

			//statement is in block
			else
			{
				cout << "\t";
				msg="\n. . . PRINT: "+begval[i]+"\n\n";
				prompt.push_back(msg);
			}
		}
		
	}
				
	else
	{
		if(scan.compare(reserved[1])==0)		//LOIS
		{
			term();
		}
		//semantic error
		else
		{
			//display
			if(prompts==1)
			{
				cout << "\n. . .ERROR ! Unable to execute PRINT :: variable " << scan << " is found to be undefined!" << endl;
			}
			else if(prompts==2)
			{
				cout << "\t";
			}
			//display after block
			else		
			{
				cout << "\t";
				msg="\n. . .ERROR ! Unable to execute PRINT :: variable "+ scan+" is found to be undefined!\n" ;
				prompt.push_back(msg);
			}
			
		}
	}
	
}

//this function checks whether the given condition (relational statement) is valid
bool isvalidCond(string compA, string compB, string condop)
{
	bool valid, exist;
	
	vals=compA.c_str();
	
	exist=identexist(compA);
	
	//left side of relational operation is defined variable
	if(exist)
	{
		
		for(i=0;i<6;i++)
		{
			//checks if relational operation used is valid
			if(condop.compare(conds[i])==0)
			{
				vals=compB.c_str();
				
				exist=identexist(compB);
				
				//right side of relational statement is defined variable
				if(exist)
				{
					return true;
				}
				
				//check if right side is an int
				else
				{
					valid=isnum(compB,vals);
					
					//right side is really an integer
					if(valid)
					{
						return true;
					}
					
					//semantical error
					else
					{
						return false;
					}
				}
			}
		}
		
		return false;
	}
	
	//check whether left side of relational statement is an int
	else
	{
		valid=isnum(compA,vals);
		
		//if its int proceed
		if(valid)
		{
			//check the relational operator
			for(i=0;i<6;i++)
			{
				//relational operator is valid
				if(condop.compare(conds[i])==0)
				{
					exist=identexist(compB);
					
					//right side of relational statement is defined variable
					if(exist)
					{
						return true;
					}
					
					//check whether right side is int
					else
					{
						vals=compB.c_str();
						
						valid=isnum(compB,vals);
						
						//right side is int
						if(valid)
						{
							return true;
						}
						
						//semantical error
						else
						{
							return false;
						}
						
					}
				}
			}
			
			return false;
		}
	}
	return false;
}

//function for PRINT :: outputs
void iterPrint(int prompts, int &z, int w)
{
	bool flag2;
	
	z=z+1;
	flag=identexist(tokens[z]);
	
	flag2=identexistbeg(tokens[z]);
	
	//if varname is int type
	if(flag)
	{
		
		//is inside an IF statement
		if(w==0)
		{
			i=getvalue(tokens[z]);		//index of variable
			
			msg="\n. . . PRINT: "+value[i]+"\n\n";
			prompt.push_back(msg);
			z=z+1;
		}
		else if(w==2)
		{
			z=z+1;
		}
		else
		{
			if(prompts==0)
			{
				i=getvalue(tokens[z]);		//index of variable
				msg="\n. . . PRINT: "+value[i]+"\n\n";
				prompt.push_back(msg);
				z=z+1;
			}
			else if(prompts==2)
			{
				z=z+1;
			}
			else
			{
				i=getvalue(tokens[z]);		//index of variable
			
				msg="\n. . . PRINT: "+value[i]+"\n\n";
				iterative.push_back(msg);
				z=z+1;
			}
		}
	}
	
	//if varname is string format
	else if(flag2==true)
	{
		//is inside an IF
		if(w==0)		//execute
		{
			i=getvaluebeg(tokens[z]);		//index of variable
			//statement isn't on block
			msg="\n. . . PRINT: "+begval[i]+"\n\n";
			prompt.push_back(msg);
			z=z+1;
		}
		else if(w==2)
		{
			z=z+1;
		}
		else
		{
			if(prompts==0)
			{
				i=getvaluebeg(tokens[z]);		//index of variable
				//statement isn't on block

				msg="\n. . . PRINT: "+begval[i]+"\n\n";
				prompt.push_back(msg);
				z=z+1;
			}
			else if(prompts==2)
			{
				z=z+1;
			}
			else
			{
				i=getvaluebeg(tokens[z]);		//index of variable
				//statement isn't on block

				msg="\n. . . PRINT: "+begval[i]+"\n\n";
				iterative.push_back(msg);
				z=z+1;
			}
		}
		
	}
				
	else
	{
		if(tokens[z].compare(reserved[1])==0)		//LOIS
		{
			term();
		}
		//semantic error
		else
		{
			if(w==0)
			{
				msg="\n. . .ERROR ! Unable to execute PRINT :: variable "+ tokens[z]+" is found to be undefined!\n" ;
				prompt.push_back(msg);
			}
			else if(w==2)
			{
				//do nothing
			}
			else
			{
				msg="\n. . .ERROR ! Unable to execute PRINT :: variable "+ tokens[z]+" is found to be undefined!\n" ;
				iterative.push_back(msg);	
			}
			
			z=z+1;
		}
	}
}

//start of selection block(it would restrict nested selections)
void iterselstart(int prompts, int &z)
{
	z=z+1;
	
	if(tokens[z].compare(reserved[2])==0) 	//if scanned string is INTO 
	{
		if(prompts==2||prompts==0)		//execute till syntax and semantics checking only OR perform it
		{
			iterInto(2,z, prompts);
		}
		else
		{
			iterInto(0,z,prompts);
		}
	} //ENDIF INTO
		
	else if(tokens[z].compare(reserved[5])==0)		//if PRINT
	{	
		
		if(prompts==2||prompts==0)			//execute till syntax and semantics checking only or perform it
		{
			iterPrint(2,z,prompts);
		}
		else
		{
			iterPrint(0,z,prompts);
		}
	}		//endif PRINT condition
				
	else if(tokens[z].compare(reserved[4])==0)		//if BEG
	{
		msg="\t. . .Sorry! Input inside block(s) feature is still unavailable\n\t";
		prompt.push_back(msg);
		z=z+2;
	}				//endif BEG
			
	else if(tokens[z]=="SIOL")
	{
		cout << endl << ". . .Error! :: Program already started!" << endl <<endl;
	}
	
	else if(tokens[z].compare(reserved[11])==0)			//if IF
	{
		cout << endl << ". . .Error! :: Nested selection is not allowed!" << endl <<endl;
		term();
	}
		//endif IF
	
	else if(tokens[z]=="ITERATE")
	{
		cout << endl << ". . .Sorry! :: Nested iteration isn't allowed! " << endl << endl; 
		term();
	}		
	else
	{
		if(tokens[z].compare(reserved[1])==0)		//LOIS means stop
		{
			term();
		}
					
		else if(tokens[z].compare(reserved[12])==0)	//END of selection block
		{
			cout << endl;
		}
					
		else
		{
			msg="\n. . .Error! :: "+ tokens[z] + " does not name a type.\n\n";
			prompt.push_back(msg);
			z=z+1;
		}
				
	}
}

//start of selection block(it would restrict nested selections)
void selstart(int prompts)
{
	cin >> scan;
				
	check=scan.c_str();
			
	if(check[0]=='*' && scan.size()==1)		//comment
	{
		comment();
	}
		
	else if(check[0]=='*')		//if comment
	{		
		if(check[check.length()-1]=='*')
		{
			cout << endl;
		}	
		else
		{	
			comment();	
		}		
	}		//endif comment

	else if(scan.compare(reserved[2])==0) 	//if scanned string is INTO 
	{
		if(prompts==2)		//execute till syntax and semantics checking only
		{
			isInto(2);
		}
		else
		{
			isInto(0);
		}
	} //ENDIF INTO
		
	else if(scan.compare(reserved[5])==0)		//if PRINT
	{	
		
		if(prompts==2)			//execute till syntax and semantics checking only
		{
			isPrint(2);
		}
		else
		{
			isPrint(0);
		}
	}		//endif PRINT condition
				
	else if(scan.compare(reserved[4])==0)		//if BEG
	{
		if(prompts==2)		//execute till syntax and semantics checking only
		{
			isBeg(2);
		}
		else
		{
			isBeg(0);
		}
		
	}				//endif BEG

	else if(scan.compare(reserved[14])==0)
	{
		iterate(prompts);
	}			
	else if(scan=="SIOL")
	{
		cout << endl << ". . .Error! :: Program already started!" << endl <<endl;
	}
	
	else if(scan.compare(reserved[11])==0)			//if IF
	{
		cout << endl << ". . .Error! :: Nested selection is not allowed!" << endl <<endl;
	}		//endif IF
	
	//iteration inside a selection
	else if(scan.compare(reserved[14])==0)
	{
		if(prompts==2)		//execute till syntax and semantics checking only
		{
			iterate(2);
		}
		else
		{
			iterate(0);
		}
	}	
	else
	{
		if(scan.compare(reserved[1])==0)		//LOIS means stop
		{
			term();
		}
					
		else if(scan.compare(reserved[12])==0)	//END of selection block
		{
			cout << endl;
		}
					
		else
		{
			cout << endl << ". . .Error! :: "<< scan << " does not name a type." <<endl << endl;
		}
				
	}
}

//returns the number from an int or a previously defined variable
int getnumber(string var)
{
	string temp;
	flag=identexist(var);
	
	if(flag)
	{
		index=getvalue(var);		//get the index of variable
		temp=value[index];
		vals=temp.c_str();
		return atoi(vals);		//int version of variable value
	}
	
	else
	{
		vals=var.c_str();
		return atoi(vals);		//int version of value
	}
}

//this function returns the relational operator of the conditional statement
int getrelate(string condop)
{
	for(i=0;i<6;i++)
	{
		if(condop.compare(conds[i])==0)
		{
			return i;
		}
	}
}

//this function prints the prompts after the block (iterated version)
void iterafterend()
{
	for(i=0;i<prompt.size();i++)
	{
		//printing all prompts
		iterative.push_back(prompt[i]);
	}

	prompt.clear();			//clears the prompt vector content
}


//this function prints the prompts after the block
void afterend()
{
	for(i=0;i<prompt.size();i++)
	{
		//printing all prompts
		cout << prompt[i];
	}
	
	prompt.clear();			//clears the prompt vector content
	start();
}

//function for IF :: selection	(iteration version)
void iterIf(int &z)
{
	bool checker;
	string compA, compB, condop;
	int a, b, cond;						//a cond b		ex. a EQUAL B
	
	z=z+1;
	compA=tokens[z];			// the left side of comparison which is expected to be either be a previously defined variable or an integer
	z=z+1;
	condop=tokens[z];		//the expected coneditional operator
	z=z+1;
	compB=tokens[z];			// the right side of comparison which is expected to be either be a previously defined variable or an integer
	
	checker=isvalidCond(compA, compB, condop);
	
	if(checker)
	{
		z=z+1;
		
		//start of selection block :: BEGIN 
		if(tokens[z].compare(reserved[13])==0)		
		{
			cout <<"\t";
			a=getnumber(compA);
			b=getnumber(compB);
			
			cond=getrelate(condop);
			do{
				switch(cond)
				{
					//selstart() --> 0 if execute, 2 if skip; 
					case 0:
						if(a==b)
						{
							iterselstart(0,z);
						}
						else
						{
							iterselstart(2,z);
						}
						break;
					case 1:
						if(a!=b)
						{
							iterselstart(0,z);
						}
						else
						{
							iterselstart(2,z);
						}
						break;
					case 2:
						if(a<b)
						{
							iterselstart(0,z);
						}
						else
						{
							iterselstart(2,z);
						}
						break;
					case 3:
						if(a>b)
						{
							iterselstart(0,z);
						}
						else
						{
							iterselstart(2,z);
						}
						break;
					case 4:
						if(a<=b)
						{
							iterselstart(0,z);
						}
						else
						{
							iterselstart(2,z);
						}
						break;
					case 5:
						if(a>=b)
						{
							iterselstart(0,z);
						}
						else
						{
							iterselstart(2,z);
						}
						break;
				}
				
			}while(tokens[z].compare(reserved[12])!=0);		
			//end of selection block :: END
			
			cout << endl;
			iterafterend();		//prompts print out of program
		}
		
		else
		{
			if(tokens[z].compare(reserved[1])==0)
			{
				term();
			}
			else
			{
				cout << endl << ". . .Error! Expects BEGIN after a conditional statement :: received " << tokens[z] << endl;
				z=z+1;
			}
		}
	}
	
	else
	{
		cout << endl << ". . .Error! ::: Invalid conditional expression!" << endl << endl;
		z=z+1;
	}
}

//function for IF :: selection
void isIf()
{
	bool checker;
	string compA, compB, condop;
	int a, b, cond;						//a cond b		ex. a EQUAL B
	
	cin >> scan;
	compA=scan;			// the left side of comparison which is expected to be either be a previously defined variable or an integer
	cin >> scan;
	condop=scan;		//the expected coneditional operator
	cin >> scan;
	compB=scan;			// the right side of comparison which is expected to be either be a previously defined variable or an integer
	
	checker=isvalidCond(compA, compB, condop);
	
	if(checker)
	{
		cout <<"\t";
		cin >> scan;
		
		//start of selection block :: BEGIN 
		if(scan.compare(reserved[13])==0)		
		{
			cout <<"\t";
			a=getnumber(compA);
			b=getnumber(compB);
			
			cond=getrelate(condop);
			do{
				switch(cond)
				{
					//selstart() --> 0 if execute, 2 if skip; (*1 is reserved for displaying)
					case 0:
						if(a==b)
						{
							selstart(0);
						}
						else
						{
							selstart(2);
						}
						break;
					case 1:
						if(a!=b)
						{
							selstart(0);
						}
						else
						{
							selstart(2);
						}
						break;
					case 2:
						if(a<b)
						{
							selstart(0);
						}
						else
						{
							selstart(2);
						}
						break;
					case 3:
						if(a>b)
						{
							selstart(0);
						}
						else
						{
							selstart(2);
						}
						break;
					case 4:
						if(a<=b)
						{
							selstart(0);
						}
						else
						{
							selstart(2);
						}
						break;
					case 5:
						if(a>=b)
						{
							selstart(0);
						}
						else
						{
							selstart(2);
						}
						break;
				}
				
			}while(scan.compare(reserved[12])!=0);		
			//end of selection block :: END
			
			cout << endl;
			afterend();		//prompts print out of program
		}
		
		else
		{
			if(scan.compare(reserved[1])==0)
			{
				term();
			}
			else
			{
				cout << endl << ". . .Error! Expects BEGIN after a conditional statement :: received " << scan << endl;
			}
		}
	}
	
	else
	{
		cout << endl << ". . .Error! ::: Invalid conditional expression!" << endl << endl;
	}
}

//iteration process
void iteration(int initial, int test, int prompts)
{
	string star;
		
	do{
		if(prompts==0)
		{
			//printouts for guidance purposes
			star=to_string(initial);
			msg="\n\t\t ----- AT ITERATION "+star+" -----\n";
			prompt.push_back(msg);
		}
		else if(prompts==2)
		{
			//do nothing
		}
		else
		{
			//printouts for guidance purposes
			star=to_string(initial);
			msg="\n\t\t ----- AT ITERATION "+star+" -----\n";
			iterative.push_back(msg);
		}
		
		z=0;
		do
		{
			//PRINT
			if(tokens[z]=="PRINT")
			{
				iterPrint(1,z, prompts);
			}
			//INTO
			else if(tokens[z]=="INTO")
			{
				iterInto(1,z,prompts);
			}
			else if(tokens[z]=="BEG")
			{
				msg="\n. . .Sorry ! Input inside block(s) is not allowed in this version.\n\n";
				iterative.push_back(msg);
				z=z+2;
			}
			//if
			else if(tokens[z].compare(reserved[11])==0)
			{
				iterIf(z);
			}
			//endif
			else if(tokens[z]=="END")
			{
				z=z+1;
			}
			else if(tokens[z]=="ENDLOOP")
			{
				break;
			}
			else
			{
				if(prompts==0)
				{
					msg=". . .Error! :: "+tokens[z] +" does not name a type.\n\n";
					prompt.push_back(msg);
				}
				else if(prompts==2)
				{
					//do nothing
				}
				else
				{
					msg=". . .Error! :: "+tokens[z] +" does not name a type.\n\n";
					iterative.push_back(msg);
				}
				
				z=z+1;
			}
			
		}while(z<tokens.size());
		
		initial=initial+1;
		
	}while(initial<=test);
	
	if(prompts==0||prompts==2)
	{
		for(i=0;i<iterative.size();i++)
		{
			prompt.push_back(iterative[i]);
		}
	}
	else
	{
		for(i=0;i<iterative.size();i++)
		{
			cout << iterative[i];
		}
	}
	
	iterative.clear();
	tokens.clear();
}

//get tokens of LOOP (a recursive function)
void gettokens(int initial, int test, int prompts)
{
	//check test and initial values
	if(initial>test)
	{
			cout << endl << ". . .Error ! :: Initial value should be lesser than the test value\n\tLoop statement was break" << endl << endl;
	}
	//proceed
	else
	{
		cin >> scan;
		
		check=scan.c_str();
	
		if(check[0]=='*' && scan.size()==1)		//comment
		{
			comment();
			gettokens(initial, test, prompts);
		}
		
		else if(check[0]=='*')		//if comment
		{		
			if(check[check.length()-1]=='*')
			{
				gettokens(initial, test, prompts);
			}	
			else
			{	
				comment();	
				gettokens(initial, test, prompts);
			}		
		}		//endif comment
		
		//ENDLOOP
		else if(scan.compare(reserved[16])==0)
		{
			iteration(initial, test, prompts);
		}
		//ITERATE
		else if(scan.compare(reserved[14])==0)
		{
			cout << endl << "\n. . .Sorry! :: Nested Loop is still unavailable feature! " << endl << endl;
		} 
		//SIOL
		else if(scan.compare(reserved[0])==0)
		{
			cout << endl << "\n. . .Error! :: Program already started!" << endl <<endl;
		}
		//LOIS
		else if(scan.compare(reserved[1])==0)
		{
			term();
		}
		else
		{
			tokens.push_back(scan);
			gettokens(initial, test, prompts);
		}
	}
}

//iterate function
void iterate(int prompts)
{	
	string scan, var, dummy;
	const char * iter;
	int index, iterate, inindex;
	int initial, stepsize, test; 		// ITERATE initial TO test --> (body stepsize ++) [test would end if stepsize>=test]
	
	cin >> scan;
	
	if(identexist(scan))		//a previously declared variable must be inputted next
	{
		var=scan;
		index=getvalue(scan);
		
		inindex=index;
		dummy=value[index];
		iter=dummy.c_str();
		initial=atoi(iter);
		
		cin >> scan;
		if(scan.compare(reserved[17])==0)		//if TO
		{
			cin >> scan;
			//test is also previously defined
			if(identexist(scan))
			{
				index=getvalue(scan);
				iter=value[index].c_str();
				test=atoi(iter);

				cin >> scan;
				if(scan.compare(reserved[15])==0)		//if LOOP
				{
					gettokens(initial, test, prompts);	
				}			//endif LOOP
				else
				{
					cout << "\n\tError! :: Expects LOOP received " << scan << " !\n\n";
				}
			}
			
			//test might be an integer
			else
			{
				iter=scan.c_str();
				if(isnum(scan,iter))
				{
					test=atoi(iter);
					cin >> scan;
					
					if(scan.compare(reserved[15])==0)		//if LOOP
					{
						gettokens(initial, test, prompts);	
					}			//endif LOOP
					else
					{
						cout << "\n\tError! :: Expects LOOP received " << scan << " !\n\n";
					}
				}
				
				else
				{
					cout << endl << ". . .Error! :: Test in iteration statement is invalid! " << endl << endl;
				}
				
			}
		}		//endif TO
		else
		{
			cout << endl << ". . .Error! :: expects TO received " << scan << " !\n\n";
		}
	}
	
	//inputted might also be an integer
	else
	{
		iter=scan.c_str();
		flag=isnum(scan,iter);
		//initial is an integer 
		if(flag)
		{
			initial=atoi(iter);
			cin >> scan;
			w=0;
			if(scan.compare(reserved[17])==0)		//if TO
			{
				cin >> scan;
				
				//a previously defined variable
				if(identexist(scan))
				{
					index=getvalue(scan);
					iter=value[index].c_str();;
					test=atoi(iter);

					cin >> scan;
					if(scan.compare(reserved[15])==0)		//if LOOP
					{
						gettokens(initial, test, prompts);	
					}			//endif LOOP
					else
					{
						cout << "\n\tError! :: Expects LOOP received " << scan << " !\n\n";
					}
				}
				//might be an integer
				else
				{
					iter=scan.c_str();
					if(isnum(scan,iter))
					{
						test=atoi(iter);

						cin >> scan;
						if(scan.compare(reserved[15])==0)		//if LOOP
						{
							gettokens(initial, test, prompts);	
						}			//endif LOOP
						else
						{
						cout << "\n\tError! :: Expects LOOP received " << scan << " !\n\n";
						}		
					}
					//not an integer
					else
					{
						cout << endl << ". . .Error! :: Test in iteration statement is invalid! " << endl << endl;
					}
				}
			}
			else
			{
				cout << endl << ". . .Error! :: expects TO received " << scan << " !\n\n";
			}
		}
		//invalid initial
		else
		{
			cout << endl << ". . .Error! :: Initial in iteration statement is invalid! " << endl << endl;
		}
	}
}


//start of the program
void start()
{
	
	cin >> scan;
	
	check=scan.c_str();
	
	if(check[0]=='*' && scan.size()==1)		//comment
	{
		comment();
	}
		
	else if(check[0]=='*')		//if comment
	{		
		if(check[check.length()-1]=='*')
		{
			cout << endl;
		}	
		else
		{	
			comment();	
		}		
	}		//endif comment

	else if(scan.compare(reserved[2])==0) 	//if scanned string is INTO 
	{
		isInto(1);
	} //ENDIF INTO
		
	else if(scan.compare(reserved[5])==0)		//if PRINT
	{	
		isPrint(1);
	}		//endif PRINT condition
				
	else if(scan.compare(reserved[4])==0)		//if BEG
	{
		isBeg(1);
		//cin.ignore();
	}				//endif BEG
			
	else if(scan=="SIOL")
	{
		cout << endl << ". . .Error! :: Program already started!" << endl <<endl;
	}
	
	else if(scan.compare(reserved[11])==0)			//if IF
	{
		isIf();
	}		//endif IF
	
	else if(scan.compare(reserved[14])==0)			//if ITERATE
	{
		iterate(1);
	}		//endif ITERATE
	
	else if(scan.compare(reserved[1])==0)
	{
		term();
	}
		
	else
	{
		if(scan.compare(reserved[1])==0)		//to prevent LOIS to be detected as an error
		{
			cout << " ";
		}
		else
		{
			cout << endl << ". . .Error! :: "<< scan << " does not name a type." <<endl << endl;
			//break;
		}
				
	}
}

//main program
int main(void)
{
	intro();
	cin >> scan;		//scan the first string and it must be the string SIOL
	
	
	if(reserved[0].compare(scan)==0)	//if it is "SIOL" proceed
	{
		cout << endl;
		// do the whole process while scanned string is not LOIS
		do			
		{
			start();
		}while(reserved[1].compare(scan)!=0);	//END DO LOOP
	}
	else
	{
		cout << endl << ". . .ERROR! Must declare SIOL first!!!!! " << endl << endl;
	}
	
	cout << endl << endl<<"Program terminates...";
	getchar();
	return 0;
}
