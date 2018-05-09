#include "LOOKUPQueue.hpp"
#include "Request.hpp"

#include <iostream>

int main() {

    LOOKUPQueue *queue = new LOOKUPQueue();

    double time;
    int track;
    int sector;




    int index = 1;
    while (1)
    {


        std::cin >> time;
        std::cin >> track;
        std::cin >> sector;
        if ( std::cin.eof() ) break; // so the results arent duplicated
        Request * req = new Request(time, track, sector, index);
        queue->addRequest(req);

        index++;

    }




    queue->print();


    delete queue;


    return 0;
}
