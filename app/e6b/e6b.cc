#include <utility/ostream.h>
#include <system.h>

using namespace EPOS;

OStream cout;

int main()
{

    for (int i = 0; i < 65; i++) {
        char * cp = new (FLASH) char('A');
        cout << "new char('A')\t\t=> {p=" << (void *)cp << ",v=" <<cp << "}" << endl;
    }

    return 0;
}
