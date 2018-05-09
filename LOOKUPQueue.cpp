#include "LOOKUPQueue.hpp"
#include "Request.hpp"
#include "AccessTime.hpp"

#include <iomanip> // std::setw
#include <fstream>

bool lookupDebug = false;

void LOOKUPQueue::addRequest(Request *request)
{
    int trackNum = 0;

    FCFSQueueNode *rNode = new FCFSQueueNode(request);
    if( isEmpty() ) {
        head = tail = rNode;
    } else {

        for (auto cur = head; cur; cur = cur -> next())
        {

            if (cur == tail)
            {
                if (lookupDebug)
                    std::cout << "Inside 1 -> " << request->time() << std::endl;
                cur->next(rNode);
                tail = rNode;
                break;
            }

            else if ( cur->request()->track() == request->track() )
            {
                if ( cur->next()->request()->track() != request->track() )
                {
                    if (lookupDebug)
                        std::cout << "Inside 2 -> " << request->time() << std::endl;

                    rNode->next(cur->next());
                    cur->next(rNode);
                    break;
                }
            }

            else if ( cur->request()->track() < request->track() && cur->next()->request()->track() < request->track() && cur->request()->track() > cur->next()->request()->track())
            {
                if (lookupDebug)
                    std::cout << "Inside 3 -> " << request->time() << std::endl;

                rNode->next(cur->next());
                cur->next(rNode);
                break;
            }

//            else if (cur->next()->request()->track() < request->track() )
            else if (cur->next()->request()->track() < request->track() && cur->request()->track() > cur->next()->request()->track())
            {
                if (lookupDebug)
                    std::cout << "Inside 4 -> " << request->time() << std::endl;

                rNode->next(cur->next());
                cur->next(rNode);
                break;
            }

            if (lookupDebug)
                std::cout << "Request has not been service yet -> " << request->time() << std::endl;
            // else {}

        }


    }
}

Request *LOOKUPQueue::getRequest()
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

FCFSQueueNode *LOOKUPQueue::getHead() {
    return head;
}

bool LOOKUPQueue::isEmpty()
{
    return head == nullptr;
}

void LOOKUPQueue::print()
{

    std::ofstream LOOK_OUTPUT;
    LOOK_OUTPUT.open("LOOK_OUTPUT");

    LOOK_OUTPUT << "LOOK REPORT" << std::endl;

    AccessTime * accessTime = new AccessTime();
    accessTime->setTime(head->request()->time());

    LOOK_OUTPUT << std::setw(4) << "#" << std::setw(8) << "Trac" << std::setw(8) << "Sec" << std::setw(8) << "Entr" << std::setw(8) << "Init" << std::setw(8);
    LOOK_OUTPUT << "Comp" << std::setw(8) << "Wait" << std::setw(8) << "Serv" << std::setw(8) << "TmInSys" << std::endl;

    int i = 1;
    for(auto cur = head; cur; cur = cur->next() )
    {
        accessTime->setSeekTime(accessTime->getCurTrack(), cur->request()->track());
        accessTime->setRotationalDelay(accessTime->getCurSector(), cur->request()->sector());

        // Increment i
        LOOK_OUTPUT << std::setw(4) << cur->request()->index() << std::setw(8);

        // print out current track
        LOOK_OUTPUT << cur->request()->track() << std::setw(8);

        // print out sector
        LOOK_OUTPUT << cur->request()->sector() << std::setw(8);


        // Set decimal precision
        LOOK_OUTPUT << std::fixed << std::setprecision(2);

        // ENTR
        // set time
        accessTime->setTime( cur->request()->time() ); // Entr
        // get initial time
        LOOK_OUTPUT << accessTime->getTime() << std::setw(8); // Entr


        //INIT
        // get initial time
        accessTime->setCurrentTime();
        LOOK_OUTPUT << accessTime->getCurTime() << std::setw(8);


        // Comp
        accessTime->setAccessTime();
        accessTime->setComp();
        LOOK_OUTPUT << accessTime->getComp() << std::setw(8);

        // Wait
        accessTime->setWait();
        LOOK_OUTPUT << accessTime->getWait() << std::setw(8);

        // Serv
        // accessTime->setAccessTime() // Already set, is called automatically
        // by setRotationalDelay
        LOOK_OUTPUT << accessTime->getAccessTime() << std::setw(8);

        //TmInSys
        accessTime->setTmInSys();
        LOOK_OUTPUT << accessTime->getTmInSys() ;


        //AT THE END YOU NEED TO SET THE CURRENT TRACK TO PLUS 1 BECAUSE THATS WHERE IT LEFT OFF
        accessTime->setCurSector( accessTime->getCurSector() + 1 );
        LOOK_OUTPUT << std::endl;


    }

    LOOK_OUTPUT.close();
}

LOOKUPQueue::~LOOKUPQueue()
{
    while( head != nullptr ) {
        FCFSQueueNode *node = head;
        head = node->next();
        delete node;
    }
}
