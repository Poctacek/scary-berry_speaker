import machine

class DFPlayer:
    def __init__(self, uart_id=0, tx_pin=0, rx_pin=1):
        # V MicroPythonu používáme HW UART přímo z RP2040
        self.uart = machine.UART(uart_id, baudrate=9600, tx=machine.Pin(tx_pin), rx=machine.Pin(rx_pin))

    def _send_cmd(self, cmd, param1=0, param2=0):
        buf = bytearray(10)
        buf[0] = 0x7E
        buf[1] = 0xFF
        buf[2] = 0x06
        buf[3] = cmd
        buf[4] = 0x00
        buf[5] = param1
        buf[6] = param2
        
        # Kontrolní součet (checksum) podle protokolu DFPlayer Mini
        checksum = -(buf[1] + buf[2] + buf[3] + buf[4] + buf[5] + buf[6])
        buf[7] = (checksum >> 8) & 0xFF
        buf[8] = checksum & 0xFF
        buf[9] = 0xEF
        
        self.uart.write(buf)

    def set_volume(self, volume):
        if 0 <= volume <= 30:
            self._send_cmd(0x06, 0x00, volume)

    def play(self, track_number):
        self._send_cmd(0x0F, 0x01, track_number)