import machine
import time
import random
from dfplayer import DFPlayer

player = DFPlayer(uart_id=0, tx_pin=0, rx_pin=1)
player.set_volume(30)
pir = machine.Pin(15, machine.Pin.IN, machine.Pin.PULL_DOWN)

TOTAL_TRACKS = 3

print("Waiting for motion...")

while True:
    if pir.value() == 1:
        track = random.randint(1, TOTAL_TRACKS)
        print(f"Motion detected, playing 00{track}.mp3")
        player.play(track)

        time.sleep(6)


        time.sleep(0.1)