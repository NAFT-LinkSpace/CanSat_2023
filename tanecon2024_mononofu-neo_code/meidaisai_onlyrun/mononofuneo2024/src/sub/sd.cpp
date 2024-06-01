#include "sd.hpp"

void sd::init(){
  
  if (!SD.begin(CS_SD))
  {
    Serial.println("Card Mount Failed");
    return;
  }
  uint8_t cardType = SD.cardType();

  if (cardType == CARD_NONE)
  {
    Serial.println("No SD card attached");
    return;
  }

  Serial.print("SD Card Type: ");
  if (cardType == CARD_MMC)
  {
    Serial.println("MMC");
  }
  else if (cardType == CARD_SD)
  {
    Serial.println("SDSC");
  }
  else if (cardType == CARD_SDHC)
  {
    Serial.println("SDHC");
  }
  else
  {
    Serial.println("UNKNOWN");
  }

  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  // Serial.printf("SD Card Size: %lluMB\n", cardSize);
////////////////
  do
        {
            sprintf(sd_filename, "/%4d.txt", n_logdata);
            if (SD.exists(sd_filename) == false)
                break;
            n_logdata++;
        } while (true);
  writeFile(SD, sd_filename, "Start! ");
}

void sd::writeFile(fs::FS &fs, const char *path, const char *message)
{
  Serial.printf("Writing file: %s\n", path);

  File file = fs.open(path, FILE_WRITE);
  file.print(message);
  file.close();
}

void sd::appendFile(fs::FS &fs, const char *path, String message)
{
  // Serial.printf("Appending to file: %s\n", path);

  File file = fs.open(path, FILE_APPEND);
  file.print(message);
  file.close();
}

void sd::makebuffer(io& Io){
  buffer+=String(Io.now_time);
  buffer+=",";
  buffer+=String(Io.status);
  buffer+=",";
  buffer+=String(Io.press_bme);
  buffer+=",";
  buffer+=String(Io.lat_ave,7);
  buffer+=",";
  buffer+=String(Io.lon_ave,7);
  buffer+=",";
  buffer+=String(Io.deltatheta);
  buffer+=",";
  buffer+=String(Io.distance,5);
  buffer+="\r\n";
}

void sd::logWrite(io& sensors){
    appendFile(SD,sd_filename,buffer);
    buffer="";
    // Serial.print("append");
}