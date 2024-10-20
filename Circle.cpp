#include "Circle.h"
#include "Figure.h"
#include <iostream>
#include <utility>

Circle::Circle(const std::pair<int, int> position, int radius) : Figure(position), m_position(position), m_radius(radius) {}

void Circle::move(int x, int y) {
    m_position.first = x;
    m_position.second = y;
}

