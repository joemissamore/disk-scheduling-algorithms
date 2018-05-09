#ifndef __EventQueueNode_hpp
#define __EventQueueNode_hpp

#include "DiskDone.hpp"
#include "Request.hpp"
#include "Timer.hpp"
// class Timer;

class EventQueueNode
{
    public:
        EventQueueNode(): _next(nullptr), _diskDone(nullptr), _timer(nullptr), _request(nullptr), _time(0) {}
        EventQueueNode( DiskDone * diskDone ): _next(nullptr), _diskDone(diskDone), _timer(nullptr), _request(nullptr), _time(diskDone->time()) {}
        EventQueueNode( Timer * timer ): _next(nullptr), _diskDone(nullptr), _timer(timer), _request(nullptr), _time(timer->time()) {}
        EventQueueNode( Request * request ):_next(nullptr),  _diskDone(nullptr), _timer(nullptr), _request(request), _time(request->time() * 0.1) {}
        EventQueueNode * next() { return _next; }

        void next(EventQueueNode *node) { _next = node; }

        DiskDone * diskDone() { return _diskDone; }
        Timer * timer() { return _timer; }
        Request * request() { return _request; }

        double time() { return _time; }





    private:
        DiskDone * _diskDone; // Construct this
        Timer * _timer; // Construct this
        Request * _request;

        EventQueueNode * _next;

        double _time;



};

#endif
