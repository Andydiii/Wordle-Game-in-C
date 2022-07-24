#include "wordle.h"
#include <string.h>
#include <assert.h>
#include "cs136-trace.h"

// see wordle.h
// evaluate_guess(secret, guess, result) returns whether or not secret is equal 
//   to guess and modifies result chars (of comparison) as described above
// note: for this function, repeating letters in guess are each handled as
//   described above even if secret contains just one such letter (see example)
// example:
//   char result[6];
//   evaluate_guess("apple", "paper", result) => false; result => "paPe."
//   evaluate_guess("place", "paper", result) => false; result => "Pape."
// requires: result is sufficiently large [not asserted]
//           secret and guess have the same length
// effects: result will be modified
// time: O(n^2)
bool evaluate_guess(const char *secret, const char *guess, char *result) {
  assert(secret);
  assert(guess);
  assert(result);
  int len_secret = strlen(secret);
  int len_guess = strlen(guess);
  assert(len_guess == len_secret);
  int same_or_not = 0;
  for (int i = 0; i < len_guess; ++i) {
    if (guess[i] == secret[i]) {
      result[i] = guess[i] - 'a' + 'A';
    }
    else {
      --same_or_not;
      for (int j = 0; j < len_guess; ++j) {
        if (guess[i] == secret[j]) {
          result[i] = guess[i];
          break;
        }
        else {
          result[i] = '.';
        }
      }
    }
  }
  if (same_or_not < 0) {
    return false;
  }
  else {
    return true;
  }    
}


// see wordle.h
// find_in_list(guess, word_list, num_words) finds the index of the string 
//    matching guess in word_list, or -1 if no match is found
// example:
//   char *words[3] = { "goodbye", "hello", "hurray" };
//   find_in_list("goodbye", words, 3) => 0
// requires: word_list is sorted lexicographically in ascending order 
//           [not asserted]
// time: O(m * log(num_words)), where m is the length of guess
int find_in_list(const char *guess, char *word_list[], int num_words) {
  assert(guess);
  assert(word_list);
  int i = 0;
  int j = num_words - 1;
  while (i <= j) {
    int mid = (i + j) / 2;
    if (strcmp(word_list[mid], guess) == 0) {
      return mid;
    }
    else if (strcmp(word_list[mid], guess) < 0) {
      i = mid + 1;
    }
    else {
      j = mid - 1;
    }
  }
  return -1;
}


// see wordle.h
// available_letters(guesses, results, num_guesses, alphabet) determines the 
//   status of each alphabet letter a...z in the secret word, based on results
//   of existing guesses; the result is stored in alphabet as an "alphabet
//   string" (null terminated), where each of a..z is:
//     . (period), if the letter does not exist in secret word
//     lowercase letter, if the status of the letter is unknown
//     UPPERCASE letter, if the letter exists in secret word
// example: char alphabet[27]
//          char *guesses[2] = { "apple", "touch" };
//          char *results[2] = { ".pp..", ".OUCH" };
//          available_letters(guesses, results, 2, alphabet);
//          alphabet => ".bCd.fgHijk.mnOPqrs.Uvwxyz"
// requires: first "num_guesses" elements in guesses and results are valid
//           strings of the same length
//           alphabet is sufficiently large [not asserted]
//           num_guesses >= 0
// effects: alphabet is modified
// time: O(num_guesses * m) where m is the length of each guess
void available_letters(char *guesses[], char *results[], int num_guesses,
                       char *alphabet) {
  assert(guesses);
  assert(results);
  assert(num_guesses >= 0);
  int len_alphabet = 26;
  for (int index = 0; index < len_alphabet; ++index) {
    alphabet[index] = 'a' + index;
  }
  int len = strlen(results[0]);
  for (int i = 0; i < num_guesses; ++i) {
    assert(guesses[i]);
    assert(results[i]);
    for (int j = 0; j < len; ++j) {
      int pos = guesses[i][j] - 'a';
      if (results[i][j] == '.') {
        alphabet[pos] = '.';
      }
      else if (alphabet[pos] <= 'z' 
               && alphabet[pos] >= 'a') {
        alphabet[pos] = alphabet[pos] - 'a' + 'A';
      }
    }
  }
}

