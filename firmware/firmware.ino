// Felipe : 11/04 
// Projeto de Hardware da UEPG *Trabalhando como calouro pros parceiro do quinto ano;
// Tem comentário em tudo pra eu lembrar o que fazer, tenho TDAH :)
// Atualização só para as correções que o James comentou, continuarei escrevendo o codigo na segunda a noite.

#include <PubSubClient.h>
#include <WiFi.h>
#define PortaBotao 16
  
const char* ssid = "NOMEDAREDE";
const char* senha = "SenhaDaRede";
const char* mqtt_server "Insira o IP aqui";
const int mqtt_port = 1883;
const char* topicoUnico = "bacias/comando/proxima"
int botaoPress = 0;

void conectarWiFi(){
  WiFi.begin(ssid,senha); // Tenta conctar

  while (WiFi.status() != WL_CONNECTED()){ // Enquanto não ta conectado
    delay(500);
    Serial.println("To conectano, calma, eu trabalho pior sobre pressão");
  }
  Serial.println("Conectei !!! :D");
  Serial.println(WiFi_localIP();)
}
void mqttReconect(){
  while (!client.connected()){
    Serial.println("Conectando o MQTT");
    String clientId = "ENGEASIER_MQTT";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientID.c_str())){
      Serial.println("Conectado ( eu acho )")
      client.subscribe(topicoUnico);
    }
    else {
      Serial.print("Falha ao conectar = ");
      Serial.print(client.state());
      Serial.println("Tentando reconecção em 5 segundos");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  conectarWiFi();
  

  pinMode(PortaBotao, INPUT_PULLUP); // Declara a porta do botão
}

void loop() {
  //Reconectar o Wifi se tiver dado merda 
  if (WiFi.status() != WL_CONNECTED){
    WiFi.begin(ssid,senha);  // Não sei se é assim que reconecta XD pesquisa depois
    while (WiFi.status() != WL_CONNECTED){ // Enquanto não ta conectado
      delay(500);
      Serial.println("To conectano, calma, eu trabalho pior sobre pressão");
    }
    Serial.println("Conectei !!! :D");
  }
  //ler o botão
  botaoPress = digitalRead(PortaBotao);

  if (botaoPress == LOW){
    client.publich(topico, 1);
    delay(200); //Debouce improvisado por enquanto
  }
  //Conhectar o MQTT
}
