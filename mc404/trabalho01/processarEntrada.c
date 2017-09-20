#include "montador.h"
#include "token.h"
#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

/*
 * Remove white spaces on start and end of string
 */
char *strtrim(char *str)
{
  char *end;

  while(str[0] == ' '){
      str++;
  }

  if(!*str){
    return str;
  }

  end = str + strlen(str) - 1;
  while(end > str && end[0] == ' ') {
      end--;
  }

  end[1] = '\0';

  return str;
}


/* 
 * Argumentos:
 *  entrada: cadeia de caracteres com o conteudo do arquivo de entrada.
 *  tamanho: tamanho da cadeia.
 * Retorna:
 *  1 caso haja erro na montagem; 
 *  0 caso não haja erro.
 */
int processarEntrada(char* entrada, unsigned tamanho) 
{
    /*
     * Defining token
     */
    Token token;
    TipoDoToken token_type[] = {
        0,          
        DefRotulo,  // Group 1
        Diretiva,   // Group 2
        Instrucao,  // Group 3
        Nome,       // Group 4
        0,          // Group 5 (numbers)
        0,          // Group 6 (numbers)
        0           // Group 7 (ERROR)
    };
    size_t num_groups = 8;
    size_t num_lines = 0;
    for(unsigned int i = 0; i < tamanho; i++){
        if(entrada[i] == '\n'){
            num_lines++;
        }
    }
    
    /*
     * Start working with regex
     */
    
    // This regex is quite hard on the eye.
    // Basically it separates the instructions in groups
    // The groups are the ones found in the token_type variable
    regex_t regex;
    regmatch_t regexMatches[num_lines];
    char* regex_string = "[ \t]*([^0-9 :#\n][^ #:\n]*[:])?[ \t]*([.][^0-9 #\n][^ #\n]*)?[ \t]*([A-Z]*)?([a-zA-Z_]+[ \t\n])?[ \t]*([0-9xA-F\"]+[^a-zA-Z:_\n])?[ \t]*([0-9xA-F\"]+[^a-zA-Z:_\n])?[ \t]*([^ \t#\n]+)?[ \t]*[^\n]*";
    // Compile regex
    if(regcomp(&regex, regex_string, REG_EXTENDED)) {
        printf("Error while compiling regex\n");
        return 1;
    } 

    // Used to match the error group, 
    // to know if it was a lexic or gramatical error
    regex_t regex_allowed;
    regmatch_t dummy[num_lines];
    char* regex_allowed_string = "^[ \t]*(([^0-9 :#\n][^ #:\n]*[:])|([.][^0-9 #\n][^ #\n]*)|([a-zA-Z]*))[ \t]*$";
    // Compile regex
    if(regcomp(&regex_allowed, regex_allowed_string, REG_EXTENDED)) {
        printf("Error while compiling regex_allowed\n");
        return 1;
    } 

    /*
     * Loops through document lines to apply regex on each one
     */ 
    char* cursor = entrada;
    unsigned int m;
    for (m = 0; m < num_lines; m++){ 
        if (regexec(&regex, cursor, num_groups, regexMatches, 0)){
            break;
        }
        
        /*
         * Loops through each group found
         */
        unsigned offset = 0;
        for (unsigned int g = 1; g < num_groups; g++){
            int start = regexMatches[g].rm_so;
            int end = regexMatches[g].rm_eo;

            if(start == end){
                continue;
            }
            
            token.tipo = token_type[g];
            token.linha = m + 1;
            token.palavra = (char*)malloc((end-start)*sizeof(char));
            switch(g){
                //Rotule
                case 1:
                    strncpy(token.palavra, cursor + start, end-start-1);
                    token.palavra[end-start-1] = '\0';
                    break;
                //Directive
                case 2:
                    if(regexMatches[2].rm_eo - regexMatches[2].rm_so){
                        goto error_gramatic;
                    }
                    strncpy(token.palavra, cursor + start + 1, end-start-1);
                    token.palavra[end-start-1] = '\0';
                    break;
                //Instruction
                case 3:
                    if(regexMatches[2].rm_eo - regexMatches[2].rm_so){
                        goto error_gramatic;
                    }
                    strncpy(token.palavra, cursor + start, end-start);
                    token.palavra[end-start] = '\0';
                    break;
                //Name
                case 4:
                    if(!((regexMatches[2].rm_eo - regexMatches[2].rm_so) || (regexMatches[3].rm_eo - regexMatches[3].rm_so))){
                        goto error_gramatic;
                    }
                    strncpy(token.palavra, cursor + start, end-start);
                    token.palavra[end-start] = '\0';
                    break;
                //Number (1)
                case 5:
                    if(!((regexMatches[2].rm_eo - regexMatches[2].rm_so) || (regexMatches[3].rm_eo - regexMatches[3].rm_so))){
                        goto error_gramatic;
                    }
                    if(cursor[start+1] == 'x'){
                        token.tipo = Hexadecimal;
                    }else{
                        token.tipo = Decimal;
                    }
                    strncpy(token.palavra, cursor + start, end-start);
                    token.palavra[end-start] = '\0';
                    break;
                //Number (2)
                case 6:
                    if(cursor[start+1] == 'x'){
                        token.tipo = Hexadecimal;
                    }else{
                        token.tipo = Decimal;
                    }
                    strncpy(token.palavra, cursor + start, end-start);
                    token.palavra[end-start] = '\0';
                    break;
                /*
                 * ERROR
                 *
                 * Regex caught something that should not be found
                 */
                case 7:
                    printf("");
                    char test[end-start];
                    strncpy(test, cursor + start, end-start);
                    test[end-start] = '\0';

                    if(!regexec(&regex_allowed, test, 1, dummy, 0)){
                        goto error_gramatic;
                    }else {
                        goto error_lexic;
                    }
                    break;
            }
            token.palavra = strtrim(token.palavra);

            if(token.palavra[0] == '"'){
                token.palavra++;
            }
            for(int i = end-start-1; i >= 0 ; i--){
                if(token.palavra[i] == '"'){
                    token.palavra[i] = '\0';
                    break;
                }
            }

            adicionarToken(token);
        }
        cursor = strchr(cursor, '\n') + 1;
    }

    imprimeListaTokens();

    regfree(&regex);

    return 0; 

    error_gramatic: fprintf(stderr, "ERRO GRAMATICAL: palavra na linha %d!\n", m+1);
    return 1;
    
    error_lexic: fprintf(stderr, "ERRO LEXICO: palavra inválida na linha %d!\n", m+1);
    return 1;
}

