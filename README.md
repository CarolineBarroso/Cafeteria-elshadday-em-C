# ☕ Sistema de Gerenciamento de Produtos de uma Cafeteria

## 📌 Sobre o projeto

O **Sistema de Gerenciamento de Produtos de uma Cafeteria** é um projeto desenvolvido em linguagem C com o objetivo de facilitar o cadastro, a organização, a consulta e o gerenciamento dos produtos de uma cafeteria.

O sistema permite realizar operações de inclusão, alteração, exclusão, pesquisa e ordenação de produtos, além de armazenar as informações em arquivos para que os dados permaneçam disponíveis mesmo após o encerramento do programa.

O projeto foi desenvolvido com foco na aplicação prática dos conceitos de programação estruturada, manipulação de arquivos, funções, estruturas de dados e organização de informações.

## 🎯 Objetivo

Desenvolver um sistema que permita administrar os produtos de uma cafeteria de maneira organizada e prática, possibilitando o controle das informações de cada produto, como identificação, nome, categoria, preço, quantidade disponível e fornecedor.

## ⚙️ Tecnologias e ferramentas utilizadas

- **Linguagem C:** desenvolvimento da lógica e das funcionalidades do sistema.
- **Biblioteca stdio.h:** entrada e saída de dados e manipulação de arquivos.
- **Biblioteca stdlib.h:** funções auxiliares e gerenciamento de recursos.
- **Biblioteca string.h:** manipulação e comparação de textos.
- **Biblioteca ctype.h:** tratamento e análise de caracteres.
- **GDB Online:** ambiente utilizado para executar, testar e verificar o funcionamento do código.

## 🗂️ Informações dos produtos

Cada produto cadastrado possui os seguintes campos:

| Campo | Descrição |
|---|---|
| ID | Identificador único do produto. |
| Nome | Nome do produto comercializado. |
| Categoria | Classificação do produto. |
| Preço | Valor de venda do produto. |
| Quantidade | Quantidade disponível em estoque. |
| Fornecedor | Nome do fornecedor responsável pelo produto. |

## 🚀 Funcionalidades do sistema

O programa apresenta um menu interativo com as seguintes operações:

| Opção | Funcionalidade | Descrição |
|---|---|---|
| 1 | Criar/verificar arquivo | Verifica a existência do arquivo utilizado para armazenar os produtos. |
| 2 | Listar produtos | Exibe os produtos cadastrados no sistema. |
| 3 | Inserir produto | Permite cadastrar um novo produto com suas respectivas informações. |
| 4 | Alterar produto | Permite modificar os dados de um produto já cadastrado. |
| 5 | Excluir produto | Remove um produto do cadastro. |
| 6 | Buscar por nome | Localiza produtos utilizando o nome como critério de pesquisa. |
| 7 | Buscar por categoria | Filtra os produtos de acordo com sua categoria. |
| 8 | Ordenar nome A-Z | Organiza os produtos em ordem alfabética crescente. |
| 9 | Ordenar nome Z-A | Organiza os produtos em ordem alfabética decrescente. |
| 10 | Ordenar preço crescente | Apresenta os produtos do menor para o maior preço. |
| 11 | Ordenar preço decrescente | Apresenta os produtos do maior para o menor preço. |
| 12 | Exportar CSV | Gera um arquivo CSV com os dados dos produtos cadastrados. |
| 0 | Sair | Encerra a execução do programa. |

## 🧠 Conceitos de programação aplicados

Durante o desenvolvimento, foram utilizados diferentes conceitos fundamentais da linguagem C:

- **Struct:** criação de uma estrutura chamada `Produto` para organizar os dados de cada cadastro.
- **Vetores:** armazenamento temporário de até 100 produtos na memória.
- **Funções:** divisão do programa em partes menores, facilitando a organização, manutenção e reutilização do código.
- **Ponteiros:** utilização de referências para trabalhar com dados e operações do programa.
- **Condicionais:** aplicação de decisões utilizando estruturas como `if` e `else`.
- **Estruturas de repetição:** utilização de laços para percorrer registros e executar operações.
- **Manipulação de strings:** leitura, comparação, busca e tratamento de textos.
- **Manipulação de arquivos:** leitura, gravação e atualização dos dados armazenados.
- **Bubble Sort:** algoritmo utilizado para ordenar os produtos por nome e preço.
- **Validação de dados:** verificações para evitar entradas inválidas e inconsistências nos cadastros.

## 📁 Arquivos utilizados

O sistema utiliza arquivos para armazenar e exportar as informações dos produtos.

| Arquivo | Finalidade |
|---|---|
| `produtos.txt` | Armazenamento dos registros dos produtos cadastrados. |
| `produtos_temp.txt` | Arquivo temporário utilizado durante operações de atualização e exclusão de registros. |
| `produtos.csv` | Arquivo gerado para exportar os dados em formato CSV. |

A exportação CSV permite visualizar e organizar os dados em programas de planilhas, como Microsoft Excel.

## 📊 Organização do funcionamento

O funcionamento do sistema segue uma sequência de operações:

1. Inicialização do programa.
2. Verificação e carregamento dos dados armazenados.
3. Exibição do menu principal.
4. Escolha da operação desejada pelo usuário.
5. Execução da funcionalidade selecionada.
6. Atualização dos registros quando necessário.
7. Armazenamento das informações nos arquivos.
8. Exportação dos dados em CSV, quando solicitada.
9. Encerramento do programa.

## 💻 Execução do projeto

Para executar o projeto, é necessário possuir um compilador
