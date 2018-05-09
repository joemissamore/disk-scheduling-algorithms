#include "Disk.hpp"
// #include "DiskDone.hpp"
#include "AccessTime.hpp"
#include "Request.hpp"
#include "EventQueueNode.hpp"

extern double systemTime;

// AccessTime * accessTime = new AccessTime();

bool diskDebug = false;

// The Job of processRequest
// By default add the request to the waitQueue
// If the disk is not busy calculate its completion time
// If the disk is busy return a null ptr;
DiskDone * Disk::processRequest(Request * request)
{
    if (diskDebug)
    {
        std::cout << "Inside process request" << std::endl;
    }

        waitQueue->addRequest(request);

        if (state == 0)
        {
            if (diskDebug)
            {
                std::cout << "The state == 0 for the REQUEST: " << request->time() << std::endl;
            }
            // Calculate
            accessTime->setSeekTime(accessTime->getCurTrack(), request->track());
            accessTime->setRotationalDelay(accessTime->getCurSector(), request->sector());
            accessTime->setTime(request->time());
            accessTime->setCurrentTime();
            accessTime->setAccessTime();
            accessTime->setComp();
            accessTime->setWait();
            accessTime->setTmInSys();

            // This pushes all stats into there vectors
            timeInSystem.push_back(accessTime->getTmInSys());
            waitTime.push_back(accessTime->getWait());
            serviceTime.push_back(accessTime->getAccessTime());

            accessTime->setCurSector(accessTime->getCurSector() + 1);

            state = 1;
            return new DiskDone(accessTime->getComp(), getDiskType());
        }

        if (diskDebug)
        {
            std::cout << "The state == 1 for the REQUEST: " << request->time() << std::endl;
        }

        return nullptr;










    // if state = 1 reutrn null

    // if state is not 1
    // {
        // remove request from waitqueue and serve it, generate a disk-done event for it, and return the disk-done event.
    // }
    // accessTime->setSeekTime(accessTime->getCurTrack(), reqEvent->track());
    // accessTime->setRotationalDelay(accessTime->getCurSector(), reqEvent->sector());
    // accessTime->setTime(reqEvent->time());
    // accessTime->setCurrentTime();
    // accessTime->setAccessTime();
    // accessTime->setComp();
    // accessTime->setWait();
    // accessTime->setTmInSys();
    //
    // // This pushes all stats into there vectors
    // timeInSystem.push_back(accessTime->getTmInSys());
    // waitTime.push_back(accessTime->getWait());
    // serviceTime.push_back(accessTime->getAccessTime());



    // There is no need to do anything to the timer


    // waitTimeAvg = waitTimeAvg / j;
    // std::cout << "waitTimeAvg: " << waitTimeAvg << std::endl;
    // serviceTimeAvg = serviceTimeAvg / j;
    // std::cout << "serviceTimeAvg: " << serviceTimeAvg << std::endl;




    // waitQueue->print();

    // std::cout << "accessTime->getComp(): " << accessTime->getComp() << std::endl;


    // accessTime->setCurSector(accessTime->getCurSector() + 1);


    // return new DiskDone(accessTime->getComp(), getDiskType());

}

// ProcessDiskDoneRequest's job is different in that it services a diskDoneEvent
// When the disk is done servicing a request it removes that request from the WaitQueue
// If the WaitQueue is empty the it sets its state = 0 and returns a nullptr;
// If the WaitQueue is not empty it calculates the DiskDone

