// Bibliotecas
#include <WiFi.h>
#include <DHT.h>
#include <UbidotsEsp32Mqtt.h>

// Configuração do ubidots
const char *UBIDOTS_TOKEN = "SEU_TOKEN";

// configuração do WiFi
const char *WIFI_SSID = "esp32nilton";
const char *WIFI_PASS = "senha123";

const char *DEVICE_LABEL = "DHT11";
const char *TEMPERATURA_LABEL = "temperatura";
const char *UMIDADE_LABEL = "umidade";

// Envia daddos a cada 5 segundos
const int PUBLISH_FREQUENCY = 5000;
unsigned long timer;

// Configuração do DHT
#define DHT_PIN 4
#define DHT_TYPE DHT11

DHT dht (DHT_PIN, DHT_TYPE);
Ubidots ubidots (UBIDOTS_TOKEN);

// Callback MQTT
void callback(char *topic, byte *payload, unsigned int length){
  Serial.print("Mensagem recebida [");
  Serial.print(topic);
  Serial.print("]");

  // Loop do payload
  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}


void setup() {
  // porta serial
  Serial.begin(9600);

  // Inicializa o DHT
  dht.begin();

  // Conecta ao Wi-Fi
  ubidots.connectToWifi(WIFI_SSID, WIFI_PASS);

  // Configura o callback do MQTT
  ubidots.setCallback(callback);

  // Configura o MQTT
  ubidots.setup();

  // Conecta no Ubidots
  ubidots.reconnect();

  timer = millis();

  Serial.println("Sistema iniciado!");
}

void loop() {
  // Verifica conexão do MQTT
  if (!ubidots.connected())
  {
    ubidots.reconnect();
  }

  // Envia os dados a cada 5 segundos
  if (abs((long)(millis() - timer)) > PUBLISH_FREQUENCY)
  {
    // Lê o sensor
    float temperatura = dht.readTemperature();
    float umidade = dht.readHumidity();

    // Verifica se a leitura é válida
    if (isnan(temperatura) || isnan(umidade))
    {
      Serial.println("Erro ao ler o DHT11");
      timer = millis();
      return;
    }

    // Mostrar no Monitor Serial
    Serial.print("Temperatura: ");
    Serial.print(temperatura);
    Serial.println(" ºC");

    Serial.print("Umidade: ");
    Serial.print(umidade);
    Serial.println(" %");

    // Adiciona as variáveis ao pacote do MQTT
    ubidots.add(TEMPERATURA_LABEL, temperatura);
    ubidots.add(UMIDADE_LABEL, umidade);

    // Publicar no Ubidots
    ubidots.publish(DEVICE_LABEL);

    Serial.println("Sucesso!!!");
    timer = millis();
  }
  ubidots.loop();
}
