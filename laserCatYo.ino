#include <SPI.h>
#include <WiFi101.h>

#include <Servo.h>

char ssid[] = "yourssid";
char pass[] = "yourpass";


int keyIndex = 0;

int laserPin = 6;

Servo myservo1;
Servo myservo2;

int pos1 = 0;
int pos2 = 0;
int temps = 600;

int servo1move = 0;

int status = WL_IDLE_STATUS;
char server[] = "yourdomain.com";
WiFiClient client;
WiFiClient client0;
WiFiClient client1;


void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(laserPin, OUTPUT);

  myservo1.attach(2);
  myservo2.attach(3);

  Serial.begin(57600);
   
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    while (true);
  }

  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
    delay(10000);
  }
  
  Serial.println("Connected to wifi");
  printWifiStatus();

}


void loop() {
  Serial.println("\nStarting connection to server...");
  
  if (client.connect(server, 80)) {
    Serial.println("connected to server");
    
    client.println("GET switchState.txt HTTP/1.0");
    client.println("Host: yourdomain.com");
    client.println("Connection: close");
    client.println();
    
    delay(300);
    char c;
    
    while (client.available()) {
      c = client.read();
      Serial.write(c);
     }

    if (atoi(&c)) {
      digitalWrite(LED_BUILTIN, HIGH);
      digitalWrite(laserPin, HIGH);
    }else{
      digitalWrite(LED_BUILTIN, LOW);
      digitalWrite(laserPin, LOW);
    }
  }

  if (client0.connect(server, 80)) {
    Serial.println("connected to server");
    
    client0.println("GET xpos.txt HTTP/1.0");
    client0.println("Host: yourdomain.com");
    client0.println("Connection: close");
    client0.println();
    delay(300);
    char d;
    
    while (client0.available()) {
      d = client0.read();
      Serial.write(d);
     }

    if (atoi(&d)) {
      Serial.println("X move");
      pos1 = random(0,180);
      myservo1.write(pos1);
      delay(100);
    }else{
      Serial.println("X dontmove");
      d = 0;
    } 
  }

  if (client1.connect(server, 80)) {
    Serial.println("connected to server");
    
    // Make a HTTP request:
    client1.println("GET /cat/ypos.txt HTTP/1.0");
    client1.println("Host: yourdomain.com");
    client1.println("Connection: close");
    client1.println();
    delay(300);
    char e;
    
    while (client1.available()) {
      e = client1.read();
      Serial.write(e);
     }

    if (atoi(&e)) {
      Serial.println("Y move");
      pos2 = random(0,30);
      myservo2.write(pos2);
      Serial.println(pos2);
      delay(100);
    }else{
      Serial.println("Y dontmove");
      e = 0;
    } 
  }
  
  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting from server.");
    client.stop();
  }

}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

