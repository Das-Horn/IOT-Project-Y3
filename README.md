# IOT-Project-Y3
The repo for all code for our IOT College project

# Zerotier Network details
Below the details to join the network as well as IP assignments can be found about the network used for this project.

  

## IP Assignments
|Device| IP Address  |
|--|--|
| Raspberry Pi |  ....... |
|Reverse Proxy| ...... |

## PHPMYADMIN Login and connection Guide
URL: **....../phpmyadmin**

| Username | Password |
|--|--|
| admin |  ....... |


## Connection Guide to Raspberry Pi
To connect to the raspberry pi you will need the [zerotier](https://www.zerotier.com/download/) software. After setting this up create an account and join the network. The join code for the IOT project network is Removed. Once you join the network you should be able to connect to the pi using SSH and the IP Address listed above.

|Login| Details  |
|--|--|
| Username | pi |
| Password | ...... |

The command should be like this:

    ssh pi@......
Then enter the password above when prompted.

# Reverse Proxy
The reverse proxy is a cloud VM using the following software configured in a certain way to act as a reverse proxy for the database. This was done to allow outside connections to access the database.

## Software list
- Zerotier-cli
- Python
- Nginx

# Materials Used
## Service
**Vercel** is used to host the website for this project this can be accessed [here](https://iot-project-y3.vercel.app/).

## Devices

- ESP-32
- Raspberry pi  
- Cloud VM (Google Cloud)
  

## Sensors
- PIR motion sensor
- DHT 11 sensor
- Smoke sensor
- Shock sensor

# Graphs
Store pin graphs and charts here l8r

-  [DB Graph](https://app.dbdesigner.net/designer/schema/492615)

# References
-  [Next JS Docs](https://nextjs.org/docs)
-  [React Documentation](https://reactjs.org/docs/getting-started.html)
-  [Websocket Info ESP32](https://youtu.be/_Z9Axfh6AEU)
-  [Sequelize Docs](https://sequelize.org/v7/manual/model-querying-basics.html)
- [Prisma Docs](https://www.prisma.io/docs/)
