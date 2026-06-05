#ifndef MULTILINEFILE_H
#define MULTILINEFILE_H

#include "Entry.h"
#include <vector>
#include <string>

class MultiLineFile : public Entry {
private:
    std::vector<std::string> lines;

public:
    MultiLineFile(const std::string& name, Entry* parent);
    ~MultiLineFile() override;

    void printContent() const override;
    void editContent() override;
};

#endif // MULTILINEFILE_H
