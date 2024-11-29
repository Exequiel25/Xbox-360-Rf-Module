#include <Arduino.h>

#define sync_pin 2  // power button repurposed for sync button (pin 5 on the module)
#define data_pin 3  // data line (pin 6 on the module)
#define clock_pin 4 // clock line (pin 7 on module)

int led_cmd[10] = {0, 0, 1, 0, 0, 0, 0, 1, 0, 0};     // Activates/initializes the LEDs, leaving the center LED lit.
int anim_cmd[10] = {0, 0, 1, 0, 0, 0, 0, 1, 0, 1};    // Makes the startup animation on the ring of light.
int sync_cmd[11] = {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1}; // Initiates the sync process in SLIM model.
volatile boolean sync_enable = 0;

void SendData(int data[], int delay_ms)
{
    pinMode(data_pin, OUTPUT);
    digitalWrite(data_pin, LOW); // Start sending data.
    int previous_clock = 1;
    for (size_t i = 0; i < 10; i++)
    {
        while (previous_clock == digitalRead(clock_pin))
        {
        } // Detects change in clock
        previous_clock = digitalRead(clock_pin);
        // Should be after downward edge of clock, so send bit of data now
        digitalWrite(data_pin, data[i]);
        while (previous_clock == digitalRead(clock_pin))
        {
        } // Detects upward edge of clock
        previous_clock = digitalRead(clock_pin);
    }
    digitalWrite(data_pin, HIGH);
    pinMode(data_pin, INPUT);
    delay(delay_ms);
}

void Init()
{
    pinMode(data_pin, INPUT);
    pinMode(clock_pin, INPUT);
    digitalWrite(clock_pin, HIGH);

    SendData(led_cmd, 50);
    delay(50);
}

void setup()
{
    Serial.begin(9600);
    Serial.write("Initializing...");
    Init();
    SendData(led_cmd, 7000);
}

void loop()
{
}