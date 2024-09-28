int led = 19;
int value = 0;
int Alarme = 15;

#define LDR 34

float luz=0;
const float GAMMA = 0.7;
const float RL10 = 33;
int valorAnterior = 0;

#include <WiFi.h>
#include <PubSubClient.h>


const char* ssid = "Wokwi-GUEST";
const char* password = "";
const char* mqtt_server = "test.mosquitto.org";

WiFiClient WOKWI_Client;
PubSubClient client(WOKWI_Client);

void setup_wifi() {

  delay(10);

  Serial.println();
  Serial.print("Conectando ao ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.println("Endereço IP: ");
  Serial.println(WiFi.localIP());

}

void reconnect() {
  while (!client.connected()) {
    Serial.println("Conectando ao MQTT");
    if (client.connect("WOKWI_Client")) {
      Serial.println("MQTTConectado");
    } else {
      Serial.print("failed");
      Serial.print(client.state());
      Serial.println("Tente novamente em 3s");
      delay(3000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  pinMode(led, OUTPUT);
  pinMode(13, INPUT);
  pinMode(Alarme, OUTPUT);
}

void Conectado_WIFI()
{
  if(WiFi.status())
  digitalWrite(0, HIGH);
  else
  digitalWrite(0, LOW);  
}

void Conectado_MQTT()
{
  if(client.connected())
  digitalWrite(2,HIGH);
  else
  digitalWrite(2, LOW);
}


void Sensor_Movimento(){
    Serial.println("Detector de movimento:");
     value = digitalRead(13);
  if (value == 1) {
    Serial.println("Sensor de movimento ATIVADO!!!...");
    delay(100);
    digitalWrite(led, HIGH);
    digitalWrite(Alarme, HIGH);
    delay(300);
    digitalWrite(Alarme, LOW);
  }
  else {
    Serial.println("Sensor de movimento desativado...");
    delay(300);
    digitalWrite(led, LOW);
  }
  delay(3000);
}

void loop() {
  reconnect();
  Conectado_MQTT();
  Conectado_WIFI();
  Sensor_Movimento();
  float iluminacao =  fotoresistor();
}

float  fotoresistor()
{
  int analogValue = analogRead(LDR);

   if (analogValue != valorAnterior) {
   


  float voltage = analogValue / 4096. * 3.3;
  float resistencia = 2000 * voltage / (1 - voltage / 3.3);
   luz = pow(RL10 * 1e3 * pow(10, GAMMA) / resistencia, (1 / GAMMA));


  Serial.print("Luz Ambiente: ");

  if (luz > 400) {
    Serial.println("Luz Clara!");
    digitalWrite(led, LOW);
  } else {
    Serial.println("Luz baixa");
    digitalWrite(led, HIGH);
  }


    Serial.print("Luminosidade: ");
  Serial.println(luz);

    valorAnterior = analogValue;
  }
  return luz;
}