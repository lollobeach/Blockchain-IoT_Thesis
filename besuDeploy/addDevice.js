const Web3 = require('web3')
const fs = require('fs')
require('dotenv').config()

const web3 = new Web3(process.env.HOST)
const { abi } = JSON.parse(fs.readFileSync('./build/contracts/Traceability.json'))

const signer = web3.eth.accounts.privateKeyToAccount(
    process.env.ADMIN_KEY
)

web3.eth.accounts.wallet.add(signer)

const contract = new web3.eth.Contract(
    abi,
    process.env.CONTRACT_ADDRESS
)

const index = web3.utils.utf8ToHex('8965')

const tx = contract.methods.addDevice(index, /* public address of the device to be added */)

web3.eth.getBlock('latest', async (err, block) => {
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