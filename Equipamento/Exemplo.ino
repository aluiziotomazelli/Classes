#include "Arduino.h"
#include "Equipamento.h"
// =============================================================================
//  CRIA OBJETOS PARA OS EQUIPAMENTOS LIGADOS NAS SA�DAS DO ARDUINO
//
//  A sintaxe de cria��o �:
//  Equipamento nomeDoEquipamento(pino em que ele est� ligado);
//
//  Por padr�o a sa�da � inicializada desligada, se quiser inicializar ela
//  ligada � preciso usar a sintaxe abaixo:
//  Equipamento nomeDoEquipamento(pino, HIGH);
//
// =============================================================================

Equipamento aquecedor(10);      //aquecedor ligado no pino 10
Equipamento fan(11);            //fan ligado no pino 11
Equipamento solenoide(A2);      //solenoide ligada no pino 12
Equipamento filtro(9, HIGH);    //filtro ligado no pino 13, que ir� iniciar ligado

void setup()
{
    Serial.begin(115200);   //inicia a sa�da serial para comunica��o

    // =============================================================================
    //  SETUP NOS EQUIPAMENTOS
    //
    //  O comando abaixo d� setup em cada objeto criado, seta os pinos como sa�da e
    //  os inicia desligados, OU ligados se na cria��o foi colocada a palavra HIGH
    //  como no exemplo Equipamento filtro(13, HIGH);
    // =============================================================================
    Serial.println(F("Fazendo setup nos equipamentos"));
    Equipamento::setupAll();    //Faz setup em todos equipamentos
}

void loop()
{
    delay(2000);    //delay para facilitar a visualiza��o das etapas

    // =============================================================================
    //  PARA LIGAR UM EQUIPAMENTO USA-SE A FUN��O:
    //  nomeDoEquipamento.liga();
    // =============================================================================
    Serial.println(F("Ligando equipamentos"));
    aquecedor.liga();
    fan.liga();
    solenoide.liga();

    // =============================================================================
    //  PARA VERIFICAR SE UM EQUIPAMENTO EST� LIGADO:
    //  nomeDoEquipamento.isLigado();
    //  A fun��o acima retorna true se o equipamento estiver ligado
    // =============================================================================
    if (filtro.isLigado()) {    //se o filtro estiver ligado
        Serial.println(F("O filtro est� ligado"));
    }
    delay(2000);    //delay para facilitar a visualiza��o das etapas

    // =============================================================================
    //  PARA DESLIGAR UM EQUIPAMENTO USA-SE A FUN��O:
    //  nomeDoEquipamento.desliga();
    // =============================================================================
    filtro.desliga();               //desliga o filtro
    delay(2000);
    solenoide.desliga();            //desliga solen�ide
    if (!solenoide.isLigado()) {    //se a solen�ide N�O estiver ligada
        Serial.println(F("A solen�ide est� desligada"));
    }
    delay(2000);    //delay para facilitar a visualiza��o das etapas

    // =============================================================================
    //  PARA LIGAR TODOS EQUIPAMENTOS:
    //  Equipamento::ligaAll();
    // =============================================================================
    Serial.println(F("Ligando TODOS equipamentos"));
    Equipamento::ligaAll();
    delay(2000);    //delay para facilitar a visualiza��o das etapas

    // =============================================================================
    //  PARA DESLIGAR TODOS EQUIPAMENTOS:
    //  Equipamento::desligaAll();
    // =============================================================================
    Serial.println(F("Desligando TODOS equipamentos"));
    Equipamento::desligaAll();
    delay(2000);    //delay para facilitar a visualiza��o das etapas
}
