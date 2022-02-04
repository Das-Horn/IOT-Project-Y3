import { PrismaClient } from '@prisma/client'


export default async function handler(req,res){
    const prisma = new PrismaClient();
    const results = await prisma.connected_Sensors.findMany();
    res.status(200).json(results); //send results
}

