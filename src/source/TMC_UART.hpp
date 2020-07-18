
#pragma once

#include <stdint.h>
#include "TMC_HAL.h"

class SSwitch {
  public:
    SSwitch(const TMCStepper_n::PinDef pin1, const TMCStepper_n::PinDef pin2, const uint8_t address);
    void active();
  private:
    TMCStepper_n::PinDef p1;
    TMCStepper_n::PinDef p2;
    const uint8_t addr;
};

namespace TMCStepper_n {

struct TMC_UART {
protected:

  template<class> friend class TMCStepper;
  template<class> friend class TMC2208_n::GCONF_i;
  template<class> friend class TMC2208_n::GSTAT_i;
  template<class> friend class TMC2208_n::IFCNT_i;
  template<class> friend class TMC2208_n::SLAVECONF_i;
  template<class> friend class TMC2208_n::OTP_PROG_i;
  template<class> friend class TMC2208_n::OTP_READ_i;
  template<class> friend class TMC2208_n::IOIN_i;
  template<class> friend class TMC2208_n::FACTORY_CONF_i;
  template<class> friend class TMC2208_n::IHOLD_IRUN_i;
  template<class> friend class TMC2208_n::TPOWERDOWN_i;
  template<class> friend class TMC2208_n::TSTEP_i;
  template<class> friend class TMC2208_n::TPWMTHRS_i;
  template<class> friend class TMC2208_n::VACTUAL_i;
  template<class> friend class TMC2208_n::MSCNT_i;
  template<class> friend class TMC2208_n::MSCURACT_i;
  template<class> friend class TMC2208_n::CHOPCONF_i;
  template<class> friend class TMC2208_n::DRV_STATUS_i;
  template<class> friend class TMC2208_n::PWMCONF_i;
  template<class> friend class TMC2208_n::PWM_SCALE_i;
  template<class> friend class TMC2208_n::PWM_AUTO_i;

  template<class> friend class TMC2209_n::IOIN_i;
  template<class> friend class TMC2209_n::SGTHRS_i;
  template<class> friend class TMC2209_n::SG_RESULT_i;
  template<class> friend class TMC2209_n::COOLCONF_i;

  TMC_UART(HardwareSerial * SerialPort, uint8_t addr);
  TMC_UART(HardwareSerial * SerialPort, uint8_t addr, PinDef mul_pin1, PinDef mul_pin2);
  TMC_UART(PinDef SW_RX_pin, PinDef SW_TX_pin, uint8_t addr);

  static constexpr uint8_t TMC_READ = 0x00,
                          TMC_WRITE = 0x80;

  HardwareSerial * HWSerial = nullptr;
  #if SW_CAPABLE_PLATFORM
    SoftwareSerial * SWSerial = nullptr;
    const TMCStepper_n::PinDef RXTX_pin = 0; // Half duplex
  #endif

  SSwitch *sswitch = nullptr;

  static constexpr uint8_t  TMC2208_SYNC = 0x05,
                                                      TMC2208_SLAVE_ADDR = 0x00;
  static constexpr uint8_t replyDelay = 2;
  static constexpr uint8_t abort_window = 50;
  static constexpr uint8_t max_retries = 2;

  struct ReadRequest {
    static constexpr uint8_t length = 4;
    uint8_t sync = TMC2208_SYNC;
    uint8_t driverAddress;
    uint8_t registerAddress;
    uint8_t crc = 0;
  };

  struct WriteDatagram {
    static constexpr uint8_t length = 8;
    uint8_t sync = TMC2208_SYNC;
    uint8_t driverAddress;
    uint8_t registerAddress;
    uint32_t data;
    uint8_t crc = 0;
  };

  typedef WriteDatagram ReadResponse;

  int available();
  size_t getTime() const;
  void preWriteCommunication();
  void preReadCommunication();
  void serial_read(uint8_t *data, int8_t length);
  void serial_write(const uint8_t *data, int8_t length);
  void postWriteCommunication();
  void postReadCommunication();
  void write(uint8_t, uint32_t);
  uint32_t read(uint8_t);
  const uint8_t slaveAddress;
  uint8_t calcCRC(uint8_t datagram[], uint8_t len);

  ReadResponse sendReadRequest(ReadRequest &datagram);

  uint16_t bytesWritten = 0;
  bool CRCerror = false;
};

};
