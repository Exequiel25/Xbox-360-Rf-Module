| Data (bin)    | Data (hex)  | Name            | Description                                                                             |
| ------------- | ----------- | --------------- | --------------------------------------------------------------------------------------- |
| 00 0000 0100  | 0x004       | SYNC            | Displays the XBOX 360 controller sync LED sequence (not sure if it really syncs)        |
| 00 0000 01001 | 0x009       | SYNC_SLIM       | Displays the XBOX 360 controller sync LED sequence (not sure if it really syncs)        |
| 00 0000 1001  | 0x009       | CTRL_OFF        | Turns off all controllers                                                               |
| 00 0000 01RP  | 0x01X       | CONFIG          | Configures the module (R bit is RF on/off, P bit is 0 for standing orientation)         |
| 00 1000 0000  | 0x080       | LED_OFF         | Turns off the LED controller                                                            |
| 00 1000 0100  | 0x084       | LED_INIT        | Initializes the LEDs (needed before any other commands) and turns on the power LED      |
| 00 1000 0101  | 0x085       | BOOT_ANIM       | Same as LED_INIT + Displays the XBOX 360 boot LED sequence (appears to only work once)  |
| 00 1000 1000  | 0x088       | LED_INIT_NOPWR  | Initializes the LEDs (needed before any other commands)                                 |
| 00 1000 1001  | 0x089       | BOOT_ANIM_NOPWR | Same as LED_INIT + Displays the XBOX 360 boot LED sequence (appears to only work once)  |
| 00 1010 ABCD  | 0x0AX       | SET_GREEN_LEDS  | Sets the four green LEDs on or off (four least significant bits encode green led value) |
| 00 1011 ABCD  | 0x0BX       | SET_RED_LEDS    | Sets the four red LEDs on or off (same as SET_GREEN_LEDS but independent of it)         |
| 00 1100 0000  | 0x0C0       | CLEAR_ERROR     | Clears any error display (blinking red leds or orange solid)                            |
| 00 1100 0001  | 0x0C1       | SLOW_BLINK_ALL  | Blinks all four red LEDs                                                                |
| 00 1100 0001  | 0x0C2       | SLOW_BLINK_1    | Blinks top left red LED                                                                 |
| 00 1100 0001  | 0x0C3       | SLOW_BLINK_2    | Blinks top right red LED                                                                |
| 00 1100 0001  | 0x0C4       | SLOW_BLINK_3    | Blinks bottom right red LED                                                             |
| 00 1100 0001  | 0x0C5       | SLOW_BLINK_4    | Blinks top left red LED                                                                 |
| 00 1101 0000  | 0x0D0       | CLEAR_ERROR     | Clears any error display (blinking red leds or orange solid)                            |
| 00 1101 0001  | 0x0D1       | FAST_BLINK_ALL  | Blinks all four red LEDs                                                                |
| 00 1101 0001  | 0x0D2       | FAST_BLINK_1    | Blinks top left red LED                                                                 |
| 00 1101 0001  | 0x0D3       | FAST_BLINK_2    | Blinks top right red LED                                                                |
| 00 1101 0001  | 0x0D4       | FAST_BLINK_3    | Blinks bottom right red LED                                                             |
| 00 1101 0001  | 0x0D5       | FAST_BLINK_4    | Blinks top left red LED                                                                 |
| 00 1110 0000  | 0x0E0       | CLEAR_ERROR     | Clears any error display (blinking red leds or orange solid)                            |
| 00 1110 0000  | 0x0E1_0x0EF | LED_AMBER       | Sets all leds to amber colour                                                           |
