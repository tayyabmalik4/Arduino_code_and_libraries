#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

 
#define SS_PIN 10
#define RST_PIN 9

#define SERVO_PIN 3
Servo myservo;

#define ACCESS_DELAY 2000
#define DENIED_DELAY 1000
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
 
void setup() 
{
  Serial.begin(115200);   // Initiate a serial communication
  SPI.begin();          // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  myservo.attach(SERVO_PIN);
  myservo.write(90);
  delay(100);
  myservo.write( 0 );
  Serial.println("Put your card to the reader...");
  Serial.println();
  pinMode(8,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(6,OUTPUT);

}
void loop() 
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
// || content.substring(1) == "55 4B 61 24" 
// || content.substring(1) == "57 8E C8 CB"
// || content.substring(1) == "C7 2C BB CA"
// || content.substring(1) == "6A 0C F5 A2"
// || content.substring(1) == "57 60 C7 CB"
// || content.substring(1) == "3A B8 78 19"
// || content.substring(1) == "55 40 82 24"
// || content.substring(1) == "A7 10 C9 CB"
  if (content.substring(1) == "3A B8 78 19" || content.substring(1) == "A7 10 C9 CB"|| content.substring(1) == "57 60 C7 CB" || content.substring(1) == "6A 0C F5 A2" || content.substring(1) == "C7 2C BB CA"|| content.substring(1) == "57 8E C8 CB" || content.substring(1) == "50 49 8D 1F" ||content.substring(1) == "6A 47 C4 A2" ||content.substring(1) == "55 31 6D 2A" ||content.substring(1) == "50 28 1C 1F" ) //change here the UID of the card
  {
    Serial.println("Authorized access");
    Serial.println();
   myservo.write( 90 );
   digitalWrite(8,HIGH);
   digitalWrite(7,HIGH);
   delay(100);
   digitalWrite(8,LOW);
   digitalWrite(7,LOW);
   delay(100);
   digitalWrite(8,HIGH);
   digitalWrite(7,HIGH);
   delay(100);
   digitalWrite(8,LOW);
   delay(15000);
   digitalWrite(7,LOW);
   myservo.write( 0 );
  
  

  }
 
 else   {
    Serial.println(" Access denied");
    digitalWrite(8,HIGH);
    digitalWrite(6,HIGH);
    delay(1000);
    digitalWrite(8,LOW);
    digitalWrite(6,LOW);
 

    delay(DENIED_DELAY);

 
  }
}
