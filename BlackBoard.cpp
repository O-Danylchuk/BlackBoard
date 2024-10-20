#include "BlackBoard.h"
#include <iostream>
#include "Circle.h"
#include "Square.h"
#include "Triangle.h"
#include "Line.h"
#include <fstream>
#include <sstream>
#include "CLI.h"
#include "FigureFactory.h"


BlackBoard::BlackBoard(int height, int width) : m_height(height), m_width(width), m_board(height, std::vector<char>(width, ' ')) {
}

BlackBoard::~BlackBoard() {}

void BlackBoard::display() const {
    std::cout << "+";
    for (int i = 0; i < m_width; ++i) {
        std::cout << "-";
    }
    std::cout << "+" << std::endl;

    for (int i = 0; i < m_height; ++i) {
        std::cout << "|";
        for (int j = 0; j < m_width; ++j) {
            std::cout << m_board[i][j];
        }
        std::cout << "|" << std::endl;
    }

    std::cout << "+";
    for (int i = 0; i < m_width; ++i) {
        std::cout << "-";
    }
    std::cout << "+" << std::endl;
}

void BlackBoard::showSelected(int ID) {
    for (const auto& figure : m_figures) {
        if (figure->getId() == ID) {
            switch (figure->m_type) {
                case Figure::FigureType::Circle: {
                    Circle* circle = dynamic_cast<Circle*>(figure.get());
                    if (circle) {
                        std::cout << "Circle: Position (" << circle->getPosition().first << ", " << circle->getPosition().second 
                                << "), Radius: " << circle->getRadius() << std::endl;
                    }
                    break;
                }
                case Figure::FigureType::Square: {
                    Square* square = dynamic_cast<Square*>(figure.get());
                    if (square) {
                        std::cout << "Square: Position (" << square->getPosition().first << ", " << square->getPosition().second 
                                << "), Width: " << square->getWidth() << ", Height: " << square->getHeight() << std::endl;
                    }
                    break;
                }
                case Figure::FigureType::Triangle: {
                    Triangle* triangle = dynamic_cast<Triangle*>(figure.get());
                    if (triangle) {
                        std::cout << "Triangle: Position (" << triangle->getPosition().first << ", " << triangle->getPosition().second 
                                << ")" << ", Height: " << triangle->getHeight() << std::endl;
                    }
                    break;
                }
                case Figure::FigureType::Line: {
                    Line* line = dynamic_cast<Line*>(figure.get());
                    if (line) {
                        std::cout << "Line: Position (" << line->getPosition().first << ", " << line->getPosition().second 
                                << ")" << ", Length: " << line->getLength() << std::endl;
                    }
                    break;
                }
                default:
                    std::cout << "No figure with this ID" << std::endl;
                    break;
            }
        }
    }
}
char chooseColor(Figure::Color color) {
    switch (color) {
        case Figure::Color::Red:
            return 'R';
        case Figure::Color::Green:
            return 'G';
        case Figure::Color::Blue:
            return 'B';
        case Figure::Color::Yellow:
            return 'Y';
        case Figure::Color::Magenta:
            return 'M';
        case Figure::Color::Cyan:
            return 'C';
        case Figure::Color::White:
            return 'W';
        default:
            return ' ';
    }
}

