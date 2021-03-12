package CodeWars;

/*
* https://www.codewars.com/kata/5264d2b162488dc400000001
* In this exercise I could use StringBuilder.reverse() (or StringBuffer.reverse), but I discovered this method later
*
* Exercise:
* Write a function that takes in a string of one or more words, and returns the same string, but with all five or more
* letter words reversed (Just like the name of this Kata). Strings passed in will consist of only letters and spaces.
* Spaces will be included only when more than one word is present.
*
* Examples:
* spinWords( "Hey fellow warriors" ) => returns "Hey wollef sroirraw"
* spinWords( "This is a test") => returns "This is a test"
* spinWords( "This is another test" )=> returns "This is rehtona test"
*/
public class SpinWords {

    public String spinWords(String sentence) {
        String[] words = sentence.split(" ");

        for(int k= 0; k<words.length; k++){
            if (words[k].length()>4){
                char[] word_a = words[k].toCharArray();
                int j = words[k].length() - 1;
                for(int i = 0; i<j; i++, j--) {
                    char temp = word_a[i];
                    word_a[i] = word_a[j];
                    word_a[j] = temp;
                }
                words[k] = new String(word_a);
            }
        }

        return String.join(" ", words);
    }
}

class SpinWordsTest {
    public static void main(String[] args) {
        System.out.println(new SpinWords().spinWords("This is a test with this long wrd: longword"));
    }
}