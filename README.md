# ESP32 ANALOG TO UDP
Ce projet concerne un programme Arduino destiné à être exécuté sur un module ESP32. Le programme permet de lire les valeurs analogiques de certaines broches de l'ESP32 et de les envoyer via le protocole UDP à un ordinateur distant.

## Configuration
Avant d'uploader le programme, vous devez configurer les paramètres suivants :

### Configuration Wi-Fi
Dans la section `WIFI SETUP`, vous devez spécifier les détails de votre réseau Wi-Fi :

```cpp
char ssid[] = "NomDuRouteur"; // Nom du réseau Wi-Fi
char pass[] = "MotDePasse";   // Mot de passe du réseau Wi-Fi
```
Vous pouvez décommenter l'une des lignes ssid et pass en fonction de votre réseau, ou les modifier pour correspondre à votre réseau personnel.

### Configuration de l'adresse IP
Si vous souhaitez utiliser une adresse IP statique pour l'ESP32, vous pouvez la configurer en modifiant les lignes suivantes :

```cpp
IPAddress ip(192, 168, 0, 215);    // Adresse IP locale (statique)
IPAddress gateway(192, 168, 0, 1); // Adresse IP du routeur
IPAddress subnet(255, 255, 255, 0); // Masque de sous-réseau
```
Assurez-vous de spécifier les bonnes adresses IP pour votre réseau.

### Configuration de l'ordinateur distant
Vous devez également spécifier l'adresse IP de l'ordinateur distant auquel vous souhaitez envoyer les valeurs en UDP :

```cpp
char computer_ip[] = "192.168.0.100"; // Adresse IP de l'ordinateur
uint16_t computer_port = 4242;        // Port de l'ordinateur
```

Assurez-vous de spécifier l'adresse IP correcte de votre ordinateur distant et le port sur lequel il écoutera les paquets UDP.

### Configuration des broches
Le programme lit les valeurs analogiques à partir des broches de l'ESP32 spécifiées dans le tableau `inputs_to_send`. Par défaut, les broches suivantes sont utilisées :

```cpp
const uint8_t inputs_to_send[] = {33, 32, 35, 34, 39, 36}; // Broches de l'ESP32 à lire
```
Si vous souhaitez lire d'autres broches, vous pouvez les ajouter à ce tableau en spécifiant les numéros de broche appropriés.

### Configuration du nom du module
Si vous souhaitez changer le nom du module dans les paquets UDP vous pouvez le faire à cette ligne :
```cpp
char nom_module[] = "A"; // Premiere partie du parametre envoyé par exemple "A33 4096"
```
## Utilisation
Une fois que vous avez configuré les paramètres nécessaires, vous pouvez téléverser le programme sur votre module ESP32 à l'aide de l'IDE Arduino ou d'un autre outil compatible.

Assurez-vous d'avoir correctement connecté les broches que vous souhaitez lire aux capteurs ou aux sources de signaux appropriés.

Le programme lit périodiquement les valeurs analogiques des broches spécifiées et les envoie à l'ordinateur distant via le protocole UDP. Les valeurs sont envoyées avec un format spécifique, par exemple "A33 4096", où "A" est la première partie du paramètre envoyé.

Si vous avez activé le mode de débogage (DEBUG = true), les valeurs lues seront également affichées sur le moniteur série avec une vitesse de bauds de 115200.