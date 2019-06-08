//=============================================================
//  Classe Equipamento
//  Cria objetos para cada equipamento e permite que eles sejam
//  ligados, desligados, etc....
//
//  @author Aluizio Tomazelli Junior
//  Data: 08/06/2019
//=============================================================
#ifndef EQUIPAMENTO_H_
#define EQUIPAMENTO_H_
#include <Arduino.h>

class Equipamento {
private:
    byte pino;                          //pino do equipamento
    bool ligado;                        //estado do pino
    static Equipamento *atual;          //ponteiro para o ultimo objeto criado, compartilhado por todos objetos
    Equipamento *anterior;              //ponteiro para o objeto anterior criado, cada objeto tem o seu

public:
    Equipamento(byte pin);
    Equipamento(byte pin, bool state);
    void setup();                       //Faz o setup do equipamento
    void liga();                        //Liga equipamento
    void desliga();                     //Desliga equipamento
    bool isLigado();                    //Informa se o equipamento está ligado

    static void setupAll();             //Chama setup para todos objetos criados
    static void desligaAll();           //Chama desliga para todos objetos
    static void ligaAll();              //Chama desliga para todos objetos

};

Equipamento *Equipamento::atual = 0;    //Inicia a variável estática em zero

//  Construtor
//  @param byte pin - pino da saída digital na qual o equipamento está ligado
//  @param bool state - estado inicial da saída, HIGH ou LOW (true ou false, 1 ou 0)
Equipamento::Equipamento(byte pin, bool state)
        : pino(pin), ligado(state) {
    anterior = atual;       //Copia para a variável "anterior" um ponteiro para o ultimo objeto criado
    atual = this;           //Copia na variavel estática um ponteiro para o objeto que está sendo criado
}

void Equipamento::setup() {
    pinMode(pino, OUTPUT);          //seta o pino
    digitalWrite(pino, ligado);     //inicia com o valor da variável
}

void Equipamento::liga() {
    if (!ligado) {                      //se está desligado
        ligado = true;                  //muda o estado
        digitalWrite(pino, ligado);     //liga o equipamento
    }
}

void Equipamento::desliga() {
    if (ligado) {                       //se está ligado
        ligado = false;                 //muda o estado
        digitalWrite(pino, ligado);     //deliga o equipamento
        Serial.println("Deliga");
    }
}

//  @return - true se o equipamento está ligado
bool Equipamento::isLigado()
{
    return ligado;              //retorna true se o equipamento estiver ligado
}

//  setupAll() - Chama a função setup() para todos objetos criados
//
//  Faz um loop pegando o ponteiro para o ultimo objeto criado, chama setup para ele,
//  troca para o objeto anterior e repete, até chegar no primeiro obejto criado, onde
//  a variável "i" será 0 e irá interromper o laço.
void Equipamento::setupAll() {
    for (Equipamento *i = atual; i != 0; i = i->anterior)
        i->setup();
}

//  desligaAll() - Chama a função desliga() para todos objetos criados
void Equipamento::desligaAll() {
    for (Equipamento *i = atual; i != 0; i = i->anterior)
        i->desliga();
}

//  ligaAll() - Chama a função liga() para todos objetos criados
void Equipamento::ligaAll() {
    for (Equipamento *i = atual; i != 0; i = i->anterior)
        i->liga();
}

#endif /* EQUIPAMENTO_H_ */
