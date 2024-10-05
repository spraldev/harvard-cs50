-- Keep a log of any SQL queries you execute as you solve the mystery.

/*
Suspects:

*/

-- Grabbing the crime:
SELECT * FROM crime_scene_reports WHERE month = 7 AND day = 28 AND street = "Humphrey Street";

--Get interviews from the day
SELECT * FROM interviews WHERE month = 7 AND day = 28;

-- Get atm transactions for the day
SELECT * from atm_transactions WHERE month = 7 AND day = 28 AND atm_location = "Leggett Street";

-- Get phone calls on that day
SELECT * FROM phone_calls WHERE day = 28 AND month = 7 AND duration < 60;

-- Get the nearest flight
 SELECT * FROM flights WHERE day = 29 AND month = 7;

-- Get the passengers on that flight
SELECT * FROM passengers WHERE flight_id = 36;


-- Final querty
SELECT name FROM people INNER JOIN phone_calls ON people.phone_number = phone_calls.caller INNER JOIN bank_accounts ON people.id = bank_accounts.person_id INNER JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number INNER JOIN passengers ON people.passport_number = passengers.passport_number WHERE atm_transactions.month = 7 AND atm_transactions.day = 28 AND atm_transactions.atm_location = "Leggett Street" AND phone_calls.day = 28 AND phone_calls.MONTH = 7 AND phone_calls.duration < 60;
