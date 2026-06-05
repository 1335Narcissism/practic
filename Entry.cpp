#include "Entry.h"

Entry::Entry(const std::string& entryName, Entry* parentEntry)
    : name(entryName), hidden(false), parent(parentEntry) {}

Entry::~Entry() {}

std::string Entry::getName() const {
    return name;
}

void Entry::setName(const std::string& newName) {
    name = newName;
}

bool Entry::isHidden() const {
    return hidden;
}

void Entry::setHidden(bool isHidden) {
    hidden = isHidden;
}

Entry* Entry::getParent() const {
    return parent;
}

bool Entry::isDirectory() const {
    return false;
}

void Entry::printContent() const {
    std::cout << "Cannot print content of this entry (unsupported type).\n";
}

void Entry::editContent() {
    std::cout << "Cannot edit this entry (unsupported type).\n";
}
