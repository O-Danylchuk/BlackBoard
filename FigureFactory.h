#pragma once
#include "Figure.h"
#include <string>

class FigureFactory
{
public:
    Figure* createFigure(const std::string& type, Point position);
    ~FigureFactory() {}
};