#include <iostream>
#include <string>
#include <vector>
#include <sstream>

int main() {
    int rows;
    int cols;

    std::string line;

    getline(std::cin, line);
    rows = std::stoi(line);

    getline(std::cin, line);
    cols = std::stoi(line);

    std::vector<std::vector<int>> result;
    result.resize(cols);


    for (int i = 0; i < cols; ++i) {
        std::vector<int> xx;
        xx.resize(rows);

        result[i] = xx;
    }

    for (int i = 0; i < rows; ++i) {
        getline(std::cin, line);
        std::istringstream iss(line);

        for (int j = 0 ; j < cols; ++j) {
            iss >> result[j][i];
        }
    }
    

    for (int i = 0; i < cols; ++i) {
        for (int j = 0 ; j < rows; ++j) {
            if (j > 0) {
                std::cout <<' ';
            }
            std::cout << result[i][j];
        }
        std::cout << '\n';
    }

    return 0;
}