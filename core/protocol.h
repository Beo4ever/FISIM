#ifndef _CORE_PROTOCOL_STRUCT_H_
#define _CORE_PROTOCOL_STRUCT_H_

struct Protocol {

    // service flags
    static const unsigned short int
    V_ERROR = 0x00,
    V_OK = 0x01,
    V_NO = 0x02,
    V_SUCCESS = 0x03,

    //instances values
    V_MULTICAST_INSTANCE = 0x20,
    V_FACETOFACE_INSTANCE = 0x21,
    V_TRANSFER_INSTANCE = 0x22,
    V_STREAM_INSTANCE = 0x23,
    V_INSTANCE_IS_FULL = 0x28;

    static const unsigned short int
    //lobby flags
    F_CONNECT = 0x05,
    F_DISCONNECT = 0x06,

    //instance flags
    F_CREATE_INSTANCE = 0x0B,
    F_UPDATE_INSTANCE = 0x0C,
    F_DELETE_INSTANCE = 0x0D,
    F_PAUSE_INSTANCE = 0x0E,
    F_HIDE_INSTANCE = 0x0F,
    F_CHECK_INSTANCE = 0x10,
    F_LIST_INSTANCE = 0x11,
    F_INVITE_INSTANCE = 0x12,
    F_JOIN_INSTANCE = 0x13,
    F_LEAVE_INSTANCE = 0x14,

    //data flags
    F_SEND_MSG = 0x2A,
    F_FORWARD_MSG = 0x2B,
    F_VERIFY_MSG = 0x2C,
    F_MULTICAST_MSG = 0x2D,
    F_FACETOFACE_MSG = 0x3E;
};
#endif
