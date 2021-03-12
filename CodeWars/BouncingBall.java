package CodeWars;

/*
 * kata: https://www.codewars.com/kata/5544c7a5cb454edb3c000047
 *
 * Description:
 * A child is playing with a ball on the nth floor of a tall building. The height of this floor, h, is known.
 * He drops the ball out of the window. The ball bounces (for example), to two-thirds of its height (a bounce of 0.66).
 * His mother looks out of a window 1.5 meters from the ground.
 * How many times will the mother see the ball pass in front of her window (including when it's falling and bouncing?
 *
 * Conditions:
 * Float parameter "h" in meters must be greater than 0
 * Float parameter "bounce" must be greater than 0 and less than 1
 * Float parameter "window" must be less than h.
 * If all three conditions above are fulfilled, return a positive integer, otherwise return -1.
 *
 * Example:
 * - h = 3, bounce = 0.66, window = 1.5, result is 3
 * - h = 3, bounce = 1, window = 1.5, result is -1
 */
public class BouncingBall {
    public static int bouncingBall(double h, double bounce, double window) {
        if(h<0 || bounce<=0 || bounce>=1 || window>=h)
            return -1;

        int bounceTimesSeen = 0;

        Ball palla = new Ball(bounce, h);
        while(palla.getMaxH() > window){
            palla.letItBounce();
            bounceTimesSeen++;
            if (palla.getMaxH() > window)
                bounceTimesSeen++;
        }
        return bounceTimesSeen;
    }
}


class Ball{
    double bounce;
    double maxH;

    Ball(double bounce, double maxH){
        this.bounce = bounce;
        this.maxH = maxH;
    }

    public double getMaxH() {
        return maxH;
    }

    void letItBounce(){
        this.maxH *= this.bounce;
    }
}


class BouncingBallsTest{
    public static void main(String[] args) {
        Ball palla = new Ball( 0.66, 3);
        System.out.println("TESTING 'Ball' Object" + palla.getMaxH());
        System.out.println("La palla ora si trova a " + palla.getMaxH());
        System.out.println("La palla rimbalza...");
        palla.letItBounce();
        System.out.println("La palla ora si trova a " + palla.getMaxH());
        System.out.println("La palla rimbalza...");
        palla.letItBounce();
        System.out.println("La palla ora si trova a " + palla.getMaxH()+"\n");

        System.out.println("_______________________\nTESTING bouncingBall(1, 0.66, 1.5)");
        System.out.println(BouncingBall.bouncingBall(1, 0.66, 1.5));
        System.out.println("_______________________\nTESTING bouncingBall(3, 0.66, 1.5)");
        System.out.println(BouncingBall.bouncingBall(3, 0.66, 1.5));
        System.out.println("_______________________\nTESTING bouncingBall(30, 0.66, 1.5)");
        System.out.println(BouncingBall.bouncingBall(30, 0.66, 1.5));

    }
}