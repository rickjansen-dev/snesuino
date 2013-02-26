/* 
  Snesuino
  Version: 1.0 (26/02/2013) - first version   
*/

#include <SNESpad.h>

// put your own strobe/clock/data0/data1 pin numbers here
SNESpad nintendo = SNESpad(2,3,4,7);

//int newstate_0 = 0;
int oldstate_0 = 0;
//int newstate_1 = 0;
int oldstate_1 = 0;

// define keyboard keys to press (controller 0)
const int SNES0_KEY_A = 0x11; // N
const int SNES0_KEY_B = 0x10; // M
const int SNES0_KEY_X = 0x0F; // L
const int SNES0_KEY_Y = 0x1C; // K
const int SNES0_KEY_UP = 0x52; // ArrowUp
const int SNES0_KEY_DOWN = 0x51; // ArrowDown
const int SNES0_KEY_LEFT = 0x50; // ArrowLeft
const int SNES0_KEY_RIGHT = 0x4F; // ArrowRight
const int SNES0_KEY_L = 0x05; // B
const int SNES0_KEY_R = 0x0D; // J
const int SNES0_KEY_SELECT = 0x16; // S
const int SNES0_KEY_START = 0x07;  // D

void setup() {
  Serial.begin(115200);  
}

void loop() {
  
  nintendo.buttons();

  if (nintendo.state_0 != oldstate_0)
  {
     // er is iets veranderd, afhandelen die hap
    
     processButtons(oldstate_0, nintendo.state_0);
     
     // de nieuwe staat is de oude staat
     oldstate_0 = nintendo.state_0; 
  }
  
  if (nintendo.state_1 != oldstate_1)
  {
     // er is iets veranderd, afhandelen die hap
    
     processButtons2();
     
     // de nieuwe staat is de oude staat
     oldstate_1 = nintendo.state_1; 
  }

}

// yes this is ugly, but it is still in testing

void processButtons(int oldstate, int newstate)
{
  processButton(SNES_A, SNES0_KEY_A, oldstate, newstate);
  processButton(SNES_B, SNES0_KEY_B, oldstate, newstate);
  processButton(SNES_X, SNES0_KEY_X, oldstate, newstate);
  processButton(SNES_Y, SNES0_KEY_Y, oldstate, newstate);
  processButton(SNES_UP, SNES0_KEY_UP, oldstate, newstate);
  processButton(SNES_DOWN, SNES0_KEY_DOWN, oldstate, newstate);
  processButton(SNES_LEFT, SNES0_KEY_LEFT, oldstate, newstate);
  processButton(SNES_RIGHT, SNES0_KEY_RIGHT, oldstate, newstate);
  processButton(SNES_START, SNES0_KEY_START, oldstate, newstate);
  processButton(SNES_SELECT, SNES0_KEY_SELECT, oldstate, newstate);
  processButton(SNES_L, SNES0_KEY_L, oldstate, newstate);
  processButton(SNES_R, SNES0_KEY_R, oldstate, newstate);
}

void processButtons2()
{
  processButton2(SNES_A);
    processButton2(SNES_B);
      processButton2(SNES_X);
        processButton2(SNES_Y);
          processButton2(SNES_UP);
            processButton2(SNES_DOWN);
              processButton2(SNES_LEFT);
                processButton2(SNES_RIGHT);
                  processButton2(SNES_START);
                    processButton2(SNES_SELECT);
                      processButton2(SNES_L);
                        processButton2(SNES_R);
}


void processButton(int button, int mappedkey, int oldstate, int newstate)
{
  if (!(oldstate & button) && (newstate & button))
  {
     // button press
     Serial.print(button);
     Serial.println(" pressed (1)");
  }
  if ((oldstate & button) && !(newstate & button))
  {
     Serial.print(button);
     Serial.println(" released (1)");
  }
}

void processButton2(int button)
{
  if (!(oldstate_1 & button) && (nintendo.state_1 & button))
  {
     // button press
     Serial.print(button);
     Serial.println(" pressed (2)");
  }
  if ((oldstate_1 & button) && !(nintendo.state_1 & button))
  {
     Serial.print(button);
     Serial.println(" released (2)");
  }
}
