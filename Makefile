CFLAGS=-std=c++11 -ggdb

FCFSOBJECTS=FCFSQueueNode.o FCFSQueue.o main_FCFS.o AccessTime.o
STRACKOBJECTS=FCFSQueueNode.o STRACKQueue.o main_STRACK.o AccessTime.o
PICKUPOBJECTS=FCFSQueueNode.o PICKUPQueue.o main_PICKUP.o AccessTime.o
LOOKUPOBJECTS=FCFSQueueNode.o LOOKUPQueue.o main_LOOKUP.o AccessTime.o
CLOOKOBJECTS=FCFSQueueNode.o CLOOKQueue.o main_CLOOK.o AccessTime.o
MAINOBJECTS=FCFSQueueNode.o EventQueue.o FCFSQueue.o STRACKQueue.o PICKUPQueue.o LOOKUPQueue.o CLOOKQueue.o main.o AccessTime.o Disk.o

fcfs_track.x: $(FCFSOBJECTS)
	g++ $(CFLAGS) $(FCFSOBJECTS) -o fcfs_test.x

same_track.x: $(STRACKOBJECTS)
	g++ $(CFLAGS) $(STRACKOBJECTS) -o same_track.x

pick_up.x: $(PICKUPOBJECTS)
	g++ $(CFLAGS) $(PICKUPOBJECTS) -o pick_up.x

look_up.x: $(LOOKUPOBJECTS)
	g++ $(CFLAGS) $(LOOKUPOBJECTS) -o look_up.x

c_look.x: $(CLOOKOBJECTS)
	g++ $(CFLAGS) $(CLOOKOBJECTS) -o c_look.x

simulation.x: $(MAINOBJECTS)
	g++ $(CFLAGS) $(MAINOBJECTS) -o simulation.x

AccessTime.o: AccessTime.cpp AccessTime.hpp
	g++ $(CFLAGS) -c AccessTime.cpp -o AccessTime.o

main.o: main.cpp EventQueue.hpp EventQueue.cpp
	g++ $(CFLAGS) -c main.cpp -o main.o

Disk.o: Disk.cpp Disk.hpp
	g++ $(CFLAGS) -c Disk.cpp -o Disk.o

EventQueue.o: EventQueue.cpp EventQueue.hpp EventQueueNode.hpp
	g++ $(CFLAGS) -c EventQueue.cpp -o EventQueue.o

CLOOKQueue.o: CLOOKQueue.cpp CLOOKQueue.hpp FCFSQueueNode.hpp AccessTime.hpp
	g++ $(CFLAGS) -c CLOOKQueue.cpp -o CLOOKQueue.o

main_CLOOK.o: main_CLOOK.cpp CLOOKQueue.hpp CLOOKQueue.cpp
	g++ $(CFLAGS) -c main_CLOOK.cpp -o main_CLOOK.o

LOOKUPQueue.o: LOOKUPQueue.cpp LOOKUPQueue.hpp FCFSQueueNode.hpp AccessTime.hpp
	g++ $(CFLAGS) -c LOOKUPQueue.cpp -o LOOKUPQueue.o

main_LOOKUP.o: main_LOOKUP.cpp LOOKUPQueue.hpp LOOKUPQueue.cpp
	g++ $(CFLAGS) -c main_LOOKUP.cpp -o main_LOOKUP.o

PICKUPQueue.o: PICKUPQueue.cpp PICKUPQueue.hpp FCFSQueueNode.hpp AccessTime.hpp
	g++ $(CFLAGS) -c PICKUPQueue.cpp -o PICKUPQueue.o

main_PICKUP.o: main_PICKUP.cpp PICKUPQueue.hpp PICKUPQueue.cpp
		g++ $(CFLAGS) -c main_PICKUP.cpp -o main_PICKUP.o

STRACKQueue.o: STRACKQueue.cpp STRACKQueue.hpp FCFSQueueNode.hpp AccessTime.hpp
	g++ $(CFLAGS) -c STRACKQueue.cpp -o STRACKQueue.o

main_STRACK.o: main_STRACK.cpp STRACKQueue.hpp STRACKQueue.cpp
	g++ $(CFLAGS) -c main_STRACK.cpp -o main_STRACK.o

FCFSQueueNode.o: FCFSQueueNode.cpp FCFSQueueNode.hpp
	g++ $(CFLAGS) -c FCFSQueueNode.cpp -o FCFSQueueNode.o

FCFSQueue.o: FCFSQueue.cpp FCFSQueue.hpp FCFSQueueNode.hpp AccessTime.hpp
	g++ $(CFLAGS) -c FCFSQueue.cpp -o FCFSQueue.o

main_FCFS.o: main_FCFS.cpp FCFSQueue.hpp FCFSQueueNode.hpp
	g++ $(CFLAGS) -c main_FCFS.cpp -o main_FCFS.o

clean:
	rm -fr *~ *.x *.o *_OUTPUT
