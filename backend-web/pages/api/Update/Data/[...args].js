import { PrismaClient } from '@prisma/client'

const prisma = new PrismaClient();

export default async function handler(req,res){

    var args = req.query;

    if(args['args'].length != 4){
        console.log("Invalid variable amount");
        res.status(205).json('{"error" : "incorrect amount of arguments"}');
        return
    }

    const NewTypes = await prisma.sensorData.create({
            data : {
                MC : parseInt(args['args'][0]),
                DataType : args['args'][1],
                Data : args['args'][2],
                SensorID : parseInt(args['args'][3]),
            }
        }
    );
    console.log(NewTypes);
    res.status(200).json(NewTypes);
}
