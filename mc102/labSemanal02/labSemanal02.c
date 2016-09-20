/*
 * NOME: Rodrigo Seiji Piubeli Hirao
 * RA: 182867
 * TURMA: R
 */

#include <stdio.h>

#define ANO_INICIAL 2016

/*
 * Dadas a configuração da maquete, o preço e a capacidade do galão 
 * de água em vários fornecedores, o aniversário da cidade e o último 
 * ano em que a exposição estará aberta, determinar quanto será gasto 
 * pela prefeitura com água, para manter a maquete sempre cheia.
 *
 * @stdin format
 * * $k
 * * [[($x , $y) ]\n]
 * * $dia/$mes
 * * $ano
 * * $f
 * * $c \$$pi
 *
 * @entrada
 * * k {short+} número de ilhas na maquete, 2 < $k < 100
 * * vértice [{Ponto}] vértices da ilha
 * * * x {double} coordenada X do vértice
 * * * y {double} coordenada Y do vértice
 * * data {Data} data de aniversário da cidade
 * * * dia {int} dia do aniversário da cidade
 * * * mes {int} mês do aniversário da cidade
 * * ano {int} ano até o qual terão exposições, $ano >= 2016
 * * f {short+} número de fornecedores de água, $f < 100
 * * galão [{Galão}] galão
 * * * c {int} capacidade do galão
 * * * pi {double} preço do galão
 * 
 * @stdout format
 * * A manutencao da maquete custara $x aos cofres publicos.
 *
 * @saída
 * * x {double} custo calculado da água
 */
int main(){

    unsigned short int k;
    
    scanf("%hu", &k);
    
    /*
     * Cálculo do volume necessária de água
     */
    double min_x, min_y, max_x, max_y;
    double area_ilhas = 0;
    //Área das ilhas
    for(int i = 0; i < k;  i++){
        double x0, y0, xb, yb, x, y;
        double area_ilha = 0;
    
        //Área da primeira ilha
        scanf("\n(%lf , %lf)", &x0, &y0);
        xb = x0;
        yb = y0;
        if(i == 0){
            min_x = x0;
            min_y = y0;
            max_x = x0;
            max_y = y0;
        }

        //Áreas das ilhas restantes
        do{
            scanf(" (%lf , %lf)", &x, &y);
            area_ilha += (x - xb) * (y + yb)/2;
            xb = x;
            yb = y;
            if(x < min_x) min_x = x;
            if(y < min_y) min_y = y;
            if(x > max_x) max_x = x;
            if(y > max_y) max_y = y;
        } while(x0 != x || y0 != y);
        if(area_ilha < 0) area_ilha = -area_ilha;

        area_ilhas += area_ilha;
    }

    //Volumes finais
    double vol_ilhas, vol_total, vol_agua;
    
    vol_ilhas = (area_ilhas * 0.5) * 1000;
    vol_total = ((max_x - min_x + 1) * (max_y - min_y + 1) * 0.5) * 1000;
    vol_agua = vol_total - vol_ilhas;

    
    /*
     * Gerenciamento das datas
     */
    int dia, mes, ano;
    scanf("%d/%d", &dia, &mes);
    scanf("\n%d", &ano);
    
    int ano_inicial = ANO_INICIAL - 1;
    int ano_final = ano;
    int cont_eventos = 0;

    /*
     * Contagem de sextas feiras 13
     */
    int cont_sextafeira13 = 0;
    for(int ano_atual = ano_inicial; ano_atual <= ano_final; ano_atual++){
       for(int mes_atual = 3; mes_atual < 15; mes_atual++){

            if(ano_atual == ano_inicial && mes_atual == 3) mes_atual = 13;
            if(ano_atual == ano_final && mes_atual == 13) break;
            
            //Congruência de Zeller
            int dia_da_semana = (13 + ((13*(mes_atual + 1))/5) + (ano_atual%100) + (ano_atual%100)/4 + (ano_atual/100)/4 + 5*(ano_atual/100))%7;

            if(dia_da_semana == 6) cont_sextafeira13++;
        }
    }
    cont_eventos += cont_sextafeira13;

    /*
     * Contagem de aniversários não consecutivos
     */
    
    if(mes == 2 && dia == 29){
        ano_inicial = ANO_INICIAL;
        for(int ano_atual = ano_inicial; ano_atual <= ano_final; ano_atual++){
            if((ano_atual % 4 == 0 && ano_atual % 100 != 0) || ano_atual % 400 == 0){
                cont_eventos++;
            }
        }
    }else{    
        cont_eventos += (ano - ano_inicial);
    }

    if(12 <= dia && dia <= 14){
        if(mes != 1 && mes != 2){
            ano_inicial = ANO_INICIAL;
        }else{
            ano_final = ano - 1;
            mes += 12;
        }
        
        for(int ano_atual = ano_inicial; ano_atual <= ano_final; ano_atual++){
            //Congruência de Zeller
            int dia_da_semana = (dia + ((13*(mes + 1))/5) + (ano_atual%100) + (ano_atual%100)/4 + (ano_atual/100)/4 + 5*(ano_atual/100)) % 7;

            if((dia == 12 && dia_da_semana == 5) || (dia == 13 && dia_da_semana == 6) || (dia == 14 && dia_da_semana == 0))
                cont_eventos--;
        }
    }
    
    /*
     * Verificação do melhor galão, e seu preço
     */
    double menor_preco;
    
    unsigned short int f;
    int c;
    double pi;

    scanf("\n%hu", &f);
    
    int quant_galoes;
    scanf("%d $%lf", &c, &pi);
    quant_galoes = vol_agua / c;
    if(vol_agua - quant_galoes != 0.0) quant_galoes++;
    menor_preco = quant_galoes * pi;

    for(int i = 1; i < f; i++){
        scanf("%d $%lf", &c, &pi);
        quant_galoes = vol_agua / c;
        if(vol_agua - quant_galoes != 0.0) quant_galoes++;

        if(quant_galoes * pi < menor_preco)
            menor_preco = quant_galoes * pi;
    }
    
    /*
     * Cálculo do preço final
     */
    double preco_final = menor_preco * cont_eventos;
    
    printf("A manutencao da maquete custara $%.2lf aos cofres publicos.\n", preco_final);
}

