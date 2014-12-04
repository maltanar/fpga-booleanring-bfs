#include "aximasterwrapper.h"


// The purpose of this module is to bundle the individual AXI channel signals into bigger SystemC signals
// - broken-out signals on the Verilator-generated peripheral side
// - bundled signals on the "external" side

// Usage: call each setup*Channel function with the in/out ports of the Verilator-generated peripheral

AXIMasterWrapper::AXIMasterWrapper(sc_module_name name)
{
    // bind ready-valid I/Os for the bundled side to internal signals
    /*
    readAddrValid.bind(m_readAddr_VALID);
    readAddrReady.bind(m_readAddr_READY);

    readDataValid.bind(m_readData_VALID);
    readDataReady.bind(m_readData_READY);

    writeAddrValid.bind(m_writeAddr_VALID);
    writeAddrReady.bind(m_writeAddr_READY);

    writeDataValid.bind(m_writeData_VALID);
    writeDataReady.bind(m_writeData_READY);

    writeRespValid.bind(m_writeResp_VALID);
    writeRespReady.bind(m_writeResp_READY);
    */


    // declare the wrapper functions as SC_METHODs
    SC_METHOD(channelWrapReadAddress);
    sensitive << m_readAddr_READY << m_readAddr_VALID << m_readAddr_SIZE << m_readAddr_LEN << m_readAddr_PROT
              << m_readAddr_BURST << m_readAddr_LOCK << m_readAddr_CACHE << m_readAddr_QOS << m_readAddr_ID << m_readAddr_ADDR;

    SC_METHOD(channelWrapReadData);
    sensitive << readData;

    SC_METHOD(channelWrapWriteData);
    sensitive << m_writeData_DATA << m_writeData_LAST << m_writeData_STRB;

    SC_METHOD(channelWrapWriteAddress);
    sensitive << m_writeAddr_READY << m_writeAddr_VALID << m_writeAddr_SIZE << m_writeAddr_LEN << m_writeAddr_PROT
              << m_writeAddr_BURST << m_writeAddr_LOCK << m_writeAddr_CACHE << m_writeAddr_QOS << m_writeAddr_ID << m_writeAddr_ADDR;

    SC_METHOD(channelWrapWriteResponse);
    sensitive << writeResp;
}

void AXIMasterWrapper::channelWrapReadData()
{
    // move read data from bundled to broken-out
    AXIReadData data = readData.read();

    m_readData_DATA = data.data;
    m_readData_ID = data.id;
    m_readData_LAST = data.last;
    m_readData_RESP = data.resp;
}

void AXIMasterWrapper::channelWrapReadAddress()
{
    // move read address from broken-out to bundled
    AXIAddress addr;

    addr.addr = m_readAddr_ADDR;
    addr.burst = m_readAddr_BURST;
    addr.cache = m_readAddr_CACHE;
    addr.id = m_readAddr_ID;
    addr.len = m_readAddr_LEN;
    addr.lock = m_readAddr_LOCK;
    addr.prot = m_readAddr_PROT;
    addr.qos = m_readAddr_QOS;
    addr.size = m_readAddr_SIZE;

    readAddr.write(addr);
}

void AXIMasterWrapper::channelWrapWriteData()
{
    // move write data from broken-out to bundled
    AXIWriteData data;

    data.data = m_writeData_DATA;
    data.last = m_writeData_LAST;
    data.strb = m_writeData_STRB;

    writeData.write(data);
}

void AXIMasterWrapper::channelWrapWriteAddress()
{
    // move write address from broken-out to bundled
    AXIAddress addr;

    addr.addr = m_writeAddr_ADDR;
    addr.burst = m_writeAddr_BURST;
    addr.cache = m_writeAddr_CACHE;
    addr.id = m_writeAddr_ID;
    addr.len = m_writeAddr_LEN;
    addr.lock = m_writeAddr_LOCK;
    addr.prot = m_writeAddr_PROT;
    addr.qos = m_writeAddr_QOS;
    addr.size = m_writeAddr_SIZE;

    writeAddr.write(addr);
}

