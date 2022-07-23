 // This is a simple I/O driver client for the wordle module

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "wordle.h"
#include "wordlist.h"

int main(void) {
  char cmd[100] = "";
  char secret[100] = "";
  char guess1[100] = "";
  char guess2[100] = "";
  char guess3[100] = "";
  char guess4[100] = "";
  char guess5[100] = "";
  char guess6[100] = "";
  char result1[100] = "";
  char result2[100] = "";
  char result3[100] = "";
  char result4[100] = "";
  char result5[100] = "";
  char result6[100] = "";
  char *guesses[6] = {guess1, guess2, guess3, guess4, guess5, guess6};
  char *results[6] = {result1, result2, result3, result4, result5, result6};
  char *solutions[100] = {};

  int max_solutions = 100;
  char hard_guess[100] = "";
  char alphabet[27] = "";
  const char *winmsg[2] = {"-", "!"};

  while (1) {
    if (scanf("%s", cmd) != 1) {
      break;
    }
    if (!strcmp(cmd, "guess")) {
      assert(scanf("%s", secret) == 1);
      assert(scanf("%s", guess1) == 1);
      bool success = evaluate_guess(secret, guess1, result1);
      printf("%s: %s => %s %s\n", secret, guess1, result1, winmsg[success]);
    } else if (!strcmp(cmd, "word?")) {
      assert(scanf("%s", guess1) == 1);
      int idx = find_in_list(guess1, wordle_word_list, wordle_word_list_len);
      printf("%s? %d\n", guess1, idx);
    } else if (!strcmp(cmd, "available")) {
      int num_guesses = 0;
      assert(scanf("%d", &num_guesses) == 1);
      for (int i = 0; i < num_guesses; ++i) {
        assert(scanf("%s", guesses[i]) == 1);
        assert(scanf("%s", results[i]) == 1);
      }
      available_letters(guesses, results, num_guesses, alphabet);
      printf("%s\n", alphabet);
    } else if (!strcmp(cmd, "hard")) {
      int num_guesses = 0;
      assert(scanf("%d", &num_guesses) == 1);
      for (int i = 0; i < num_guesses; ++i) {
        assert(scanf("%s", guesses[i]) == 1);
        assert(scanf("%s", results[i]) == 1);
      }
      assert(scanf("%s", hard_guess) == 1);
      bool valid = valid_hard_guess(guesses, results, num_guesses, hard_guess);
      printf("%s> %s\n", hard_guess, winmsg[valid]);
    } else if (!strcmp(cmd, "solve")) {
      int num_guesses = 0;
      assert(scanf("%d", &num_guesses) == 1);
      for (int i = 0; i < num_guesses; ++i) {
        assert(scanf("%s", guesses[i]) == 1);
        assert(scanf("%s", results[i]) == 1);
      }
      int num_solutions = find_solution(guesses, results, num_guesses,
                                        wordle_word_list, wordle_word_list_len,
                                        solutions, max_solutions);
      if (num_solutions == 0) {
        printf("NO SOLUTIONS\n");
      } else {
        for (int i = 0; i < num_solutions; ++i) {
          if (i) {
            printf(" ");
          }
          printf("%s", solutions[i]);
        }
        printf("\n");
      }
    } else {
      break;
    }
  }
}
