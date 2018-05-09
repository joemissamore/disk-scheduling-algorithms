#ifndef __QUEUE_HPP
#define __QUEUE_HPP

#include "FCFSQueueNode.hpp"

class Request;

class Queue {

	// Virtual Functions
	// Are functions that you can expect to be redefined in derived
	// classes.
public:
    virtual void addRequest(Request *request) = 0;
    virtual FCFSQueueNode *getHead() = 0;
    virtual Request *getRequest() = 0;
    virtual bool isEmpty() = 0;
    virtual void print() = 0;
    virtual ~Queue() {}

};

#endif
