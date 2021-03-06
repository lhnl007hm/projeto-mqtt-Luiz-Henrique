#include <PubSubClient.h>
#include <UIPEthernet.h>
#include <utility/logging.h>
#include <SPI.h>


//Define o endereço MAC que será utilizado
byte mac[] = {0x40, 0x32, 0xD3, 0x03, 0x49, 0xC6};

int pino2 = 2;
boolean estado_sensor;
EthernetClient client;

PubSubClient mqttClient(client);


void setup() {
    
    
    //motor
    pinMode(pino2,INPUT_PULLUP);
    
    
    //Inicia o controlador Ethernet e solicita um IP para o servidor de DHCP
    Ethernet.begin(mac);

    //Inicia o monitor Serial
    Serial.begin(9600);

    mqttClient.setServer("ip do servidor",1883);

    //Exibe no Monitor Serial as informações sobre o IP do Arduino
    Serial.print("O IP do Arduino e: ");
    Serial.println(Ethernet.localIP());

    //Exibe no Monitor Serial as informações sobre a Máscara de Rede do Arduino
    Serial.print("A Mascara de Rede do Arduino e: ");
    Serial.println(Ethernet.subnetMask());

    //Exibe no Monitor Serial as informações sobre o Gateway do Arduino
    Serial.print("O Gateway do Arduino e: ");
    Serial.println(Ethernet.gatewayIP());

    //Exibe uma linha em branco
    Serial.println("");
    delay(5000);
}

void loop() {

  estado_sensor = digitalRead(pino2);

  mqttClient.connect("nome");
  
 //logica booleana para informar o estado da porta
  if(estado_sensor == 1){

    mqttClient.publish("topico","mensagem");
    Serial.println(estado_sensor);
    delay(1000);
  
    }else{

    mqttClient.publish("topico","mensagem");
    Serial.println(estado_sensor);
    delay(1000);

  }

  mqttClient.loop();

  delay(500);
    
}
