# libopencm3_lwip
Collection of libopencm3 drivers for lwIP.

The drivers themselves live in the `/src/port` folder, with each driver corresponding to an environment in the PlatformIO build environment.

The actual source code is platform-agnostic, and sets up a series of tasks that can be simultaneously tested to validate the performance/reliability of these drivers.

To test the driver functions, run the python script that lives in the `/test` folder. You should have the hardware device on your local network and know the IP address of the device. (This IP address can be static or DHCP, this is defined in the global config file.)

Note that these drivers use the PlatformIO-lwIP library, which is in turn based on the PlatformIO-FreeRTOS library.
These libraries are unmodified wrappers around the source libraries: version numbers as follows:
- lwIP : **STABLE-2.1.X**
- FreeRTOS : **v10.4.0**
Porting the driver to other versions of lwIP and other RTOSes is relatively straightforward,
but some native FreeRTOS functions are used in the driver for performance reasons.

## Features Tested:
- TCP Echo Server
- UDP Rx - Flood
- UDP Tx - Flood
- Corrupt Frame/CRC handling
- Collision Frame handling
- Hardware IP address filtering (Unicast & Multicast)
- PTP Tx and Rx timestamping
- Link up/down testing (has to be performed manually)

## Driver Standard Structure:
TODO
