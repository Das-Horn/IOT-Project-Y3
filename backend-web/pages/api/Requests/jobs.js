import { PrismaClient } from '@prisma/client'

const prisma = new PrismaClient();

export default async function handler(req,res){

    const results = await prisma.jobs.findMany();

    res.status(200).json(results); //send results
}

