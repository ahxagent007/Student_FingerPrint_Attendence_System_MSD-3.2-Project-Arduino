
#include <Wire.h> 
#include <LiquidCrystal.h>
#include <Keypad.h>
#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>

int displayMode = 0;
int tempID = 0;
String courseNo = "";
String ATTEND_STR = "ID : ";


//WIFI
#define wifi Serial
String wifiSSID = "MSD_STUDENT";
String wifiPASS = "123456789";
String HOST = "192.168.0.105";
String PORT = "5000";
String rxd, getData;
bool connectFlag = false;


//finger print
SoftwareSerial mySerial(10, 11); //RX,TX
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
int id ,getId;
bool fig = false;



//LiquidCrystal lcd(RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(A1, A0, A5, A4, A3, A2); 


//KEYPAD
const byte rows = 4;
const byte cols = 4;

char keys[rows][cols] = {
      {'1','2','3','A'},
      {'4','5','6','B'},
      {'7','8','9','C'},
      {'*','0','#','D'}
  };

byte rowPin[] = {2,3,4,5};
byte colPins[] = {6,7,8,9};

Keypad kpd = Keypad(makeKeymap(keys),rowPin, colPins, rows, cols);

void setup()
{
  
  //WiFi
  wifi.begin(9600);
  
  //LCD
  lcd.begin(20, 4);
  //lcd.print("XIAN");

  //FINGER PRINT  
  finger.begin(57600);
  
  if(finger.verifyPassword()){
    //Serial.println("Found fingerprint sensor!");
    }else{
      //Serial.println("Did not find fingerprint sensor :(");
      }


}


void loop()
{
  //while(connectFlag == false) wifi_init();
  //if(figer) getId = matchFinger();
    

  if(displayMode == 0){
      printMainMenu();
  }else if(displayMode == 1){
      printAddStudent();
  }else if(displayMode == 2){
      printTakeAttend();
  }else if(displayMode == 3){
      printTakingAttendance();
  }else if(displayMode == 4){
      printAttendedStudents();
  }else if(displayMode == 5){
      sendDataToServer();
  }
  

  
}


void printAttendedStudents(){
  lcd.setCursor(0,0);
  lcd.print(ATTEND_STR);
  lcd.setCursor(0,3);
  lcd.print("B: BACK   C: CLEAR");

  char x = kpd.getKey();
    if(x){
      if(x == 'B'){
        displayMode = 0;
        lcd.clear();
        }else if(x == 'C'){
          ATTEND_STR = (String)"ID : ";
          lcd.clear();
          lcd.setCursor(0,2);
          lcd.print("ATTENDANCE CLEARED!");
          sendData("CLEAR");
          delay(1500);
          displayMode = 0;
          lcd.clear();
          }
      
      }
  }


void sendDataToServer(){
  lcd.setCursor(0,1);
  lcd.print("SENDING DATA.");
  delay(200);
  lcd.print(".");
  delay(200);
  lcd.print(".");
  delay(200);
  lcd.print(".");
  delay(200);
  lcd.print(".");
  delay(200);
  lcd.print(".");
  sendData("PRINT");
  delay(500);
  lcd.setCursor(0,3);
  lcd.print("<<<<<<<<DONE>>>>>>>>");
  delay(1500);
  displayMode = 0;
  lcd.clear();
  
  }

void printMainMenu(){
  //lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("A: TAKE ATTENDANCE");
  lcd.setCursor(0,1);
  lcd.print("B: ADD STUDENT");
  lcd.setCursor(0,2);
  lcd.print("C: SEE ATTENDANCE");
  lcd.setCursor(0,3);
  lcd.print("D: SEND DATA");

    char x = kpd.getKey();
    if(x){
      if(x == 'A'){
        
        displayMode = 2;
        lcd.clear();
        
      }else if(x == 'B'){
        
        displayMode = 1;
        lcd.clear();
        
      }else if(x == 'C'){

        displayMode = 4;   //See Attended Students     
        lcd.clear();
        
      }else if(x == 'D'){
        displayMode = 5;   //Send Data to server    
        lcd.clear(); 
      } 
    }
  
  }

void printTakeAttend(){
    lcd.setCursor(0,0);
    lcd.print("ENTER COURSE : ");
    //lcd.setCursor(0,10);

    lcd.setCursor(0,3);
    lcd.print("A: DONE");
    lcd.setCursor(11,3);
    lcd.print("B: CANCEL");
    lcd.setCursor(0,1);

    char x = kpd.getKey();
    if(x){
      if(x == 'A'){
        
        displayMode = 3; //Start Attandence
        lcd.clear();
        
      }else if(x == 'B'){
        displayMode = 0;
        lcd.clear();
      }else{
          courseNo += x;
          lcd.print(courseNo);
      }  
      
    }
    
  }

