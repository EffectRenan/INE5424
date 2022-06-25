// EPOS System Binding

#include <utility/spin.h>
#include <machine.h>
#include <process.h>
#include <architecture.h>

// extern "C" {
//     __USING_SYS;

//     // Heap
//     static Spin _heap_lock;
//     void _lock_heap() { Thread::lock(&_heap_lock); }
//     void _unlock_heap() { Thread::unlock(&_heap_lock); }
//     
//     void _pre_main() {
//         db<Init, Thread>(WRN) << "_pre_main: " << CPU::id() << endl;
//         // CPU::smp_barrier();

//         if (CPU::id() != 0) {
//             Thread * thread = Thread::self();
//             thread->idle();
//             while(true);
//         }
//     }
// }

extern "C" {
    __USING_SYS;

    // Libc legacy
    void _panic() { Machine::panic(); }
    void _exit(int s) { Thread::exit(s); for(;;); }
    void __exit() { Thread::exit(CPU::fr()); }  // must be handled by the Page Fault handler for user-level tasks
    void __cxa_pure_virtual() { db<void>(ERR) << "Pure Virtual method called!" << endl; }

    // Utility-related methods that differ from kernel and user space.
    // OStream
    void _print(const char * s) { Display::puts(s); }
    static volatile int _print_lock = -1;
    void _print_preamble() {
        if(Traits<System>::multicore) {
            static char tag[] = "<0>: ";

            int me = CPU::id();
            int last = CPU::cas(_print_lock, -1, me);
            for(int i = 0, owner = last; (Traits<System>::hysterically_debugged || (i < 10)) && (owner != me); i++, owner = CPU::cas(_print_lock, -1, me));
            if(last != me) {
                tag[1] = '0' + CPU::id();
                _print(tag);
            }
        }
    }
    void _print_trailler(bool error) {
        if(Traits<System>::multicore) {
            static char tag[] = " :<0>";

            if(_print_lock != -1) {
                tag[3] = '0' + CPU::id();
                _print(tag);

                _print_lock = -1;
            }
        }
        if(error)
            _panic();
    }

    // Heap
    static Spin _heap_lock;
    void _lock_heap() { Thread::lock(&_heap_lock); }
    void _unlock_heap() { Thread::unlock(&_heap_lock); }
}
