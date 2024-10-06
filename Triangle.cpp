#include "Triangle.h"
#include <iostream>

Triangle::Triangle(const std::pair<int, int>& position, int height, int base) : Figure(position), m_position(position), m_height(height), m_base(base) {
    type = FigureType::Triangle;
}

void Triangle::move(int x, int y) {
    m_position.first += x;
    m_position.second += y;
    draw();
}