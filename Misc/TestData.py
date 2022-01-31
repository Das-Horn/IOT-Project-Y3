import mysql.connector

mydb = mysql.connector.connect(
  host="10.147.19.13",
  user="admin",
  password="Mufcmufc@1",
  database="iotProject"
)

mycursor = mydb.cursor()

sql = "INSERT INTO SensorData (MC, DataType, Data, Room) VALUES (%s, %s, %s, %s)"
val = ("1", "Temp", "20", "1")
mycursor.execute(sql, val)

mydb.commit()

print(mycursor.rowcount, "record inserted.")
print("ID:", mycursor.lastrowid)
