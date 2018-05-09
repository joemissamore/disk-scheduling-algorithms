#include "CLOOKQueue.hpp"
#include "Request.hpp"
#include "AccessTime.hpp"

#include <iomanip> // std::setw
#include <fstream>
bool debugCLOOK = false;

void CLOOKQueue::addRequest(Request *request)
{
    int trackNum = 0;

    FCFSQueueNode *rNode = new FCFSQueueNode(request);
    if( isEmpty() ) {
        if (debugCLOOK)
            std::cout << "#0: " << request->track() << std::endl;
        head = tail = rNode;
    } else {

        for (auto cur = head; cur; cur = cur -> next())
        {
            if (cur == tail)
            {
                if (debugCLOOK)
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
                    if (debugCLOOK)
                    {
                        std::cout << "2.1!" << std::endl;
                        std::cout << "Track: " << request->track() << " Sector: " << request->sector() << std::endl;
                    }

                    rNode->next(cur->next());
                    cur->next(rNode);
                    break;
                }

                else if ( cur->request()->track() == request->track() )
                {
                    if ( cur->next()->request()->track() != request->track() )
                    {
                        if (debugCLOOK)
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

            //  79 --> 89 --> 9 --> 43
            // [40]
            // else if (cur->request()->track() > request->track() && cur->request()->track() > cur->next()->request()->track())
            else if (cur->request()->track() > request->track() && cur->next()->request()->track() > request->track() && cur->request()->track() > cur->next()->request()->track())
            {
                if (debugCLOOK)
                {
                        std::cout << "#4" << std::endl;
                        std::cout << "Track: " << request->track() << " Sector: " << request->sector() << std::endl;
                }

                rNode->next(cur->next());
                cur->next(rNode);
                break;
            }

            else if (cur->request()->track() < request->track() && cur->next()->request()->track() > request->track())
            {
                if (debugCLOOK)
                {
                        std::cout << "#5" << std::endl;
                        std::cout << "Track: " << request->track() << " Sector: " << request->sector() << std::endl;
                }

                rNode->next(cur->next());
                cur->next(rNode);
                break;
            }
            else if (cur->request()->track() < request->track() && cur->request()->track() > cur->next()->request()->track())
            {
                if (debugCLOOK)
                {
                        std::cout << "#6" << std::endl;
                        std::cout << "Track: " << request->track() << " Sector: " << request->sector() << std::endl;
                }
                rNode->next(cur->next());
                cur->next(rNode);
                break;
            }

            if (debugCLOOK)
            {
                    std::cout << "The following has not been evaluated -> ";
                    std::cout << "Track: " << request->track() << " Sector: " << request->sector() << std::endl;
            }
        }




    }
}

Request *CLOOKQueue::getRequest()
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

FCFSQueueNode *CLOOKQueue::getHead() {
    return head;
}


bool CLOOKQueue::isEmpty()
{
    return head == nullptr;
}

void CLOOKQueue::print()
{

    std::ofstream CLOOK_OUTPUT;
    CLOOK_OUTPUT.open("CLOOK_OUTPUT");

    CLOOK_OUTPUT << "CLOOK REPORT" << std::endl;



    AccessTime * accessTime = new AccessTime();
    accessTime->setTime(head->request()->time());

    CLOOK_OUTPUT << std::setw(4) << "#" << std::setw(8) << "Trac" << std::setw(8) << "Sec" << std::setw(8) << "Entr" << std::setw(8) << "Init" << std::setw(8);
    CLOOK_OUTPUT << "Comp" << std::setw(8) << "Wait" << std::setw(8) << "Serv" << std::setw(8) << "TmInSys" << std::endl;

    int i = 1;
    for(auto cur = head; cur; cur = cur->next() )
    {
        accessTime->setSeekTime(accessTime->getCurTrack(), cur->request()->track());
        accessTime->setRotationalDelay(accessTime->getCurSector(), cur->request()->sector());


        CLOOK_OUTPUT << std::setw(4) << cur->request()->index() << std::setw(8);

        // print out current track
        CLOOK_OUTPUT << cur->request()->track() << std::setw(8);

        // print out sector
        CLOOK_OUTPUT << cur->request()->sector() << std::setw(8);


        // Set decimal precision
        CLOOK_OUTPUT << std::fixed << std::setprecision(2);

        // ENTR
        // set time
        accessTime->setTime( cur->request()->time() ); // Entr
        // get initial time
        CLOOK_OUTPUT << accessTime->getTime() << std::setw(8); // Entr


        //INIT
        // get initial time
        accessTime->setCurrentTime();
        CLOOK_OUTPUT << accessTime->getCurTime() << std::setw(8);


        // Comp
        accessTime->setAccessTime();
        accessTime->setComp();
        CLOOK_OUTPUT << accessTime->getComp() << std::setw(8);

        // Wait
        accessTime->setWait();
        CLOOK_OUTPUT << accessTime->getWait() << std::setw(8);

        // Serv
        // accessTime->setAccessTime() // Already set, is called automatically
        // by setRotationalDelay
        CLOOK_OUTPUT << accessTime->getAccessTime() << std::setw(8);

        //TmInSys
        accessTime->setTmInSys();
        CLOOK_OUTPUT << accessTime->getTmInSys() ;


        //AT THE END YOU NEED TO SET THE CURRENT TRACK TO PLUS 1 BECAUSE THATS WHERE IT LEFT OFF
        accessTime->setCurSector( accessTime->getCurSector() + 1 );
        CLOOK_OUTPUT << std::endl;
    }

    CLOOK_OUTPUT.close();
}

CLOOKQueue::~CLOOKQueue()
{
    while( head != nullptr ) {
        FCFSQueueNode *node = head;
        head = node->next();
        delete node;
    }
}
