#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <string.h>


int main(){
  // Open the bus in read/write mode.
  // If the returned value is < 0, there was an error.
  int i2cBus1 = open("/dev/i2c-1", O_RDWR);

  int slaveAddress = 0x7;
  // Initiate the handshake with the slave.
  // If the returned value is < 0, there was an error.
  ioctl(i2cBus1, I2C_SLAVE, slaveAddress);

  char message[] = "hello world\n";

    while(1){
      // Send the message. Returns the number of bytes sent.
      write(i2cBus1, message, strlen(message));
    }

  return 0;
}
