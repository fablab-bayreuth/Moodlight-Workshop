void handleForm() {
  Serial.println("handleForm");
  
  
  if(server.arg("ssid") != ""){
    ssid = server.arg("ssid");
    Serial.print("ssid:");
    Serial.println(ssid);
  } 
  if(server.arg("password") != ""){
    password = server.arg("password");
    Serial.print("password:");
    Serial.println(password);
  } 

  if(server.arg("wifi_ssid") != ""){
    wifi_ssid = server.arg("wifi_ssid");
    Serial.print("wifi_ssid:");
    Serial.println(wifi_ssid);
  } 

  if(server.arg("wifi_password") != ""){
    wifi_password = server.arg("wifi_password");
    Serial.print("wifi_password:");
    Serial.println(wifi_password);
  } 

  if(server.arg("mdns_name") != ""){
    mdnsName = server.arg("mdns_name");
    Serial.print("mdnsName:");
    Serial.println(mdnsName);
  } 
  
  String s = ssid + ";" + password + ";" + wifi_ssid + ";" + wifi_password + ";" + mdnsName;
  server.send(200, "text/html", s);

  writeToFlashMemory(); //store config
  ESP.restart();
}

void handleGet(){
  String s = ssid + ";" + password + ";" + wifi_ssid + ";" + wifi_password + ";" + mdnsName;
  Serial.println(s);
  server.send(200, "text/html", s);
}
