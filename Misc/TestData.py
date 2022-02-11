import mysql.connector
import time
import random

mydb = mysql.connector.connect(
  host="10.147.19.13",
  user="craig",
  password="mufcmufc",
  database="iotProject"
)

mycursor = mydb.cursor()

sql = "INSERT INTO SensorData (MC, DataType, Data , SensorID) VALUES (%s, %s, %s, %s)"

while True:
    i = str(random.randrange(0, 40))
    val = ("1", "Temp", i, "1")
    mycursor.execute(sql, val)
    mydb.commit()

    print(mycursor.rowcount, "record inserted.")
    print("ID:", mycursor.lastrowid)

    i = str(random.randrange(10, 100))
    val = ("1", "Humid", i, "1")
    mycursor.execute(sql, val)
    mydb.commit()

    print(mycursor.rowcount, "record inserted.")
    print("ID:", mycursor.lastrowid)
    time.sleep(3)
