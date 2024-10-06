#include "Square.h"
#include <iostream>

Square::Square(const std::pair<int, int>& position, int height) : m_position(position), m_height(height) {
    type = FigureType::Square;
}

void Square::draw() {
    std::cout << "Drawing square at position (" << m_position.first << ", " << m_position.second << "), height: " << m_height << std::endl;
}

void Square::move(int x, int y) {
    m_position.first += x;
    m_position.second += y;
    draw();
}