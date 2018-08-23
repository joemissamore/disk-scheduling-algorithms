# disk-scheduling-algorithms


Please use the following make commands to produce the appropiate report.



make fcfs_track.x
./fcfs_track < inputFile.in
Produces FCFS_OUTPUT


make same_track.x
./same_track.x < inputFile.in
Produces STRACK_OUTPUT


make pick_up.x
./pick_up.x < inputFile.in
Produces PICKUP_OUTPUT


make look_up.x
./look_up.x < inputFile.in
Produces LOOK_OUTPUT


make c_look.x
./c_look.x < inputFile.in
Produces CLOOK_OUTPUT


make simulation.x
./simulation < inputFile
Produces TIMER_OUTPUT and SUMMARY_OUTPUT

simulation.x runs a simulation of all the disks and there appropriate Queues simultaneously.
At run time the EventQueue is filled with the requests from the input file and then hands each request
read in from the file to each disk. From there the disk simulates the request based on the disk scheduling
algorithm it's responsible for.
