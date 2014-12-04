#include <iostream>
#include "types.h"

using namespace std;

ostream &operator<<(ostream &file, const MemResponse &val)
{
    return file << "id: " << val.id << " readVal: " << val.readData << " isWrite: " << val.isWrite << endl;
}
