#include <SCServo.h>

SMS_STS sms_sts;

// Initial positions for servos
int initial_position_1;
int initial_position_2;
int initial_position_3;
int initial_position_4;
int initial_position_5;
int initial_position_6;
int Pos1;
int Pos2;
int Pos3;
int Pos6;
int Pos5;
int Pos4;

// Target positions for jumping
int target_position_1 = 2200;  // Target position for servo 1 (small leg)
int target_position_2_6 = 1200; // Target position for servos 2 and 6 (large leg)

// Servo speed
int speed = 3800;

void setup() {
  Serial.begin(1000000); // Servo baud rate
  sms_sts.pSerial = &Serial;
  
  delay(5000); // Delay to ensure serial initialization is complete

  // Calibrate to center positions
  sms_sts.CalibrationOfs(1);
  sms_sts.CalibrationOfs(2);
  sms_sts.CalibrationOfs(3);
  sms_sts.CalibrationOfs(4);
  sms_sts.CalibrationOfs(5);
  sms_sts.CalibrationOfs(6);
  delay(1000); // Delay to ensure calibration is complete

  Serial.println("Reading initial positions");
  // Read current servo positions as initial positions
  initial_position_1 = sms_sts.ReadPos(1);
  initial_position_2 = sms_sts.ReadPos(2);
  initial_position_3 = sms_sts.ReadPos(3);
  initial_position_4 = sms_sts.ReadPos(4);
  initial_position_5 = sms_sts.ReadPos(5);
  initial_position_6 = sms_sts.ReadPos(6);

  // Validate initial positions
  if (initial_position_1 == -1 || initial_position_2 == -1 || initial_position_3 == -1 || 
      initial_position_4 == -1 || initial_position_5 == -1 || initial_position_6 == -1) {
    Serial.println("Error reading initial positions. Please check the connections and IDs of the servos.");
    while (1); // Stop program execution
  }

  Serial.println("Setup complete, ready to move.");
}

void loop() {
  int target_position_2_6 = 1200; // 目标位置 2 6
  int target_position_3_5 = 1000; // 目标位置 3 5
  int target_position_1 = 2200; // 目标位置 1 
  int target_position_4 = 2000; // 目标位置 1 4
  // Initial position to crouch
  Serial.println("Preparing for jump...");
  
  
  // Phase 1: Initial push with the small leg (servo 1)
  Serial.println("Phase 1: Initial push with small leg");
  sms_sts.RegWritePosEx(1, initial_position_1 + target_position_1, speed, 0);
  sms_sts.RegWritePosEx(4, initial_position_4, speed, 0); // 舵机(ID6)移动到初始位置
  sms_sts.RegWriteAction();
  delay(300); // Short delay for initial push stabilization

  // Phase 2: Main thrust with the large leg (servos 2 and 6)
  Serial.println("Phase 2: Main thrust with large leg");
  sms_sts.RegWritePosEx(2, initial_position_2, speed, 0); // 舵机(ID2)移动到初始位置
  sms_sts.RegWritePosEx(6, initial_position_6, speed, 0); // 舵机(ID6)移动到初始位置
  sms_sts.RegWritePosEx(3, initial_position_3 - target_position_3_5, speed, 0);
  sms_sts.RegWritePosEx(5, initial_position_5 + target_position_3_5, speed, 0);
  sms_sts.RegWritePosEx(4, initial_position_4 + target_position_4, speed, 0); // 舵机(ID3)逆时针移动到目标位置
  sms_sts.RegWriteAction();
  delay(350); // Allow time for main thrust
    Pos1 = sms_sts.ReadPos(1);
    Pos2 = sms_sts.ReadPos(2);
    Pos3 = sms_sts.ReadPos(3);
    Pos4 = sms_sts.ReadPos(4);
    Pos6 = sms_sts.ReadPos(6);
    Pos5 = sms_sts.ReadPos(5);
    Serial.println("jump!!!!!!!");
    Serial.print("ID2 Pos: ");
    Serial.println(Pos2);
    Serial.print("ID6 Pos: ");
    Serial.println(Pos6);
    Serial.print("ID4 Pos: ");
    Serial.println(Pos4);
    Serial.print("ID1 Pos: ");
    Serial.println(Pos1);
    Serial.print("ID3 Pos: ");
    Serial.println(Pos3);
    Serial.print("ID5 Pos: ");
    Serial.println(Pos5);
    
  Serial.println("Jump executed");

  // Optionally, return to initial positions
  Serial.println("Returning to initial positions...");
  sms_sts.RegWritePosEx(2, initial_position_2 + target_position_2_6 , speed, 0); // 舵机(ID2)逆时针移动到目标位置
  sms_sts.RegWritePosEx(6, initial_position_6 - target_position_2_6 , speed, 0); // 舵机(ID6)逆时针移动到目标位置
  
  sms_sts.RegWritePosEx(1, initial_position_1, speed, 0);
  sms_sts.RegWritePosEx(3, initial_position_3, speed, 0);
  sms_sts.RegWritePosEx(5, initial_position_5, speed, 0);
  sms_sts.RegWriteAction();
  delay(350); // Allow time to return to start position
    Serial.println("jump!!!!!!!");
    Serial.print("ID2 Pos: ");
    Serial.println(Pos2);
    Serial.print("ID6 Pos: ");
    Serial.println(Pos6);
    Serial.print("ID4 Pos: ");
    Serial.println(Pos4);
    Serial.print("ID1 Pos: ");
    Serial.println(Pos1);
    Serial.print("ID3 Pos: ");
    Serial.println(Pos3);
    Serial.print("ID5 Pos: ");
    Serial.println(Pos5);
    
  Serial.println("Loop over, ready for next jump.");
  delay(1000); // Delay before the next jump cycle
}


