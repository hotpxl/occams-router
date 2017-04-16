#include <iostream>

#include "controller.hh"
#include "timestamp.hh"

static unsigned int current_window_size = 1;
constexpr uint64_t const kDelayThreshold = 100;

Controller::Controller(bool const debug) : debug_{debug} {}

unsigned int Controller::window_size(void) {
  if (debug_) {
    std::cerr << "At time " << timestamp_ms() << " window size is "
              << current_window_size << std::endl;
  }

  return current_window_size;
}

void Controller::datagram_was_sent(uint64_t const sequence_number,
                                   uint64_t const send_timestamp) {
  if (debug_) {
    std::cerr << "At time " << send_timestamp << " sent datagram "
              << sequence_number << std::endl;
  }
}

void Controller::ack_received(uint64_t const sequence_number_acked,
                              uint64_t const send_timestamp_acked,
                              uint64_t const recv_timestamp_acked,
                              uint64_t const timestamp_ack_received) {
  if (debug_) {
    std::cerr << "At time " << timestamp_ack_received
              << " received ack for datagram " << sequence_number_acked
              << " (send @ time " << send_timestamp_acked
              << ", received @ time " << recv_timestamp_acked
              << " by receiver's clock)" << std::endl;
  }

  if (kDelayThreshold < timestamp_ack_received - send_timestamp_acked) {
    if (1 < current_window_size) {
      current_window_size /= 2;
    }
  } else {
    current_window_size += 1;
  }
}

unsigned int Controller::timeout_ms(void) { return 1000; }
