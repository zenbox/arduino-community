/****************************************************************************************************************************
  mimetable.h - Dead simple web-server.
  For Ethernet shields

  EthernetWebServer is a library for the Ethernet shields to run WebServer

  Based on and modified from ESP8266 https://github.com/esp8266/Arduino/releases
  Built by Khoi Hoang https://github.com/khoih-prog/EthernetWebServer
  Licensed under MIT license

  Original author:
  @file       Esp8266WebServer.h
  @author     Ivan Grokhotkov

  Version: 2.4.1

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.0.0   K Hoang      13/02/2020 Initial coding for Arduino Mega, Teensy, etc to support Ethernetx libraries
  ...
  2.2.0   K Hoang      05/05/2022 Add support to custom SPI for Teensy, Mbed RP2040, Portenta_H7, etc.
  2.2.1   K Hoang      25/08/2022 Auto-select SPI SS/CS pin according to board package
  2.2.2   K Hoang      06/09/2022 Slow SPI clock for old W5100 shield or SAMD Zero. Improve support for SAMD21
  2.2.3   K Hoang      17/09/2022 Add support to AVR Dx (AVR128Dx, AVR64Dx, AVR32Dx, etc.) using DxCore
  2.2.4   K Hoang      26/10/2022 Add support to Seeed XIAO_NRF52840 and XIAO_NRF52840_SENSE using `mbed` or `nRF52` core
  2.3.0   K Hoang      15/11/2022 Add new features, such as CORS. Update code and examples to send big data
  2.4.0   K Hoang      22/12/2022 Fix compile errors for new ESP32 core v2.0.6
  2.4.1   K Hoang      06/01/2023 Add support to `WIZNet W6100` using IPv4
 *************************************************************************************************************************************/

#pragma once

#ifndef __MIMETABLE_H__
#define __MIMETABLE_H__

namespace mime
{

enum type
{
  html,
  htm,
  css,
  txt,
  js,
  json,
  png,
  gif,
  jpg,
  ico,
  svg,
  ttf,
  otf,
  woff,
  woff2,
  eot,
  sfnt,
  xml,
  pdf,
  zip,
  gz,
  appcache,
  none,
  maxType
};

struct Entry
{
  const char endsWith[16];
  const char mimeType[32];
};

// Table of extension->MIME strings stored in PROGMEM, needs to be global due to GCC section typing rules
const Entry mimeTable[maxType] =
{
  { ".html",      "text/html" },
  { ".htm",       "text/html" },
  { ".css",       "text/css" },
  { ".txt",       "text/plain" },
  { ".js",        "application/javascript" },
  { ".json",      "application/json" },
  { ".png",       "image/png" },
  { ".gif",       "image/gif" },
  { ".jpg",       "image/jpeg" },
  { ".ico",       "image/x-icon" },
  { ".svg",       "image/svg+xml" },
  { ".ttf",       "application/x-font-ttf" },
  { ".otf",       "application/x-font-opentype" },
  { ".woff",      "application/font-woff" },
  { ".woff2",     "application/font-woff2" },
  { ".eot",       "application/vnd.ms-fontobject" },
  { ".sfnt",      "application/font-sfnt" },
  { ".xml",       "text/xml" },
  { ".pdf",       "application/pdf" },
  { ".zip",       "application/zip" },
  { ".gz",        "application/x-gzip" },
  { ".appcache",  "text/cache-manifest" },
  { "",           "application/octet-stream" }
};
//extern const Entry mimeTable[maxType];
} // namespace mime

#endif    // #ifndef __MIMETABLE_H__

