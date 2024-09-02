#include <SCServo.h>

SMS_STS sms_sts;
bool up = true;

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
int target_position_2_6 = 1200; // 目标位置 2 6
int target_position_3_5 = 1200; // 目标位置 3 5
int target_position_1 = 1400; // 目标位置 1 
int target_position_4 = 500; // 目标位置 4
int speed = 4500;
int speed_up = 5000;
int speed_2_6 = 4500;

void setup() {
  Serial.begin(1000000); // 舵机波特率1000000
  sms_sts.pSerial = &Serial;
  
  delay(5000); // 延迟以确保串口初始化完成

  // 中位校准
  sms_sts.CalibrationOfs(1);
  sms_sts.CalibrationOfs(2);
  sms_sts.CalibrationOfs(3);
  sms_sts.CalibrationOfs(4);
  sms_sts.CalibrationOfs(5);
  sms_sts.CalibrationOfs(6);
  delay(1000); // 延迟以确保校准完成
  Serial.println("Reading initial positions");
  // 使用FeedBack函数读取当前舵机位置作为初始位置
  initial_position_1 = sms_sts.ReadPos(1);
  initial_position_2 = sms_sts.ReadPos(2);
  initial_position_3 = sms_sts.ReadPos(3);
  initial_position_4 = sms_sts.ReadPos(4);
  initial_position_5 = sms_sts.ReadPos(5);
  initial_position_6 = sms_sts.ReadPos(6);
  Serial.print("ID1 init_Pos: ");
  Serial.println(initial_position_1);
  Serial.print("ID2 init_Pos: ");
  Serial.println(initial_position_2);
  Serial.print("ID3 init_Pos: ");
  Serial.println(initial_position_3);
  Serial.print("ID4 init_Pos: ");
  Serial.println(initial_position_4);
  Serial.print("ID5 init_Pos: ");
  Serial.println(initial_position_5);
  Serial.print("ID6 init_Pos: ");
  Serial.println(initial_position_6);
  // 检查读取的位置是否有效
  if (initial_position_1 == -1 || initial_position_2 == -1 || initial_position_3 == -1 || initial_position_4 == -1 || initial_position_5 == -1 || initial_position_6 == -1) {
    Serial.println("Error reading initial positions. Please check the connections and IDs of the servos.");
    while (1); // 停止程序运行
  }


  Serial.println("Setup complete, ready to move.");

  // sms_sts.WritePosEx(1, initial_position_1 + target_position_1, speed_up, 0); // 舵机(ID3)逆时针移动到目标位置
  //   // sms_sts.RegWriteAction();
  // delay(250);

}

void loop() {
  // 三个三个一组，每一组2个大腿舵机，一个小腿舵机
  // 2,6 3,5 为大腿舵机组 , 4、1 为小腿舵机组
  // int target_position_1 = 2000; // 目标位置
  // int target_position = 1200; // 目标位置
  // int target_position_up = 2000; // 目标位置

  // 首先，初始状态要开始拉2，6，4，力大一点，然后拽回去1，3，5.
    //小腿test
    // sms_sts.RegWritePosEx(1, initial_position_1 - target_position_1, speed_up, 0); // 舵机(ID2)逆时针移动到目标位置
    // sms_sts.RegWritePosEx(4, initial_position_4, speed_up, 0); // 舵机(ID3)逆时针移动到目标位置
    // sms_sts.RegWriteAction();
    // // delay(350);
    // delay(250);
  
    //拉264
    
    sms_sts.WritePosEx(1, initial_position_1, speed_up, 0); // 舵机(ID2)逆时针移动到目标位置
    delay(250);
    sms_sts.RegWritePosEx(2, initial_position_2 + target_position_2_6 , speed_2_6, 0); // 舵机(ID2)逆时针移动到目标位置
    sms_sts.RegWritePosEx(6, initial_position_6 - target_position_2_6 , speed_2_6, 0); // 舵机(ID6)逆时针移动到目标位置
    sms_sts.RegWritePosEx(4, initial_position_4 + target_position_4, speed_up, 0); // 舵机(ID3)逆时针移动到目标位置
    
    // sms_sts.RegWritePosEx(1, initial_position_1 - target_position_1, speed_up, 0); // 舵机(ID2)逆时针移动到目标位置
    // // sms_sts.RegWriteAction();
   
    sms_sts.RegWritePosEx(3, initial_position_3, speed, 0); // 舵机(ID3)移动到初始位置
    sms_sts.RegWritePosEx(5, initial_position_5, speed, 0); // 舵机(ID5)移动到初始位置
    
    sms_sts.RegWriteAction();
    delay(250);
    sms_sts.WritePosEx(4, initial_position_4 + target_position_4, speed_up, 0); // 舵机(ID3)逆时针移动到目标位置
    delay(50);
    // sms_sts.WritePosEx(1, initial_position_1 - target_position_1, speed_up, 0); // 舵机(ID2)逆时针移动到目标位置
    // delay(350);



    
    // Pos1 = sms_sts.ReadPos(1);
    // Pos2 = sms_sts.ReadPos(2);
    // Pos3 = sms_sts.ReadPos(3);
    // Pos4 = sms_sts.ReadPos(4);
    // Pos6 = sms_sts.ReadPos(6);
    // Pos5 = sms_sts.ReadPos(5);
    

    
    // Serial.print("ID2 Pos: ");
    // Serial.println(Pos2);
    // Serial.print("ID6 Pos: ");
    // Serial.println(Pos6);
    // Serial.print("ID4 Pos: ");
    // Serial.println(Pos4);
    // Serial.print("ID1 Pos: ");
    // Serial.println(Pos1);
    // Serial.print("ID3 Pos: ");
    // Serial.println(Pos3);
    // Serial.print("ID5 Pos: ");
    // Serial.println(Pos5);
    
   
  
    sms_sts.WritePosEx(4, initial_position_4, speed_up, 0); // 舵机(ID6)移动到初始位置
    delay(50);
    sms_sts.WritePosEx(1, initial_position_1 + target_position_1, speed_up, 0); // 舵机(ID2)逆时针移动到目标位置
    delay(250);
    sms_sts.RegWritePosEx(5, initial_position_5 + target_position_3_5, speed, 0); // 舵机(ID5)逆时针移动到目标位置
    sms_sts.RegWritePosEx(3, initial_position_3 - target_position_3_5, speed, 0); // 舵机(ID3)逆时针移动到目标位置
    
    // sms_sts.RegWriteAction();
    sms_sts.RegWritePosEx(2, initial_position_2, speed_2_6, 0); // 舵机(ID2)移动到初始位置
    sms_sts.RegWritePosEx(6, initial_position_6, speed_2_6, 0); // 舵机(ID6)移动到初始位置
    // sms_sts.RegWritePosEx(4, initial_position_4, speed_up, 0); // 舵机(ID6)移动到初始位置
    sms_sts.RegWriteAction();
    delay(250);
    Serial.println("大腿前拉,小腿不变");
    delay(100);

    
   
    Serial.println("大腿不变,小腿下拉");
    delay(100);
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
  
    // delay(1000);
   

  Serial.println("loop over!!!!!!!");
}
void stand(){


}
