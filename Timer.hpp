#ifndef __TIMER_HPP
#define __TIMER_HPP

class Timer {

    public:
        Timer(): _time(0) {}
        Timer(double setTime): _time(setTime) {}
        double time() { return _time; }


    private:
        double _time;
};

#endif
