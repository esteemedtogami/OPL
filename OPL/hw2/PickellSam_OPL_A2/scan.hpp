/* Definitions the scanner shares with the parser
    Michael L. Scott, 2008-2017.
*/

#include <string>

typedef enum {t_read, t_write, t_id, t_literal, t_gets,
	      t_add, t_sub, t_mul, t_div, t_lparen, t_rparen, t_eof,
	      t_lessEq, t_greaterEq, t_less, t_greater, t_equal, t_do,
	      t_nEqual, t_od, t_if, t_fi, t_check} token;

extern std::string token_image;

extern token scan();
