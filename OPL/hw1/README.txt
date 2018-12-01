/*********************
Student: Sam Pickell
Date: 2/07/2018
Filename: README.txt
**********************/
----------------------------------------------------------------------

--All code was obtained from https://rosettacode.org/wiki/Combinations
--or https://www.geeksforgeeks.org/itertools-combinations-module-python-print-po
     ssible-combinations/
--and modified in some cases with languages that cooperated when
--trying to implement user input

-------------------------------------------------------------------------

Ada

1. The enviorment was very easy. Using the jgrasp ide it was
   easy enough to run working Ada code. Also Ada is very readable,
   albeit a little intimidating.

2. Trying to program in this language was difficult. As seen
   in the function my partner and I tried to implement, even
   though it followed the same structure as the others, it
   was marked "non-visible". The other challenging part was
   trying to work around variables needing to be declared
   before the main "begin" statement. This makes user input
   incredibly difficult to implement, though our attempted
   function tries to address that.

3. At run time, no one language seemed to be any faster or slower
   than another. However I would believe that Ada is the least
   efficient of all of the languages, based on its sheer length.

4. Strangely enough, I like how wordy Ada is. It's fairly clear
   what everything does just by looking at it. I feel like given
   enough practice with the language, it would be relatively
   straightforward. However, I greatly dislike how not beginner
   friendly Ada is, and how you must declare all variables before
   "main". This greatly affects user input.

5. Iterators weren't used in the Ada implementation. The closest
   thing to iteration was for loops.
   
----------------------------------------------------------------------------

C#

1. This language was a breath of fresh air compared to Ada. Having
   both a Java and C/C++ background, this language was very
   straightforward. It had many of the familar and useful OOP
   tools, such as .length and iterators.

2. The only hard part was adjusting to a new syntax.

3. At run time, no one language seemed to be any faster or slower
   than another.

4. I liked the familiarity it had to languages I've already used,
   and didn't really dislike anything in particular.

5. Iterators were very useful in the C# implementation. Having
   a way to create the sorted groups and print them out in
   order probably made this one of the more efficient
   implementations.

----------------------------------------------------------------------------

OCaml

1. As a programmer, the language was very readable, so
   understanding how it worked wasn't too challenging.

2. OCaml proved to be challenging in that we
   	 a) Weren't able to get user input working
	 b) Couldn't fully test it as we couldn't get it
	    to print to the screen
   However, reading through the code lead us to believe that
   the way it is now, it has a k = 3 and n = 4, and that it
   sorts properly.

3. At run time, no one language seemed to be any faster or slower
   than another. However, we couldn't really prove that for OCaml
   other than that it compiled and built an executable in no time.

4. I liked how "main" could consist of a single line
   of code, and how you could initialize a list from the
   function call. And much like Ada, I disliked how much of
   a challenge it was trying to implement user input, or
   even printing to the screen.

5. This implementation didn't utilize iterators from what we
   could tell, beyond a for loop anyway.

----------------------------------------------------------------------------

Prolog

1. The easiest thing about Prolog was that it has the clpfd library built
   into it, making it easy to write functions over a finite distance.

2. The challenge for Prolog was interfacing with the interpreter. We
   weren't fully able to test it because of this.

3. At run time, no one language seemed to be any faster or slower
   than another. However, like OCaml, there was no real way to prove
   that for Prolog in our case, since we had trouble with the interpreter.
   The only thing we can say for certain was that when the interpreter was
   running, giving it the command "consult('prolog_ver.pl')." returned
   "true". I would believe however, given how short the program is,
   it's probably one of the fastest implmentations.

4. I liked how this program could be written in so few lines, especially
   when compared to Ada and realize they accomplish the same thing. I
   dislike how unintuitive the interpreter is.

5. From what I can tell, chain functions similarly to an iterator, and
   is useful in that regard.

----------------------------------------------------------------------------

Python

1. This was the easiest language to use. Not only was it intuitive
   coming from C++ as they share many elements, but the combination
   function already exists in Python.

2. Nothing in particular that I disliked.

3. At run time, no one language seemed to be any faster or slower
   than another. That being said, as one of the shorter programs
   with the combination function built into the language, it was
   likely one of the faster languages.

4. I liked how beginner friendly Python is, and how it had the
   combination function built in.

5. Iterators were useful in Python, very straightforward in filling
   the array.

----------------------------------------------------------------------------
