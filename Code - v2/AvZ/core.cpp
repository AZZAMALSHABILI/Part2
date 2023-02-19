// *********************************************************
// Course: TCP1101 PROGRAMMING FUNDAMENTALS
// Year: Trimester 1, 2022/23 (T2215)
// Lab: T13L
// Names: ABDALLAH A A ELEYAN_1 | MANSOUB WESAM MANSOUB HEMDAN_2 | AZZAM HUSSEIN AHMED ALSHABILI_3
// IDs: 1211305298_1 | 1211304594_2 | 1211305639_3
// Emails: 1211305298@student.mmu.edu.my_1 | 1211304594@student.mmu.edu.my_2 | 1211305639@student.mmu.edu.my_3
// Phones: 01128867649_1 | 0178838574_2 | 01127383214_3
// *********************************************************

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include "../pf/helper.h"
#include "../AvZ/BoardBox.h"
#include "../AvZ/utilities.h"
#include "../AvZ/commands.h"
#include "../AvZ/core.h"

void RenderGameBoard(const std::vector<std::vector<std::string>>& gameBoardSymbols) {
  std::cout << "  " << char(201) << std::setw(29) << std::setfill(char(205)) << "" << char(187) << std::endl
    << "  " << char(186) << " ALIEN VS ZOMBIES GAME BOARD " << char(186) << std::endl
    << "  " << char(200) << std::setw(29) << std::setfill(char(205)) << "" << char(188) << std::endl;

  const int height = gameBoardSymbols.size();
  const int width = gameBoardSymbols[0].size();

  for (int i = 0, row = 0; i < (height * 2) + 1; i++) {
    if (i % 2 == 0) {
      std::cout << "  ";
      if (i == 0) std::cout << char(218);
      for (int j = 0; j < width; j++) {
        if (i == 0) std::cout << char(196) << char(196) << char(196) << (j == width - 1 ? char(191) : char(194));
        else if (i % 2 == 0 && i != height * 2) {
          if (j == 0) std::cout << char(195);
          std::cout << char(196) << char(196) << char(196) << (j == width - 1 ? char(180) : char(197));
        }
        if (i == height * 2 && j == 0) std::cout << char(192);
        if (i == height * 2 && j > 0 && j < width) std::cout << char(196) << char(196) << char(196) << char(193);
        if (i == height * 2 && j == width - 1) std::cout << char(196) << char(196) << char(196) << char(217);
      }
      std::cout << std::endl;
    }
    else {
      std::cout << row + 1 << " " << char(179);
      for (int j = 0, col = 0; j < width; j++, col++)
        std::cout << " " << gameBoardSymbols[row][col] << " " << char(179);
      std::cout << std::endl;
      row += 1;
    }
  }

  if (width > 9) {
    std::cout << "  ";
    for (int i = 0; i < 9; i++) std::cout << "    ";
    for (int i = 10; i <= width; i++) std::cout << "  " << (int)(i / 10) << " ";
    std::cout << std::endl;
  }
  std::cout << "  ";
  for (int i = 0, j = 1; i < width; i++, j++) {
    if (j % 10 == 0) j = 0;
    std::cout << "  " << j << " ";
  }
  std::cout << std::endl << std::endl;
}



void PrepareGameBoard(std::vector<std::vector<BoardBox>>& gameBoard, const int& numberOfZombies) {
  // Place The Alien In Center Position Of The Board
  short xCenter = gameBoard[0].size() / 2;    // Rows
  short yCenter = gameBoard.size() / 2;       // Columns
  unsigned int life = ALIEN_LIFE;
  gameBoard[yCenter][xCenter] = BoardBox("A", life);

  // Place The Zombies On The Board
  for (int i = 1; i <= numberOfZombies; i++) {
    unsigned int yPosition = GenerateRandomNumber(0, gameBoard.size() - 1);
    unsigned int xPosition = GenerateRandomNumber(0, gameBoard[0].size() - 1);
    unsigned int zombieLife = GenerateRandomNumber(10, 30) * 10;
    unsigned int attackPower = GenerateRandomNumber(1, 3) * 10;
    unsigned int maxAttackRange = gameBoard.size() > gameBoard[0].size() ? gameBoard.size() : gameBoard[0].size();
    unsigned int attackRange = GenerateRandomNumber(1, maxAttackRange);
    gameBoard[yPosition][xPosition] = BoardBox(std::to_string(i), zombieLife, attackPower, attackRange);
  }

  // Place The Other Objects
  std::vector<std::string> GAME_OBJECTS({ "<", ">", "^", "v", "h", "p", "r", " " });
  for (int i = 0; i < gameBoard.size(); i++) {
    for (int j = 0; j < gameBoard[0].size(); j++) {
      if (gameBoard[i][j].GetBoxSymbol() == "_") {
        const std::string object = GAME_OBJECTS[GenerateRandomNumber(0, GAME_OBJECTS.size() - 1)];
        gameBoard[i][j] = BoardBox(object);
      }
    }
  }
}

