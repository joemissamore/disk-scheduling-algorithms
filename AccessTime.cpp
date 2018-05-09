#include "AccessTime.hpp"

void AccessTime::setSeekTime (int curr_track, int dest_track)
{
    seekTime = ( curr_track > dest_track ) ?  ( ( curr_track - dest_track ) * 3 ) :
        ( ( dest_track - curr_track ) * 3 );

    setCurTrack( dest_track );
}

void AccessTime::setRotationalDelay(int curr_sector, int dest_sector)
{
    int total_sectors = 30;

    rotationalDelay =  ( curr_sector > dest_sector ) ?
        ( ( ( total_sectors - curr_sector ) + dest_sector ) * 0.1 ) :
        ( ( dest_sector - curr_sector ) * 0.1 );

    setCurSector( dest_sector );
    // setAccessTime(); // ?

}
void AccessTime::setCurrentTime()
{
    currentTime = (accessTime == 0) ? ( currentTime = time ) : ( currentTime = getComp() );
}
