#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <QtGlobal>

// Both projects MUST include the same protocol.h.
// These values preserve the packet format from your uploaded code.
namespace Protocol
{
constexpr quint16 TCP_PORT = 4001;
constexpr quint16 UDP_PORT = 4002;
constexpr quint8 CMD_ADD = 0x01;
constexpr quint8 CMD_UPDATE = 0x02;
constexpr quint8 CMD_DELETE = 0x03;
constexpr quint8 ACK_FAIL = 0x00;
constexpr quint8 ACK_SUCCESS = 0xFF;
}

// A compiler normally adds gaps (padding) between some struct members.
// Packing removes those gaps so the packet has the expected byte count.
// This still uses the computer's native byte order and float representation:
// use matching architectures for this exercise (see README).
#pragma pack(push, 1)
struct AddDataCmd
{
    quint8 cmdID;       // ADD or UPDATE; both carry the same fields.
    quint32 UniqueID;   // Fixed 32-bit unsigned ID.
    float lat;
    float longitude;   // 'long' cannot be used as a name: it is a C++ keyword.
    char comment[50];   // UTF-8 text: up to 49 bytes plus a zero terminator.
};

struct DeleteDataCmd
{
    quint8 cmdID;
    quint32 UniqueID;
};

struct AddDataResp
{
    quint8 respID;      // Echoes the command ID.
    quint8 Ack;         // 0x00 = failed, 0xFF = successful.
    quint32 UniqueID;
    float lat;
    float longitude;
    char comment[50];
};

struct DeleteDataResp
{
    quint8 respID;
    quint8 Ack;
    quint32 UniqueID;
};
#pragma pack(pop) // Restore normal alignment for any later structs.

// Compile-time checks: a build fails if a packet layout changes accidentally.
static_assert(sizeof(float) == 4, "Protocol needs 4-byte floats");
static_assert(sizeof(AddDataCmd) == 63, "Unexpected ADD/UPDATE command size");
static_assert(sizeof(DeleteDataCmd) == 5, "Unexpected DELETE command size");
static_assert(sizeof(AddDataResp) == 64, "Unexpected ADD/UPDATE response size");
static_assert(sizeof(DeleteDataResp) == 6, "Unexpected DELETE response size");
#endif
