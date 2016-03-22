
#pragma once

#include <queue>

#include <stdint.h>
#include <stdlib.h>

#include "ISendReceive.hpp"

#define BUFFER_MAX_LEN		128

class MockMessage {
public:
	MockMessage(uint8_t* data, int size) {
		int count = std::min(size, BUFFER_MAX_LEN);
		memcpy(this->_data, data, count);
		this->_size = count;
	}

	int Read(uint8_t* data, int max_length) {
		int count = std::min(max_length, this->_size);
		memcpy(data, this->_data, count);
		return count;
	}

private:
	uint8_t _data[BUFFER_MAX_LEN];
	int _size;
};

class MockSendReceive: public Freyja::ISendReceive {
public:
	MockSendReceive() {
		_send_queue = std::queue<MockMessage>();
		_receive_queue = std::queue<MockMessage>();
	}

	int Receive(uint8_t* data, size_t max_length) {
		if(_receive_queue.size() == 0) {
			return 0;
		}

		MockMessage m = _receive_queue.front();

		int count = m.Read(data, max_length);

		_receive_queue.pop();

		return count;
	}

	int PutReceive(uint8_t* data, size_t length) {
		MockMessage m = MockMessage(data, length);

		_receive_queue.push(m);

		return length;
	}

	int Send(uint8_t* data, size_t length) {
		MockMessage m = MockMessage(data, length);

		_send_queue.push(m);

		return length;
	}

	int GetSend(uint8_t* data, size_t max_length) {
		if(_send_queue.size() == 0) {
			return 0;
		}

		MockMessage m = _send_queue.front();

		int count = m.Read(data, max_length);

		_send_queue.pop();

		return count;
	}

private:
	std::queue<MockMessage> _send_queue;
	std::queue<MockMessage> _receive_queue;
};

