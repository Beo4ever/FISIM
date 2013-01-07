#include "csdkclient.h"

#include "../core/protocol.h"

CSDKClient::CSDKClient()
{
    _connection = new CNetClient();
    _fisim = new CCoreFisim();
}

int CSDKClient::connect(const char * address)
{
    if(_connection->isConnected()) {

        return 2;
    } else {
        try {
            if(! _connection->isValid()) {
                _connection = new CNetClient();
            }

            if(! _connection->connect(address, 2722)) {

                return 0;
            }
        } catch (NetException &e) {

            return 0;
        }
    }

    return 1;
}

int CSDKClient::disconnect()
{
    if(! _connection->isConnected()) {

        return 0;
    } else {
        try {
            if(! _connection->disconnect()) {

                return 2;
            }
        } catch (NetException &e) {

            return 2;
        }
    }

    return 1;
}

bool CSDKClient::sendMsg(char * msg, size_t len)
{
    CCoreFisim::packet outPack;

    memcpy(outPack.msg, msg, len);

    outPack.flag = Protocol::F_SEND_MSG;
    outPack.value = Protocol::V_OK;
    outPack.size = len;

    return _fisim->send(*_connection, outPack);
}

bool CSDKClient::sendMsgTo(char * msg, unsigned short int sender, unsigned short int receiver, size_t len)
{
    CCoreFisim::packet outPack;

    memcpy(outPack.msg, msg, len);

    outPack.flag = Protocol::F_FACETOFACE_MSG;
    outPack.value = Protocol::V_OK;
    outPack.sender = sender;
    outPack.receiver = receiver;
    outPack.size = len;

    return _fisim->send(*_connection, outPack);
}

bool CSDKClient::checkInstance(unsigned short int number)
{
    CCoreFisim::packet outPack;

    outPack.flag = Protocol::F_CHECK_INSTANCE;
    outPack.value = Protocol::V_OK;
    outPack.receiver = number;
    outPack.size = 0;

    return _fisim->send(*_connection, outPack);
}

bool CSDKClient::joinInstance(unsigned short int number)
{
    CCoreFisim::packet outPack;

    outPack.flag = Protocol::F_JOIN_INSTANCE;
    outPack.value = Protocol::V_OK;
    outPack.receiver = number;
    outPack.size = 0;

    return _fisim->send(*_connection, outPack);
}

bool CSDKClient::createMulticastInstance()
{
    CCoreFisim::packet outPack;

    outPack.flag = Protocol::F_CREATE_INSTANCE;
    outPack.value = Protocol::V_MULTICAST_INSTANCE;
    outPack.receiver = 0;
    outPack.size = 0;

    return _fisim->send(*_connection, outPack);
}

bool CSDKClient::createFaceToFaceInstance()
{
    CCoreFisim::packet outPack;

    outPack.flag = Protocol::F_CREATE_INSTANCE;
    outPack.value = Protocol::V_FACETOFACE_INSTANCE;
    outPack.receiver = 0;
    outPack.size = 0;

    return _fisim->send(*_connection, outPack);
}

bool CSDKClient::recv(CCoreFisim::packet & pack)
{
    memset(&pack, 0, sizeof(struct CCoreFisim::packet));
    return _fisim->recv(*_connection, pack);
}