bool GameBoardToString(std::vector<std::vector<BoardBox>>& gameBoard,
  std::vector<std::vector<std::string>>& gameBoardSymbols, const bool& isZombieTurn) {
  bool isAlienAlive = false;
  for (int i = 0; i < gameBoard.size(); i++) {
    for (int j = 0; j < gameBoard[0].size(); j++) {
      if (isZombieTurn && gameBoard[i][j].GetBoxSymbol() == ".") {
        gameBoard[i][j].SetBoxSymbol(" ");
        gameBoardSymbols[i][j] = " ";
      }
      else { gameBoardSymbols[i][j] = gameBoard[i][j].GetBoxSymbol(); }

      if (int(gameBoard[i][j].GetBoxSymbol()[0]) > 48 && int(gameBoard[i][j].GetBoxSymbol()[0]) < 58)
        gameBoardSymbols[i][j] = gameBoard[i][j].GetCharacterLife() > 0 ? gameBoard[i][j].GetBoxSymbol() : " ";

      if (gameBoard[i][j].GetBoxSymbol() == "A")
        isAlienAlive = gameBoard[i][j].GetCharacterLife() > 0;
    }
  }
  return isAlienAlive;
}

void GetCharacterPosition(const std::vector<std::vector<BoardBox>>& gameBoard, const std::string& symbol,
  int& rowPosition, int& columnPosition) {
  for (int i = 0; i < gameBoard.size(); i++) {
    for (int j = 0; j < gameBoard[0].size(); j++) {
      if (gameBoard[i][j].GetBoxSymbol() == symbol) {
        rowPosition = i;
        columnPosition = j;
        break;
      }
    }
  }
}

void RenderGameStats(const std::vector<std::vector<BoardBox>>& gameBoard, const bool& isAlienTurn, const  bool& isZombieTurn, const int& currentZombieNumber) {
  for (int i = 0; i < gameBoard.size(); i++) {
    for (int j = 0; j < gameBoard[0].size(); j++) {
      if (gameBoard[i][j].GetBoxSymbol() == "A") {
        isAlienTurn ? std::cout << char(176) << char(177) << " " : std::cout << "   ";

        std::cout << std::setfill(' ') << std::setw(10) << std::left << "ALIEN:" << std::setw(12) << std::right
          << "Life = " << gameBoard[i][j].GetCharacterLife() << ", " << std::setw(12)
          << "Attack = " << gameBoard[i][j].GetCharacterAttackPower() << std::endl;
        break;
      }
    }
  }

  for (int zombieNumber = 1; zombieNumber < 10; zombieNumber++) {
    for (int i = 0; i < gameBoard.size(); i++) {
      for (int j = 0; j < gameBoard[0].size(); j++) {
        if (gameBoard[i][j].GetBoxSymbol() == std::to_string(zombieNumber)) {
          (isZombieTurn && (currentZombieNumber == zombieNumber))
            ? std::cout << char(176) << char(177) << " " : std::cout << "   ";

          std::string x = "ZOMBIE " + std::to_string(zombieNumber) + ":";
          std::cout << std::setfill(' ') << std::setw(10) << std::left << x << std::setw(12) << std::right
            << "Life = " << gameBoard[i][j].GetCharacterLife() << ", " << std::setw(12)
            << "Attack = " << gameBoard[i][j].GetCharacterAttackPower() << ", " << std::setw(12)
            << "Range = " << gameBoard[i][j].GetCharacterAttackRange() << std::endl;
          break;
        }
      }
    }
  }
}

