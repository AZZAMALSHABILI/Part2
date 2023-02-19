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
#include <fstream>
#include <sstream>
#include <iomanip>
#include "../pf/helper.h"
#include "../AvZ/BoardBox.h"
#include "../AvZ/utilities.h"

void HandleArrowCommand(std::vector<std::vector<BoardBox>>& gameBoard) {
  int rowPosition = 0, columnPosition = 0;
  std::string direction = "";

  do {
    std::cout << "> Row Position On Board:    ";
    std::cin >> rowPosition;
    std::cout << "> Column Position On Board: ";
    std::cin >> columnPosition;
    std::cout << "  Direction Can Be UP, DOWN, LEFT, RIGHT Only!" << std::endl;
    std::cout << "> Target Arrow Direction:   ";
    std::cin >> direction;
    direction = ToLowerCase(direction);

    if (rowPosition < 1 || rowPosition > gameBoard.size()) {
      std::cout << "Error: Invalid Row Position!" << std::endl;
      std::cout << "Row Position Should Be Between 1 and " << gameBoard.size() << " Only!" << std::endl;
    }
    else if (columnPosition < 1 || columnPosition > gameBoard[0].size()) {
      std::cout << "Error: Invalid Column Position!" << std::endl;
      std::cout << "Row Position Should Be Between 1 and " << gameBoard[0].size() << " Only!" << std::endl;
    }
    else if (direction == "up" || direction == "down" || direction == "left" || direction == "right") {
      break;
    }
    else {
      std::cout << "Error: You Have Provided Invalid Direction!" << std::endl;
      std::cout << "Direction Can Be UP, DOWN, LEFT, RIGHT Only!" << std::endl;
    }
  } while (true);

  rowPosition -= 1;
  columnPosition -= 1;

  const std::string SYMBOL = gameBoard[rowPosition][columnPosition].GetBoxSymbol();
  if (SYMBOL == ">" || SYMBOL == "<" || SYMBOL == "^" || SYMBOL == "v") {
    if (direction == "up") gameBoard[rowPosition][columnPosition].SetBoxSymbol("^");
    else if (direction == "down") gameBoard[rowPosition][columnPosition].SetBoxSymbol("v");
    else if (direction == "left") gameBoard[rowPosition][columnPosition].SetBoxSymbol("<");
    else if (direction == "right") gameBoard[rowPosition][columnPosition].SetBoxSymbol(">");
  }
  else {
    std::cout << "Error: Provided Row & Column Position Do Not Have Arrow!" << std::endl;
  }
}

void ShowGameHelp() {
  std::cout << "Our Game Has Following Commands Available:" << std::endl
    << "   up - To Move The Alien Character In Up Direction" << std::endl
    << " down - To Move The Alien Character In Down Direction" << std::endl
    << " left - To Move The Alien Character In Left Direction" << std::endl
    << "right - To Move The Alien Character In Right Direction" << std::endl
    << "arrow - To Switch The Direction Of An Arrow On Game Board" << std::endl
    << " save - To Save The Current Game In The File" << std::endl
    << " load - To Load The Saved Game From The File" << std::endl
    << " help - To See All The Available Commands For Game" << std::endl
    << " quit - To Quit The Game While You Are Playing" << std::endl;
}

bool QuitGame() {
  std::string choice = "";

  do {
    std::cout << "Are You Sure? (y/n) ";
    std::cin >> choice;
    choice = ToLowerCase(choice);

    if (choice == "y" || choice == "yes") return true;
    else if (choice == "n" || choice == "no") return false;
    else std::cout << "Error: Please Enter Y or N" << std::endl;
  } while (true);
}

void SaveGame(const std::vector<std::vector<BoardBox>>& gameBoard, const int& currentRowPosition, const int& currentColumnPosition, const int& numberOfZombies) {
  std::string boardInformation = std::to_string(gameBoard.size()) + ",";
  boardInformation += std::to_string(gameBoard[0].size()) + ",";
  boardInformation += std::to_string(numberOfZombies) + ",";
  boardInformation += std::to_string(currentRowPosition) + ",";
  boardInformation += std::to_string(currentColumnPosition) + "\n";

  for (int i = 0; i < gameBoard.size(); i++) {
    for (int j = 0; j < gameBoard[0].size(); j++) {
      boardInformation += std::to_string(i) + "," + std::to_string(j) + ",";
      boardInformation += gameBoard[i][j].GetBoxSymbol() + ",";
      boardInformation += std::to_string(gameBoard[i][j].GetCharacterAttackPower()) + ",";
      boardInformation += std::to_string(gameBoard[i][j].GetCharacterLife()) + ",";
      boardInformation += std::to_string(gameBoard[i][j].GetCharacterAttackRange()) + "\n";
    }
  }

  std::string filename = "";
  std::cout << "> Provide Filename: ";
  std::cin.ignore();
  std::getline(std::cin, filename);

  std::string choice = "";
  bool addPasswordToFile = false;
  do {
    std::cout << "Want To Add Password To File? (y/n) ";
    std::cin >> choice;
    choice = ToLowerCase(choice);

    if (choice == "y" || choice == "yes") {
      addPasswordToFile = true;
      break;
    }
    else if (choice == "n" || choice == "no") {
      addPasswordToFile = false;
      break;
    }
    else std::cout << "Error: Please Enter Y or N" << std::endl;
  } while (true);

  if (addPasswordToFile) {
    std::string password = "";
    std::cout << "> Provide Password (Only A-Z, a-z, 0-9): ";
    std::cin >> password;
    boardInformation += "Y," + password;
  }
  else {
    boardInformation += "N";
  }

  std::ofstream gameOutput;
  gameOutput.open(filename + ".aVSz", std::ios::out | std::ios::app);
  gameOutput << boardInformation;
  gameOutput.close();
}

