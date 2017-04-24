#ifndef CONTROLLER_HH
#define CONTROLLER_HH

#include <cstdint>

class Controller {
 public:
  Controller(bool debug);

  unsigned int window_size();

  void datagram_was_sent(std::uint64_t sequence_number,
                         std::uint64_t send_timestamp);

  void ack_received(std::uint64_t sequence_number_acked,
                    std::uint64_t send_timestamp_acked,
                    std::uint64_t recv_timestamp_acked,
                    std::uint64_t timestamp_ack_received);

  unsigned int timeout_ms();

 private:
  bool debug_;
};

#endif
