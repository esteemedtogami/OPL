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
        case '+': c = getchar(); return t_add;
        case '-': c = getchar(); return t_sub;
        case '*': c = getchar(); return t_mul;
        case '/': c = getchar(); return t_div;
        case '(': c = getchar(); return t_lparen;
        case ')': c = getchar(); return t_rparen;
      case '=': c = getchar(); return t_eq;
      case '<': c = getchar(); return t_lessthan;
      case '>': c = getchar(); return t_greaterthan;
        default:
	  //printf("error\n");
	  std::perror("error");
	  std::cout << std::endl;
            exit(1);
    }
}
