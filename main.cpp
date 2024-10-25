#include <iostream>
#include <fstream>
#include "nlohmann/json.hpp"
#include <vector>
#include <cmath>

using json = nlohmann::json;

// Function to convert a string from any base to decimal (long long)
long long convertToDecimal(const std::string& value, int base) {
    return std::stoll(value, nullptr, base);
}

// Function to perform Lagrange Interpolation and find constant term (c)
long long lagrangeInterpolation(const std::vector<std::pair<int, long long>>& points, int k) {
    long long result = 0;
    
    for (int i = 0; i < k; ++i) {
        long long term = points[i].second;
        for (int j = 0; j < k; ++j) {
            if (i != j) {
                term *= (0 - points[j].first); // Numerator
                term /= (points[i].first - points[j].first); // Denominator
            }
        }
        result += term;
    }
    
    return result;
}

int main() {
    // Load JSON from file
    std::ifstream inputFile("input.json");
    json inputData;
    inputFile >> inputData;
    
    // Extract n and k
    int n = inputData["keys"]["n"];
    int k = inputData["keys"]["k"];
    
    // Store the points (x, y)
    std::vector<std::pair<int, long long>> points;
    
    for (auto& el : inputData.items()) {
        if (el.key() != "keys") {
            int x = std::stoi(el.key()); // 'x' is the key
            int base = std::stoi(el.value()["base"].get<std::string>());
            std::string value = el.value()["value"];
            
            // Convert the 'y' value from the given base to decimal
            long long y = convertToDecimal(value, base);
            
            // Add the point (x, y) to the list
            points.push_back({x, y});
        }
    }
    
    // Apply Lagrange Interpolation to find the constant term (c)
    long long secret = lagrangeInterpolation(points, k);
    
    // Output the result
    std::cout << "Secret (c) is: " << secret << std::endl;
    
    return 0;
}