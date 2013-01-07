#ifndef _CORE_FISIM_CLASS_H_
#define _CORE_FISIM_CLASS_H_

#include "../net/socket.h"
#include <string.h>

class CCoreFisim
{
    public:

	struct packet {
	    unsigned char flag;
	    unsigned char value;
	    unsigned short int sender;
	    unsigned short int receiver;
	    unsigned short int size;
	    char msg[4086];
	    packet () {memset(msg, 0, 4086);}
	};

	bool send(CNetSocket &, const struct packet &);
	bool recv(CNetSocket &, struct packet &);
	
	unsigned char * serializePack(const struct packet &, unsigned char *);
	unsigned char * deserializePack(const unsigned char *, struct packet &);
};

#endif