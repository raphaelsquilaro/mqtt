# 🌡️ Monitoramento de Temperatura e Umidade com ESP32, DHT11 e Ubidots

## 📌 Sobre o projeto

Este projeto utiliza um **ESP32** conectado a um sensor **DHT11** para realizar a leitura de temperatura e umidade do ambiente. Os dados coletados são enviados para a plataforma **Ubidots** por meio do protocolo MQTT, permitindo o monitoramento das informações em tempo real por meio de dashboards.

O sistema realiza novas leituras e publicações a cada 5 segundos, exibindo os valores no Monitor Serial e enviando-os para a nuvem.

## 🎯 Objetivos

- Medir a temperatura do ambiente em graus Celsius (°C).
- Medir a umidade relativa do ar em porcentagem (%).
- Conectar o ESP32 à rede Wi-Fi.
- Enviar os dados para a plataforma Ubidots utilizando MQTT.
- Permitir a visualização dos dados em dashboards.
- Identificar falhas na leitura do sensor e restabelecer a conexão MQTT quando necessário.

## 🛠️ Tecnologias e componentes

### Hardware

- ESP32
- Sensor de temperatura e umidade DHT11
- Cabos jumper
- Protoboard (opcional)

### Software e bibliotecas

- Arduino IDE
- Biblioteca `WiFi.h`
- Biblioteca `DHT.h`
- Biblioteca `UbidotsEsp32Mqtt.h`
- Plataforma [Ubidots](https://ubidots.com/)

## 🔌 Esquema de ligação

Conecte o sensor DHT11 ao ESP32 conforme a tabela:

| DHT11 | ESP32 |
|---|---|
| VCC | 3,3 V |
| GND | GND |
| DATA | GPIO 4 |

**Observação:** confira a pinagem do seu módulo DHT11. Sensores DHT11 sem módulo podem precisar de um resistor pull-up entre DATA e VCC.

## ⚙️ Configuração do projeto

### 1. Instale as bibliotecas

Na Arduino IDE, acesse o Gerenciador de Bibliotecas e instale:

- **DHT sensor library**, da Adafruit.
- **Ubidots ESP32 MQTT**, conforme a biblioteca utilizada no código.

A biblioteca `WiFi.h` já é disponibilizada pelo pacote de placas ESP32.

### 2. Configure o Wi-Fi

No código, informe o nome e a senha da rede Wi-Fi à qual o ESP32 será conectado:

```cpp
const char *WIFI_SSID = "NOME_DA_REDE";
const char *WIFI_PASS = "SENHA_DA_REDE";
```

### 3. Configure o token do Ubidots

Acesse sua conta no [Ubidots](https://ubidots.com/), obtenha o token de acesso e configure a variável correspondente:

```cpp
const char *UBIDOTS_TOKEN = "SEU_TOKEN";
```

**Importante:** não compartilhe seu token nem publique senhas reais em repositórios públicos. Prefira utilizar configurações locais ou mecanismos seguros para armazenar essas credenciais.

### 4. Configure os identificadores

O código utiliza os seguintes identificadores para organizar os dados na plataforma:

```cpp
const char *DEVICE_LABEL = "DHT11";
const char *TEMPERATURA_LABEL = "temperatura";
const char *UMIDADE_LABEL = "umidade";
```

- `DHT11`: identificador do dispositivo no Ubidots.
- `temperatura`: variável que armazena a temperatura.
- `umidade`: variável que armazena a umidade relativa do ar.

Esses identificadores são utilizados para publicar os dados e organizar sua visualização no dashboard.

### 5. Selecione a placa e a porta

Na Arduino IDE:

1. Selecione a placa ESP32 correspondente ao seu modelo.
2. Escolha a porta serial correta.
3. Envie o código para o dispositivo.
4. Abra o Monitor Serial com a velocidade de **9600 baud**.

## 🔄 Funcionamento do sistema

O programa executa as seguintes etapas:

1. Inicializa a comunicação serial e o sensor DHT11.
2. Conecta o ESP32 à rede Wi-Fi configurada.
3. Configura a comunicação MQTT com o Ubidots.
4. Verifica se a conexão MQTT está ativa e tenta reconectar quando necessário.
5. Realiza a leitura da temperatura e da umidade a cada 5 segundos.
6. Verifica se as leituras são válidas.
7. Exibe os valores no Monitor Serial.
8. Adiciona as variáveis ao pacote MQTT.
9. Publica os dados no dispositivo configurado no Ubidots.

Se o sensor retornar uma leitura inválida, o programa informa o erro no Monitor Serial e aguarda o próximo ciclo de leitura.

## 📊 Dados enviados

| Variável | Descrição | Unidade |
|---|---|---|
| `temperatura` | Temperatura do ambiente | °C |
| `umidade` | Umidade relativa do ar | % |

**Frequência de envio:** aproximadamente 5 segundos entre publicações bem-sucedidas.

## 🖥️ Exemplo de saída no Monitor Serial

```text
Sistema iniciado!
Temperatura: 25.4 ºC
Umidade: 62.0 %
Sucesso!!!
```

Os valores apresentados são apenas exemplos. As medições reais dependem das condições do ambiente.

## ☁️ Visualização no Ubidots

Após configurar o dispositivo e enviar o código:

1. Acesse sua conta no Ubidots.
2. Abra a seção de dispositivos (*Devices*).
3. Localize o dispositivo identificado como `DHT11`.
4. Verifique as variáveis `temperatura` e `umidade`.
5. Crie um dashboard com gráficos, indicadores ou outros widgets para acompanhar as medições.

Os dados serão atualizados conforme as publicações recebidas pela plataforma.

## 🧰 Solução de problemas

| Problema | Possível solução |
|---|---|
| Erro ao ler o DHT11 | Confira os fios, a alimentação e o pino GPIO 4. |
| ESP32 não conecta ao Wi-Fi | Verifique o nome da rede e a senha. |
| Dados não aparecem no Ubidots | Confira o token, os identificadores e a conexão MQTT. |
| Dispositivo não aparece na plataforma | Verifique se o token utilizado é válido e se os dados estão sendo publicados. |
| Leituras inconsistentes | Confira as conexões e evite leituras muito frequentes do sensor. |

## 🚀 Possíveis melhorias

- Criar dashboards personalizados no Ubidots.
- Configurar alertas para limites de temperatura e umidade.
- Armazenar o histórico das medições.
- Implementar reconexão automática ao Wi-Fi.
- Adicionar outros sensores ao ESP32.
- Melhorar o tratamento de falhas de comunicação.

## 📄 Licença

Este projeto pode ser distribuído sob a licença MIT, caso essa seja a licença escolhida pelo autor. Para utilizá-la, adicione um arquivo `LICENSE` com o texto correspondente.

## 👨‍💻 Autor

Desenvolvido como projeto de monitoramento ambiental utilizando ESP32, sensor DHT11 e plataforma Ubidots.
