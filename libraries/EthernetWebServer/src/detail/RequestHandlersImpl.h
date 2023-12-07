/****************************************************************************************************************************
  RequestHandlerImpl.h - Dead simple web-server.
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

#ifndef REQUEST_HANDLER_IMPL_H
#define REQUEST_HANDLER_IMPL_H

#if !(ESP32 || ESP8266)
#include "RequestHandler.h"
#include "mimetable.h"

class ethernetFunctionRequestHandler : public ethernetRequestHandler
{
  public:

    ethernetFunctionRequestHandler(EthernetWebServer::THandlerFunction fn, EthernetWebServer::THandlerFunction ufn,
                                   const String &uri, const HTTPMethod& method)
      : _fn(fn)
      , _ufn(ufn)
      , _uri(uri)
      , _method(method)
    {
    }

    bool canHandle(const HTTPMethod& requestMethod, const String& requestUri) override
    {
      if (_method != HTTP_ANY && _method != requestMethod)
        return false;

      if (requestUri == _uri)
        return true;

      if (_uri.endsWith("/*"))
      {
        String _uristart = _uri;
        _uristart.replace("/*", "");

        if (requestUri.startsWith(_uristart))
          return true;
      }

      return false;
    }

    bool canUpload(const String& requestUri) override
    {
      if (!_ufn || !canHandle(HTTP_POST, requestUri))
        return false;

      return true;
    }

    bool handle(EthernetWebServer& server, const HTTPMethod& requestMethod, const String& requestUri) override
    {
      ETW_UNUSED(server);

      if (!canHandle(requestMethod, requestUri))
        return false;

      _fn();
      return true;
    }

    void upload(EthernetWebServer& server, const String& requestUri, const ethernetHTTPUpload& upload) override
    {
      ETW_UNUSED(server);
      ETW_UNUSED(upload);

      if (canUpload(requestUri))
        _ufn();
    }

  protected:
    EthernetWebServer::THandlerFunction _fn;
    EthernetWebServer::THandlerFunction _ufn;
    String      _uri;
    HTTPMethod  _method;
};

class ethernetStaticRequestHandler : public ethernetRequestHandler
{
  public:

    bool canHandle(const HTTPMethod& requestMethod, const String& requestUri) override
    {
      if (requestMethod != HTTP_GET)
        return false;

      if ((_isFile && requestUri != _uri) || !requestUri.startsWith(_uri))
        return false;

      return true;
    }

#if USE_NEW_WEBSERVER_VERSION

    static String getContentType(const String& path)
    {
      using namespace mime;
      char buff[sizeof(mimeTable[0].mimeType)];

      // Check all entries but last one for match, return if found
      for (size_t i = 0; i < sizeof(mimeTable) / sizeof(mimeTable[0]) - 1; i++)
      {
        strcpy(buff, mimeTable[i].endsWith);

        if (path.endsWith(buff))
        {
          strcpy(buff, mimeTable[i].mimeType);
          return String(buff);
        }
      }

      // Fall-through and just return default type
      strcpy(buff, mimeTable[sizeof(mimeTable) / sizeof(mimeTable[0]) - 1].mimeType);
      return String(buff);
    }


#if USING_NAME_SPACE
}
#endif

#else

    static String getContentType(const String& path)
    {
      if (path.endsWith(".html"))
        return "text/html";
      else if (path.endsWith(".htm"))
        return "text/html";
      else if (path.endsWith(".css"))
        return "text/css";
      else if (path.endsWith(".txt"))
        return "text/plain";
      else if (path.endsWith(".js"))
        return "application/javascript";
      else if (path.endsWith(".png"))
        return "image/png";
      else if (path.endsWith(".gif"))
        return "image/gif";
      else if (path.endsWith(".jpg"))
        return "image/jpeg";
      else if (path.endsWith(".ico"))
        return "image/x-icon";
      else if (path.endsWith(".svg"))
        return "image/svg+xml";
      else if (path.endsWith(".ttf"))
        return "application/x-font-ttf";
      else if (path.endsWith(".otf"))
        return "application/x-font-opentype";
      else if (path.endsWith(".woff"))
        return "application/font-woff";
      else if (path.endsWith(".woff2"))
        return "application/font-woff2";
      else if (path.endsWith(".eot"))
        return "application/vnd.ms-fontobject";
      else if (path.endsWith(".sfnt"))
        return "application/font-sfnt";
      else if (path.endsWith(".xml"))
        return "text/xml";
      else if (path.endsWith(".pdf"))
        return "application/pdf";
      else if (path.endsWith(".zip"))
        return "application/zip";
      else if (path.endsWith(".gz"))
        return "application/x-gzip";
      else if (path.endsWith(".appcache"))
        return "text/cache-manifest";

      return "application/octet-stream";
    }

#endif

protected:

String _uri;
String _path;
String _cache_header;
bool _isFile;
size_t _baseUriLength;
};

#else
#include "ESP_RequestHandlersImpl.h"
#endif

#endif  // REQUEST_HANDLER_IMPL_H
