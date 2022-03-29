#ifndef CONSOLE_H
#define CONSOLE_H

class Console
{
    public:
    Console();

    virtual ~Console() = default;

    void runEventLoop(bool&);

    private:
};

#endif /* CONSOLE_H */