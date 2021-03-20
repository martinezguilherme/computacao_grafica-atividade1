#ifndef ENTRADA_HPP_
#define ENTRADA_HPP_

#include <bitset>

enum class Input { Right, Left, Down, Up };

struct Entrada {
  std::bitset<4> m_input;  // [fire, up, down, left, right]
};

#endif