void printTakingAttendance(){
  lcd.setCursor(0,0);
  lcd.print("ATTENDANCE STARTED!!");
  lcd.setCursor(0,1);
  lcd.print("ENTER YOUR FINGER");
  lcd.setCursor(0,3);
  lcd.print("A: STOP");

  char x = kpd.getKey();
  if(x){
    if(x == 'A'){
      lcd.clear();
      lcd.setCursor(0,2);
      lcd.print("ATTENDANCE FINISHED");
      courseNo = "";
      delay(1000);
      displayMode = 0;
      lcd.clear();
    }  
  }else{
      getId = matchFinger();
      
      if(getId != -1){
        lcd.setCursor(0,2);
        lcd.print("                    ");
        lcd.setCursor(0,2);
        lcd.print("PRESENT ID : "+(String)getId);
        sendData(courseNo+","+(String)getId);
        ATTEND_STR += ", "+(String)getId;
        delay(2000);

        lcd.setCursor(0,2);
        lcd.print("                    ");
        lcd.setCursor(0,2);
        lcd.print("NEXT STUDENT");
        
      }else{

      }
      delay(250);
    
  }
  
}

void printAddStudent(){
    lcd.setCursor(0,0);
    lcd.print("Enter ID : ");
    //lcd.setCursor(0,10);

    lcd.setCursor(0,3);
    lcd.print("A: ADD");
    lcd.setCursor(11,3);
    lcd.print("B: CANCEL");
    lcd.setCursor(11,0);

    char x = kpd.getKey();
    if(x){
      if(x == 'A'){
        id = tempID;
        tempID = 0;
        lcd.setCursor(0,2);
        lcd.print("ADDING ID : "+(String)id);
        delay(1000);
        lcd.clear();
        
        addStudent();
        
      }else if(x == 'B'){
        displayMode = 0;
        lcd.clear();
      }else{
          tempID *= 10;
          tempID += (int)x -48;
          
          lcd.print(tempID);
      }  
      
    }
    
  }

void addStudent(){
  lcd.setCursor(0,0);
  lcd.print("ENTER FINGER FOR");
  lcd.setCursor(0,1);
  lcd.print("ID = "+(String)id);
  bool enroll = fingerEnroll(id);
      if(enroll == true){   
        lcd.clear();
        lcd.setCursor(0,0);       
        lcd.print("STUDENT REGISTERED!");
        lcd.setCursor(0,2);       
        lcd.print("STUDENT ID = "+(String)id);
        delay(1500);
        displayMode = 0; 
        lcd.clear();
        }
  }





bool fingerEnroll(int id) {
  int p = -1;
  //Serial.print("Waiting for valid finger to enroll as #"); Serial.println(id);
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
  }
  
  p = finger.image2Tz(1);
  if (p != FINGERPRINT_OK) return false; 
  
  p = -1;
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
  } 
  
  p = finger.image2Tz(2);
  if (p != FINGERPRINT_OK) return false; 
  
  //Serial.print("Creating model for #");  Serial.println(id);
  
  p = finger.createModel();
  if (p != FINGERPRINT_OK) return false;  
  
  //Serial.print("ID "); Serial.println(id);
  p = finger.storeModel(id);
  if (p != FINGERPRINT_OK) return false; 
  return true; 
}

int matchFinger(){
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;

  //Serial.print("Found ID #"); Serial.println(finger.fingerID); 
  //lcd.print("#"+finger.fingerID);
  return finger.fingerID; 
}


void wifi_init(){
   //------------------------------ configuration
  digitalWrite(LED_BUILTIN, HIGH);
  //wifi.listen();
  wifi.println((String)"AT+CWJAP=\"" + wifiSSID + "\",\"" + wifiPASS + "\"");
  delay(100);
  if(wifi.available() > 0){
    rxd = wifi.readString();
    if(rxd.indexOf("GOT IP") != -1) {
      connectFlag = true;
      wifi.println((String)"AT+CIPSTART=\"TCP\",\"" + HOST + "\","+PORT +"");
      delay(50);
      digitalWrite(LED_BUILTIN, LOW);
    }
    rxd = "";
  }
}

void sendData(String msg){
  digitalWrite(LED_BUILTIN, HIGH);
  int digit = msg.length() + 2;

  wifi.println((String)"AT+CIPSTART=\"TCP\",\"" + HOST + "\","+PORT +"");
  delay(50);
  wifi.println((String)"AT+CIPSEND=" + digit);
  delay(50);
  wifi.println(msg);
  delay(50);
  digitalWrite(LED_BUILTIN, LOW);
}
