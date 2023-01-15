const Web3 = require('web3')
const fs = require('fs')
require('dotenv').config()

const web3 = new Web3(process.env.HOST)
const { abi } = JSON.parse(fs.readFileSync('./build/contracts/Traceability.json'))

const signer = web3.eth.accounts.privateKeyToAccount(
    process.env.FIRST_DEVICE
)

const contract = new web3.eth.Contract(
    abi,
    process.env.CONTRACT_ADDRESS
)

const latitude = web3.utils.utf8ToHex('4532.00')
const longitude = web3.utils.utf8ToHex('-34.236')
const altitude = web3.utils.utf8ToHex('32700.05')
const timestamp = web3.utils.utf8ToHex('562455')
const device = web3.utils.utf8ToHex('5e484p')
const fischCode = web3.utils.utf8ToHex('892edr')
const day = web3.utils.utf8ToHex('25/06/2022')

const tx = contract.methods.trackProduct(latitude,longitude,altitude,timestamp,device,fischCode,day)

web3.eth.getBlock('latest', async (err,block) => {
    if (err) {
        console.log(err)
        return
    }
    const _block = await block
    const gasLimit = _block.gasLimit

    tx.send({
        from: signer.address,
        gas: '0x' + gasLimit.toString(16)
    })
    .once('transactionHash', (txHash) => {
        console.log(txHash)
    })
})