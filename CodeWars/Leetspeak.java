package CodeWars;
/*
 * kata: https://www.codewars.com/kata/543bfbecdef6345f52000e4d/
 *
 * Specific Instructions
 * The code must contain a Leetspeak class inherited from an Encoder abstract class and containing an encode(String) method returning itself the encoded String.
 * The encode method should return an empty String if a null parameter is passed.
 * If any uppercase character is given, it should be compared also with the dictionary, 'a' gives '4' but 'A' gives also '4'.
 * If any character outside the dictionary is given, it should be output as is.
 *
 * Dictionary to reproduce
 * The following dictionary has to be used :
 * a -> 4
 * e -> 3
 * l -> 1
 * m -> /^^\
 * o -> 0
 * u -> (_)
 */
public class Leetspeak extends  Encoder {

    String[] dictFrom = {"a", "e", "l", "m", "o", "u"};
    String[] dictTo = {"4", "3", "1", "/^^\\", "0", "(_)"};

    public String encode(String source){
        if(source == null){
            return  "";
        }

        String translated = new String(source);
        for(int i=0; i<dictFrom.length; i++){
            translated = translated.replace(dictFrom[i], dictTo[i]);
            translated = translated.replace(dictFrom[i].toUpperCase(), dictTo[i]);
        }

        return translated;
    }

}

abstract class Encoder{
    public abstract String encode(String source);
}

class LeetspeakTest{
    public static void main(String[] args) {
        System.out.println(new Leetspeak().encode("Abcdef"));
    }
}