#include <Servo.h> //Import Servo Libary
#include <Wire.h>
#include <LiquidCrystal_I2C.h> // Import LCD Libary

LiquidCrystal_I2C lcd(0x27, 20, 4); // set the LCD address to 0x27 for a 16 chars and 2 line display
Servo myservo;
const int trigPin = 12; //กำหนดตัวแปรportที่ต่อกับขาTrig ของ Ultrasonic Distance Sensor
const int echoPin = 13; //กำหนดตัวแปรportที่ต่อกับขาEcho ของ Ultrasonic Distance Sensor
long tmeduration;
int distance;



void setup() {

  myservo.attach(3); //ช่องที่ Servo motor ไปต่อ
  pinMode(trigPin, OUTPUT); //pinMode ขา Trig ของ Ultrasonic Distance Sensor
  pinMode(echoPin, INPUT);//pinMode ขา Echo ของ Ultrasonic Distance Sensor
  Serial.begin(9600);// อ่านค่าผ่านSerial Monitor
  lcd.init();        // initialize the lcd
  lcd.backlight();   // กำหนดให้พื้นหลังไฟLCDติด
}

void loop() {
  digitalWrite(trigPin, LOW); 
  delay(2);
  digitalWrite(trigPin, HIGH);
  delay(10);
  digitalWrite(trigPin, LOW);

  tmeduration = pulseIn(echoPin, HIGH);
  distance = (0.034 * tmeduration) / 2;


  if (distance >= 200) { //ถ้าระยะห่างมากกว่าหรือเท่ากับ 200 เซนติเมตร ให้ทำคำสั่งข้างล่างนี้

    myservo.write(90); //ขยับไปที่ 90 องศา
    lcd.setCursor(0, 0); //กำหนดให้ lcd ตำแหน่งที่ 0 บรรทัดที่ 1 แสดงผล
    lcd.print("The Door closing"); //แสดงผลเป็นข้อความ
    delay(1000); //ดีเลย์ 1 วินาที ระหว่างคำสั่งข้างบนกับข้างล่าง
    lcd.setCursor(0, 1); //กำหนดให้ lcd ตำแหน่งที่ 0 บรรทัดที่ 2 แสดงผล
    lcd.print("See you later"); //แสดงผลเป็นข้อความ
    delay(5000); //ดีเลย์ 5 วินาที ระหว่างคำสั่งข้างบนกับข้างล่าง
    lcd.clear(); //ทำการ clear คำสั่งเก่า เพื่อไม่ให้คำสั่งทับซ้อนกัน
    delay(1000); //ดีเลย์ 1 วินาที ก่อนจบการทำงาน
  }
  else { //แต่ถ้าระยะห่างน้อยกว่า 200 เซนติเมตร ให้ทำคำสั่งข้างล่างนี้แทน
    myservo.write(0); //ขยับไปที่ 0 องศา
    lcd.setCursor(0, 0); //กำหนดให้ lcd ตำแหน่งที่ 0 บรรทัดที่ 1 แสดงผล
    lcd.print("hello everyone"); //แสดงผลเป็นข้อความ
    delay(1000); //ดีเลย์ 1 วินาที ระหว่างคำสั่งข้างบนกับข้างล่าง
    lcd.setCursor(0, 1); //กำหนดให้ lcd ตำแหน่งที่ 0 บรรทัดที่ 2 แสดงผล
    lcd.print("welcome!!"); //แสดงผลเป็นข้อความ
    delay(5000); //ดีเลย์ 5 วินาที ระหว่างคำสั่งข้างบนกับข้างล่าง
    lcd.clear();
    delay(1000); //ดีเลย์ 1 วินาที ก่อนจบการทำงาน
  }

  Serial.print("distance:"); //แสดงผลเป็นข้อความ
  Serial.println(distance); //แสดงผลระยะห่าง

  delay(1); //ดีเลย์ 0.001 วินาที

}

