# Atividade 1 de computação gráfica

## Nome do desenvolvedor: Guilherme Gouveia Martinez
## RA: 11201720882

    Nome e RA dos desenvolvedores.
    Uma breve descrição do que é a aplicação.
    Outras informações que considerar relevantes.

## Descrição

Esta aplicação consite na simulação de 3 objetos:
 * Um avião;
 * Uma bola colorida;
 * Um retangulo.

Primeiramente, para controlar a bola colorida, é necessário clicar em qualquer região da aplicação, logo após será possível controlar-la utilizando as teclas `A` e `D` para aumentar a sua velocidade, respectivamente para a esquerda e para a direita. Com ela, podem ser feitas colisões ao retangulo que irá reagir de acordo com a velocidade que a bola estava na hora do impacto e devolverá parte dessa força para a bola. Sua posição pode ser alterada com o deslizador contido no menu. Caso tenha velocidade suficiente, é possível derrubar o retângulo, caso contrário ele irá balançar e retornar à possição inicial. 

Através de movimentos do mouse pode-se controlar o avião, que receberá uma força proporcional de acordo com a direção e intensidade dos movimentos. Ele também irá reagir caso a velocidade vertical esteja baixa ou alta, apontando o nariz para cima ou para baixo, além de mudar de direção caso passe a se movimentar na outra direção. A figura abaixo exibem quais regiões controlam ele e as setas amarelas indicam em qual direção será aplicada a aceleração.

![Tutorial avião](https://github.com/martinezguilherme/computacao_grafica-atividade1/blob/9ac9ea6a3622cc723e29b8f07f5549fcea0c617c/captura%20de%20tela%20-%20tutorial.png)

Na parte debaixo são exibidas algumas informações, como a velocidade da bolinha, a distância dela para o obstaculo e a velocidade do avião (eixo x).

Por fim, a aplicação pode ser reiniciada ao pressionar a tecla "Espaço".
