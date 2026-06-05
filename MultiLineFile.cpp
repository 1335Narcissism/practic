#include "MultiLineFile.h"
#include <iostream>

MultiLineFile::MultiLineFile(const std::string& name, Entry* parent)
    : Entry(name, parent) {}

MultiLineFile::~MultiLineFile() {}

void MultiLineFile::printContent() const {
    for (const auto& line : lines) {
        std::cout << line << "\n";
    }
}

void MultiLineFile::editContent() {
    std::cout << "Editing MultiLineFile '" << name << "'.\n";
    std::cout << "Enter content (type ':wq' on a new line to save and exit):\n";
    
    lines.clear();
    std::string line;
    while (std::getline(std::cin, line)) {
        if (line == ":wq") {
            break;
        }
        lines.push_back(line);
    }
    
    if (!std::cin) {
        std::cin.clear();
    }
    std::cout << "File updated.\n";
}
