/*
 * NOME: Rodrigo Seiji Piubeli Hirao
 * RA: 186837
 * TURMA: R
 */

#include <stdio.h>
#include <string.h>


#define NUM_USER_TYPES 2
#define MAX_STRING_SIZE 60
#define MAX_CONTATOS 10

#define INSERIR 1
#define EXCLUIR 2
#define ALTERAR 3
#define BUSCAR 4
#define LISTAR_PESSOAIS 5
#define LISTAR_PROFISSIONAIS 6
#define LISTAR_TODOS 7
#define SAIR 0

/*
 * String
 */
typedef char string[MAX_STRING_SIZE];

/*
 * Listas
 */

string list_user_name[NUM_USER_TYPES][MAX_CONTATOS];
long int list_user_cpf[NUM_USER_TYPES][MAX_CONTATOS];
string list_user_address[NUM_USER_TYPES][MAX_CONTATOS];
long int list_user_tel[NUM_USER_TYPES][MAX_CONTATOS];
long int list_user_cell[NUM_USER_TYPES][MAX_CONTATOS];
short list_size[NUM_USER_TYPES];

/*
 * Inserir usuário
 *
 * @entrada
 * * int user_type - tipo do usuário
 * * * 1) pessoal
 * * * 2) profissional
 * * string user_name - nome do usuário
 * * int user_cpf - cpf do usuário
 * * string user_address - endereço do usuário
 * * int user_tel - telefone do usuário
 * * int user_cell - celular do usuário
 * 
 * @saida
 * * int result - posição do usuário inserido, -1 se não pode ser inserido
 */
int create(short int user_type, string user_name, long int user_cpf, string user_address, long int user_tel, long int user_cell);

/*
 * Excluir usuário
 *
 * @entrada
 * * int user_type - tipo do usuário
 * * * 1) pessoal
 * * * 2) profissional
 * * string user_name - nome do usuário
 * 
 * @saida
 * * int result - posição do usuário excluido, -1 se não pode ser excluido
 */
int delete(short int user_type, string user_name);

/*
 * Alterar usuário a partir do $user_name e do $user_type
 *
 * @entrada
 * * int user_type - tipo do usuário
 * * * 1) pessoal
 * * * 2) profissional
 * * string user_name - nome do usuário
 * * int user_cpf - cpf do usuário
 * * string user_address - endereço do usuário
 * * int user_tel - telefone do usuário
 * * int user_cell - celular do usuário
 * 
 * @saida
 * * int result - posição do usuário alterado, -1 se não pode ser alterado ou não foi encontrado
 */
int update(short int user_type, string user_name, long int user_cpf, string user_address, long int  user_tel, long int user_cell);

/*
 * Buscar usuário a partir do $user_name e do $user_type
 *
 * @entrada
 * * int user_type - tipo do usuário
 * * * 1) pessoal
 * * * 2) profissional
 * * string user_name - nome do usuário
 * * int user_cpf - cpf do usuário
 * * string user_address - endereço do usuário
 * * int user_tel - telefone do usuário
 * * int user_cell - celular do usuário
 * 
 * @saida
 * * int result - posição do usuário encontrado, -1 se nada foi encontrado
 */
int read(short int user_type, string user_name);

/*
 * Listar e deletar todos os usuários de uma lista
 *
 * @entrada
 * * int user_type - tipo do usuário
 * * * 1) pessoal
 * * * 2) profissional
 * * * 0) todas
 * 
 * @saida
 * * int result - número de usuários deletados, -1 se nada foi deletado
 */
int list(short int user_type);

/*
 * Imprimir usuário
 * 
 * @entrada
 * * int user_type - tipo se usuário
 * * * 1) pessoal
 * * * 2) profissional
 * * int user_positon - posição do usuário na lista, 0 <= $user_position < 10
 */
void printUser(short int user_type, short int user_position);

/*
 * CRUD de uma agenda telefônica, que contém nome, cpf, endereço, telefone, celular e tipo.
 *
 * @entrada
 * * int option - opção do crud
 * * * 1) inserir
 * * * 2) excluir
 * * * 3) alterar
 * * * 4) buscar
 * * * 5) listar pessoais
 * * * 6) listar todos
 * * * 7) listar profissionais
 * * * 0) sair
 * * User user
 * * * int user_type - tipo se usuário
 * * * * 1) pessoal
 * * * * 2) profissional
 * * * string user_name - nome do usuário
 * * * int user_cpf - cpf do usuário, 11 dígitos
 * * * string user_address - endereço do usuário
 * * * int user_tel - telefone do usuário, 10 dígitos
 * * * int user_cell - celular do usuário, 11 dígitos
 * 
 * @saida
 * * string message
 * * * 1) Inserido com sucesso! || Desculpe, agenda lotada!
 * * * 2) Excluido com sucesso! || Desculpe, contato $user_name nao existe!
 * * * 3) Alterado com sucesso! || Desculpe, contato $user_name nao existe!
 * * * 4) $user || Desculpe, contato $user_name nao existe!
 * * * 5) [$user] Listado com sucesso!
 * * * 6) [$user] Listado com sucesso!
 * * * 7) [$user] Listado com sucesso!
 * * * 0) Obrigado!
 * * 
 */

