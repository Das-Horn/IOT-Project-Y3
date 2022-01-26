import {Sequelize, DataTypes} from 'sequelize';

export default function handler(req,res){
    // DB code init
    const seq = new Sequelize(process.env.DB ,process.env.UNAME, process.env.PASS , {
        host : process.env.IP,          // All these stats are defined in a .env file
        dialect: 'mariadb'
    });
    try{
        await seq.authenticate();
        console.log('[Rooms] connection established to DB');
    }catch (error){
        console.log(`Cannot connect to the database`);
    }
    //Create a model of the table
    //create different one for each table
    const Rooms = seq.define('Rooms', {      
        RoomID : {
            type : DataTypes.INTEGER,
            primaryKey : true
        },
        RoomName: {
            type : DataTypes.STRINGS
        }
    },
    {
        timestamps : false
    }
    );
    //sync DB
    await Rooms.sync();
    const results = await Rooms.findAll(); //request query
    console.log(`[api Rooms] Results requested have been retrieved : \n${JSON.stringify(results)}`);
    //close connection
    seq.close();

    res.status(200).json(results); //send results
}

