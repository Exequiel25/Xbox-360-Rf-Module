#include <Arduino.h>
#include <avr/sleep.h>

// Check pinout diagram for the module to know which pins to use.
#define sync_pin 2  // Power button repurposed for sync button (pin 5 on the module)
#define data_pin 3  // Data line (pin 6 on the module)
#define clock_pin 4 // Clock line (pin 7 on module)

int led_cmd[10] = {0, 0, 1, 0, 0, 0, 0, 1, 0, 0};         // Activates/initializes the LEDs, leaving the center LED lit.
int led_timer_red_1[10] = {0, 0, 1, 0, 1, 1, 1, 0, 0, 0}; // Set quadrant 1 to red
int led_timer_red_2[10] = {0, 0, 1, 0, 1, 1, 1, 1, 0, 0}; // Set quadrant 1 and 2 to red
int led_timer_red_3[10] = {0, 0, 1, 0, 1, 1, 1, 1, 0, 1}; // Set quadrant 1, 2 and 4 to red
int led_timer_red_4[10] = {0, 0, 1, 0, 1, 1, 1, 1, 1, 1}; // Set quadrant 1, 2, 3 and 4 to red
int led_red_off[10] = {0, 0, 1, 0, 1, 1, 0, 0, 0, 0};     // Set quadrant 1, 2, 3 and 4 to off

int anim_cmd[10] = {0, 0, 1, 0, 0, 0, 0, 1, 0, 1}; // Makes the startup animation on the ring of light.

// int sync_cmd[10] = {0, 0, 0, 0, 0, 0, 0, 1, 0, 0}; // Initiates the sync process in FAT model.
int sync_cmd[11] = {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1}; // Initiates the sync process in SLIM model.

int turn_off_cmd[10] = {0, 0, 0, 0, 0, 0, 1, 0, 0, 1}; // Turns off the connected controllers.

volatile boolean sync_enable = 0;
int sync_hold_time = 0;
bool turn_off_controllers = false;

template <size_t N>
void sendData(int (&command)[N])
{
  pinMode(data_pin, OUTPUT);
  digitalWrite(data_pin, LOW); // Start sending data.
  int previous_clock = 1;
  for (size_t i = 0; i < N; i++)
  {
    while (previous_clock == digitalRead(clock_pin))
    {
    } // Detects change in clock
    previous_clock = digitalRead(clock_pin);
    // Should be after downward edge of clock, so send bit of data now
    digitalWrite(data_pin, command[i]);
    while (previous_clock == digitalRead(clock_pin))
    {
    } // Detects upward edge of clock
    previous_clock = digitalRead(clock_pin);
  }
  digitalWrite(data_pin, HIGH);
  pinMode(data_pin, INPUT);
}

void setHeldLEDs(int held_time)
{
  if (held_time >= 1000)
  {
    sendData(led_timer_red_4);
  }
  else if (held_time >= 750)
  {
    sendData(led_timer_red_3);
  }
  else if (held_time >= 500)
  {
    sendData(led_timer_red_2);
  }
  else if (held_time >= 250)
  {
    sendData(led_timer_red_1);
  }
  else
  {
    sendData(led_red_off);
  }
}

void initLEDs()
{
  sendData(led_cmd);
  delay(50);
  sendData(anim_cmd);
  delay(50);
}

void wakeUp()
{
  sync_enable = 1;
}

void sleepNow()
{
  set_sleep_mode(SLEEP_MODE_PWR_DOWN); // Set sleep mode
  sleep_enable();                      // Enable sleep bit
  attachInterrupt(0, wakeUp, LOW);
  sleep_mode();
  sleep_disable();    // Disable sleep bit
  detachInterrupt(0); // Disables interrupt 0 on pin 2
}

void setup()
{
  Serial.begin(9600);
  pinMode(sync_pin, INPUT);
  digitalWrite(sync_pin, HIGH);
  pinMode(data_pin, INPUT);
  pinMode(clock_pin, INPUT);
  delay(2000);
  initLEDs();
}

void loop()
{
  // Only sleep if the sync button is not held down
  if (!sync_enable)
  {
    Serial.println("Sleeping.");
    sleepNow();
  }
  delay(200);
  if (sync_enable)
  {
    Serial.print("Sync held time (ms): ");
    Serial.println(sync_hold_time, DEC);
    setHeldLEDs(sync_hold_time);
    // Count 1000ms, if elapsed the user wants to turn off their controllers
    if (sync_hold_time >= 1000)
    {
      turn_off_controllers = true;
      sync_hold_time = 1000;
    }
    // Initiate the user's action when they release the sync button
    if (digitalRead(sync_pin))
    {
      setHeldLEDs(0);
      if (turn_off_controllers)
      {
        Serial.println("Turning off controllers.");
        sendData(turn_off_cmd);
        turn_off_controllers = false;
      }
      else
      {
        Serial.println("Syncing controllers.");
        sendData(sync_cmd);
      }
      // Action complete, reset hold time and button state
      sync_hold_time = 0;
      sync_enable = false;
    }
    else
    {
      sync_hold_time += 200;
    }
  }
}