(*******************************************************************
   This file ("translator.ml") provides stub functions for the extra
   code you need to write for this assignment.

   There are two major stub functions in "translator.ml":
   "ast_ize_P" (which transforms a parse tree for a program into
   an abstract syntax tree[AST]); and
   "translate" (which translates an AST into an equivalent C program).

   You are also being provided with a file called "parser.ml" which
   contains working code to produce a parse tree for a program.
   Everything in the file "parser.ml" is complete and usable as-is.

   The major entry point for the parser provided in "parser.ml" is
   a function called "parse" invoked with two parameters: A parse table,
   and a string containing a calculator language program.

   The file "parser.ml" constructs two example parse tables:
   "cg_parse_table" (for the original calculator language grammar), and
   "ecg_parse_table" (for the extended calculator language grammar).

   Here are two parser examples which will work as-is:

   parse cg_parse_table sum_ave_prog;;
   parse ecg_parse_table primes_prog;;

   "sum_ave_prog" and "primes_prog" are provided at the end of this
   file (as strings). "sum_ave_prog" uses the original calculator
   language grammar, while "primes_prog" uses the extended calculator
   language grammar.

   When complete, your translator code should work when invoked as
   follows:

   print_string
   (snd
   (translate
   (ast_ize_P
   (parse ecg_parse_table primes_prog)
   )
   )
   );;

   The result of this invocation should be a C program on standard
   output, which can be compiled and run to produce the first N primes
   (where N is a number typed by the user).
 *******************************************************************)


#use "parser.ml";;


(*******************************************************************
   Declarations and functions to transform a parse tree into an
   abstract syntax tree (AST)
 *******************************************************************)

type ast_sl = ast_s list
and ast_s =
    | AST_error
    | AST_assign of (string * ast_e)
    | AST_read of string
    | AST_write of ast_e
    | AST_if of (ast_e * ast_sl)
    | AST_do of ast_sl
    | AST_check of ast_e
and ast_e =
    | AST_binop of (string * ast_e * ast_e)
    | AST_id of string
    | AST_num of string;;

	
let rec ast_ize_P (p:parse_tree) : ast_sl =
  (* your code should replace the following line *)
  PT_nt ("P", [stmtlst; ending]) -> ast_ize_SL stmtlst
(*^^^^^^^^^^^^^^^^^^^^^^not sure if this is right*)

and ast_ize_SL (sl:parse_tree) : ast_sl =
  match sl with
    | PT_nt ("SL", []) -> []
    | PT_nt ("SL", [stmt; stmtlst]) -> ast_ize_S stmt, ast_ize_SL stmtlst 
    (*^^^^^^^^^not sure if this is right*)
    | _ -> raise (Failure "malformed parse tree in ast_ize_SL")

and ast_ize_S (s:parse_tree) : ast_s =
  match s with
    | PT_nt ("S", [PT_id lhs; PT_term ":="; expr])
      -> AST_assign (lhs, (ast_ize_expr expr))
    | PT_nt ("S", [PT_term "read"; PT_id id])
      -> AST_read (id)
    | PT_nt ("S", [PT_term "write"; expr])
      -> AST_write (expr);
    | PT_nt ("S", [PT_term "if"; expr; stmtlst; PT_term "fi"])
      -> AST_if (ast_ize_expr expr, ast_ize_SL stmtlst)
    | PT_nt ("S", [PT_term "do"; stmtlst; PT_term "od"])
      -> AST_do (stmtlst)
    | PT_nt ("S", [PT_term "check"; expr]);
      -> AST_check (expr)
    | _ -> raise (Failure "malformed parse tree in ast_ize_S")

and ast_ize_expr (e:parse_tree) : ast_e =
  (* e is an R, E, T, or F parse tree node *)
  match e with
    | PT_nt ("R", [expr; exprtl]) -> ast_ize_expr expr, ast_ize_reln_tail exprtl
    | PT_nt ("E", [trm; trmtl]) -> ast_ize_expr trm, ast_ize_expr_tail trmtl
    | PT_nt ("T", [fctr; fctrtl]) -> ast_ize_expr fctr, ast_ize_expr_tail fctrtl
    | PT_id (id) -> AST_id (id)
    | PT_num (num) -> AST_num (num)
    | PT_nt ("F", ["("; expr; ")"]) -> ast_ize_expr expr
    | _ -> raise (Failure "malformed parse tree in ast_ize_expr")

and ast_ize_reln_tail (lhs:ast_e) (tail:parse_tree) : ast_e =
  (* lhs in an inheritec attribute.
     tail is an ET parse tree node *)
  match tail with
    | PT_nt ("ET", []) -> []
    | PT_nt ("ET", [PT_term "ro"; expr]) -> ast_ize_expr expr
    | _ -> raise (Failure "malformed parse tree in ast_ize_reln_tail")

