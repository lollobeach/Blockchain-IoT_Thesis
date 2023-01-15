const Web3 = require('web3')
const fs = require('fs')
require('dotenv').config()

const web3 = new Web3(process.env.HOST)
const { abi } = JSON.parse(fs.readFileSync('./build/contracts/Traceability.json'))

const contract = new web3.eth.Contract(
    abi,
    process.env.CONTRACT_ADDRESS
)

contract.methods.getAllDevices().call().then((res) => {
    console.log(res)
})