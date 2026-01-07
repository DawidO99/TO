#ifndef IUSER_INTERFACE_H
#define IUSER_INTERFACE_H

class IUserInterface {
public:
    virtual ~IUserInterface() = default;
    virtual void run() = 0;
};

#endif // IUSER_INTERFACE_H
