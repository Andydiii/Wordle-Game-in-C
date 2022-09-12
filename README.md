# Wordle-Game-in-C
In this program, we can play the game Wordle. See The New York Times website website (https://www.nytimes.com/games/wordle/index.html) to play the game (you can press on the “?” icon in the top left corner for a demonstration of game rules). Note that the official Wordle game supports a Hard Mode which requires that "any revealed hints must be used in subsequent guesses" and an Easy Mode that only requires that every guess is a valid five-letter English word.

it is provided with a Wordle client: one that allows you to play the game interactively in the console (interactive.c)

Instructions:
- first you need run the code, then enter 5 as valid letters.
- secondly, you choose the difficulties(easy, normal, and hard)
The interactive client supports three modes of playing: hard (as described above), normal (ensuring each guess is a valid word), and easy (allowing you to enter any sequence of characters for a guess). 

- Then you can start guessing! 
For example: if you type "world", and it shows like "..or.", then the "." means this letter is not in the right word.
- the output of capital letters means the letter is in the right place of the answer word.
- the output of lower case letter then means the letter is in the word, but not correct place.
- For your convience, it will also show an alphabet to let you know whats the rest possible letters you can guess, so the "." in that alphabet means the letter is not in that correct word, so dont choose that letter again!!

Have fun!
