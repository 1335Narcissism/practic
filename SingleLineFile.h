#ifndef SINGLELINEFILE_H
#define SINGLELINEFILE_H

#include "Entry.h"
#include <string>

class SingleLineFile : public Entry {
private:
    std::string content;

public:
    SingleLineFile(const std::string& name, Entry* parent);
    ~SingleLineFile() override;

    void printContent() const override;
    void editContent() override;
};

#endif // SINGLELINEFILE_H
