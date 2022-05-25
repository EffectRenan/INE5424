#include <utility/ostream.h>
#include <system.h>

using namespace EPOS;

OStream cout;

#define MAX 10

int main()
{
    char * ptrs[MAX];
    char * checker;
    char * first_valid = (char *) malloc(4, FLASH);
    
    ptrs[0] = first_valid;

    if (first_valid < (void *) Traits<Machine>::FLASH_BASE) {
        free(first_valid);
        cout << "Flash: Out of flash range" << endl;
        return 1;
    }

    // malloc

    cout << "malloc: " << (void *) ptrs[0] << endl;

    for (int i = 1; i < MAX; i++) {
        ptrs[i] = (char *) malloc(4, FLASH);
        cout << "malloc: " << (void *) ptrs[i] << endl;
    }

    // free
    
    for (int i = 0; i < MAX; i++) {
        cout << "free: " << (void *) ptrs[i] << endl;
        free(ptrs[i], FLASH);
    }

    checker = (char *) malloc(4, FLASH);

    if ((void *) checker == (void *) first_valid)
        cout << endl << "Malloc & Free: ok" << endl << endl;
    else
        cout << endl << "Malloc & Free: bad!" << endl << endl;

    free(checker, FLASH);

    // new

    for (int i = 0; i < MAX; i++) {
        ptrs[i] = new (FLASH) char('A');
        cout << "new: " << (void *) ptrs[i] << endl;
    }

    // delete

    for (int i = 0; i < MAX; i++) {
        cout << "delete: " << (void *) ptrs[i] << endl;
        delete ptrs[i];
    }

    checker = (char *) malloc(4, FLASH);
    
    if ((void *) checker == (void *) first_valid)
        cout << endl << "New & Delete: ok" << endl << endl;
    else
        cout << endl << "New & Delete: bad!" << endl << endl;

    free(checker, FLASH);

    // ------------------------------------------------------
    // Check system is ok

    // malloc
    
    char * first_valid_system = (char *) malloc(4);
    char * test_system;

    if (first_valid_system >= (void *) Traits<Machine>::FLASH_BASE) {
        free(first_valid_system);
        cout << "System: Out of system range" << endl;
        return 1;
    }

    free(first_valid_system);

    // free
    
    test_system = (char *) malloc(4);

    if (first_valid_system != test_system) {
        free(test_system);
        cout << "System free: bad!" << endl;
        return 1;
    }

    free(test_system);

    // new

    first_valid_system = new (SYSTEM) char('A');
    
    if (first_valid_system >= (void *) Traits<Machine>::FLASH_BASE) {
        free(test_system);
        cout << "System: Out of system range" << endl;
        return 1;
    }

    // delete
   
    delete first_valid_system;


    test_system = new (SYSTEM) char('A');

    if (first_valid_system != test_system) {
        free(test_system);
        cout << "System delete: bad!" << endl;
        return 1;
    }

    cout << "System is ok" << endl << endl;

    return 0;
}
