
#include <stdio.h>      // Biblioteca para entrada e saida de dados.
#include <stdlib.h>     // Biblioteca para conversoes e funcoes gerais.
#include <string.h>     // Biblioteca para manipulacao de strings.
#include <ctype.h>      // Biblioteca para trabalhar com caracteres.

// Define a quantidade maxima de produtos cadastrados.
#define MAX_PRODUTOS 100

// Define o tamanho maximo do arquivo de leitura.
#define TAM_LINHA 250

// Estrutura que armazena os dados de cada produto.
typedef struct {
    int id;                 // Identificador automatico.
    char produto[50];       // Nome do produto.
    char categoria[40];     // Categoria do produto.
    float preco;            // Preco de venda.
    int quantidade;         // Quantidade em estoque.
    char fornecedor[50];    // Nome do fornecedor.
} Produto;

// Prototipos das funcoes utilizadas.
void criarArquivo();
int carregarProdutos(Produto *lista);
int salvarProdutos(Produto *lista, int quantidade);
void listarProdutos(Produto *lista, int quantidade);
void inserirProduto(Produto *lista, int *quantidade);
void alterarProduto(Produto *lista, int quantidade);
void excluirProduto(Produto *lista, int *quantidade);
void buscarPorNome(Produto *lista, int quantidade);
void buscarPorCategoria(Produto *lista, int quantidade);
void ordenarProdutos(Produto *lista, int quantidade, int criterio);
void exportarCSV(Produto *lista, int quantidade);
int gerarID(Produto *lista, int quantidade);
int compararTexto(const char *a, const char *b);
int contemTexto(const char *texto, const char *busca);
int buscarID(Produto *lista, int quantidade, int id);
int nomeDuplicado(Produto *lista, int quantidade, const char *nome);
void lerTexto(char *destino, int tamanho, const char *mensagem);
int lerInteiro(const char *mensagem);
float lerPreco(const char *mensagem);
void exibirTabela(Produto *lista, int quantidade);
void escreverCampoCSV(FILE *arquivo, const char *texto);

// Compara dois textos sem diferenciar letras maiusculas e minusculas.
int compararTexto(const char *a, const char *b) {

    // Percorre os dois textos simultaneamente.
    while (*a && *b) {

        // Converte os caracteres para minusculas.
        int ca = tolower((unsigned char)*a);
        int cb = tolower((unsigned char)*b);

        // Verifica se os caracteres sao diferentes.
        if (ca != cb) {
            return ca - cb;
        }

        // Avanca para o proximo caractere.
        a++;
        b++;
    }

    // Retorna a diferenca entre os caracteres finais.
    return tolower((unsigned char)*a) -
           tolower((unsigned char)*b);
}

// Verifica se um texto contem outro texto.
int contemTexto(const char *texto, const char *busca) {

    // Percorre todas as posicoes possiveis do texto.
    while (*texto) {

        // Compara os caracteres sem diferenciar maiusculas.
        if (tolower((unsigned char)*texto) ==
            tolower((unsigned char)*busca)) {

            const char *a = texto;
            const char *b = busca;

            // Compara os caracteres seguintes.
            while (*a && *b &&
                   tolower((unsigned char)*a) ==
                   tolower((unsigned char)*b)) {
                a++;
                b++;
            }

            // Retorna verdadeiro quando encontrou o texto.
            if (*b == '\0') {
                return 1;
            }
        }

        // Avanca no texto principal.
        texto++;
    }

    // Retorna falso quando nao encontrou.
    return 0;
}

// Le um texto digitado pelo usuario.
void lerTexto(char *destino, int tamanho, const char *mensagem) {

    // Variavel auxiliar para controlar a entrada.
    int valido = 0;

    do {

        // Exibe a mensagem para o usuario.
        printf("%s", mensagem);

        // Recebe o texto digitado.
        if (fgets(destino, tamanho, stdin) == NULL) {
            destino[0] = '\0';
            continue;
        }

        // Remove a quebra de linha.
        destino[strcspn(destino, "\n")] = '\0';

        // Verifica se o campo esta vazio.
        if (strlen(destino) == 0) {
            printf("O campo nao pode ficar vazio!\n");
            continue;
        }

        // Verifica se existe o separador do arquivo.
        if (strchr(destino, '|') != NULL) {
            printf("Nao utilize o caractere | no texto!\n");
            continue;
        }

        valido = 1;

    } while (!valido);
}

