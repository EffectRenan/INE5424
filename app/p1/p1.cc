#include <utility/ostream.h>
#include <architecture.h>
#include <time.h>
#include <process.h>

using namespace EPOS;

OStream cout;

Thread * threads[3];

int test(int data[]);

int main()
{
    cout << "TSC test: " << TSC::time_stamp() << endl << endl;

    cout << "Scheduler test" << endl << endl;

    int data[] = {1,0}; // IO
    threads[0] = new Thread(&test, data);

    int data1[] = {0,1};
    threads[1] = new Thread(&test, data1);

    int data2[] = {0,2};
    threads[2] = new Thread(&test, data2);

    //  
    threads[0]->join();
    threads[1]->join();
    threads[2]->join();
    
    delete threads[0];
    delete threads[1];
    delete threads[2];

    return 0;
}


int test(int data[]) {
    bool is_io = data[0];
    int id = data[1];

    cout << "Thread: " << id << endl;

    if (is_io) {
        cout << "Start IO: " << id << endl << endl;
        Delay eating(50000);
        cout << "End IO: " << id << endl << endl;
    } else {
        for (unsigned int i = 0; i < 2000000000; i++) {}
    }

    cout << "End thread: " << id << endl << endl;

    return 0;
}
