#include <ESP8266WiFi.h>
#include <Servo.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
//#include <ESPAsyncWebServer.h>
const char* ssid = "park";
const char* password = "123456789";
/////////////////////////////////////////////////////////////////////////////////
#define  test  D7                            //    Led Test 
/////////////////////////////////////////////////////////////////////////// 

///////////////////////////////////////////////////////////////////////////
#define  sens1  D1
#define  ledGreenpark1  D2            //park 1
#define  ledRedpark1   D3
///////////////////////////////////////////////////
#define  sens2  D4
#define  ledGreenpark2  D5            //park 2
#define  ledRedpark2   D6
///////////////////////////////////////////////////
//#define  sens3  D7
//#define  ledGreenpark3  D8           //park 3
//#define  ledRedpark3   D9
////////////////////////////////////////////////////////////////////////////////            
////////////////////////////////////////////////////////////////////////////////

ESP8266WebServer server(80);
StaticJsonDocument<256> doc;



//AsyncWebServer server(80);
 ////////////////////////////////////////////////////////////////////////////////////////////////  Start SETUP
 void setup() {                                        
          
Serial.begin(115200);

////////////////////////////////////////////////////////////////////////////////
  pinMode(sens1, INPUT);
  pinMode(ledGreenpark1, OUTPUT);
  digitalWrite(ledGreenpark1,LOW);
  pinMode(ledRedpark1, OUTPUT);
  digitalWrite(ledRedpark1,LOW);
////////////////////////////////////////////////////////////////////////////////
  pinMode(sens2, INPUT);
  pinMode(ledGreenpark2, OUTPUT);
 digitalWrite(ledGreenpark2,LOW);
  pinMode(ledRedpark2, OUTPUT);
  digitalWrite(ledRedpark2,LOW);
////////////////////////////////////////////////////////////////////////////////
//  pinMode(sens3, INPUT);
//  pinMode(ledGreenpark3, OUTPUT);
//   digitalWrite(ledGreenpark3,LOW);
// pinMode(ledRedpark3, OUTPUT);
// digitalWrite(ledRedpark3,LOW);
//////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
pinMode(test,OUTPUT);   
digitalWrite(test,LOW);
/////////////////////////////////////////////////////////////////////
 WiFi.disconnect();
 
WiFi.softAP(ssid, password);
WiFi.setOutputPower(20.5);
  //WiFi.mode(WIFI_STA);

 // WiFi.begin(ssid, password);


         // Wait for connection

           server.begin();
IPAddress myIp=WiFi.softAPIP();
 Serial.println("Ap ip address");
  Serial.println(myIp);
 Serial.println("HTTP server started");


 
//  while (WiFi.status() != WL_CONNECTED) {
//    delay(500);
//    Serial.print(".");
//  }
//  Serial.print("Connected to ");
//  Serial.println(ssid);
//  Serial.print("IP address: ");
//  Serial.println(WiFi.localIP());
//////////////////////////////////////////////////////////////////////
  server.on("/",handleRoot);
  
 
   server.on("/P1",handleP1);  
   server.on("/P2",handleP2);  
   server.on("/open",HTTP_GET,handleRequest);  
  server.begin();
}
/////////////////////////////////////////////////////////////////////////////////////End  SetUp

/////////////////////////////////////////////////////////////////////////////////// Start  LOOP
void loop() {
server.handleClient();
sensor1() ;
sensor2() ;
}
//////////////////////////////////////////////////////////////////////////////////End  LOOP


///////////////////////////////////////////////////////////////////////////////////// Start Sensor 1
void sensor1()               
   {
  if (digitalRead(sens1) == HIGH)
      {
         if(digitalRead(ledGreenpark1)==LOW && digitalRead(ledRedpark1)==LOW )
         {

               ErrorSpace();
               NotAllowedToEnter();   ////////
                                   
                                   //  sent msg to Phone
               delay (1000);
               return ;
         } 
         else if(digitalRead(ledGreenpark1)==HIGH && digitalRead(ledRedpark1)==LOW )
         {
                 
               SuccessflyEnter1();                  
               digitalWrite(ledGreenpark1,LOW);                    
               digitalWrite(ledRedpark1,HIGH);                      
               delay (1000);
               return ;
         }
          else if(digitalRead(ledGreenpark1)==LOW && digitalRead(ledRedpark1)==HIGH )
         {
              
               ExitFromPark1(); 
               digitalWrite(ledRedpark1,LOW);                                        
               delay (1000);
               return ;
         }
         else
         {
        Serial.print("sensor1  work good ");
        delay (1000);
         }
  }
}
//////////////////////////////////////////////////////////////////////////////////// End Sensor 1


