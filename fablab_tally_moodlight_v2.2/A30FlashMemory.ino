char separator = '_';
int nextIndex = 0;

void writeToFlashMemory() {
  delay(10);
  
  Serial.print("writeToFlash: ");
  printFlashMemoryData();
  
  nextIndex = 0;
  EEPROM.write(nextIndex, separator);
  nextIndex ++;
  
  writeAtNextIndex(ssid);
  writeAtNextIndex(password); 
  writeAtNextIndex(wifi_ssid); 
  writeAtNextIndex(wifi_password); 
  writeAtNextIndex(mdnsName); 
  
  
 
  //result: "-<ssid>-<password>-<wifi_ssid>-<wifi_password>-<mdnsName>"
  EEPROM.commit();
}
void writeAtNextIndex(String s){
  for (int i = 0; i < s.length(); i++) {
    EEPROM.write(nextIndex+i, s[i]);
  }
  nextIndex += s.length();
  EEPROM.write(nextIndex, separator);
  nextIndex ++;
}

void readFromFlashMemory(){
  Serial.print("readFromFlash: ");

  if(char(EEPROM.read(0)) != separator){ //check first char
    Serial.println("nothing stored yet");
    return;
  }

  nextIndex = 1; //skip first char '-'
  

  ssid = readAddNextIndex();
  password = readAddNextIndex();
  wifi_ssid = readAddNextIndex();
  wifi_password = readAddNextIndex();
  mdnsName = readAddNextIndex();


  printFlashMemoryData();
}


String readAddNextIndex(){
  String output;
  char readChar;
  int i = 0; 
  while (readChar != separator) {
    readChar = char(EEPROM.read(nextIndex+i));
    delay(10);
    i++;

    if (readChar != separator) {
      output += readChar;
    }
  }
  nextIndex += i;
  return output;
}

void printFlashMemoryData(){
  Serial.print(ssid);
  Serial.print("; ");
  Serial.print(password);
  Serial.print("; ");
  Serial.print(wifi_ssid);
  Serial.print("; ");
  Serial.print(wifi_password);
  Serial.print("; ");
  Serial.println(mdnsName);
}
