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
        0x7E, 0xFF, 0x06, 0x0F, 0x00, 0x01, track_number, (uint8_t)(0xEF - track_number), 0xEF
    };

    for (int i = 0; i < 10; i++)
    {
        uart_putc(UART_ID, cmd[i]);
    }
}




int main()
{
    stdio_init_all();


    gpio_init(PIR_PIN);
    gpio_set_dir(PIR_PIN, GPIO_IN);
    gpio_pull_down(PIR_PIN);

    uart_init(UART_ID, BAUD_RATE);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

    printf("SBS initialized (C++)... \n");

    while (true)
    {
        if (gpio_get(PIR_PIN))
        {
            printf("Movement detected, playing 001.mp3... \n");
            play_dfplayer(1); // for now, it only plays the first track, will revisit later

            sleep_ms(6000);
        }
        sleep_ms(100);
    }
return 0;
}
