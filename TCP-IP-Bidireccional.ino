
#define DEBUG true
const int SensorESP8266 = A0;  //Declaración de pin esclusivo de un sensor analógico (LM35)
float valordelsensor = 0;
String W = " ";
char w ;
String valor3;
String datasend;

void setup()
{
  Serial.begin(115200);
  Serial3.begin(115200);
  pinMode(40, OUTPUT);
  pinMode(41, OUTPUT);
  pinMode(42, OUTPUT);
}

void loop()
{
  LecturadeSensor();

  ESP8266();


}

void ESP8266 () {
  if (Serial3.available())        // Lo que entra por WIFI - Serial
  {
    w = Serial3.read() ;
    Serial.print(w);      // Vamos montando un String con lo que entra
    W = W + w ;
  }
  if (Serial.available())    // Lo que entra por Serial - WIFI
  { char s = Serial.read();
    Serial3.print(s);
  }
  if ( w == '\n')                     // Sin han pulsado intro
  {

    if ( W.indexOf("P40a") > 0)  // Si P13 esta incluido en el string
    { digitalWrite(40, !digitalRead(40)) ;
      Serial.println("Invirtiendo pin 40");
    }

    if (W.indexOf("P41b") > 0) {
      digitalWrite(41, !digitalRead(41));
      Serial.println("Invirtiendo pin 41");
    }


    if (W.indexOf("P42c") > 0) {
      digitalWrite(42, !digitalRead(42));
      Serial.println("Invirtiendo pin 42");
    }


    if (W.indexOf("hol") > 0) {
      String cipsend = "AT+CIPSEND=0,";
      cipsend += datasend.length();
      cipsend += "\r\n";

      sendData(cipsend, 1000, DEBUG);
      sendData(datasend, 1000, DEBUG);
    }
    W = "" ;  w = ' ' ;
  }

}


void LecturadeSensor() {
  valordelsensor = analogRead(SensorESP8266);
  valordelsensor = (valordelsensor * 4.95 * 100.00) / 1024.00;
  char outsrtg3[15];
  dtostrf(valordelsensor, 4, 2, outsrtg3);
  valor3 = outsrtg3;
  datasend = ("TEMPERATURA ACTUAL: " + valor3 + "ºC");

}


String sendData(String command, const int timeout, boolean debug)
{
  String response = "";

  Serial3.print(command);

  long int time = millis();


  while ( (time + timeout) > millis())
  {
    while (Serial3.available())
    {

      char c = Serial3.read();
      response += c;
    }
  }

  if (debug)
  {
    Serial.print(response);
  }

  return response;
}


