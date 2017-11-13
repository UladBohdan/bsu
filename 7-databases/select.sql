-- 1. List of gardeners owning at least two areas.
SELECT first_name, middle_name, last_name
FROM gardeners
JOIN (SELECT gardener_id FROM areas GROUP BY gardener_id HAVING COUNT(id) >= 2)
ON (gardeners.id = gardener_id);

-- 2. Debts by surname.

-- 3. The total sum of payments.
SELECT SUM(amount) FROM transactions;
