# CMSC124


This the final project for Design and Implementation of Programming Languages. The Interpreter of SIOL (Simple Integer-Oriented Language) is created in C++11. 
As an interactive interpreter, it implements declaration, arithmetic, for loop, relational operators, and iteration line-per-line in command line.

Below is SIOL Grammar

<var_name>-> <letter>{<letter>|<digit>|_}
  
<letter>-> a|b|c…|z|A|B|C..|Z|
  
<digit>-> 0|1|2…|9|
  
<value>-> <digit>{<digit>}
  
<expr>-> <value>|<var_name>
  
<assignment>-> INTO <var_name> IS <expr>
  
<input>-> BEG <var_name>
  
<output>-> PRINT <var_name>
  
<addition>->INTO <var_name> IS ADD <var_name> <var_name>
  
<subtraction>->INTO <var_name> IS SUB <var_name> <var_name>
  
<multiplication>->INTO <var_name> IS MULT <var_name> <var_name>
  
<division>->INTO <var_name> IS DIV <var_name> <var_name>
  
<modulo>->INTO <var_name> IS MOD <var_name> <var_name>
<rel_op>-> <|>|<=|>=|==|!=
  
<if statement>      -> IF <var_name>|<value> <rel_op> <var_name>|<value> THEN
                          BEGIN
                              //more statements here//
                          END
  
<iteration statement> -> ITERATE <var_name>|<value> TO <var_name>|<value>
                         LOOP
                          //more statements here//
                         ENDLOOP
 
NOTE: Indention should be strictly observed.
siol.exe is executable file of siol.cpp.
Images and notepad are guide and format of program interaction.