void AXIMasterWrapper::channelWrapWriteResponse()
{
    // move write response from bundled to broken-out
    AXIWriteResponse resp = writeResp.read();

    m_writeResp_ID = resp.id;
    m_writeResp_RESP = resp.resp;
}


// setup*Channel functions - bind specified I/O ports to corresponding internal signals of the module

void AXIMasterWrapper::setupReadAddrChannel(sc_in<bool> &ready, sc_out<bool> &valid, sc_out<unsigned int> &SIZE, sc_out<unsigned int> &LEN,
                                            sc_out<unsigned int> &PROT, sc_out<unsigned int> &BURST, sc_out<bool> &LOCK, sc_out<unsigned int> &CACHE,
                                            sc_out<unsigned int> &QOS, sc_out<unsigned int> &ID, sc_out<unsigned int> &ADDR)
{
    ready.bind(readAddrReady);
    valid.bind(readAddrValid);

    SIZE.bind(m_readAddr_SIZE);
    LEN.bind(m_readAddr_LEN);
    PROT.bind(m_readAddr_PROT);
    BURST.bind(m_readAddr_BURST);
    LOCK.bind(m_readAddr_LOCK);
    CACHE.bind(m_readAddr_CACHE);
    QOS.bind(m_readAddr_QOS);
    ID.bind(m_readAddr_ID);
    ADDR.bind(m_readAddr_ADDR);
}

void AXIMasterWrapper::setupReadDataChannel(sc_out<bool> &ready, sc_in<bool> &valid, sc_in<unsigned int> &ID, sc_in<bool> &LAST, sc_in<unsigned int> &RESP,
                                            sc_in<unsigned long> &DATA)
{
    ready.bind(readDataReady);
    valid.bind(readDataValid);

    ID.bind(m_readData_ID);
    LAST.bind(m_readData_LAST);
    RESP.bind(m_readData_RESP);
    DATA.bind(m_readData_DATA);
}

void AXIMasterWrapper::setupWriteDataChannel(sc_in<bool> &ready, sc_out<bool> &valid, sc_out<unsigned int> &STRB, sc_out<bool> &LAST, sc_out<unsigned long> &DATA)
{
    ready.bind(writeDataReady);
    valid.bind(writeDataValid);

    STRB.bind(m_writeData_STRB);
    LAST.bind(m_writeData_LAST);
    DATA.bind(m_writeData_DATA);
}

void AXIMasterWrapper::setupWriteAddrChannel(sc_in<bool> &ready, sc_out<bool> &valid, sc_out<unsigned int> &SIZE, sc_out<unsigned int> &LEN,
                                             sc_out<unsigned int> &PROT, sc_out<unsigned int> &BURST, sc_out<bool> &LOCK, sc_out<unsigned int> &CACHE,
                                             sc_out<unsigned int> &QOS, sc_out<unsigned int> &ID, sc_out<unsigned int> &ADDR)
{
    ready.bind(writeAddrReady);
    valid.bind(writeAddrValid);

    SIZE.bind(m_writeAddr_SIZE);
    LEN.bind(m_writeAddr_LEN);
    PROT.bind(m_writeAddr_PROT);
    BURST.bind(m_writeAddr_BURST);
    LOCK.bind(m_writeAddr_LOCK);
    CACHE.bind(m_writeAddr_CACHE);
    QOS.bind(m_writeAddr_QOS);
    ID.bind(m_writeAddr_ID);
    ADDR.bind(m_writeAddr_ADDR);
}

void AXIMasterWrapper::setupWriteRespChannel(sc_out<bool> &ready, sc_in<bool> &valid, sc_in<unsigned int> &ID, sc_in<unsigned int> &RESP)
{
    ready.bind(writeRespReady);
    valid.bind(writeRespValid);

    ID.bind(m_writeResp_ID);
    RESP.bind(m_writeResp_RESP);
}
