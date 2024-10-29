/*SmartBrew: The Autonomous Robot Coffee Maker using IOT*/

//COMPONENTS LIST

//Coffee Maker Mechanism Section

//Liquid_Crystal_Display_I2C
//Servo_Cup_D1
//Servo_Black_Coffee_D2
//Servo_3n1_Coffee_D3
//Servo_Sugar_D4
//Water_pump_D5
//IR Sersor_Cup_D6
//Relay_Water_heater_D7
//Stepper_Motor_D8_D9

//Robot Wheels Mechanism Section

//Relay_DC_MotorLeft
//Relay_DC_MotorRight
//Color_Sensor_Left
//Color_Sensor_Right
//IR_Sensor_Left
//IR_Sensor_Right
//Ultrasonic_Sensor_Front_Buttom
//Ultrasonic_Sensor_Front_Middle
//Ultrasonic_Sensor_Back_Buttom
//Ultrasonic_Sensor_Back_Middle
//Current_Sensor_Left
//Current_Sensor_Right

//#include <ESP8266WebServer.h>
//#include <ESP8266WiFi.h>
//#include <LiquidCrystal_I2C.h>
//#include <Stepper.h>
//#include <Wire.h>
#include <LiquidCrystal.h>
#include <Servo.h>

/*Display_section*/
//LiquidCrystal_I2C lcd(0x27,16,2);
const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


/*Button for manually selection_LCD section*/
const int Next = 3;   //Next Button
const int Select = 4; //Next Button

/*Variety of Coffee_LCD section*/
const char* CoffeeVarieties[] = {"Black Coffee", "Caramel"};
int selectedIndex = 0;

/*WiFi SSID and PASSWORD*/
//const char* ssid = "Kodic";
//const char* password = "kodicpogi21";

/*Server port*/
//ESP8266WebServer server(80);

/*Coffee maker ingredients dropper section*/
Servo Cup;               //Wemos pin no.1 or D1 
Servo Black_Coffee;      //Wemos pin no.2 or D2

//Wemos D1 Master and Arduino uno Slave Connection 

//D3 is SCL
//D4 is SDA

Servo Caramel_Coffee;    //Wemos pin no.3 or D5
Servo Sugar;             //Wemos pin no.4 or D6

/*Servo open*/
const int BlackCoffeePosition = 90;     
const int CaramelCoffeePosition = 90;
const int SugarPosition = 90;
const int CupPosition = 90;

/*Original position of each servo*/
const int ServoClosed = 0;

//int Cup_Sensor = A0;     //Wemos analog pin Zero
//int Hot_Water = D7;      //Wemos pin no.5 to Motor Driver L298n
//int Heater = D8;         //Wemos pin no.7 to Input no.5 in Relay
//int Dir_Pin = D9;        //Wemos pin no.8 to DirPin of A4988
//int Step_Pin = D10;      //Wemos pin no.9 to StepPin of A4988

/*
 * This section is for Slave "Arduino uno"
 * Robot wheels and sensor pins that are connected to 8 Channel Relay
int Left_Forward = 2;  //Arduino pin no.2 to Input no.1 in Relay
int Left_Reverse = 3;  //Arduino pin no.3 to Input no.2 in Relay
int Right_Forward = 4; //Arduino pin no.4 to Input no.3 in Relay
int Right_Reverse = 5; //Arduino pin no.5 to Input no.4 in Relay

 * Line and Color Sensor detector pins 

//int IR_Left = A0;        //Arduino analog pin Zero
//int IR_Right = A1;       //Arduino analog pin no.1

*/

