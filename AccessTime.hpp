#ifndef __ACCESSTIME_HPP
#define __ACCESSTIME_HPP

class AccessTime
{

public:
    AccessTime(): seekTime(0), rotationalDelay(0), accessTime(0), time(0), currentTime(0), curTrack(0), curSector(0), comp(0), wait(0), TmInSys(0) {}

    // void dist (int curr_track, int dest_track);
    void setSeekTime (int curr_track, int dest_track);
    void setRotationalDelay(int curr_sector, int dest_sector);
    void setAccessTime() { accessTime = seekTime + rotationalDelay + 0.1; }
    void setTime(double _time) { time = _time * 0.1; }
    void setCurrentTime();

    void setCurSector (int _set) { curSector = _set; }
    void setCurTrack ( int _set) { curTrack = _set; }

    void setComp() { comp = accessTime + currentTime; }

    void setWait() { wait = currentTime - time; }

    void setTmInSys() { TmInSys = getComp() - getTime(); }

    //Getters
    double getSeekTime() { return seekTime; }
    double getRotationalDelay() { return rotationalDelay; }
    double getAccessTime() { return accessTime; }
    double getTime() { return time; }
    double getCurTime() { return currentTime; }
    double getComp() { return comp; }
    double getWait() { return wait; }
    double getTmInSys() { return TmInSys; }

    int getCurSector () { return curSector; }
    int getCurTrack () { return curTrack; }





private:
    // int distance;
    double seekTime;
    double rotationalDelay;
    double accessTime;
    double time; //init
    double currentTime;
    double wait;
    double comp;
    double TmInSys;

    int curTrack;
    int curSector;

//
};

#endif
