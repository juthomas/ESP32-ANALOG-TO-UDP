#include <Arduino.h>
#include <WiFiUdp.h>
#include "WiFi.h"

// WIFI SETUP
// char ssid[] = "TP-Link_F047"; // nom du routeur
// char ssid[] = "SFR_B4C8"; // nom du routeur
char ssid[] = "TP-Link_F387"; // nom du routeur

// char pass[] = "69407901";     // pas de mot de passe
// char pass[] = "enorksenez3vesterish"; // pas de mot de passe
char pass[] = "32678697"; // pas de mot de passe

//  WiFi.config(local_IP, gateway, subnet);
IPAddress ip(192, 168, 0, 215);    // Local IP (static)
IPAddress gateway(192, 168, 0, 1); // Router IP

IPAddress subnet(255, 255, 255, 0);

char computer_ip[] = "192.168.0.100"; // Adresse de l'ordinateur sur lequel envoyer les valeurs en UDP
uint16_t computer_port = 4242;        // Port de l'ordinateur sur lequel envoyer les valeurs en UDP
char nom_module[] = "A";              // Premiere partie du parametre envoyé par exemple "A33 4096"

WiFiUDP Udp;

const boolean DEBUG = true; // baud rate : 115200

const uint8_t inputs_to_send[] = {33, 32, 35, 34, 39, 36}; // Pins de l'esp32 sur lesquels lire

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);

  // Initialisation des Pins
  for (uint8_t i = 0; i < sizeof(inputs_to_send); i++)
  {
    pinMode(inputs_to_send[i], INPUT);
    digitalWrite(inputs_to_send[i], LOW);
  }

  WiFi.mode(WIFI_STA);

  // Static ip attributon
  WiFi.config(ip, gateway, subnet); // Static IP Address

  WiFi.begin(ssid, pass);
  if (DEBUG)
  {
    Serial.begin(115200);
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
  }
}

void loop()
{
  for (uint8_t i = 0; i < sizeof(inputs_to_send); i++)
  {
    uint16_t value = analogRead(inputs_to_send[i]);
    if (DEBUG)
    {
      Serial.printf("%s%d %d\n", nom_module, inputs_to_send[i], value);
    }

    Udp.beginPacket(computer_ip, computer_port);
    Udp.printf("%s%d %d\n", nom_module, inputs_to_send[i], value);
    Udp.endPacket();
  }
  delay(100);
}
