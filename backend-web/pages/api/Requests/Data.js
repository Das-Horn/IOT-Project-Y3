import {Sequelize, DataTypes} from 'sequelize';

export default async function handler(req,res){
    // DB code init
    const seq = new Sequelize(process.env.DB ,process.env.UNAME, process.env.PASS , {
        host : process.env.IP,          // All these stats are defined in a .env file
        dialect: 'mariadb'
    });
    try{
        await seq.authenticate();
        console.log('[MCLists] connection established to DB');
    }catch (error){
        console.log(`Cannot connect to the database`);
    }
    //Create a model of the table
    //create different one for each table
    const DTE = seq.define('SensorData', {      
        MC : {
            type: DataTypes.INTEGER
        },
        DataType : {
            type : DataTypes.STRING
        },
        Data : {
            type : DataTypes.STRING
        },
        TimeStamp : {
            type : DataTypes.TIME
        },
        DataKey : {
            type : DataTypes.INTEGER,
            primaryKey : true
        },
        SensorID : {
            type : DataTypes.INTEGER
        }
    },
    {
        timestamps : false
    }
    );
    //sync DB
    const results = await DTE.findAll(); //request query
    console.log(`[api MCLists] Results requested have been retrieved : \n${JSON.stringify(results)}`);
    //close connection
    seq.close();

    res.status(200).json(results); //send results
}

