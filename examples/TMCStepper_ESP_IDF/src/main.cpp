
#include <esp_log.h>
#include <TMCStepper.h>

#define TAG_EPS32_SERIAL "ESP32_UART"

const gpio_num_t
    EN_PIN     = GPIO_NUM_NC, // Enable
    DIR_PIN    = GPIO_NUM_NC, // Direction
    STEP_PIN   = GPIO_NUM_NC, // Step
    CS_PIN     = GPIO_NUM_NC, // Chip select
    SW_MOSI    = GPIO_NUM_NC, // Software Master Out Slave In (MOSI)
    SW_MISO    = GPIO_NUM_NC, // Software Master In Slave Out (MISO)
    SW_SCK     = GPIO_NUM_NC, // Software Slave Clock (SCK)
    SW_RX      = GPIO_NUM_NC, // TMC2208/TMC2224 SoftwareSerial receive pin
    SW_TX      = GPIO_NUM_NC; // TMC2208/TMC2224 SoftwareSerial transmit pin

constexpr uint8_t DRIVER_ADDRESS = 0b00; // TMC2209 Driver address according to MS1 and MS2
constexpr float R_SENSE = 0.11; // Current shunt resistor

spi_device_handle_t SPI{};
spi_host_device_t SpiPort = SPI2_HOST;
uart_port_t SerialPort = 1;

TMC2130Stepper driver(SPI, CS_PIN, R_SENSE);
// TMC2208Stepper driver(SerialPort, R_SENSE);

void begin_spi();
void begin_serial();

extern "C"
void app_main() {
    TMC_HAL::OutputPin
        enablePin{EN_PIN},
        stepPin{STEP_PIN},
        dirPin{DIR_PIN};

    enablePin.reset();

    driver.begin();
    driver.rms_current(600);
    driver.microsteps(16);
    driver.toff(3);

    while (true) {
        for (uint16_t i = 5000; i>0; i--) {
            stepPin.set();
            ets_delay_us(160);
            stepPin.reset();
            ets_delay_us(160);
        }
    }
}

void TMCStepper_n::TMC_SPI::initPeripheral() {
    spi_bus_config_t cfg{};
    cfg.mosi_io_num = GPIO_NUM_NC;
    cfg.miso_io_num = GPIO_NUM_NC;
    cfg.sclk_io_num = GPIO_NUM_NC;

    ESP_ERROR_CHECK(spi_bus_initialize(SpiPort, &cfg, 0));

    spi_device_interface_config_t dev_cfg{};
    dev_cfg.mode = 3;
    dev_cfg.clock_speed_hz = spi_speed;
    dev_cfg.spics_io_num = GPIO_NUM_NC;

    ESP_ERROR_CHECK(spi_bus_add_device(SpiPort, &dev_cfg, &SPI));
}

void TMC_HAL::TMC_UART::begin(uint32_t baudrate) {
    uart_config_t uart_config = {
        .baud_rate = static_cast<int>(baudrate),
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .rx_flow_ctrl_thresh = 0,
        .source_clk = UART_SCLK_APB,
    };

    ESP_ERROR_CHECK(uart_driver_install(SerialPort, 2048, 0, 0, NULL, 0));
    ESP_ERROR_CHECK(uart_param_config(SerialPort, &uart_config));
    ESP_ERROR_CHECK(uart_set_pin(SerialPort, SW_TX, SW_RX, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));
}
