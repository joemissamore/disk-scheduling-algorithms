#include "FCFSQueue.hpp"
#include "Request.hpp"

#include "AccessTime.hpp"

#include <iomanip>      // std::setw
#include <fstream> //std::ostream
// #include <cmath>

/*
  Actual Queue implementation

*/
void FCFSQueue::addRequest(Request *request) {
	// New QueNode
    FCFSQueueNode *rNode = new FCFSQueueNode(request);
    if( isEmpty() ) {
        head = tail = rNode;
    } else {
        tail->next(rNode);
        tail = rNode;
    }
}

Request *FCFSQueue::getRequest() {
    if( isEmpty() ) {
        std::cout << "Calling FCFSQueueNode::getRequest() on empty queue. Terminating...\n";
        exit(1);
    }
    else
    {
        Request * temp = head->request();
        head = head->next();

        return temp;
    }
}

FCFSQueueNode *FCFSQueue::getHead() {
    return head;
}

bool FCFSQueue::isEmpty() {
    return head == nullptr;
}

void FCFSQueue::print() {

    std::ofstream FCFS_OUTPUT;
    FCFS_OUTPUT.open("FCFS_OUTPUT");

    FCFS_OUTPUT << "FCFS REPORT" << std::endl;

    AccessTime * accessTime = new AccessTime();
    accessTime->setTime(head->request()->time());

    FCFS_OUTPUT << std::setw(4) << "#" << std::setw(8) << "Trac" << std::setw(8) << "Sec" << std::setw(8) << "Entr" << std::setw(8) << "Init" << std::setw(8);
    FCFS_OUTPUT << "Comp" << std::setw(8) << "Wait" << std::setw(8) << "Serv" << std::setw(8) << "TmInSys" << std::endl;

    int i = 1;
    for(auto cur = head; cur; cur = cur->next() )
    {

        accessTime->setSeekTime(accessTime->getCurTrack(), cur->request()->track());
        accessTime->setRotationalDelay(accessTime->getCurSector(), cur->request()->sector());



        FCFS_OUTPUT << std::setw(4) << cur->request()->index() << std::setw(8);

        // print out current track
        FCFS_OUTPUT << cur->request()->track() << std::setw(8);

        // print out sector
        FCFS_OUTPUT << cur->request()->sector() << std::setw(8);


        // Set decimal precision
        FCFS_OUTPUT << std::fixed << std::setprecision(2);

        // ENTR
        // set time
        accessTime->setTime( cur->request()->time() ); // Entr
        // get initial time
        FCFS_OUTPUT << accessTime->getTime() << std::setw(8); // Entr


        //INIT
        // get initial time
        accessTime->setCurrentTime();
        FCFS_OUTPUT << accessTime->getCurTime() << std::setw(8);


        // Comp
        accessTime->setAccessTime();
        accessTime->setComp();
        FCFS_OUTPUT << accessTime->getComp() << std::setw(8);

        // Wait
        accessTime->setWait();
        FCFS_OUTPUT << accessTime->getWait() << std::setw(8);

        // Serv
        // accessTime->setAccessTime() // Already set, is called automatically
        // by setRotationalDelay
        FCFS_OUTPUT << accessTime->getAccessTime() << std::setw(8);

        //TmInSys
        accessTime->setTmInSys();
        FCFS_OUTPUT << accessTime->getTmInSys() ;


        //AT THE END YOU NEED TO SET THE CURRENT TRACK TO PLUS 1 BECAUSE THATS WHERE IT LEFT OFF
        accessTime->setCurSector( accessTime->getCurSector() + 1 );

        FCFS_OUTPUT << std::endl;






    }

    FCFS_OUTPUT.close();

}

// Deletes all the nodes
FCFSQueue::~FCFSQueue() {
    while( head != nullptr ) {
        FCFSQueueNode *node = head;
        head = node->next();
        delete node;
    }
}
