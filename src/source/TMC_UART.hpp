
#pragma once

#include <stdint.h>
#include "../TMCStepper.h"
#include "TMC_HAL.h"

namespace TMC_HAL {

class SSwitch {
  public:
    SSwitch(const TMC_HAL::PinDef pin1, const TMC_HAL::PinDef pin2);
    void active(const uint8_t addr);
  private:
    TMC_HAL::PinDef p1;
    TMC_HAL::PinDef p2;
};

struct TMC_UART {
  void begin(uint32_t baudrate);

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

  template<class> friend class TMC2300_n::GCONF_i;
  template<class> friend class TMC2300_n::GSTAT_i;
  template<class> friend class TMC2300_n::IFCNT_i;
  template<class> friend class TMC2300_n::SLAVECONF_i;
  template<class> friend class TMC2300_n::IOIN_i;
  template<class> friend class TMC2300_n::IHOLD_IRUN_i;
  template<class> friend class TMC2300_n::TPOWERDOWN_i;
  template<class> friend class TMC2300_n::TSTEP_i;
  template<class> friend class TMC2300_n::VACTUAL_i;
  template<class> friend class TMC2300_n::TCOOLTHRS_i;
  template<class> friend class TMC2300_n::SGTHRS_i;
  template<class> friend class TMC2300_n::SG_VALUE_i;
  template<class> friend class TMC2300_n::COOLCONF_i;
  template<class> friend class TMC2300_n::MSCNT_i;
  template<class> friend class TMC2300_n::CHOPCONF_i;
  template<class> friend class TMC2300_n::DRV_STATUS_i;
  template<class> friend class TMC2300_n::PWMCONF_i;
  template<class> friend class TMC2300_n::PWM_SCALE_i;
  template<class> friend class TMC2300_n::PWM_AUTO_i;

  TMC_UART(HardwareSerial * SerialPort, const uint8_t addr = TMC2208_SLAVE_ADDR, SSwitch * const sw = nullptr);
  #if SW_CAPABLE_PLATFORM
    TMC_UART(SoftwareSerial *ser, const uint8_t addr);
  #endif

  static constexpr uint8_t TMC_READ = 0x00,
                          TMC_WRITE = 0x80;

  HardwareSerial * const HWSerial = nullptr;
  #if SW_CAPABLE_PLATFORM
    SoftwareSerial * const SWSerial = nullptr;
  #endif

  SSwitch * const sswitch = nullptr;

  static constexpr uint8_t  TMC2208_SYNC = 0x05,
                            TMC2208_SLAVE_ADDR = 0x00;
  static constexpr uint8_t replyDelay = 2;
  static constexpr uint8_t abort_window = 20;
  static constexpr uint8_t max_retries = 5;

  #pragma pack(push, 1)

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

  #pragma pack(pop)

  int available();
  uint32_t getTime() const;
  void preWriteCommunication();
  void preReadCommunication();
  size_t serial_read(void *data, int8_t length);
  size_t serial_write(const void *data, int8_t length);
  void postWriteCommunication();
  void postReadCommunication();
  void write(const uint8_t, const uint32_t);
  uint32_t read(const uint8_t);
  const uint8_t slaveAddress;
  uint8_t calcCRC(const uint8_t datagram[], const uint8_t len);

  ReadResponse sendReadRequest(ReadRequest &datagram);

  uint16_t bytesWritten = 0;
  bool CRCerror = false;

  void WaitForInhibitTime() const;

  static constexpr uint8_t WriteInhibitTime = 4; // Prevent too fast communication attempts
  uint32_t lastWriteTime = 0;
};

};