int main(){
    /*
     * init
     */
    int option;
    
    for(int i = 0; i < NUM_USER_TYPES; i++){
        list_size[i] = 0;
    }

    short int user_type;
    string user_name;
    long int user_cpf;
    string user_address;
    long int user_tel;
    long int user_cell;
    
    /*
     * operations
     */
    do{
        scanf("%d", &option);
        switch(option){
            case INSERIR:
                scanf("%hd", &user_type);
                scanf(" %[^\n]s", user_name);
                scanf("%ld", &user_cpf);
                scanf(" %[^\n]s", user_address);
                scanf("%ld", &user_tel);
                scanf("%ld", &user_cell);
                
                if(create(user_type, user_name, user_cpf, user_address, user_tel, user_cell) != -1){
                    printf("Inserido com sucesso!\n");
                }else{
                    printf("Desculpe, agenda lotada!\n");
                }

                break;
            case EXCLUIR:
                scanf("%hd", &user_type);
                scanf(" %[^\n]s", user_name);
                
                if(delete(user_type, user_name) != -1){
                    printf("Excluido com sucesso!\n");
                }else{
                    printf("Desculpe, contato %s nao existe!\n", user_name);
                }

                break;
            case ALTERAR:
                scanf("%hd", &user_type);
                scanf(" %[^\n]s", user_name);
                if(read(user_type, user_name) == -1){
                    printf("Desculpe, contato %s nao existe!\n", user_name);
                    break;
                } 
                scanf("%ld", &user_cpf);
                scanf(" %[^\n]s", user_address);
                scanf("%ld", &user_tel);
                scanf("%ld", &user_cell);
                
                if(update(user_type, user_name, user_cpf, user_address, user_tel, user_cell) != -1){
                    printf("Alterado com sucesso!\n");
                }else{
                    printf("Desculpe, contato %s nao existe!\n", user_name);
                }

                break;
            case BUSCAR:
                scanf("%hd", &user_type);
                scanf(" %[^\n]s", user_name);
                
                int user_index = read(user_type, user_name); 


                if(user_index !=  -1){
                    printUser(user_type, user_index);
                    printf("Buscado com sucesso!\n");
                }else{
                    printf("Desculpe, contato %s nao existe!\n", user_name);
                }

                break;
            case LISTAR_PESSOAIS:
                if(list(1) != -1){
                    printf("Listado com sucesso!\n");
                }else{
                    printf("Desculpe, agenda vazia!\n");
                }
                break;
            case LISTAR_PROFISSIONAIS:
                if(list(2) != -1){
                    printf("Listado com sucesso!\n");
                }else{
                    printf("Desculpe, agenda vazia!\n");
                }
                break;
            case LISTAR_TODOS:
                if(list(1) != -1){
                    printf("Listado com sucesso!\n");
                }else{
                    printf("Desculpe, agenda vazia!\n");
                }
                if(list(2) != -1){
                    printf("Listado com sucesso!\n");
                }else{
                    printf("Desculpe, agenda vazia!\n");
                }
                break;
            case SAIR:
                printf("Obrigado!\n");
                break;
        }
    }while(option != 0);
    
    return 0;
}

/*
 * Support Functions
 */

int create(short int user_type, string user_name, long int user_cpf, string user_address, long int  user_tel, long int user_cell){
    //check if list is empty
    if(list_size[user_type-1] == MAX_CONTATOS){
        return -1;
    }
    
    //create
    strcpy(list_user_name[user_type-1][list_size[user_type-1]], user_name);
    list_user_cpf[user_type-1][list_size[user_type-1]] = user_cpf;
    strcpy(list_user_address[user_type-1][list_size[user_type-1]], user_address);
    list_user_tel[user_type-1][list_size[user_type-1]] = user_tel;
    list_user_cell[user_type-1][list_size[user_type-1]] = user_cell;
    return list_size[user_type-1]++;
}

int delete(short int user_type, string user_name){
    //check if list is empty
    if(list_size[user_type-1] == 0){
        return -1;
    }

    //delete
    for(int i = 0; i < list_size[user_type-1]; i++){
        if(strcmp(list_user_name[user_type-1][i], user_name) == 0){
            for(int l = i; l < list_size[user_type-1]; l++){
                strcpy(list_user_name[user_type-1][l], list_user_name[user_type-1][l+1]);
                list_user_cpf[user_type-1][l] = list_user_cpf[user_type-1][l+1];
                strcpy(list_user_address[user_type-1][l], list_user_address[user_type-1][l+1]);
                list_user_tel[user_type-1][l] = list_user_tel[user_type-1][l+1];
                list_user_cell[user_type-1][l] = list_user_cell[user_type-1][l+1];
            }
            list_size[user_type-1]--;
            return i;
        }
    }
    return -1;
}

int update(short int user_type, string user_name, long int user_cpf, string user_address, long int  user_tel, long int user_cell){
    //search user
    int user_index = read(user_type, user_name);
   
    if(user_index != -1){
        list_user_cpf[user_type-1][user_index] = user_cpf;
        strcpy(list_user_address[user_type-1][user_index], user_address);
        list_user_tel[user_type-1][user_index] = user_tel;
        list_user_cell[user_type-1][user_index] = user_cell;
    }
    return user_index;
}

int read(short int user_type, string user_name){
    //check if list is empty
    if(list_size[user_type-1] == 0){
        return -1;
    }

    //read
    for(int i = 0; i < list_size[user_type-1]; i++){
        if(strcmp(list_user_name[user_type-1][i], user_name) == 0){
            return i;
        }
    }
    return -1;
}

int list(short int user_type){
    //check if list is empty
    if(list_size[user_type-1] == 0){
        return -1;
    }

    //list
    for(int i = 0; i < list_size[user_type-1]; i++){
        printUser(user_type, i);
    }
    return list_size[user_type-1];
}

void printUser(short int user_type, short int user_position){
    printf("%s\n", list_user_name[user_type-1][user_position]);
    printf("%ld\n", list_user_cpf[user_type-1][user_position]);
    printf("%s\n", list_user_address[user_type-1][user_position]);
    printf("%ld\n", list_user_tel[user_type-1][user_position]);
    printf("%ld\n", list_user_cell[user_type-1][user_position]);
}
