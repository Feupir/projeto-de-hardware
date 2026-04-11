// Felipe : 11/04 
// Projeto de Hardware da UEPG *Trabalhando como calouro pros parceiro do quinto ano;
// Tem comentário em tudo pra eu lembrar o que fazer, tenho TDAH :)

#include <WiFi.h>

const char* /* não sei pq que tem o asteristico, tenho que descobrir isso */ ssid = "NOMEDAREDE";
const char* senha = "SenhaDaRede";
int PortaBotao = 16;
int botaoPress = 0;

void setup() {
  Serial.begin(115200);
  //Conecta a internet
  WiFi.begin(ssid,senha); // Tenta conctar

  while (WiFi.status() != WL_CONNECTED()){ // Enquanto não ta conectado
    delay(500);
    Serial.println("To conectano, calma, eu trabalho pior sobre pressão");
  }
  Serial.println("Conectei !!! :D");

  pinMode(PortaBotao, INPUT_PULLUP); // Declara a porta do botão
}

void loop() {
  //Reconectar o Wifi se tiver dado merda 
  if (WiFi.status() != WL_CONNECTED()){
    WiFi.begin(ssid,senha);  // Não sei se é assim que reconecta XD pesquisa depois
    while (WiFi.status() != WL_CONNECTED()){ // Enquanto não ta conectado
      delay(500);
      Serial.println("To conectano, calma, eu trabalho pior sobre pressão");
    }
    Serial.println("Conectei !!! :D");
  }
  //ler o botão
  botaoPress = digitalRead(PortaBotao);

  if (botaoPress == LOW){
    Serial.println("APERTO Ó, TA APERTADO"); // (Inserir o Código de verdade aqui depois)
    delay(200); //Debouce improvisado por enquanto
  }


  //Conhectar o MQTT
}
