#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"

#define UART_ID uart0
#define BAUD_RATE 9600
#define UART_TX_PIN 0
#define UART_RX_PIN 1
#define PIR_PIN 15

void dfplayer_send_cmd(uint8_t cmd, uint8_t param1, uint8_t param2)
{
    uint8_t buf[10];
    buf[0] = 0x7E;
    buf[1] = 0xFF;
    buf[2] = 0x06;
    buf[3] = cmd;
    buf[4] = 0x00;
    buf[5] = param1;
    buf[6] = param2;


uint16_t checksum = -(buf[1] + buf[2] + buf[3] + buf[4] + buf[5] + buf[6]);
buf[7] = (uint8_t)(checksum >> 8);
buf[8] = (uint8_t)(checksum & 0xFF);
buf[9] = 0xEF;

uart_write_blocking(UART_ID, buf, 10);
}

void dfplayer_set_vol(uint8_t volume)
{
    if (volume > 30)
    {
        volume = 30
    }
    dfplayer_send_cmd(0x06, 0x00, volume);
}

void dfplayer_play(uint8_t track_number)
{
    dfplayer_send_cmd(0x0F, 0x01, track_number);
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
