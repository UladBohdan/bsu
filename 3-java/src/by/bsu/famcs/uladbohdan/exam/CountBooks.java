package by.bsu.famcs.uladbohdan.exam;

import javax.xml.parsers.*;
import org.xml.sax.helpers.*;

/** A program using SAX to keep track of the number
 *  of copies of Core Web Programming ordered. Entries
 *  that look like this will be recorded:
 * <XMP>
 *    ...
 *    <count>23</count>
 *    <book>
 *      <isbn>0130897930</isbn>
 *      ...
 *    </book>
 *
 *  </XMP>
 * All other entries will be ignored -- different books,
 *  orders for yachts, things that are not even orders, etc.
 *

 */

public class CountBooks {
    public static void main(String[] args) {

        String filename = "test.xml";
        countBooks(filename);
        System.exit(0);
    }

    private static void countBooks(String filename) {
        DefaultHandler handler = new CountHandler();
        SAXParserFactory factory = SAXParserFactory.newInstance();
        try {
            SAXParser parser = factory.newSAXParser();
            parser.parse(filename, handler);
        } catch(Exception e) {
            String errorMessage =
                    "Error parsing " + filename + ": " + e;
            System.err.println(errorMessage);
            e.printStackTrace();
        }
    }
}
