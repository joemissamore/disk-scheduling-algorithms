#include <iostream>

#include "Queue.hpp"
#include "FCFSQueueNode.hpp"

// Forward Decleration
class Request;

class STRACKQueue: public Queue {

public:
    STRACKQueue(): head(nullptr), tail(nullptr) {}

    virtual void addRequest(Request *request);
    virtual FCFSQueueNode *getHead();
    virtual Request *getRequest();
    virtual bool isEmpty();
    virtual void print();
    virtual ~STRACKQueue();

private:
    FCFSQueueNode *head, *tail;
};
