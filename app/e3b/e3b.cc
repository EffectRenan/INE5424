// EPOS PC UART Mediator Test Program

#include <utility/string.h>
#include <machine/riscv/riscv_uart.h>

using namespace EPOS;
    
UART uart(0, 0, 0, 0);

void print(char *text);
char get(char &pressed);

int main()
{

    char text[] = "Press a button\n";
    print(text);

    char pressed = 0;
    while(!get(pressed));

    strcpy(text, "Pressed: ");
    print(text);

    uart.put(pressed);
    
    uart.flush();

    strcpy(text, "\nDone!\n");
    print(text);

    return 0;
}

void print(char *text)
{
    for (int i = 0; i < (int) strlen(text); i++)
        uart.put(text[i]);
}

char get(char &pressed)
{
    pressed = uart.get();
    return pressed;
}
