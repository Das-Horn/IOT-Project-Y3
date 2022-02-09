import { PrismaClient } from '@prisma/client'

const prisma = new PrismaClient();

export default async function handler(req,res){
    const args = req.query['args'];



    const results = await prisma.sensorData.findMany({
        where : {
            DataType : args[0]
        },
        orderBy : {
            TimeStamp : "desc"
        },
        take : 100,
    })
    prisma.$disconnect()
    res.status(200).json(results);
}