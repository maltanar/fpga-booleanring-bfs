#ifndef AXIMASTERWRAPPER_H
#define AXIMASTERWRAPPER_H

#include "types.h"
#include "params.h"

#include <systemc.h>

#define uint32_t    unsigned int
#define vluint64_t  unsigned long int

class AXIMasterWrapper : public sc_module
{
    SC_HAS_PROCESS(AXIMasterWrapper);

public:
    AXIMasterWrapper(sc_module_name name);


    void setupReadAddrChannel(sc_in<bool> & ready, sc_out<bool> & valid,
                              sc_out<uint32_t> &	SIZE,
                              sc_out<uint32_t> &	LEN,
                              sc_out<uint32_t> &	PROT,
                              sc_out<uint32_t> &	BURST,
                              sc_out<bool>     &	LOCK,
                              sc_out<uint32_t> &	CACHE,
                              sc_out<uint32_t> &	QOS,
                              sc_out<uint32_t> &	ID,
                              sc_out<uint32_t> &	ADDR);

    void setupReadDataChannel(sc_out<bool> & ready, sc_in<bool> & valid,
                              sc_in<uint32_t>   &   ID,
                              sc_in<bool>       &   LAST,
                              sc_in<uint32_t>   &   RESP,
                              sc_in<vluint64_t> &	DATA);

    void setupWriteDataChannel(sc_in<bool> & ready, sc_out<bool> & valid,
                               sc_out<uint32_t>   &	STRB,
                               sc_out<bool>       &	LAST,
                               sc_out<vluint64_t> & DATA);

    void setupWriteAddrChannel(sc_in<bool> & ready, sc_out<bool> & valid,
                               sc_out<uint32_t> &	SIZE,
                               sc_out<uint32_t> &	LEN,
                               sc_out<uint32_t> &	PROT,
                               sc_out<uint32_t> &	BURST,
                               sc_out<bool>     &	LOCK,
                               sc_out<uint32_t> &	CACHE,
                               sc_out<uint32_t> &	QOS,
                               sc_out<uint32_t> &	ID,
                               sc_out<uint32_t> &	ADDR);

    void setupWriteRespChannel(sc_out<bool> & ready, sc_in<bool> & valid,
                               sc_in<uint32_t>   &   ID,
                               sc_in<uint32_t>   &   RESP);

    // SystemC methods for the adapter
    void channelWrapReadData();
    void channelWrapReadAddress();
    void channelWrapWriteData();
    void channelWrapWriteAddress();
    void channelWrapWriteResponse();

    // read address channel
    sc_out<AXIAddress> readAddr;
    sc_out<bool> readAddrValid;
    sc_in<bool> readAddrReady;

    // read data channel
    sc_in<AXIReadData> readData;
    sc_in<bool> readDataValid;
    sc_out<bool> readDataReady;

    // write address channel
    sc_out<AXIAddress> writeAddr;
    sc_out<bool> writeAddrValid;
    sc_in<bool> writeAddrReady;

    // write data channel
    sc_out<AXIWriteData> writeData;
    sc_out<bool> writeDataValid;
    sc_in<bool> writeDataReady;

    // write response channel
    sc_in<AXIWriteResponse> writeResp;
    sc_in<bool> writeRespValid;
    sc_out<bool> writeRespReady;

protected:
    // internal signals for wrapping
    // read address channel signals
    sc_signal<bool>	m_readAddr_READY;
    sc_signal<bool>	m_readAddr_VALID;
    sc_signal<uint32_t>	m_readAddr_SIZE;
    sc_signal<uint32_t>	m_readAddr_LEN;
    sc_signal<uint32_t>	m_readAddr_PROT;
    sc_signal<uint32_t>	m_readAddr_BURST;
    sc_signal<bool>	m_readAddr_LOCK;
    sc_signal<uint32_t>	m_readAddr_CACHE;
    sc_signal<uint32_t>	m_readAddr_QOS;
    sc_signal<uint32_t>	m_readAddr_ID;
    sc_signal<uint32_t>	m_readAddr_ADDR;

    // read data channel signals
    sc_signal<bool>	m_readData_READY;
    sc_signal<bool>	m_readData_VALID;
    sc_signal<uint32_t>	m_readData_ID;
    sc_signal<bool>	m_readData_LAST;
    sc_signal<uint32_t>	m_readData_RESP;
    sc_signal<vluint64_t>	m_readData_DATA;

    // write address channel signals
    sc_signal<bool>	m_writeAddr_READY;
    sc_signal<bool>	m_writeAddr_VALID;
    sc_signal<uint32_t>	m_writeAddr_SIZE;
    sc_signal<uint32_t>	m_writeAddr_LEN;
    sc_signal<uint32_t>	m_writeAddr_PROT;
    sc_signal<uint32_t>	m_writeAddr_BURST;
    sc_signal<bool>	m_writeAddr_LOCK;
    sc_signal<uint32_t>	m_writeAddr_CACHE;
    sc_signal<uint32_t>	m_writeAddr_QOS;
    sc_signal<uint32_t>	m_writeAddr_ID;
    sc_signal<uint32_t>	m_writeAddr_ADDR;

    // write data channel signals
    sc_signal<bool>	m_writeData_READY;
    sc_signal<bool>	m_writeData_VALID;
    sc_signal<uint32_t>	m_writeData_STRB;
    sc_signal<bool>	m_writeData_LAST;
    sc_signal<vluint64_t> m_writeData_DATA;

    // write response channel signals
    sc_signal<bool>	m_writeResp_READY;
    sc_signal<bool>	m_writeResp_VALID;
    sc_signal<uint32_t>	m_writeResp_ID;
    sc_signal<uint32_t>	m_writeResp_RESP;
};

#endif // AXIMASTERWRAPPER_H
