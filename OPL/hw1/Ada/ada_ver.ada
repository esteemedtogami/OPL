--Obtained and adapted from: https://rosettacode.org/wiki/Combinations#Ada

--need this in order to use IO
with Ada.Text_IO;                       use Ada.Text_IO;
with Ada.Integer_Text_IO;           use Ada.Integer_Text_IO;
 
 --main function
procedure Test_Combinations is
   generic
      type Integers is range <>;
      --this is somewhat like a class
   package Combinations is
      type Combination is array (Positive range <>) of Integers;
      procedure First (X : in out Combination);
      procedure Next (X : in out Combination);
      --for some reason the compiler thinks this is private
      --even though we tried to format it like the others
      procedure Final(k : in Integer; n : in Integer); 
      procedure Put (X : Combination);
   end Combinations;
 
   --class definitions
   package body Combinations is
      procedure First (X : in out Combination) is
      begin
         X (1) := Integers'First;
         --populate the X array
         for I in 2..X'Last loop
            X (I) := X (I - 1) + 1;
         end loop;
      end First;
      procedure Next (X : in out Combination) is
      begin
      --this is the sorting and smaller array setup
         for I in reverse X'Range loop
            if X (I) < Integers'Val (Integers'Pos (Integers'Last) - X'Last + I) then
               X (I) := X (I) + 1;
               for J in I + 1..X'Last loop
                  X (J) := X (J - 1) + 1;
               end loop;
               return;
            end if;
         end loop;
         raise Constraint_Error;
      end Next;
      procedure Put (X : Combination) is
      begin
         --this function prints the sorted arrays to the screen
         for I in X'Range loop
            Put (Integers'Image (X (I)));
         end loop;
      end Put;
      procedure Final(k : in Integer; n : in Integer) is
      --this is the function we tried to implement per the blackboard spec
      --It should utilize user input but it is impossible to test
      --as the function is "non-visible" for some reason and
      --the internet has not provided a solution as far as
      --we could find
   subtype length is Integer range 1..n;
   X : Combination (1..k);
   begin
   First (X);
   loop
      Put (X); New_Line;
      Next (X);
   end loop;
exception
   when Constraint_Error =>
      null;
   end Final;
end Combinations;
   --package lengths is new Combinations (length);
   --use lengths;
   k : Integer;
   n : Integer;
begin
   --This asks for user input
   Put("Enter k: ");
   Get(k);
   Put("Enter n: ");
   Get(n);
   Final(k,n);
   --again, for some reason "Final" is private
end Test_Combinations;