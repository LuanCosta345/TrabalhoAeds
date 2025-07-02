# TrabalhoAeds

Trabalho da Disciplina de Algoritimos e Estruturas de Dados do 1 Semestre de Engenharia de Software da Puc Minas

📁 Estrutura de Pastas  
Cada entidade do projeto possui sua própria pasta organizada da seguinte forma:

    PastaNome_Objeto/
    ├── ObjetoClass.cpp      -> Definição da classe do objeto
    └── CrudObjeto.cpp       -> Implementação das operações CRUD para o objeto

Sobre a Disciplina
Esta disciplina envolve conceitos básicos de lógica de programação, estruturas de decisão e repetição, funções, manipulação de ponteiros, arrays, strings e registros, que são essenciais para a formação em Engenharia de Software.

Contribuições
Este projeto tem finalidade acadêmica e uso pessoal, porém contribuições, sugestões e melhorias são sempre muito bem-vindas!

Desenvolvido por {nome}, {nome}, {nome}


# Sistema de Gerenciamento de Locais

## Visão Geral
Este sistema implementa um CRUD (Create, Read, Update, Delete) completo para gerenciamento de locais geográficos, atendendo aos requisitos específicos:

- ✅ **Armazenamento em arquivo binário** usando bibliotecas C (`fopen`, `fwrite`, `fread`)
- ✅ **Sem uso do tipo `string`** - utiliza arrays de `char`
- ✅ **Sistema de ID único automático** para cada local
- ✅ **Persistência de dados** entre execuções do programa

## Estrutura de Arquivos

### LocaisClass.cpp
Define a classe `Local` com os seguintes atributos:
- `int id`: Identificador único do local
- `char nome[MAX_NOME]`: Nome do local (máximo 100 caracteres)
- `float coordenadaX`: Coordenada X do local
- `float coordenadaY`: Coordenada Y do local

### CrudLocais.cpp
Implementa todas as operações CRUD e funcionalidades auxiliares:

## Funcionalidades Implementadas

### 1. **Sistema de ID Automático**
- Cada local recebe um ID único sequencial
- IDs são controlados através do arquivo `contador_id.dat`
- Garante que não haverá conflitos de ID mesmo após exclusões

### 2. **Armazenamento em Arquivo Binário**
- **Arquivo principal**: `locais.dat` - armazena os dados dos locais em formato binário
- **Arquivo de controle**: `contador_id.dat` - armazena o próximo ID disponível
- Utiliza funções C puras: `fopen()`, `fwrite()`, `fread()`, `fclose()`

### 3. **Operações CRUD**

#### **CREATE - Cadastrar Local**
- Solicita nome e coordenadas
- Verifica se já existe um local com o mesmo nome
- Gera ID automático sequencial
- Salva no arquivo binário

#### **READ - Listar/Buscar Locais**
- **Listar todos**: Exibe todos os locais cadastrados com ID, nome e coordenadas
- **Buscar por ID**: Permite localizar um local específico pelo seu ID único

#### **UPDATE - Atualizar Local**
- Busca local pelo ID
- Permite alterar nome e coordenadas
- Verifica conflitos de nome com outros locais
- Atualiza arquivo binário

#### **DELETE - Deletar Local**
- Busca local pelo ID
- Exibe dados do local para confirmação
- Solicita confirmação antes da exclusão
- Remove do arquivo reorganizando os dados

### 4. **Validações Implementadas**
- ✅ Verificação de nomes duplicados
- ✅ Confirmação antes de exclusão
- ✅ Tratamento de IDs inexistentes
- ✅ Limpeza de buffer de entrada
- ✅ Remoção de quebras de linha em strings

### 5. **Gerenciamento de Memória**
- Uso de arrays estáticos para evitar vazamentos de memória
- Limite definido de 1000 locais por execução
- Sem uso de alocação dinâmica desnecessária

## Como Compilar e Executar

```bash
# Compilar
g++ -o locais.exe CrudLocais.cpp

# Executar
./locais.exe
```

## Menu de Operações
```
=== Menu Locais ===
1. Cadastrar Local
2. Listar Locais
3. Buscar Local por ID
4. Atualizar Local
5. Deletar Local
0. Sair
```

## Arquivos Gerados pelo Sistema
- `locais.dat`: Dados dos locais em formato binário
- `contador_id.dat`: Próximo ID disponível
- `locais.exe`: Executável compilado

## Requisitos Atendidos
- [x] Armazenamento em arquivo binário usando bibliotecas C
- [x] Não utilização do tipo `string`
- [x] Sistema de ID único para locais
- [x] Operações CRUD completas
- [x] Persistência de dados
- [x] Validações e tratamento de erros

## Observações Técnicas
- O programa utiliza apenas bibliotecas C padrão
- Arrays de `char` são utilizados ao invés de `string`
- Arquivos binários garantem eficiência no armazenamento
- IDs sequenciais facilitam a identificação e busca
- Sistema robusto com validações adequadas 