and ast_ize_expr_tail (lhs:ast_e) (tail:parse_tree) : ast_e =
  (* lhs in an inherited attribute.
     tail is a TT or FT parse tree node *)
  match tail with
    | PT_nt ("TT", []) -> []
    | PT_nt ("TT", [PT_id "+"; trm; trmtl]) 
      -> AST_binop("+", ast_ize_expr trm, ast_ize_expr_tail trmtl)
    | PT_nt ("TT", [PT_id "-"; trm; trmtl]) 
      -> AST_binop("-", ast_ize_expr trm, ast_ize_expr_tail trmtl)
    | PT_nt ("FT", []) -> []
    | PT_nt ("FT", [PT_id "*"; fctr; fctrtl]) 
      -> AST_binop ("*", ast_ize_expr fctr, ast_ize_expr_tail fctrtl)
    | PT_nt ("FT", [AST_binop "/"; fctr; fctrtl]) 
      -> AST_binop ("/", ast_ize_expr fctr, ast_ize_expr_tail fctrtl)
    | _ -> raise (Failure "malformed parse tree in ast_ize_expr_tail")
;;


(*******************************************************************
   Functions to translate an AST into C
 *******************************************************************)

(* The code below is (obviously) a bare stub. The intent is that when
   you run translate on a full, correct AST, you'll get back code for an
   equivalent C program. If there are any variables that are written in
   the program but never read, you'll also get a warning message
   indicating their names and the lines on which the writes occur. Your
   C program should contain code to check for dynamic semantic errors. *)

(*The following is commented out so this stub code will not produce errors!*)

let rec translate (ast:ast_sl)
  :  string   * string
  (* warnings   output_program *) = 
  print_string("#include <stdio.h>\n")
    print_string("#include <stdlib.h>\n")
    print_string("#include <ctype.h>\n")
    print_string("#include <limits.h>\n")
    print_string("#define UNINIT = INT_MIN\n\n")

    (* getint function *)
    print_string("int getint() {\n")
    print_string("int n;\n\n)")
    print_string("if (!(scanf(\"%d\", &n)) {\n")
    (* check for EOF *)
    print_string("printf(\"Reached EOF\");\n")
    print_string("exit(1);\n")
    print_string("}\n\n")
    (* check for uninit *)
    print_string("if (!isdigit(n)) {\n")
    print_string("printf(\"Not a digit\");\n")
    print_string("exit(1);\n")
    print_string("}\n\n")
    print_string("return n;\n")

    (* putint function *)
    print_string("void putint(int n) {\n")
    print_string("printf(\"%d\n\", n);\n\n")

    (* check zero divide *)
    print_string("void checkzerodivide (int div) {\n")
    print_string("if (div == 0) {\n")
    print_string("printf(\"Divide by zero\");\n")
    print_string("exit(1);\n")
    print_string("} else {\n")
    print_string("return div;\n")
    print_string("}\n\n")

    (* check uninit *)
    print_string("void checkuninit (int n) {\n")
    print_string("if (n == UNINIT) {\n")
    print_string("printf(\"Uninitialized variable\");\n")
    print_string("exit(1);\n")
    print_string("}\n\n")

    (* main *)
    print_string("int main(void) {\n")

    (* SL *)
    print_string("\nAST_sl [\n " ^ (translate_sl sl))

    (* Epiloge *)
    print_string("return 0;\n")
    printf_string("}")

and translate_sl sl =
  match sl with 
    | [] -> "]"
    | head::[] -> translate_sl head ^ "\n\n"
    | head::rest -> translate_sl head ^ ";\n " ^ translate_sl rest


and translate_s s =
  match s with 
    | AST_error -> "AST_error"
    | AST_assign (lhs, rhs) -> "AST_assign('" ^ lhs ^ "', " ^ translate_e rhs ^ ")"
    | AST_read id -> "AST_read('" ^ id ^ "')"
    | AST_write expr -> "AST_write(" ^ translate__e expr ^ ")"
    | AST_if (expr, sl) -> "AST_if(" ^ translate_e expr ", " ^ translate_sl sl ^ ")"
    | AST_do sl -> "AST_do(" ^ translate_sl sl ^ ")"
    | AST_check expr -> "AST_check(" ^ translate_e expr ^ ")"

and translate_assign (lhs, rhs) : s =
  print_string(AST_assign (lhs, rhs))

and translate_read (id) : s =
  print_string(AST_read (id))

and translate_write (expr) : s =
  print_string(AST_write (expr))

and translate_if (expr, sl) : s =
  print_string(AST_if (expr, sl))

and translate_do  (sl) : s =
  print_string(AST_do (sl))

and translate_check (expr) : s =
  print_string(AST_check (expr))

and translate_expr expr =
  match expr with
    | AST_binop (op, lhs, rhs) -> "AST_binop('" ^ op ^ "', " ^ translate_e lhs ^ ", " ^ translate_e rhs ^ ")"
    | AST_id id -> "AST_id '" ^ id ^ "'"
    | AST_num num -> "AST_num '" ^ num ^ "'";;




(*******************************************************************
   Sample programs in the calculator language
 *******************************************************************)

let sum_ave_prog = "
read a
read b
sum := a + b
write sum
write sum / 2";;
	 
let primes_prog = "
read n
cp := 2
do check n > 0
found := 0
cf1 := 2
cf1s := cf1 * cf1
do check cf1s <= cp
cf2 := 2
pr := cf1 * cf2
do check pr <= cp
if pr == cp
found := 1
fi
cf2 := cf2 + 1
pr := cf1 * cf2
od
cf1 := cf1 + 1
cf1s := cf1 * cf1
od
if found == 0
write cp
n := n - 1
fi
cp := cp + 1
od";;
