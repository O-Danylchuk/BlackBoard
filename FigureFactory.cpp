#include "FigureFactory.h"
#include <iostream>
#include "Figure.h"
#include "Circle.h"
#include "Square.h"
#include "Triangle.h"
#include <stdexcept>
#include <memory>
#include <utility>
#include <iostream>

std::unique_ptr<Figure> FigureFactory::createFigure(Figure::FigureType type, std::pair<int, int>& position, int firstVal, int secondVal) {
    switch (type) {
        case Figure::FigureType::Circle:
            return std::make_unique<Circle>(position, firstVal);
        case Figure::FigureType::Square:
            return std::make_unique<Square>(position, firstVal);
        case Figure::FigureType::Triangle:
            return std::make_unique<Triangle>(position, firstVal, secondVal);  
        default:
            throw std::invalid_argument("Invalid figure type");
    }
}