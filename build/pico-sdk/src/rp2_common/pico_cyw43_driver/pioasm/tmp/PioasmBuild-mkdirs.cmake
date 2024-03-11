# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/Users/andyvotava/src/rsbryPico/pico/pico-sdk/tools/pioasm"
  "/Users/andyvotava/src/WirelessGCC/build/pioasm"
  "/Users/andyvotava/src/WirelessGCC/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm"
  "/Users/andyvotava/src/WirelessGCC/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/tmp"
  "/Users/andyvotava/src/WirelessGCC/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src/PioasmBuild-stamp"
  "/Users/andyvotava/src/WirelessGCC/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src"
  "/Users/andyvotava/src/WirelessGCC/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src/PioasmBuild-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/andyvotava/src/WirelessGCC/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src/PioasmBuild-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/andyvotava/src/WirelessGCC/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src/PioasmBuild-stamp${cfgdir}") # cfgdir has leading slash
endif()
