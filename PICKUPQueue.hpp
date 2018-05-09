#include <iostream>

#include "Queue.hpp"
#include "FCFSQueueNode.hpp"

// Forward Decleration
class Request;

class PICKUPQueue: public Queue {

public:
    PICKUPQueue(): head(nullptr), tail(nullptr) {}

    virtual void addRequest(Request *request);
    virtual FCFSQueueNode *getHead();
    virtual Request *getRequest();
    virtual bool isEmpty();
    virtual void print();
    virtual ~PICKUPQueue();

private:
    FCFSQueueNode *head, *tail;
};
