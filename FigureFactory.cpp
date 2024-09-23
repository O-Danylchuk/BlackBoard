#include "FigureFactory.h"
#include "Figure.h"
#include "Circle.h"
#include "Square.h"
#include "Triangle.h"
#include <memory> // For std::unique_ptr

std::unique_ptr<Figure> FigureFactory::createFigure(const std::string& type, Point position) {
    if (type == "Circle") {
        return std::make_unique<Circle>(position);
    } else if (type == "Square") {
        return std::make_unique<Square>(position);
    } else if (type == "Triangle") {
        return std::make_unique<Triangle>(position);
    } else { 
        throw std::invalid_argument("Unknown figure type");
    }
}
