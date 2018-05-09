#include "EventQueue.hpp"
#include "Request.hpp"

// #include "AccessTime.hpp"

#include <iomanip>      // std::setw
// #include <cmath>

bool debugEq = false;

/*
  Actual Queue implementation

*/
void EventQueue::addRequest(Request *request) {}
void EventQueue::addRequest(EventQueueNode * rNode) {
	// New QueNode
    // EventQueueNode *rNode = new EventQueueNode(request->request());
    if( isEmpty() ) {
        if (debugEq)
        {
            std::cout << "Inside 1 -> Time: " << rNode->time() << std::endl;
        }

        head = tail = rNode;
    } else {

        for (auto cur = head; cur; cur = cur->next())
        {

            // if (cur == head && cur == tail)
            // {
            //     if (debugEq)
            //     {
            //         std::cout << "Inside 1.5 -> Time: " << rNode->time() << std::endl;
            //     }
            //     rNode->next(head);
            //     head = rNode;
            //     break;
            // }

            if (cur == head && cur->time() > rNode->time())
            {
                if (debugEq)
                {
                    std::cout << "Inside 2.5 -> Time: " << rNode->time() << std::endl;
                }

                rNode->next(head);
                head = rNode;
                break;
            }

            else if (cur == tail)
            {
                if (debugEq)
                {
                    std::cout << "Inside 2 -> Time: " << rNode->time() << std::endl;
                }

                cur->next(rNode);
                tail = rNode;
                break;
            }
            //

            //LEFT OFF HERE BELIEVE THERE IS SOMETHING WRONG WITH THIS STATEMENT
            // 24
            // 22 - 56 - 89
            else if (cur->next()->time() > rNode->time())
            {
                if (debugEq)
                {
                    std::cout << "Inside 3 -> Time: " << rNode->time() << std::endl;
                }
                //22 -->
                rNode->next(cur->next());
                cur->next(rNode);
                break;
            }

            else if (cur->time() == rNode->time())
            {
                // if ( cur->next()->time() != rNode->time() )
                // {
                //     std::cout << "2.1!" << std::endl;
                //     std::cout << "Track: " << rNode->track() << " Sector: " << rNode->sector() << std::endl;
                //     rNode->next(cur->next());
                //     cur->next(rNode);
                //     break;
                // }
                if ( cur->next()->time() != rNode->time() )
                {
                    if (debugEq)
                    {
                        std::cout << "Inside 4 -> Time: " << rNode->time() << std::endl;
                    }

                    rNode->next(cur->next());
                    cur->next(rNode);
                    break;
                }
            }
            //
            if (debugEq)
            {
                std::cout << "The request as not been serviced yet for -> " << rNode->time() << std::endl;
            }
        }
    }
}
Request *EventQueue::getRequest()
{

}

EventQueueNode *EventQueue::getEventQueueNode() {
    if( isEmpty() ) {
        std::cout << "Calling EventQueueNode::getRequest() on empty queue. Terminating...\n";
        exit(1);
    }
    else
    {
        EventQueueNode * temp = head;
        head = head->next();

        return temp;

    }


    // else if (request() != nullptr)
    //     return request();
}

bool EventQueue::isEmpty() {
    return head == nullptr;
}

void EventQueue::print() {

        for (auto cur = head; cur; cur = cur->next())
        {
            std::cout << "Time: " << cur->time();
            std::cout << std::endl;
        }
}

// Deletes all the nodes
EventQueue::~EventQueue() {
    while( head != nullptr ) {
        EventQueueNode *node = head;
        head = node->next();
        delete node;
    }
}
