import {Sequelize, DataTypes} from 'sequelize';

export default async function handler(req,res){
    // DB code init
    const seq = new Sequelize(process.env.DB ,process.env.UNAME, process.env.PASS , {
        host : process.env.IP,          // All these stats are defined in a .env file
        dialect: 'mariadb'
    });
    try{
        await seq.authenticate();
        console.log('[Sensors] connection established to DB');
    }catch (error){
        console.log(`Cannot connect to the database`);
    }
    //Create a model of the table
    //create different one for each table
    const ConSen = seq.define('connected Sensors', {      
        MC : {
            type : DataTypes.INTEGER,
            primaryKey : true
        },
        Sensors: {
            type : DataTypes.STRING
        },
        SensorID : {
            type : DataTypes.INTEGER,
            primaryKey : true
        },
        location : {
            type : DataTypes.INTEGER
        }
    },
    {
        timestamps : false
    }
    );
    //sync DB
    const results = await ConSen.findAll(); //request query
    console.log(`[api Sensors] Results requested have been retrieved : \n${JSON.stringify(results)}`);
    //close connection
    seq.close();

    res.status(200).json(results); //send results
}

