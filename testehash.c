/*
 * O testehash é uma ferramenta simples para geração de hash.
 * Desenvolvi para demonstrar a produção de hashs em sistemas e criptomoedas
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <openssl/sha.h> //Apesar de existirem diversas bibliotecas criptográficas, a libssl é uma das mais usadas
                         //a documentação é, infelizmente, uma porcaria

//A função digest recebe uma string, como array de chars e retorna o hexdigest (saida hexadecimal em tamanho duplo)
//como string (ponteiro de char)
char* digest(char mensagem[]){

    char *strout = (char*)malloc(sizeof(char)*SHA256_DIGEST_LENGTH);//A string de saída é alocada com o tamanho padrão da
                                                                    //SHA256

    unsigned char hash[SHA256_DIGEST_LENGTH];//A hash é armazenada em estado bruto num array de chars sem sinal 
    /* O algoritmo para encriptar a mensagem, de forma mais comum é:
     * Criar um "wrapper" contexto. O contexto é um conjunto de dados previamente gerados que será usado pela função para produzir o hash
     * O contexto é inicializado, atualizado com os dados da mensagem e por fim o hash é produzido
     */
    SHA256_CTX contexto;
    SHA256_Init(&contexto);
    SHA256_Update(&contexto, mensagem, strlen(mensagem));
    SHA256_Final(hash, &contexto);

    /* Como o hash é um array de tamanho fixo (SHA256_DIGEST_LENGTH), contendo em seus elementos os trechos do hash, não é possível
     * imprimir diretamente seus dados. Pra isso usamos o seguinte algoritmo:
     * Usamos uma variável temporária (buff) do tipo char, com tamanho "duplo", para receber cada um dos itens. 
     * Como não ha metodo direto para isso, mas há como imprimir com a string de formato 02x (hexadecimal de 2 posições, completados com zeros a esquerda)
     * usamos a função sprintf para imprimir para a variável temporária buff 
     * O conteúdo de buff é concatenado na variável de saída strout, que é retornada
     */

    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++){
        char *buff = (char*)malloc(sizeof(char)*2+1);

        sprintf(buff, "%02x", hash[i]);
        strcat(strout, buff);

    }

    return strout;
}

//A função imprime o hash de um inteiro. O inteiro é primeiro "impresso para uma variável" string, 
//já que os resultados para o tratamento para uma string e para os números são diferentes (a codificação varia)
void _imp_int(int c){
    char *_c;
    _c = (char*)malloc(sizeof(char)*SHA256_DIGEST_LENGTH);

    sprintf(_c, "%d", c);
    printf("| Inteiro: %08d | Hash: %s\n", c, digest(_c));
    free(_c);

}

/* A funçao gera o hahs da string recebida. 
 * O condicional e meramente estetico, permitindo que strings muito extensas sejam impressas numa linha e seu hash em ou-
 * tra. 
 */
void _imp_str(char *c){

    if(strlen(c)<16)
    	printf("| String: %s | Hash: %s\n", c, digest(c));
    else
	printf("| String: %s \n| Hash: %s\n", c, digest(c));
}

int main(int argc, char *argv[]){

    srand(time(NULL)); //Inicializa a semente de números pseudoaleatórios, usando o tempo do sistema
		       //Felizmente este não é um sistema "seguro"

    /*Existem interpretadores de argumentos em C, mas não são simples de usar e criam dependências externas 
     *A abordagem mais simples é só procurar na linha de comando em posições específicas pelos argumentos esperados 
     *O programa, no entanto, perde a flexibilidade
     *No nosso caso contamos a quantidade de argumentos e comparamos a segunda posição pelos argumentos n (para gerar números 
     *aleatórios), s (para encriptar uma string) ou sl (para encadear a sequencia de stringis a seguir e processar como uma string única)
     */
    if(argc==3 && strcmp(argv[1], "-n")==0){
	char *ptr;
	long int v = strtol(argv[2], &ptr, 10); /*A função strtol separa letras e números de uma string, colocando os dados alfanuméricos no ponteiro ptr 
						 *e o número existe é retornado (armazenado na variável v, no nosso caso). Caso não existam números (ou ele
						 *não esteja antes das letras) a variável v tem valor 0 e o programa sugere ao usuário o uso correto. 
						 */
	if(v==0)
            printf("Digite um número inteiro para informar a quantidade de hashs de números inteiros a serem gerados\n");
        else
            for(int i=0; i<atoi(argv[2]); i++)
                _imp_int(rand()%99999999); // Número aleatório de 8 posições 
    }

    //Neste caso tudo que estiver depois do argumento -s é tratado como string individual e seu hash gerado individualmente
    else if(argc>=3 && strcmp(argv[1], "-s")==0){
        for(int i=2; i<argc; i++)
            _imp_str(argv[i]);
    }

    //Neste caso (-sl) as strings apresentadas após o argumento são concatenadas e encriptadas como uma string só
    else if(argc>=3 && strcmp(argv[1], "-sl")==0){

        char buffer[1024];

        for(int i=2; i<argc; i++){
	//O condicional abaixo evita que os espaços entre as strings sejam ignorados ou que um espaço seja incluído no começo da string
	//(o que fatalmente resultaria o hash de saída)
            if(strcmp(buffer, "")==0)
                strcat(buffer, argv[i]);
            else {
                strcat(buffer, " ");
                strcat(buffer, argv[i]);
            }
        }

        _imp_str(buffer);

    }
    else {
        printf("Uso do testehash:\n");
        printf("testehash -n X - O programa gerará X números aleatórios e seus respectivos hashes\n");
        printf("testehash -s <string1> ... <stringX> - O programa apresentará os hashs das X strings apresentadas \n");
        printf("testehash -sl <string> - O programa unirá todas as strings apresentadas e criará um hash único\n");

    }

}
