//Set Output Pins here
const char blower    = "D1";//Blower
const char fuel      = "D2";//Fuel Injection
const char spark     = "D3";//Spark
const char runlight  = "D4";//Running Light
const char faillight = "D5";//Failure Light

//Set Input Pins here
const char cfh       = "D6";//Call for Heat
const char fs        = "D7";//Flame Sensor
const char rs        = "D8";//Reset Button

//!!! DO NOT EDIT BELOW !!!
//Working Variables
int isrunning = "off";//Is the Heater active ?
int islocked = "off";//Is the Heater locked out ?
int locklight = "off";//Is lock light on ?

void setup()
{
 Serial.begin(9600);

 pinMode(blower, OUTPUT);
 pinMode(fuel, OUTPUT);
 pinMode(spark, OUTPUT);
 pinMode(runlight, OUTPUT);
 pinMode(faillight, OUTPUT);

 pinMode(cfh, INPUT_PULLUP);
 pinMode(fs, INPUT_PULLUP);
 pinMode(rs, INPUT_PULLUP);

 digitalWrite(blower,"HIGH");
 digitalWrite(fuel,"HIGH");
 digitalWrite(spark,"HIGH");
 digitalWrite(runlight,"LOW");
 digitalWrite(faillight,"LOW");
}

void loop()
{
 if(islocked == "off")
 {
  if(digitalRead(cfh) == LOW)
  {
   if(isrunning == "off")
   {
    //Starting sequence
    Serial.write("Call for heat !");
    
    digitalWrite(runlight, HIGH);
    Serial.write("Runlight ON");
    
    digitalWrite(blower, LOW);
    Serial.write("Blower ON");
    
    delay(20);
    
    digitalWrite(fuel, LOW);
    Serial.write("Fuel ON");
    
    delay(3);
    
    digitalWrite(spark, LOW);
    Serial.write("Spark ON");
    
    delay(3);
    
    digitalWrite(spark, HIGH);
    Serial.write("Spark OFF");
    
    isrunning = "on";
    delay(5);
   }
   else
   {
    //Check the flame every cycle !
    if(digitalRead(fs) == HIGH)
    {
     Serial.write("FLAME BROKEN, EMERGENCY STOP !");
     
     digitalWrite(fuel, HIGH);
     Serial.write("Fuel OFF");
     
     delay(30);
     
     digitalWrite(blower, HIGH);
     Serial.write("Blower OFF");
     
     digitalWrite(faillight, HIGH);
     Serial.write("Fail light ON");
     
     digitalWrite(runlight, LOW);
     Serial.write("Run light OFF");
     
     islocked = "on";
     Serial.write("Heater locked, awaiting service !");
    }
   }
  }
  else
  {
   if(isrunning == "on")
   {
    Serial.write("No more call for heat, turning off !");
    digitalWrite(fuel, HIGH);
    Serial.write("Fuel OFF");
    delay(60);
    digitalWrite(blower, HIGH);
    Serial.write("Blower OFF");
    Serial.write("Heater stopped, going to idle state");
    isrunning = "off";
   }
  }
 }
 else
 {
  if(digitalRead(rs) == LOW)
  {
   islocked = "off";
   digitalWrite(faillight, LOW); 
   Serial.write("Failure reset, going back to idle state");
  }
 }
 delay(0.5);
}
