#include "Directory.h"
#include <iostream>
#include <algorithm>

Directory::Directory(const std::string& name, Entry* parent)
    : Entry(name, parent) {}

Directory::~Directory() {
    for (Entry* child : children) {
        delete child;
    }
    children.clear();
}

bool Directory::isDirectory() const {
    return true;
}

void Directory::addEntry(Entry* entry) {
    if (entry) {
        children.push_back(entry);
    }
}

void Directory::removeEntry(Entry* entry) {
    auto it = std::find(children.begin(), children.end(), entry);
    if (it != children.end()) {
        children.erase(it);
    }
}

Entry* Directory::findEntry(const std::string& entryName) const {
    for (Entry* child : children) {
        if (child->getName() == entryName) {
            return child;
        }
    }
    return nullptr;
}

const std::vector<Entry*>& Directory::getChildren() const {
    return children;
}

void Directory::printContent() const {
    std::cout << "This is a directory. Use 'ls' to list its contents.\n";
}

void Directory::editContent() {
    std::cout << "Cannot edit a directory.\n";
}
