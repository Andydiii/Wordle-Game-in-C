/**
 File: main.c
 Enter a description for this file.
*/

#include <string.h>
#include "cs136-trace.h"
#include "wordle.h"
#include <assert.h>
#include <stdio.h>
#include <wordlist.h>

int main(void) {
  // ************************* evaluate_guess
  char result[6];
  assert(evaluate_guess("apple", "paper", result) 
         == false);
  assert(strcmp(result, "paPe.") == 0);
  assert(evaluate_guess("place", "paper", result) 
         == false); 
  assert(strcmp(result, "Pape.") == 0);
  
  // ************************* find_in_list
  char *words[3] = { "goodbye", "hello", "hurray" };
  assert(find_in_list("goodbye", words, 3) == 0);
  
  //*************************
  char alphabet[27];
  char *guesses1[2] = { "apple", "touch" };
  char *results1[2] = { ".pp..", ".OUCH" };
  available_letters(guesses1, results1, 2, alphabet);
  assert(strcmp(alphabet, ".bCd.fgHijk.mnOPqrs.Uvwxyz")
         == 0);
  //*************************
  char *guesses2[1] = { "apple" };
  char *results2[1] = { ".pp.." };
  char *guesses3[3] = { "abcde", "afgdh", "nylok"};
  char *results3[3] = { "A..d.", "A..d.", "ny..."};
  assert(valid_hard_guess(guesses2, results2, 1, "touch") 
         == false);
  assert(valid_hard_guess(guesses2, results2, 1, "pouch") 
         == true);
  assert(valid_hard_guess(guesses2, results2, 1, "spout") 
         == false);
  assert(valid_hard_guess(guesses3, results3, 3, "adbcd")
         == false);
  assert(valid_hard_guess(guesses3, results3, 3, "anyde")
         == false);
  assert(valid_hard_guess(guesses3, results3, 3, "andyy")
         == true);  
  //*********
}
