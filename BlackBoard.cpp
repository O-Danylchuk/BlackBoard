#include "BlackBoard.h"
#include <iostream>

BlackBoard::BlackBoard(int height, int width) : m_height(height), m_width(width) {
    m_board = new char*[m_height];
    for (int i = 0; i < m_height; ++i) {
        m_board[i] = new char[m_width];
        for (int j = 0; j < m_width; ++j) {
            m_board[i][j] = ' ';
        }
    }
}

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

BlackBoard::~BlackBoard() {
    for (int i = 0; i < m_height; ++i) {
        delete[] m_board[i];
    }
    delete[] m_board;
}

void BlackBoard::clearBoard() {
    for (int i = 0; i < m_height; ++i) {
        for (int j = 0; j < m_width; ++j) {
            m_board[i][j] = ' ';
        }
    }
}