void ResetAlienAttackPower(std::vector<std::vector<BoardBox>>& gameBoard) {
  for (int i = 0; i < gameBoard.size(); i++) {
    for (int j = 0; j < gameBoard[0].size(); j++) {
      if (gameBoard[i][j].GetBoxSymbol() == "A") {
        gameBoard[i][j].SetCharacterAttackPower(0);
        break;
      }
    }
  }
}

void AttackAlienPlayer(std::vector<std::vector<BoardBox>>& gameBoard, const int& attackingZombie) {
  int alienRowPosition = 0, alienColumnPosition = 0;
  int attackingZombieRowPosition = 0, attackingZombieColumnPosition = 0;
  int zombieAttackRange = 0, zombieDamagePower = 0;

  GetCharacterPosition(gameBoard, "A", alienRowPosition, alienColumnPosition);

  for (int i = 0; i < gameBoard.size(); i++) {
    for (int j = 0; j < gameBoard[0].size(); j++) {
      if (gameBoard[i][j].GetBoxSymbol() == std::to_string(attackingZombie)) {
        zombieAttackRange = gameBoard[i][j].GetCharacterAttackRange();
        zombieDamagePower = gameBoard[i][j].GetCharacterAttackPower();
        attackingZombieRowPosition = i;
        attackingZombieColumnPosition = j;
        break;
      }
    }
  }

  for (int i = 1; i < zombieAttackRange; i++) {
    bool condition1 = (attackingZombieRowPosition - i) > -1;
    bool condition2 = (attackingZombieRowPosition - i) == alienRowPosition;
    bool condition3 = (attackingZombieColumnPosition + i) < gameBoard[0].size();
    bool condition4 = (attackingZombieColumnPosition - i) == alienColumnPosition;
    bool condition5 = (attackingZombieRowPosition + i) < gameBoard.size();
    bool condition6 = (attackingZombieRowPosition + i) == alienRowPosition;
    bool condition7 = (attackingZombieColumnPosition - i) > -1;
    bool condition8 = (attackingZombieColumnPosition - i) == alienColumnPosition;

    bool conditionA = condition1 && condition2;
    bool conditionB = condition3 && condition4;
    bool conditionC = condition5 && condition6;
    bool conditionD = condition7 && condition8;

    if (conditionA || conditionB || conditionC || conditionD) {
      const int alienLife = gameBoard[alienRowPosition][alienColumnPosition].GetCharacterLife();
      gameBoard[alienRowPosition][alienColumnPosition].SetCharacterLife(alienLife - zombieDamagePower);
      break;
    }
  }
}

