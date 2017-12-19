-- id / first_name / middle_name / last_name / address / status
INSERT INTO gardeners VALUES (1, 'Frieda', 'Robscheit', 'Robbins', 'Belarus, Minsk', 'adult');
INSERT INTO gardeners VALUES (2, 'Geraldine', NULL, 'Seydoux', 'USA, New York', 'adult');
INSERT INTO gardeners VALUES (3, 'Francishak', NULL, 'Skaryna', 'Belarus, Polacak, vul. Vilienskaja', 'senior');
INSERT INTO gardeners VALUES (4, 'Jocelyn', 'Bell', 'Burnell', 'Europe, Sweden', 'senior');
INSERT INTO gardeners VALUES (5, 'Lise', NULL, 'Meitner', 'Poland, Warsaw', 'adult');
INSERT INTO gardeners VALUES (6, 'Maria', NULL, 'Mitchell', 'USA, CA, San Francisco', 'adult');
INSERT INTO gardeners VALUES (7, 'Max', NULL, 'Planck', 'Germany, Kiel', 'senior');
INSERT INTO gardeners VALUES (8, 'Polly', NULL, 'Matzinger', 'France, Paris', 'senior');
INSERT INTO gardeners VALUES (9, 'Rosalind', NULL, 'Franklin', 'Notting Hill, London, United Kingdom', 'senior');
INSERT INTO gardeners VALUES (10, 'Stephen', NULL, 'Hawking', 'Oxford, United Kingdom', 'senior');
COMMIT;

-- id / gardener_id / site_number / square
INSERT INTO areas VALUES(1, 1, '12', 200);
INSERT INTO areas VALUES(2, 2, '17', 450);
INSERT INTO areas VALUES(3, 3, '18', 600);
INSERT INTO areas VALUES(4, 4, '19a', 300);
INSERT INTO areas VALUES(5, 4, '19b', 750);
INSERT INTO areas VALUES(6, 5, '23', 120);
INSERT INTO areas VALUES(7, 6, '25', 480);
INSERT INTO areas VALUES(8, 7, '26', 450);
INSERT INTO areas VALUES(9, 7, '27', 230);
INSERT INTO areas VALUES(10, 8, '28', 270);
INSERT INTO areas VALUES(11, 9, '29', 315);
INSERT INTO areas VALUES(12, 10, '29/2', 410);
COMMIT;

-- id / area_id / purpose / material / square
INSERT INTO buildings VALUES(1, 1, 'living', 'wood', 120);
INSERT INTO buildings VALUES(2, 1, 'garage', 'bricks', 25);
INSERT INTO buildings VALUES(3, 1, 'storage', 'bricks', 30);
INSERT INTO buildings VALUES(4, 2, 'living', 'stone', 150);
INSERT INTO buildings VALUES(5, 3, 'garage', 'wood', 30);
INSERT INTO buildings VALUES(6, 4, 'storage', 'bricks', 34);
INSERT INTO buildings VALUES(7, 5, 'living', 'wood', 200);
INSERT INTO buildings VALUES(8, 6, 'living', 'bricks', 180);
INSERT INTO buildings VALUES(9, 7, 'garage', 'bricks', 15);
INSERT INTO buildings VALUES(10, 7, 'living', 'wood', 210);
INSERT INTO buildings VALUES(11, 8, 'living', 'bricks', 130);
INSERT INTO buildings VALUES(12, 9, 'living', 'bricks', 80);
INSERT INTO buildings VALUES(13, 10, 'living', 'wood', 130);
INSERT INTO buildings VALUES(14, 11, 'living', 'wood', 170);
INSERT INTO buildings VALUES(15, 12, 'storage', 'bricks', 60);
COMMIT;

-- id / gardener_id / value
INSERT INTO phone_numbers VALUES(1, 1, '+375291234567');
INSERT INTO phone_numbers VALUES(2, 1, '+152163256327');
INSERT INTO phone_numbers VALUES(3, 3, '+232138473275');
INSERT INTO phone_numbers VALUES(4, 5, '+432432875483');
INSERT INTO phone_numbers VALUES(5, 7, '+342643728432');
INSERT INTO phone_numbers VALUES(6, 7, '+344327839243');
INSERT INTO phone_numbers VALUES(7, 9, '+447834927432');
INSERT INTO phone_numbers VALUES(8, 10, '+437284324822');
COMMIT;

