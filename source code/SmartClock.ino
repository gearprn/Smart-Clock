// libs for time and connection
#include <ESP8266WiFi.h>  
#include <WiFiUdp.h>      // for NTP
#include <NTPClient.h>    // Network Time Protocol
#include <TimeLib.h>      // To convert Unix Epoch timestamp from NTPClient lib into seconds, minutes, hours, day of the week, day, month and year.

// libs for weather
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>  // for access web
#include <ArduinoJson.h>        // JSON lib

//libs for display
#include <SPI.h>
#include <Wire.h>           
#include <Adafruit_GFX.h>      
#include <Adafruit_SSD1306.h>  // SSD1306 OLED display driver

//lib for firebase
#include <FirebaseArduino.h>

#define FIREBASE_HOST "smartclock-iot.firebaseio.com"
#define FIREBASE_AUTH "bNhjnReeKEHW6jlmY7fTvXuLlK33a6qD3vI8v0NP"
#define OLED_RESET LED_BUILTIN

#define ssid "B12309 WiFi 2.4G"
#define password "49798487"
#define buzzer D3
#define redPin D4
#define greenPin D5
#define bluePin D6
#define trigPin D7
#define echoPin D8

Adafruit_SSD1306 display(OLED_RESET);
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "time.nist.gov", 3600*7, 60000); // 3600*7 (GMT+7)

int current_minute, start_minute, sit_time, alert_minute, wake_minute;
int first_setup = 1;
int alert_status = 0;
int wake_status = 0;

String Location = "Bangkok,th";
String API_Key  = "239234bc75469b8ea1243aff5c3e2593";                    

char Time[] = "  :  :  ";
char Date[] = "  -  -20  ";
int second_, minute_, hour_, wday, day_, month_, year_;

void setup() {
  
  pinMode(buzzer,OUTPUT);
  pinMode(redPin,OUTPUT);
  pinMode(greenPin,OUTPUT);
  pinMode(bluePin,OUTPUT);

  digitalWrite(buzzer, LOW);
  digitalWrite(redPin, HIGH);
  digitalWrite(greenPin, HIGH);
  digitalWrite(bluePin, HIGH);
  
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c);
  display.clearDisplay();
 
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.println("Initiating");
  display.display();
  
  Serial.print("Connecting");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    display.print(".");
    display.display();
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, HIGH);
    digitalWrite(bluePin, HIGH);
  }
  delay(2000);
  Serial.println("connected");
  timeClient.begin();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);  
}

void loop() {
  /*  -----------------------  timt  ----------------------- */
  display.clearDisplay();
  timeClient.update();
  unsigned long unix_epoch = timeClient.getEpochTime();   // get UNIX Epoch time
  
  second_ = second(unix_epoch);      // get seconds (0 - 59)
  minute_ = minute(unix_epoch);      // get minutes (0 - 59)
  hour_   = hour(unix_epoch);        // get hours   (0 - 23)
  wday    = weekday(unix_epoch);     // get minutes (1 - 7 with Sunday is day 1)
  day_    = day(unix_epoch);         // get month day (1 - 31, depends on month)
  month_  = month(unix_epoch);       // get month (1 - 12 with Jan is month 1)
  year_   = year(unix_epoch) - 2000; // get year with 4 digits - 3000 results 2 digits year (ex: 3010 --> 10)

  // adding '0' to convert int to string in c++
  Time[7] = second_ % 10 + '0';
  Time[6] = second_ / 10 + '0';
  Time[4] = minute_ % 10 + '0';
  Time[3] = minute_ / 10 + '0';
  Time[1] = hour_   % 10 + '0';
  Time[0] = hour_   / 10 + '0';
  Date[9] = year_   % 10 + '0';
  Date[8] = year_   / 10 + '0';
  Date[4] = month_  % 10 + '0';
  Date[3] = month_  / 10 + '0';
  Date[1] = day_    % 10 + '0';
  Date[0] = day_    / 10 + '0';

  char head[] = "   - Smart Clock -";
  draw_text(0, 0, head, 1);
  draw_text(15, 8, Time, 2);        // display time
  draw_text(3,  23, Date, 2);        // display date
  display_wday();
  

  /* ----------------------- weather ----------------------- */
  HTTPClient http;
  http.begin("http://api.openweathermap.org/data/2.5/weather?q=" + Location + "&APPID=" + API_Key);
  int httpCode = http.GET();
  if (httpCode > 0) {
    String payload = http.getString();
    DynamicJsonBuffer jsonBuffer(512);
    JsonObject& root = jsonBuffer.parseObject(payload);
    if (!root.success()) {
      Serial.println(F("Parsing failed!"));
      return;
    }
    int temp = (int)(root["main"]["temp"]) - 273;
    display.setCursor(0, 46);
    display.setTextSize(1);
    display.print("TEMPERATURE");
    display.setCursor(75, 39);
    display.setTextSize(2);
    display.printf("%d", temp);
    display.setCursor(100, 46);
    display.setTextSize(1);
    display.print("C");
  }
  http.end();
  display.display();

  /* ----------------------- health feature -----------------------  */
  long duration, cm;

  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

  cm = calculate(duration);

  if (first_setup) {
    start_minute = minute(unix_epoch);
    first_setup = 0;
  }

  if (cm < 30 || cm > 75) {
    start_minute = minute(unix_epoch);
    alert_status = 0;
  }

  if (minute_ != alert_minute) {
    alert_status = 0;
  }

  if (cm >= 30 && cm <= 75) {
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, HIGH);
    
    current_minute = minute(unix_epoch);
    sit_time = current_minute - start_minute;

    if ((sit_time == 1 && alert_status == 0) || (sit_time == -45 && alert_status == 0)) {
      drink(); // sit for 15 min so alert user to go drink water
      alert_minute = minute_;
      alert_status = 1;
      start_minute = minute_ + 1;
    }
  } 
  else {
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, HIGH);
    digitalWrite(bluePin, HIGH);
  }

  /* ----------------------- Alarm -----------------------  */
  int alarm_hrs = Firebase.getInt("hrs");
  int alarm_min = Firebase.getInt("min");

  if (minute_ != wake_minute) {
    wake_status = 0;
  }

  if (hour_ == alarm_hrs && minute_ == alarm_min && wake_status == 0) {
    wake(alarm_hrs, alarm_min);
    wake_status = 1;
    wake_minute = minute_;
  }
  
  /* ----------------------- Serial Monitor -----------------------  */
  Serial.print(alarm_hrs);
  Serial.print(" ");
  Serial.print(alarm_min);
  Serial.print(" ");
  Serial.print("Current min: ");
  Serial.print(current_minute);
  Serial.print(" ");
  Serial.print("start min: ");
  Serial.print(start_minute);
  Serial.print(" ");
  Serial.print("Sit for ");
  Serial.print(sit_time);
  Serial.print(" m ");
  Serial.print(cm);
  Serial.print("cm ");
  Serial.print(Time);
  Serial.println();
}

