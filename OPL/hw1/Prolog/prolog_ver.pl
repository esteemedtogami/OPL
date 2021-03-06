/**
 Code taken from Rosetta Code, https://rosettacode.org/wiki/Combinations#Prolog
    
	This library is commonly used in combinatorial programs
    
*/
:- use_module(library(clpfd)).

/**
	defines a comb function.
	length takes list and int as input
	Predicate fails if L is equivalent to N
	chain forms a partial order Relation.
	Relation is denoted by #<
	Label takes on the value that is created
	This sets up constraints that maintain consistency
    
*/
comb_clpfd(L, M, N) :-
	length(L, M),
	L ins 1..N,
	chain(L, #<),
	label(L).
