#include "Arduino.h"
#include "Equipamento.h"
// =============================================================================
//  CRIA OBJETOS PARA OS EQUIPAMENTOS LIGADOS NAS SAÍDAS DO ARDUINO
//
//  A sintaxe de criação é:
//  Equipamento nomeDoEquipamento(pino em que ele está ligado, ESTADO_INICIAL);
//
// =============================================================================

Equipamento aquecedor(10, LOW);     //aquecedor ligado no pino 10, inicia desligado
Equipamento fan(11, LOW);           //fan ligado no pino 11
Equipamento solenoide(A2, LOW);     //solenoide ligada no pino 12
Equipamento filtro(9, HIGH);        //filtro ligado no pino 13, inicia ligado

void setup()
{
    Serial.begin(115200);   //inicia a saída serial para comunicação

    // =============================================================================
    //  SETUP NOS EQUIPAMENTOS
    //
    //  O comando abaixo dá setup em cada objeto criado, seta os pinos como saída e
    //  os inicia ligados ou desligados, conforme o parâmetro passado no construtor
    //  dele, HIGH ou LOW
    // =============================================================================
    Serial.println(F("Fazendo setup nos equipamentos"));
    Equipamento::setupAll();    //Faz setup em todos equipamentos
}

void loop()
{
    delay(2000);    //delay para facilitar a visualização das etapas

    // =============================================================================
    //  PARA LIGAR UM EQUIPAMENTO USA-SE A FUNÇÃO:
    //  nomeDoEquipamento.liga();
    // =============================================================================
    Serial.println(F("Ligando equipamentos"));
    aquecedor.liga();
    fan.liga();
    solenoide.liga();

    // =============================================================================
    //  PARA VERIFICAR SE UM EQUIPAMENTO ESTÁ LIGADO:
    //  nomeDoEquipamento.isLigado();
    //  A função acima retorna true se o equipamento estiver ligado
    // =============================================================================
    if (filtro.isLigado()) {    //se o filtro estiver ligado
        Serial.println(F("O filtro está ligado"));
    }
    delay(2000);    //delay para facilitar a visualização das etapas

    // =============================================================================
    //  PARA DESLIGAR UM EQUIPAMENTO USA-SE A FUNÇÃO:
    //  nomeDoEquipamento.desliga();
    // =============================================================================
    filtro.desliga();               //desliga o filtro
    delay(2000);
    solenoide.desliga();            //desliga solenóide
    if (!solenoide.isLigado()) {    //se a solenóide NÃO estiver ligada
        Serial.println(F("A solenóide está desligada"));
    }
    delay(2000);    //delay para facilitar a visualização das etapas

    // =============================================================================
    //  PARA LIGAR TODOS EQUIPAMENTOS:
    //  Equipamento::ligaAll();
    // =============================================================================
    Serial.println(F("Ligando TODOS equipamentos"));
    Equipamento::ligaAll();
    delay(2000);    //delay para facilitar a visualização das etapas

    // =============================================================================
    //  PARA DESLIGAR TODOS EQUIPAMENTOS:
    //  Equipamento::desligaAll();
    // =============================================================================
    Serial.println(F("Desligando TODOS equipamentos"));
    Equipamento::desligaAll();
    delay(2000);    //delay para facilitar a visualização das etapas
}
