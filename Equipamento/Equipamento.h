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
    bool isLigado();                    //Informa se o equipamento está ligado
    static void setupAll();             //Chama setup para todos objetos criados
    static void desligaAll();           //Chama desliga para todos objetos
    static void ligaAll();              //Chama desliga para todos objetos

};
Equipamento *Equipamento::ultimo = 0;    //Inicia a variável estática em zero

//  Construtor
//  @param byte pin - pino da saída digital na qual o equipamento está ligado
//  @param bool state - estado inicial da saída, HIGH ou LOW (true ou false, 1 ou 0)
//
//  No primeiro objeto criado, a sua variável "anterior" será 0, e a variável "ultimo"
//      será um ponteiro para o próprio objeto. No segundo objeto criado, a sua variável
//      anterior, será um ponteiro para o objeto que foi criado antes dele (no caso o primeiro),
//      e a variável "ultimo", static, portanto compartilhada por todos objetos, será um
//      ponteiro para o objeto atual. Dessa forma podemos "rastrear" todos objetos criados,
//      pois a variável "ultimo" aponta sempre para o último objeto, e dentro dele há um ponteiro
//      para o objeto anterior, e assim sucessivamente, até o primeiro objeto onde o ponteiro
//      da variável "anterior é igual a zero. Com isso é possível chamar o mesmo método para todos
//      objetos criados, partindo do último até chegar ao primeiro -- isso será usado nas funções
//      setupAll() e demais xxxxxAll().
Equipamento::Equipamento(byte pin, bool state)
        : pino(pin), ligado(state) {
    anterior = ultimo;      //Copia para a variável "anterior" o ponteiro do ultimo objeto criado
    ultimo = this;          //Copia na variável atual (static) um ponteiro para o objeto que está sendo criado
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
bool Equipamento::isLigado() {
    return ligado;
}

//  setupAll() - Chama a função setup() para todos objetos criados
//
//  Faz um loop usando como controle a variável "ultimo", que aponta para o último
//      objeto criado, e chama o método setup() para esse último objeto. Ao final
//      da primeira execução do laço a variável de controle assume o valor da variável
//      "anterior", que, no último objeto, aponta para o penúltimo objeto criado.
//      Executa o laço novamente, que irá chamar setup() para o penúltimo objeto,
//      onde, por sua vez, a variável "anterior" aponta para o antepenúltimo objeto criado.
//      Dessa forma o laço é executado até que atinja o primeiro objeto criado, onde sua
//      variável "anterior" tem valor 0, o que irá interromper o laço por não mais satisfazer
//      a condição de controle: i != 0
void Equipamento::setupAll() {
    for (Equipamento *i = ultimo; i != 0; i = i->anterior)
        i->setup();
}

//  desligaAll() - Chama a função desliga() para todos objetos criados
void Equipamento::desligaAll() {
    for (Equipamento *i = ultimo; i != 0; i = i->anterior)
        i->desliga();
}

//  ligaAll() - Chama a função liga() para todos objetos criados
void Equipamento::ligaAll() {
    for (Equipamento *i = ultimo; i != 0; i = i->anterior)
        i->liga();
}

#endif /* EQUIPAMENTO_H_ */
