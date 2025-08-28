/*
  ROBOVANGUARD – WRO Future Engineers 2025
  World Robot Olympiad – Future Engineers Division

  Team ID: 1129
  Team Name: ROBOVANGUARD

  Mentor: Mr. S. Valai Ganesh (Mech, AP SG)
  Team Leader: M. Manojkumar (CSBS) – Reg. No: 953623244024
  Hardware Lead: V. Rakshit (EEE) – Reg. No: 953623105044
  Mechanical: P. Chandru (Mech) – Reg. No: 953623114009

  Project Summary:
  - Autonomous vehicle built on ESP32 with Ackermann steering, ultrasonic sensing,
    and TCS34725-based color detection, integrated with the RoboVision Android app
    for box/sign cues over serial.
  - This file contains Round 2 logic adding box detection and event-driven maneuvers
    on top of Round 1 navigation primitives.

  Notes for Reviewers/Assessors:
  - Documentation-oriented edits only; no functional changes were made.
  - Parameters, thresholds, timings, and function calls are preserved.
*/

// File: WRO_Round_2_Code_Final.ino
// Purpose: Round 2 navigation + box detection behavior for ROBOVANGUARD.

// ########### Loop ############################################################################################################ //
int line_chk_count = 12;  // 3 Laps - 12 count, 1 Lap - 4 count.
int line_count = 0;// 12

int normal_speed = 210;//pwm
int turn_speed = 230;//pwm
int turn_delay = 2600;//ms

const int blue_line_thold = 7000; //Blue Color Temp value
const int orange_line_thold = 3000; //Orange Color Temp value

bool left_right_arc_turn = 1;
bool left_right_r_turn = 0;

int fus_box_dist = 30;
//#---Servo Angles---###################################################################
int servo_center = 100;//deg
int left_turn_angle = servo_center - 20; //80 deg
int right_turn_angle = servo_center + 20;//120 deg
//#########################################################################################//
bool lt_st_count = 0;
bool rt_st_count = 0;
int rbox_count = 0;
int gbox_count = 0;

#define DPDT_Push_Button_Pin 34

int col_val, start_col, colour_line; // colour_line = 1 ->> Orange // colour_line = 3 ->> Blue
int f_us, f1_us, f2_us, b_us, l_us, r_us, fusa, far;

bool COLOR_LOCK = 1;//1 Initial True state.
bool LOGIC_LOCK = 1;//1 Initial True state.
bool DPDT_STATE = 0;//0 Initial False state.
//#########################################################################################//
char ab;
int serial_count;
bool bd_lock = 1;

const int bufferSize = 1;  
char abd[bufferSize];  

int abdRead;
char red_value = '1';
char green_value = '2';
//#########################################################################################//

void loop() 
{
  
  DPDT_STATE = digitalRead(DPDT_Push_Button_Pin);
  //Serial.println("DPDT Button State : "+String(DPDT_STATE));

  get_US_Values(f_us, f1_us, f2_us, b_us, l_us, r_us);
  //US_Values(f_us, b_us, l_us, r_us);
  // Serial.println("F_US : " + String(f_us) + " | F1_US : " + String(f1_us) + " | F2_US : " + String(f2_us) + 
  //             " | B_US : " + String(b_us) + 
  //             " | L_US : " + String(l_us) + " | R_US : " + String(r_us));

  far = fus_array();

  col_val = get_CS_Values();
  //Serial.println("Color Value : " + String(col_val));

  color_line_fun(); // color line pickup

  
  if (DPDT_STATE == 1) 
  { 
    if (LOGIC_LOCK == 1) 
    { 
      box_detection();

      if (col_val != 0)
      {
        color_logic_fun();
      }
      else if (col_val == 0)
      {
        side_us_logic_fun();
      }   

    }
      
  }else{
      bot_shutdown();
  }

  
    

  if (line_count == line_chk_count) 
  {
    end_stop();
    bot_shutdown();
    LOGIC_LOCK = 0;
    line_count = 0; 
  }   

}


