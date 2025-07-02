#include "LocaisClass.cpp"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <stdbool.h>

const char* ARQUIVO_LOCAIS = "locais.dat";
const char* ARQUIVO_CONTADOR = "contador_id.dat";

// Função para obter próximo ID disponível
int obterProximoId() {
    FILE* arquivo = fopen(ARQUIVO_CONTADOR, "rb");
    int proximoId = 1;
    
    if (arquivo != NULL) {
        fread(&proximoId, sizeof(int), 1, arquivo);
        fclose(arquivo);
    }
    
    return proximoId;
}

// Função para salvar próximo ID
void salvarProximoId(int id) {
    FILE* arquivo = fopen(ARQUIVO_CONTADOR, "wb");
    if (arquivo != NULL) {
        fwrite(&id, sizeof(int), 1, arquivo);
        fclose(arquivo);
    }
}

// Função para salvar um local no arquivo binário
void salvarLocal(const Local& local) {
    FILE* arquivo = fopen(ARQUIVO_LOCAIS, "ab");
    if (arquivo != NULL) {
        fwrite(&local, sizeof(Local), 1, arquivo);
        fclose(arquivo);
    } else {
        printf("Erro ao abrir arquivo para escrita!\n");
    }
}

// Função para carregar todos os locais do arquivo
int carregarLocais(Local locais[], int maxLocais) {
    FILE* arquivo = fopen(ARQUIVO_LOCAIS, "rb");
    int count = 0;
    
    if (arquivo != NULL) {
        while (count < maxLocais && fread(&locais[count], sizeof(Local), 1, arquivo) == 1) {
            count++;
        }
        fclose(arquivo);
    }
    
    return count;
}

// Função para reescrever todo o arquivo com os locais atualizados
void salvarTodosLocais(Local locais[], int quantidade) {
    FILE* arquivo = fopen(ARQUIVO_LOCAIS, "wb");
    if (arquivo != NULL) {
        fwrite(locais, sizeof(Local), quantidade, arquivo);
        fclose(arquivo);
    } else {
        printf("Erro ao salvar locais!\n");
    }
}

// Função para verificar se um nome já existe
bool nomeJaExiste(Local locais[], int quantidade, const char* nome) {
    for (int i = 0; i < quantidade; i++) {
        if (strcmp(locais[i].getNome(), nome) == 0) {
            return true;
        }
    }
    return false;
}

// Função para buscar local por ID
int buscarLocalPorId(Local locais[], int quantidade, int id) {
    for (int i = 0; i < quantidade; i++) {
        if (locais[i].getId() == id) {
            return i;
        }
    }
    return -1;
}

void criarLocal() {
    const int MAX_LOCAIS = 1000;
    Local locais[MAX_LOCAIS];
    int quantidade = carregarLocais(locais, MAX_LOCAIS);
    
    char nome[MAX_NOME];
    float x, y;
    
    printf("Digite o nome do local: ");
    fflush(stdout);
    getchar(); // Limpar buffer
    fgets(nome, MAX_NOME, stdin);
    
    // Remover quebra de linha se existir
    size_t len = strlen(nome);
    if (len > 0 && nome[len-1] == '\n') {
        nome[len-1] = '\0';
    }
    
    printf("Digite a coordenada X: ");
    scanf("%f", &x);
    
    printf("Digite a coordenada Y: ");
    scanf("%f", &y);
    
    // Verificar se nome já existe
    if (nomeJaExiste(locais, quantidade, nome)) {
        printf("Local com este nome já cadastrado!\n");
        return;
    }
    
    // Obter próximo ID e criar local
    int novoId = obterProximoId();
    Local novoLocal(novoId, nome, x, y);
    
    // Salvar local
    salvarLocal(novoLocal);
    
    // Atualizar contador de ID
    salvarProximoId(novoId + 1);
    
    printf("Local cadastrado com sucesso! ID: %d\n", novoId);
}

void listarLocais() {
    const int MAX_LOCAIS = 1000;
    Local locais[MAX_LOCAIS];
    int quantidade = carregarLocais(locais, MAX_LOCAIS);
    
    if (quantidade == 0) {
        printf("Nenhum local cadastrado.\n");
        return;
    }
    
    printf("\n=== Lista de Locais ===\n");
    for (int i = 0; i < quantidade; i++) {
        locais[i].exibir();
    }
    printf("Total: %d locais\n", quantidade);
}

