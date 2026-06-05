#ifndef TERMINAL_H
#define TERMINAL_H

#include "Directory.h"
#include <string>
#include <vector>

class Terminal {
private:
    Directory* root;
    Directory* cwd;
    bool isRunning;

    std::vector<std::string> splitCommand(const std::string& cmd) const;
    std::string getPrompt() const;

    void executeHelp();
    void executeExit();
    void executeLs();
    void executeCd(const std::string& name);
    void executeCat(const std::string& name);
    void executeTouch(const std::string& name, const std::string& type);
    void executeMkdir(const std::string& name);
    void executeRm(const std::string& name);
    void executeRestore(const std::string& name);
    void executeMv(const std::string& oldName, const std::string& newName);
    void executeEdit(const std::string& name);

public:
    Terminal();
    ~Terminal();

    void run();
};

#endif // TERMINAL_H
