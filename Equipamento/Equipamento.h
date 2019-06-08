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
    static Equipamento *ultimo;         //ponteiro para o ultimo objeto criado, compartilhado por todos objetos
    Equipamento *anterior;              //ponteiro para o objeto anterior criado, cada objeto tem o seu

public:
    Equipamento(byte pin, bool state);
    void setup();                       //Faz o setup do equipamento
    void liga();                        //Liga equipamento
    void desliga();                     //Desliga equipamento
    bool isLigado();                    //Informa se o equipamento est� ligado
    static void setupAll();             //Chama setup para todos objetos criados
    static void desligaAll();           //Chama desliga para todos objetos
    static void ligaAll();              //Chama desliga para todos objetos

};
Equipamento *Equipamento::ultimo = 0;    //Inicia a vari�vel est�tica em zero

//  Construtor
//  @param byte pin - pino da sa�da digital na qual o equipamento est� ligado
//  @param bool state - estado inicial da sa�da, HIGH ou LOW (true ou false, 1 ou 0)
//
//  No primeiro objeto criado, a sua vari�vel "anterior" ser� 0, e a vari�vel "ultimo"
//      ser� um ponteiro para o pr�prio objeto. No segundo objeto criado, a sua vari�vel
//      anterior, ser� um ponteiro para o objeto que foi criado antes dele (no caso o primeiro),
//      e a vari�vel "ultimo", static, portanto compartilhada por todos objetos, ser� um
//      ponteiro para o objeto atual. Dessa forma podemos "rastrear" todos objetos criados,
//      pois a vari�vel "ultimo" aponta sempre para o �ltimo objeto, e dentro dele h� um ponteiro
//      para o objeto anterior, e assim sucessivamente, at� o primeiro objeto onde o ponteiro
//      da vari�vel "anterior � igual a zero. Com isso � poss�vel chamar o mesmo m�todo para todos
//      objetos criados, partindo do �ltimo at� chegar ao primeiro -- isso ser� usado nas fun��es
//      setupAll() e demais xxxxxAll().
Equipamento::Equipamento(byte pin, bool state)
        : pino(pin), ligado(state) {
    anterior = ultimo;      //Copia para a vari�vel "anterior" o ponteiro do ultimo objeto criado
    ultimo = this;          //Copia na vari�vel atual (static) um ponteiro para o objeto que est� sendo criado
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
bool Equipamento::isLigado() {
    return ligado;
}

//  setupAll() - Chama a fun��o setup() para todos objetos criados
//
//  Faz um loop usando como controle a vari�vel "ultimo", que aponta para o �ltimo
//      objeto criado, e chama o m�todo setup() para esse �ltimo objeto. Ao final
//      da primeira execu��o do la�o a vari�vel de controle assume o valor da vari�vel
//      "anterior", que, no �ltimo objeto, aponta para o pen�ltimo objeto criado.
//      Executa o la�o novamente, que ir� chamar setup() para o pen�ltimo objeto,
//      onde, por sua vez, a vari�vel "anterior" aponta para o antepen�ltimo objeto criado.
//      Dessa forma o la�o � executado at� que atinja o primeiro objeto criado, onde sua
//      vari�vel "anterior" tem valor 0, o que ir� interromper o la�o por n�o mais satisfazer
//      a condi��o de controle: i != 0
void Equipamento::setupAll() {
    for (Equipamento *i = ultimo; i != 0; i = i->anterior)
        i->setup();
}

//  desligaAll() - Chama a fun��o desliga() para todos objetos criados
void Equipamento::desligaAll() {
    for (Equipamento *i = ultimo; i != 0; i = i->anterior)
        i->desliga();
}

//  ligaAll() - Chama a fun��o liga() para todos objetos criados
void Equipamento::ligaAll() {
    for (Equipamento *i = ultimo; i != 0; i = i->anterior)
        i->liga();
}

#endif /* EQUIPAMENTO_H_ */
