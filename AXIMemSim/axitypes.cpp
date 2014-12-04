#include "axitypes.h"


ostream &operator<<(ostream &file, const AXIAddress &val)
{
    return file << "addr: " << val.addr << " id: " << val.id << endl;
}


void sc_trace(sc_trace_file *&tf, const AXIAddress &val, std::string nm)
{

}


ostream &operator<<(ostream &file, const AXIWriteData &val)
{
    return file << "writeData: " << val.data << endl;
}


void sc_trace(sc_trace_file *&tf, const AXIWriteData &val, std::string nm)
{

}


ostream &operator<<(ostream &file, const AXIWriteResponse &val)
{
    return file << "writeResp: " << val.resp << " id: " << val.id << endl;
}


void sc_trace(sc_trace_file *&tf, const AXIWriteResponse &val, std::string nm)
{

}


ostream &operator<<(ostream &file, const AXIReadData &val)
{
    return file << "readData: " << val.data << " id: " << val.id << endl;
}


void sc_trace(sc_trace_file *&tf, const AXIReadData &val, std::string nm)
{

}
