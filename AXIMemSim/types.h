#ifndef TYPES_H
#define TYPES_H


using namespace std;

typedef unsigned int MemAddress;
typedef unsigned int MemWord;


typedef struct {
    bool isWrite;
    MemWord writeData;
    MemAddress addr;
    unsigned int burstLen;
    unsigned int id;
} MemRequest;

typedef struct {
    bool isWrite;
    MemWord readData;
    unsigned int id;
    bool error;

    /*
    MemResponse& operator= (const MemResponse& rhs)
    {
        return *this;
    }

    bool operator== (const MemResponse& rhs) const
    {
        return true;
    }
    */
} MemResponse;

ostream& operator<< (ostream& file, const MemResponse& val);


#endif // TYPES_H
