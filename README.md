# Arduino library for Trinamic TMC stepper motor drivers
This library works with any Arduino compatible board (Arduino, STM32, NXP, etc) and it's available on PlatformIO

| Drivers | Support | Supply |Max RMS | Interface | CoolStep™ | StallGuard™ | StealthChop™ |
| :-----: |:-------:| :----: | :------:| :-------: | :-------: | :---------: | :----------: |
| TMC2130 | :heavy_check_mark: | 5…46V | 1.4 A | SPI | :heavy_check_mark:| :heavy_check_mark: v2 | :heavy_check_mark: v1 |
| TMC2160 | :heavy_check_mark: | 8…60V | external MOSFETs | SPI | :heavy_check_mark: | :heavy_check_mark: v2 | :heavy_check_mark: v2 |
| TMC2208 | :heavy_check_mark: | 4.75…36V | 1.4A | UART ||| :heavy_check_mark: v2 |
| TMC2209 | :heavy_check_mark: | 4.75…29V | 2.0A | UART | :heavy_check_mark: | :heavy_check_mark: v4 | :heavy_check_mark: v2 |
| TMC2224 | :heavy_check_mark: | 4.75…36V | 1.4A | UART |  |  | :heavy_check_mark: v2 |
| TMC2660 | :heavy_check_mark: | 9…30V | 2.8A | SPI | :heavy_check_mark: | :heavy_check_mark: v2 |  |
| TMC5130 | :heavy_check_mark: | 4.75…46V | 1.4A | SPI/UART | :heavy_check_mark: | :heavy_check_mark: v2 | :heavy_check_mark: v1 |
| TMC5160 | :heavy_check_mark: | 8…60V | external MOSFETs | SPI/UART | :heavy_check_mark: | :heavy_check_mark: v2 | :heavy_check_mark: v2 |
| TMC5161 | :heavy_check_mark: | 8…40V | 3.5A | SPI/UART | :heavy_check_mark: | :heavy_check_mark: v2 | :heavy_check_mark: v2 |

### Used on
- 3D printer firmware (Marlin)
