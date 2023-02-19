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
#include "../pf/helper.h"
#include "../AvZ/core.h"

int MainGameMenu() {
  int choice = 0;
  do {
    pf::ClearScreen();
    std::cout << "WELCOME TO ALIEN VS ZOMBIE GAME!" << std::endl;
    std::cout << "1. Start New Game" << std::endl;
    std::cout << "2. About Game" << std::endl;
    std::cout << "3. Exit" << std::endl;
    std::cout << "Selection: ";
    std::cin >> choice;

    if (choice < 1 || choice > 3) {
      std::cout << "Invalid Selection, Try Again!" << std::endl;
      pf::Pause();
      continue;
    }
  } while (choice < 1 || choice > 3);

  return choice;
}

void NewGameMenu() {
  int numberOfRows = 0;
  int numberOfColumns = 0;
  int numberOfZombies = 0;
  bool isValidInformation = false;

  do {
    pf::ClearScreen();

    std::cout << "START NEW GAME - Provide Basic Information" << std::endl;
    std::cout << "> Enter Odd Number Of Rows:               ";
    std::cin >> numberOfRows;
    std::cout << "> Enter Odd Number Of Columns:            ";
    std::cin >> numberOfColumns;
    std::cout << "> Enter Number Of Zombies (between 1-9):  ";
    std::cin >> numberOfZombies;

    if (numberOfRows <= 0 || numberOfColumns <= 0 || numberOfZombies <= 0) {
      std::cout << "No Value Can Be Negative Or Equal To Zero!" << std::endl
        << "Invalid Information, Try Again!" << std::endl;
      pf::Pause();
    }
    else if (numberOfRows % 2 == 0 || numberOfColumns % 2 == 0) {
      std::cout << "Number Of Rows OR Columns Must Be Odd!" << std::endl
        << "Invalid Information, Try Again!" << std::endl;
      pf::Pause();
    }
    else if (numberOfZombies > 9) {
      std::cout << "Number Of Zombies Must Be Less Than 9!" << std::endl
        << "Invalid Information, Try Again!" << std::endl;
      pf::Pause();
    }
    else {
      isValidInformation = true;
    }
  } while (!isValidInformation);

  StartGame(numberOfRows, numberOfColumns, numberOfZombies);
}

void AboutGame() {
  pf::ClearScreen();
  std::cout << "ABOUT GAME" << std::endl;
  std::cout << "Title: Alien VS Zombie" << std::endl;
  std::cout << "Version: v1.0" << std::endl;
  pf::Pause();
}