// Le um numero inteiro valido.
int lerInteiro(const char *mensagem) {

    char entrada[100];
    char *fim;
    long valor;

    while (1) {

        printf("%s", mensagem);

        if (fgets(entrada, sizeof(entrada), stdin) == NULL) {
            continue;
        }

        valor = strtol(entrada, &fim, 10);

        // Ignora espacos depois do numero.
        while (isspace((unsigned char)*fim)) {
            fim++;
        }

        // Verifica se a entrada contem um inteiro valido.
        if (fim == entrada || *fim != '\0' && *fim != '\n') {
            printf("Digite um numero inteiro valido!\n");
            continue;
        }

        if (valor < 0 || valor > 2147483647L) {
            printf("Valor fora do intervalo permitido!\n");
            continue;
        }

        return (int)valor;
    }
}

// Le um preco valido.
float lerPreco(const char *mensagem) {

    char entrada[100];
    char *fim;
    float valor;

    while (1) {

        printf("%s", mensagem);

        if (fgets(entrada, sizeof(entrada), stdin) == NULL) {
            continue;
        }

        // Converte o texto para numero decimal.
        valor = strtof(entrada, &fim);

        while (isspace((unsigned char)*fim)) {
            fim++;
        }

        // Verifica se a conversao foi realizada corretamente.
        if (fim == entrada || (*fim != '\0' && *fim != '\n')) {
            printf("Digite um preco valido!\n");
            continue;
        }

        // Impede valores negativos ou iguais a zero.
        if (valor <= 0) {
            printf("O preco deve ser maior que zero!\n");
            continue;
        }

        return valor;
    }
}

// Cria o arquivo de produtos com dados iniciais.
void criarArquivo() {

    FILE *arquivo = fopen("produtos.txt", "r");

    // Verifica se o arquivo ja existe.
    if (arquivo != NULL) {
        fclose(arquivo);
        printf("Arquivo de produtos encontrado!\n");
        return;
    }

    // Cria o arquivo caso ainda nao exista.
    arquivo = fopen("produtos.txt", "w");

    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo!\n");
        return;
    }

    // Insere os produtos iniciais da cafeteria.
    fprintf(arquivo, "1|Cafe Expresso|Bebidas quentes|8.00|50|Cafe pele\n");
    fprintf(arquivo, "2|Cappuccino|Bebidas quentes|12.50|30|Cafe Especial\n");
    fprintf(arquivo, "3|Pao de Queijo|Salgados|6.00|40|Sabor especial\n");
    fprintf(arquivo, "4|Bolo de Cenoura|Doces|9.50|20|Confeitaria luamar\n");

    // Fecha o arquivo.
    fclose(arquivo);

    printf("Arquivo criado com sucesso!\n");
}

// Carrega os produtos armazenados no arquivo.
int carregarProdutos(Produto *lista) {

    FILE *arquivo = fopen("produtos.txt", "r");

    char linha[TAM_LINHA];
    int quantidade = 0;

    // Verifica se o arquivo foi aberto.
    if (arquivo == NULL) {
        return 0;
    }

    // Percorre cada linha do arquivo.
    while (fgets(linha, sizeof(linha), arquivo) != NULL &&
           quantidade < MAX_PRODUTOS) {

        // Converte os campos da linha para a estrutura.
        if (sscanf(linha,
            "%d|%49[^|]|%39[^|]|%f|%d|%49[^\n]",
            &lista[quantidade].id,
            lista[quantidade].produto,
            lista[quantidade].categoria,
            &lista[quantidade].preco,
            &lista[quantidade].quantidade,
            lista[quantidade].fornecedor) == 6) {

            // Avanca para a proxima posicao do vetor.
            quantidade++;
        }
    }

    // Fecha o arquivo depois da leitura.
    fclose(arquivo);

    // Retorna a quantidade de produtos carregados.
    return quantidade;
}

