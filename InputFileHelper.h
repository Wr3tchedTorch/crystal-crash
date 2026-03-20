#pragma once
#include <fstream>
#include <ios>

class InputFileHelper
{
public:
    static bool is_empty(std::ifstream& pFile)
    {
        return pFile.peek() == std::ifstream::traits_type::eof();
    }
};