#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9          // Configurable, see typical pin layout above
#define SS_PIN          53         // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance


void setup() {
  Serial.begin(9600);		// Initialize serial communications with the PC
  while (!Serial);		// Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();			// Init SPI bus
  mfrc522.PCD_Init();		// Init MFRC522
  mfrc522.PCD_DumpVersionToSerial();	// Show details of PCD - MFRC522 Card Reader details
  Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
}

void loop() {
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  } 
  Serial.println("iniciado");
  byte pagina = 0x00;
  byte buffer[18];
  byte sizebuffer = sizeof(buffer);  
  MFRC522::StatusCode status;
  for(pagina; pagina != 16; pagina +=4){// la lectura regresa 16 bytes es decir 4 paginas de datos
  status = (MFRC522::StatusCode) mfrc522.MIFARE_Read(pagina, buffer, &sizebuffer);
if (status != MFRC522::STATUS_OK) {
        Serial.print(F("PCD_Authenticate() failed: "));
        Serial.println(mfrc522.GetStatusCodeName(status));
        return;
    }
    for ( int a = 0; a != 16; a++){
     Serial.print(buffer[a] );  
    }
  } 
  mfrc522.PICC_HaltA();
}


