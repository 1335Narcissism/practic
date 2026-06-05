#include "Terminal.h"
#include "SingleLineFile.h"
#include "MultiLineFile.h"
#include <iostream>
#include <sstream>

Terminal::Terminal() : isRunning(true) {
    root = new Directory("/", nullptr);
    cwd = root;
}

Terminal::~Terminal() {
    delete root; // Automatically deletes all children recursively
}

std::vector<std::string> Terminal::splitCommand(const std::string& cmd) const {
    std::vector<std::string> tokens;
    std::stringstream ss(cmd);
    std::string token;
    while (ss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

std::string Terminal::getPrompt() const {
    std::string path = "";
    Entry* curr = cwd;
    while (curr != nullptr) {
        if (curr->getName() == "/") {
            path = "/" + path;
        } else {
            path = "/" + curr->getName() + path;
        }
        curr = curr->getParent();
    }
    if (path.length() > 1 && path.substr(0, 2) == "//") {
        path = path.substr(1);
    }
    return "terminal:" + path + "$ ";
}

void Terminal::run() {
    std::string line;
    std::cout << "Welcome to Virtual Terminal. Type 'help' for commands.\n";
    while (isRunning) {
        std::cout << getPrompt();
        if (!std::getline(std::cin, line)) {
            break; // EOF
        }

        std::vector<std::string> tokens = splitCommand(line);
        if (tokens.empty()) continue;

        std::string cmd = tokens[0];

        if (cmd == "help") {
            executeHelp();
        } else if (cmd == "exit") {
            executeExit();
        } else if (cmd == "ls") {
            executeLs();
        } else if (cmd == "cd") {
            if (tokens.size() > 1) executeCd(tokens[1]);
            else std::cout << "cd: missing argument\n";
        } else if (cmd == "cat") {
            if (tokens.size() > 1) executeCat(tokens[1]);
            else std::cout << "cat: missing argument\n";
        } else if (cmd == "touch") {
            if (tokens.size() > 1) {
                std::string type = (tokens.size() > 2) ? tokens[2] : "single";
                executeTouch(tokens[1], type);
            } else {
                std::cout << "touch: missing argument\n";
            }
        } else if (cmd == "mkdir") {
            if (tokens.size() > 1) executeMkdir(tokens[1]);
            else std::cout << "mkdir: missing argument\n";
        } else if (cmd == "rm") {
            if (tokens.size() > 1) executeRm(tokens[1]);
            else std::cout << "rm: missing argument\n";
        } else if (cmd == "restore") {
            if (tokens.size() > 1) executeRestore(tokens[1]);
            else std::cout << "restore: missing argument\n";
        } else if (cmd == "mv") {
            if (tokens.size() > 2) executeMv(tokens[1], tokens[2]);
            else std::cout << "mv: missing arguments\n";
        } else if (cmd == "edit") {
            if (tokens.size() > 1) executeEdit(tokens[1]);
            else std::cout << "edit: missing argument\n";
        } else {
            std::cout << cmd << ": command not found\n";
        }
    }
}

void Terminal::executeHelp() {
    std::cout << "Available commands:\n"
              << "  help             - show this message\n"
              << "  exit             - exit terminal\n"
              << "  ls               - list directory contents\n"
              << "  cd <dir>         - change directory (use .. to go up)\n"
              << "  cat <file>       - display file content\n"
              << "  touch <file> [single|multi] - create file\n"
              << "  mkdir <dir>      - create directory\n"
              << "  rm <name>        - hide entry\n"
              << "  restore <name>   - unhide entry\n"
              << "  mv <old> <new>   - rename entry\n"
              << "  edit <file>      - edit file content\n";
}

void Terminal::executeExit() {
    isRunning = false;
}

void Terminal::executeLs() {
    for (Entry* child : cwd->getChildren()) {
        if (!child->isHidden()) {
            std::cout << child->getName();
            if (child->isDirectory()) {
                std::cout << "/";
            }
            std::cout << "  ";
        }
    }
    std::cout << "\n";
}

void Terminal::executeCd(const std::string& name) {
    if (name == "..") {
        if (cwd->getParent() != nullptr) {
            // cwd is not root (since root's parent is nullptr)
            // Wait, we need to be careful with type casting.
            // cwd->getParent() returns Entry*. Since we only create directories as parents,
            // we can safely static_cast to Directory*.
            cwd = static_cast<Directory*>(cwd->getParent());
        }
    } else {
        Entry* e = cwd->findEntry(name);
        if (e && !e->isHidden()) {
            if (e->isDirectory()) {
                cwd = static_cast<Directory*>(e);
            } else {
                std::cout << "cd: " << name << ": Not a directory\n";
            }
        } else {
            std::cout << "cd: " << name << ": No such file or directory\n";
        }
    }
}

void Terminal::executeCat(const std::string& name) {
    Entry* e = cwd->findEntry(name);
    if (e && !e->isHidden()) {
        if (!e->isDirectory()) {
            e->printContent();
        } else {
            std::cout << "cat: " << name << ": Is a directory\n";
        }
    } else {
        std::cout << "cat: " << name << ": No such file or directory\n";
    }
}

void Terminal::executeTouch(const std::string& name, const std::string& type) {
    if (cwd->findEntry(name)) {
        std::cout << "touch: cannot create '" << name << "': File exists\n";
        return;
    }
    if (type == "multi") {
        cwd->addEntry(new MultiLineFile(name, cwd));
    } else {
        cwd->addEntry(new SingleLineFile(name, cwd));
    }
}

void Terminal::executeMkdir(const std::string& name) {
    if (cwd->findEntry(name)) {
        std::cout << "mkdir: cannot create directory '" << name << "': File exists\n";
        return;
    }
    cwd->addEntry(new Directory(name, cwd));
}

void Terminal::executeRm(const std::string& name) {
    Entry* e = cwd->findEntry(name);
    if (e && !e->isHidden()) {
        e->setHidden(true);
    } else {
        std::cout << "rm: cannot remove '" << name << "': No such file or directory\n";
    }
}

void Terminal::executeRestore(const std::string& name) {
    Entry* e = cwd->findEntry(name);
    if (e && e->isHidden()) {
        e->setHidden(false);
    } else if (e) {
        std::cout << "restore: '" << name << "' is not hidden\n";
    } else {
        std::cout << "restore: cannot find '" << name << "': No such file or directory\n";
    }
}

void Terminal::executeMv(const std::string& oldName, const std::string& newName) {
    Entry* e = cwd->findEntry(oldName);
    if (e && !e->isHidden()) {
        if (cwd->findEntry(newName)) {
            std::cout << "mv: cannot move to '" << newName << "': File exists\n";
        } else {
            e->setName(newName);
        }
    } else {
        std::cout << "mv: cannot rename '" << oldName << "': No such file or directory\n";
    }
}

void Terminal::executeEdit(const std::string& name) {
    Entry* e = cwd->findEntry(name);
    if (e && !e->isHidden()) {
        if (!e->isDirectory()) {
            e->editContent();
        } else {
            std::cout << "edit: " << name << ": Is a directory\n";
        }
    } else {
        std::cout << "edit: " << name << ": No such file or directory\n";
    }
}
