#include "PICKUPQueue.hpp"
#include "Request.hpp"
#include "AccessTime.hpp"

#include <iomanip> // std::setw
#include <fstream>

bool debug = false;

void PICKUPQueue::addRequest(Request *request)
{
    int trackNum = 0;

    FCFSQueueNode *rNode = new FCFSQueueNode(request);
    if( isEmpty() ) {
        if (debug)
        {
                std::cout << "#0" << std::endl;
                std::cout << "Track: " << request->track() << " Sector: " << request->sector() << std::endl;
        }
        head = tail = rNode;
    } else {

        for (auto cur = head; cur; cur = cur -> next())
        {

            if (cur == tail)
            {
                if (debug)
                {
                        std::cout << "#1" << std::endl;
                        std::cout << "Track: " << request->track() << " Sector: " << request->sector() << std::endl;
                }
                cur->next(rNode);
                tail = rNode;
                break;
            }

            else if ( cur->request()->track() == request->track() )
            {
                if ( cur->next()->request()->track() != request->track() )
                {
                    if (debug)
                    {
                        std::cout << "2.1!" << std::endl;
                        std::cout << "Track: " << request->track() << " Sector: " << request->sector() << std::endl;
                    }

                    rNode->next(cur->next());
                    cur->next(rNode);
                    break;
                }
            }


            else if (cur->next()->request()->track() < request->track() && cur->request()->track() > request->track())
            {
                if (debug)
                {
                        std::cout << "#4" << std::endl;
                        std::cout << "Track: " << request->track() << " Sector: " << request->sector() << std::endl;
                }
                rNode->next(cur->next()); // = 77 --> 48
                cur->next(rNode); // 79 --> 77
                break;
            }



        }
        trackNum = request->track();

        if (debug)
        {
                std::cout << "The following has not been evaluated -> ";
                std::cout << "Track: " << request->track() << " Sector: " << request->sector() << std::endl;
        }


    }


}

Request *PICKUPQueue::getRequest()
{
    if( isEmpty() ) {
        std::cout << "Calling PICKUPQueue::getRequest() on empty queue. Terminating...\n";
        exit(1);
    }
    else
    {
        Request * temp = head->request();
        head = head->next();

        return temp;
    }
}

FCFSQueueNode *PICKUPQueue::getHead() {
    return head;
}

bool PICKUPQueue::isEmpty()
{
    return head == nullptr;
}

void PICKUPQueue::print()
{

    std::ofstream PICKUP_OUTPUT;
    PICKUP_OUTPUT.open("PICKUP_OUTPUT");

    PICKUP_OUTPUT << "PICKUP REPORT" << std::endl;

    AccessTime * accessTime = new AccessTime();
    accessTime->setTime(head->request()->time());

    PICKUP_OUTPUT << std::setw(4) << "#" << std::setw(8) << "Trac" << std::setw(8) << "Sec" << std::setw(8) << "Entr" << std::setw(8) << "Init" << std::setw(8);
    PICKUP_OUTPUT << "Comp" << std::setw(8) << "Wait" << std::setw(8) << "Serv" << std::setw(8) << "TmInSys" << std::endl;

    // int i = 1;
    for(auto cur = head; cur; cur = cur->next() )
    {
        accessTime->setSeekTime(accessTime->getCurTrack(), cur->request()->track());
        accessTime->setRotationalDelay(accessTime->getCurSector(), cur->request()->sector());


        PICKUP_OUTPUT << std::setw(4) << cur->request()->index() << std::setw(8);

        // print out current track
        PICKUP_OUTPUT << cur->request()->track() << std::setw(8);

        // print out sector
        PICKUP_OUTPUT << cur->request()->sector() << std::setw(8);


        // Set decimal precision
        PICKUP_OUTPUT << std::fixed << std::setprecision(2);

        // ENTR
        // set time
        accessTime->setTime( cur->request()->time() ); // Entr
        // get initial time
        PICKUP_OUTPUT << accessTime->getTime() << std::setw(8); // Entr


        //INIT
        // get initial time
        accessTime->setCurrentTime();
        PICKUP_OUTPUT << accessTime->getCurTime() << std::setw(8);


        // Comp
        accessTime->setAccessTime();
        accessTime->setComp();
        PICKUP_OUTPUT << accessTime->getComp() << std::setw(8);

        // Wait
        accessTime->setWait();
        PICKUP_OUTPUT << accessTime->getWait() << std::setw(8);

        // Serv
        // accessTime->setAccessTime() // Already set, is called automatically
        // by setRotationalDelay
        PICKUP_OUTPUT << accessTime->getAccessTime() << std::setw(8);

        //TmInSys
        accessTime->setTmInSys();
        PICKUP_OUTPUT << accessTime->getTmInSys() ;


        //AT THE END YOU NEED TO SET THE CURRENT TRACK TO PLUS 1 BECAUSE THATS WHERE IT LEFT OFF
        accessTime->setCurSector( accessTime->getCurSector() + 1 );
        PICKUP_OUTPUT << std::endl;


    }

    PICKUP_OUTPUT.close();
}

PICKUPQueue::~PICKUPQueue()
{
    while( head != nullptr ) {
        FCFSQueueNode *node = head;
        head = node->next();
        delete node;
    }
}