void buscarLocalPorIdMenu() {
    const int MAX_LOCAIS = 1000;
    Local locais[MAX_LOCAIS];
    int quantidade = carregarLocais(locais, MAX_LOCAIS);
    
    int id;
    printf("Digite o ID do local: ");
    scanf("%d", &id);
    
    int indice = buscarLocalPorId(locais, quantidade, id);
    if (indice != -1) {
        printf("\nLocal encontrado:\n");
        locais[indice].exibir();
    } else {
        printf("Local com ID %d não encontrado!\n", id);
    }
}

void atualizarLocal() {
    const int MAX_LOCAIS = 1000;
    Local locais[MAX_LOCAIS];
    int quantidade = carregarLocais(locais, MAX_LOCAIS);
    
    int id;
    printf("Digite o ID do local a ser atualizado: ");
    scanf("%d", &id);
    
    int indice = buscarLocalPorId(locais, quantidade, id);
    if (indice != -1) {
        printf("Local atual:\n");
        locais[indice].exibir();
        
        char novoNome[MAX_NOME];
        float x, y;
        
        printf("\nDigite o novo nome do local: ");
        fflush(stdout);
        getchar(); // Limpar buffer
        fgets(novoNome, MAX_NOME, stdin);
        
        // Remover quebra de linha se existir
        size_t len = strlen(novoNome);
        if (len > 0 && novoNome[len-1] == '\n') {
            novoNome[len-1] = '\0';
        }
        
        printf("Digite a nova coordenada X: ");
        scanf("%f", &x);
        
        printf("Digite a nova coordenada Y: ");
        scanf("%f", &y);
        
        // Verificar se o novo nome já existe (exceto no local atual)
        bool nomeConflito = false;
        for (int i = 0; i < quantidade; i++) {
            if (i != indice && strcmp(locais[i].getNome(), novoNome) == 0) {
                nomeConflito = true;
                break;
            }
        }
        
        if (nomeConflito) {
            printf("Já existe outro local com este nome!\n");
            return;
        }
        
        // Atualizar local
        locais[indice].setNome(novoNome);
        locais[indice].setCoordenadaX(x);
        locais[indice].setCoordenadaY(y);
        
        // Salvar todas as alterações
        salvarTodosLocais(locais, quantidade);
        
        printf("Local atualizado com sucesso!\n");
    } else {
        printf("Local com ID %d não encontrado!\n", id);
    }
}

void deletarLocal() {
    const int MAX_LOCAIS = 1000;
    Local locais[MAX_LOCAIS];
    int quantidade = carregarLocais(locais, MAX_LOCAIS);
    
    int id;
    printf("Digite o ID do local a ser deletado: ");
    scanf("%d", &id);
    
    int indice = buscarLocalPorId(locais, quantidade, id);
    if (indice != -1) {
        printf("Local a ser deletado:\n");
        locais[indice].exibir();
        
        char confirmacao;
        printf("Confirma a exclusão? (s/n): ");
        scanf(" %c", &confirmacao);
        
        if (confirmacao == 's' || confirmacao == 'S') {
            // Remover local do array (mover elementos para a esquerda)
            for (int i = indice; i < quantidade - 1; i++) {
                locais[i] = locais[i + 1];
            }
            quantidade--;
            
            // Salvar array atualizado
            salvarTodosLocais(locais, quantidade);
            
            printf("Local deletado com sucesso!\n");
        } else {
            printf("Operação cancelada.\n");
        }
    } else {
        printf("Local com ID %d não encontrado!\n", id);
    }
}

int main() {
    int opcao;
    do {
        printf("\n=== Menu Locais ===\n");
        printf("1. Cadastrar Local\n");
        printf("2. Listar Locais\n");
        printf("3. Buscar Local por ID\n");
        printf("4. Atualizar Local\n");
        printf("5. Deletar Local\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1: criarLocal(); break;
            case 2: listarLocais(); break;
            case 3: buscarLocalPorIdMenu(); break;
            case 4: atualizarLocal(); break;
            case 5: deletarLocal(); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opção inválida!\n");
        }
    } while (opcao != 0);
    
    return 0;
} 