# mbed LoRaWan shield

Main program to send data from a NUCLEO_L476RG with LoRaWAN using the LoRaWAN Shield (developed at Vives).

This project is inspired by the [LoRaWAN Shield Example](https://github.com/sillevl/lorawan-shield-example/) repository of [sillevl](https://github.com/sillevl).

## LoRaWAN packet format

| type | value |
|:---:|:---|
| uInt16 | light-sensor |
| uInt16 | temperature-sensor 1 |
| uInt16 | temperature-sensor 2 |
| uInt16 | moisture-sensor 1 |
| uInt16 | moisture-sensor 2 |
| uInt16 | moisture-sensor 3 |
| uInt16 | moisture-sensor 4 |
| uInt16 | moisture-sensor 5 |
| uInt8 | battery status |
| uInt8 | sensor status (bit for each sensor in same order as above) |