void LoadGame(std::vector<std::vector<BoardBox>>& gameBoard, int& numberOfRows, int& numberOfColumns,
  int& numberOfZombies, int& currentRowPosition, int& currentColumnPosition) {
  std::vector<std::vector<BoardBox>> _gameBoard(numberOfRows, std::vector<BoardBox>(numberOfColumns));
  int _numberOfRows = numberOfRows;
  int _numberOfColumns = numberOfColumns;
  int _numberOfZombies = numberOfZombies;
  int _currentRowPosition = currentRowPosition;
  int _currentColumnPosition = currentColumnPosition;

  std::string filename = "";
  std::cout << "> Provide Filename: ";
  std::cin.ignore();
  std::getline(std::cin, filename);

  std::ifstream gameInput(filename + ".aVSz");
  std::string line;
  std::getline(gameInput, line);

  if (line.length() < 3) {
    std::cout << "Error: Invalid Filename!" << std::endl;
    pf::Pause();
    return;
  }

  std::stringstream ss(line);
  std::string word;
  for (int j = 0; std::getline(ss, word, ','); j++) {
    if (j == 0) _numberOfRows = stoi(word);
    else if (j == 1) _numberOfColumns = stoi(word);
    else if (j == 2) _numberOfZombies = stoi(word);
    else if (j == 3) _currentRowPosition = stoi(word);
    else if (j == 4) _currentColumnPosition = stoi(word);
  }

  _gameBoard.clear();
  for (int j = 0; j < _numberOfRows; j++)
    _gameBoard.push_back(std::vector<BoardBox>(_numberOfColumns));

  int cellCount = (_numberOfRows * _numberOfColumns) + 1;
  for (int z = 1; z <= cellCount; z++) {
    std::getline(gameInput, line);
    if (z == cellCount) {
      std::stringstream ss(line);
      std::string word;

      std::string password = "";
      bool hasPassword = false;
      for (int j = 0; std::getline(ss, word, ','); j++) {
        if (j == 0 && word == "Y") hasPassword = true;
        else if (j == 0 && word == "N") hasPassword = false;
        if (j == 1 && hasPassword) password = word;
      }

      bool isValidPassword = false;
      if (hasPassword) {
        std::string userInputtedPassword = "";
        std::cout << "> Provide Password: ";
        std::cin >> userInputtedPassword;

        if (password != userInputtedPassword) {
          std::cout << "Error: Invalid Password!" << std::endl;
          pf::Pause();
          return;
        }
        else {
          isValidPassword = true;
        }
      }

      if (isValidPassword || !hasPassword) {
        gameBoard.clear();
        for (int j = 0; j < _numberOfRows; j++)
          gameBoard.push_back(std::vector<BoardBox>(_numberOfColumns));

        for (int i = 0; i < _numberOfRows; i++) {
          for (int j = 0; j < _numberOfColumns; j++) {
            gameBoard[i][j].SetBoxSymbol(_gameBoard[i][j].GetBoxSymbol());
            gameBoard[i][j].SetCharacterAttackPower(_gameBoard[i][j].GetCharacterAttackPower());
            gameBoard[i][j].SetCharacterAttackRange(_gameBoard[i][j].GetCharacterAttackRange());
            gameBoard[i][j].SetCharacterLife(_gameBoard[i][j].GetCharacterLife());
          }
        }

        numberOfRows = _numberOfRows;
        numberOfColumns = _numberOfColumns;
        numberOfZombies = _numberOfZombies;
        currentRowPosition = _currentRowPosition;
        currentColumnPosition = _currentColumnPosition;
      }
    }
    else {
      std::stringstream ss(line);
      std::string word;

      int rowLocation = 0, columnLocation = 0;
      int characterAttackPower = 0, characterLife = 0, characterAttackRange = 0;
      std::string symbol = "";

      for (int j = 0; std::getline(ss, word, ','); j++) {
        if (j == 0) rowLocation = stoi(word);
        else if (j == 1) columnLocation = stoi(word);
        else if (j == 2) symbol = word;
        else if (j == 3) characterAttackPower = stoi(word);
        else if (j == 4) characterLife = stoi(word);
        else if (j == 5) characterAttackRange = stoi(word);
      }

      _gameBoard[rowLocation][columnLocation].SetBoxSymbol(symbol);
      _gameBoard[rowLocation][columnLocation].SetCharacterAttackPower(characterAttackPower);
      _gameBoard[rowLocation][columnLocation].SetCharacterLife(characterLife);
      _gameBoard[rowLocation][columnLocation].SetCharacterAttackRange(characterAttackRange);
    }
  }

  gameInput.close();
}