#ifndef UNITTEST_TRANSPORT_H
#define UNITTEST_TRANSPORT_H

#if defined(TARGET_LPC1768)


  #include <stdio.h>

  #include <usb/usb.h>
  #include <usb/usbcfg.h>
  #include <usb/usbhw.h>
  #include <usb/usbcore.h>
  #include <usb/cdc.h>
  #include <usb/cdcuser.h>
  #include <usb/mscuser.h>
  #include <CDCSerial.h>
  #include <usb/mscuser.h>

  void unittest_uart_begin() {
      USB_Init();
      USB_Connect(false);
      delay(1000);
      USB_Connect(true);
      delay(1000);
  }

  void unittest_uart_putchar(char c) {
    UsbSerial.write((uint8_t)c);
  }

  void unittest_uart_flush() {
    UsbSerial.flush();
  }

  void unittest_uart_end() {}

#elif defined(ARDUINO_ARCH_STM32)

  #include <USBSerial.h>

  void unittest_uart_begin() {
      SerialUSB.begin(115200);
  }

  void unittest_uart_putchar(char c) {
    SerialUSB.write(c);
  }

  void unittest_uart_flush() {
    SerialUSB.flush();
  }

  void unittest_uart_end() {
    SerialUSB.end();
  }

#endif
#endif