DiskDone * Disk::processDiskDoneRequest ()
{
    Request * req = waitQueue->getRequest();



    if (diskDebug)
    {
        std::cout << "Inside processDiskDoneRequest for REQUEST: " << req->time() << std::endl;
    }

    // delete req; // cant delete a nullptr



    if (waitQueue->isEmpty())
    {
        if (diskDebug)
        {
            std::cout << "waitQueue is Empty for disk NUMBER: " << getDiskType() << std::endl;
        }

        state = 0;
        return nullptr;
    }



    if (state == 1)
    {

        if(diskDebug)
        {
            std::cout << "The state is 1 for disk NUMBER: " << getDiskType() << std::endl;
        }

    Request * request = waitQueue->getHead()->request(); // reassigning request pointer.


    // else the waitQueue is not empty and will begin to service a request
    // calculate the service time and return its diskDoneEvent.
    accessTime->setSeekTime(accessTime->getCurTrack(), request->track());
    accessTime->setRotationalDelay(accessTime->getCurSector(), request->sector());
    accessTime->setTime(request->time());
    accessTime->setCurrentTime();
    accessTime->setAccessTime();
    accessTime->setComp();
    accessTime->setWait();
    accessTime->setTmInSys();

    // This pushes all stats into there vectors
    timeInSystem.push_back(accessTime->getTmInSys());
    waitTime.push_back(accessTime->getWait());
    serviceTime.push_back(accessTime->getAccessTime());

    accessTime->setCurSector(accessTime->getCurSector() + 1);

    // state = 1; // redundant because the state has never changed

    return new DiskDone(accessTime->getComp(), getDiskType());

    }

    // accessTime->setSeekTime(accessTime->getCurTrack(), reqEvent->track());
    // accessTime->setRotationalDelay(accessTime->getCurSector(), reqEvent->sector());
    // accessTime->setTime(reqEvent->time());
    // accessTime->setCurrentTime();
    // accessTime->setAccessTime();
    // accessTime->setComp();
    // accessTime->setWait();
    // accessTime->setTmInSys();
    //
    // accessTime->setCurSector(accessTime->getCurSector() + 1);
    //
    // // This pushes all stats into there vectors
    // timeInSystem.push_back(accessTime->getTmInSys());
    // waitTime.push_back(accessTime->getWait());
    // serviceTime.push_back(accessTime->getAccessTime());
    //
    // return new DiskDone(accessTime->getComp(), getDiskType());


}

void Disk::processTimerEvent()
{
    int i = 0;
    for (auto cur = waitQueue->getHead(); cur; cur = cur->next())
    {
        i++;
    }

    timer.push_back(i);
    // std::cout << "Time: " << systemTime << "   FCFS: " << waitQueueLength() << std::endl;
}

void Disk::calculateDisk()
{
    timeInSystemMax = timeInSystemMin = timeInSystem[0];
    waitTimeMax = waitTimeMin = waitTime[0];
    serviceTimeMax = serviceTimeMin = serviceTime[0];

    //calculating the averages
    double j = 0;
    for (double i = 0; i < timeInSystem.size(); i++)
    {
        if ( timeInSystemMax < timeInSystem[i] ) { timeInSystemMax = timeInSystem[i]; }
        if ( waitTimeMax < waitTime[i] ) { waitTimeMax = waitTime[i]; }
        if ( serviceTimeMax < serviceTime[i] ) { serviceTimeMax = serviceTime[i]; }

        if ( timeInSystemMin > timeInSystem[i] ) { timeInSystemMin = timeInSystem[i]; }
        if ( waitTimeMin > waitTime[i] ) { waitTimeMin = timeInSystem[i]; }
        if ( serviceTimeMin > serviceTime[i] ) { serviceTimeMin = serviceTime[i]; }




        timeInSystemAvg += timeInSystem[i];
        waitTimeAvg += waitTime[i];
        serviceTimeAvg += serviceTime[i];

        j = i + 1; // plus 1 for calculating averages
    }

    timeInSystemAvg = timeInSystemAvg / j;
    // std::cout << "timeInSystemAvg: " << timeInSystemAvg << std::endl;

    waitTimeAvg = waitTimeAvg / j;
    // std::cout << "waitTimeAvg: " << waitTimeAvg << std::endl;

    serviceTimeAvg = serviceTimeAvg / j;
    // std::cout << "serviceTimeAvg: " << serviceTimeAvg << std::endl;

    // std::cout << "timeInSystemMin: " << timeInSystemMin << std::endl;
    // std::cout << "timeInSystemMax: " << timeInSystemMax << std::endl;

    double k = 0;
    for (double i = 0; i < timer.size(); i++)
    {
        if (numInQMax < timer[i])
            numInQMax = timer[i];

        numInQAvg += timer[i];

        k = i + 1;
    }

    numInQAvg = numInQAvg / k;


}

Disk::~Disk()
{

}
