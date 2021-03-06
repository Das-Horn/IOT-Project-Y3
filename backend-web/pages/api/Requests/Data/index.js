import { PrismaClient } from '@prisma/client'

const prisma = new PrismaClient();

export default async function handler(req,res){

    const results = await prisma.sensorData.findMany({
        orderBy : {
            DataKey : "desc"
        },
        take : 100,
    })
    prisma.$disconnect()
    res.status(200).json(results);
}