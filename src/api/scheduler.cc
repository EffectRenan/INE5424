// EPOS CPU Scheduler Component Implementation

#include <process.h>
#include <time.h>

__BEGIN_SYS

// The following Scheduling Criteria depend on Alarm, which is not available at scheduler.h
template <typename ... Tn>
FCFS::FCFS(int p, Tn & ... an): Priority((p == IDLE) ? IDLE : Alarm::elapsed()) {}

// Since the definition above is only known to this unit, forcing its instantiation here so it gets emitted in scheduler.o for subsequent linking with other units is necessary.
template FCFS::FCFS<>(int p);

template <typename ... Tn>
PP::PP(int p, Tn & ... an): Priority((p == IDLE) ? IDLE : p) {}

// Since the definition above is only known to this unit, forcing its instantiation here so it gets emitted in scheduler.o for subsequent linking with other units is necessary.
template PP::PP<>(int p);

bool PP::award(bool end) {
    db<PP>(TRC) << "PP award" << endl;

    if (!end)
        _priority = HIGH;

    return !end;
}

template MW::MW<>(int p, int q);

bool MW::charge(int state) {

    if (state != 0)
        db<MW>(TRC) << "MW charge: " << state << endl;

    if (_priority_class != MAIN && _priority_class != IDLE) {
        db<MW>(TRC) << "class: " <<  _priority_class << " | priority: " << _priority_base << endl;
        if (state == Thread::SUSPENDED) {
            // If quantum expires, priority lowered, but never below base
            decrease_priority();
        } else if (state == Thread::WAITING) {
            // If wait occurs, priority boosted depending on what was waited for
            increase_priority();
        }
    }

    return true;
}

void MW::decrease_priority() {
    if (_priority_base > NORMAL_PRIORITY) {
        _priority = actual_priority(_priorities[_priority_class][--_priority_base]);
    }
}

void MW::increase_priority() {
    if (_priority_base < HIGH_PRIORITY) {
        _priority = actual_priority(_priorities[_priority_class][++_priority_base]);
    }
}

int MW::actual_priority(int priority) {
    
    db<MW>(WRN) << "MW actual: " << priority << endl;
    if (priority == 0) { // MAIN
        return 0;
    }

    int p = (_priority_class + QTT_PRIORITIES) * priority;
    db<MW>(TRC) << "actual priority: " << p << endl;
    return p;
}

__END_SYS
