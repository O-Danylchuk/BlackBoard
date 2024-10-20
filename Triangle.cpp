#include "Triangle.h"
#include "Figure.h"
#include <iostream>

Triangle::Triangle(const std::pair<int, int>& position, int base) : Figure(position), m_position(position), m_base(base) {}

void Triangle::move(int x, int y) {
    m_position.first = x;
    m_position.second = y;
}