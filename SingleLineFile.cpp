#include "SingleLineFile.h"
#include <iostream>

SingleLineFile::SingleLineFile(const std::string& name, Entry* parent)
    : Entry(name, parent), content("") {}

SingleLineFile::~SingleLineFile() {}

void SingleLineFile::printContent() const {
    std::cout << content << "\n";
}

void SingleLineFile::editContent() {
    std::cout << "Editing SingleLineFile '" << name << "'. Enter new content (one line):\n> ";
    std::string line;
    if (std::getline(std::cin, line)) {
        content = line;
        std::cout << "File updated.\n";
    } else {
        // clear error state if cin fails
        std::cin.clear();
        std::cout << "Failed to read input.\n";
    }
}
