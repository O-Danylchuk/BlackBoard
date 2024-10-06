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
    std::string fWord, figureType, filePath;
    int x, y, firstVal, secondVal;
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
            ss >> fWord >> figureType >> x >> y >> firstVal >> secondVal;
            std::pair<int, int> position = std::make_pair(x, y);
            Figure::FigureType type;
            if (figureType == "circle") {
                type = Figure::FigureType::Circle;
            } else if (figureType == "square") {
                type = Figure::FigureType::Square;
            } else if (figureType == "triangle") {
                type = Figure::FigureType::Triangle;
            } else {
                std::cout << "Invalid figure type" << std::endl;
                break;
            }
            std::unique_ptr<Figure> figure = figureFactory.createFigure(type, position, firstVal, secondVal);   
            board.addFigure(figure);
            board.drawFigure(type, position, firstVal, secondVal);
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