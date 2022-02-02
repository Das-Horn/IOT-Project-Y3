
# Web server Documentation
## Data types in database

|Data Type| Data Name |
|--|--|
| Float | Temperature |
| Float | Humidity |
| Binary | Actions |
| Float | ?? Light ?? |
| Boolean | Motion Sensor|

  

## API Data return example

  You will get two types of responses from the API depending on the type of request. When posting data to the table you will see a response similar to this : 
  

    1 | Temp | 32 | 4
 
This response will  send back all the variables give to the table in plain text upon success. The other response is for when you are receiving data from the Database through the API. This will come in a format similar to this. 

    [{"MC":1,"DataType":"Temp","Data":"32","TimeStamp":"10:44:05","DataKey":123,"SensorID":4},{"MC":1,"DataType":"Temp","Data":"29","TimeStamp":"10:49:27","DataKey":124,"SensorID":1},{"MC":1,"DataType":"Temp","Data":"29","TimeStamp":"10:49:28","DataKey":125,"SensorID":1},{"MC":1,"DataType":"Temp","Data":"35","TimeStamp":"10:49:29","DataKey":126,"SensorID":1},{"MC":1,"DataType":"Temp","Data":"2","TimeStamp":"10:49:30","DataKey":127,"SensorID":1},{"MC":1,"DataType":"Temp","Data":"20","TimeStamp":"10:49:31","DataKey":128,"SensorID":1},{"MC":1,"DataType":"Temp","Data":"38","TimeStamp":"10:49:33","DataKey":129,"SensorID":1},{"MC":1,"DataType":"Temp","Data":"30","TimeStamp":"10:49:34","DataKey":130,"SensorID":1},{"MC":1,"DataType":"Temp","Data":"34","TimeStamp":"10:49:35","DataKey":131,"SensorID":1},{"MC":1,"DataType":"Temp","Data":"38","TimeStamp":"10:49:36","DataKey":132,"SensorID":1},{"MC":1,"DataType":"Temp","Data":"21","TimeStamp":"10:49:37","DataKey":133,"SensorID":1},{"MC":1,"DataType":"Temp","Data":"5","TimeStamp":"10:49:38","DataKey":134,"SensorID":1},{"MC":1,"DataType":"Temp","Data":"26","TimeStamp":"10:49:40","DataKey":135,"SensorID":1},{"MC":1,"DataType":"Temp","Data":"29","TimeStamp":"10:49:41","DataKey":136,"SensorID":1},{"MC":1,"DataType":"Temp","Data":"7","TimeStamp":"10:49:42","DataKey":137,"SensorID":1},{"MC":1,"DataType":"Temp","Data":"33","TimeStamp":"10:49:43","DataKey":138,"SensorID":1},{"MC":1,"DataType":"Temp","Data":"23","TimeStamp":"10:49:44","DataKey":139,"SensorID":1},{"MC":1,"DataType":"Temp","Data":"17","TimeStamp":"10:49:46","DataKey":140,"SensorID":1}]
   As you can see this Data comes in an array containing a JSON Object for each row in the table.

## API DB update docs

The update section of the database is used to update the database with new information from the sensors on the arduino.

There are two sections of the Database that can be updated, These are the Data table and the Jobs. However it should be noted that the Table API only creates new entries where as the Jobs API can only update existing entries in the table.

 - Example for Data entry : **URL/api/Update/Data/MC/DataType/Data/SensorID**
 - Example for Jobs entry : **URL/api/Update/jobs/SensorID/Action**

A list of compatible data types can be found below.

- INT : integer

- STR : string

- FLT : float

- BIN : binary
