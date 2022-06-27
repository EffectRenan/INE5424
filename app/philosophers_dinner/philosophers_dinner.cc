// EPOS Scheduler Test Program

#include <machine/display.h>
#include <time.h>
#include <synchronizer.h>
#include <process.h>

using namespace EPOS;

const int iterations = 10;

Mutex table;

Thread * phil[5];
Semaphore * chopstick[5];

OStream cout;

int philosopher(int data[]);

int main()
{
    table.lock();
    Display::clear();
    Display::position(0, 0);
    cout << "The Philosopher's Dinner:" << endl;

    for(int i = 0; i < 5; i++)
        chopstick[i] = new Semaphore;

    int data[] = {0,  5, 32};
    phil[0] = new Thread(&philosopher, data);
    int data1[] = {1, 10, 44};
    phil[1] = new Thread(&philosopher, data1);
    int data2[] = {2, 16, 39};
    phil[2] = new Thread(&philosopher, data2);
    int data3[] = {3, 16, 24};
    phil[3] = new Thread(&philosopher, data3);
    int data4[] = {4, 10, 20};
    phil[4] = new Thread(&philosopher, data4);

    cout << "Philosophers are alive and hungry!" << endl;

    Display::position(7, 44);
    cout << '/';
    Display::position(13, 44);
    cout << '\\';
    Display::position(16, 35);
    cout << '|';
    Display::position(13, 27);
    cout << '/';
    Display::position(7, 27);
    cout << '\\';
    Display::position(19, 0);

    cout << "The dinner is served ..." << endl;
    table.unlock();

    for(int i = 0; i < 5; i++) {
        int ret = phil[i]->join();
        table.lock();
        Display::position(20 + i, 0);
        cout << "Philosopher " << i << " ate " << ret << " times " << endl;
        table.unlock();
    }

    for(int i = 0; i < 5; i++)
        delete chopstick[i];
    for(int i = 0; i < 5; i++)
        delete phil[i];

    cout << "The end!" << endl;

    return 0;
}

int philosopher(int data[])
{
    int n = data[0];
    int l = data[1];
    int c = data[2];
    int first = (n < 4)? n : 0;
    int second = (n < 4)? n + 1 : 4;

    for(int i = iterations; i > 0; i--) {

        table.lock();
        Display::position(l, c);
        cout << "thinking";
        table.unlock();

        Delay thinking(1000000);

        table.lock();
        Display::position(l, c);
        cout << " hungry ";
        table.unlock();

        chopstick[first]->p();   // get first chopstick
        chopstick[second]->p();  // get second chopstick

        table.lock();
        Display::position(l, c);
        cout << " eating ";
        table.unlock();

        Delay eating(500000);

        table.lock();
        Display::position(l, c);
        cout << "  sate  ";
        table.unlock();

        chopstick[first]->v();   // release first chopstick
        chopstick[second]->v();  // release second chopstick
    }

    table.lock();
    Display::position(l, c);
    cout << "  done  ";
    table.unlock();

    return iterations;
}
