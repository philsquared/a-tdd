DROP VIEW IF EXISTS flights_taken_by;
DROP TABLE IF EXISTS flights_taken;
DROP TABLE IF EXISTS flight;
DROP TABLE IF EXISTS member;


DROP TABLE IF EXISTS member;
CREATE TABLE member (
    username TEXT PRIMARY KEY,
    password TEXT NOT NULL,
    name TEXT,
    email TEXT,
    data JSONB
);

DROP TABLE IF EXISTS flight;
CREATE TABLE flight (
    id SERIAL PRIMARY KEY,
    origin TEXT NOT NULL,
    destination TEXT NOT NULL,
    mileage INTEGER,
    airline TEXT NOT NULL,
    number INTEGER NOT NULL
);

DROP TABLE IF EXISTS flights_taken;
CREATE TABLE flights_taken (
    flight_id SERIAL PRIMARY KEY,
    member_id TEXT NOT NULL,
    date_taken TIMESTAMP NOT NULL
);

DROP VIEW IF EXISTS flights_taken_by;
CREATE VIEW flights_taken_by AS
    select m.username
    from member m
        inner join flights_taken ft on ft.member_id = m.username
        inner join flight f on ft.flight_id = f.id;
