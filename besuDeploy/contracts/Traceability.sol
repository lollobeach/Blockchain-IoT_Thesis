// SPDX-License-Identifier: MIT

pragma solidity >= 0.8.0;

contract Traceability {

    struct Device {
        bytes32 idDevice;
        address deviceAddress;
    }


    mapping(bytes32 => bytes[]) private productsForDevice;
    mapping(address => bool) private devices;
    mapping(address => bytes32) private idOfDevice;

    Device[] private devicesAdded;
    bytes[] private allProducts;

    event Track(bytes jsonData);

    event AddDevice(bytes32 _idDevice, address _deviceAddress);


    function addDevice(bytes32 _idDevice, address _deviceAddress) public {
        require(msg.sender == /* wallet address of admin */, "Only admin can add addresses");
        require(devices[_deviceAddress] == false, "This device already exist");

        devices[_deviceAddress] = true;
        idOfDevice[_deviceAddress] = _idDevice;
        Device memory device;
        device.idDevice = _idDevice;
        device.deviceAddress = _deviceAddress;

        devicesAdded.push(device);


        emit AddDevice(_idDevice, _deviceAddress);
    }


    function trackProduct(bytes calldata jsonData) public {
        require(devices[msg.sender] == true, "Address not authorized!");

        productsForDevice[idOfDevice[msg.sender]].push(jsonData);
        allProducts.push(jsonData);

        emit Track(jsonData);
    }


    function getAllDevices() public view returns(Device[] memory) {
        return devicesAdded;
    }


    function getProductsByDevice(bytes32 _idDevice) public view returns(bytes[] memory) {
        return productsForDevice[_idDevice];
    }


    function getAllProductsTracked() public view returns(bytes[] memory) {
        return allProducts;
    }

}