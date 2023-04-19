const Web3 = require("web3");
const fs = require("fs");
require("dotenv").config();

const web3 = new Web3(process.env.BESU_NODE);
const { abi } = JSON.parse(
  fs.readFileSync("./build/contracts/Traceability.json")
);

const signer = web3.eth.accounts.privateKeyToAccount(process.env.PRIVATE_KEY);

web3.eth.accounts.wallet.add(signer);

const contract = new web3.eth.Contract(abi, process.env.CONTRACT_ADDRESS);

const index = web3.utils.utf8ToHex(/* id of device to return its tracks */);

contract.methods
  .getProductsByDevice(index)
  .call()
  .then((res) => {
    res.forEach((x) => {
      let stringData = web3.utils.hexToUtf8(x);
      console.log(stringData);
    });
  });
