// SPDX-License-Identifier: MIT

pragma solidity >= 0.8.0;

contract Traceability {

    struct Product {
        bytes32 latitude;
        bytes32 longitude;
        bytes32 altitude;
        bytes32 unixTime;
        bytes32 device;
        bytes32 fishCode;
    }

    struct Device {
        bytes32 idDevice;
        address deviceAddress;
    }


    mapping(address => bool) private devices;
    mapping(bytes32 => Product[]) private productTracked;
    mapping(bytes32 => Product[]) private productsForDay;

    Device[] private devicesAdded;
    Product[] private productAdded;

    event Track(bytes32 _latitude, bytes32 _longitude, bytes32 _altitude, bytes32 _unixTime, bytes32 _device, bytes32 _fishCode);

    event AddDevice(bytes32 _idDevice, address _deviceAddress);


    function addDevice(bytes32 _idDevice, address _deviceAddress) public {
        require(msg.sender == /* Admin public address */, "Only admin can add addresses");
        require(devices[_deviceAddress] == false, "This device already exist");

        devices[_deviceAddress] = true;
        Device memory device;
        device.idDevice = _idDevice;
        device.deviceAddress = _deviceAddress;

        devicesAdded.push(device);


        emit AddDevice(_idDevice, _deviceAddress);
    }


    function trackProduct(bytes32 _latitude, bytes32 _longitude, bytes32 _altitude, bytes32 _unixTime, bytes32 _device, bytes32 _fishCode, bytes32 _day) public {
        require(devices[msg.sender] == true, "Address not authorized!");
        Product memory product = Product({latitude: _latitude, longitude: _longitude, altitude: _altitude, unixTime: _unixTime, device: _device, fishCode: _fishCode});
        
        productTracked[_device].push(product);
        productAdded.push(product);
        productsForDay[_day].push(product);

        emit Track(_latitude, _longitude, _altitude, _unixTime, _device, _fishCode);
    }


    function getAllDevices() public view returns(Device[] memory) {
        return devicesAdded;
    }


    function getProductsByDevice(bytes32 _idDevice) public view returns(Product[] memory) {
        return productTracked[_idDevice];
    }


    function getAllProductTracked() public view returns(Product[] memory) {
        return productAdded;
    }


    function getProductsForDay(bytes32 day) public view returns(Product[] memory) {
        return productsForDay[day];
    }

}