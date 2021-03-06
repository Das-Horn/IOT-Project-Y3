import { PrismaClient } from '@prisma/client'

const prisma = new PrismaClient();

export default async function handler(req,res){
    var args = req.query['args'];
    
    prisma.logins.findMany()
    .then(
        function(resp) {
            var r = false;
            resp.forEach(i => {
                if(i.Name == args[0] && i.Password == args[1]){
                    console.log('match')
                    r = true;
                }
            });
            return r;
        }
    ).then(
        function(resp) {
            res.status(200).json({login : resp});
        }
    )
}