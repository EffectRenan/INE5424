#include <architecture.h>
#include <process.h>
#include <time.h>
#include <utility/ostream.h>

using namespace EPOS;

OStream cout;


#define HIGH 2
#define ABOVE 3
#define NORMAL 4

Thread *threads[10];

int test(int id);
int test2(int id);

int main() {

  cout << "Windows scheduler test" << endl << endl;

  threads[0] = new Thread(Thread::Configuration(Thread::READY, Thread::Criterion(NORMAL)), &test, 1); // 
  threads[1] = new Thread(Thread::Configuration(Thread::READY, Thread::Criterion(ABOVE)), &test, 2); // 
  threads[2] = new Thread(Thread::Configuration(Thread::READY, Thread::Criterion(HIGH)), &test, 3); // 
  threads[3] = new Thread(Thread::Configuration(Thread::READY, Thread::Criterion(HIGH)), &test, 4); // 
  threads[4] = new Thread(Thread::Configuration(Thread::READY, Thread::Criterion(HIGH)), &test, 5); // 
  threads[5] = new Thread(Thread::Configuration(Thread::READY, Thread::Criterion(HIGH)), &test, 6); // 
  threads[6] = new Thread(Thread::Configuration(Thread::READY, Thread::Criterion(HIGH)), &test, 7); // 
  threads[7] = new Thread(Thread::Configuration(Thread::READY, Thread::Criterion(HIGH)), &test, 8); // 
  threads[8] = new Thread(Thread::Configuration(Thread::READY, Thread::Criterion(HIGH)), &test, 9); // 
  threads[9] = new Thread(Thread::Configuration(Thread::READY, Thread::Criterion(HIGH)), &test, 10); // 

  for (int i = 0 ; i < 10; i++) {
      threads[i]->join();
      delete threads[i];
  }

  return 0;
}

int test(int id) {

  cout << "Init thread: " << id << endl;
  for (int i = 0; i < 1000000000; i++) {}
  Delay eating(100000);

  cout << "End Thread:" << id << endl;

  return 0;
}

int test2(int id) {

  // cout << "Thread: " << id << endl;

  Delay thinking(100000);
  for (int i = 0; i < 1000000000; i++) {}
  for (int i = 0; i < 1000000000; i++) {}

  cout << "End Thread:" << id << endl;

  return 0;
}
