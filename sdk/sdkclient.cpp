#include "sdkclient.h"

#include "../core/protocol.h"

CSDKClient::CSDKClient()
{
    _connection = new CNetClient();
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
    memcpy(_outPack.msg, msg, len);

    _outPack.flag = Protocol::F_SEND_MSG;
    _outPack.value = Protocol::V_OK;
    _outPack.size = len;

    return _fisim.send(*_connection, _outPack);
}

bool CSDKClient::sendMsgTo(char * msg, unsigned short int sender, unsigned short int receiver, size_t len)
{
    memcpy(_outPack.msg, msg, len);

    _outPack.flag = Protocol::F_FACETOFACE_MSG;
    _outPack.value = Protocol::V_OK;
    _outPack.sender = sender;
    _outPack.receiver = receiver;
    _outPack.size = len;

    return _fisim.send(*_connection, _outPack);
}

bool CSDKClient::checkInstance(unsigned short int number)
{
    _outPack.flag = Protocol::F_CHECK_INSTANCE;
    _outPack.value = Protocol::V_OK;
    _outPack.receiver = number;
    _outPack.size = 0;

    return _fisim.send(*_connection, _outPack);
}

bool CSDKClient::joinInstance(unsigned short int number)
{
    _outPack.flag = Protocol::F_JOIN_INSTANCE;
    _outPack.value = Protocol::V_OK;
    _outPack.receiver = number;
    _outPack.size = 0;

    return _fisim.send(*_connection, _outPack);
}

bool CSDKClient::leaveInstance()
{
    _outPack.flag = Protocol::F_LEAVE_INSTANCE;
    _outPack.value = Protocol::V_OK;
    _outPack.size = 0;

    return _fisim.send(*_connection, _outPack);
}

bool CSDKClient::createMulticastInstance()
{
    _outPack.flag = Protocol::F_CREATE_INSTANCE;
    _outPack.value = Protocol::V_MULTICAST_INSTANCE;
    _outPack.receiver = 0;
    _outPack.size = 0;

    return _fisim.send(*_connection, _outPack);
}

bool CSDKClient::createFaceToFaceInstance()
{
    _outPack.flag = Protocol::F_CREATE_INSTANCE;
    _outPack.value = Protocol::V_FACETOFACE_INSTANCE;
    _outPack.receiver = 0;
    _outPack.size = 0;

    return _fisim.send(*_connection, _outPack);
}

bool CSDKClient::recv(CCoreFisim::packet & pack)
{
    memset(&pack, 0, sizeof(struct CCoreFisim::packet));

    return _fisim.recv(*_connection, pack);
}