-- id / gardener_id / type / value / metric_date
INSERT INTO metrics VALUES(1, 1, 'electricity', 100, to_date('01-07-2017', 'dd-mm-yyyy'));
INSERT INTO metrics VALUES(2, 1, 'water', 17, to_date('17-07-2017', 'dd-mm-yyyy'));
INSERT INTO metrics VALUES(3, 2, 'electricity', 83, to_date('19-07-2017', 'dd-mm-yyyy'));
INSERT INTO metrics VALUES(4, 3, 'water', 19, to_date('25-07-2017', 'dd-mm-yyyy'));
INSERT INTO metrics VALUES(5, 4, 'electricity', 44, to_date('28-07-2017', 'dd-mm-yyyy'));
INSERT INTO metrics VALUES(6, 5, 'water', 23, to_date('30-07-2017', 'dd-mm-yyyy'));
INSERT INTO metrics VALUES(7, 6, 'electricity', 61, to_date('01-08-2017', 'dd-mm-yyyy'));
INSERT INTO metrics VALUES(8, 6, 'water', 22, to_date('05-08-2017', 'dd-mm-yyyy'));
INSERT INTO metrics VALUES(9, 7, 'electricity', 73, to_date('08-08-2017', 'dd-mm-yyyy'));
INSERT INTO metrics VALUES(10, 8, 'water', 19, to_date('09-08-2017', 'dd-mm-yyyy'));
INSERT INTO metrics VALUES(11, 9, 'electricity', 98, to_date('09-08-2017', 'dd-mm-yyyy'));
INSERT INTO metrics VALUES(12, 10, 'water', 24, to_date('11-08-2017', 'dd-mm-yyyy'));
COMMIT;

-- id / name / period / period_start / amount
INSERT INTO tax_payments VALUES(1, 'annual', 'year', to_date('01-01-2017', 'dd-mm-yyyy'), 7000);
INSERT INTO tax_payments VALUES(2, 'area', 'year', to_date('01-01-2017', 'dd-mm-yyyy'), 6000);
INSERT INTO tax_payments VALUES(3, 'property', 'year', to_date('01-01-2017', 'dd-mm-yyyy'), 8300);
INSERT INTO tax_payments VALUES(4, 'electricity', 'month', to_date('01-10-2017', 'dd-mm-yyyy'), 100);
INSERT INTO tax_payments VALUES(5, 'water', 'month', to_date('01-10-2017', 'dd-mm-yyyy'), 50);
INSERT INTO tax_payments VALUES(6, 'electricity', 'month', to_date('01-11-2017', 'dd-mm-yyyy'), 102);
INSERT INTO tax_payments VALUES(7, 'water', 'month', to_date('01-11-2017', 'dd-mm-yyyy'), 51);
COMMIT;

-- id / subject_status / type / value / tax_payment_id
INSERT INTO discounts VALUES(1, 'senior', 'percentage', 100, 2);
INSERT INTO discounts VALUES(2, 'senior', 'percentage', 50, 3);
COMMIT;

-- id / tax_payment_id / gardener_id / transaction_date / amount
INSERT INTO transactions VALUES(1, 1, 1, to_date('15-07-2017', 'dd-mm-yyyy'), 1500);
INSERT INTO transactions VALUES(2, 2, 1, to_date('17-07-2017', 'dd-mm-yyyy'), 2314);
INSERT INTO transactions VALUES(3, 3, 1, to_date('19-07-2017', 'dd-mm-yyyy'), 1100);
INSERT INTO transactions VALUES(4, 4, 1, to_date('23-07-2017', 'dd-mm-yyyy'), 893);
INSERT INTO transactions VALUES(5, 5, 1, to_date('25-07-2017', 'dd-mm-yyyy'), 123);
INSERT INTO transactions VALUES(6, 1, 1, to_date('30-07-2017', 'dd-mm-yyyy'), 1743);
INSERT INTO transactions VALUES(7, 2, 1, to_date('01-08-2017', 'dd-mm-yyyy'), 1500);
INSERT INTO transactions VALUES(8, 3, 1, to_date('02-08-2017', 'dd-mm-yyyy'), 1400);
INSERT INTO transactions VALUES(9, 4, 1, to_date('07-08-2017', 'dd-mm-yyyy'), 1300);
INSERT INTO transactions VALUES(10, 5, 1, to_date('07-08-2017', 'dd-mm-yyyy'), 1222);
INSERT INTO transactions VALUES(11, 1, 1, to_date('07-08-2017', 'dd-mm-yyyy'), 998);
INSERT INTO transactions VALUES(12, 2, 1, to_date('09-08-2017', 'dd-mm-yyyy'), 875);
COMMIT;

-- id / type / value
INSERT INTO costs VALUES(1, 'annual', 17);
INSERT INTO costs VALUES(2, 'area', 2);
INSERT INTO costs VALUES(3, 'property-wood', 3);
INSERT INTO costs VALUES(4, 'property-bricks', 4);
INSERT INTO costs VALUES(5, 'property-stone', 4);
INSERT INTO costs VALUES(6, 'electricity', 11);
INSERT INTO costs VALUES(7, 'water', 9);
COMMIT;

SELECT * FROM gardeners;
SELECT * FROM buildings;
SELECT * FROM areas;
SELECT * FROM metrics;
SELECT * FROM discounts;
SELECT * FROM phone_numbers;
SELECT * FROM transactions;
SELECT * FROM tax_payments;
SELECT * FROM costs;
