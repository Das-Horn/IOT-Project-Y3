INSERT INTO `MC identities` (MCName, MCIP) VALUES ("TestingSet1", "127.0.0.1");

--@block insert with foreign KEY

INSERT INTO MCEntries(SensorsCount,LastEntry,TotalEntries,MC)
SELECT 1,NOW(),0,MCKey
  FROM `MC identities`
 WHERE MCName = 'TestingSet2'
 LIMIT 1;

INSERT INTO (SensorsCount,LastEntry,TotalEntries,MC)
SELECT 1,NOW(),0,MCKey
  FROM `MC identities`
 WHERE MCName = 'TestingSet2'
 LIMIT 1;

--@block show table column names

SELECT COLUMN_NAME 
FROM INFORMATION_SCHEMA.COLUMNS 
WHERE 
    TABLE_SCHEMA = Database()
AND TABLE_NAME = '' ;