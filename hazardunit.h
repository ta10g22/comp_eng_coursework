#ifndef HAZARDUNIT_H
#define HAZARDUNIT_H

#include "pipelineregs.h"

class HazardUnit {
public:
    HazardUnit();

    // Stall on load-use hazard
    bool detectLoadUse(const IFID& if_id, const IDEX& id_ex) const;

    // Forwarding selectors for ALU inputs:
    // 0 = no forward, 1 = from EX/MEM, 2 = from MEM/WB
    void computeForwarding(const IDEX& id_ex,
                           const EXMEM& ex_mem,
                           const MEMWB& mem_wb,
                           int& forwardA,
                           int& forwardB) const;
};

#endif // HAZARDUNIT_H
