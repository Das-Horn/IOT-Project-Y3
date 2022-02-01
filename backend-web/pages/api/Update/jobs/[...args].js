import { Sequelize,DataTypes } from 'sequelize';



export default async function handler(req, res) {
    // Code to get the api variables from the link
    var args = req.query;

    if(args['args'].length < 1){
        console.log("Invalid variable amount");
        res.status(205).json('{"error" : "incorrect amount of arguments"}');
        return
    }
    // Connect to DB and test connection
    const seq = new Sequelize(process.env.DB ,process.env.UNAME, process.env.PASS , {
        host : process.env.IP,          // All these stats are defined in a .env file
        dialect: 'mariadb'
    });
    try{
      await seq.authenticate();
      console.log('Connection Established');
    }catch (error){
      console.log('Unable to connect to DB:\t',error);
    }
    // Create Model (Table) and syn with DBc

    const Jobs = seq.define('Jobs', {
        MC : {
            type: DataTypes.INTEGER
        },
        JobID : {
            type : DataTypes.INTEGER,
            primaryKey : true
        },
        Action : {
            type : DataTypes.BOOLEAN
        },
        SensorID : {
            type : DataTypes.INTEGER
        }
    },
    {
      timestamps: false
    }
    );
    // try to create a database entry
    try {
        await Jobs.update({
            Action : parseInt(args['args'][1]) == 1 ? true : false 
        },
        {
            where : {SensorID : parseInt(args['args'][0])}
        });
    } catch (error) {
        console.log(`[Update] error adding entry to database`);
        res.status(205).json({OOPS : error});
        return;
    }
    const results = `${args['args'].join(' | ')}`
    console.log(`[api Update] results of POST by user : \n${JSON.stringify(results,null, 2)}`);
    // Close connection and send response
    seq.close();
    res.status(200).json(results);
  }

