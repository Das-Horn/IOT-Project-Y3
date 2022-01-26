import {Sequelize, DataTypes} from 'sequelize';

export default async function handler(req,res){
    // DB code init
    const seq = new Sequelize(process.env.DB ,process.env.UNAME, process.env.PASS , {
        host : process.env.IP,          // All these stats are defined in a .env file
        dialect: 'mariadb'
    });
    try{
        await seq.authenticate();
        console.log('[MCEntries] connection established to DB');
    }catch (error){
        console.log(`Cannot connect to the database`);
    }
    //Create a model of the table
    //create different one for each table
    const MCE = seq.define('MCEntries', {      
        MC : {
            type : DataTypes.INTEGER,
            primaryKey : true
        },
        TotalEntries : {
            type: DataTypes.INTEGER
        },
        LastEntry : {
            type :DataTypes.TIME
        },
        SensorsCount : {
            type : DataTypes.INTEGER
        }
    },
    {
        timestamps : false
    }
    );
    //sync DB
    const results = await MCE.findAll(); //request query
    console.log(`[api MCEntries] Results requested have been retrieved : \n${JSON.stringify(results)}`);
    //close connection
    seq.close();

    res.status(200).json(results); //send results
}

