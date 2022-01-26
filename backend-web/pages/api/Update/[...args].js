import { Sequelize,DataTypes } from 'sequelize';



export default async function handler(req, res) {
    // Code to get the api variables from the link
    var args = req.query;

    if(args['args'].length < 1){
        console.log("Invalid variable amount");
        res.status(205).json('{"error" : "incorrect amount of arguments"}');
        return
    }
    // if(args['args'][1] < 0){
    //   args['args'][1] = args['args'][1] * -1; 
    // }
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
// Create Model (Table) and sync with DB

    const Update = seq.define('bintimes', {
        id : {
          type : DataTypes.INTEGER,
          primaryKey : true
        },
        bin_id : {
          type : DataTypes.INTEGER,
        },
        entry_time : {
          type : DataTypes.TIME
        },
        perc_filled : {
          type : DataTypes.INTEGER
        },
        filled : {
          type : DataTypes.BOOLEAN
        },
    },
    {
      timestamps: false
    }
    );

    await Update.create({
        bin_id :  parseInt(args['args'][0]),
        perc_filled : parseInt(args['args'][1]),
        filled : parseInt(args['args'][2]),
    });

    // await bintimes.apply();
    // await bintimes.sync();
    const results = `${args['args'].join(' | ')}`
    console.log(`[api gettimes.js] results of POST by user : \n${JSON.stringify(results,null, 2)}`);
// Close connection and send response
    seq.close();
    res.status(200).json(results);
  }

