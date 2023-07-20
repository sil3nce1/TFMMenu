# Overlay com DirectX Hook para o jogo Transformice

Este projeto teve como objetivo criar um overlay para o jogo Transformice utilizando um hook no DirectX. O overlay é uma camada visual que é desenhada na parte superior do jogo, permitindo adicionar informações adicionais, gráficos ou interações sem modificar diretamente o código do jogo.

## Funcionamento

O overlay foi desenvolvido usando técnicas de hooking, que envolve a injeção de código em tempo de execução para interceptar chamadas da API DirectX do jogo e, assim, desenhar nossa camada visual. Ao realizar o hook no DirectX, podemos acessar as funções de desenho e, dessa forma, inserir elementos gráficos na tela do jogo.

## Pré-requisitos

- Sistema operacional compatível (ex: Windows 7, Windows 10, etc.).
- Conhecimento em C/C++ para a criação do hook e desenvolvimento do overlay.
- Um compilador C/C++ para compilar o código.
- Ferramentas para a injeção do hook no processo do jogo (ex: DLL Injector).

## Instruções de Uso

1. Clone o repositório do projeto para sua máquina local.

2. Abra o projeto em seu ambiente de desenvolvimento (ex: Visual Studio).

3. Compile o código para gerar a biblioteca de hook (DLL).

4. Execute o Transformice.

5. Utilize um injetor de DLL para injetar a biblioteca de hook no processo do Transformice em execução.
