#if defined(_WIN32) || defined(WIN32)
#include "../stdafx.h"
#endif
#include "fisim.h"
#include <errno.h>
#include <iostream>

bool CCoreFisim::send(CNetSocket & sock, const struct packet & pack)
{
    size_t len;
    unsigned char buffer[4096];

    unsigned char * ptr = serializePack(pack, buffer);
    len = ptr - buffer;
    return (sock.send((const char *)buffer, len) > 0);
}

bool CCoreFisim::recv(CNetSocket & sock, struct packet & pack)
{
    size_t len = 4096;
    int result;
    unsigned char buffer[4096];
    memset(buffer, 0, len);

    result = sock.recv((char *)buffer, len);
    deserializePack(buffer, pack);

    if(result < 0 || result == 0) {
        if(errno != EWOULDBLOCK) {
            sock.erase();
        }

        return false;
    }

    return true;
}

unsigned char * CCoreFisim::serializePack(const struct packet & pack, unsigned char * buffer)
{
    memset(buffer, 0, 4096);

    size_t size = (pack.size > Protocol::V_MAX_MSG_SIZE) ?
                    Protocol::V_MAX_MSG_SIZE :
                    pack.size;

    buffer[0] = pack.flag;
    buffer[1] = pack.value;
    buffer[2] = pack.sender >> 8;
    buffer[3] = (unsigned char) pack.sender;
    buffer[4] = pack.receiver >> 8;
    buffer[5] = (unsigned char) pack.receiver;
    buffer[6] = size >> 8;
    buffer[7] = (unsigned char) size;
    
    if(pack.size > 0) {
        memcpy(buffer + 8, pack.msg, size);
    }

    return buffer + 8 + size;
}

unsigned char * CCoreFisim::deserializePack(const unsigned char * buffer, struct packet & pack)
{
    memset(&pack, 0, sizeof(struct packet));

    pack.flag = buffer[0];
    pack.value = buffer[1];
    pack.sender = buffer[2] << 8;
    pack.sender += buffer[3];
    pack.receiver = buffer[4] << 8;
    pack.receiver += buffer[5];
    pack.size = buffer[6] << 8;
    pack.size += buffer[7];
    if(pack.size > Protocol::V_MAX_MSG_SIZE) {
        pack.size = Protocol::V_MAX_MSG_SIZE;
    }
    if(pack.size > 0) {
        memcpy(pack.msg, buffer + 8, pack.size);
    }

    return (unsigned char *)buffer;
}