// Salva os produtos utilizando um arquivo temporario.
int salvarProdutos(Produto *lista, int quantidade) {

    FILE *temporario = fopen("produtos_temp.txt", "w");

    // Verifica se foi possivel criar o arquivo temporario.
    if (temporario == NULL) {
        printf("Erro ao criar arquivo temporario!\n");
        return 0;
    }

    // Percorre o vetor de produtos.
    for (int i = 0; i < quantidade; i++) {

        // Grava todos os campos no arquivo temporario.
        fprintf(temporario, "%d|%s|%s|%.2f|%d|%s\n",
            lista[i].id,
            lista[i].produto,
            lista[i].categoria,
            lista[i].preco,
            lista[i].quantidade,
            lista[i].fornecedor);
    }

    // Fecha o arquivo temporario.
    fclose(temporario);

    // Substitui o arquivo original pelo temporario.
    // A remocao anterior permite trabalhar tambem em Windows.
    if (remove("produtos.txt") != 0) {
        FILE *teste = fopen("produtos.txt", "r");

        if (teste != NULL) {
            fclose(teste);
            remove("produtos_temp.txt");
            printf("Erro ao substituir o arquivo original!\n");
            return 0;
        }
    }

    // Renomeia o arquivo temporario.
    if (rename("produtos_temp.txt", "produtos.txt") != 0) {
        printf("Erro ao renomear o arquivo temporario!\n");
        return 0;
    }

    printf("Dados salvos com sucesso!\n");

    return 1;
}

// Gera um novo ID automaticamente.
int gerarID(Produto *lista, int quantidade) {

    int maiorID = 0;

    // Percorre todos os produtos cadastrados.
    for (int i = 0; i < quantidade; i++) {

        // Identifica o maior ID existente.
        if (lista[i].id > maiorID) {
            maiorID = lista[i].id;
        }
    }

    // Retorna o proximo identificador.
    return maiorID + 1;
}

// Verifica se determinado ID ja existe.
int buscarID(Produto *lista, int quantidade, int id) {

    for (int i = 0; i < quantidade; i++) {

        if (lista[i].id == id) {
            return i;
        }
    }

    return -1;
}

// Verifica se o nome do produto ja esta cadastrado.
int nomeDuplicado(Produto *lista, int quantidade, const char *nome) {

    for (int i = 0; i < quantidade; i++) {

        // Compara os nomes ignorando maiusculas e minusculas.
        if (compararTexto(lista[i].produto, nome) == 0) {
            return 1;
        }
    }

    return 0;
}

// Exibe os produtos em formato de tabela.
void exibirTabela(Produto *lista, int quantidade) {

    // Verifica se existem produtos cadastrados.
    if (quantidade == 0) {
        printf("\nNenhum produto cadastrado!\n");
        return;
    }

    printf("\n");
    printf("---------------------------------------------------------------------------------------------------------------\n");

    printf("%-5s %-25s %-22s %-12s %-12s %-20s\n",
        "ID", "PRODUTO", "CATEGORIA", "PRECO", "QUANTIDADE", "FORNECEDOR");

    printf("---------------------------------------------------------------------------------------------------------------\n");

    // Percorre o vetor para exibir os registros.
    for (int i = 0; i < quantidade; i++) {

        printf("%-5d %-25.25s %-22.22s R$ %-9.2f %-12d %-20.20s\n",
            lista[i].id,
            lista[i].produto,
            lista[i].categoria,
            lista[i].preco,
            lista[i].quantidade,
            lista[i].fornecedor);
    }

    printf("---------------------------------------------------------------------------------------------------------------\n");
}

// Lista todos os produtos cadastrados.
void listarProdutos(Produto *lista, int quantidade) {

    printf("\n========== PRODUTOS DA CAFETERIA ==========\n");

    // Chama a funcao responsavel pela exibicao.
    exibirTabela(lista, quantidade);
}

