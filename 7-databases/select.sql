-- 1. List of gardeners owning at least two areas.
BEGIN
    DBMS_OUTPUT.PUT_LINE('Gardeners owing at least two areas: ');
END;
/
SELECT first_name, middle_name, last_name
FROM gardeners
JOIN (SELECT gardener_id FROM areas GROUP BY gardener_id HAVING COUNT(id) >= 2)
ON (gardeners.id = gardener_id);

-- 2. Debts by surname.
CREATE OR REPLACE FUNCTION calculateDebts(surname in VARCHAR2)
RETURN INTEGER IS
    debt INTEGER := 0;
    paid INTEGER := 0;
    shouldPay INTEGER := 0;
BEGIN
    SELECT SUM(amount) INTO paid FROM transactions
        WHERE gardener_id = (SELECT UNIQUE id FROM gardeners WHERE last_name = surname);
    SELECT SUM(amount) INTO shouldPay FROM tax_payments;
    debt := shouldPay - paid;
    RETURN debt;
END;
/
DECLARE
    debtsLevel REAL;
BEGIN
    debtsLevel := calculateDebts('Robbins');
    DBMS_OUTPUT.PUT_LINE('Debts: ' || debtsLevel);
END;

-- 3. The total sum of payments.
BEGIN
    DBMS_OUTPUT.PUT_LINE('Total amount of transactions:');
END;
/
SELECT SUM(amount) FROM transactions;
