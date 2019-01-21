
/////////////////////////////////////////////////////////////////////////////////////////////////
// This is arduino control system for interactive audio box by John Cheongun Lee 15.Nov.2018
// It controls RFID reader, Wav Trigger and Volume reader
//
//
//
//
/////////////////////////////////////////////////////////////////////////////////////////////////

#include <AltSoftSerial.h>    // Arduino build environment requires this
#include <wavTrigger.h>
#include <SPI.h>
#include <MFRC522.h>

#define TOTAL_SONG_COUNT 5
#define LED 13                // our LED
#define VOLUME A0
#define VOLUME_POWER A1
#define RST_PIN         7          // Configurable, see typical pin layout above
#define SS_PIN          10         // Configurable, see typical pin layout above
#define SLOW_START      1500

wavTrigger player;             // Our WAV Trigger object

byte gLedState = 0;           // LED State
int  gSeqState = 0;           // Main program sequencer state
int  gRateOffset = 0;         // WAV Trigger sample-rate offset
int  gNumTracks;              // Number of tracks on SD card
int  curVolume;
int  curTrackNo;
int  prevVolume;
uint8_t control = 0x00;
boolean isPlaying;

char gplayerVersion[VERSION_STRING_LEN];    // WAV Trigger version string

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

String songID[TOTAL_SONG_COUNT] = {"42385717025474128","42335717025474128","42285717025474128","42175717025474128","42125717025474128"};
//String songID[TOTAL_SONG_COUNT] = {"42385717025474128", "42335717025474128", "42285717025474128", "42235717025474128", "42125717025474128"};

void setup()
{
  Serial.begin(9600);

  pinMode(LED, OUTPUT);

  digitalWrite(LED, gLedState);

  initDefaultData();

  initWavTrigger();

  initRC522();
}

void initDefaultData()
{
  isPlaying = true;

  curVolume = -40;
  curTrackNo = 1;

  prevVolume = curVolume;

  analogWrite(VOLUME_POWER, 255);
}

void initRC522()
{
  while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)

  SPI.begin();      // Init SPI bus

  mfrc522.PCD_Init();   // Init MFRC522
  mfrc522.PCD_SetAntennaGain(mfrc522.RxGain_avg);
  //mfrc522.PCD_DumpVersionToSerial();  // Show details of PCD - MFRC522 Card Reader details

  //Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
}

void initWavTrigger()
{
  // WAV Trigger startup at 57600
  player.start();

  player.setAmpPwr(true);

  // Send a stop-all command and reset the sample-rate offset, in case we have
  //  reset while the WAV Trigger was already playing.
  player.stopAllTracks();
  player.samplerateOffset(0);

  // Enable track reporting from the WAV Trigger
  player.setReporting(true);

  // Allow time for the WAV Trigger to respond with the version string and
  //  number of tracks.
  delay(1000);

  // If bi-directional communication is wired up, then we should by now be able
  //  to fetch the version string and number of tracks on the SD card.
  if (player.getVersion(gplayerVersion, VERSION_STRING_LEN) == true)
  {
    //Serial.print(gplayerVersion);
    //Serial.print("\n");
    gNumTracks = player.getNumTracks();
    //Serial.print("Number of tracks = ");
    //Serial.print(gNumTracks);
    //Serial.print("\n");

    playTrack(1, SLOW_START);

    delay(1000);

    player.stopAllTracks();
  }
  else
  {
    //Serial.println("WAV Trigger response not available");
  }

  player.samplerateOffset(0);            // Reset our sample rate offset
  player.masterGain(0);                  // Reset the master gain to 0dB
}

void playTrack(int trackNo, int slowStart)
{
  isPlaying = true;

  curTrackNo = trackNo;

  delay(slowStart);

  player.stopAllTracks();

  delay(30);

  player.trackGain(trackNo, curVolume);              // Preset Track with gain to -40dB

  delay(30);

  player.trackPlayPoly(trackNo);               // Start Track

  Serial.print("Song playing... ");
  Serial.print(trackNo);
  Serial.print(" volume is ");
  Serial.println(curVolume);
  
}

void stopTrack()
{
  if (isPlaying == true)
  {
    //Serial.println("Stopping current track");

    player.trackFade(curTrackNo, -70, 700, true);
  }

  delay(800);

  //Serial.println("Stopping current track");

  player.stopAllTracks();
}

void readVolume()
{
  curVolume = analogRead(VOLUME);

  curVolume = map(curVolume, 50, 1000, -50, 5);

  if (curVolume <= -50)
  {
    curVolume = -70;
  }

  curVolume = constrain(curVolume, -70, 5);

  if (curVolume != prevVolume && isPlaying == true)
  {
    player.trackGain(curTrackNo, curVolume);

    //Serial.print("volume = ");
    //Serial.println(curVolume);
  }

  prevVolume = curVolume;
}

void checkCardRemoval()
{
  bool newCard;
  uint8_t control = 0x00;

  newCard = false;

  while (true)
  {
    control = 0;

    for (int i = 0; i < 3; i++) 
    {
      if (!mfrc522.PICC_IsNewCardPresent()) 
      {
        if (mfrc522.PICC_ReadCardSerial()) 
        {
          //Serial.print("a ");
          control |= 0x16;
        }
       
        if (mfrc522.PICC_ReadCardSerial()) {
          //Serial.print("b ");
          control |= 0x16;
        }
        
        //Serial.print('c');
        control += 0x1;
      }
      //Serial.print('d');
      control += 0x4;
    }

    readVolume();

    //Serial.println(control);

    if (control == 13 || control == 14)
    {
      delay(50);

      control = 0;
    } else
    {
      break;
    }

    /*

      if (control != 13 && control != 14)
      {
      break;
      }

    */
  }

  //Serial.println("CardRemoved");

  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
}

void checkCardRemoval2()
{
  uint8_t control = 0x00;

  while (true)
  {
    control = 0;

    for (int i = 0; i < 3; i++)
    {
      if (!mfrc522.PICC_IsNewCardPresent())
      {
        //Serial.println("Traying to read ...");
        //Serial.println(mfrc522.PICC_ReadCardSerial());

        if (mfrc522.PICC_ReadCardSerial() == false)
        {
          //Serial.println("data read");

          control++;
        }
      }

      readVolume();

      delay(20);
    }

    //Serial.println(control);

    if (control > 2)
    {
      //Serial.println(control);
      
      break;
    }
  }

  Serial.println("CardRemoved");

  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
}

void checkCard()
{
  String tempUID;

  if ( !mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }

  if ( !mfrc522.PICC_ReadCardSerial())
  {
    //Serial.println("Can't read card serial!");
    
    return;
  }

  for (int i = 0; i < mfrc522.uid.size; i++)
  {
    tempUID += String(mfrc522.uid.uidByte[i]);
  }

  Serial.print("NewCard ");
  Serial.println(tempUID);

  for (int i = 0; i < TOTAL_SONG_COUNT; i++)
  {
    //Serial.println(songID[i]);

    if (tempUID.equals(songID[i]) == true)
    {      
      playTrack(i + 1, SLOW_START);
      
      break;
    }
  }

  checkCardRemoval2();

  stopTrack();
}

//void loop() {
//  // Look for new cards
//  if ( ! mfrc522.PICC_IsNewCardPresent()) {
//    return;
//  }
//
//  // Select one of the cards
//  if ( ! mfrc522.PICC_ReadCardSerial()) {
//    return;
//  }
//
//  // Dump debug info about the card; PICC_HaltA() is automatically called
//  //mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
//
//  checkCardRemoval();
//}

void loop()
{
  checkCard();

  readVolume();

  delay(20);
}
