#include <WiFi101.h>
#include <ArduinoMqttClient.h>

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);
String Payload = "{"; // Chaine de caractère qui contiendra le message envoyer de l'objet vers node-red
bool first = false;

String RPCData, PrevData;

const char topic[] = "home/HumTemp";
const char topicTemp[] = "home/temperature";
// Affiche la payload qui est envoyé ainsi que sa longeur

/*
  Fonctionnalité qui permet de créer la chaine de données a envoyé au broker MQTT
  Pour le moment, cette chaine ne doit pas dépassé un maximum de 100 caractère
*/
// {"ts":1666778909000,"values":{
void appendTimestamps(float value)
{
  first = false;
  Payload = "{\"ts\":";
  Payload += value;
  Payload += ",\"values\":{";
}

//"Temperature":23.169,"Humidite":59.411}}
/**

@brief Ajoute une paire clé-valeur à la charge utile (payload) en format JSON.
@param Name Le nom de la clé.
@param Val La valeur associée à la clé.
*/
void appendPayload(String Name, float Val)
{
  // Si c'est la première clé-valeur à ajouter, on ajoute seulement une virgule
  // pour séparer de la clé précédente.
  if (first)
  {
    Payload += ",";
  }
  // Ajoute la clé avec des guillemets et sa valeur.
  Payload += "\"";
  Payload += Name;
  Payload += "\":";
  Payload += Val;

  // Met à jour le flag pour indiquer qu'on a ajouté au moins une clé-valeur.
  first = true;
}

/*
  Fonctionnalité qui permet l'envoie de la chaine de caractères sous la forme de paires
  Nom associé a la donnée, Valeur de al donnée
*/
void sendPayload()
{
  char attributes[200];
  Payload += "}}";
  Payload.toCharArray(attributes, 200);

  mqttClient.beginMessage(topic);
  mqttClient.print(attributes);
  mqttClient.endMessage();

  Serial.print("Payload -> ");
  Serial.println(Payload);
  Serial.print("Payload length -> ");
  Serial.println(Payload.length());
}
