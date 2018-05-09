#include <iostream>

#include "Queue.hpp"
#include "EventQueueNode.hpp"

// Forward Decleration
class Request;

class EventQueue {

public:
    EventQueue(): head(nullptr), tail(nullptr) {}

    virtual void addRequest(Request *request);
    void addRequest(EventQueueNode * );

    virtual Request *getRequest();
    EventQueueNode *getEventQueueNode();
    virtual bool isEmpty();
    virtual void print();
    virtual ~EventQueue();


private:
    EventQueueNode *head, *tail;
};
