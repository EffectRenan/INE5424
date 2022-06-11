#include <utility/ostream.h>
#include <architecture.h>
#include <time.h>

using namespace EPOS;

OStream cout;

#define CLASS0_MIN 8
#define CLASS0_MAX 18

#define CLASS1_MIN 8
#define CLASS1_MAX 17

#define CLASS2_MIN 8
#define CLASS2_MAX 9

#define WAITING_TIME 1 // In seconds. Make sure that simulation time is fair enough (traits).
#define CLASS_BITS 0xFF

#define ALLOW_EVENTS_TEST 0

void event_test(int min, int max, int event_class);

int main()
{
    cout << "CYCLES: "  << PMU::mcycle() << endl ; 
    cout << "INSTRUCTIONS: " << PMU::minstret() << endl << endl;

    if (ALLOW_EVENTS_TEST) {
        cout << "EVENTS TEST" << endl;

        cout << "------------------------------" << endl;
        event_test(CLASS0_MIN, CLASS0_MAX, 0);

        cout << "------------------------------" << endl;
        event_test(CLASS1_MIN, CLASS1_MAX, 1);
        
        cout << "------------------------------" << endl;
        event_test(CLASS2_MIN, CLASS2_MAX, 2);
    } else {
        cout << "Events (Instruction Commit, Microarchitectural and Memory System) are not implemented by QEMU to test!" << endl;
    }
        
    return 0;
}

void event_test(int min, int max, int event_class) {
    int event_offset;
    int channel;
    int read;

    // Monitoring each event in a different channel.
    for (int i = min; i <= max; i++) {
        event_offset = (1 << i);
        channel = i;
        PMU::config(channel, (event_offset | (event_class & CLASS_BITS)));
    }

    for (int i = min; i <= max; i++) {
        Delay waiting_events(WAITING_TIME * 100000);

        event_offset = (1 << i);
        channel = i;
        read = PMU::read(channel);
        cout << "Class: " << event_class <<  ", Offset: " << (i) << ", Read: " << read << endl;
        PMU::reset(channel);
        PMU::stop(channel);
    }
}
