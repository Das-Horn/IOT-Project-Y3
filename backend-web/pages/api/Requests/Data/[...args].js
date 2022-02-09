import { PrismaClient } from '@prisma/client'

const prisma = new PrismaClient();

export default async function handler(req,res){
    const args = req.query['args'];
    let results;
    console.log(args);

    if(args.length == 1){
        results = await prisma.sensorData.findMany({
            where : {
                DataType : args[0]
            },
            orderBy : {
                TimeStamp : "desc"
            },
            take : 100,
        })
    } else {
        results = await prisma.sensorData.findMany({
            where : {
            AND: [
                {DataType : args[0]},
                {MC : parseInt(args[1])}
            ]
            },
            orderBy : {
                TimeStamp : "desc"
            },
            take : 100,
        })
    }
    console.log(results);
    res.status(200).json(results);
}