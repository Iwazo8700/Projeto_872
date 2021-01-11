# Projeto_872
Enzo Iwata e João Kruse

## Ideia Inicial

A ideia incial seria fazer um jogo no estilo de Tetris

### Solo
O jogo funciona basicamente como o Tetris

### Multiplayer
Todos os jogadores jogam no mesmo mapa movendo cada um uma peça. Peças interagem entre si e o último jogador a colocar a peça na linha é quem recebe os pontos.

## Como Jogar

Depois de compilar o jogo com cmake, 2 executáveis serão criados: Sirtet e client.
Para iniciar o servidor executamos o Sirtet. Com o servidor rodando, podemos executar o client, que conectará com o servidor (o IP do servidor com o qual se conectar pode ser escolhido no arquivo config na pasta assets) e a tela do jogo será aberta.

Controles:
* A ou Left Arrow --> move a peça pra esquerda
* D ou Right Arrow --> move a peça para a direita
* S ou Down Arrow --> Desce a peça mais rápido
* Space --> Desce a peça o máximo possível
* Q --> Gira a peça no sentido anti-horário
* E --> GIra a peça no sentido horário

O jogo termina quando todos os jogadores jogando tiverem perdido, e o servidor é finalizado.


OBS: O jogo possui um arquivo com as configurações chamado config na pasta assets. É importante que o cliente e o servidor estejam usando as mesmas configurações.

O jogo foi desenvolvido e testado em Ubuntu 16.04 e 20.04. Embora o jogo possua diferetes parâmetros que podem ser modificados no arquivo de configuração a maioria deles foi testada mais profundamente apenas nas configurações padrões, de modo que é possível que alterá-las cause bugs.
