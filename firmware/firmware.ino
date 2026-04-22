// Felipe : 11/04
// Projeto de Hardware da UEPG *Trabalhando como calouro pros parceiro do quinto ano;
// Tem comentário em tudo pra eu lembrar o que fazer, tenho TDAH :)

#include <PubSubClient.h>
#include <WiFi.h>
#include <SparkFun_APDS9960.h>
#include <Wire.h>


#define PinoAPDS 2

const char* ssid = "NOMEDAREDE";
const char* senha = "SenhaDaRede";
const char* mqtt_server "Insira o IP aqui";
const int mqtt_port = 1883;
const char* topicoUnico = "bacias/comando/proxima" ;
sensorGesto apds = SparkFun_APDS9960();
int isr_flag = 0; // Variavel da interrupção do sensor de gesto.

void conectarWiFi() {
  WiFi.begin(ssid, senha);  // Tenta conctar

  while (WiFi.status() != WL_CONNECTED()) {  // Enquanto não ta conectado
    delay(500);
    Serial.println("To conectano, calma, eu trabalho pior sobre pressão");
  }
  Serial.println("Conectei !!! :D");
  Serial.println(WiFi_localIP();)
}
void mqttReconect() {
  while (!client.connected()) {
    Serial.println("Conectando o MQTT");
    String clientId = "ENGEASIER_MQTT";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientID.c_str())) {
      Serial.println("Conectado ( eu acho )")
        client.subscribe(topicoUnico);
    } else {
      Serial.print("Falha ao conectar = ");
      Serial.print(client.state());
      Serial.println("Tentando reconecção em 5 segundos");
      delay(5000);
    }
  }
}

void handleGesture() {
    if ( apds.isGestureAvailable() ) {
    switch ( apds.readGesture() ) {
      case DIR_UP:
        client.publish(topico, "indo") // X para o valor de abrir detalhes técnicos.
        break;
      case DIR_DOWN:
        client.publish(topico, "home") // X para o valor de voltar para o inicio.
        break;
      case DIR_LEFT:
        client.publish(topico, "anterior") // X para o valor de voltar uma Bacia.
        break;
      case DIR_RIGHT:
        client.publish(topico, "proximo") // X para o valor de ir pra próxima bacia.
        break;
      default:
        Serial.println("NONE");
    }
  }
}

void interruptRoutine(){
  isr_flag =1;
}


void setup() {
  Serial.begin(115200);
  conectarWiFi();
  mqttReconect();
  pinMode(PinoAPDS, INPUT);
  attachInterrupt(0, interruptRoutine, FALLING); // Interrupção pro sensor só funcionar quando algum gesto estiver sendo feito.

}

void loop() {
  //Reconectar o Wifi se tiver dado merda
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(ssid, senha);                 // Não sei se é assim que reconecta XD pesquisa depois
    while (WiFi.status() != WL_CONNECTED) {  // Enquanto não ta conectado
      delay(500);
      Serial.println("To conectano, calma, eu trabalho pior sobre pressão");
    }
    Serial.println("Conectei !!! :D");
  }
  mqttReconect();
  //Sensor de gesto a partir daqui
  if( isr_flag == 1 ) {
    detachInterrupt(0);
    handleGesture();
    isr_flag = 0;
    attachInterrupt(0, interruptRoutine, FALLING);
  }
}
