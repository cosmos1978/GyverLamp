void request_weather(){
  int jsonListIndex;
  HTTPClient httpc;

  httpc.useHTTP10(true);
  httpc.begin("http://api.openweathermap.org/data/2.5/forecast?q=" + city + "," + countryCode + "&appid=" + openWeatherID + "&mode=json&units=metric");
  httpc.GET();

  jsonListIndex = forecast.toInt() / 3;

  StaticJsonDocument<800> filter;
    filter["list"][0]["weather"][0]["main"] = true;
    filter["list"][0]["main"]["temp"] = true;
    filter["list"][0]["main"]["humidity"] = true;
    filter["list"][0]["wind"]["speed"] = true;
    
    filter["list"][8]["weather"][0]["main"] = true;
    filter["list"][8]["main"]["temp"] = true;
    filter["list"][8]["main"]["humidity"] = true;
    filter["list"][8]["wind"]["speed"] = true;  

    filter["list"][16]["weather"][0]["main"] = true;
    filter["list"][16]["main"]["temp"] = true;
    filter["list"][16]["main"]["humidity"] = true;
    filter["list"][16]["wind"]["speed"] = true; 

    filter["list"][24]["weather"][0]["main"] = true;
    filter["list"][24]["main"]["temp"] = true;
    filter["list"][24]["main"]["humidity"] = true;
    filter["list"][24]["wind"]["speed"] = true; 

    filter["list"][32]["weather"][0]["main"] = true;
    filter["list"][32]["main"]["temp"] = true;
    filter["list"][32]["main"]["humidity"] = true;
    filter["list"][32]["wind"]["speed"] = true; 
  DynamicJsonDocument doc(7000);
  deserializeJson(doc, httpc.getStream(), DeserializationOption::Filter(filter));
  JsonObject obj = doc.as<JsonObject>();
  weatherStringTemp = obj["list"][jsonListIndex]["weather"][0]["main"];
  weatherString = String(weatherStringTemp);
  weatherTemp = obj["list"][jsonListIndex]["main"]["temp"];;
  weatherHumidity = obj["list"][jsonListIndex]["main"]["humidity"];
  weatherWind = obj["list"][jsonListIndex]["wind"]["speed"];

  if (String(weatherString) == "Clear"){
    weather = CLEAR;
  }
  else if (String(weatherString) == "Clouds"){
    weather = CLOUDS;
  }
  else if (String(weatherString) == "Rain" || String(weatherString) == "Drizzle"){
    weather = RAIN;
  }
  else if (String(weatherString) == "Thunderstorm"){
    weather = THUNDERSTORM;
  }
  else if (String(weatherString) == "Snow"){
    weather = SNOW;
  }

 // if (previousWeather != weather){
 //   EEPROM.write(WEATHER_ADDR_2, weather);
 //   EEPROM.commit();
  //}
  
  httpc.end();
}

void weatherRoutine(){ 
    if (weather == CLEAR || weather == CLOUDS){
      if (weather == CLEAR){
        modes[currentMode].speed = 117;
        weatherClearRoutine();
        fillString(String(int(round(weatherTemp)))+" C", CRGB::Blue, false);
      }
      else if (weather == CLOUDS){
        modes[currentMode].speed = 100;
        cloudNoise(); 
        fillString(String(int(round(weatherTemp)))+" C", CRGB::Orange, false);
      }
    }
    if (weather == RAIN || weather == THUNDERSTORM){
        weatherRainRoutine();
        fillString(String(int(round(weatherTemp)))+" C", CRGB::Orange, false);
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
      fillString(String(int(round(weatherTemp)))+" C", CRGB::Blue, false);
    }    
}