bool DirectionalMovement(std::vector<std::vector<BoardBox>>& gameBoard, const std::string direction,
  std::string& gameCommand, int& currentRowPosition, int& currentColumnPosition,
  bool& isAlienTurn, bool& isZombieTurn, bool& takeCommandFromKeyboard, int& zombieNumber, const int& maxZombies) {

  bool isInsideBoundary = false;
  if (direction == "up") isInsideBoundary = currentRowPosition - 1 > -1;
  else if (direction == "down") isInsideBoundary = currentRowPosition + 1 < gameBoard.size();
  else if (direction == "left") isInsideBoundary = currentColumnPosition - 1 > -1;
  else if (direction == "right") isInsideBoundary = currentColumnPosition + 1 < gameBoard[0].size();

  if (!isInsideBoundary) {
    isAlienTurn = false;
    isZombieTurn = true;
    takeCommandFromKeyboard = false;
    std::cout << "Alien Turn Gone..." << std::endl;
    std::cout << "Zombie " << (zombieNumber == 0 ? 1 : zombieNumber) << " Got Turn..." << std::endl;
    return false;
  }

  std::string playerName = "";
  if (isAlienTurn) playerName = "Alien";
  else if (isZombieTurn) playerName = "Zombie " + std::to_string(zombieNumber == 0 ? 1 : zombieNumber);
  std::cout << playerName << " Moved " << ToUpperCase(direction) << "!" << std::endl;

  std::string _x = gameBoard[currentRowPosition][currentColumnPosition].GetBoxSymbol();
  unsigned int attack = gameBoard[currentRowPosition][currentColumnPosition].GetCharacterAttackPower();
  unsigned int range = gameBoard[currentRowPosition][currentColumnPosition].GetCharacterAttackRange();
  unsigned int life = gameBoard[currentRowPosition][currentColumnPosition].GetCharacterLife();

  int rowIndex = 0, columnIndex = 0;
  if (direction == "up") {
    rowIndex = currentRowPosition - 1;
    columnIndex = currentColumnPosition;
  }
  else if (direction == "down") {
    rowIndex = currentRowPosition + 1;
    columnIndex = currentColumnPosition;
  }
  else if (direction == "left") {
    rowIndex = currentRowPosition;
    columnIndex = currentColumnPosition - 1;
  }
  else if (direction == "right") {
    rowIndex = currentRowPosition;
    columnIndex = currentColumnPosition + 1;
  }

  if (!(int(gameBoard[rowIndex][columnIndex].GetBoxSymbol()[0]) > 48
    && int(gameBoard[rowIndex][columnIndex].GetBoxSymbol()[0]) < 58))
    gameBoard[currentRowPosition][currentColumnPosition].SetBoxSymbol(isAlienTurn ? "." : " ");
  else if (isZombieTurn) gameBoard[currentRowPosition][currentColumnPosition].SetBoxSymbol(" ");

  if (direction == "up") currentRowPosition -= 1;
  else if (direction == "down") currentRowPosition += 1;
  else if (direction == "left") currentColumnPosition -= 1;
  else if (direction == "right") currentColumnPosition += 1;

  const std::string SYMBOL = gameBoard[currentRowPosition][currentColumnPosition].GetBoxSymbol();
  if (int(SYMBOL[0]) > 48 && int(SYMBOL[0]) < 58) {
    bool flag = false;
    for (int i = 0; i < gameBoard.size(); i++) {
      for (int j = 0; j < gameBoard[0].size(); j++) {
        if (gameBoard[i][j].GetBoxSymbol() == SYMBOL) {
          gameBoard[i][j].SetCharacterLife(gameBoard[i][j].GetCharacterLife() - attack);
          std::cout << playerName << " Attacked The Zombie!" << std::endl;

          if (gameBoard[i][j].GetCharacterLife() > 0) {
            isAlienTurn = false;
            isZombieTurn = true;
            takeCommandFromKeyboard = false;
          }
          else {
            gameBoard[i][j].SetBoxSymbol("A");
            gameBoard[i][j].SetCharacterLife(life);
          }
          flag = true;
          break;
        }
      }
      if (flag) break;
    }

    return false;
  }
  else if (SYMBOL == "A") {
    unsigned int damage = gameBoard[currentRowPosition][currentColumnPosition].GetCharacterLife() - attack;
    gameBoard[currentRowPosition][currentColumnPosition].SetCharacterLife(damage);
    gameBoard[currentRowPosition][currentColumnPosition + 1].SetBoxSymbol(_x);
    isAlienTurn = true;
    isZombieTurn = false;
    takeCommandFromKeyboard = true;

    return false;
  }
  else {
    if (SYMBOL != "r" && isAlienTurn)
      gameBoard[currentRowPosition][currentColumnPosition].SetBoxSymbol("A");
    else if (SYMBOL != "r" && isZombieTurn)
      gameBoard[currentRowPosition][currentColumnPosition].SetBoxSymbol(std::to_string(zombieNumber));

    if (SYMBOL == "^" || SYMBOL == "<" || SYMBOL == ">" || SYMBOL == "v") {
      takeCommandFromKeyboard = false;
      if (isAlienTurn) attack += 20;
      if (SYMBOL == "^") gameCommand = "up";
      else if (SYMBOL == "v") gameCommand = "down";
      else if (SYMBOL == "<") gameCommand = "left";
      else if (SYMBOL == ">") gameCommand = "right";
    }
    else if (SYMBOL == "p") {
      bool isPodExecuted = false;
      int row = gameBoard.size(), col = gameBoard[0].size();
      takeCommandFromKeyboard = false;

      for (int i = currentRowPosition; i < row; i++) {
        col = gameBoard[0].size();
        for (int j = currentColumnPosition; j < col; j++) {
          if (int(gameBoard[i][j].GetBoxSymbol()[0]) > 48 && int(gameBoard[i][j].GetBoxSymbol()[0]) < 58) {
            gameBoard[i][j].SetCharacterLife(gameBoard[i][j].GetCharacterLife() - 10);
            isPodExecuted = true;
            break;
          }
          if (j == gameBoard[0].size() - 1) { j = -1; col = currentColumnPosition; }
        }
        if (isPodExecuted) break;
        if (i == gameBoard.size() - 1) { i = -1; row = currentRowPosition; }
      }

      std::cout << playerName << " Moved To Pod Object!" << std::endl;
    }
    else if (SYMBOL == "r") {
      std::vector<std::string> HIDDEN_ROCK_OBJECTS({ "^", "v", "<", ">", "h", "p" });
      const std::string hiddenRockObject = HIDDEN_ROCK_OBJECTS[GenerateRandomNumber(0, HIDDEN_ROCK_OBJECTS.size() - 1)];
      gameBoard[currentRowPosition][currentColumnPosition].SetBoxSymbol(hiddenRockObject);

      if (direction == "up") currentRowPosition += 1;
      else if (direction == "down") currentRowPosition -= 1;
      else if (direction == "left") currentColumnPosition += 1;
      else if (direction == "right") currentColumnPosition -= 1;

      if (isAlienTurn) gameBoard[currentRowPosition][currentColumnPosition].SetBoxSymbol("A");
      else if (isZombieTurn) gameBoard[currentRowPosition][currentColumnPosition].SetBoxSymbol(std::to_string(zombieNumber));

      isAlienTurn = false;
      isZombieTurn = true;
      takeCommandFromKeyboard = false;

      gameBoard[currentRowPosition][currentColumnPosition].SetCharacterAttackPower(attack);
      gameBoard[currentRowPosition][currentColumnPosition].SetCharacterLife(life);
      gameBoard[currentRowPosition][currentColumnPosition].SetCharacterAttackRange(range);

      std::cout << playerName << " Moved To Rock Object!" << std::endl;
      return true;
    }
    else if (SYMBOL == "h") {
      takeCommandFromKeyboard = false;
      if (isAlienTurn) life += 20;
    }
    else if (SYMBOL == " ") {
      takeCommandFromKeyboard = false;
      std::vector<std::string> DIRECTIONS({ "left", "right", "up", "down" });
      gameCommand = DIRECTIONS[GenerateRandomNumber(0, DIRECTIONS.size() - 1)];

      std::cout << playerName << " Moved To Empty Space!" << std::endl;
    }
    else if (SYMBOL == ".") {
      takeCommandFromKeyboard = false;
      std::vector<std::string> DIRECTIONS({ "left", "right", "up", "down" });
      gameCommand = DIRECTIONS[GenerateRandomNumber(0, DIRECTIONS.size() - 1)];

      std::cout << playerName << " Moved To Trail Object!" << std::endl;
    }

    gameBoard[currentRowPosition][currentColumnPosition].SetCharacterAttackPower(attack);
    gameBoard[currentRowPosition][currentColumnPosition].SetCharacterLife(life);
    gameBoard[currentRowPosition][currentColumnPosition].SetCharacterAttackRange(range);

    // if (zombieNumber <= 0) 
    if (zombieNumber == maxZombies) {
      zombieNumber = 1;
      isZombieTurn = false;
      isAlienTurn = true;
      takeCommandFromKeyboard = true;
    }
    else if (zombieNumber == 0) {
      // isZombieTurn = true;
      isAlienTurn = true;
      takeCommandFromKeyboard = false;
    }
  }

  return false;
}

