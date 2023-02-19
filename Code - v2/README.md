# Alien vs. Zombie

Alien vs. Zombie is a turn-based combat game in which the player takes control of Alien in order to destroy a horde of Zombies. Prior to the game, the player can change the game board dimensions and the number of zombies. A game can also be saved to a file and loaded from a file by the player.

Please provide the YouTube link to your [Video Demo]
( https://youtu.be/Tyml6AlwAyk ) .

## Compilation Instructions

Provide instructions on how to compile your program, especially when it is non-trivial.

For example:

```
g++ pf\*.cpp AvZ\*.h AvZ\*.cpp main.cpp -DDEMO -o game
```

## User Manual

Mainly, this game has two player roles. One is named as Alien which is assigned to the player who is playing this game. And the other one is named as Zombie which is controlled and played by the computer. The Zombie role could have multiple instances, depending on the number of zombies been selected by the Alien player. The higher the number of Zombies, more the game will be tough and hard to play.

Now, to play this game. First, you have to compile it using the above mentioned command. You can execute this command on any command line terminal of your choice. Once the game is successfully compiled, you can play it by typing the executable filename (that is  generated after compilation).

In the main game menu, you have 3 options:

1. **Start New Game** - To Start The New Game, To Which It WIll Further Ask The Following:
   1. Row Count
      - Represents The Number Of Rows You Would Like To Have For Game Board.
      - It Should Be An Odd Number.
   2. Column Count
      - Represents The Number Of Columns You Would Like To Have For Game Board.
      - It Should Be An Odd Number.
   3. Zombie Count
      - Represents The Number Of Zombies You Would Like To Have In Game.
      - It Should Be Between 1 and 9.
2. **About Game** - To Know About The Basic Information Of The Game.
3. **Exit** - To Exit The Execution Of The Game.

Once above information is provided, the program will generate the game board automatically for you. And you can play the game by typing the following different commands (on at a time):

- **up** - To Move The Alien Character In Up Direction
- **down** - To Move The Alien Character In Down Direction
- **left** - To Move The Alien Character In Left Direction
- **right** - To Move The Alien Character In Right Direction
- **arrow** - To Switch The Direction Of An Arrow On Game Board
- **save** - To Save The Current Game In The File
- **load** - To Load The Saved Game From The File
- **help** - To See All The Available Commands For Game
- **quit** - To Quit The Game While You Are Playing

## Progress Log

- [Part 1](PART1.md)
- [Part 2](PART2.md)

## Contributors

Please replace the following with your group members' names. 

- ABDALLAH A A ELEYAN
- MANSOUB WESAM MANSOUB HEMDAN
- AZZAM HUSSEIN AHMED ALSHABILI