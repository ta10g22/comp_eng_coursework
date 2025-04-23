#include "hazardunit.h"

HazardUnit::HazardUnit() {}

bool HazardUnit::detectLoadUse(const IFID& if_id, const IDEX& id_ex) const {
    if (id_ex.valid && id_ex.opcode == "lw") {
        int loadReg = id_ex.rt;
        int rs = if_id.instr.rs;
        int rt = if_id.instr.rt;
        if (loadReg != 0 && (loadReg == rs || loadReg == rt)) {
            return true;  // must stall
        }
    }
    return false;
}

void HazardUnit::computeForwarding(const IDEX& id_ex,
                                   const EXMEM& ex_mem,
                                   const MEMWB& mem_wb,
                                   int& forwardA,
                                   int& forwardB) const {
    forwardA = forwardB = 0;
    int rs = id_ex.rs, rt = id_ex.rt;

    // Check EX/MEM stage
    if (ex_mem.valid && ex_mem.writeReg != 0) {
        if (ex_mem.writeReg == rs) forwardA = 1;
        if (ex_mem.writeReg == rt) forwardB = 1;
    }
    // Check MEM/WB stage
    if (mem_wb.valid && mem_wb.writeReg != 0) {
        if (forwardA == 0 && mem_wb.writeReg == rs) forwardA = 2;
        if (forwardB == 0 && mem_wb.writeReg == rt) forwardB = 2;
    }
}