/* 
  Snesuino
  Version: 1.1 (27/02/2013) - added support for 2 controllers & 2 leds  
*/

#include <SNESpad.h>

#undef DEBUG

// put your own strobe/clock/data0/data1 pin numbers here
SNESpad nintendo = SNESpad(2,3,4,5);

// joystick output buffer
//uint8_t buf[8] = { 0 };	
#define NUM_BUTTONS	40
#define NUM_AXES	8	       // 8 axes, X, Y, Z, etc
#define LED_0 12
#define LED_1 13

typedef struct joyReport_t {
    int16_t axis[NUM_AXES];
    uint16_t button[2];
    uint8_t trailer;
} joyReport_t;

joyReport_t joyReport;

int oldstate_0 = 0;
int oldstate_1 = 0;


void setup() 
{
  pinMode(LED_0, OUTPUT);
  pinMode(LED_1, OUTPUT);
  
  Serial.begin(115200); 
  delay(200);
  
  // make sure the joyReport structure is initialized to 0
  for (uint8_t ind=0; ind<8; ind++) {
    joyReport.axis[ind] = 0;
  }
  for (uint8_t ind=0; ind<sizeof(joyReport.button); ind++) {
    joyReport.button[ind] = 0;
  } 
  joyReport.trailer = 0;
}

void loop() {
  
  // get the current button state of the SNES controllers
  nintendo.buttons();

  if (nintendo.state_0 != oldstate_0 || nintendo.state_1 != oldstate_1)
  {
    // check if any of the buttons are pressed, if so, set the appropriate led to high

    
     // something changed, lets send the current state over usb    
     joyReport.button[0] = nintendo.state_0;
     joyReport.button[1] = nintendo.state_1;
     
     sendJoystickState(&joyReport);
     
    if (nintendo.state_0 != 0)
    {
      digitalWrite(LED_0, HIGH);
    } 
    else
    {
      digitalWrite(LED_0, LOW);
    }
    if (nintendo.state_1 != 0)
    {
      digitalWrite(LED_1, HIGH);
    } 
    else
    {
      digitalWrite(LED_1, LOW);
    }
     
     // save the current state as the old state
     oldstate_0 = nintendo.state_0; 
     oldstate_1 = nintendo.state_1;
  }


}

void sendJoystickState(struct joyReport_t *report)
{
#ifndef DEBUG
    Serial.write((uint8_t *)report, sizeof(joyReport_t));
#else
    // dump human readable output for debugging
    for (uint8_t ind=0; ind<NUM_AXES; ind++) {
	Serial.print("axis[");
	Serial.print(ind);
	Serial.print("]= ");
	Serial.print(report->axis[ind]);
	Serial.print(" ");
    }
    Serial.println();
    for (uint8_t ind=0; ind<(NUM_BUTTONS/16); ind++) {
	Serial.print("button[");
	Serial.print(ind);
	Serial.print("]= ");
	Serial.print(report->button[ind], HEX);
	Serial.print(" ");
    }
    Serial.println();
#endif
}



