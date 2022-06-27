#include <architecture.h>
#include <machine/riscv/riscv_ic.h>
#include <process.h>
#include <time.h>
#include <utility/ostream.h>

using namespace EPOS;

OStream cout;

Thread *phil[5];

int test();

int main() {
  cout << "main: " << CPU::id() << endl;

  for (int i = 0; i < 5; i++) {
    phil[0] = new Thread(&test);
  }

  for (int i = 0; i < 5; i++) {
    phil[i]->join();
  }



  for (int i = 0; i < 5; i++) {
    delete phil[i];
  }

  cout << "end main!" << endl;
  return 0;
}

int test() {
  cout << "test: " << CPU::id() << endl;
  // cout << "test!" << endl;
  for (unsigned i = 0; i < 3000000000; i++);
  // for (unsigned i = 0; i < 50000000000; i++);
  // for (unsigned i = 0; i < 50000000000; i++);
  // cout << "end test!" << endl; return 0;
  return 0;
}
