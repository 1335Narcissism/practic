#ifndef DIRECTORY_H
#define DIRECTORY_H

#include "Entry.h"
#include <vector>
#include <string>

class Directory : public Entry {
private:
    std::vector<Entry*> children;

public:
    Directory(const std::string& name, Entry* parent);
    ~Directory() override;

    bool isDirectory() const override;

    void addEntry(Entry* entry);
    void removeEntry(Entry* entry);
    Entry* findEntry(const std::string& entryName) const;
    const std::vector<Entry*>& getChildren() const;

    // A directory does not support direct edit or print content in the same way files do.
    // However, ls command inside Terminal will print its contents.
    void printContent() const override;
    void editContent() override;
};

#endif // DIRECTORY_H
