void saveEEPROM() {
  EEPROM.put(3 * currentMode + 40, modes[currentMode]);
  if (EEPROM.read(200) != currentMode) EEPROM.write(200, currentMode);
  EEPROM.commit();
}

void eepromTick() {
  if (settChanged && millis() - eepromTimer > 30000) {
    settChanged = false;
    eepromTimer = millis();
    saveEEPROM();
    EEPROM.commit();
  }
}

void saveAlarm(byte almNumber) {
  EEPROM.write(5 * almNumber, alarm[almNumber].state);   // рассвет
  eeWriteInt(5 * almNumber + 1, alarm[almNumber].time);
  EEPROM.commit();
}

void saveDawnMmode() {
  EEPROM.write(199, dawnMode);   // рассвет
  EEPROM.commit();
}

void eeprom_write_string(String string){
    int string_length =string.length();
    char temp_char[string_length + 1];
    string.toCharArray(temp_char, string_length + 1);
    EEPROM.write(addr, string_length);
    for (int i = 0 ; i < string_length ; i++){
      addr++;
      EEPROM.write(addr, temp_char[i]);
    }
    addr++;
    EEPROM.commit();
}
