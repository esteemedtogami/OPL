(* Code taken from Rosetta Code, https://rosettacode.org/wiki/Combinations#OCaml*)

(* Begin writing combination - comb - function *)
let comb m xs =
  let xs = Array.of_list xs in

(* Exits if m is greater than Array.length xs *)
  if m > Array.length xs then
	[]
  else begin

(* Dynamically allocates an array and initializes to 0 *)
	let arr = Array.make (m+1) [] in
	arr.(0) <- [[]];

(* A for loop with j initialized to 0 and exiting at Array.length xs - m *)
(* i intialized to 1 and exiting at i = m *)
(* List.map puts all the results into one list *)
	for j = 0 to Array.length xs - m do
  	for i = 1 to m do
   	arr.(i) <- arr.(i) @ List.map (fun ys -> xs.(j+i-1)::ys) arr.(i-1)
  	done
	done;
 
	arr.(m)
 
  end
;;

(* Chooses a combination of length 3 from the set 1-4 *)
comb 3 [1;2;3;4];;
