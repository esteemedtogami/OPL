#Obtained from: https://www.geeksforgeeks.org/itertools-combinations-module-python-print-possible-combinations/
#Added user input

#We use the tool combinations from itertools 
#which will find each possible combination
from itertools import combinations

#This function takes a list and a length
#and simply returns every combination of
#length k
def combos(my_ints, k):
   return list(combinations(my_ints, k))

#The main program starts here      
k = input("Please enter k: ")
n = input("Please enter n: ")
my_ints=[]

#Populate the list from 1 to n
for i in range(n):
   my_ints.append(i+1)

#Print the combination function
#to the screen
print combos(my_ints, k)
