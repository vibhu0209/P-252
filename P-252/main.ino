// ESP32 will make post requests to server on local network
// ESP32 has to be on same network

//  including libraries
#include<WiFi.h>
#include<HTTPClient.h>

//  wifi credentials
const char ssid[] = "home sweet home";
const char password[] = "password1998";

//  API url
String api = "http://192.168.1.32:5000/add";

//  http client
HTTPClient http;

//  potpin
const int potpin = 34;

void setup()
{
  Serial.begin(115200);
  Serial.print("Connecting to : ");
  Serial.println(ssid);
  WiFi.begin(ssid , password);
  while (WiFi.status()  !=  WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println("Connected with Wifi !");
}

void loop()
{

  //  reading potentiometer
  int pot = analogRead(potpin);
  Serial.print("Pot Val : ");
  Serial.println(pot);

  //  check if wifi is still connected
  if (WiFi.status()  ==  WL_CONNECTED)
  {
        
    //  connect with server on that particular API
    http.begin(api);

    //  type of data to be shared : JSON
    http.addHeader("Content-Type" , "application/json");

    //  data to be sent in JSON format
    String info = "{\"potentiometer\" : " + String(pot) + "}";

    //  hit the POST request
    int http_code = http.POST(info);

    //  check for response
    //  if response code > 0, valid response
    if (http_code  >  0)
    {
      //  get the message from server
      String response = http.getString();
      Serial.print("Response code : ");
      Serial.print(http_code);
      Serial.print('\t');
      Serial.print("Message from Server : ");
      Serial.println(response);
    }

    //  if response code < 0, some error occured
    else
    {
      Serial.print("Error code : ");
      Serial.println(http_code);
    }

    //  end the connection with server to free up the resources
    http.end();
  }

  //  if wifi not connected
  else
  {
    Serial.print("Not connected with : ");
    Serial.println(ssid);
  }


  //  wait for 1 seconds before hittng a POST request again
  delay(1000);

}
