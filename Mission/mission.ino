#include <grass.h>

int mission_time = 0;

int rotate(int quick = 40, int moderate = 30, int slow = 20, int very_slow = 10, int minimum = 5 ) {
  //compass car
  int rotation = 0;
  if (robot.compass.get_heading() < 180) {
    // left turn
    if (robot.compass.get_heading() > 120) {
      // quick turn
      rotation = -quick;
    } else if (robot.compass.get_heading() > 70) {
      // moderate turn
      rotation = -moderate;
    } else if (robot.compass.get_heading() > 40) {
      // slow turn
      rotation = -slow;
    } else if (robot.compass.get_heading() > minimum) {
      // very slow turn
      rotation = -very_slow;
    } else {
      // stop because compassReading > 0 && compassReading <= 2
      rotation = 0;
    }
  } else if (robot.compass.get_heading() >= 180) {
    // right turn
    if (robot.compass.get_heading() < 240) {
      // quick turn
      rotation = quick;
    } else if (robot.compass.get_heading() < 290) {
      // moderate turn
      rotation = moderate;
    } else if (robot.compass.get_heading() < 320) {
      // slow turn
      rotation = slow;
    } else if (robot.compass.get_heading() < 360 - minimum) {
      // very slow turn
      rotation = very_slow;
    } else {
      // stop because compassReading < 360 && compassReading >= 358
      rotation = 0;
    }
  }
  return rotation;
}

void mtrs_ctrl(int spd0, int spd1, int spd2, int spd3){
  /*
  0   1
  3   2
  */

  spd0 = (spd0  + rotate());
  spd1 = (-spd1  + rotate());
  spd2 = (-spd2 + rotate());
  spd3 = (spd3 + rotate());

  robot.mtrs[0].set_spd(spd0);
  robot.mtrs[1].set_spd(spd1);
  robot.mtrs[2].set_spd(spd2);
  robot.mtrs[3].set_spd(spd3);
}

void compass_motor(){
  if(robot.compass.get_heading() >= 10 && robot.compass.get_heading() < 180){
    mtrs_ctrl(-70,70,70,-70);
  }else if(robot.compass.get_heading() >= 180 && robot.compass.get_heading() < 350){
    mtrs_ctrl(70,-70,-70,70);
  }else if(robot.compass.get_heading() >= 350 || robot.compass.get_heading() < 10){
    mtrs_ctrl(0,0,0,0);
  }
}

void setup(){
  Serial.begin(9600);
  robot.begin();
  robot.compass.reset_heading();
}

void loop(){
  // now assume no different speed with the wheels


  //point A back: 55cm right: 66

  //get data
  Serial.print(robot.uts_back.read_dist_cm ());
  Serial.print(" ");
  Serial.print(robot.uts_right.read_dist_cm());
  Serial.print(" ");
  Serial.println(robot.compass.get_heading());

  while(1){
    if(robot.uts_back.read_dist_cm () < 20){
      robot.compass.reset_heading();
      delay(300);
      break;
    }
  }
  
  while(1){
    if(mission_time >= 6){
      break;
    }else{
      while(1){
        //at point a
        if((robot.uts_back.read_dist_cm () < 60) && (robot.uts_right.read_dist_cm () < 70)){
          //go to point b
          while(1){
            Serial.print("Now mission_time: ");
            Serial.println(mission_time);
            if((robot.uts_back.read_dist_cm () > 120) && (robot.uts_right.read_dist_cm () < 80)){   //arrive point b
              mtrs_ctrl(0, 0, 0, 0);
              mission_time = mission_time + 1;
              delay(200);
              break;
            }else{
              //move forward
              mtrs_ctrl(60, 75, 70, 60);
            }
          }
        }else{
          break;
        }
      }

      while(1){
        //at point b
        if((robot.uts_back.read_dist_cm () > 120) && (robot.uts_right.read_dist_cm () < 80)){
          //go to point c
          while(1){
            Serial.print("Now mission_time: ");
            Serial.println(mission_time);
            if(
              ((robot.uts_back.read_dist_cm () > 70) && (robot.uts_back.read_dist_cm () < 90)) && 
              ((robot.uts_right.read_dist_cm () > 85) && (robot.uts_right.read_dist_cm () < 100))
            ){   //arrive point c
              mtrs_ctrl(0, 0, 0, 0);
              mission_time = mission_time + 1;
              delay(200);
              break;
            }else{
              //move left backwards
              mtrs_ctrl(-60, 0, -65, 0);
            }
          }
        }else{
          break;
        }
      }

      while(1){
        //at point c
        if(
          ((robot.uts_back.read_dist_cm () > 70) && (robot.uts_back.read_dist_cm () < 90)) && 
          ((robot.uts_right.read_dist_cm () > 85) && (robot.uts_right.read_dist_cm () < 100))
        ){    //go to point d
          while(1){
            Serial.print("Now mission_time: ");
            Serial.println(mission_time);
            if((robot.uts_back.read_dist_cm () < 60) && (robot.uts_right.read_dist_cm () > 110)){   //arrive point d
              mtrs_ctrl(0, 0, 0, 0);
              mission_time = mission_time + 1;
              delay(200);
              break;
            }else{
              mtrs_ctrl(-60, 0, -65, 0);
            }
          }
        }else{
          break;
        }
      }

      while(1){
        //at point d
        if((robot.uts_back.read_dist_cm () < 60) && (robot.uts_right.read_dist_cm () > 110)){
          //go to point e
          while(1){
            Serial.print("Now mission_time: ");
            Serial.println(mission_time);
            if((robot.uts_back.read_dist_cm () > 105) && (robot.uts_right.read_dist_cm () > 90)){   //arrive point e
              mtrs_ctrl(0, 0, 0, 0);
              mission_time = mission_time + 1;
              delay(200);
              break;
            }else{
              mtrs_ctrl(60, 70, 70, 60);
            }
          }
        }else{
          break;
        }
      }

      while(1){
        //at point e
        if((robot.uts_back.read_dist_cm () > 105) && (robot.uts_right.read_dist_cm () > 90)){    //go to point c
          while(1){
            Serial.print("Now mission_time: ");
            Serial.println(mission_time);
            if(
              ((robot.uts_back.read_dist_cm () > 70) && (robot.uts_back.read_dist_cm () < 90)) && 
              ((robot.uts_right.read_dist_cm () > 85) && (robot.uts_right.read_dist_cm () < 100))
            ){   //arrive point c
              mtrs_ctrl(0, 0, 0, 0);
              mission_time = mission_time + 1;
              delay(200);
              break;
            }else{
              mtrs_ctrl(30, -40, 30, -70);
            }
          }
        }else{
          break;
        }
      }

      while(1){
        //at point c
        if(
          ((robot.uts_back.read_dist_cm () > 70) && (robot.uts_back.read_dist_cm () < 90)) && 
          ((robot.uts_right.read_dist_cm () > 85) && (robot.uts_right.read_dist_cm () < 100))
        ){ 
          //go to point a
          while(1){
            Serial.print("Now mission_time: ");
            Serial.println(mission_time);
            if((robot.uts_back.read_dist_cm () < 60) && (robot.uts_right.read_dist_cm () < 70)){   //arrive point a
              mtrs_ctrl(0, 0, 0, 0);
              mission_time = mission_time + 1;
              delay(200);
              break;
            }else{
              mtrs_ctrl(30, -60, 30, -60);
            }
          }
        }else{
          break;
        }
      }
    }

    
  }
  
  
  // Serial.print(rotate());
  // Serial.print(" ");
  // Serial.println(robot.compass.get_heading());
  // mtrs_ctrl(50, 50, 50, 50);
}