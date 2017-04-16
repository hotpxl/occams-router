#include <algorithm>
#include <climits>
#include <iostream>

#include "controller.hh"
#include "timestamp.hh"

using namespace std;

static constexpr int kInterval = 30;

/* Default constructor */
Controller::Controller( const bool debug )
  : debug_(debug), packets_received_(0), calc_time_(0),
    pps_estimate_(0.0), best_rtt_(numeric_limits<uint32_t>::max())
{
}

/* Get current window size, in datagrams */
unsigned int Controller::window_size( void )
{
  // We can tune the algorithm by adjusting the constant used
  // to calculate max_delay.
  const int32_t max_delay = static_cast<int>(best_rtt_ * 1.5);
  return pps_estimate_ * max_delay;
}

/* A datagram was sent */
void Controller::datagram_was_sent( const uint64_t sequence_number,
				    /* of the sent datagram */
				    const uint64_t send_timestamp )
                                    /* in milliseconds */
{
  if ( debug_ ) {
    cerr << "At time " << send_timestamp
         << " sent datagram " << sequence_number << endl;
  }

  if ((send_timestamp - calc_time_) >= kInterval) {
    pps_estimate_ = (1.0 * packets_received_) / kInterval;
    calc_time_ = send_timestamp - (send_timestamp % kInterval);
    packets_received_ = 0;
  }
}

/* An ack was received */
void Controller::ack_received( const uint64_t sequence_number_acked,
			       /* what sequence number was acknowledged */
			       const uint64_t send_timestamp_acked,
			       /* when the acknowledged datagram was sent (sender's clock) */
			       const uint64_t recv_timestamp_acked,
			       /* when the acknowledged datagram was received (receiver's clock)*/
			       const uint64_t timestamp_ack_received )
                               /* when the ack was received (by sender) */
{
  if ( debug_ ) {
    cerr << "At time " << timestamp_ack_received
	 << " received ack for datagram " << sequence_number_acked
	 << " (send @ time " << send_timestamp_acked
	 << ", received @ time " << recv_timestamp_acked << " by receiver's clock)"
	 << endl;
  }

  // Update our best-observed RTT if possible.
  const uint64_t rtt = timestamp_ack_received - send_timestamp_acked;
  if (rtt < best_rtt_) {
    best_rtt_ = rtt;
    if (debug_) cerr << "Best observed RTT = " << best_rtt_ << endl;
  }

  if ((timestamp_ack_received - calc_time_) >= kInterval) {
    pps_estimate_ = (1.0 * packets_received_) / kInterval;
    calc_time_ = timestamp_ack_received - (
        timestamp_ack_received % kInterval);
    packets_received_ = 0;
  }

  packets_received_++;
}

/* How long to wait if there are no acks before sending one more packet */
unsigned int Controller::timeout_ms(void)
{
  return 100;
}
