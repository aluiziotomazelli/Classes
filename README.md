# Classes

  #Equipamento
  
  Uma pequena classe para comandar equipamentos ligados nas saídas digitais do Arduino.
  Usando a classe é possível comandar os equipamento de uma forma mais intuitiva, em vez
  de usar os comandos digitalWrite, pinMode, etc.
  
  // Criando objetos ou instancias para cada equipamentos
  
  Equipamento aquecedor(10, LOW);     //aquecedor ligado no pino 10, inicia desligado
  
  Equipamento filtro(9, HIGH);        //filtro ligado no pino 13, inicia ligado

  // Fazendo o setup deles: a função abaixo deve ser executada dentro da função setup() 
  //    do arduíno, ela faz setup em todos equipamentos, seta os pinos como saídas e os inicia
  //    no estado definido na criação das instancias
  Equipamento::setupAll();    //Faz setup em todos equipamentos
  
  // Ligando um equipamento
  aquecedor.liga();
  
  // Desligando um equipamento
  filtro.desliga();
  
  // Ligando TODOS equipamentos
  Equipamento::ligaAll();
  
  //  Desligando TODOS equipamentos
  Equipamento::desligaAll();
  
  //  Verificando se algum esquipmento está ligado
  filtro.isLigado();
  aquecedor.isLigado();
