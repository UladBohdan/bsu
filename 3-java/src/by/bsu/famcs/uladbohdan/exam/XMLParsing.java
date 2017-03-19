package by.bsu.famcs.uladbohdan.exam;

import org.xml.sax.*;
import javax.xml.parsers.*;
import org.w3c.dom.*;
import java.lang.annotation.*;
import java.util.Iterator;

@Target(value=ElementType.FIELD)
@Retention(value=RetentionPolicy.SOURCE)
@interface MyAnnotation {
    public int value();
    public String str() default "hello";
}

public class XMLParsing {

    public static void main(String[] args) {
        int[] arr = new int[] {5,4,9,4,5,4,3,3};
        System.out.println(methodOne(arr));



    }

    static int methodOne(int... x) {
        int sum = 0;
        for (int i: x)
            sum+=i;
        return sum;
    }

    @MyAnnotation(value = 0, str = "hi")
    private int x = 65;
    int a7;

}