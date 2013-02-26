/* 
   this example from the SNESpad Arduino library
   displays the buttons on the joystick as bits
   on the serial port - rahji@rahji.com
   
   Version: 1.3 (11/12/2010) - got rid of shortcut constructor - seems to be broken
   
*/

#include <SNESpad.h>

// put your own strobe/clock/data pin numbers here -- see the pinout in readme.txt
SNESpad nintendo = SNESpad(2,3,4,7);

int newstate_0 = 0;
int oldstate_0 = 0;
int newstate_1 = 0;
int oldstate_1 = 0;

void setup() {
  Serial.begin(115200);  
}

void loop() {
  
  nintendo.buttons();
  newstate_0 = nintendo.state_0;
  newstate_1 = nintendo.state_1;
  
  if (newstate_0 != oldstate_0)
  {
     // er is iets veranderd, afhandelen die hap
    
     processButtons();
     
     // de nieuwe staat is de oude staat
     oldstate_0 = newstate_0; 
  }
  
  if (newstate_1 != oldstate_1)
  {
     // er is iets veranderd, afhandelen die hap
    
     processButtons2();
     
     // de nieuwe staat is de oude staat
     oldstate_1 = newstate_1; 
  }
  
//  if (state & SNES_A)
//  {
//    if (stateA == false)
//    {
//      // A is pressed! send a A to serial port
//      Serial.println("A pressed");  
//      stateA = !stateA;
//    }
//  } 
//  else
//  {
//    if (stateA == true)
//    {
//      // A is not pressed! send END_A if A was pressed previously
//      Serial.println("A released"); 
//      stateA = !stateA;
//    }
//  }

  // shows the shifted bits from the joystick
  // buttons are high (1) when up 
  // and low (0) when pressed
  //Serial.println(~state, BIN);

  //delay(500);
}

void processButtons()
{
  processButton(SNES_A);
    processButton(SNES_B);
      processButton(SNES_X);
        processButton(SNES_Y);
          processButton(SNES_UP);
            processButton(SNES_DOWN);
              processButton(SNES_LEFT);
                processButton(SNES_RIGHT);
                  processButton(SNES_START);
                    processButton(SNES_SELECT);
                      processButton(SNES_L);
                        processButton(SNES_R);
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


void processButton(int button)
{
  if (!(oldstate_0 & button) && (newstate_0 & button))
  {
     // button press
     Serial.print(button);
     Serial.println(" pressed (1)");
  }
  if ((oldstate_0 & button) && !(newstate_0 & button))
  {
     Serial.print(button);
     Serial.println(" released (1)");
  }
}

void processButton2(int button)
{
  if (!(oldstate_1 & button) && (newstate_1 & button))
  {
     // button press
     Serial.print(button);
     Serial.println(" pressed (2)");
  }
  if ((oldstate_1 & button) && !(newstate_1 & button))
  {
     Serial.print(button);
     Serial.println(" released (2)");
  }
}
