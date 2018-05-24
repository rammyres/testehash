package testehash;

import java.security.MessageDigest;
import java.util.Objects;
import java.util.concurrent.ThreadLocalRandom;

public class Main {

    private static String sha256(String base) {
        try{
            MessageDigest digest = MessageDigest.getInstance("SHA-256");
            byte[] hash = digest.digest(base.getBytes("UTF-8"));
            StringBuilder hexString = new StringBuilder();

            for(byte h : hash){
            //for (int i = 0; i < hash.length; i++) {
                String hex = Integer.toHexString(0xff & h);
                if(hex.length() == 1) hexString.append('0');
                hexString.append(hex);
            }

            return hexString.toString();
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


	// write your code here
    }
}
