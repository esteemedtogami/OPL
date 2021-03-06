/* Complete recursive descent parser for the calculator language.
    Builds on figure 2.16.  Prints a trace of productions predicted and
    tokens matched.  Does no error recovery: prints "syntax error" and
    dies on invalid input.
    Michael L. Scott, 2008-2017.
*/

//#include "stdio.h"
//#include "stdlib.h"
#include <iostream>
#include <cstdlib>
#include "scan.hpp"
#include <exception>

const char* names[] = {"read", "write", "id", "literal", "gets",
                       "add", "sub", "mul", "div", "lparen", "rparen", "eof",
		       "lessEq", "greaterEq", "less", "greater"};

static token input_token;

class Syntax_Error{};

void error () {
  //printf ("syntax error\n");
  std::cout << "Syntax error" << std::endl;
  // exit (1);
  return;
}

void match (token expected){
    if (input_token == expected) {
      //printf ("matched %s", names[input_token]);
      std::cout << "Matched " << names[input_token];
        if (input_token == t_id || input_token == t_literal)
	  //printf (": %s", token_image);
	  std::cout << ": " << token_image;
        //printf ("\n");
	std::cout << std::endl;
        input_token = scan ();
    }
    else
      {
	error ();
	input_token =  expected;
	throw Syntax_Error();
      }
}

void program ();
void stmt_list ();
void stmt ();
void relation ();
void expr ();
void expr_tail ();
void term_tail ();
void term ();
void factor_tail ();
void factor ();
void add_op ();
void mul_op ();
void rel_op ();

void program () {
    switch (input_token) {
        case t_id:
        case t_read:
        case t_write:
        case t_eof:
	  //printf ("predict program --> stmt_list eof\n");
	  std::cout << "Predict program --> stmt_list eof" << std::endl;
            stmt_list ();
            match (t_eof);
            break;
        default: error ();
    }
}

void stmt_list () {
    switch (input_token) {
        case t_id:
        case t_read:
        case t_write:
	  //printf ("predict stmt_list --> stmt stmt_list\n");
	  std::cout << "Predict stmt_list --> stmt stmt_list" << std::endl;
            stmt ();
            stmt_list ();
            break;
        case t_eof:
	  //printf ("predict stmt_list --> epsilon\n");
	  std::cout << "Predict stmt_list --> epsilon" << std::endl;
            break;          /*  epsilon production */
        default: error ();
    }
}

void stmt () {
  try
    {
    switch (input_token) {
        case t_id:
	  //printf ("predict stmt --> id gets expr\n");
	  std::cout << "Predict stmt --> id gets expr" << std::endl;
            match (t_id);
            match (t_gets);
            expr ();
            break;
        case t_read:
	  //printf ("predict stmt --> read id\n");
	  std::cout << "Predict stmt --> read id" << std::endl;
            match (t_read);
            match (t_id);
            break;
        case t_write:
	  //printf ("predict stmt --> write expr\n");
	  std::cout << "Predict stmt --> write expr" << std::endl;
            match (t_write);
            relation ();
            break;
        case t_if:
          std::cout << "Predict stmt --> if R SL fi" << std::endl;
            match (t_if);
            relation ();
            stmt_list ();
            match(t_fi);
	    break;
        case t_do:
	  std::cout << "Predict stmt --> do SL do" << std::endl;
	    match (t_do);
	    stmt_list ();
	    match(t_od);
	    break;
        case t_check:
	  std::cout << "Predict stmt --> check R" << std::endl;
	    match (t_check);
	    relation ();
	    break;
      
      
    default: error (); throw Syntax_Error(); //throw exception
    }
    }
  //start exception handling
  catch(Syntax_Error())
    {
      while(true)
	{
	  switch(input_token)
	    {
	      //FIRST (statement)
	    case t_id: case t_read: case t_write:
	      stmt ();
	      return;

	      //FOLLOW (statement)
	    case t_eof:
	      return;

	    default:
	      input_token = scan();
	    }
	}
    }
}

void relation () {
  try
    {
    switch (input_token) {
       case t_id:
       case t_literal:
       case t_lparen:
         std::cout << "Predict relation --> expr expr_tail" << std::endl;
           expr ();
           expr_tail ();
           break;
       default: error (); throw Syntax_Error();
	                                           //throw exception
    }
    }
  //start exception handling
  catch(Syntax_Error())
    {
      while(true)
	{
	  switch(input_token)
	    {
	      //FIRST (relation)
	    case t_id: case t_literal: case t_lparen:
	      relation ();
	      return;

	      //FOLLOW (relation)
	    case t_equal: case t_nEqual: case t_less: case t_greater:
	    case t_read: case t_write: case t_eof:
	      return;

	    default:
	      input_token = scan();
	    }
	}
    }
}

void expr () {
  try
    {
    switch (input_token) {
        case t_id:
        case t_literal:
        case t_lparen:
	  //printf ("predict expr --> term term_tail\n");
	  std::cout << "Predict expr --> term term_tail" << std::endl;
            term ();
            term_tail ();
            break;
        default: error (); throw Syntax_Error();
	                                           //throw exception
    }
    }
  //start exception handling
  catch(Syntax_Error())
    {
      while(true)
	{
	  switch(input_token)
	    {
	      //FIRST (expression)
	    case t_id: case t_literal: case t_lparen:
	      expr ();
	      return;

	      //FOLLOW (relation)
	    case t_rparen:
	    case t_read: case t_write: case t_eof:
	      return;

	    default:
	      input_token = scan();
	    }
	}
    }
}

