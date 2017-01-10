#include <MFRC522.h>

#include <SoftwareSerial.h>
SoftwareSerial bt(1,0);
//RFID pins 
int mipin=11; // ICSP-4 MOSI:
int mopin =12; // ICSP-1 MISO: 
int iscppin= 13; // ISCP-3 SCK :
int sspin= 10; //(Configurable) SS :
int resetpin= 9; //(Configurable) RST :

//Bluetooth pins
int txpin=1; //rx pin of bluetooth
int rxpin=0; // tx pin of bluetooth
String rfidcode[20];
MFRC522 mfrc522(sspin, resetpin);  // Create MFRC522 instance

byte nuidPICC[4];    // storing uid code 

//simple database for checking the item and it's price
struct database
{
 byte uid[4];
 char itemname[20];
 int price; 
}variable[10];


void senddata(byte i)
{
  bt.print(variable[i].itemname);
  bt.print(variable[i].price);
}

void setup() {
  Serial.begin(9600);   // Initialize serial communications with the PC
  SPI.begin();      // Init SPI bus
  mfrc522.PCD_Init();   // Init MFRC522
  for(int k=0;k<10;k++)
  assign_value(k);
  
}

void assign_value(int k)                     // values for each item is to stored as per item name and price
{
  for( byte i=0; i < 4 ; i++)
  variable[k].uid[i]="ab";
    strcpy(variable[k].itemname,"First item");
}
void loop()
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  // Dump debug info about the card; PICC_HaltA() is automatically called
mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
 for (byte i = 0; i < 4; i++) {
      nuidPICC[i] = mfrc522.uid.uidByte[i];
    }
}

void itemcheck()
{
  for(byte i=0; i<10; i++)
  
    for(byte j=0; j<4; j++)
    
     if(variable[i].uid[j]==nuidPICC[j])
       if(j==3)
        senddata(i);
}