void BlackBoard::drawFigure(Figure::FigureType type, Figure::Color color, std::pair<int, int>& position, int firstVal, int secondVal) {
    if (position.first < 0 || position.first >= m_width || position.second < 0 || position.second >= m_height) {
        std::cout << "Invalid position" << std::endl;
        return;
    }

    char colorChar = chooseColor(color);

    if (type == Figure::FigureType::Circle) {
        int radius = firstVal;
        if (radius <= 0 || radius > m_width || radius > m_height) {
            std::cout << "Invalid radius" << std::endl;
            return;
        }
        int centerX = position.first;
        int centerY = position.second;

        for (int y = -radius; y <= radius; ++y) {
            for (int x = -radius; x <= radius; ++x) {
                if (x * x + y * y <= radius * radius) {
                    int drawX = centerX + x;
                    int drawY = centerY + y;
                    if (drawX >= 0 && drawX < m_width && drawY >= 0 && drawY < m_height) {
                        m_board[drawY][drawX] = colorChar;
                    }
                }
            }
        }
    } else if (type == Figure::FigureType::Square) {
        int height = firstVal;
        int width = secondVal;
        int startX = position.first;
        int startY = position.second;

        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                int drawX = startX + x;
                int drawY = startY + y;
                if (drawX >= 0 && drawX < m_width && drawY >= 0 && drawY < m_height) {
                    m_board[drawY][drawX] = colorChar;
                }
            }
        }
    } else if (type == Figure::FigureType::Triangle) {
        int height = firstVal;
        int startX = position.first;
        int startY = position.second;
        for (int x = 1; x <= height; ++x) {
            for (int y = 0; y < x; ++y) {
                int drawX = startX + x;
                int drawY = startY + y;
                if (drawX >= 0 && drawX < m_width && drawY >= 0 && drawY < m_height) {
                    m_board[drawY][drawX] = colorChar;
                }
            }
        }
    } else if (type == Figure::FigureType::Line) {
        int length = firstVal;
        int startX = position.first;
        int startY = position.second;
        for (int x = 0; x < length; ++x) {
            int drawX = startX + x;
            int drawY = startY;
            if (drawX >= 0 && drawX < m_width && drawY >= 0 && drawY < m_height) {
                m_board[drawY][drawX] = colorChar;
            }
        }
    } else {
        std::cout << "Invalid figure type (this should never happen )" << std::endl;
    }
}

void BlackBoard::addFigure(std::unique_ptr<Figure> figure){
    for (const auto& f : m_figures) {
        if (f->m_type == figure->m_type) {
            switch (f->m_type) {
                case Figure::FigureType::Circle: {
                    Circle* circle = dynamic_cast<Circle*>(f.get());
                    Circle* newCircle = dynamic_cast<Circle*>(figure.get());
                    if (circle && newCircle) {
                        if (circle->getPosition() == newCircle->getPosition()) {
                            std::cout << "Position already occupied by a circle" << std::endl;
                            return;
                        }
                    }
                    break;
                }
                case Figure::FigureType::Square: {
                    Square* square = dynamic_cast<Square*>(f.get());
                    Square* newSquare = dynamic_cast<Square*>(figure.get());
                    if (square && newSquare) {
                        if (square->getPosition() == newSquare->getPosition()) {
                            std::cout << "Position already occupied by a square" << std::endl;
                            return;
                        }
                    }
                    break;
                }
                case Figure::FigureType::Triangle: {
                    Triangle* triangle = dynamic_cast<Triangle*>(f.get());
                    Triangle* newTriangle = dynamic_cast<Triangle*>(figure.get());
                    if (triangle && newTriangle) {
                        if (triangle->getPosition() == newTriangle->getPosition()) {
                            std::cout << "Position already occupied by a triangle" << std::endl;
                            return;
                        }
                    }
                    break;
                }
                case Figure::FigureType::Line: {
                    Line* line = dynamic_cast<Line*>(f.get());
                    Line* newLine = dynamic_cast<Line*>(figure.get());
                    if (line && newLine) {
                        if (line->getPosition() == newLine->getPosition()) {
                            std::cout << "Position already occupied by a line" << std::endl;
                            return;
                        }
                    }
                    break;
                }
                default:
                    break;
            }
        }
    }
    m_figures.push_back(std::move(figure));
}

void BlackBoard::clearBoard() {
    for (auto& row : m_board) {
        std::fill(row.begin(), row.end(), ' ');
    }
}

