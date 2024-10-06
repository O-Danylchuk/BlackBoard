#include "Square.h"
#include <iostream>

Square::Square(const std::pair<int, int>& position, int height) : m_position(position), m_height(height), m_type(FigureType::Square) {}

void Square::move(int x, int y) {
    m_position.first += x;
    m_position.second += y;
}