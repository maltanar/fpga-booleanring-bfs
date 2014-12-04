#ifndef AXISLAVE_H
#define AXISLAVE_H

#include "types.h"
#include "params.h"

#include <systemc.h>


class AXISlave : public sc_module
{
    SC_HAS_PROCESS(AXISlave);

public:
    AXISlave(sc_module_name name);

    sc_in_clk clk;



};

#endif // AXISLAVE_H