void color_line_fun()
{
  if(COLOR_LOCK == 1)
  {
    if(col_val == 1)
    {
      start_col = 1;
      colour_line = 1;
      COLOR_LOCK = 0;
    }
    else if(col_val == 3)
    {
      start_col = 3;
      colour_line = 3;
      COLOR_LOCK = 0;
    }
  }
}

void color_logic_fun()
{

   //# Orange Line & Right Turn Condition: #/////////////////////////////////////////////////////////////////
      if ((col_val == colour_line) && (col_val != 3))
      { 
        line_count++;
        Serial.println("Orange Line Count : " + String(line_count));

        if(left_right_arc_turn)
        {
          rgb_led(0, 0, 0);
          delay(1);  
          motor_forward(turn_speed);
          rgb_led(150, 0, 150);
          moveServoTo(right_turn_angle);
          delay(turn_delay);
          moveServoTo(servo_center);
          delay(1);
          rgb_led(0, 0, 0);
        }

        if(left_right_r_turn)
        {
          rgb_led(0, 0, 0);
          motor_forward(turn_speed);
          rgb_led(150, 0, 150);

          moveServoTo(right_turn_angle);
          delay(1500); 
          motor_backward(turn_speed);
          delay(1);      
          moveServoTo(left_turn_angle);
          delay(1500);
          moveServoTo(servo_center);
          delay(1);  
          motor_forward(210);
          rgb_led(0, 0, 0);
        }
        
      } 
      
      //# Blue Line & Left Turn Condition: #/////////////////////////////////////////////////////////////////
      if ((col_val == colour_line) && (col_val != 1))
      { 
        line_count++;
        Serial.println("Blue Line Count : " + String(line_count));

        if(left_right_arc_turn)
        {
            rgb_led(0, 0, 0);
            rgb_led(150, 0, 150);
            moveServoTo(left_turn_angle);
            delay(turn_delay);
            moveServoTo(servo_center);
            rgb_led(0, 0, 0);
        }


        if(left_right_r_turn)
        {
            rgb_led(0, 0, 0);
            motor_forward(turn_speed);
            rgb_led(150, 0, 150);

            moveServoTo(left_turn_angle);
            delay(1500); 
            motor_backward(turn_speed);
            delay(1);      
            moveServoTo(right_turn_angle);
            delay(1500);
            moveServoTo(servo_center);
            delay(1);  
            motor_forward(210);
            rgb_led(0, 0, 0);

        }
        
      } 

}


void side_us_logic_fun()
{              
    motor_forward(normal_speed);

    if ((l_us < 30) && (l_us != 0))
    { 
        rgb_led(0, 0, 0);
        rgb_led(255, 0, 50); 
        moveServoTo(servo_center + 15);

        if(rt_st_count == 0)
        {
          if(lt_st_count == 0)
          {
            lt_st_count = 1;
          }
        }

    }
    if ((l_us > 30) && (r_us > 30) && (l_us != 0) && (r_us != 0)) 
    { 
        rgb_led(0, 0, 0);
        rgb_led(255, 255, 0);
        moveServoTo(servo_center); //100
    } 

    if ((r_us < 30) && (r_us != 0))
    {
        rgb_led(0, 0, 0);
        rgb_led(255, 0, 50); 
        moveServoTo(servo_center - 15);//90

        if(lt_st_count == 0)
        {
          if(rt_st_count == 0)
          {
            rt_st_count = 1;
          }
        }

    }
}

void bot_shutdown()
{
  motor_stop();
  moveServoTo(servo_center);
  rgb_led(0, 0, 0);
}

