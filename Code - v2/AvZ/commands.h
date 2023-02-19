// *********************************************************
// Course: TCP1101 PROGRAMMING FUNDAMENTALS
// Year: Trimester 1, 2022/23 (T2215)
// Lab: T13L
// Names: ABDALLAH A A ELEYAN_1 | MANSOUB WESAM MANSOUB HEMDAN_2 | AZZAM HUSSEIN AHMED ALSHABILI_3
// IDs: 1211305298_1 | 1211304594_2 | 1211305639_3
// Emails: 1211305298@student.mmu.edu.my_1 | 1211304594@student.mmu.edu.my_2 | 1211305639@student.mmu.edu.my_3
// Phones: 01128867649_1 | 0178838574_2 | 01127383214_3
// *********************************************************

#ifndef COMMANDS_ALIEN_VS_ZOMBIE_GAME
#define COMMANDS_ALIEN_VS_ZOMBIE_GAME

#include <vector>
#include "../AvZ/BoardBox.h"

void HandleArrowCommand(std::vector<std::vector<BoardBox>>&);
void ShowGameHelp();
bool QuitGame();
void SaveGame(const std::vector<std::vector<BoardBox>>&, const int&, const int&, const int&);
void LoadGame(std::vector<std::vector<BoardBox>>&, int&, int&, int&, int&, int&);

#endif