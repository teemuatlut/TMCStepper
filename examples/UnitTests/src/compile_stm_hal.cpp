
#if defined(USE_HAL_DRIVER) && !defined(USE_FULL_LL_DRIVER)

#include <TMCStepper.h>

const auto ENABLE_Pin = GPIO_PIN_0;
const auto ENABLE_GPIO_Port = GPIOA;
const auto CS_Pin = GPIO_PIN_4;
const auto CS_GPIO_Port = GPIOA;
const auto SW_SPI_MOSI_Pin = GPIO_PIN_8;
const auto SW_SPI_MOSI_GPIO_Port = GPIOA;
const auto SW_SPI_MISO_Pin = GPIO_PIN_11;
const auto SW_SPI_MISO_GPIO_Port = GPIOA;
const auto SW_SPI_SCK_Pin = GPIO_PIN_1;
const auto SW_SPI_SCK_GPIO_Port = GPIOA;

SPI_HandleTypeDef hspi1;
UART_HandleTypeDef huart2;
constexpr float R_SENSE = 0.11f;

TMC_HAL::OutputPin enPin({ENABLE_GPIO_Port, ENABLE_Pin});

SW_SPIClass sw_spi({SW_SPI_MOSI_GPIO_Port, SW_SPI_MOSI_Pin}, {SW_SPI_MISO_GPIO_Port, SW_SPI_MISO_Pin}, {SW_SPI_SCK_GPIO_Port, SW_SPI_SCK_Pin});

TMC2130Stepper driver ( hspi1, {CS_GPIO_Port, CS_Pin}, R_SENSE);
TMC2130Stepper driver1(sw_spi, {CS_GPIO_Port, CS_Pin}, R_SENSE);
TMC2160Stepper driver2( hspi1, {CS_GPIO_Port, CS_Pin}, R_SENSE);
TMC2160Stepper driver3(sw_spi, {CS_GPIO_Port, CS_Pin}, R_SENSE);
TMC2660Stepper driver4( hspi1, {CS_GPIO_Port, CS_Pin}, R_SENSE);
TMC2660Stepper driver5(sw_spi, {CS_GPIO_Port, CS_Pin}, R_SENSE);
TMC5130Stepper driver6( hspi1, {CS_GPIO_Port, CS_Pin}, R_SENSE);
TMC5130Stepper driver7(sw_spi, {CS_GPIO_Port, CS_Pin}, R_SENSE);
TMC5160Stepper driver8( hspi1, {CS_GPIO_Port, CS_Pin}, R_SENSE);
TMC5160Stepper driver9(sw_spi, {CS_GPIO_Port, CS_Pin}, R_SENSE);

TMC2208Stepper driver10(huart2, R_SENSE);
TMC2209Stepper driver12(huart2, R_SENSE, 2);
TMC2300Stepper driver14(huart2, R_SENSE, 3);

extern "C"
int main() {
    driver.begin();
    driver.rms_current(600);
    driver.microsteps(16);
}

#endif
