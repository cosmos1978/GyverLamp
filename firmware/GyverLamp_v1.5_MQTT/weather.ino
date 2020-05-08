void request_weather(){
  int previousWeather = weather;
  int noOfBrackets;
  
  HTTPClient httpc;
  String url = "http://api.openweathermap.org/data/2.5/forecast?q=" + city + "," + countryCode + "&appid=" + openWeatherID + "&mode=json&units=metric&cnt=3";
  httpc.begin(url);
  int httpCode = httpc.GET();

  if (forecast == "0"){
    noOfBrackets = 1;
  }
  else if (forecast == "6"){
    noOfBrackets = 3;
  }
  else if (forecast == "12"){
    noOfBrackets = 5;
  }
  else if (forecast == "18"){
    noOfBrackets = 7;
  }
  else if (forecast == "24"){
    noOfBrackets = 9;
  }
  else if (forecast == "48"){
    noOfBrackets = 17;
  }
  else if (forecast == "72"){
    noOfBrackets = 25;
  }
  else if (forecast == "96"){
    noOfBrackets = 33;
  }
  // parse json (forecast, 24h later)
  //if (httpCode > 0) { //Check the returning code
      String payload = httpc.getString(); //Get the request response payload
   // }
  // parse json (forecast, 24h later)
  int pos = payload.indexOf('[');
  if (pos == -1){
    return;
  }
  for (int i=0; i<noOfBrackets; i++){
    pos = payload.indexOf('[', pos + 1 );
  }
  for (int i=0; i<5; i++){
    pos = payload.indexOf("\"", pos + 1 );
  }
   String weatherString =  payload.substring(pos+1, payload.indexOf("\"", pos+2));
  //Serial.println(weatherString);

  if (weatherString == "Clear"){
    weather = CLEAR;
  }
  else if (weatherString == "Clouds"){
    weather = CLOUDS;
  }
  else if (weatherString == "Rain" || weatherString == "Drizzle"){
    weather = RAIN;
  }
  else if (weatherString == "Thunderstorm"){
    weather = THUNDERSTORM;
  }
  else if (weatherString == "Snow"){
    weather = SNOW;
  }

  if (previousWeather != weather){
    EEPROM.write(WEATHER_ADDR, weather);
    EEPROM.commit();
  }
  
  httpc.end();
}

void weatherRoutine(){ 
    if (weather == CLEAR || weather == CLOUDS){
      if (weather == CLEAR){
        modes[currentMode].speed = 117;
        weatherClearRoutine();
      }
      else if (weather == CLOUDS){
        modes[currentMode].speed = 100;
        cloudNoise(); 
      }
    }
    if (weather == RAIN || weather == THUNDERSTORM){
        weatherRainRoutine();
      if (weather == THUNDERSTORM){
        int randomThunder = random8(100);
        if (randomThunder > 98){
          r = 200;
          g = 200;
          b = 200;
          colorRoutine();        }        
      }    
      FastLED.delay(1000 / 60);  
    }
    
    else if (weather == SNOW){
      snowRoutine();
    }    
}
