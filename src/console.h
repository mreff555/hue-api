#ifndef CONSOLE_H
#define CONSOLE_H

class Console
{
    public:
    Console();

    virtual ~Console() = default;

    /**
     * @brief Starts the event looop
     * @param boolean terminate value.  Call should exist within one iteration of loop.
     */
    void runEventLoop(bool&);

    private:
};

#endif /* CONSOLE_H */