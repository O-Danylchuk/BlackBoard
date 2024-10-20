#include "Line.h"

Line::Line(const std::pair<int, int>& position, int length) : m_position(position), m_length(length) {}

void Line::move(int x, int y) {
    m_position.first = x;
    m_position.second = y;
}