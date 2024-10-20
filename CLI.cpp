#include "CLI.h"
#include "BlackBoard.h"
#include "Figure.h"
#include "FigureFactory.h"
#include <iostream>
#include <utility>
#include <sstream>
BlackBoard board(30, 150);
FigureFactory figureFactory;

const std::unordered_map<std::string, CLI::Command> CLI::m_commandsMap = {
    {"draw", Command::draw},
    {"list", Command::list},
    {"move", Command::move},
    {"select", Command::select},
    {"edit", Command::edit},
    {"paint", Command::paint},
    {"shapes", Command::shapes},
    {"add", Command::add},
    {"undo", Command::undo},
    {"clear", Command::clear},
    {"save", Command::save},
    {"load", Command::load},
    {"help", Command::help},
    {"clear", Command::clear},
    {"clearBoard", Command::clearBoard}
};

CLI::Command CLI::parseCommand(const std::string& commandStr) {
    auto it = m_commandsMap.find(commandStr);
    if (it != m_commandsMap.end()) {
        return it->second;
    } else {
        return Command::invalid;
    }
}

void CLI::executeCommand(const CLI::Command& command) {
    std::stringstream ss(m_userInput);
    std::string fWord, type, filePath, color;
    int x, y, firstVal, secondVal, ID;
    switch (command) {        
        case Command::draw:
        {
            system("clear");
            board.display();
            break;
        }
        case Command::list:
        {
            board.listFigures();
            break;
        }
        case Command::shapes:
        {
            for (const auto& shape : figureFactory.getSupportedShapes()) {
                std::cout << shape << std::endl;
            }
            break;
        }
        case Command::add: 
        {
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
            board.addFigure(std::move(figure));
            board.drawFigure(figureType, figureColor, position, firstVal, secondVal);
            break;
        }            
        case Command::undo:
        {
            board.undoLastFigure();
            break;
        }
        case Command::clear:
        {
            system("clear");
            break;
        }
        case Command::clearBoard:
        {
            board.clearBoard();
            break;
        }
        case Command::save:
        {
            ss >> fWord >> filePath;
            board.save(filePath);
            break;
        }
        case Command::load:
        {
            ss >> fWord >> filePath;
            board.load(filePath);
            break;
        }
        case Command::help:
        {
            help();
            break;
        }
        case Command::move:
        {
            ss >> fWord >> ID >> x >> y;
            board.moveFigure(ID, x, y);
            break;
        }
        case Command::select:
        {
            ss >> fWord >> ID;
            board.showSelected(ID);
            break;
        }
        default:
        {
            std::cout << "Invalid command" << std::endl;
            break;
        }
    }
}
void CLI::help() {
    std::cout << "Available methods:\ndraw -> draws blackboard to the console\nlist -> shows all added shapes and their parameters\nshapes -> shows all supported figures with needed params\nadd -> adds cpecified figure to the blackboard\nundo -> remofe last added figure\nclear -> clear the console\nclearBoard -> remove all figures from the board\nsave <file path> -> state of blackboard is saved to file with cpecivied location\nload -> load state of blackboard to file\n" << std::endl;
}

void CLI::run() {
    std::getline(std::cin, m_userInput);
    std::string fWord = m_userInput.substr(0, m_userInput.find(' '));
    while (fWord != "exit") {
        Command command = parseCommand(fWord);
        if (command == Command::invalid) {
            std::cout << "Invalid command" << std::endl;
            std::getline(std::cin, m_userInput);
            fWord = m_userInput.substr(0, m_userInput.find(' '));
            system("clear");
            continue;
        }
        executeCommand(command);
        std::getline(std::cin, m_userInput);
        fWord = m_userInput.substr(0, m_userInput.find(' '));
    }
    std::cout << "Exiting..." << std::endl; 
}