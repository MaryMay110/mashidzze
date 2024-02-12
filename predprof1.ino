#include <Servo.h>
#include <SoftwareSerial.h>
#include <AccelStepper.h>
#include <Thread.h>
#include <GyverOLED.h>
#define TX A0
#define RX A1
#define MAX_DICTIONARY_SIZE 10
GyverOLED<SSD1306_128x64, OLED_NO_BUFFER> oledDisplay;
String keys[MAX_DICTIONARY_SIZE];*
char values[MAX_DICTIONARY_SIZE];
int dict_size = 0;
Servo servo_to_take;
int y = 30000;
int cnt = 0;
int count_value = 0;
Thread rasberyThread = Thread();
Thread getAppThread = Thread();
Thread stoppingThread = Thread();
unsigned long time; 
unsigned long take_cubic = 30000;
SoftwareSerial bluetooth(RX, TX);
SoftwareSerial BTSerial(RX, TX);
AccelStepper mistepper(4, 10, 12, 11, 13);
AccelStepper mrstepper(4, 6, 8, 7, 9);
AccelStepper mlstepper(4, 2, 4, 3, 5);
char camebite;
int e = 0;
int r = 1;
char* stroka1;
char* stroka2;
char* stroka3;
char* stroka4;
char* stroka5;
char* stroka6;
char* stroka7;
char* stroka8;
char* stroka9;
char* stroka10;
bool shouldRun;
char comandy[10];
char values_FRas[1];
String keys_berry[1];
String num_values[1];
int num = 0;
int t = 0;
void addTD(String key, char value) {
  if (dict_size < MAX_DICTIONARY_SIZE) {
    keys[dict_size] = key;
    values[dict_size] = value;
    dict_size++;
  }
}

char getterFromDict(String key) {
  for (int i = 0; i < dict_size; i++) {
    if (keys[i] == key) {
      return values[i];
    }
  }
}

void setup() {
  zero(comandy);
  addTD("винты", '1');
  addTD("гайки",'2');
  addTD("шайбы",'3');
  addTD("шпильки",'4');
  addTD("подшиники",'5');
  addTD("лин. напр.",'6');
  addTD("валы",'7');
  addTD("двигатели",'8');
  addTD("датчики",'9');
  servo_to_take.attach(A2);
  oledDisplay.init();      
  oledDisplay.clear();       
  oledDisplay.setScale(3);  
  oledDisplay.home();     
  Serial.begin(9600);
  BTSerial.begin(9600);
  stroka1 = "1";
  stroka2 = "2";
  stroka3 = "3";
  stroka4 = "4";
  stroka5 = "5";
  stroka6 = "6";
  stroka7 = "7";
  stroka8 = "8";
  stroka9 = "9";
  stroka10 ="0";
  stoppingThread.onRun(ifStopped);
  stoppingThread.setInterval(10);
  rasberyThread.onRun(berry);
  rasberyThread.setInterval(10);
  getAppThread.onRun(getApp);
  getAppThread.setInterval(10);
  bluetooth.begin(9600);
  mlstepper.setMaxSpeed(300.0);
  mlstepper.setAcceleration(100.0);
  mlstepper.setSpeed(300);
  mlstepper.setCurrentPosition(0);
  
  mistepper.setMaxSpeed(1000.0);
  mistepper.setAcceleration(100.0);
  mistepper.setSpeed(1000);
  mistepper.setCurrentPosition(0);
  
  mrstepper.setMaxSpeed(1000.0);
  mrstepper.setAcceleration(100.0);
  mrstepper.setSpeed(1000);
  mrstepper.setCurrentPosition(0);
}

void displaying(){
    if (num_values[0] != keys_berry[0]){
      oledDisplay.print(keys_berry[0]);
      num_values[0] = keys_berry[0];
    }
  }
char perebor(char f[], char value[]){
  int cont = 0;
  for(int g=0; g<9; g++){
    if (f[g] == value[0]){
      f[g] = '0';
      cont= cont+1;
      }
    }
    if (cont > 0){
      return '1';
      }
    else if(cont == 0){
      return '0';
      }
  }
void zero(char list0[]){
    for(int p = 1;p < 11; p++ ){
    list0[p] = '0';
    }
  }

int count_zero(char list1[]){
  int cont = 0;
  for(int c=1; c<11;c++){
    if (list1[c] == '0'){
      cont++;
      }
    }
    return cont;
  }