// see wordle.h
// valid_hard_guess(guesses, results, num_guesses, next_guess) evaluates 
//    whether or not next_guess is a valid attempt, given existing guesses, 
//    when playing Wordle in hard mode which requires that
//    "any revealed hints must be used in subsequent guesses", i.e.
//    A previously correctly positioned letter must be used in the same spot
//       in next_guess.
//    A letter from the secret word that showed up in a wrong spot in guesses
//       cannot be used in the same spot in next_guess.
//    A letter from the secret word that showed up in a wrong spot in guesses
//       should be used in next_guess.
//    A letter that was previous identified as not part of the secret word 
//        cannot be used in next_guess.
// examples: char *guesses[1] = { "apple" };
//           char *results[1] = { ".pp.." };
//           valid_hard_guess(guesses, results, 1, "touch") => false
//           valid_hard_guess(guesses, results, 1, "pouch") => true
//           valid_hard_guess(guesses, results, 1, "spout") => false
// requires: first "num_guesses" elements in guesses and results are valid
//           strings of the same length
//           length of next_guess matches length of strings in guesses
//           num_guesses >= 0
// time: O(num_guesses * m^2) where m is the length of each guess
bool valid_hard_guess(char *guesses[], char *results[], int num_guesses,
                      const char *next_guess) {
  assert(guesses);
  assert(results);
  assert(next_guess);
  int len = strlen(next_guess);
  for (int i = 0; i < num_guesses; ++i) {
    assert(guesses[i]);
    assert(results[i]);
    for (int j = 0; j < len; ++j) {
      if ( (results[i][j] == guesses[i][j] - 'a' + 'A') 
          && (next_guess[j] != guesses[i][j]) ) {
        return false;
      }
      else if ( (results[i][j] <= 'z' 
                 && results[i][j] >= 'a') ) {
        if (next_guess[j] == results[i][j]) {
          return false;
        }
        int reuse_time = 0;
        // check if the letter used again
        for (int pos = 0; pos < len; ++pos) {
          if (next_guess[pos] == results[i][j]) {
            ++reuse_time;
            break;
          }
        }
        if (reuse_time == 0) {
          return false;
        }
      }
      else if (results[i][j] == '.') {
        for (int pos = 0; pos < len; ++pos) {
          if (next_guess[pos] == guesses[i][j]) {
            return false;
          }
        }
      }
    }
  }
  return true;
}

// see wordle.h
// find_solution(guesses, results, num_guesses, 
//               word_list, num_words,
//               solutions, max_solutions) returns the number of potential valid
//               secret words for a Wordle game, from word_list, that would each
//               evaluate to provided results for each of the provided guesses;
//               solutions is modified to store the subset of word_list that
//               matches the described potential secret words
//               the returned number is capped by max_solutions
// note: if find_solution returns the number n then the first n valid potential 
//       secret words from word_list is what to be stored in solutions, 
//       preserving the order.
// example: char *solutions[20] = {0};
//          char *guesses[2] = { "funky", "plane" };
//          char *results[2] = { ".....", "pla.E" };
//          find_solution(guesses, results, 2, 
//                        wordle_word_list, wordle_word_list_len, 
//                        solutions, 20) => 4
//          solutions => { "ample", "apple", "lapse", "maple" }
// requires: first "num_guesses" elements in guesses and results are valid
//           strings of the same lengh
//           max_solutions >= 1
//           num_guesses >= 0
//           if num_guesses > 0, then the length of the first guess must 
//           match the length of all strings in word_list
// effects: solutions may be modified
// time: O(num_words * num_guesses * m) where m is the length of each guess
//valid_hard_guess(char *guesses[], char *results[], 
// int num_guesses, const char *next_guess)
int find_solution(char *guesses[], char *results[], int num_guesses,
                  char *word_list[], int num_words,
                  char *solutions[], int max_solutions) {
  int num = 0;
  assert(guesses);
  assert(results);
  for (int i = 0; i < num_words; ++i) {
    if (num == max_solutions) {
      return num;
    }
    if (valid_hard_guess(guesses, results, num_guesses, word_list[i])) {
      solutions[num] = word_list[i];
      ++num;
    }
  }
  return num;
}