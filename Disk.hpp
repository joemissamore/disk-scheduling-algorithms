#ifndef __FCFSDISK_HPP
#define __FCFSDISK_HPP

#include "AccessTime.hpp"
// #include "FCFSQueue.hpp"
#include "Queue.hpp"

#include <vector>

class DiskDone;

class Disk {

    public:
        Disk(): waitQueue(nullptr), accessTime(new AccessTime()), _diskType(0), state(0), _waitQueueLength(0), timeInSystemMin(0), timeInSystemMax(0), timeInSystemAvg(0),
        waitTimeMin(0), waitTimeMax(0), waitTimeAvg(0), serviceTimeMin(0), serviceTimeMax(0), serviceTimeAvg(0), numInQMax(0), numInQAvg(0) {}

        Disk( Queue * q, int diskType ): waitQueue(q), accessTime(new AccessTime()), _diskType(diskType), state(0), _waitQueueLength(0), timeInSystemMin(0), timeInSystemMax(0), timeInSystemAvg(0),
        waitTimeMin(0), waitTimeMax(0), waitTimeAvg(0), serviceTimeMin(0), serviceTimeMax(0), serviceTimeAvg(0), numInQMax(0), numInQAvg(0) {}

        int getDiskType() { return _diskType; }

        virtual Queue * getWaitQueue() { return waitQueue; }
        virtual DiskDone * processRequest(Request * ); //
        virtual DiskDone * processDiskDoneRequest ();//
        virtual void processTimerEvent(); //
        virtual void calculateDisk();//

        // virtual int& waitQueueLength() { return _waitQueueLength; }

        virtual std::vector<int> getTimer() { return timer; }
        virtual std::vector<double> getTimeInSystem() { return timeInSystem; }
        virtual std::vector<double> getWaitTime() { return waitTime; }
        virtual std::vector<double> getServiceTime() { return serviceTime; }

        virtual double getTimeInSystemMin () { return timeInSystemMin; }
        virtual double getTimeInSystemMax() { return timeInSystemMax; }
        virtual double getTimeInSystemAvg() { return timeInSystemAvg; }

        virtual double getWaitTimeMin() { return waitTimeMin; }
        virtual double getWaitTimeMax() { return waitTimeMax; }
        virtual double getWaitTimeAvg() { return waitTimeAvg; }

        virtual double getServiceTimeMin() { return serviceTimeMin; }
        virtual double getServiceTimeMax() { return serviceTimeMax; }
        virtual double getServiceTimeAvg() { return serviceTimeAvg; }

        virtual double getNumInQMax() { return numInQMax; }
        virtual double getNumInQAvg() { return numInQAvg; }

        virtual ~Disk();



    protected:
        Queue * waitQueue;
        AccessTime * accessTime;
        int state;
        int _waitQueueLength;
        int _diskType;

        std::vector <int> timer;
        std::vector <double> timeInSystem;
        std::vector <double> waitTime;
        std::vector <double> serviceTime;

        double timeInSystemMin, timeInSystemMax, timeInSystemAvg;
        double waitTimeMin, waitTimeMax, waitTimeAvg;
        double serviceTimeMin, serviceTimeMax, serviceTimeAvg;
        double numInQMax, numInQAvg;
        // int _processDiskDoneRequests;

};

#endif
