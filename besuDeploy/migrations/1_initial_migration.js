const Traceability = artifacts.require("Traceability");

module.exports = function (deployer) {
  deployer.deploy(Traceability);
};
