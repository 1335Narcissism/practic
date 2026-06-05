#ifndef ENTRY_H
#define ENTRY_H

#include <string>
#include <iostream>

class Entry {
protected:
    std::string name;
    bool hidden;
    Entry* parent;

public:
    Entry(const std::string& entryName, Entry* parentEntry);
    virtual ~Entry();

    virtual std::string getName() const;
    virtual void setName(const std::string& newName);

    virtual bool isHidden() const;
    virtual void setHidden(bool isHidden);

    virtual Entry* getParent() const;

    virtual bool isDirectory() const;

    // Polymorphic methods (with default implementations as abstract classes are forbidden)
    virtual void printContent() const;
    virtual void editContent();
};

#endif // ENTRY_H