void box_detection()
{
  motor_forward(normal_speed);
   // Check if data available on serial port
    if((far == 1) && (Serial.available() > 0))  
    { 
      ab = Serial.read();
      serial_count++;
    }
    else
    {
      ab = 'n';
      buffer_limit();  //[*]
    }

    if((ab == '1') && (far == 1)) // Red Box
    {
      rgb_led(0, 0, 0); 
      rgb_led(255, 0, 0);
      rbox_count++;

        motor_backward(220);
        delay(1000);
        motor_stop();
        delay(1000);
        moveServoTo(right_turn_angle);
        motor_forward(220);
         // Right Turn
        delay(1400);
        moveServoTo(left_turn_angle);  // Left Turn
        delay(800);
        moveServoTo(servo_center);
        rgb_led(0, 0, 0);

        //Event - 1
        // moveServoTo(right_turn_angle); 
        // delay(1500);
        // moveServoTo(left_turn_angle); 
        // delay(1500);
        // moveServoTo(servo_center);

     

      buffer_limit(); //[*]
    } 

    if((ab == '2') && (far == 1)) // Green Box
    {
      rgb_led(0, 0, 0); 
      rgb_led(0, 255, 0); 
      gbox_count++;

      motor_backward(220);
      delay(1000);
      motor_stop();
      delay(1000);
      moveServoTo(left_turn_angle);
      motor_forward(220);
        // Left Turn
      delay(1400);
      moveServoTo(right_turn_angle); // Right Turn
      delay(800);
      moveServoTo(servo_center);

      // moveServoTo(left_turn_angle); 
      // delay(1500);
      // moveServoTo(right_turn_angle); 
      // delay(1500);
      // moveServoTo(servo_center);

      rgb_led(0, 0, 0); 

      buffer_limit(); //[*]
    }
            
}

int fus_array()
{
  if(((f_us <= fus_box_dist) && (f_us != 0)) || 
    ((f1_us <= fus_box_dist) && (f1_us != 0)) || 
    ((f2_us <= fus_box_dist) && (f2_us != 0)) ) { fusa = 1; }

  else{fusa = 0;}

  return fusa;
}

void buffer_limit()
{
  while(Serial.available() > 0)
  {
    abdRead = Serial.readBytesUntil(red_value, abd, bufferSize);
    abdRead = Serial.readBytesUntil(green_value, abd, bufferSize);
    
    abd[abdRead] = '\0';
  }

}

void left_stop()
{
  rgb_led(0, 0, 0);
  delay(1);
  rgb_led(255, 255, 255);
  
  motor_forward(215);
  delay(1000);
  moveServoTo(left_turn_angle);
  delay(1500);
  moveServoTo(right_turn_angle);
  delay(1500);
  moveServoTo(servo_center);
  delay(1000);
  
  rgb_led(0, 0, 0);
}

void right_stop()
{
  rgb_led(0, 0, 0);
  delay(1);
  rgb_led(255, 255, 255);

  motor_forward(215);
  delay(1000);
  moveServoTo(right_turn_angle);
  delay(1500);
  moveServoTo(left_turn_angle);
  delay(1500);
  moveServoTo(servo_center);
  delay(1000);

  rgb_led(0, 0, 0);

}

void end_stop()
{

  if(start_col == 3)
  {
      // Anti-clock wise:
      if(colour_line == 3)
      {
        if(lt_st_count == 1)
        {
          left_stop();
        }
        else if(rt_st_count == 1)
        {
          right_stop();
        }
      }

      if(colour_line == 1)
      {
        if(lt_st_count == 1)
        {
          right_stop();
        }
        else if(rt_st_count == 1)
        {
          left_stop();
        }
      }
  }
  
 ///////////////////////////////////////////////////////////////////
  if(start_col == 1)
  {
      // clock wise:
      if(colour_line == 3)
      {
        if(lt_st_count == 1)
        {
          right_stop();
        }
        else if(rt_st_count == 1)
        {
          left_stop();
        }
      }

      if(colour_line == 1)
      {
        if(lt_st_count == 1)
        {
          left_stop();
        }
        else if(rt_st_count == 1)
        {
          right_stop();
        }
      }
  }

}



