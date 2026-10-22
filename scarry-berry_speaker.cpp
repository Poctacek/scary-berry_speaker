#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"

#define UART_ID uart0
#define BAUD_RATE 9600
#define UART_TX_PIN 0
#define UART_RX_PIN 1
#define PIR_PIN 15


void play_dfplayer(uint8_t track_number)
{
    uint8_t cmd[10] = {
        // TODO: Fill in the command bytes to play the specified track number on the DFPlayer module
    };

    for (int i = 0; i < 10; i++)
    {
        uart_putc(UART_ID, cmd[i]);
    }



}




int main()
{
    stdio_init_all();
}
