#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#define BUFMAX 5000

//USAGE::send code from python to c using pipe on command line

//This code takes in what is passed to it from the python function, and converts it into an array of arrays in the format:
//[1, 1, 3]
//number of block, peg from, peg to
//array literally contains [ and ] chars

std::vector<std::string> split_string(const std::string& str,
                                      const std::string& delimiter)
{
    std::vector<std::string> strings;

    std::string::size_type pos = 0;
    std::string::size_type prev = 0;
    while ((pos = str.find(delimiter, prev)) != std::string::npos)
    {
        strings.push_back(str.substr(prev, pos - prev));
        prev = pos + 1;
    }

    // To get the last substring (or only, if delimiter is not found)
    strings.push_back(str.substr(prev));

    return strings;
}

int main() {
    char buffer[BUFMAX + 1];
    char *bp = buffer;
    int c;
    FILE *in;
    while (EOF != (c = fgetc(stdin)) && (bp - buffer) < BUFMAX) {
        *bp++ = c;
    }
    *bp = 0;    // Null-terminate the string
    //printf("%s", buffer);
    auto strings = split_string(buffer, "\n");
    int i = 1;
    for (auto itr = strings.begin(); itr != strings.end(); itr++)
        std::cout << *itr << "\n";
    //printf(split_string(buffer, "\n"));
}
