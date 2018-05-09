#include <iostream>

// Forward Decleration
class Request;


/*
    DISK TYPES
    0 - NOTHING
    1 - FCFS
    2 - ST
    3 - PICK UP
    4 - LOOK UP
    5 - C LOOK
*/

class DiskDone {

public:
    DiskDone(): _time(0), _diskType(0) {}
    DiskDone(double time, int diskType): _time(time), _diskType(diskType) {}

    int getDiskType() { return _diskType; }
    double time() { return _time; }

private:
    double _time;
    int _diskType;
};
