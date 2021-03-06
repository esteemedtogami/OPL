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

const char* names[] = {"read", "write", "id", "literal", "gets",
                       "add", "sub", "mul", "div", "lparen", "rparen",
		       "eof", "t_eq", "t_lessthan", "t_greaterthan"};

static token input_token;

void error () {
  //printf ("syntax error\n");
  std::cout << "Syntax error" << std::endl;
    exit (1);
}

void match (token expected) {
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
    else error ();
}

void program ();
void stmt_list ();
void stmt ();
void relation();
void expr ();
void term_tail ();
void term ();
void factor_tail ();
void factor ();
void rel_op();
void add_op ();
void mul_op ();

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
            expr ();
            break;
        default: error ();
    }
}

void relation()
{
  
}

void expr () {
    switch (input_token) {
        case t_id:
        case t_literal:
        case t_lparen:
	  //printf ("predict expr --> term term_tail\n");
	  std::cout << "Predict expr --> term term_tail" << std::endl;
            term ();
            term_tail ();
            break;
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

void rel_op()
{
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
    input_token = scan ();
    program ();
    return 0;
}
