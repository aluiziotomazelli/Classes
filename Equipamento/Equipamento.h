//=============================================================
//  Classe Equipamento
//  Data: 05/06/19
//
//  Cria objetos para cada equipamento e permite que eles sejam
//  ligados, desligados, etc....
//=============================================================
#ifndef EQUIPAMENTO_H_
#define EQUIPAMENTO_H_
#include <Arduino.h>

//  Classe para facilitar o c�digo e torn�-lo mais leg�vel
class Equipamento {
private:
    byte pino;                          //pino do equipamento
    bool ligado;                        //estado do pino
    static Equipamento *atual;          //ponteiro para o ultimo objeto criado
    Equipamento *anterior;              //ponteiro para o objeto anterior criado

public:
    Equipamento(byte pin);
    Equipamento(byte pin, bool state);
    void setup();                       //Faz o setup do equipamento
    void liga();                        //Liga equipamento
    void desliga();                     //Desliga equipamento
    bool isLigado();                    //Informa se o quipamento est� ligado

    static void setupAll();             //Chama setup para todos objetos criados
    static void desligaAll();           //Chama desliga para todos objetos
    static void ligaAll();              //Chama desliga para todos objetos

};

Equipamento *Equipamento::atual = 0;    //Inicia a variavel estatica em zero

//  Construtor
//  @param byte pin - pino da sa�da digital na qual o equipamento est� ligado
//  @param bool state - estado inicial da sa�da, HIGH ou LOW (true ou false, 1 ou 0)
//
Equipamento::Equipamento(byte pin, bool state)
        : pino(pin), ligado(state) {
    anterior = atual;       //Copia para o membro "anterior" um ponteiro para o ultimo objeto criado
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

// Faz um loop pegando o ponteiro para o ultimo objeto criado, chama setup para ele,
// troca para o objeto anterior e repete, at� chegar no primeiro obejto criado, onde
// a vari�vel "i" ser� 0 e ir� interromper o la�o.
void Equipamento::setupAll() {
    for (Equipamento *i = atual; i != 0; i = i->anterior)
        i->setup();
}

void Equipamento::desligaAll() {
    for (Equipamento *i = atual; i != 0; i = i->anterior)
        i->desliga();
}

void Equipamento::ligaAll() {
    for (Equipamento *i = atual; i != 0; i = i->anterior)
        i->liga();
}

#endif /* EQUIPAMENTO_H_ */
