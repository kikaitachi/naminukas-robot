#ifndef NAMINUKAS_BRAIN_MESSAGE_H_
#define NAMINUKAS_BRAIN_MESSAGE_H_

#include <string>
#include "WebSocket.hpp"
#include "Telemetry.hpp"

namespace message {
  const int TELEMETRY_ADD = 0;
  const int TELEMETRY_UPDATE = 1;
  const int TELEMETRY_DELETE = 2;
  const int TELEMETRY_QUERY = 3;

  int write_data(void **buf, int *buf_len, const void *data, size_t len);
  int read_data(void **buf, int *buf_len, void *data, size_t len);

  int write_int(void **buf, int *buf_len, int value);
  int read_int(void **buf, int *buf_len, int *value);

  int write_float(void **buf, int *buf_len, float value);
  int read_float(void **buf, int *buf_len, float *value);

  int write_double(void **buf, int *buf_len, double value);
  int read_double(void **buf, int *buf_len, double *value);

  int write_string(void **buf, int *buf_len, std::string value);
}

class MessageHandler {
  public:
    MessageHandler(telemetry::Items& telemetryItems);
    void handle(WebSocketServer *server, Client *client, void *payload, size_t size);

  private:
    telemetry::Items& telemetryItems;
};

#endif  // NAMINUKAS_BRAIN_MESSAGE_H_