void BlackBoard::listFigures() {
    for (const auto& figure : m_figures) {
        switch (figure->m_type) {
            case Figure::FigureType::Circle: {
                Circle* circle = dynamic_cast<Circle*>(figure.get());
                if (circle) {
                    std::cout << "Circle: Position (" << circle->getPosition().first << ", " << circle->getPosition().second 
                              << "), Radius: " << circle->getRadius() << ", ID: " << circle->getId() << std::endl;
                }
                break;
            }
            case Figure::FigureType::Square: {
                Square* square = dynamic_cast<Square*>(figure.get());
                if (square) {
                    std::cout << "Square: Position (" << square->getPosition().first << ", " << square->getPosition().second 
                              << "), Width: " << square->getWidth() << ", Height: " << square->getHeight()
                              << ", ID: " << square->getId() << std::endl;
                }
                break;
            }
            case Figure::FigureType::Triangle: {
                Triangle* triangle = dynamic_cast<Triangle*>(figure.get());
                if (triangle) {
                    std::cout << "Triangle: Position (" << triangle->getPosition().first << ", " << triangle->getPosition().second 
                              << ")" << ", Height: " << triangle->getHeight() 
                              << ", ID: " << triangle->getId() << std::endl;
                }
                break;
            }
            case Figure::FigureType::Line: {
                Line* line = dynamic_cast<Line*>(figure.get());
                if (line) {
                    std::cout << "Line: Position (" << line->getPosition().first << ", " << line->getPosition().second 
                              << ")" << ", Length: " << line->getLength() 
                              << ",ID: " << line->getId() << std::endl;
                }
                break;
            }
            default:
                break;
        }
    }
}

void BlackBoard::undoLastFigure() {
    if (!m_figures.empty()) {
        m_figures.pop_back();
        clearBoard();
        for (const auto& figure : m_figures) {
            if (figure->m_type == Figure::FigureType::Circle) {
                Circle* circle = dynamic_cast<Circle*>(figure.get());
                std::pair<int, int> position = circle->getPosition();
                drawFigure(figure->m_type, figure->m_color, position, circle->getRadius(), 0);
            } else if (figure->m_type == Figure::FigureType::Square) {
                Square* square = dynamic_cast<Square*>(figure.get());
                std::pair<int, int> position = square->getPosition();
                drawFigure(figure->m_type, figure->m_color, position, square->getHeight(), square->getWidth());
            } else if (figure->m_type == Figure::FigureType::Triangle) {
                Triangle* triangle = dynamic_cast<Triangle*>(figure.get());
                std::pair<int, int> position = triangle->getPosition();
                drawFigure(figure->m_type, figure->m_color, position, triangle->getHeight(), 0);
            }
        }
    }
}

void BlackBoard::save(const std::string& filePath) {
    std::ofstream file(filePath);
    if (!file.is_open()) {
        std::cout << "Unable to open file" << std::endl;
        return;
    }
    for (const auto& figure : m_figures) {
        switch (figure->m_type) {
            case Figure::FigureType::Circle: {
                Circle* circle = dynamic_cast<Circle*>(figure.get());
                if (circle) {
                    std::ofstream file(filePath, std::ios::app);
                    file << "add " << circle->getColor() << " circle " << circle->getPosition().first <<  " " << circle->getPosition().second 
                         << " " << circle->getRadius() << std::endl;
                }
                break;
            }
            case Figure::FigureType::Square: {
                Square* square = dynamic_cast<Square*>(figure.get());
                if (square) {
                    std::ofstream file(filePath, std::ios::app);
                    file << "add " << square->getColor() << " square " << square->getPosition().first <<  " " << square->getPosition().second 
                         << " " << square->getHeight() << std::endl;
                }
                break;
            }
            case Figure::FigureType::Triangle: {
                Triangle* triangle = dynamic_cast<Triangle*>(figure.get());
                if (triangle) {
                    std::ofstream file(filePath, std::ios::app);
                    file << "add " << triangle->getColor() << " triangle " << triangle->getPosition().first <<  " " << triangle->getPosition().second 
                         << " " << triangle->getBase() << std::endl;
                }
                break;
            }
            case Figure::FigureType::Line: {
                Line* line = dynamic_cast<Line*>(figure.get());
                if (line) {
                    std::ofstream file(filePath, std::ios::app);
                    file << "add" << line->getColor() << " line " << line->getPosition().first <<  " " << line->getPosition().second 
                         << " " << line->getLength() << std::endl;
                }
                break;
            }
            default:
                break;
        }
    }
    file.close();
}

