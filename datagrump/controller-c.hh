#ifndef CONTROLLER_HH
#define CONTROLLER_HH

#include <cstdint>

class Controller {
 public:
  Controller(bool const debug);

  unsigned int window_size();

  void datagram_was_sent(std::uint64_t sequence_number,
                         std::uint64_t send_timestamp);

  void ack_received(std::uint64_t sequence_number_acked,
                    std::uint64_t send_timestamp_acked,
                    std::uint64_t recv_timestamp_acked,
                    std::uint64_t timestamp_ack_received);

  unsigned int timeout_ms();

 private:
  constexpr static std::uint64_t const kDelayThreshold = 100;
  constexpr static std::uint64_t const kLowWatermark = LOW_WATERMARK;
  constexpr static std::uint64_t const kHighWatermark = HIGH_WATERMARK;
  bool debug_;
  unsigned int current_window_size_;
};

#endif
