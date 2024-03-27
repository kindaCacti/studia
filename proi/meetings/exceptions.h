#pragma once
#include <iostream>
#include <string>

class IncorrectDate :public std::exception{
    private:
        std::string message;

    public:
        IncorrectDate(std::string msg) : message(msg) {}
        void write () {
            std::cout << message << std::endl;
        }
};