void loop() {
  unsigned long curMillis = millis();
  if (getAppThread.shouldRun()){
  getAppThread.run();
  }
  if (rasberyThread.shouldRun()){
    rasberyThread.run();
  }
  if (stoppingThread.shouldRun()){
    stoppingThread.run();
    }
    servo_to_take.write(70);
   if (comandy[0]=='o' and values_FRas[0] !='0'){
    if(curMillis < 20000){
      displaying();
        for(int g=0; g<9; g++){
    if (comandy[g] == values_FRas[0]){
      comandy[g] = '0';
      mlstepper.moveTo(600);
      mlstepper.runToPosition();
      servo_to_take.write(70);
      mrstepper.moveTo(-900);
      mrstepper.runToPosition();
        servo_to_take.write(110);
   mrstepper.moveTo(1000);
  mrstepper.runToPosition();   
    servo_to_take.write(70);
mlstepper.moveTo(0);
mlstepper.runToPosition();    
      }
    }
    BTSerial.write(stroka1, strlen(stroka1));
    }
if(curMillis > 20000 and curMillis < 40000){
  BTSerial.write(stroka1, strlen(stroka1));
mlstepper.runToPosition();
mistepper.moveTo(3000);
mistepper.runToPosition();
mistepper.stop();
oledDisplay.clear();
oledDisplay.home();
}
    if(curMillis < 60000 and curMillis > 40000){
      
displaying();
        for(int g=0; g<9; g++){
    if (comandy[g] == values_FRas[0]){
      comandy[g] = '0';
      mlstepper.moveTo(600);
      mlstepper.runToPosition();
                servo_to_take.write(70);
      mrstepper.moveTo(-700);
      mrstepper.runToPosition();    
    servo_to_take.write(110);
        mrstepper.moveTo(800);
  mrstepper.runToPosition();   
    servo_to_take.write(70);
  mlstepper.moveTo(0);
  mlstepper.runToPosition();
      }
    }
    BTSerial.write(stroka2, strlen(stroka2));
      }
if(curMillis < 80000 and curMillis > 60000){
  BTSerial.write(stroka2, strlen(stroka2));
mistepper.moveTo(6000);
mistepper.runToPosition();
mistepper.stop();
oledDisplay.clear(); 
oledDisplay.home();
}
     if(curMillis < 100000 and curMillis > 80000){
      
displaying();
        for(int g=0; g<9; g++){
    if (comandy[g] == values_FRas[0]){
      comandy[g] = '0';
      mlstepper.moveTo(600);
      mlstepper.runToPosition();
                servo_to_take.write(70);
      mrstepper.moveTo(-700);
      mrstepper.runToPosition();    
    servo_to_take.write(110);
  mrstepper.moveTo(800);
  mrstepper.runToPosition();   
    servo_to_take.write(70);
    mlstepper.moveTo(0);
    mrstepper.runToPosition(); 
    
      }
    }
BTSerial.write(stroka3, strlen(stroka3));  
   }
   if (curMillis > 100000 and curMillis < 120000){
    BTSerial.write(stroka3, strlen(stroka3));  
    mlstepper.moveTo(2900);
mlstepper.runToPosition();
mlstepper.stop();
oledDisplay.clear();
oledDisplay.home();
    }
       if(curMillis > 120000 and curMillis < 140000){
      displaying();
        for(int g=0; g<9; g++){
    if (comandy[g] == values_FRas[0]){
      comandy[g] = '0';
      mlstepper.moveTo(3500);
      mrstepper.runToPosition(); 
          servo_to_take.write(70);
      mrstepper.moveTo(-700);
      mrstepper.runToPosition();    
    servo_to_take.write(110);
  mrstepper.moveTo(800);
  mrstepper.runToPosition();   
    servo_to_take.write(70);
    mlstepper.moveTo(2900);
    mrstepper.runToPosition();
    
      }
    }
    BTSerial.write(stroka4, strlen(stroka4));
    }
if(curMillis > 140000 and curMillis < 160000){
mistepper.moveTo(3000);
mistepper.runToPosition();
mistepper.stop();
oledDisplay.clear();
oledDisplay.home();
}
    if(curMillis < 180000 and curMillis > 160000){
      
displaying();
        for(int g=0; g<9; g++){
    if (comandy[g] == values_FRas[0]){
      comandy[g] = '0';
      mlstepper.moveTo(3500);
      mrstepper.runToPosition();  
                servo_to_take.write(70);
      mrstepper.moveTo(-700);
      mrstepper.runToPosition();    
    servo_to_take.write(110);
  mrstepper.moveTo(800);
  mrstepper.runToPosition();   
    servo_to_take.write(70);
     mlstepper.moveTo(2900);
    mrstepper.runToPosition();  
      }
    }
    BTSerial.write(stroka5, strlen(stroka5));
      }
if(curMillis < 200000 and curMillis > 180000){
mistepper.moveTo(0);
mistepper.runToPosition();
mistepper.stop();
oledDisplay.clear(); 
oledDisplay.home();
}

if (curMillis > 220000 and curMillis < 240000){
  displaying();
        for(int g=0; g<9; g++){
    if (comandy[g] == values_FRas[0]){
      comandy[g] = '0';
      mlstepper.moveTo(3500);
      mrstepper.runToPosition();
                servo_to_take.write(70);
      mrstepper.moveTo(-700);
      mrstepper.runToPosition();    
    servo_to_take.write(110);
  mrstepper.moveTo(800);
  mrstepper.runToPosition();   
    servo_to_take.write(70);
    mlstepper.moveTo(5800);
    mrstepper.runToPosition();
      }
    }
    BTSerial.write(stroka6, strlen(stroka6));
  }
if (curMillis > 240000 and curMillis < 260000){
  mlstepper.moveTo(2900);
      mlstepper.moveTo(5800);
mlstepper.runToPosition();
mlstepper.stop();
oledDisplay.clear();
oledDisplay.home();
  }
if(curMillis < 280000 and curMillis > 260000){
      displaying();
        for(int g=0; g<9; g++){
    if (comandy[g] == values_FRas[0]){
      comandy[g] = '0';
      mlstepper.moveTo(6000);
      mrstepper.runToPosition();
          servo_to_take.write(70);
      mrstepper.moveTo(-700);
      mrstepper.runToPosition();    
    servo_to_take.write(110);
  mrstepper.moveTo(800);
  mrstepper.runToPosition();   
    servo_to_take.write(70);
    mlstepper.moveTo(5800);
    mrstepper.runToPosition();
      }
    }
    BTSerial.write(stroka7, strlen(stroka7));
    }
if(curMillis > 280000 and curMillis < 300000){
  mlstepper.moveTo(5800);
mistepper.moveTo(3000);
mistepper.runToPosition();
mistepper.stop();
oledDisplay.clear();
oledDisplay.home();
}
    if(curMillis < 320000 and curMillis > 300000){
      
displaying();
        for(int g=0; g<9; g++){
    if (comandy[g] == values_FRas[0]){
      comandy[g] = '0';
      mlstepper.moveTo(6000);
                servo_to_take.write(70);
      mrstepper.moveTo(-700);
      mrstepper.runToPosition();    
    servo_to_take.write(110);
  mrstepper.moveTo(800);
  mrstepper.runToPosition();   
    servo_to_take.write(70);
      }
    }
    BTSerial.write(stroka8, strlen(stroka8));
      }
if(curMillis < 340000 and curMillis > 320000){
  mlstepper.moveTo(5800);
mistepper.moveTo(6000);
mistepper.runToPosition();
mistepper.stop();
oledDisplay.clear(); 
oledDisplay.home();
}

    
}
}


void berry(){
     if(Serial.available() > 0){
    String data = Serial.readStringUntil('\n');
    char value = getterFromDict(data);
    values_FRas[0] = value;
    keys_berry[0] = data;
  }
  }
void getApp(){
  if (bluetooth.available() > 0) {
    char command = bluetooth.read();
    Serial.println(command);
    if(command=='o'){comandy[0] = 'o';}
    if(command=='1'){comandy[1] = '1';}
    if(command=='2'){comandy[2] = '2';}
    if(command=='3'){comandy[3] = '3';}
    if(command=='4'){comandy[4] = '4';}
    if(command=='5'){comandy[5] = '5';}
    if(command=='6'){comandy[6] = '6';}
    if(command=='7'){comandy[7] = '7';}
    if(command=='8'){comandy[8] = '8';}
    if(command=='9'){comandy[9] = '9';}
    if(command=='f'){zero(comandy);}
  }
}

void ifStopped(){
      if (count_zero(comandy) == 9) {
      mistepper.moveTo(0);
      mistepper.runToPosition();
      mistepper.stop();

      mlstepper.moveTo(0);
      mlstepper.runToPosition();
      mlstepper.stop();
      }
  }