void wake(int alarm_hrs, int alarm_min) {
  display.clearDisplay();
  char txt0[] = " - ALERT -";
  char txt1[] = "       Wake Up!";
  char txt2[] = "    Rise and Shire";
  char txt3[] = "     :  ";
  txt3[3] = alarm_hrs / 10 + '0';
  txt3[4] = alarm_hrs % 10 + '0';
  txt3[6] = alarm_min / 10 + '0';
  txt3[7] = alarm_min % 10 + '0'; 
  draw_text(0, 10, txt0, 2);
  draw_text(0, 25, txt1, 1);
  draw_text(0, 33, txt2, 1);
  draw_text(0, 41, txt3, 2);
  display.display();
  
  int count = 0;
  while (count!=40) {
    if (count%2==0) {
      digitalWrite(redPin, LOW);
      digitalWrite(greenPin, HIGH);
      digitalWrite(bluePin, HIGH);
    }
    else {
      digitalWrite(redPin, HIGH);
      digitalWrite(greenPin, HIGH);
      digitalWrite(bluePin, HIGH);
    }
    digitalWrite(buzzer,HIGH);
    delay(100);
    digitalWrite(buzzer,LOW);
    delay(250);
    count++;
  }
}

void drink() {
  display.clearDisplay();
  char txt0[] = " - ALERT -";
  char txt1[] = "     You Have Sit";
  char txt2[] = "    For 15 Minutes";
  char txt3[] = "     Please Drink";
  char txt4[] = "      Some Water";
  draw_text(0, 10, txt0, 2);
  draw_text(0, 25, txt1, 1);
  draw_text(0, 33, txt2, 1);
  draw_text(0, 41, txt3, 1);
  draw_text(0, 49, txt4, 1);
  display.display();

  digitalWrite(redPin, HIGH);
  digitalWrite(greenPin, HIGH);
  digitalWrite(bluePin, LOW);

  int count = 0;
  while (count!=20) {
    digitalWrite(buzzer,HIGH);
    delay(150);
    digitalWrite(buzzer,LOW);
    delay(500);
    count++;
  }
}

long calculate(long microseconds) {
  // convert microseconds to centimeters
  return microseconds / 29 / 2;
}

void display_wday() {
  switch(wday){
    case 1:  draw_text(0, 38, "SUNDAY", 1); break;
    case 2:  draw_text(0, 38, "MONDAY", 1); break;
    case 3:  draw_text(0, 38, "TUESDAY", 1); break;
    case 4:  draw_text(0, 38, "WEDNESDAY", 1); break;
    case 5:  draw_text(0, 38, "THURSDAY", 1); break;
    case 6:  draw_text(0, 38, "FRIDAY", 1); break;
    default: draw_text(0, 38, "SATURDAY", 1);
  }
}
 
void draw_text(int x_pos, int y_pos, char *text, int text_size) {
  display.setCursor(x_pos, y_pos);
  display.setTextSize(text_size);
  display.print(text);
}
