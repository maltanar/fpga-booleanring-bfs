#ifndef AXITYPES_H
#define AXITYPES_H

#include <systemc.h>

using namespace std;

// many of these signals are much less than 32 bits, but Verilator expands them to
// 32 bits anyway, so that's how we define them here

// AXI address channel types
typedef unsigned int    AXIAddressAddr;
typedef unsigned int    AXIAddrSize;
typedef unsigned int    AXIAddrLen;
typedef unsigned int    AXIAddrProt;
typedef unsigned int    AXIAddrBurst;
typedef bool            AXIAddrLock;
typedef unsigned int    AXIAddrCache;
typedef unsigned int    AXIAddrQoS;
typedef unsigned int    AXIAddrID;

// AXI write data channel types
typedef unsigned long int   AXIWriteDataData;
typedef unsigned int        AXIWriteStrobe;
typedef bool                AXIWriteLast;

// AXI write response channel types
typedef unsigned int    AXIWriteRespID;
typedef unsigned int    AXIWriteRespResp;

// AXI read data channel types
typedef unsigned long int   AXIReadDataData;
typedef unsigned int        AXIReadDataID;
typedef bool                AXIReadDataLast;
typedef unsigned int        AXIReadDataResp;


// AXI channel type definitions

typedef struct AXIAddress {
    AXIAddressAddr  addr;
    AXIAddrSize     size;
    AXIAddrLen      len;
    AXIAddrProt     prot;
    AXIAddrBurst    burst;
    AXIAddrLock     lock;
    AXIAddrCache    cache;
    AXIAddrQoS      qos;
    AXIAddrID       id;

    AXIAddress& operator= (const AXIAddress& rhs)
    {
        addr = rhs.addr;
        size = rhs.size;
        len = rhs.len;
        prot = rhs.prot;
        burst = rhs.burst;
        lock = rhs.lock;
        cache = rhs.cache;
        qos = rhs.qos;
        id = rhs.id;

        return *this;
    }

    bool operator== (const AXIAddress& rhs) const
    {
        return  (addr == rhs.addr) &&
                (size == rhs.size) &&
                (len == rhs.len) &&
                (prot == rhs.prot) &&
                (burst == rhs.burst) &&
                (lock == rhs.lock) &&
                (cache == rhs.cache) &&
                (qos == rhs.qos) &&
                (id == rhs.id);
    }

} AXIAddress;

ostream& operator<< (ostream& file, const AXIAddress& val);
void sc_trace(sc_trace_file *& tf, const AXIAddress& val, std::string nm);


typedef struct AXIWriteData {
    AXIWriteDataData    data;
    AXIWriteStrobe      strb;
    AXIWriteLast        last;

    AXIWriteData& operator= (const AXIWriteData& rhs)
    {
        data = rhs.data;
        strb = rhs.strb;
        last = rhs.last;

        return *this;
    }

    bool operator== (const AXIWriteData& rhs) const
    {
        return (data == rhs.data) && (strb == rhs.strb) && (last == rhs.last);
    }

} AXIWriteData;

ostream& operator<< (ostream& file, const AXIWriteData& val);
void sc_trace(sc_trace_file *& tf, const AXIWriteData& val, std::string nm);

typedef struct  AXIWriteResponse {
    AXIWriteRespID      id;
    AXIWriteRespResp    resp;

    AXIWriteResponse& operator= (const AXIWriteResponse& rhs)
    {
        id = rhs.id;
        resp = rhs.resp;

        return *this;
    }

    bool operator== (const AXIWriteResponse& rhs) const
    {
        return (id == rhs.id) && (resp == rhs.resp);
    }

} AXIWriteResponse;

ostream& operator<< (ostream& file, const AXIWriteResponse& val);
void sc_trace(sc_trace_file *& tf, const AXIWriteResponse& val, std::string nm);

typedef struct AXIReadData {
    AXIReadDataData     data;
    AXIReadDataID       id;
    AXIReadDataLast     last;
    AXIReadDataResp     resp;

    AXIReadData& operator= (const AXIReadData& rhs)
    {
        data = rhs.data;
        id = rhs.id;
        last = rhs.last;
        resp = rhs.resp;

        return *this;
    }

    bool operator== (const AXIReadData& rhs) const
    {
        return (data == rhs.data) && (id == rhs.id) && (last == rhs.last) && (resp == rhs.resp);
    }

} AXIReadData;

ostream& operator<< (ostream& file, const AXIReadData& val);
void sc_trace(sc_trace_file *& tf, const AXIReadData& val, std::string nm);

#endif // AXITYPES_H
