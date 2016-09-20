/*
 * NOME: Rodrigo Seiji Piubeli Hirao
 * RA: 186837
 * TURMA: R
 */

#include <stdio.h>

#define MAX_IMAGE_SIZE 600
#define MAX_FILTER_SIZE 10

/*
 * Matrizes das imagens rgb
 */
int  image_r[MAX_IMAGE_SIZE][MAX_IMAGE_SIZE], 
     image_g[MAX_IMAGE_SIZE][MAX_IMAGE_SIZE], 
     image_b[MAX_IMAGE_SIZE][MAX_IMAGE_SIZE],
     image_gray[MAX_IMAGE_SIZE][MAX_IMAGE_SIZE];
long image_final[MAX_IMAGE_SIZE][MAX_IMAGE_SIZE];

/*
 * Ler imagem e descomprimí-la
 *
 * @entrada
 * * int image_to_read[$width][$height] - matriz da imagem que será lida
 * * int width - largura da imagem
 * * int height - altura da imagem
 */
void readImage(int image_to_read[MAX_IMAGE_SIZE][MAX_IMAGE_SIZE], int width, int height);

/*
 * Escrever imagem
 *
 * @entrada
 * * int image_to_print[$width][$height] - matriz da imagem que será impressa
 * * int width - largura da imagem
 * * int height - altura da imagem
 */
void printImage(long image_to_print[MAX_IMAGE_SIZE][MAX_IMAGE_SIZE], int width, int height);

/*
 * O programa lerá uma matriz comprimida, descomprimirá, deixará ela em escala cinza, 
 * e, então, aplicará o filtro desejado, a partir do algoritmo de convolução de matrizes.
 * 
 * @stdin
 * * $D
 * * $X
 * * $M
 * * $width $height
 * * $image_r $image_g $image_b
 *
 * @entrada
 * * int D - divisor da convolução
 * * int X - ordem da matriz quadrada $M, $X = 2K + 1 / K e Z, $X < 10
 * * int M[$X][$X] - matriz quadrada usada na convolução
 * * int $width - largura da imagem, em pixels, $width <= 600
 * * int $height - largura da imagem, em pixels, $height <= 600
 * * int $image_r[$width][$height] - matriz dos pixels vermelhos da imagem
 * * int $image_g[$width][$height] - matriz dos pixels verdes da imagem
 * * int $image_b[$width][$height] - matriz dos pixels azuis da imagem
 *
 * @stdout
 * * P2
 * * $width $height
 * * 255
 * * $image_final
 * 
 * @saída
 * * int width - largura, em pixels, da imagem
 * * int height - altura, em pixels, da imagem
 * * int A - altura da matriz da imagem final, número de linhas
 * * int l - largura da matriz da imagem final, número de colunas
 * * int image_final[$A][$L] - matriz da imagem após serem aplicados os filtros
 * 
 */
int main(){
    
    /*
     * Leitura das variáveis de convolução
     */
    int D, X;
    int M[MAX_FILTER_SIZE][MAX_FILTER_SIZE];
    scanf("%d", &D);
    scanf("%d", &X);

    #ifdef DEBUG
        printf(">Matriz de convolução de divisor %d:\n", D);
    #endif

    for(int i = 0; i < X; i++){
        for(int j = 0; j < X; j++){
                scanf("%d", &M[i][j]);

                #ifdef DEBUG
                    printf("%3d ", M[i][j]);
                #endif
        }

        #ifdef DEBUG
            printf("\n");
        #endif
    }
    
    /*
     * Leitura das imagens R G B
     */
    int width, height;
    scanf("%d %d", &width, &height);

    #ifdef DEBUG
        printf("\n\n>Imagem na cor vermelha, de tamanho %d por %d:\n\n", width, height);
    #endif
    readImage(image_r, width, height);
    #ifdef DEBUG
        printImage(image_r, width, height);
    #endif

    #ifdef DEBUG
        printf("\n\n>Imagem na cor verde, de tamanho %d por %d:\n\n", width, height);
    #endif
    readImage(image_g, width, height);
    #ifdef DEBUG
        printImage(image_g, width, height);
    #endif

    #ifdef DEBUG
        printf("\n\n>Imagem na cor azul, de tamanho %d por %d:\n\n", width, height);
    #endif
    readImage(image_b, width, height);
    #ifdef DEBUG
        printImage(image_b, width, height);
    #endif
    
    /*
     * Convert to grayscale
     */

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            image_gray[i][j] = (image_r[i][j] + image_g[i][j] + image_b[i][j])/3;
        }
    }

    #ifdef DEBUG
        printf("\n\n>Imagem em escala cinza:\n\n");
        printImage(image_gray, width, height);
    #endif 
    
    /*
     * Aplicações dos filtros nas imagem (convolução)
     */
    
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            //valores dos cantos
            if(i < X/2 || j < X/2 || i > height - 1 - X/2 || j > width - 1 - X/2){
                image_final[i][j] = image_gray[i][j];
            }
            //valores para aplicar a convolução
            else{
                image_final[i][j] = 0;
                for(int m = -X/2; m <= X/2; m++){
                    for(int n = -X/2; n <= X/2; n++){
                        image_final[i][j] += (image_gray[i+m][j+n] * M[m+X/2][n+X/2]);
                    }
                }
                image_final[i][j] /= D;
                if(image_final[i][j] < 0){
                    image_final[i][j] = 0;
                }
                else if(image_final[i][j] > 255){
                    image_final[i][j] = 255;
                }
            }
        }
    }

    #ifdef DEBUG
        printf("\n\n>Imagem final:\n\n");
    #endif 
    printImage(image_final, width, height);

    return 0;
}

/*
 * Funções de suporte
 */

void readImage(int image_to_read[MAX_IMAGE_SIZE][MAX_IMAGE_SIZE], int width, int height){
    int num_colors = 0;
    int cur_color;

    int i = 0, j = 0;
    while(i < height){
        scanf("%d", &num_colors);
        scanf("%d", &cur_color);

        #ifdef DEBUG
            printf("%d %d - ", num_colors, cur_color);
        #endif

        while(num_colors > 0){
            image_to_read[i][j] = cur_color;
            num_colors--;
            j++;
            if(j == width){
                j = 0;
                i++;
            }
        }
    }
    #ifdef DEBUG
        printf("\n");
    #endif
}

void printImage(long image_to_print[MAX_IMAGE_SIZE][MAX_IMAGE_SIZE], int width, int height){
    #ifdef DEBUG
        printf("\n");
    #endif
    #ifndef DEBUG
        printf("P2\n%d %d\n255\n", width, height);
    #endif
    for(int i = 0; i < height; i++){ 
        #ifdef DEBUG
            printf("%4ld", image_to_print[i][0]); 
        #else
            printf("%ld", image_to_print[i][0]); 
        #endif
        for(int j = 1; j < width;j++){
            #ifdef DEBUG
                printf(" %4ld", image_to_print[i][j]); 
            #else
                printf(" %ld", image_to_print[i][j]); 
            #endif
        }
        printf("\n");
    }
}
