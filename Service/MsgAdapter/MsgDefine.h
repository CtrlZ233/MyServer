#ifndef MSG_DEFINE_H_
#define MSG_DEFINE_H_

namespace MessageAdapter {
    enum MsgType {
        CONNECTION,
        DISCONNECTION,
        REGISTER_REQ,
        LOGIN_REQ,
        MSGTYPE_BOTTOM
    };

    enum ResponseCode {
        OK,
        INVALID_REQ,
        SERVER_ERR,
        CONN_MAX,
        REQ_FAILED,
        ResponseCode_BOTTOM
    };

    enum ReqPos {
        MSG_TYPE,
        PID_0,
        PID_1,
        PID_2,
        PID_3,
        DATA,
        POS_BOTTOM
    };
}

#endif