void BlackBoard::moveFigure(int ID, int x, int y) {
    clearBoard();
    for (const auto& f : m_figures) {
        if (f->m_type == Figure::FigureType::Circle) {
            Circle* circle = dynamic_cast<Circle*>(f.get());
            if (circle->getId() == ID){
                circle->move(x, y);
                std::pair<int, int> position = circle->getPosition();
                drawFigure(f->m_type, f->m_color, position, circle->getRadius(), 0);
                continue;
            }
            std::pair<int, int> position = circle->getPosition();
            drawFigure(f->m_type, f->m_color, position, circle->getRadius(), 0);
        } else if (f->m_type == Figure::FigureType::Square) {
            Square* square = dynamic_cast<Square*>(f.get());
            if (square->getId() == ID) {
                square->move(x, y);
                std::pair<int, int> position = square->getPosition();
                drawFigure(f->m_type, f->m_color, position, square->getHeight(), square->getWidth());
                continue;
            }
            std::pair<int, int> position = square->getPosition();
            drawFigure(f->m_type, f->m_color, position, square->getHeight(), square->getWidth());
        } else if (f->m_type == Figure::FigureType::Triangle) {
            Triangle* triangle = dynamic_cast<Triangle*>(f.get());
            if (triangle->getId() == ID) {
                triangle->move(x, y);
                std::pair<int, int> position = triangle->getPosition();
                drawFigure(f->m_type, f->m_color, position, triangle->getBase(), 0);
                continue;
            }
            std::pair<int, int> position = triangle->getPosition();
            drawFigure(f->m_type, f->m_color, position, triangle->getHeight(), 0);
        } else if (f->m_type == Figure::FigureType::Line) {
            Line* line = dynamic_cast<Line*>(f.get());
            if (line->getId() == ID) {
                line->move(x, y);
                std::pair<int, int> position = line->getPosition();
                drawFigure(f->m_type, f->m_color, position, line->getLength(), 0);
                continue;;
            }
            std::pair<int, int> position = line->getPosition();
            drawFigure(f->m_type, f->m_color, position, line->getLength(), 0);
        }
    }
}

void BlackBoard::load(const std::string& filePath) {
    clearBoard();
    for (auto& figure : m_figures) {
        m_figures.pop_back();
    }
    
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cout << "Unable to open file" << std::endl;
        return;
    }
    std::string line;
    int i = 0;
    std::string fWord, type, color;
    int x, y, firstVal, secondVal, ID;
    FigureFactory figureFactory;
    figureFactory.resetID();
    bool isValid = true;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        ss >> fWord >> color >> type >> x >> y >> firstVal >> secondVal;
            std::pair<int, int> position = std::make_pair(x, y);
            Figure::FigureType figureType;
            Figure::Color figureColor;
            if (type == "circle") {
                figureType = Figure::FigureType::Circle;
            } else if (type == "square") {
                figureType = Figure::FigureType::Square;
            } else if (type == "triangle") {
                figureType = Figure::FigureType::Triangle;
            } else if (type == "line") {
                figureType = Figure::FigureType::Line;
            } else {
                std::cout << "Invalid figure type" << std::endl;
                break;
            }
            if (color == "red") {
                figureColor = Figure::Color::Red;
            } else if (color == "green") {
                figureColor = Figure::Color::Green;
            } else if (color == "blue") {
                figureColor = Figure::Color::Blue;
            } else if (color == "yellow") {
                figureColor = Figure::Color::Yellow;
            } else if (color == "magenta") {
                figureColor = Figure::Color::Magenta;
            } else if (color == "cyan") {
                figureColor = Figure::Color::Cyan;
            } else if (color == "white") {
                figureColor = Figure::Color::White;
            } else {
                std::cout << "Invalid color" << std::endl;
                break;
            }
            std::unique_ptr<Figure> figure = figureFactory.createFigure(figureType, figureColor, position, firstVal, secondVal);  
            this->addFigure(std::move(figure));
            this->drawFigure(figureType, figureColor, position, firstVal, secondVal);
            continue;
        
    }
}