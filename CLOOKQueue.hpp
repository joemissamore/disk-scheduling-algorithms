#include <iostream>

#include "Queue.hpp"
#include "FCFSQueueNode.hpp"

// Forward Decleration
class Request;

class CLOOKQueue: public Queue {

public:
    CLOOKQueue(): head(nullptr), tail(nullptr) {}

    virtual void addRequest(Request *request);
    virtual FCFSQueueNode *getHead();
    virtual Request *getRequest();
    virtual bool isEmpty();
    virtual void print();
    virtual ~CLOOKQueue();

private:
    FCFSQueueNode *head, *tail;
};
