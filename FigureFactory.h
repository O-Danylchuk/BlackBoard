#pragma once
#include "Figure.h"
#include <string>
#include <vector>
#include <memory>

class FigureFactory
{
public:
    void createFigure(Figure& figure, Figure::FigureType type, std::pair<int, int>& position);
    ~FigureFactory() {}
private:
    std::vector<std::unique_ptr<Figure>> figures;
};