void StartGame(const int& _numberOfRows, const int& _numberOfColumns, const int& _numberOfZombies) {
  int numberOfRows = _numberOfRows;
  int numberOfColumns = _numberOfColumns;
  int numberOfZombies = _numberOfZombies;

  std::vector<std::vector<std::string>> gameBoardSymbols(numberOfRows, std::vector<std::string>(numberOfColumns));
  std::vector<std::vector<BoardBox>> gameBoard(numberOfRows, std::vector<BoardBox>(numberOfColumns));
  std::vector<bool> whichZombieTurn = std::vector<bool>(numberOfZombies, false);

  int currentRowPosition = gameBoard.size() / 2;
  int currentColumnPosition = gameBoard[0].size() / 2;

  PrepareGameBoard(gameBoard, numberOfZombies);

  std::string playerCommand = "";
  bool isAlienTurn = true;
  bool isZombieTurn = false;
  bool takeCommandFromKeyboard = true;
  int currentZombieNumber = 0;

  bool isFirstIteration = true;
  while (true) {
    // std::cout << "isAlienTurn = " << isAlienTurn << std::endl;
    // std::cout << "isZombieTurn = " << isZombieTurn << std::endl;
    // std::cout << "takeCommandFromKeyboard = " << takeCommandFromKeyboard << std::endl;
    // std::cout << "numberOfZombies = " << numberOfZombies << std::endl;
    // std::cout << "currentZombieNumber = " << currentZombieNumber << std::endl;
    // std::cout << "playerCommand = " << playerCommand << std::endl;
    // std::cout << "currentRowPosition = " << currentRowPosition << std::endl;
    // std::cout << "currentColumnPosition = " << currentColumnPosition << std::endl;
    // pf::Pause();

    if (isFirstIteration) {
      isFirstIteration = false;

      gameBoardSymbols.clear();
      for (int i = 0; i < numberOfRows; i++)
        gameBoardSymbols.push_back(std::vector<std::string>(numberOfColumns));

      playerCommand = "";
      isAlienTurn = true;
      isZombieTurn = false;
      takeCommandFromKeyboard = true;
      currentZombieNumber = 0;
    }

    if (isAlienTurn) currentZombieNumber = 0;

    if (isZombieTurn) {
      if (currentZombieNumber == numberOfZombies) {
        isZombieTurn = false;
        isAlienTurn = true;
        takeCommandFromKeyboard = true;
        currentZombieNumber = 1;
      }
      else {
        isAlienTurn = false;
        takeCommandFromKeyboard = false;
        isZombieTurn = true;
        currentZombieNumber++;
      }
    }

    pf::ClearScreen();

    bool isAlienAlive = GameBoardToString(gameBoard, gameBoardSymbols, isZombieTurn);
    RenderGameBoard(gameBoardSymbols);
    RenderGameStats(gameBoard, isAlienTurn, isZombieTurn, currentZombieNumber);

    if (!isAlienAlive) {
      std::cout << "Alas! Alien Died..." << std::endl;
      pf::Pause();
      break;
    }

    if (isAlienTurn)
      GetCharacterPosition(gameBoard, "A", currentRowPosition, currentColumnPosition);
    else if (isZombieTurn)
      GetCharacterPosition(gameBoard, std::to_string(currentZombieNumber), currentRowPosition, currentColumnPosition);

    if (takeCommandFromKeyboard && isAlienTurn) {
      std::cout << "> Command: ";
      std::cin >> playerCommand;
      playerCommand = ToLowerCase(playerCommand);
    }
    else if (isAlienTurn) {
      takeCommandFromKeyboard = true;
      isZombieTurn = false;
    }

    if (isZombieTurn) {
      const std::vector<std::string> ALLOWED_COMMANDS({ "up", "down", "left", "right" });
      playerCommand = ALLOWED_COMMANDS[GenerateRandomNumber(0, ALLOWED_COMMANDS.size() - 1)];

      ResetAlienAttackPower(gameBoard);
      AttackAlienPlayer(gameBoard, currentZombieNumber);
    }

    if (playerCommand == "up" || playerCommand == "down" || playerCommand == "right" || playerCommand == "left") {
      if (DirectionalMovement(gameBoard, playerCommand, playerCommand, currentRowPosition, currentColumnPosition, isAlienTurn, isZombieTurn, takeCommandFromKeyboard, currentZombieNumber, numberOfZombies))
        continue;
    }
    else if (playerCommand == "arrow")
      HandleArrowCommand(gameBoard);
    else if (playerCommand == "help")
      ShowGameHelp();
    else if (playerCommand == "save")
      SaveGame(gameBoard, currentRowPosition, currentColumnPosition, numberOfZombies);
    else if (playerCommand == "load") {
      LoadGame(gameBoard, numberOfRows, numberOfColumns, numberOfZombies, currentRowPosition, currentColumnPosition);
      isFirstIteration = true;
      continue;
    }
    else if (playerCommand == "quit") if (QuitGame()) break;

    pf::Pause();
  }
}