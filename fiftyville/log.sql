-- Existing tables
.table

-- tables schema
.schema

-- Specific reports from the known date and place of robbery (July 28 2023 on Humphrey Street)
SELECT * FROM crime_scene_reports WHERE day = 28 AND month = 7 AND year = 2023 AND street = 'Humphrey Street';

-- Interviews transcript from the day of the robbery
SELECT * FROM interviews WHERE day = 28 AND month = 7 AND year = 2023;

-- Ruth: car left from the bakery within 10 minutes after the theft
-- Eugene: early in the day thief was seen withdrawing money from and ATM on Leggett Street
-- Raymond: Thief was talking on the phone for less than a minute. Was heard that the thief was planning to take the earliest flight out of Fiftyville the next day.
--            Thief told the accomplice to buy the tickets.

-- Security logs from the day and time of the robbery (10:15am)
.schema bakery_security_logs
SELECT * FROM bakery_security_logs WHERE day = 28 AND month = 7 AND year = 2023 AND hour = 10;

-- Suspect 1 license_plate = 5P2BI95 (exit min 16)
-- Suspect 2 license_plate = 94KL13X (exit min 18)
-- Suspect 3 license_plate = 6P58WS2 (exit min 18)
-- Suspect 4 license_plate = 4328GD8 (exit min 19)
-- Suspect 5 license_plate = G412CB7 (exit min 20)
-- Suspect 6 license_plate = L93JTIZ (exit min 21)
-- Suspect 7 license_plate = 322W7JE (exit min 23)
-- Suspect 8 license_plate = 0NTHK55 (exit min 23)

-- ATM transactions on Leggett Street on the day of the robbery
.schema atm_transactions
SELECT * FROM atm_transactions WHERE day = 28 AND month = 7 AND year = 2023 AND atm_location = 'Leggett Street';

-- Suspect 1 account_number = 28500762 (amount 48)
-- Suspect 2 account_number = 28296815 (amount 20)
-- Suspect 3 account_number = 76054385 (amount 60)
-- Suspect 4 account_number = 49610011 (amount 50)
-- Suspect 5 account_number = 16153065 (amount 80)
-- Suspect 6 account_number = 25506511 (amount 20)
-- Suspect 7 account_number = 81061156 (amount 30)
-- Suspect 8 account_number = 26013199 (amount 35)

-- Phone call on the day of the robbery that lasted less then a minute
.schema phone_calls
SELECT * FROM phone_calls WHERE day = 28 AND month = 7 AND year = 2023 AND duration < 60;

-- Suspect 1 phone_calls: caller = (130) 555-0289 || receiver = (996) 555-8899 (duration 51)
-- Suspect 2 phone_calls: caller = (499) 555-9472 || receiver = (892) 555-8872 (duration 36)
-- Suspect 3 phone_calls: caller = (367) 555-5533 || receiver = (375) 555-8161 (duration 45)
-- Suspect 4 phone_calls: caller = (499) 555-9472 || receiver = (717) 555-1342 (duration 50)
-- Suspect 5 phone_calls: caller = (286) 555-6063 || receiver = (676) 555-6554 (duration 43)
-- Suspect 6 phone_calls: caller = (770) 555-1861 || receiver = (725) 555-3243 (duration 49)
-- Suspect 7 phone_calls: caller = (031) 555-6622 || receiver = (910) 555-3251 (duration 38)
-- Suspect 8 phone_calls: caller = (826) 555-1652 || receiver = (066) 555-9701 (duration 55)
-- Suspect 9 phone_calls: caller = (338) 555-6650 || receiver = (704) 555-2131 (duration 54)

-- schema for people and bank_accounts
.schema people
.schema bank_accounts

-- search and compare phone numbers and license plates to find names of suspects
SELECT id, name, passport_number, license_plate FROM people
    WHERE phone_number IN ('(130) 555-0289', '(499) 555-9472', '(367) 555-5533', '(499) 555-9472', '(286) 555-6063', '(770) 555-1861', '(031) 555-6622', '(826) 555-1652', '(338) 555-6650')
    AND license_plate IN ('5P2BI95', '94KL13X', '6P58WS2', '4328GD8', 'G412CB7', 'L93JTIZ', '322W7JE', '0NTHK55');

-- Suspect 1: name = Sofia || passport_number = 1695452385 || license_plate = G412CB7 || phone_number = (130) 555-0289 || id = 398010
-- Suspect 2: name = Kelsey || passport_number = 8294398571 || license_plate = 0NTHK55 || phone_number = (499) 555-9472 || id = 560886
-- Suspect 3: name = Bruce || passport_number = 5773159633 || license_plate = 94KL13X || phone_number = (367) 555-5533 || id = 686048
-- Suspect 4: name = Diana || passport_number = 3592750733 || license_plate = 322W7JE || phone_number = (770) 555-1861 || id = 514354

-- serching bank accounts with the account numbers from the ATM on Leggett Street
SELECT * FROM bank_accounts JOIN people ON people.id = bank_accounts.person_id
    WHERE account_number IN ('28500762', '28296815', '76054385', '49610011', '16153065', '25506511', '81061156', '26013199')
    AND id IN ('398010', '560886', '686048', '514354');

-- Final suspects:
-- Suspect 1: name = Bruce || passport_number = 5773159633 || license_plate = 94KL13X || phone_number = (367) 555-5533 || id = 686048 || account_number = 49610011
-- Suspect 2: name = Diana || passport_number = 3592750733 || license_plate = 322W7JE || phone_number = (770) 555-1861 || id = 514354 || account_number = 26013199

-- accomplice name and other details
SELECT * FROM people WHERE phone_number = '(725) 555-3243';
-- bank account for accomplice
SELECT * FROM bank_accounts JOIN people ON people.id = bank_accounts.person_id WHERE id IN ('864400', '847116');

--Accomplice (suspect Bruce) suspect 1: name = Robin || passport_number = NULL || license_plate = 4V16VO0 || phone_number = (375) 555-8161 || id = 864400 || account_number = 94751264
--Accomplice (suspect Diana) suspect 2: name = Philip || passport_number = 3391710505 || license_plate = GW362R6 || phone_number = (725) 555-3243 || id = 847116 || account_number = 47746428

-- schema for airports, flights, passengers
.schema airports
.schema flights
.schema passengers

--All flights from Fiftyville in the morning (before 12) the day after the robbery
SELECT * FROM passengers
    JOIN flights ON passengers.flight_id = flights.id
        WHERE origin_airport_id = (SELECT id from airports WHERE city = 'Fiftyville')
        AND day = 29 AND month = 7 AND year = 2023 AND hour < 12
        AND passport_number IN ('3592750733', '5773159633');

-- Flights: flight_id = 36 || passport_number = 5773159633 || id = 36 || origin_airport_id = 8 (Fiftyville) || destination_airport_id = 4 (New York City) ||  hour = 8 || minute = 20
-- Thief = Bruce
-- Accomplice = Robin

-- plane destination for thiefs flight
SELECT city FROM airports WHERE id = 4;
