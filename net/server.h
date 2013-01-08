#ifndef _NET_SERVER_CLASS_H_
#define _NET_SERVER_CLASS_H_

#include <vector>
#include "socket.h"
#include "client.h"

class CNetServer : public CNetSocket {

    public:
        CNetServer() : CNetSocket() {_clients.clear();}
        ~CNetServer();
        int bind(const char *, const int);
        int list(const int);
        CNetClient * accept();
        virtual void erase();
    protected:
        int _maxConnect;
        std::vector <CNetClient*> _clients;
        std::vector<CNetClient*>::iterator _iter;
};
#endif
