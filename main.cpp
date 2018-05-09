#include "EventQueue.hpp"
#include "Request.hpp"
#include "Disk.hpp"
#include "iomanip"

#include "FCFSQueue.hpp"
#include "STRACKQueue.hpp"
#include "PICKUPQueue.hpp"
#include "LOOKUPQueue.hpp"
#include "CLOOKQueue.hpp"

#include <iostream>
#include <queue>
#include <fstream>

bool debugMain = false;

double systemTime = 0;

int main() {

    // std::queue <Request *> queueRequest;

    // EVENT QUEUE
    EventQueue * eq = new EventQueue();

    // EventQueue * eqSTRACK = new EventQueue();

    // DECLARING DISK
    Disk * fcfsDisk = new Disk(new FCFSQueue(), 1);
    Disk * strackDisk = new Disk(new STRACKQueue(), 2);
    Disk * pickUpDisk = new Disk(new PICKUPQueue(), 3);
    Disk * lookUpDisk = new Disk(new LOOKUPQueue(), 4);
    Disk * cLookDisk = new Disk(new CLOOKQueue(), 5);




    double time;
    int track;
    int sector;




    // ---------------  POPULATING EVENT QUEUE WITH REQUEST  ---------------
    double timeTrack = 0;
    int index = 1;
    while (1)
    {


        std::cin >> time;
        std::cin >> track;
        std::cin >> sector;
        if ( std::cin.eof() ) break; // so the results arent duplicated

        EventQueueNode * eQNode = new EventQueueNode (new Request(time, track, sector, index));



        // queueRequest.push(req);
        eq->addRequest(eQNode); // FCFS



        while (eQNode->time() > timeTrack)
        {
            timeTrack += 50;
            eq->addRequest(new EventQueueNode (new Timer(timeTrack)));

        }

        index++;

    }

    if (debugMain)
    {
        std::cout << "Event Q before servicing request: " << std::endl;
        eq->print();
    }

    // ---------------  POPULATING EVENT QUEUE WITH REQUEST  ---------------

















    int iterCount = 1;
    while (!eq->isEmpty())
    {



        if (debugMain)
        {
            std::cout << "On iteration #: " << iterCount << std::endl;
            eq->print();
            iterCount++;
        }


        EventQueueNode * eventQNode = eq->getEventQueueNode(); // grabs eventQNode and removes it from the Q

        if (debugMain)
            std::cout << "Inside is not empty loop" << std::endl;
        // eq->print();

        if ( eventQNode->diskDone() != nullptr ) // then its a disk done event it needs to be serviced
        {


            if (eventQNode->diskDone()->getDiskType() == 1)
            {
                if (debugMain)
                {
                    std::cout << "A disk done event is being serviced at time: " << eventQNode->time() << " for FCFS" << std::endl;

                }


                DiskDone * diskDone = fcfsDisk->processDiskDoneRequest();

                if (diskDone != nullptr)
                {
                        eq->addRequest(new EventQueueNode(diskDone));

                        while (diskDone->time() >= timeTrack )
                        {
                            timeTrack += 50;
                            eq->addRequest(new EventQueueNode (new Timer(timeTrack)));
                        }

                }

            }
            //
            //
            else if (eventQNode->diskDone()->getDiskType() == 2)
            {

                if (debugMain)
                    std::cout << "A disk done event is being serviced at time: " << eventQNode->time() << " for STRACK" << std::endl;

                DiskDone * diskDone = strackDisk->processDiskDoneRequest();

                if (diskDone != nullptr)
                {
                        eq->addRequest(new EventQueueNode(diskDone));

                        while (diskDone->time() >= timeTrack )
                        {
                            timeTrack += 50;
                            eq->addRequest(new EventQueueNode (new Timer(timeTrack)));
                        }

                }




            }

            else if (eventQNode->diskDone()->getDiskType() == 3)
            {
                if (debugMain)
                    std::cout << "A disk done event is being serviced at time: " << eventQNode->time() << " for PICKUP" << std::endl;

                    DiskDone * diskDone = pickUpDisk->processDiskDoneRequest();

                    if (diskDone != nullptr)
                    {
                            eq->addRequest(new EventQueueNode(diskDone));

                            while (diskDone->time() >= timeTrack )
                            {
                                timeTrack += 50;
                                eq->addRequest(new EventQueueNode (new Timer(timeTrack)));
                            }

                    }
            }




            else if (eventQNode->diskDone()->getDiskType() == 4)
            {
                if (debugMain)
                    std::cout << "A disk done event is being serviced at time: " << eventQNode->time() << " for LOOKUP" << std::endl;

                    DiskDone * diskDone = lookUpDisk->processDiskDoneRequest();

                    if (diskDone != nullptr)
                    {
                            eq->addRequest(new EventQueueNode(diskDone));

                            while (diskDone->time() >= timeTrack )
                            {
                                timeTrack += 50;
                                eq->addRequest(new EventQueueNode (new Timer(timeTrack)));
                            }

                    }
            }




            else if (eventQNode->diskDone()->getDiskType() == 5)
            {
                if (debugMain)
                    std::cout << "A disk done event is being serviced at time: " << eventQNode->time() << " for CLOOK" << std::endl;

                    DiskDone * diskDone = cLookDisk->processDiskDoneRequest();

                    if (diskDone != nullptr)
                    {
                            eq->addRequest(new EventQueueNode(diskDone));

                            while (diskDone->time() >= timeTrack )
                            {
                                timeTrack += 50;
                                eq->addRequest(new EventQueueNode (new Timer(timeTrack)));
                            }

                    }
            }

        }

        // If the eventQNode is a request the disk must process the request
        else if ( eventQNode->request() != nullptr ) //then the node is a request
        {
            DiskDone * diskDoneFCFS = fcfsDisk->processRequest(eventQNode->request());
            DiskDone * diskDoneSTRACK = strackDisk->processRequest(eventQNode->request());
            DiskDone * diskDonePICKUP = pickUpDisk->processRequest(eventQNode->request());
            DiskDone * diskDoneLOOKUP = lookUpDisk->processRequest(eventQNode->request());
            DiskDone * diskDoneCLOOK = cLookDisk->processRequest(eventQNode->request());

            if (diskDoneFCFS != nullptr)
            {
                eq->addRequest(new EventQueueNode(diskDoneFCFS));

                while (diskDoneFCFS->time() >= timeTrack )
                {
                    timeTrack += 50;
                    eq->addRequest(new EventQueueNode (new Timer(timeTrack)));
                }


            }

            if (diskDoneSTRACK != nullptr)
            {
                eq->addRequest(new EventQueueNode(diskDoneSTRACK));

                while (diskDoneSTRACK->time() >= timeTrack)
                {
                    timeTrack += 50;
                    eq->addRequest(new EventQueueNode (new Timer(timeTrack)));
                }

            }

            if (diskDonePICKUP != nullptr)
            {
                eq->addRequest(new EventQueueNode(diskDonePICKUP));

                while (diskDonePICKUP->time() >= timeTrack)
                {
                    timeTrack += 50;
                    eq->addRequest(new EventQueueNode (new Timer(timeTrack)));
                }

            }

            if (diskDoneLOOKUP != nullptr)
            {
                eq->addRequest(new EventQueueNode(diskDoneLOOKUP));

                while (diskDoneLOOKUP->time() >= timeTrack)
                {
                    timeTrack += 50;
                    eq->addRequest(new EventQueueNode (new Timer(timeTrack)));
                }

            }


            if (diskDoneCLOOK != nullptr)
            {
                eq->addRequest(new EventQueueNode(diskDoneCLOOK));

                while (diskDoneCLOOK->time() >= timeTrack)
                {
                    timeTrack += 50;
                    eq->addRequest(new EventQueueNode (new Timer(timeTrack)));
                }

            }





        }



        // THE TIMER IS NOTED OUT AND WILL JUST BE DELETED

        else if (eventQNode->timer() != nullptr) // its a timer
        {
            // if (debugMain)
            //     std::cout << "A timer event is being serviced at time: " << eventQNode->time() << std::endl;
            //
            fcfsDisk->processTimerEvent();
            strackDisk->processTimerEvent();
            pickUpDisk->processTimerEvent();
            lookUpDisk->processTimerEvent();
            cLookDisk->processTimerEvent();

        }



        // eq->print();
        delete eventQNode;
    }















    std::ofstream TIMER_OUTPUT;
    TIMER_OUTPUT.open ("TIMER_OUTPUT");


    // TIMER -------------------------
    //print out timer
    double timerIncrementer = 50.00;

    TIMER_OUTPUT << "TIMER REPORT" << std::endl;
    TIMER_OUTPUT << std::setw(10) << "Time" << std::setw(14) << "FCFS" << std::setw(14) << "STRACK" << std::setw(14) << "PICKUP";
    TIMER_OUTPUT << std::setw(14) << "CLOOK" << std::setw(14) << "LOOKUP" << std::endl;

    for (int i = 0; i < fcfsDisk->getTimer().size(); i++)
    {   TIMER_OUTPUT << std::fixed << std::setprecision(2) << std::setw(10) << timerIncrementer;
        TIMER_OUTPUT << std::setw(14) << fcfsDisk->getTimer()[i] << std::setw(14) << strackDisk->getTimer()[i];
        TIMER_OUTPUT << std::setw(14) << pickUpDisk->getTimer()[i] << std::setw(14) << cLookDisk->getTimer()[i];
        TIMER_OUTPUT << std::setw(14) << lookUpDisk->getTimer()[i];
        TIMER_OUTPUT << std::endl;
        timerIncrementer += 50;
    }










    // / ---------- CALCULATE --------------
    fcfsDisk->calculateDisk();
    strackDisk->calculateDisk();
    pickUpDisk->calculateDisk();
    lookUpDisk->calculateDisk();
    cLookDisk->calculateDisk();
    // / ---------- CALCULATE --------------












    // SUMMARY OUTPUT -------------

    std::ofstream SUMMARY_OUTPUT;
    SUMMARY_OUTPUT.open ("SUMMARY_OUTPUT");


    SUMMARY_OUTPUT << "SUMMARY REPORT" << std::endl << std::endl;

    SUMMARY_OUTPUT << std::setw(13) << std::left << "Name";
    SUMMARY_OUTPUT << std::setw(36) << std::left << "TimeInSystem";
    SUMMARY_OUTPUT << std::setw(36) << std::left << "WaitTime";
    SUMMARY_OUTPUT << std::setw(36) << std::left << "ServiceTime";
    SUMMARY_OUTPUT << std::setw(36) << std::left << "NumInQue" << std::endl;


    SUMMARY_OUTPUT << std::setw(15) << std::right << "Min" << std::right << std::setw(10) << "Max" << std::setw(10) << "Avg";
    SUMMARY_OUTPUT << std::setw(16) << std::right << "Min" << std::right << std::setw(10) << "Max" << std::setw(10) << "Avg";
    SUMMARY_OUTPUT << std::setw(16) << std::right << "Min" << std::right << std::setw(10) << "Max" << std::setw(10) << "Avg";
    SUMMARY_OUTPUT << std::setw(16) << std::right << "Max" << std::right << std::setw(10) << "Avg" << std::endl;




    // SET PRECISION
    SUMMARY_OUTPUT << std::fixed << std::setprecision(2);



    // FCFS -----------------------------------------
    // NAME
    SUMMARY_OUTPUT << std::setw(8) << std::left << "FCFS";

    // TIME IN SYSTEM
    SUMMARY_OUTPUT << std::setw(7)  << std::right << fcfsDisk->getTimeInSystemMin() << std::right << std::setw(10) << fcfsDisk->getTimeInSystemMax() << std::setw(10) << fcfsDisk->getTimeInSystemAvg();

    // WAIT TIME
    SUMMARY_OUTPUT << std::setw(16) << std::right << fcfsDisk->getWaitTimeMin() << std::right << std::setw(10) << fcfsDisk->getWaitTimeMax() << std::setw(10) << fcfsDisk->getWaitTimeAvg();

    // SERVICE TIME
    SUMMARY_OUTPUT << std::setw(16) << std::right << fcfsDisk->getServiceTimeMin() << std::right << std::setw(10) << fcfsDisk->getServiceTimeMax() << std::setw(10) << fcfsDisk->getServiceTimeAvg();

    // NumInQue
    SUMMARY_OUTPUT << std::setw(16) << std::right << fcfsDisk->getNumInQMax() << std::right << std::setw(10) << fcfsDisk->getNumInQAvg();
    SUMMARY_OUTPUT << std::endl;

    // FCFS -----------------------------------------



    // STRACK -----------------------------------------
    // NAME
    SUMMARY_OUTPUT << std::setw(8) << std::left << "STRACK";

    // TIME IN SYSTEM
    SUMMARY_OUTPUT << std::setw(7) << std::right << strackDisk->getTimeInSystemMin() << std::right << std::setw(10) << strackDisk->getTimeInSystemMax() << std::setw(10) << strackDisk->getTimeInSystemAvg();

    // WAIT TIME
    SUMMARY_OUTPUT << std::setw(16) << std::right << strackDisk->getWaitTimeMin() << std::right << std::setw(10) << strackDisk->getWaitTimeMax() << std::setw(10) << strackDisk->getWaitTimeAvg();

    // SERVICE TIME
    SUMMARY_OUTPUT << std::setw(16) << std::right << strackDisk->getServiceTimeMin() << std::right << std::setw(10) << strackDisk->getServiceTimeMax() << std::setw(10) << strackDisk->getServiceTimeAvg();

    // NumInQue
    SUMMARY_OUTPUT << std::setw(16) << std::right << strackDisk->getNumInQMax() << std::right << std::setw(10) << strackDisk->getNumInQAvg();
    SUMMARY_OUTPUT << std::endl;


    // STRACK -----------------------------------------



    // PICKUP -----------------------------------------
    // NAME
    SUMMARY_OUTPUT << std::setw(8) << std::left << "PICKUP";

    // TIME IN SYSTEM
    SUMMARY_OUTPUT << std::setw(7) << std::right << pickUpDisk->getTimeInSystemMin() << std::right << std::setw(10) << pickUpDisk->getTimeInSystemMax() << std::setw(10) << pickUpDisk->getTimeInSystemAvg();

    // WAIT TIME
    SUMMARY_OUTPUT << std::setw(16) << std::right << pickUpDisk->getWaitTimeMin() << std::right << std::setw(10) << pickUpDisk->getWaitTimeMax() << std::setw(10) << pickUpDisk->getWaitTimeAvg();

    // SERVICE TIME
    SUMMARY_OUTPUT << std::setw(16) << std::right << pickUpDisk->getServiceTimeMin() << std::right << std::setw(10) << pickUpDisk->getServiceTimeMax() << std::setw(10) << pickUpDisk->getServiceTimeAvg();

    // NumInQue
    SUMMARY_OUTPUT << std::setw(16) << std::right << pickUpDisk->getNumInQMax() << std::right << std::setw(10) << pickUpDisk->getNumInQAvg();
    SUMMARY_OUTPUT << std::endl;


    // PICKUP -----------------------------------------




    // CLOOK -----------------------------------------


    SUMMARY_OUTPUT << std::setw(8) << std::left << "CLOOK";

    // TIME IN SYSTEM
    SUMMARY_OUTPUT << std::setw(7) << std::right << cLookDisk->getTimeInSystemMin() << std::right << std::setw(10) << cLookDisk->getTimeInSystemMax() << std::setw(10) << cLookDisk->getTimeInSystemAvg();

    // WAIT TIME
    SUMMARY_OUTPUT << std::setw(16) << std::right << cLookDisk->getWaitTimeMin() << std::right << std::setw(10) << cLookDisk->getWaitTimeMax() << std::setw(10) << cLookDisk->getWaitTimeAvg();

    // SERVICE TIME
    SUMMARY_OUTPUT << std::setw(16) << std::right << cLookDisk->getServiceTimeMin() << std::right << std::setw(10) << cLookDisk->getServiceTimeMax() << std::setw(10) << cLookDisk->getServiceTimeAvg();

    // NumInQue
    SUMMARY_OUTPUT << std::setw(16) << std::right << cLookDisk->getNumInQMax() << std::right << std::setw(10) << cLookDisk->getNumInQAvg();
    SUMMARY_OUTPUT << std::endl;

    // CLOOK -----------------------------------------









    // LOOKUP -----------------------------------------

    SUMMARY_OUTPUT << std::setw(8) << std::left << "LOOKUP";

    // TIME IN SYSTEM
    SUMMARY_OUTPUT << std::setw(7) << std::right << lookUpDisk->getTimeInSystemMin() << std::right << std::setw(10) << lookUpDisk->getTimeInSystemMax() << std::setw(10) << lookUpDisk->getTimeInSystemAvg();

    // WAIT TIME
    SUMMARY_OUTPUT << std::setw(16) << std::right << lookUpDisk->getWaitTimeMin() << std::right << std::setw(10) << lookUpDisk->getWaitTimeMax() << std::setw(10) << lookUpDisk->getWaitTimeAvg();

    // SERVICE TIME
    SUMMARY_OUTPUT << std::setw(16) << std::right << lookUpDisk->getServiceTimeMin() << std::right << std::setw(10) << lookUpDisk->getServiceTimeMax() << std::setw(10) << lookUpDisk->getServiceTimeAvg();

    // NumInQue
    SUMMARY_OUTPUT << std::setw(16) << std::right << lookUpDisk->getNumInQMax() << std::right << std::setw(10) << lookUpDisk->getNumInQAvg();
    SUMMARY_OUTPUT << std::endl;

    // LOOKUP -----------------------------------------





    SUMMARY_OUTPUT.close();


    // SUMMARY OUTPUT -------------









    delete eq;


    return 0;
}
