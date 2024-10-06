#include "BlackBoard.h"
#include <iostream>
#include "Circle.h"
#include "Square.h"
#include "Triangle.h"
#include <fstream>


BlackBoard::BlackBoard(int height, int width) : m_height(height), m_width(width), m_board(height, std::vector<char>(width, ' ')) {}

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

void BlackBoard::drawFigure(Figure::FigureType type, std::pair<int, int>& position, int firstVal, int secondVal) {
    if (position.first < 0 || position.first >= m_width || position.second < 0 || position.second >= m_height) {
        std::cout << "Invalid position" << std::endl;
        return;
    }
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
                        m_board[drawY][drawX] = 'O';
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
                    m_board[drawY][drawX] = 'X';
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
                    m_board[drawY][drawX] = 'X';
                }
            }
            std::cout << std::endl;
        }
    } else if (type == Figure::FigureType::Line) {
        int length = firstVal;
        int startX = position.first;
        int startY = position.second;
        for (int x = 0; x < length; ++x) {
            int drawX = startX + x;
            int drawY = startY;
            if (drawX >= 0 && drawX < m_width && drawY >= 0 && drawY < m_height) {
                m_board[drawY][drawX] = '*';
            }
        }
    } else {
        std::cout << "Invalid figure type (this should never happen )" << std::endl;
    }
}

void BlackBoard::addFigure(std::unique_ptr<Figure>& figure){
    m_figures.push_back(std::move(figure));
}

void BlackBoard::clearBoard() {
    for (auto& row : m_board) {
        std::fill(row.begin(), row.end(), ' ');
    }
}

void BlackBoard::listFigures() {
    for (const auto& figure : m_figures) {
        switch (figure->type) {
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
            if (figure->type == Figure::FigureType::Circle) {
                Circle* circle = dynamic_cast<Circle*>(figure.get());
                std::pair<int, int> position = circle->getPosition();
                drawFigure(figure->type, position, circle->getRadius(), 0);
            } else if (figure->type == Figure::FigureType::Square) {
                Square* square = dynamic_cast<Square*>(figure.get());
                std::pair<int, int> position = square->getPosition();
                drawFigure(figure->type, position, square->getHeight(), square->getWidth());
            } else if (figure->type == Figure::FigureType::Triangle) {
                Triangle* triangle = dynamic_cast<Triangle*>(figure.get());
                std::pair<int, int> position = triangle->getPosition();
                drawFigure(figure->type, position, triangle->getHeight(), 0);
            }
        }
    }
}

void BlackBoard::save(const std::string& filePath) {
    std::ofstream file(filePath);
    if (file.is_open()) {
        for (int i = 0; i < m_height; ++i) {
            for (int j = 0; j < m_width; ++j) {
                file << m_board[i][j];
            }
            file << std::endl;
        }
        file.close();
    } else {
        std::cout << "Unable to open file" << std::endl;
    }
}

void BlackBoard::load(const std::string& filePath) {
    clearBoard();
    std::ifstream file(filePath);
    if (file.is_open()) {
        std::string line;
        int i = 0;
        while (std::getline(file, line)) {
            if (i < m_height) {
                for (int j = 0; j < m_width; ++j) {
                    m_board[i][j] = line[j];
                }
                ++i;
            } else {
                break;
            }
        }
        file.close();
    } else {
        std::cout << "Unable to open file" << std::endl;
    }
}