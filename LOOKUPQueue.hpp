#include <iostream>

#include "Queue.hpp"
#include "FCFSQueueNode.hpp"

// Forward Decleration
class Request;

class LOOKUPQueue: public Queue {

public:
    LOOKUPQueue(): head(nullptr), tail(nullptr) {}

    virtual void addRequest(Request *request);
    virtual FCFSQueueNode *getHead();
    virtual Request *getRequest();
    virtual bool isEmpty();
    virtual void print();
    virtual ~LOOKUPQueue();

private:
    FCFSQueueNode *head, *tail;
};
