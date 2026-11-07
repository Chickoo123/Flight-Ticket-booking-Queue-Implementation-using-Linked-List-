// input.hpp - defensive console input helpers.
// Plain `cin >> int` loops forever on non-numeric input and on EOF; these don't.
#pragma once

#include <iostream>
#include <limits>
#include <optional>
#include <string>

// Reads an int in [lo, hi]. Re-prompts on bad input; returns nullopt on EOF.
inline std::optional<int> read_int(const std::string& prompt, int lo, int hi) {
    while (true) {
        std::cout << prompt;
        int value;
        if (std::cin >> value) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (value >= lo && value <= hi) return value;
            std::cout << "Please enter a number between " << lo << " and " << hi << ".\n";
            continue;
        }
        if (std::cin.eof()) return std::nullopt;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "That is not a number. Try again.\n";
    }
}

// Reads a non-blank line (trimmed). Returns nullopt on EOF.
inline std::optional<std::string> read_line(const std::string& prompt) {
    std::string line;
    while (true) {
        std::cout << prompt;
        if (!std::getline(std::cin, line)) return std::nullopt;
        const auto first = line.find_first_not_of(" \t\r");
        if (first == std::string::npos) {
            std::cout << "Value cannot be empty.\n";
            continue;
        }
        const auto last = line.find_last_not_of(" \t\r");
        return line.substr(first, last - first + 1);
    }
}
