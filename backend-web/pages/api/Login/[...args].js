import {Sequelize, DataTypes} from 'sequelize';

export default async function handler(req,res){
    // DB code init
    const seq = new Sequelize(process.env.DB ,process.env.UNAME, process.env.PASS , {
        host : process.env.IP,          // All these stats are defined in a .env file
        dialect: 'mariadb',
        dialectOptions : {
            options : {
                requestTimeout : 4000
            }
        }
    });
    try{
        await seq.authenticate();
        console.log('[Login] connection established to DB');
    }catch (error){
        console.log(`Cannot connect to the database`);
        res.status(500).json({error : "Timed out connecting to DB"});
        return
    }
    //Create a model of the table
    //create different one for each table
    const Login = seq.define('Login', {
        ID : {
            type : DataTypes.INTEGER,
            primaryKey: true
        },
        Name : {
            type : DataTypes.STRING
        },
        Password : {
            type: DataTypes.STRING
        }
    },
    {
        timestamps : false
    }
    );
    //sync DB
    try{
    const results = await Login.findAll(); //request query
    console.log(`\n\n\n[api Login] Results requested have been retrieved : \n${JSON.stringify(results)}\n\n\n`);
    //close connection
    seq.close();

    res.status(200).json(results); //send results
    } catch(error){
        res.status(500).json({error : error});
    }
}