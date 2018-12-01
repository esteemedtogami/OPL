/* Simple ad-hoc scanner for the calculator language.
    Michael L. Scott, 2008-2017.
*/

//#include "stdio.h"
//#include "stdlib.h"
//#include "string.h"
//#include "ctype.h"
#include <iostream>
#include <cstdlib>
#include <cctype>
#include <cerrno>

#include "scan.hpp"

char token_img[100];
std::string token_image(token_img);
std::string prev_token_image;

token scan() {
    static int c = ' ';
        /* next available char; extra (int) width accommodates EOF */
    int i = 0;              /* index into token_image */

    /* skip white space */
    while (isspace(c)) {
        c = getchar();
    }
    if (c == EOF)
        return t_eof;
    if (isalpha(c)) {
        do {
	  //token_image[i++] = c;
	  token_image.at(i++) = c;
            c = getchar();
        } while (isalpha(c) || isdigit(c) || c == '_');
        //token_image[i] = '\0';
	token_image.at(i) = '\0';
        //if (!strcmp(token_image, "read")) return t_read;
	if(!(token_image == "read")) return t_read;
        //else if (!strcmp(token_image, "write")) return t_write;
	else if (!(token_image == "write")) return t_write;
	else if (!(token_image == "if")) return t_if;
	else if (!(token_image == "fi")) return t_fi;
	else if (!(token_image == "do")) return t_do;
	else if (!(token_image == "od")) return t_od;
	else if (!(token_image == "check")) return t_check;
        else return t_id;
    }
    else if (isdigit(c)) {
        do {
	  //token_image[i++] = c;
	  token_image.at(i++) = c;
            c = getchar();
        } while (isdigit(c));
        //token_image[i] = '\0';
	token_image.at(i) = '\0';
        return t_literal;
    } else switch (c) {
        case ':':
            if ((c = getchar()) != '=') {
	      //fprintf(stderr, "error\n");
	      std::perror("error");
	      std::cout << std::endl;
                exit(1);
            } else {
                c = getchar();
                return t_gets;
            }
            break;
        case '=':
	    if ((c = getchar()) != '=') {
	      std::perror("error");
	      std::cout << std:: endl;
	        exit(1);
	    } else {
	        c = getchar();
	        return t_equal;
	    }
	    break;
        case '!':
	    if((c = getchar()) != '=') {
	      std::perror("error");
	      std::cout << std::endl;
	        exit(1);
	    } else {
	        c = getchar();
		return t_nEqual;
	    }
	    break;
        case '>':
	    if ((c = getchar()) == '=') {
	      c = getchar();
	      return t_lessEq;
	    } else if (c == ' ') {
	        c = getchar();
	        return t_less;
	    } else {
	        std::perror("error");
	        std::cout << std::endl;
	        exit(1);
	    }
	    break;
	case '<':
	    if ((c = getchar()) == '=') {
	      c = getchar();
	      return t_greaterEq;
	    } else if (c == ' ') {
	        c = getchar();
	        return t_greater;
	    } else {
	        std::perror("error");
	        std::cout << std::endl;
	        exit(1);
	    }
	    break;
        case '+': c = getchar(); return t_add;
        case '-': c = getchar(); return t_sub;
        case '*': c = getchar(); return t_mul;
        case '/': c = getchar(); return t_div;
        case '(': c = getchar(); return t_lparen;
        case ')': c = getchar(); return t_rparen;
        default:
	  //printf("error\n");
	  std::perror("error");
	  std::cout << std::endl;
            exit(1);
    }
}
