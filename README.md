# firmware-robo
Firmware para um robô de futebol de robôs

## Estruturamento do projeto

```
├── build           (Arquivos de compilação do projeto)
├── build-pc        (Arquivos de compilação para o simulador)
├── build-robot     (Arquivos de compilação para o firmware do robô)
└── src             (Código fonte do projeto)
    ├── common      (Códigos comuns independente da plataforma de compilação)
    ├── firmware    (Códigos exclusivos do firmware)
    ├── hal         (Camada de abstração de hardware)
    └── simulator   (Códigos exclusivos do simulador)
        └── protos  (Arquivos necessários para comunicação com o GrSim)
```

## Como testar?

### Rodar no simulador

Para rodar no simulador será necessário ter instalado o GrSim em seu computador e estar com ele aberto. Após isso, checar se o endereço IP e porta estão de acordo com os pré-definidos no projeto (usam o padrão do simulador, então provavelmente já está devidamente configurado). Então será necessário estar no diretório base do repositório e executar o seguinte comando:

```meson setup build-pc```

### Compilar o firmware

Será necessário ter instalado o SDCC para que seja possível fazer o cross-compiling (compilar para o PIC16F873 e depois converter para .hex). Após ter instalado o SDCC, executar o seguinte comando no diretório base do repositório:

```meson setup build-robot --cross-file cross_pic.txt```

### To-Do

- [ ] Testar a compilação de firmware num robô real
- [ ] Implementar uma melhor estratégia
- [ ] Criar mais funcionalidades pro robô
- [ ] Testar e, se necessário, calibrar o PID
