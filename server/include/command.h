#ifndef COMMAND_H
#define COMMAND_h

class Command {
    virtual void execute(const std::string& args) = 0; 
    virtual ~Command() {}
};


#endif
