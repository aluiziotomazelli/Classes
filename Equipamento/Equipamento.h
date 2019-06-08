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
    bool isLigado();                    //Informa se o equipamento est� ligado

    static void setupAll();             //Chama setup para todos objetos criados
    static void desligaAll();           //Chama desliga para todos objetos
    static void ligaAll();              //Chama desliga para todos objetos

};

Equipamento *Equipamento::atual = 0;    //Inicia a vari�vel est�tica em zero

//  Construtor
//  @param byte pin - pino da sa�da digital na qual o equipamento est� ligado
//  @param bool state - estado inicial da sa�da, HIGH ou LOW (true ou false, 1 ou 0)
Equipamento::Equipamento(byte pin, bool state)
        : pino(pin), ligado(state) {
    anterior = atual;       //Copia para a vari�vel "anterior" um ponteiro para o ultimo objeto criado
    atual = this;           //Copia na variavel est�tica um ponteiro para o objeto que est� sendo criado
}

void Equipamento::setup() {
    pinMode(pino, OUTPUT);          //seta o pino
    digitalWrite(pino, ligado);     //inicia com o valor da vari�vel
}

void Equipamento::liga() {
    if (!ligado) {                      //se est� desligado
        ligado = true;                  //muda o estado
        digitalWrite(pino, ligado);     //liga o equipamento
    }
}

void Equipamento::desliga() {
    if (ligado) {                       //se est� ligado
        ligado = false;                 //muda o estado
        digitalWrite(pino, ligado);     //deliga o equipamento
        Serial.println("Deliga");
    }
}

//  @return - true se o equipamento est� ligado
bool Equipamento::isLigado()
{
    return ligado;              //retorna true se o equipamento estiver ligado
}

//  setupAll() - Chama a fun��o setup() para todos objetos criados
//
//  Faz um loop pegando o ponteiro para o ultimo objeto criado, chama setup para ele,
//  troca para o objeto anterior e repete, at� chegar no primeiro obejto criado, onde
//  a vari�vel "i" ser� 0 e ir� interromper o la�o.
void Equipamento::setupAll() {
    for (Equipamento *i = atual; i != 0; i = i->anterior)
        i->setup();
}

//  desligaAll() - Chama a fun��o desliga() para todos objetos criados
void Equipamento::desligaAll() {
    for (Equipamento *i = atual; i != 0; i = i->anterior)
        i->desliga();
}

//  ligaAll() - Chama a fun��o liga() para todos objetos criados
void Equipamento::ligaAll() {
    for (Equipamento *i = atual; i != 0; i = i->anterior)
        i->liga();
}

#endif /* EQUIPAMENTO_H_ */
