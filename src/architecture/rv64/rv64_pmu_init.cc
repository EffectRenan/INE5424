// EPOS RV64 PMU Mediator Initialization

#include <architecture/pmu.h>

#ifdef __riscv__

__BEGIN_SYS

void RV64_PMU::init()
{
    db<Init, PMU>(TRC) << "PMU::init()" << endl;
}

__END_SYS

#endif
