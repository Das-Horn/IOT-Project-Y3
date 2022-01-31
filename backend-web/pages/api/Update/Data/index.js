

// Do not use this link it will push no data

export default function handler(req,res){
    console.log(`[api Update index.js] This link does not work. please supply arguments.`)
    res.status(205).json({'error' : 'please  supply arguments.'});
}