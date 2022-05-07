#include <utility/ostream.h>
#include <time.h>

using namespace EPOS;

OStream cout;

int main()
{
    for (int count = 0; count < 100000; count++) {
        cout << "Hello world! | " << count << endl;
        // Delay thinking(1000000);
    }

    return 0;
}