// #include <SCServo.h>

// SMS_STS sms_sts;

// // Initial positions for servos
// int initial_position_1;
// int initial_position_2;
// int initial_position_3;
// int initial_position_4;
// int initial_position_5;
// int initial_position_6;

// // Target positions for jumping
// int target_position_1 = 2200;  // Target position for servo 1 (small leg)
// int target_position_2_6 = 1200; // Target position for servos 2 and 6 (large leg)
// int target_position_3_5 = 1000; // Target position for servos 3 and 5

// // Servo speed
// int speed = 6000; // Increase speed for more torque and faster motion

// void setup() {
//   Serial.begin(1000000); // Servo baud rate
//   sms_sts.pSerial = &Serial;
  
//   delay(5000); // Delay to ensure serial initialization is complete

//   // Calibrate to center positions
//   sms_sts.CalibrationOfs(1);
//   sms_sts.CalibrationOfs(2);
//   sms_sts.CalibrationOfs(3);
//   sms_sts.CalibrationOfs(4);
//   sms_sts.CalibrationOfs(5);
//   sms_sts.CalibrationOfs(6);
//   delay(1000); // Delay to ensure calibration is complete

//   Serial.println("Reading initial positions");
//   // Read current servo positions as initial positions
//   initial_position_1 = sms_sts.ReadPos(1);
//   initial_position_2 = sms_sts.ReadPos(2);
//   initial_position_3 = sms_sts.ReadPos(3);
//   initial_position_4 = sms_sts.ReadPos(4);
//   initial_position_5 = sms_sts.ReadPos(5);
//   initial_position_6 = sms_sts.ReadPos(6);

//   // Validate initial positions
//   if (initial_position_1 == -1 || initial_position_2 == -1 || initial_position_3 == -1 || 
//       initial_position_4 == -1 || initial_position_5 == -1 || initial_position_6 == -1) {
//     Serial.println("Error reading initial positions. Please check the connections and IDs of the servos.");
//     while (1); // Stop program execution
//   }

//   Serial.println("Setup complete, ready to move.");
// }

// void loop() {
//   // Initial position to crouch
//   Serial.println("Preparing for jump...");
  
//   // Phase 1: Initial push with the small leg (servo 1)
//   Serial.println("Phase 1: Initial push with small leg");
//   sms_sts.RegWritePosEx(1, initial_position_1 + target_position_1, speed, 0);
//   sms_sts.RegWritePosEx(4, initial_position_4, speed, 0); // Stabilize servo
//   sms_sts.RegWriteAction();
//   delay(100); // Short delay for initial push stabilization

//   // Phase 2: Main thrust with the large leg (servos 2 and 6)
//   Serial.println("Phase 2: Main thrust with large leg");
//   sms_sts.RegWritePosEx(2, initial_position_2 + target_position_2_6, speed, 0);
//   sms_sts.RegWritePosEx(6, initial_position_6 - target_position_2_6, speed, 0);
//   sms_sts.RegWriteAction();
//   delay(150); // Allow time for main thrust

//   // Quickly retract servos 3 and 5
//   Serial.println("Retracting servos 3 and 5 for stabilization");
//   sms_sts.RegWritePosEx(3, initial_position_3 - target_position_3_5, speed, 0);
//   sms_sts.RegWritePosEx(5, initial_position_5 + target_position_3_5, speed, 0);
//   sms_sts.RegWriteAction();
//   delay(150); // Quick retract for stabilization

//   // Print the positions for debugging
//   int Pos1 = sms_sts.ReadPos(1);
//   int Pos2 = sms_sts.ReadPos(2);
//   int Pos3 = sms_sts.ReadPos(3);
//   int Pos4 = sms_sts.ReadPos(4);
//   int Pos6 = sms_sts.ReadPos(6);
//   int Pos5 = sms_sts.ReadPos(5);
//   Serial.println("Jump executed");
//   Serial.print("ID2 Pos: "); Serial.println(Pos2);
//   Serial.print("ID6 Pos: "); Serial.println(Pos6);
//   Serial.print("ID4 Pos: "); Serial.println(Pos4);
//   Serial.print("ID1 Pos: "); Serial.println(Pos1);
//   Serial.print("ID3 Pos: "); Serial.println(Pos3);
//   Serial.print("ID5 Pos: "); Serial.println(Pos5);

//   // Optionally, return to initial positions
//   Serial.println("Returning to initial positions...");
//   sms_sts.RegWritePosEx(1, initial_position_1, speed, 0);
//   sms_sts.RegWritePosEx(2, initial_position_2, speed, 0);
//   sms_sts.RegWritePosEx(6, initial_position_6, speed, 0);
//   sms_sts.RegWritePosEx(3, initial_position_3, speed, 0);
//   sms_sts.RegWritePosEx(5, initial_position_5, speed, 0);
//   sms_sts.RegWritePosEx(4, initial_position_4, speed, 0);
//   sms_sts.RegWriteAction();
//   delay(500); // Allow time to return to start position

//   Serial.println("Loop over, ready for next jump.");
//   delay(1000); // Delay before the next jump cycle
// }
