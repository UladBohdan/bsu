package by.bsu.famcs.uladbohdan.exam;

import org.xml.sax.*;
import org.xml.sax.helpers.*;
import javax.swing.*;

/** A SAX parser handler that keeps track of the number
 *  of copies of Core Web Programming ordered. Entries
 *  that look like this will be recorded:
 *  <XMP>
 *    ...
 *    <count>23</count>
 *    <book>
 *      <isbn>0130897930</isbn>
 *      ...
 *    </book>
 *  </XMP>
 *  All other entries will be ignored -- different books,
 *  orders for yachts, things that are not even orders, etc.
 *

 */

public class CountHandler extends DefaultHandler {
    private boolean collectCount = false;
    private boolean collectISBN = false;
    private int currentCount = 0;
    private int totalCount = 0;

    /** If you start the "count" or "isbn" elements,
     *  set a flag so that the characters method can check
     *  the value of the tag body.
     */

    @Override
    public void startElement(String namespaceUri,
                             String localName,
                             String qualifiedName,
                             Attributes attributes)
            throws SAXException {
        if (qualifiedName.equals("count")) {
            collectCount = true;
            currentCount = 0;
        } else if (qualifiedName.equals("isbn")) {
            collectISBN = true;
        }
    }

    /** If you end the "count" or "isbn" elements,
     *  set a flag so that the characters method will no
     *  longer check the value of the tag body.
     */

    @Override
    public void endElement(String namespaceUri,
                           String localName,
                           String qualifiedName)
            throws SAXException {
        if (qualifiedName.equals("count")) {
            collectCount = false;
        } else if (qualifiedName.equals("isbn")) {
            collectISBN = false;
        }
    }

    /** Since the "count" entry comes before the "book"
     *  entry (which contains "isbn"), we have to temporarily
     *  record all counts we see. Later, if we find a
     *  matching "isbn" entry, we will record that temporary
     *  count.
     */

    @Override
    public void characters(char[] chars,
                           int startIndex,
                           int length) {
        if (collectCount || collectISBN) {
            String dataString =
                    new String(chars, startIndex, length).trim();
            if (collectCount) {
                try {
                    currentCount = Integer.parseInt(dataString);
                } catch(NumberFormatException nfe) {
                    System.err.println("Ignoring malformed count: " +
                            dataString);
                }
            } else if (collectISBN) {
                if (dataString.equals("0130897930")) {
                    totalCount = totalCount + currentCount;
                }
            }
        }
    }

    /** Report the total number of copies ordered.
     *  Gently chide underachievers.
     */

    @Override
    public void endDocument() throws SAXException {
        String message =
                "You ordered " + totalCount + " copies of \n" +
                        "Core Web Programming Second Edition.\n";
        if (totalCount < 250) {
            message = message + "Please order more next time!";
        } else {
            message = message + "Thanks for your order.";
        }
        JOptionPane.showMessageDialog(null, message);
    }
}