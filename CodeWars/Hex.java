package CodeWars;
/*
 * kata: https://www.codewars.com/kata/5483366098aa442def0009af
 * Description:
 * Create a class Hex which takes a number as an argument.
 *
 * Adding a hex object to a number (by using valueOf) generates a number, but calling toString or toJSON will show its
 * hexadecimal value starting with "0x". To make hex objects comparable you have to provide a method equals.
 *
 * Example:
 * Hex FF = new Hex(255);
 * FF.toString() == "0xFF"
 * FF.valueOf() + 1 == 256
 * FF.equals(new Hex(255)) == true

 * Also create two methods, plus and minus which will add or subtract a number or Hex object and return a new Hex object.
 * Hex a = new Hex(10);
 * Hex b = new Hex(5);
 * a.plus(b).toJSON() == "0xF";
 * a.plus(2).toJSON() == "0xC";
 *
 * Also, create a parse class method that can parse Hexadecimal numbers and convert them to standard decimal numbers:
 * Hex.parse("0xFF") == 255
 * Hex.parse("FF") == 255
 */

public class Hex {
    int value;
    private final char [] digits = {'0', '1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
    
    public Hex(int value) {
        this.value = value;
    }

    public int getValue() {
        return value;
    }

    public void setValue(int value) {
        this.value = value;
    }

    char convertValueToDigit(int value){
        return this.digits[value];
    }

    int convertDigitToValue(char digit){
        return new String(this.digits).indexOf(digit);
    }

    public int valueOf() {
        return this.getValue();
    }

    String toJSON(){
        StringBuffer json = new StringBuffer("");
        int remain = -1, current = this.value;

        do{
            json.append(this.convertValueToDigit(current % 16));
            current /= 16;
        } while(current > 0);

        return "0x" + json.reverse();
    }

    Hex plus(int other){
        return new Hex(this.value + other);
    }

    Hex minus(int other){
        return new Hex(this.value - other);
    }

    public Hex plus(Hex other){
        return new Hex(this.value + other.getValue());
    }

    public Hex minus(Hex other){
        return new Hex(this.value - other.getValue());
    }

    public static int parse(String string){
        int value = 0;

        string = string.replace("0x", "");

        for(int i = 0; i<string.length(); i++){
            value += new Hex(0).convertDigitToValue(string.charAt(string.length()-i-1)) * Math.pow(16, i);
        }

        return value;
    }

    @Override
    public boolean equals(Object other) {
        if (!(other instanceof  Hex))
            return false;
        Hex otherHex = (Hex) other;
        return this.value == otherHex.getValue();
    }

    @Override
    public String toString() {
        return this.toJSON();
    }
}

class HexTest{
    public static void main(String[] args) {
        System.out.println("____________________________________\nTESTING Hex.parse()");
        System.out.println("Parsing ''");
        System.out.println(Hex.parse(""));
        System.out.println("Parsing '124'");
        System.out.println(Hex.parse("124"));
        System.out.println("Parsing '0x12D'");
        System.out.println(Hex.parse("0x12D"));

        Hex testHex = new Hex(0);
        System.out.println("____________________________________\nTESTING Hex.convert...()");
        System.out.println("Converting 'A'");
        System.out.println(testHex.convertDigitToValue('A'));
        System.out.println("Converting 15");
        System.out.println(testHex.convertValueToDigit(15));

        System.out.println("____________________________________\nTESTING Hex.toString()");
        System.out.println("Hex(0).plus(301).toString()");
        System.out.println(testHex.plus(301).toString());
        System.out.println("Hex(0).toString()");
        testHex.setValue(0);
        System.out.println(testHex.toString());
    }
}
