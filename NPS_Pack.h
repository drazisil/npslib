#ifndef _NPS_PACK_H
#define _NPS_PACK_H

#include <string.h>
struct MsgPack {};

struct _NPS_CommData
{
  long CommId;               // The ID of this channel (4)
  char Riff[32];    // The RIFF of this channel (32)
  long SlotNumber;                 // The slot for this user on this channel (4)
  long SlotFlags;                  // Flags that say how to act if a slot is 
                                   // unavailable (4)

  long Port;                       // The port this channel connected on (4)
  unsigned long Protocol;          // NPSTCP or NPSUDP (4)
  unsigned long UserId;               // ID of the owner of this channel (4)
  short ConnectedUsers;            // Number of people on this channel (2)
  short OpenChannels;              // Number of channels on this server (2)
  short CanReady;            // Able to ready for a game (2)
  short GameReady;           // Is the player ready for a game (2)
  short IsMaster;            // Are we the master in this game (2)
  short ChannelType;               // NPS_PUBLIC_CHANNEL, NPS_PRIVATE_CHANNEL,
                                   //  or NPS_OPAQUE_CHANNEL (2)
  char Password[17]; // The password if a private channel (8)
  short DisableBacklog;      // TRUE if backlogging messages is (2)
  char GameServerIsRunning;        // Game server state for this channel (1)
  char Dummy;                      // Alignment placeholder (1)
  short LaunchGameServer;    // TRUE if a game server should be launched
                                   //  at channel create (2)
  unsigned short MaxReadyPlayers;  // Max players allowed to ready (2)
  long SKU;                        // SKU of the game requesting launch (4)
  long SendRate;                   // If rate limiting, this is the rate. (4)
  char ChannelData[256]; // User settable channel info (256)
  unsigned long Flags;             // Flags associated with this channel (4)
  short MessageOnList;       // If rate limiting, this flag indicates 
                                   //  that a message is already on the pending
                                   //  message list for this user
  short IsBeingRemoved;      // TRUE if in process of being removed (2)
                                   //  this file has to be C compatible (4)
  unsigned short MetaMsgLen;           // Total length of all messages in
                                   //  MessagesToSend (2)
  short NumMetaMsg;                // Number of messages in MessagesToSend (2)
  
}
NPS_CommData;

class NPS_Pack
{
private:
    /* data */
public:
    NPS_Pack(/* args */);
    ~NPS_Pack();

    int pack(unsigned char *buf, int len, char *packcode, void* p4, void*p5,...);
    int unpack(NPS_Pack *param_1,unsigned char *data,int len,char *packcode,_NPS_CommData *dest,...);
};

NPS_Pack::NPS_Pack(/* args */)
{
}

NPS_Pack::~NPS_Pack()
{
}


#endif
