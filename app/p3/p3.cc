#include <architecture.h>
#include <process.h>
#include <time.h>
#include <utility/ostream.h>

using namespace EPOS;

OStream cout;

Thread *threads[3];

int test(int id);

int main() {

  cout << "Windows scheduler test" << endl << endl;

  threads[0] = new Thread(&test, 1); // highest
  threads[1] = new Thread(&test, 2); // above
  threads[2] = new Thread(&test, 3); // normal

  for (int i = 0; i < 1000000000; i++) {}

  threads[0]->join();
  threads[1]->join();
  threads[2]->join();

  delete threads[0];
  delete threads[1];
  delete threads[2];

  return 0;
}

int test(int id) {

  cout << "Thread: " << id << endl;
  for (int i = 0; i < 1000000000; i++) {}
  Delay thinking(1000000);
  for (int i = 0; i < 1000000000; i++) {}

  cout << "End Thread:" << id << endl;

  return 0;
}
