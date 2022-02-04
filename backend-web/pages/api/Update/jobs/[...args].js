import { PrismaClient } from '@prisma/client'


export default async function handler(req,res){
    const prisma = new PrismaClient();
    var args = req.query;

    if(args['args'].length < 2){
        console.log("Invalid variable amount");
        res.status(205).json('{"error" : "incorrect amount of arguments"}');
        return
    }

    const results = await prisma.jobs.update({
        data : {
            Action : parseInt(args['args'][1]) == 1 ? true : false
        },
        where : {
            SensorID : parseInt(args['args'][0])
        }
    })
   
    res.status(200).json(results);
  }