// Insere um novo produto no cadastro.
void inserirProduto(Produto *lista, int *quantidade) {

    // Verifica se existe espaco no vetor.
    if (*quantidade >= MAX_PRODUTOS) {
        printf("Limite de produtos atingido!\n");
        return;
    }

    // Cria uma estrutura auxiliar.
    Produto novo;

    // Gera o ID automaticamente.
    novo.id = gerarID(lista, *quantidade);

    printf("\n========== NOVO PRODUTO ==========\n");

    printf("ID gerado automaticamente: %d\n", novo.id);

    // Recebe o nome e verifica duplicatas.
    while (1) {

        lerTexto(novo.produto, sizeof(novo.produto),
                 "Nome do produto: ");

        if (nomeDuplicado(lista, *quantidade, novo.produto)) {
            printf("Esse produto ja esta cadastrado!\n");
        } else {
            break;
        }
    }

    // Recebe as demais informacoes.
    lerTexto(novo.categoria, sizeof(novo.categoria),
             "Categoria: ");

    novo.preco = lerPreco("Preco: R$ ");

    novo.quantidade = lerInteiro("Quantidade em estoque: ");

    lerTexto(novo.fornecedor, sizeof(novo.fornecedor),
             "Fornecedor: ");

    // Verifica novamente se o ID ja existe.
    if (buscarID(lista, *quantidade, novo.id) != -1) {
        printf("Erro: ID duplicado!\n");
        return;
    }

    // Adiciona o produto na proxima posicao do vetor.
    lista[*quantidade] = novo;

    // Atualiza a quantidade de produtos.
    (*quantidade)++;

    // Salva as alteracoes no arquivo.
    if (!salvarProdutos(lista, *quantidade)) {
        (*quantidade)--;
        return;
    }

    printf("Produto cadastrado com sucesso!\n");
}

// Altera os dados de um produto.
void alterarProduto(Produto *lista, int quantidade) {

    int id;

    printf("\n========== ALTERAR PRODUTO ==========\n");

    // Solicita o ID do produto.
    id = lerInteiro("Informe o ID do produto: ");

    // Localiza a posicao do produto no vetor.
    int posicao = buscarID(lista, quantidade, id);

    // Verifica se o produto foi encontrado.
    if (posicao == -1) {
        printf("Produto nao encontrado!\n");
        return;
    }

    // Exibe o cadastro atual.
    exibirTabela(&lista[posicao], 1);

    // Estrutura auxiliar para receber as alteracoes.
    Produto novo = lista[posicao];

    printf("\nDigite as novas informacoes:\n");

    // Recebe o novo nome.
    while (1) {

        lerTexto(novo.produto, sizeof(novo.produto),
                 "Novo nome: ");

        // Permite manter o nome do proprio produto,
        // mas impede repetir o nome de outro cadastro.
        int duplicado = 0;

        for (int i = 0; i < quantidade; i++) {

            if (i != posicao &&
                compararTexto(lista[i].produto, novo.produto) == 0) {
                duplicado = 1;
                break;
            }
        }

        if (!duplicado) {
            break;
        }

        printf("Ja existe outro produto com esse nome!\n");
    }

    // Recebe os novos campos.
    lerTexto(novo.categoria, sizeof(novo.categoria),
             "Nova categoria: ");

    novo.preco = lerPreco("Novo preco: R$ ");

    novo.quantidade = lerInteiro("Nova quantidade: ");

    lerTexto(novo.fornecedor, sizeof(novo.fornecedor),
             "Novo fornecedor: ");

    // Atualiza os dados na estrutura.
    lista[posicao] = novo;

    // Salva utilizando arquivo temporario.
    if (!salvarProdutos(lista, quantidade)) {
        printf("Nao foi possivel confirmar a alteracao!\n");
        return;
    }

    printf("Produto alterado com sucesso!\n");
}

// Exclui um produto do cadastro.
void excluirProduto(Produto *lista, int *quantidade) {

    int id;

    printf("\n========== EXCLUIR PRODUTO ==========\n");

    // Solicita o identificador do produto.
    id = lerInteiro("Informe o ID: ");

    // Localiza o produto.
    int posicao = buscarID(lista, *quantidade, id);

    // Verifica se o produto existe.
    if (posicao == -1) {
        printf("Produto nao encontrado!\n");
        return;
    }

    // Exibe os dados que serao excluidos.
    exibirTabela(&lista[posicao], 1);

    // Solicita confirmacao.
    printf("Confirma a exclusao? (1 = Sim / 0 = Nao): ");

    int confirmar = lerInteiro("");

    if (confirmar != 1) {
        printf("Exclusao cancelada!\n");
        return;
    }

    // Desloca os elementos posteriores uma posicao.
    for (int i = posicao; i < *quantidade - 1; i++) {
        lista[i] = lista[i + 1];
    }

    // Diminui a quantidade de registros.
    (*quantidade)--;

    // Atualiza o arquivo por meio de arquivo temporario.
    if (!salvarProdutos(lista, *quantidade)) {
        printf("Nao foi possivel confirmar a exclusao!\n");
        return;
    }

    printf("Produto excluido com sucesso!\n");
}

