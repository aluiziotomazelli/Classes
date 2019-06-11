# Classes

  ### Equipamento
  
  Uma pequena classe para comandar equipamentos ligados nas saídas digitais do Arduino.
  Usando a classe é possível comandar os equipamento de uma forma mais intuitiva, em vez
  de usar os comandos digitalWrite, pinMode, etc.
  
  #### Comandos individuais para os objetos
  > objeto.liga();  
  > obejto.desliga();  
  > objeto.isLigado();  
  
  #### Comandos para TODOS objetos criados
  > Equipamento::setupAll();  
  > Equipamento::ligaAll();  
  > Equipamento::desligaAll();  
