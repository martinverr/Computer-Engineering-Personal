package CodeWars;
/*
 * kata: https://www.codewars.com/kata/5412509bd436bd33920011bc
 *
 * Description:
 * Usually when you buy something, you're asked whether your credit card number, phone number or answer to your most
 * secret question is still correct. However, since someone could look over your shoulder, you don't want that shown
 * on your screen. Instead, we mask it.
 *
 * Your task is to write a function maskify, which changes all but the last four characters into '#'.
 *
 * Examples
 * Maskify.Maskify("4556364607935616"); // should return "############5616"
 * Maskify.Maskify("64607935616");      // should return "#######5616"
 * Maskify.Maskify("1");                // should return "1"
 * Maskify.Maskify("");
 */
public class Maskify {
    public static String maskify(String str) {
        //throw new UnsupportedOperationException("Unimplemented");
        char[] newString = str.toCharArray();

        for(int i=0; i<str.length()-4; i++){
            newString[i] = '#';
        }

        return new String(newString);
    }
}

class TestMaskify{
    public static void main(String[] args) {
        System.out.println(Maskify.maskify("9318265178465"));
        System.out.println(Maskify.maskify("93"));
        System.out.println(Maskify.maskify(""));
        System.out.println(Maskify.maskify("9318"));
    }
}