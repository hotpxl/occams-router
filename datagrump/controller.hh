#ifndef CONTROLLER_HH
#define CONTROLLER_HH

#include <cstdint>
#include <deque>

/* Congestion controller interface */

class Controller
{
private:
  bool debug_; /* Enables debugging output */

  /* Add member variables here */

  // TUNING PARAMETERS
  static constexpr int kIntervalMs = 25;  /* Measurement interval (ms) */
  static constexpr int kMaxEstimates = 5; /* Number of estimates to keep */
  static constexpr double kBwAggressiveness = 1.75;

  uint64_t packets_received_;    /* Packets received in the last interval. */
  uint64_t calc_time_;           /* Last time we did a packet/ms estimate. */
  std::deque<double> ppms_;      /* N most recent packet/ms estimates. */
  uint32_t best_rtt_;            /* Best RTT we have seen the whole time. */

  void update_ppms() {
    const double ppms = (1.0 * packets_received_) / kIntervalMs;

    if (ppms_.size() == kMaxEstimates) ppms_.pop_back();
    ppms_.push_front(ppms);

    packets_received_ = 0;
  }

  double avg_ppms() const {
    if (ppms_.empty()) return 0;

    double total = 0.0;
    for (const auto ppms : ppms_) {
      total += ppms;
    }
    return total / ppms_.size();
  }

public:
  /* Public interface for the congestion controller */
  /* You can change these if you prefer, but will need to change
     the call site as well (in sender.cc) */

  /* Default constructor */
  Controller( const bool debug );

  /* Get current window size, in datagrams */
  unsigned int window_size( void );

  /* A datagram was sent */
  void datagram_was_sent( const uint64_t sequence_number,
			  const uint64_t send_timestamp );

  /* An ack was received */
  void ack_received( const uint64_t sequence_number_acked,
		     const uint64_t send_timestamp_acked,
		     const uint64_t recv_timestamp_acked,
		     const uint64_t timestamp_ack_received );

  /* How long to wait (in milliseconds) if there are no acks
     before sending one more datagram */
  unsigned int timeout_ms( void );
};

#endif
