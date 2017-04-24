#include <iostream>
#include "controller.hh"
#include "timestamp.hh"

Controller::Controller(bool debug) : debug_{debug} {}

unsigned int Controller::window_size() {
  if (debug_) {
    std::cerr << "At time " << timestamp_ms() << " window size is "
              << WINDOW_SIZE_CHANGE_ME << std::endl;
  }

  return WINDOW_SIZE_CHANGE_ME;
}

void Controller::datagram_was_sent(std::uint64_t sequence_number,
                                   std::uint64_t send_timestamp) {
  if (debug_) {
    std::cerr << "At time " << send_timestamp << " sent datagram "
              << sequence_number << std::endl;
  }
}

void Controller::ack_received(std::uint64_t sequence_number_acked,
                              std::uint64_t send_timestamp_acked,
                              std::uint64_t recv_timestamp_acked,
                              std::uint64_t timestamp_ack_received) {
  if (debug_) {
    std::cerr << "At time " << timestamp_ack_received
              << " received ack for datagram " << sequence_number_acked
              << " (send @ time " << send_timestamp_acked
              << ", received @ time " << recv_timestamp_acked
              << " by receiver's clock)" << std::endl;
  }
}

unsigned int Controller::timeout_ms() { return 1000; }
