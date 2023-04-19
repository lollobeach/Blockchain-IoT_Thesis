require('dotenv').config()

const PrivateKeyProvider = require("@truffle/hdwallet-provider");
const privateKey = process.env.PRIVATE_KEY;
const privateKeyProvider = new PrivateKeyProvider(privateKey, process.env.BESU_NODE);

module.exports = {
  // See <http://truffleframework.com/docs/advanced/configuration>
  // for more about customizing your Truffle configuration!
  networks: {
    besuWallet: {
      provider: privateKeyProvider,
      network_id: "*"
    },
  },

  compilers: {
    solc: {
      version: "0.8.15",      // Fetch exact version from solc-bin (default: truffle's version)
      // docker: true,        // Use "0.5.1" you've installed locally with docker (default: false)
      // settings: {          // See the solidity docs for advice about optimization and evmVersion
      //  optimizer: {
      //    enabled: false,
      //    runs: 200
      //  },
      //  evmVersion: "byzantium"
      // }
    }
  }
};
