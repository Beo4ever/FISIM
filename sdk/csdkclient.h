#ifndef _CSDKCLIENT_H_
#define _CSDKCLIENT_H_

#include "../net/client.h"
#include "../core/fisim.h"

class CSDKClient
{
public:
    CSDKClient();

    int connect(const char *);
    int disconnect();
    bool sendMsg(char * msg, size_t len);
    bool sendMsgTo(char * msg, unsigned short int sender, unsigned short int receiver, size_t len);
    bool checkInstance(unsigned short int number);
    bool joinInstance(unsigned short int number);
    bool createMulticastInstance();
    bool createFaceToFaceInstance();

    bool recv(CCoreFisim::packet & pack);

private:
    CNetClient * _connection;

    CCoreFisim * _fisim;
};

#endif // _CSDKCLIENT_H_
