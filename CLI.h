#pragma once
#include <iostream>
#include <unordered_map>

class CLI 
{
public:
    void run();
    void help();
    ~CLI() {}
private:
    std::string m_userInput;
    
    enum class Command
    {
        draw,
        list,
        shapes,
        add,
        undo,
        clear,
        move,
        select,
        edit,
        paint,
        clearBoard,
        save,
        load,
        help,
        invalid
    };

    static const std::unordered_map<std::string, Command> m_commandsMap;

    Command parseCommand(const std::string& commandStr);
    void executeCommand(const Command& command);
};