// Busca produtos pelo nome.
void buscarPorNome(Produto *lista, int quantidade) {

    char nome[50];
    int encontrados = 0;

    printf("\n========== BUSCAR POR NOME ==========\n");

    // Recebe o nome ou parte do nome.
    lerTexto(nome, sizeof(nome), "Digite o nome: ");

    // Percorre os produtos cadastrados.
    for (int i = 0; i < quantidade; i++) {

        // Pesquisa ignorando maiusculas e minusculas.
        if (contemTexto(lista[i].produto, nome)) {

            if (encontrados == 0) {
                printf("\nResultados encontrados:\n");
            }

            exibirTabela(&lista[i], 1);

            encontrados++;
        }
    }

    // Informa quando nao existem resultados.
    if (encontrados == 0) {
        printf("Nenhum produto encontrado!\n");
    }
}

// Busca produtos pela categoria.
void buscarPorCategoria(Produto *lista, int quantidade) {

    char categoria[40];
    int encontrados = 0;

    printf("\n========== BUSCAR POR CATEGORIA ==========\n");

    // Recebe a categoria desejada.
    lerTexto(categoria, sizeof(categoria), "Digite a categoria: ");

    // Percorre os produtos.
    for (int i = 0; i < quantidade; i++) {

        // Compara a categoria sem diferenciar maiusculas.
        if (contemTexto(lista[i].categoria, categoria)) {

            exibirTabela(&lista[i], 1);

            encontrados++;
        }
    }

    if (encontrados == 0) {
        printf("Nenhum produto encontrado nessa categoria!\n");
    }
}

// Ordena os produtos utilizando Bubble Sort.
void ordenarProdutos(Produto *lista, int quantidade, int criterio) {

    Produto auxiliar;

    // Percorre o vetor realizando comparacoes.
    for (int i = 0; i < quantidade - 1; i++) {

        for (int j = 0; j < quantidade - i - 1; j++) {

            int trocar = 0;

            // Criterio 1: Nome em ordem crescente.
            if (criterio == 1 &&
                compararTexto(lista[j].produto,
                              lista[j + 1].produto) > 0) {
                trocar = 1;
            }

            // Criterio 2: Nome em ordem decrescente.
            if (criterio == 2 &&
                compararTexto(lista[j].produto,
                              lista[j + 1].produto) < 0) {
                trocar = 1;
            }

            // Criterio 3: Preco crescente.
            if (criterio == 3 &&
                lista[j].preco > lista[j + 1].preco) {
                trocar = 1;
            }

            // Criterio 4: Preco decrescente.
            if (criterio == 4 &&
                lista[j].preco < lista[j + 1].preco) {
                trocar = 1;
            }

            // Realiza a troca utilizando uma variavel auxiliar.
            if (trocar) {

                auxiliar = lista[j];

                lista[j] = lista[j + 1];

                lista[j + 1] = auxiliar;
            }
        }
    }

    // Exibe os produtos ordenados.
    // A ordenacao acontece somente na memoria.
    // O arquivo original permanece inalterado.
    exibirTabela(lista, quantidade);
}

// Escreve um campo CSV entre aspas.
void escreverCampoCSV(FILE *arquivo, const char *texto) {

    // Abre as aspas do campo.
    fputc('"', arquivo);

    // Percorre cada caractere.
    while (*texto) {

        // Duplica aspas internas conforme o padrao CSV.
        if (*texto == '"') {
            fputc('"', arquivo);
        }

        fputc(*texto, arquivo);

        texto++;
    }

    // Fecha as aspas.
    fputc('"', arquivo);
}

