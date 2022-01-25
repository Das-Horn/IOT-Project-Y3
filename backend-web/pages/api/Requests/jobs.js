import {Sequelize, DataTypes} from 'sequelize';

export default function handler(req,res){
    // DB code init
    const seq = new Sequelize(process.env.DB ,process.env.UNAME, process.env.PASS , {
        host : process.env.IP,          // All these stats are defined in a .env file
        dialect: 'mysql'
    });
    try{
        await seq.authenticate();
        console.log('[MCLists] connection established to DB');
    }catch (error){
        console.log(`Cannot connect to the database`);
    }
    //Create a model of the table
    //create different one for each table
    const Jobs = seq.define('MCLists', {      
        JobID : {
            type : DataTypes.INTEGER,
            primaryKey : true
        },
        MC : {
            type : DataTypes.INTEGER,
        },
        Action : {
            type : DataTypes.BOOLEAN
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
    await Jobs.sync();
    const results = await Jobs.findAll(); //request query
    console.log(`[api MCLists] Results requested have been retrieved : \n${JSON.stringify(results)}`);
    //close connection
    seq.close();

    res.status(200).json(results); //send results

    res.status(200);
}