//////////////////////////////////////////////////////////////////////////////////// Start Sensor 2
void sensor2()                    
   {
  if (digitalRead(sens2) == HIGH)
      {
         if(digitalRead(ledGreenpark2)==LOW && digitalRead(ledRedpark2)==LOW )
         {
               NotAllowedToEnter();
               ErrorSpace();
                                   //  sent msg to Phone
               delay (1000);
               return ;
         } 
         else if(digitalRead(ledGreenpark2)==HIGH && digitalRead(ledRedpark2)==LOW )
         {
                 
               SuccessflyEnter2();                    //  sent msg to Phone
               digitalWrite(ledGreenpark2,LOW);                    
               digitalWrite(ledRedpark2,HIGH);                      
               delay (1000);
               return ;
         }
          else if(digitalRead(ledGreenpark2)==LOW && digitalRead(ledRedpark2)==HIGH )
         {
               ExitFromPark2();
               Serial.print("الحساس تحسس من اجل خروج سيارة اخرى من مصفها ");  
               digitalWrite(ledRedpark2,LOW);                                        
               delay (1000);
               return ;
         }
         else
         {
        Serial.print("sensor2  work good ");
        delay (1000);
         }
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////End Sensor 2

///////////////////////////////////////////////////////////////////////////// /////// function to control the arduino by Json
    void OpenServoJson1()
    {
        StaticJsonDocument <200> control;
       control["SOS1"]="SOS1";
       serializeJsonPretty(control,Serial);
     }
 //////////////////////////////////////////////////////////    
    void OpenServoJson2()
    {
        StaticJsonDocument <200> control;
       control["SOS2"]="SOS2";
       serializeJsonPretty(control,Serial);
     }
 //////////////////////////////////////////////////////////    
    void ErrorSpace()
    {
        StaticJsonDocument <200> control;
        control["BZAR"]="BZAR";
        serializeJsonPretty(control,Serial);
     }
///////////////////////////////////////////////////////////////////////////////////////////
  void NotAllowedToEnter()
  {   
       StaticJsonDocument <200> control;
        control["NotAllowedToEnter"]="NotAllowedToEnter";
        serializeJsonPretty(control,Serial) ;  
    }
   
///////////////////////////////////////////////////////////////////////////////////////////////////////////
    void  SuccessflyEnter1(){
  
  
       StaticJsonDocument <200> control;
        control["SuccessflyEnter1"]="SuccessflyEnter1";
        serializeJsonPretty(control,Serial) ;  
  
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////
     void SuccessflyEnter2(){
  
  
       StaticJsonDocument <200> control;
        control["SuccessflyEnter2"]="SuccessflyEnter2";
        serializeJsonPretty(control,Serial);   
  
  }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 void ExitFromPark1(){
  
     StaticJsonDocument <200> control;
        control["ExitFromPark1"]="ExitFromPark1";
        serializeJsonPretty(control,Serial) ;
 
  }
////////////////////////////////////////////////////////////////////////////////////////////////////////////
 void ExitFromPark2(){ 
     StaticJsonDocument <200> control;
        control["ExitFromPark2"]="ExitFromPark2";
        serializeJsonPretty(control,Serial) ;
  }


///////////////////////////////////////////////////////////////////////////////////////////////////////////
  void handleRoot() {

                    server.send(200, "text/plain","READY");

                      }    

                      
  
                     
////////////////////////////////////////////////////////////////////////////////////
             void handleP1() {
                   if( digitalRead(ledGreenpark2) == HIGH)
                   {
           
                     doc["status"] =404;
                     doc["message"] ="من فضلك انتظر قليلا الكراج مشغول"; 
                     String response;
                    serializeJson(doc, response);
                     
                     server.send(200, "application/json",response);
                     server.send(200, "text/plain",response);
                    }
                   else{
                        if(digitalRead(ledRedpark1) == HIGH)
                        {                          
                     doc["status"] =404;
                     doc["message"] ="لاداعي لطلب فتح الباب ,سيفتح عند خروجك تلقائيا";      
                     String response;
                    serializeJson(doc, response);                     
                     server.send(200, "application/json",response);
                     server.send(200, "text/plain",response);                          
                          }
                       else{
                      if(digitalRead(ledGreenpark1) == HIGH)
                        {
                         doc["status"] =404;
                         
                     doc["message"] ="انت فعلا داخل الكراج"; // "Hello from ESP8266!";
                     String response;
                    serializeJson(doc, response);
                     
                       server.send(200, "application/json",response);
                     server.send(200, "text/plain",response); 
                                                   
                          }
                        else{
                       digitalWrite(ledGreenpark1,HIGH);                       
                     doc["status"] =200;
                     doc["message"] ="تم فتح الباب بنجاح"; // "Hello from ESP8266!";
                     String response;
                    serializeJson(doc, response);
                     
                       server.send(200, "application/json",response);
                     server.send(200, "text/plain",response);
                          OpenServoJson1();
                    
                      //  Serial.print("open servo for inter  car to Park 1 ");
                      //Serial.print(200);
                    }}
                   }
                      }
///////////////////////////////////////////////                      
  void handleP2() {
                  if( digitalRead(ledGreenpark1) == HIGH) 
                  {
                  
                     doc["status"] =404;
                     doc["message"] ="من فضلك انتظر قليلا الكراج مشغول"; // "Hello from ESP8266!";
                     String response;
                    serializeJson(doc, response);
                     
                     server.send(200, "application/json",response);
                     server.send(200, "text/plain",response);
                                                 
                    }
                    else
                 {
                      if(digitalRead(ledRedpark2) == HIGH)
                    {                          
                     doc["status"] =404;
                     doc["message"] ="لاداعي لطلب فتح الباب ,سيفتح عند خروجك تلقائيا";       // "Hello from ESP8266!";
                     String response;
                    serializeJson(doc, response);                     
                     server.send(200, "application/json",response);
                     server.send(200, "text/plain",response);                          
                   }
                     else{
                     if(digitalRead(ledGreenpark2) == HIGH)
                        {
                         doc["status"] =404;
                         
                     doc["message"] ="انت فعلا داخل الكراج"; // "Hello from ESP8266!";
                     String response;
                    serializeJson(doc, response);
                     
                       server.send(200, "application/json",response);
                     server.send(200, "text/plain",response); 
                                                   
                          }
                      else {
                      
                      digitalWrite(ledGreenpark2,HIGH);
                      doc["status"] =200;
                     doc["message"] ="تم فتح الباب بنجاح"; // "Hello from ESP8266!";
                     String response;
                    serializeJson(doc, response);
                     
                       server.send(200, "application/json",response);
                     server.send(200, "text/plain",response);
                          OpenServoJson2();
                  //  Serial.print("open servo for inter  car to Park 2 ");}
                    
                      //Serial.print(200);
                 }}
                 }
                 }
                 

//   void handleP3() {
//                    digitalWrite(ledGreenpark3,HIGH);
//                    OpenServoJson();
//                    server.send(200, "text/plain","Park 3 for you");
//                    Serial.print("open servo for inter  car to Park 3 ");
//                      //Serial.print(200);
//                 }


void handleRequest() {

          digitalWrite(test,!digitalRead(test));
           
            if (server.hasArg("NumPark")) {
     // StaticJsonDocument<256> doc;
       String numberParkString = server.arg("NumPark");
        int  numberPark=numberParkString.toInt();
         switch(numberPark)
          {
            case 1: handleP1(); break;
            case 2: handleP2(); break;
            //case 3: handleP3(); break;
            default:
            doc["status"] =404;
            doc["message"] = "عذرا مصفك في الكراج المجاور"; // "Hello from ESP8266!";
            String response;
            serializeJson(doc, response);
            server.send(200, "application/json", response);
          }  
//    doc["status"] = 404;
//    doc["message"] ="رسالة خاطئة"; // "Hello from ESP8266!";
//      String response;
//      serializeJson(doc, response);
//       server.send(200, "application/json", response);
//   // Serial.println(message);
//     server.send(200, "text/plain", response);
       }
                   
  server.send(200, "text/plain", "OK");
 
}
