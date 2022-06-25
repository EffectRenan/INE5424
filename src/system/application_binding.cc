// EPOS Application Binding

#include <utility/spin.h>
#include <utility/ostream.h>
#include <architecture/cpu.h>
#include <system.h>

__BEGIN_SYS
__END_SYS

// Global objects
__BEGIN_SYS
OStream kerr;
__END_SYS

// Bindings
extern "C" {
    // Utility methods that differ from kernel and user space.
    // Heap
    static _UTIL::Simple_Spin _heap_spin;
    void _lock_heap() { _heap_spin.acquire(); }
    void _unlock_heap() { _heap_spin.release();}
    
    void _pre_main() {
        db<Init, Thread>(WRN) << "_pre_main: " << CPU::id() << endl;
        // CPU::smp_barrier();

        if (CPU::id() != 0) {
            Thread * thread = Thread::self();
            thread->idle();
            while(true);
        }
    }
    
}

__USING_SYS;
