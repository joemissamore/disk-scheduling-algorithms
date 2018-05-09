#include <iostream>

#include "Queue.hpp"
#include "FCFSQueueNode.hpp"

// Forward Decleration
class Request;

class FCFSQueue: public Queue {

public:
    FCFSQueue(): head(nullptr), tail(nullptr) {}

    virtual void addRequest(Request *request);

    virtual FCFSQueueNode *getHead();

    virtual Request *getRequest();
    virtual bool isEmpty();
    virtual void print();
    virtual ~FCFSQueue();

private:
    FCFSQueueNode *head, *tail;
};
