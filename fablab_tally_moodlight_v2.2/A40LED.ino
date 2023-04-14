void leds(int r, int g, int b){
  led1(r, g, b);
  led2(r, g, b);
}

void led1(int r, int g, int b){
  analogWrite(LED_RED,   r);                         
  analogWrite(LED_GREEN, g);
  analogWrite(LED_BLUE,  b);
}

void led2(int r, int g, int b){
  analogWrite(LED2_RED,   r);                        
  analogWrite(LED2_GREEN, g);
  analogWrite(LED2_BLUE,  b);
}

void demoLED(){
  leds(0, 0, 0);
  delay(1000);
  led1(512, 0, 0);
  led2(0, 0, 0);
  delay(1000);
  led1(0, 0, 0);
  led2(512, 0, 0);
  delay(1000);
  leds(0, 512, 0);
  delay(1000);
  leds(0, 0, 0);
}
