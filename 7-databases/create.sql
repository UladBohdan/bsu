DROP TABLE buildings;
DROP TABLE areas;
DROP TABLE metrics;
DROP TABLE discounts;
DROP TABLE phone_numbers;
DROP TABLE transactions;
DROP TABLE tax_payments;
DROP TABLE gardeners;
DROP TABLE costs;

CREATE TABLE gardeners (
  id NUMBER PRIMARY KEY,
  first_name VARCHAR2(200) NOT NULL,
  middle_name VARCHAR2(200),
  last_name VARCHAR2(200) NOT NULL,
  address VARCHAR2(200),
  status VARCHAR2(200),

  CONSTRAINT status_check CHECK (status in ('adult', 'senior')) ENABLE
);

CREATE TABLE areas (
  id NUMBER PRIMARY KEY,
  gardener_id NUMBER NOT NULL,
  site_number VARCHAR2(10) NOT NULL UNIQUE,
  square NUMBER NOT NULL,

  CONSTRAINT area_square_check CHECK (square<=2000) ENABLE,

  CONSTRAINT areas_fk_gardener
    FOREIGN KEY (gardener_id)
    REFERENCES gardeners(id)
);

CREATE TABLE buildings (
  id NUMBER PRIMARY KEY,
  area_id NUMBER NOT NULL,
  purpose VARCHAR2(200) NOT NULL,
  material VARCHAR2(200) NOT NULL,
  square NUMBER NOT NULL,

  CONSTRAINT building_square_check CHECK (square<=500) ENABLE,

  CONSTRAINT purpose_check CHECK
    (purpose in ('living', 'storage', 'garage')) ENABLE,
  CONSTRAINT material_check CHECK
    (material in ('wood', 'bricks', 'stone')) ENABLE,
  CONSTRAINT building_fk_area
    FOREIGN KEY (area_id)
    REFERENCES areas(id)
);

CREATE TABLE phone_numbers (
  id NUMBER PRIMARY KEY,
  gardener_id NUMBER NOT NULL,
  value VARCHAR2(200) NOT NULL,

  CONSTRAINT phone_number_fk_gardener
    FOREIGN KEY (gardener_id)
    REFERENCES gardeners(id)
);

CREATE TABLE metrics (
  id NUMBER PRIMARY KEY,
  gardener_id NUMBER NOT NULL,
  type VARCHAR2(200) NOT NULL,
  value NUMBER NOT NULL,
  metric_date DATE NOT NULL,

  CONSTRAINT metrics_type_check CHECK (type in ('electricity', 'water')) ENABLE,

  CONSTRAINT metric_fk_gardener
    FOREIGN KEY (gardener_id)
    REFERENCES gardeners(id)
);

CREATE TABLE tax_payments (
  id NUMBER PRIMARY KEY,
  name VARCHAR2(200) NOT NULL,
  period VARCHAR2(200) NOT NULL,
  period_start DATE NOT NULL,

  CONSTRAINT period_check CHECK (period in ('month', 'year')) ENABLE,
  CONSTRAINT name_check CHECK (name in ('annual', 'area', 'property',
    'electricity', 'water')) ENABLE
);

CREATE TABLE discounts (
  id NUMBER PRIMARY KEY,
  subject_status VARCHAR2(30) NOT NULL,
  type VARCHAR2(200) NOT NULL,
  value NUMBER NOT NULL,
  tax_payment_id NUMBER NOT NULL,

  CONSTRAINT discount_type_check CHECK (type in ('percentage', 'value')) ENABLE,
  CONSTRAINT subject_status_check CHECK
    (subject_status in ('adult', 'senior', 'any')) ENABLE,
  CONSTRAINT tax_payment_fk_gardener
    FOREIGN KEY (tax_payment_id)
    REFERENCES tax_payments(id)
);

CREATE TABLE transactions (
  id NUMBER PRIMARY KEY,
  tax_payment_id NUMBER NOT NULL,
  gardener_id NUMBER NOT NULL,
  transaction_date DATE NOT NULL,
  amount NUMBER NOT NULL,

  CONSTRAINT transaction_amount_check CHECK (amount<=10000) ENABLE,

  CONSTRAINT transaction_fk_gardener
    FOREIGN KEY (gardener_id)
    REFERENCES gardeners(id),

  CONSTRAINT transaction_fk_tax_payment
    FOREIGN KEY (tax_payment_id)
    REFERENCES tax_payments(id)
);

CREATE TABLE costs (
  id NUMBER PRIMARY KEY,
  type VARCHAR2(200) NOT NULL,
  value NUMBER,

  CONSTRAINT cost_type_check CHECK (type in ('annual', 'area', 'property-wood',
    'property-bricks', 'property-stone', 'electricity', 'water')) ENABLE
);
