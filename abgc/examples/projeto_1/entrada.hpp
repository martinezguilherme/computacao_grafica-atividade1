#ifndef ENTRADA_HPP_
#define ENTRADA_HPP_

#include <bitset>

enum class Input { Right, Left, Down, Up, Espaco };

struct Entrada {
  std::bitset<5> m_input; 
};

#endif