package testehash;

import java.security.MessageDigest; //Funções criptográficas
import java.util.Objects; //Funções de comparação de conteúdo
import java.util.concurrent.ThreadLocalRandom; //Criação de números aleatórios

public class Main {

    //A função sha256 retorna um hash sha256 da string base, que é recebida como parâmetro
    private static String sha256(String base) {
        try{
            MessageDigest digest = MessageDigest.getInstance("SHA-256"); //Cria o objeto digest, com o algoritmo sha256
            byte[] hash = digest.digest(base.getBytes("UTF-8")); /* Os hashs produzido pelas funções digest
                                                                             * são arrays de dados brutos, portanto o
                                                                             * melhor meio para armazenar a saida é um
                                                                             * do tipo byte (um inteiro hexadécimal
                                                                             * assinado de 8 bits)
                                                                             */
            StringBuilder hexString = new StringBuilder(); //Considerando que a mensagem foi separada em diversos itens
                                                           //de um array, é preciso concatenar os mesmos pra apresentar
                                                           //a saida de forma consistente

            //Para cada byte no hash, ele deve ser convertido em string
            for(byte h : hash){
                String hex = Integer.toHexString(0xff & h); //Converte o item em string
                                                              //A operação 0xff & byte garante que somente os últimos
                                                              //8 bits sejam utilizados na conversão
                if(hex.length() == 1) hexString.append('0'); //Caso o item tenha comprimento 1, a string de retorno
                                                             // recebe 0
                hexString.append(hex); //O byte convertido é anexado a String de saida
            }

            return hexString.toString(); //Retorna a string e saida
        } catch(Exception ex){
            throw new RuntimeException(ex);
        }
    }

    public static void main(String[] args){
        try {
            if (args.length == 2 && Objects.equals(args[0], "-n"))
                for (int i = 0; i < Integer.parseInt(args[1]); i++) {
                    Integer a = ThreadLocalRandom.current().nextInt(1, 1000000);
                    System.out.printf("Inteiro: %7s | Hash: %s\n", a, sha256(Integer.toString(a)));
                }
            else if (args.length >= 2 && Objects.equals(args[0], "-s")) {
                for (int i = 1; i < args.length; i++)
                    System.out.printf("String: %s | Hash: %s\n", args[i], sha256(args[i]));
            } else if(args.length >= 2 && Objects.equals(args[0], "-sl")){
                StringBuilder c = new StringBuilder();
                for(int i = 1; i<args.length; i++) {
                    c.append(" ");
                    c.append(args[i]);
                }
                System.out.printf("String: %s | Hash: %s\n", c.toString(), sha256(c.toString()));

            } else {
                System.out.println("Uso do testeHash:");
                System.out.println("testeHash -n X - O programa gerará X números aleatórios e seus respectivos hashes");
                System.out.println("TesteHash -s <string1> ... <stringX> - O programa apresentará os hashs das X strings apresentadas ");
                System.out.println("TesteHash -sl <string> - O programa unirá todas as strings apresentadas e criará um hash único");

            }
        } catch (Exception e){

            if(e instanceof java.lang.NumberFormatException)
                System.out.println("Digite um número inteiro para a geração de hashes de números aleatórios");
        }
    }
}
