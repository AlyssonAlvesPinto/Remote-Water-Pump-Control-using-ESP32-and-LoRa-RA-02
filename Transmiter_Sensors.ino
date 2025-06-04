#include <SPI.h>
#include <LoRa.h>

#define LORA_SCK  18
#define LORA_MISO 19
#define LORA_MOSI 23
#define LORA_SS   5
#define LORA_RST  14
#define LORA_DIO0 2

#define NIVEL_BAIXO  32  // sensor inferior
#define NIVEL_ALTO   33  // sensor superior

String lastCommand = "";
bool enchendo = false;

void setup() {
  Serial.begin(115200);
  while (!Serial);

  pinMode(NIVEL_BAIXO, INPUT_PULLUP);
  pinMode(NIVEL_ALTO, INPUT_PULLUP);

  SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_SS);
  LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);

  if (!LoRa.begin(433E6)) {
    Serial.println("Erro ao iniciar LoRa.");
    while (true);
  }

  Serial.println("Sistema iniciado.");
}

void loop() {
  bool nivelBaixoAtivado = digitalRead(NIVEL_BAIXO) == LOW;
  bool nivelAltoAtivado  = digitalRead(NIVEL_ALTO) == LOW;

  String comando = "";

  if (!nivelBaixoAtivado && !nivelAltoAtivado && !enchendo) {
    // Ambos sensores abertos → inicia enchimento
    comando = "LIGAR";
    enchendo = true;
  } 
  else if (nivelAltoAtivado && enchendo) {
    // Sensor de cima detecta cheio → para enchimento
    comando = "DESLIGAR";
    enchendo = false;
  }

  if (comando != "" && comando != lastCommand) {
    Serial.println("Enviando comando: " + comando);
    LoRa.beginPacket();
    LoRa.print(comando);
    LoRa.endPacket();
    lastCommand = comando;
  }

  delay(2000);
}
