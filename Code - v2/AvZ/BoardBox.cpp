// *********************************************************
// Course: TCP1101 PROGRAMMING FUNDAMENTALS
// Year: Trimester 1, 2022/23 (T2215)
// Lab: T13L
// Names: ABDALLAH A A ELEYAN_1 | MANSOUB WESAM MANSOUB HEMDAN_2 | AZZAM HUSSEIN AHMED ALSHABILI_3
// IDs: 1211305298_1 | 1211304594_2 | 1211305639_3
// Emails: 1211305298@student.mmu.edu.my_1 | 1211304594@student.mmu.edu.my_2 | 1211305639@student.mmu.edu.my_3
// Phones: 01128867649_1 | 0178838574_2 | 01127383214_3
// *********************************************************

#include <string>
#include "BoardBox.h"

BoardBox::BoardBox()
  : m_BoxSymbol("_"), m_CharacterLife(0), m_CharacterAttackPower(0), m_CharacterAttackRange(0) {}

BoardBox::BoardBox(const std::string& boxSymbol)
  : m_BoxSymbol(boxSymbol), m_CharacterLife(0), m_CharacterAttackPower(0), m_CharacterAttackRange(0) {}

BoardBox::BoardBox(const std::string& boxSymbol, unsigned int& characterLife)
  : m_BoxSymbol(boxSymbol), m_CharacterLife(characterLife), m_CharacterAttackPower(0), m_CharacterAttackRange(0) {}

BoardBox::BoardBox(const std::string& boxSymbol, unsigned int& characterLife,
  unsigned int& characterAttackPower, unsigned int& characterAttackRange)
  : m_BoxSymbol(boxSymbol), m_CharacterLife(characterLife)
  , m_CharacterAttackPower(characterAttackPower), m_CharacterAttackRange(characterAttackRange) {}

BoardBox::~BoardBox() {}

const std::string& BoardBox::GetBoxSymbol() const {
  return m_BoxSymbol;
}

unsigned int BoardBox::GetCharacterLife() const {
  return m_CharacterLife;
}

unsigned int BoardBox::GetCharacterAttackPower() const {
  return m_CharacterAttackPower;
}

unsigned int BoardBox::GetCharacterAttackRange() const {
  return m_CharacterAttackRange;
}

void BoardBox::SetBoxSymbol(const std::string& boxSymbol) {
  m_BoxSymbol = boxSymbol;
}

void BoardBox::SetCharacterLife(unsigned int characterLife) {
  m_CharacterLife = characterLife;
}

void BoardBox::SetCharacterAttackPower(unsigned int characterAttackPower) {
  m_CharacterAttackPower = characterAttackPower;
}

void BoardBox::SetCharacterAttackRange(unsigned int characterAttackRange) {
  m_CharacterAttackRange = characterAttackRange;
}