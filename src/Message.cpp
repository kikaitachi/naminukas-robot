#include <cstring>
#include "Logger.hpp"
#include "Message.hpp"

namespace message {

  int write_data(void **buf, int *buf_len, const void *data, size_t len) {
  	if (*buf_len < len) {
  		return -1;
  	}
  	memcpy(*buf, data, len);
  	*buf = (int8_t *)*buf + len;
  	*buf_len = *buf_len - len;
  	return 0;
  }

  int read_data(void **buf, int *buf_len, void *data, size_t len) {
  	if (*buf_len < len) {
  		return -1;
  	}
  	memcpy(data, *buf, len);
  	*buf = (int8_t *)*buf + len;
  	*buf_len = *buf_len - len;
  	return 0;
  }

  int write_int(void **buf, int *buf_len, int value) {
  	if (*buf_len < 1) {
  		return -1;
  	}
  	int sign;
  	if (value < 0) {
  		sign = 1 << 6;
  		value = -value;
  	} else {
  		sign = 0;
  	}
  	int8_t byte = ((value > 63 ? 1 : 0) << 7) | sign | (value & 63);
  	memcpy(*buf, &byte, 1);
  	value >>= 6;
  	*buf = (int8_t *)*buf + 1;
  	*buf_len = *buf_len - 1;
  	while (value > 0) {
  		if (*buf_len < 1) {
  			return -1;
  		}
  		int8_t byte = ((value > 127 ? 1 : 0) << 7) | (value & 127);
  		memcpy(*buf, &byte, 1);
  		value >>= 7;
  		*buf = (int8_t *)*buf + 1;
  		*buf_len = *buf_len - 1;
  	}
  	return 0;
  }

  int read_int(void **buf, int *buf_len, int *value) {
  	int negative;
  	for (int i = 0; *buf_len > 0; ) {
  		int byte = ((int8_t *)*buf)[0];
  		if (i == 0) {
  			*value = byte & 63;
  			negative = (byte & (1 << 6)) > 0;
  			i += 6;
  		} else {
  			*value = *value | ((byte & 127) << i);
  			i += 7;
  		}
  		*buf = (int8_t *)*buf + 1;
  		*buf_len = *buf_len - 1;
  		if (byte >= 0) {
  			if (negative) {
  				*value = -*value;
  			}
  			return 0;
  		}
  	}
  	return -1;
  }

  int write_float(void **buf, int *buf_len, float value) {
  	return write_data(buf, buf_len, &value, 4);
  }

  int read_float(void **buf, int *buf_len, float *value) {
  	return read_data(buf, buf_len, value, 4);
  }

  int write_double(void **buf, int *buf_len, double value) {
  	return write_data(buf, buf_len, &value, 8);
  }

  int read_double(void **buf, int *buf_len, double *value) {
  	return read_data(buf, buf_len, value, 8);
  }

  int write_string(void **buf, int *buf_len, std::string value) {
    write_int(buf, buf_len, value.length());
    return write_data(buf, buf_len, value.c_str(), value.length());
  }
}

MessageHandler::MessageHandler(telemetry::Items& telemetryItems) :
    telemetryItems(telemetryItems) {
};

#define MAX_OUT_MSG_SIZE 1024 * 64

void MessageHandler::handle(WebSocketServer *server, Client *client, void *payload, size_t size) {
  logger::info("Got message from %d of %d bytes", client->fd, size);
  void *buf = payload;
  int buf_len = size;
  int msg_type;
  message::read_int(&buf, &buf_len, &msg_type);
  logger::debug("Message type: %d", msg_type);
  switch (msg_type) {
    case message::TELEMETRY_QUERY: {
	    char buffer[MAX_OUT_MSG_SIZE];
      logger::debug("Client %d has %d changed telemetry item ids", client->fd, client->changed_telemetry_item_ids.size());
      for (auto &telemetry_item_id : client->changed_telemetry_item_ids) {
        std::map<int, telemetry::Item*>::iterator it = telemetryItems.id_to_item.find(telemetry_item_id);
        if (it != telemetryItems.id_to_item.end()) {
		      void *buf = buffer;
          int buf_len = sizeof(buffer);
          message::write_int(&buf, &buf_len, message::TELEMETRY_UPDATE);
          message::write_int(&buf, &buf_len, it->second->getId());
          it->second->serialize_value(&buf, &buf_len);
		      server->sendBinary(client->fd, buffer, sizeof(buffer) - buf_len);
        }
      }
      client->changed_telemetry_item_ids.clear();
      break;
    }
    case message::TELEMETRY_UPDATE: {
      int item_id;
      message::read_int(&buf, &buf_len, &item_id);
      std::map<int, telemetry::Item*>::iterator it = telemetryItems.id_to_item.find(item_id);
      if (it == telemetryItems.id_to_item.end()) {
        logger::warn("Receiver telemetry update message for item with non existing id %d", item_id);
      } else {
        if (it->second->getType() == telemetry::TYPE_ACTION) {
          it->second->deserialize_value(&buf, &buf_len);
        } else {
          logger::warn("Receiver telemetry update message for item %d with non action type %d", item_id, it->second->getType());
        }
      }
      break;
    }
    default:
      logger::warn("Received unsupported message type %d from %d", msg_type, client->fd);
      break;
  }
}
