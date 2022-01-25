import {sequelize, DataType, Sequelize} from 'sequelize';
import { isPrimitive } from 'sequelize/dist/lib/utils';

export default function handler(req,res){
    // DB code init
    const seq = new Sequelize('' ,'Uname', 'pass' , {
        // host : , ip
        // dialect: 'mysql'
    });
    try{
        await seq.authenticate();
        console.log('[MCLists] connection established to DB');
    }catch (error){
        console.log(`Cannot connect to the database`);
    }
    //Create a model of the table
    res.status(200);
}

