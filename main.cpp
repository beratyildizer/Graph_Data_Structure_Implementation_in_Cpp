/*
*
* Filename      : main.cpp
* Programmer(s) : Berat Yildizer
******************************************************************************/

#include <iostream>
#include <chrono>
#include "graph.h"


using namespace std;

int main()
{
    try {
        string s{ "dataset.txt" };

        auto i = get_instance(s);

        auto start = std::chrono::high_resolution_clock::now();
        auto j = graph_colouring(*i);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::micro> duration = end - start;
        std::cout << "Execution time: " << duration.count() << " microseconds." << std::endl;

        for (const auto& s : j) {
            std::cout << s.first << ". vertices color is " << s.second << std::endl;
        }


    }
    catch (const exception& x) {
        cout << x.what();
    }
 

    
}

