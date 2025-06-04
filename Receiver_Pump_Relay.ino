#include <SPI.h>
#include <LoRa.h>

// --- Pinos LoRa ---
#define LORA_SCK   18
#define LORA_MISO  19
#define LORA_MOSI  23
#define LORA_SS    5
#define LORA_RST   14
#define LORA_DIO0  2

// --- Pino do relé ---
#define PINO_RELE  25   // ajuste se necessário

// --- Controle de estado da bomba ---
bool bombaLigada = false;

void setup() {
  Serial.begin(115200);
  while (!Serial);

  // Inicializa pino do relé
  pinMode(PINO_RELE, OUTPUT);
  digitalWrite(PINO_RELE, HIGH);  // desliga relé (ativo LOW)

  // Inicializa SPI e LoRa
  SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_SS);
  LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);

  if (!LoRa.begin(433E6)) {
    Serial.println("Erro ao iniciar LoRa.");
    while (true);
  }

  Serial.println(">> Receptor PRONTO <<");
}

void loop() {
  int packetSize = LoRa.parsePacket();

  if (packetSize) {
    String comando = "";
    while (LoRa.available()) {
      comando += (char)LoRa.read();
    }

    comando.trim();  // remove espaços e quebras de linha

    Serial.println(">> Comando recebido: " + comando);

    if (comando == "LIGAR" && !bombaLigada) {
      ligarBomba();
    } else if (comando == "DESLIGAR" && bombaLigada) {
      desligarBomba();
    }
  }
}

void ligarBomba() {
  digitalWrite(PINO_RELE, LOW);  // ativo em LOW
  bombaLigada = true;
  Serial.println(">> Bomba LIGADA");
}

void desligarBomba() {
  digitalWrite(PINO_RELE, HIGH);  // desativa relé
  bombaLigada = false;
  Serial.println(">> Bomba DESLIGADA");
}
