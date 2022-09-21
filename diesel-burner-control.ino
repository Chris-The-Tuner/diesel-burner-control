//Set Output Pins here
const char blower    = "D2";//Blower
const char fuel      = "D3";//Fuel Injection
const char spark     = "D4";//Spark
const char runlight  = "D5";//Running Light
const char faillight = "D6";//Failure Light

//Set Input Pins here
const char cfh       = "D7";//Call for Heat
const char fs        = "D8";//Flame Sensor
const char rs        = "D9";//Reset Button

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
    
    delay(2000);
    
    digitalWrite(fuel, LOW);
    Serial.write("Fuel ON");
    
    delay(3000);
    
    digitalWrite(spark, LOW);
    Serial.write("Spark ON");
    
    delay(3000);
    
    digitalWrite(spark, HIGH);
    Serial.write("Spark OFF");
    
    isrunning = "on";
    delay(5000);
   }
   else
   {
    //Check the flame every cycle !
    if(digitalRead(fs) == HIGH)
    {
     Serial.write("FLAME BROKEN, EMERGENCY STOP !");
     
     digitalWrite(fuel, HIGH);
     Serial.write("Fuel OFF");
     
     delay(30000);
     
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
    delay(60000);
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
 delay(500);
}
