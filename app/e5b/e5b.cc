#include <utility/ostream.h>
#include <architecture.h>
#include <time.h>

using namespace EPOS;

OStream cout;

int main()
{
    cout << PMU::read(0) << endl;

    return 0;
}