void expr_tail () {
    switch (input_token) {
        case t_equal:
        case t_nEqual:
        case t_less:
        case t_greater:
        case t_lessEq:
        case t_greaterEq:
	  //printf ("predict term_tail --> add_op term term_tail\n");
	  std::cout << "Predict expr_tail --> rel_op expr"
		    << std::endl;
	    rel_op ();
            expr ();
            break;
        case t_rparen:
        case t_id:
        case t_read:
        case t_write:
        case t_eof:
	  //printf ("predict term_tail --> epsilon\n");
	  std::cout << "Predict term_tail --> epsilon" << std::endl;
            break;          /*  epsilon production */
    default: error ();
    }
}

void term_tail () {
    switch (input_token) {
        case t_add:
        case t_sub:
	  //printf ("predict term_tail --> add_op term term_tail\n");
	  std::cout << "Predict term_tail --> add_op term term_tail"
		    << std::endl;
	    add_op ();
            term ();
            term_tail ();
            break;
        case t_rparen:
        case t_id:
        case t_read:
        case t_write:
        case t_eof:
	  //printf ("predict term_tail --> epsilon\n");
	  std::cout << "Predict term_tail --> epsilon" << std::endl;
            break;          /*  epsilon production */
        default: error ();
    }
}

void term () {
    switch (input_token) {
        case t_id:
        case t_literal:
        case t_lparen:
	  //printf ("predict term --> factor factor_tail\n");
	  std::cout << "Predict term --> factor factor_tail" << std::endl;
            factor ();
            factor_tail ();
            break;
        default: error ();
    }
}

void factor_tail () {
    switch (input_token) {
        case t_mul:
        case t_div:
	  //printf ("predict factor_tail --> mul_op factor factor_tail\n");
	  std::cout << "Predict factor_tail --> mul_op factor factor_tail"
		    << std::endl;
            mul_op ();
            factor ();
            factor_tail ();
            break;
        case t_add:
        case t_sub:
        case t_rparen:
        case t_id:
        case t_read:
        case t_write:
        case t_eof:
	  //printf ("predict factor_tail --> epsilon\n");
	  std::cout << "Predict factor_tail --> epsilon" << std::endl;
            break;          /*  epsilon production */
        default: error ();
    }
}

void factor () {
    switch (input_token) {
        case t_id :
	  //printf ("predict factor --> id\n");
	  std::cout << "Predict factor --> id" << std::endl;
            match (t_id);
            break;
        case t_literal:
	  //printf ("predict factor --> literal\n");
	  std::cout << "Predict factor --> literal" << std::endl;
            match (t_literal);
            break;
        case t_lparen:
	  //printf ("predict factor --> lparen expr rparen\n");
	  std::cout << "Predict fatcor --> lparen expr rparen" << std::endl;
            match (t_lparen);
            expr ();
            match (t_rparen);
            break;
        default: error ();
    }
}

void rel_op () {
    switch (input_token) {
        case t_equal:
	  //printf ("predict rel_op --> equal\n");
	  std::cout << "Predict rel_op --> equal" << std::endl;
            match (t_equal);
            break;
        case t_nEqual:
	  //printf ("predict rel_op --> nEqual\n");
	  std::cout << "Predict rel_op --> nEqual" << std::endl;
            match (t_nEqual);
            break;
	case t_less:
	  //printf ("predict rel_op --> less\n");
	  std::cout << "Predict rel_op --> less" << std::endl;
            match (t_less);
            break;
	case t_greater:
	  //printf ("predict rel_op --> greater\n");
	  std::cout << "Predict rel_op --> greater" << std::endl;
            match (t_greater);
            break;
	case t_lessEq:
	  //printf ("predict rel_op --> lessEq\n");
	  std::cout << "Predict rel_op --> lessEq" << std::endl;
            match (t_lessEq);
            break;
	case t_greaterEq:
	  //printf ("predict rel_op --> greaterEq\n");
	  std::cout << "Predict rel_op --> greaterEq" << std::endl;
            match (t_greaterEq);
            break;
        default: error ();
    }
}

void add_op () {
    switch (input_token) {
        case t_add:
	  //printf ("predict add_op --> add\n");
	  std::cout << "Predict add_op --> add" << std::endl;
            match (t_add);
            break;
        case t_sub:
	  //printf ("predict add_op --> sub\n");
	  std::cout << "Predict add_op --> sub" << std::endl;
            match (t_sub);
            break;
        default: error ();
    }
}

void mul_op () {
    switch (input_token) {
        case t_mul:
	  //printf ("predict mul_op --> mul\n");
	  std::cout << "Predict mul_op --> mul" << std::endl;
            match (t_mul);
            break;
        case t_div:
	  //printf ("predict mul_op --> div\n");
	  std::cout << "Predict mul_op --> div" << std::endl;
            match (t_div);
            break;
        default: error ();
    }
}

int main () {
  std::cout << "Didn't make it to step 4, therefore test doesn't"
	    << " work properly." << std::endl;
    input_token = scan ();
    program ();
    return 0;
}
