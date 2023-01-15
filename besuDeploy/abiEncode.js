const Web3 = require("web3")

const web3 = new Web3

const latitude = web3.utils.utf8ToHex('4532.00')
const longitude = web3.utils.utf8ToHex('-34.236')
const altitude = web3.utils.utf8ToHex('32700.05')
const timestamp = web3.utils.utf8ToHex('562455')
const device = web3.utils.utf8ToHex('5e484p')
const fischCode = web3.utils.utf8ToHex('892edr')
const day = web3.utils.utf8ToHex('25/06/2022')

const parameters = web3.eth.abi.encodeParameters(
    ['bytes32','bytes32','bytes32','bytes32','bytes32','bytes32','bytes32'],
    [latitude,longitude,altitude,timestamp,device,fischCode,day]
)

console.log(parameters)