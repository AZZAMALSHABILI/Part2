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
#include "AvZ/menus.h"

int main() {
  while (true) {
    switch (MainGameMenu()) {
    case 1:
      NewGameMenu();
      break;
    case 2:
      AboutGame();
      break;
    case 3:
      exit(1);
      break;
    }
  }

  return 0;
}