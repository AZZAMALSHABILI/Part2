// *********************************************************
// Course: TCP1101 PROGRAMMING FUNDAMENTALS
// Year: Trimester 1, 2022/23 (T2215)
// Lab: T13L
// Names: ABDALLAH A A ELEYAN_1 | MANSOUB WESAM MANSOUB HEMDAN_2 | AZZAM HUSSEIN AHMED ALSHABILI_3
// IDs: 1211305298_1 | 1211304594_2 | 1211305639_3
// Emails: 1211305298@student.mmu.edu.my_1 | 1211304594@student.mmu.edu.my_2 | 1211305639@student.mmu.edu.my_3
// Phones: 01128867649_1 | 0178838574_2 | 01127383214_3
// *********************************************************

#ifndef CORE_ALIEN_VS_ZOMBIE_GAME
#define CORE_ALIEN_VS_ZOMBIE_GAME

#include <vector>
#include <string>
#include "../AvZ/BoardBox.h"

#define ALIEN_LIFE 150

void RenderGameBoard(const std::vector<std::vector<std::string>>&);
void PrepareGameBoard(std::vector<std::vector<BoardBox>>&, const int&);
bool GameBoardToString(const std::vector<std::vector<BoardBox>>&, std::vector<std::vector<std::string>>&, const bool&);
void RenderGameStats(const std::vector<std::vector<BoardBox>>&, const bool&, const bool&, const int&);
void GetCharacterPosition(const std::vector<std::vector<BoardBox>>&, const std::string&, int&, int&);
void ResetAlienAttackPower(std::vector<std::vector<BoardBox>>&);
void AttackAlienPlayer(std::vector<std::vector<BoardBox>>&, const int&);
bool DirectionalMovement(std::vector<std::vector<BoardBox>>&, const std::string, std::string&, int&, int&, bool&, bool&, bool&, int&, const int&);
void StartGame(const int&, const int&, const int&);

#endif