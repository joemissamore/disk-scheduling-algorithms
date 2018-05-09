#include "STRACKQueue.hpp"
#include "Request.hpp"
#include "AccessTime.hpp"

#include <iomanip> // std::setw
#include <fstream>

bool debugST = false;

void STRACKQueue::addRequest(Request *request)
{
    FCFSQueueNode *rNode = new FCFSQueueNode(request);
    if( isEmpty() ) {
        head = tail = rNode;
    } else

    {

        for (auto cur = head; cur; cur = cur->next())
        {
            if ( cur->next() == nullptr )
            {
                  cur->next(rNode);
                  tail = rNode;
                  break;
            }


            else if ( cur->request()->track() == request->track() )
            {
                if ( cur->next()->request()->track() != request->track() )
                {
                    if (debugST)
                    {
                        std::cout << "2.1!" << std::endl;
                        std::cout << "Track: " << request->track() << " Sector: " << request->sector() << std::endl;
                    }

                    rNode->next(cur->next());
                    cur->next(rNode);
                    break;
                }
            }
        }
    }
}

Request *STRACKQueue::getRequest()
{
    if( isEmpty() ) {
        std::cout << "Calling STRACKQueue::getRequest() on empty queue. Terminating...\n";
        exit(1);
    }
    else
    {
        Request * temp = head->request();
        head = head->next();

        return temp;
    }
}

FCFSQueueNode *STRACKQueue::getHead() {
    return head;
}

bool STRACKQueue::isEmpty()
{
    return head == nullptr;
}

void STRACKQueue::print()
{
    std::ofstream STRACK_OUTPUT;
    STRACK_OUTPUT.open("STRACK_OUTPUT");
    STRACK_OUTPUT << "STRACK REPORT" << std::endl;

    AccessTime * accessTime = new AccessTime();
    accessTime->setTime(head->request()->time());

    STRACK_OUTPUT << std::setw(4) << "#" << std::setw(8) << "Trac" << std::setw(8) << "Sec" << std::setw(8) << "Entr" << std::setw(8) << "Init" << std::setw(8);
    STRACK_OUTPUT << "Comp" << std::setw(8) << "Wait" << std::setw(8) << "Serv" << std::setw(8) << "TmInSys" << std::endl;

    int i = 1;
    for(auto cur = head; cur; cur = cur->next() )
    {
        accessTime->setSeekTime(accessTime->getCurTrack(), cur->request()->track()); //
        accessTime->setRotationalDelay(accessTime->getCurSector(), cur->request()->sector()); //


        STRACK_OUTPUT << std::setw(4) << cur->request()->index() << std::setw(8);

        // print out current track
        STRACK_OUTPUT << cur->request()->track() << std::setw(8);

        // print out sector
        STRACK_OUTPUT << cur->request()->sector() << std::setw(8);


        // Set decimal precision
        STRACK_OUTPUT << std::fixed << std::setprecision(2);

        // ENTR
        // set time
        accessTime->setTime( cur->request()->time() ); // Entr
        // get initial time
        STRACK_OUTPUT << accessTime->getTime() << std::setw(8); // Entr


        //INIT
        // get initial time
        accessTime->setCurrentTime();
        STRACK_OUTPUT << accessTime->getCurTime() << std::setw(8);


        // Comp
        accessTime->setAccessTime();
        accessTime->setComp();
        STRACK_OUTPUT << accessTime->getComp() << std::setw(8);

        // Wait
        accessTime->setWait();
        STRACK_OUTPUT << accessTime->getWait() << std::setw(8);

        // Serv
        // accessTime->setAccessTime() // Already set, is called automatically
        // by setRotationalDelay
        STRACK_OUTPUT << accessTime->getAccessTime() << std::setw(8);

        //TmInSys
        accessTime->setTmInSys();
        STRACK_OUTPUT << accessTime->getTmInSys() ;


        //AT THE END YOU NEED TO SET THE CURRENT TRACK TO PLUS 1 BECAUSE THATS WHERE IT LEFT OFF
        accessTime->setCurSector( accessTime->getCurSector() + 1 );
        STRACK_OUTPUT << std::endl;
    }
}

STRACKQueue::~STRACKQueue()
{
    while( head != nullptr ) {
        FCFSQueueNode *node = head;
        head = node->next();
        delete node;
    }
}