// Exporta os produtos para um arquivo CSV.
void exportarCSV(Produto *lista, int quantidade) {

    FILE *arquivo = fopen("produtos.csv", "w");

    // Verifica se o arquivo pode ser criado.
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo CSV!\n");
        return;
    }

    // Cria o cabecalho da planilha.
    fprintf(arquivo,
        "ID,Produto,Categoria,Preco,Quantidade,Fornecedor\n");

    // Percorre todos os registros.
    for (int i = 0; i < quantidade; i++) {

        // Escreve o ID.
        fprintf(arquivo, "%d,", lista[i].id);

        // Escreve os campos de texto entre aspas.
        escreverCampoCSV(arquivo, lista[i].produto);
        fprintf(arquivo, ",");

        escreverCampoCSV(arquivo, lista[i].categoria);
        fprintf(arquivo, ",");

        // Escreve o preco.
        fprintf(arquivo, "%.2f,", lista[i].preco);

        // Escreve a quantidade.
        fprintf(arquivo, "%d,", lista[i].quantidade);

        escreverCampoCSV(arquivo, lista[i].fornecedor);

        // Finaliza o registro.
        fprintf(arquivo, "\n");
    }

    // Fecha o arquivo CSV.
    fclose(arquivo);
    
    printf("\nConteudo do arquivo CSV:\n");

       FILE *teste = fopen("produtos.csv", "r");

    if (teste != NULL) {
    char linha[250];

    while (fgets(linha, sizeof(linha), teste) != NULL) {
        printf("%s", linha);
    }

    fclose(teste);
}

    printf("Arquivo produtos.csv exportado com sucesso!\n");
    
      FILE *verificar = fopen("produtos.csv", "r");

    if (verificar != NULL) {
    printf("Confirmado: arquivo encontrado!\n");
    fclose(verificar);
} else {
    printf("Erro: arquivo nao encontrado!\n");
}
}

// Funcao principal do programa.
int main() {

    // Declara o vetor de estruturas.
    Produto lista[MAX_PRODUTOS];

    // Armazena a quantidade de produtos.
    int quantidade;

    // Armazena a opcao selecionada.
    int opcao;

    // Cria o arquivo caso ainda nao exista.
    criarArquivo();

    // Carrega os registros armazenados.
    quantidade = carregarProdutos(lista);

    // Repete o menu ate o usuario escolher sair.
    do {

        printf("\n");
        printf("============================================\n");
        printf("       SISTEMA DE GERENCIAMENTO             \n");
        printf("          CAFETERIA ELSHADDAY               \n");
        printf("============================================\n");

        printf("1  - Criar/verificar arquivo\n");
        printf("2  - Listar produtos\n");
        printf("3  - Inserir produto\n");
        printf("4  - Alterar produto\n");
        printf("5  - Excluir produto\n");
        printf("6  - Buscar por nome\n");
        printf("7  - Buscar por categoria\n");
        printf("8  - Ordenar nome (A-Z)\n");
        printf("9  - Ordenar nome (Z-A)\n");
        printf("10 - Ordenar preco (menor para maior)\n");
        printf("11 - Ordenar preco (maior para menor)\n");
        printf("12 - Exportar para CSV\n");
        printf("0  - Sair\n");

        printf("============================================\n");

        // Recebe a opcao do usuario.
        opcao = lerInteiro("Escolha uma opcao: ");

        // Executa a funcionalidade selecionada.
        switch (opcao) {

            case 1:
                criarArquivo();
                break;

            case 2:
                listarProdutos(lista, quantidade);
                break;

            case 3:
                inserirProduto(lista, &quantidade);
                break;

            case 4:
                alterarProduto(lista, quantidade);
                break;

            case 5:
                excluirProduto(lista, &quantidade);
                break;

            case 6:
                buscarPorNome(lista, quantidade);
                break;

            case 7:
                buscarPorCategoria(lista, quantidade);
                break;

            case 8:
                ordenarProdutos(lista, quantidade, 1);
                break;

            case 9:
                ordenarProdutos(lista, quantidade, 2);
                break;

            case 10:
                ordenarProdutos(lista, quantidade, 3);
                break;

            case 11:
                ordenarProdutos(lista, quantidade, 4);
                break;

            case 12:
                exportarCSV(lista, quantidade);
                break;

            case 0:
                printf("Sistema encerrado!\n");
                break;

            default:
                printf("Opcao invalida! Tente novamente.\n");
        }

    } while (opcao != 0);

    // Finaliza a execucao.
    return 0;
}

