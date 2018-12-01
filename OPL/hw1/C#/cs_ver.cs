//Obtained from: https://rosettacode.org/wiki/Combinations#C.2B.2B
//Added user input

using System;
using System.Collections.Generic;
 
public class Program
{
	//recursive function
  public static IEnumerable<int[]> FindCombosRec(int[] buffer, int done, int begin, int end)
  {
	//for loop populating buffer array for length k
    for (int i = begin; i < end; i++)
    {
      buffer[done] = i;

        //if buffer is k in length, we're done
      if (done == buffer.Length - 1)
        yield return buffer;
	//otherwise, recusrively call itself
      else
        foreach (int[] child in FindCombosRec(buffer, done+1, i+1, end))
          yield return child;
    }
  }
 
  public static IEnumerable<int[]> FindCombinations(int m, int n)
  {
	//return the recursive function
    return FindCombosRec(new int[m], 0, 0, n);
  }


//The main function
  static void Main()
  {
	//our two variables
	int k, n;

	//Output to the screen and get user input
	Console.WriteLine("Enter k: ");
	k = Convert.ToInt32(Console.ReadLine());
	Console.WriteLine("Enter n: ");
	n = Convert.ToInt32(Console.ReadLine());

	//iterate through an array of length k with range n
    foreach (int[] c in FindCombinations(k, n))
    {
	//print the sets of combinations to the screen
      for (int i = 0; i < c.Length; i++)
      {
        Console.Write((c[i]+1) + " ");
      }
      Console.WriteLine();
    }
  }
}
