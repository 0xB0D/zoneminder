//ZoneMinder Packet Queue Interface Class
//Copyright 2016 Steve Gilvarry
//
//This file is part of ZoneMinder.
//
//ZoneMinder is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.
//
//ZoneMinder is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with ZoneMinder.  If not, see <http://www.gnu.org/licenses/>.


#ifndef ZM_PACKETQUEUE_H
#define ZM_PACKETQUEUE_H

//#include <boost/interprocess/managed_shared_memory.hpp>
//#include <boost/interprocess/containers/map.hpp>
//#include <boost/interprocess/allocators/allocator.hpp>
#include <list>
#include "zm_packet.h"
#include "zm_thread.h"

extern "C" {
#include <libavformat/avformat.h>
}

class zm_packetqueue {
  public: // For now just to ease development
    std::list<ZMPacket *>    pktQueue;
    std::list<ZMPacket *>::iterator analysis_it;

    int video_stream_id;
    int video_packet_count; // keep track of how many video packets we have, because we shouldn't have more than image_buffer_count
    int first_video_packet_index;
    int max_video_packet_count; // allow a negative value to someday mean unlimited

    Mutex mutex;

public:
    zm_packetqueue( int p_max_video_packet_count, int p_video_stream_id );
    virtual ~zm_packetqueue();

    bool queuePacket( ZMPacket* packet );
    ZMPacket * popPacket( );
    unsigned int clearQueue( unsigned int video_frames_to_keep, int stream_id );
    void clearQueue( );
    unsigned int size();
    unsigned int get_video_packet_count();
    void clear_unwanted_packets( timeval *recording, int mVideoStreamId );

    // Functions to manage the analysis frame logic
    bool increment_analysis_it();
    ZMPacket *get_analysis_packet();
};

#endif /* ZM_PACKETQUEUE_H */
