#include "Line.h"

Line::Line(const std::pair<int, int>& position, int length) : m_position(position), m_length(length), type(FigureType::Line) {}