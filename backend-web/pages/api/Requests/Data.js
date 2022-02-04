import { PrismaClient } from '@prisma/client'


export default async function handler(req,res){
    const prisma = new PrismaClient();

    const results = await prisma.sensorData.findMany({
        orderBy : {
            DataKey : "desc"
        },
        take : 100,
    })

    res.status(200).json(results);
}