void setup() {
  /*Display*/
  lcd.begin(16, 2);
  //lcd.backlight();

  /*Button for manual selection*/
  pinMode(Next, INPUT_PULLUP);
  pinMode(Select, INPUT_PULLUP);

  /*Display selection*/
  displaySelection();
  
  /*Coffee dropper mechanism section using Servo motor*/
  Cup.attach(13);              //Cup dropper
  Black_Coffee.attach(2);     //Black coffee dropper
  Caramel_Coffee.attach(5);   //3n1 coffee dropper
  Sugar.attach(6);            //Sugar dropper
  
  /*pinMode section for Coffee dropper mechanism*/
  //pinMode(Hot_Water, OUTPUT);  //Water pump connected to Motor Driver
  //pinMode(Cup_Sensor, INPUT);  //IR Sensor for Cup 
  //pinMode(Heater, OUTPUT);     //PTC Heater connected to Relay Common and it is Input no.5

  /*pinMode for Stepper motor*/
  //pinMode(Dir_Pin, OUTPUT);    //A4988 Direction pin
  //pinMode(Step_Pin, OUTPUT);   //A4988 Step pin
  
/*
 * Wemos D1 Master and Arduino uno Slave
 
  //pinMode section for Robot Wheels 
  
  pinMode(Left_Forward, OUTPUT);  //Connected to Common1 or Input no.1 in Relay
  pinMode(Left_Reverse, OUTPUT);  //Connected to Common2 or Input no.2 in Relay
  pinMode(Right_Forward, OUTPUT); //Connected to Common3 or Input no.3 in Relay
  pinMode(Right_Reverse, OUTPUT); //Connected to Common4 or Input no.4 in Relay


  //Line Sensor 
  
   * This is for Slave "Arduino uno"
  pinMode(IR_Left, INPUT);        //Analog Input pin no.1
  pinMode(IR_Right, INPUT);       //Analog Input pin no.2
  
*/
  /*Connect to WiFi*/
  //WiFi.begin(ssid, password);
  //while(WiFi.status() != WL_CONNECTED){
    //delay(500);
  //}
  //server.on("/", handleRoot);
  //server.on("/order", handleOrder);
  //server.begin();

  Serial.begin(9600);

}

void loop() {
  /*Web Server loop*/
  //server.handleClient();
  
/*If Next button is pressed*/
  if(digitalRead(Next) == LOW){
    selectedIndex = (selectedIndex + 1) % 2; //Loop doon sa option
    displaySelection();
    delay(300);
  }
/*If Select button is pressed*/
  if(digitalRead(Select) == LOW){
    serveCoffee(selectedIndex);
    delay(300);
  }

/*This are the code that I will use to control the Servo Coffee Mechanism*/

  //Opening of Servo = 90;
  
  //Cup.write(CupPosition);
  //Black_Coffee.write(BlackCoffeePosition);
  //Caramel_Coffee.write(CaramelCoffeePosition);
  //Sugar.write(SugarPosition);

  //Back to original position = 0;
  
  //Cup.write(ServoClosed);
  //Black_Coffee.write(ServoClosed);
  //Caramel_Coffee.write(ServoClosed);
  //Sugar.write(ServoClosed);
}
void displaySelection(){
  /*Display Feedback*/
  lcd.clear();
  lcd.print("Select ur Coffee: ");
  lcd.setCursor(0, 1);
  lcd.print(CoffeeVarieties[selectedIndex]);
}
void serveCoffee(int index){
  /*Dispensing the Cup and kinds of Coffee*/
  Cup.write(180);
  delay(400);
  Cup.write(0);

  switch (index){
    // Black Coffee
    case 0:                                
      Black_Coffee.write(BlackCoffeePosition);
      delay(500);                             //Pouring of Black Coffee
      Black_Coffee.write(ServoClosed);
      break;
    case 1:
      Caramel_Coffee.write(CaramelCoffeePosition);
      delay(500);                             //Pouring of Caramel
      Caramel_Coffee.write(ServoClosed);
      break;
  }
    Sugar.write(180);
    delay(1000);
    Sugar.write(90);
}
//void handleRoot(){
  //String html = "<html><body><h1>Select Coffee</h1>";
  //for(int i = 0; i < 2; i++){
    //html += "<form action='/order' method='GET'>";
    //html += "<input type='hidden' name='type' value='"+ String(i)+"'>";
    //html += "</form>";
  //}
  //html += "</body><html>";
  //server.send(200, "text/html", html);
//}
//void handleOrder(){
  //if(server.hasArg("type")){
    //int coffeeType = server.arg("type").toInt();
    //serveCoffee(coffeeType);
  //}
  //server.send(200, "text/html", "<h1>Order received!</h1><a href='/'>Back</a>");
//}
