/* failover.h

   Definitions for address trees... */

/*
 * Copyright (c) 1999 Internet Software Consortium.
 * Use is subject to license terms which appear in the file named
 * ISC-LICENSE that should have accompanied this file when you
 * received it.   If a file named ISC-LICENSE did not accompany this
 * file, or you are not sure the one you have is correct, you may
 * obtain an applicable copy of the license at:
 *
 *             http://www.isc.org/isc-license-1.0.html. 
 *
 * This file is part of the ISC DHCP distribution.   The documentation
 * associated with this file is listed in the file DOCUMENTATION,
 * included in the top-level directory of this release.
 *
 * Support and other services are available for ISC products - see
 * http://www.isc.org for more information.
 */

#if defined (FAILOVER_PROTOCOL)
struct failover_option_info {
	int code;
	const char *name;
	enum { FT_UINT8, FT_IPADDR, FT_UINT32, FT_BYTES, FT_TEXT_OR_BYTES,
	       FT_DDNS, FT_DDNS1, FT_UINT16, FT_TEXT,
	       FT_UNDEF, FT_DIGEST } type;
	int num_present;
	int offset;
	u_int32_t bit;
};

typedef struct {
	unsigned count;
	u_int8_t *data;
} failover_option_t;

#define FM_OFFSET(x) (long)(&(((failover_message_t *)0) -> x))

#define FTO_BINDING_STATUS		1
#define FTB_BINDING_STATUS			0x00000002
#define FTO_ASSIGNED_IP_ADDRESS		2
#define FTB_ASSIGNED_IP_ADDRESS			0x00000004
#define FTO_SERVER_ADDR			3
#define FTB_SERVER_ADDR				0x00000008
#define FTO_ADDRESSES_TRANSFERRED	4
#define FTB_ADDRESSES_TRANSFERRED		0x00000010
#define FTO_CLIENT_IDENTIFIER		5
#define FTB_CLIENT_IDENTIFIER			0x00000020
#define FTO_CHADDR			6
#define FTB_CHADDR				0x00000040
#define FTO_DDNS			7
#define FTB_DDNS				0x00000080
#define FTO_REJECT_REASON		8
#define FTB_REJECT_REASON			0x00000100
#define FTO_MESSAGE			9
#define FTB_MESSAGE				0x00000200
#define FTO_MCLT			10
#define FTB_MCLT				0x00000400
#define FTO_VENDOR_CLASS		11
#define FTB_VENDOR_CLASS			0x00000800
#define FTO_LEASE_EXPIRY		13
#define FTB_LEASE_EXPIRY			0x00002000
#define FTO_POTENTIAL_EXPIRY		14
#define FTB_POTENTIAL_EXPIRY			0x00004000
#define FTO_GRACE_EXPIRY		15
#define FTB_GRACE_EXPIRY			0x00008000
#define FTO_CLTT			16
#define FTB_CLTT				0x00010000
#define FTO_STOS			17
#define FTB_STOS				0x00020000
#define FTO_SERVER_STATE		18
#define FTB_SERVER_STATE			0x00040000
#define FTO_SERVER_FLAGS		19
#define FTB_SERVER_FLAGS			0x00080000
#define FTO_VENDOR_OPTIONS		20
#define FTB_VENDOR_OPTIONS			0x00100000
#define FTO_MAX_UNACKED			21
#define FTB_MAX_UNACKED				0x00200000
#define FTO_RECEIVE_TIMER		23
#define FTB_RECEIVE_TIMER			0x00800000
#define FTO_HBA				24
#define FTB_HBA					0x01000000
#define FTO_MESSAGE_DIGEST		25
#define FTB_MESSAGE_DIGEST			0x02000000
#define FTO_PROTOCOL_VERSION		26
#define FTB_PROTOCOL_VERSION			0x04000000
#define FTO_TLS_REQUEST			27
#define FTB_TLS_REQUEST				0x08000000
#define FTO_TLS_REPLY			28
#define FTB_TLS_REPLY				0x10000000
#define FTO_REQUEST_OPTIONS		29
#define FTB_REQUEST_OPTIONS			0x20000000
#define FTO_REPLY_OPTIONS		30
#define FTB_REPLY_OPTIONS			0x40000000
#define FTO_MAX				FTO_REPLY_OPTIONS

#define FTM_POOLREQ		1
#define FTM_POOLRESP		2
#define FTM_BNDUPD		3
#define FTM_BNDACK		4
#define FTM_CONNECT		5
#define FTM_CONNECTACK		6
#define FTM_UPDREQ		7
#define FTM_UPDDONE		8
#define FTM_UPDREQALL		9
#define FTM_STATE		10
#define FTM_CONTACT		11
#define FTM_DISCONNECT		12

#define DHCP_FAILOVER_MAX_MESSAGE_SIZE	2048

typedef struct {
	u_int8_t type;

	u_int8_t binding_status;
	u_int8_t protocol_version;
	u_int8_t reject_reason;
	u_int8_t server_flags;
	u_int8_t server_state;
	u_int8_t tls_reply;
	u_int8_t tls_request;
	u_int32_t stos;
	u_int32_t time;
	u_int32_t xid;
	u_int32_t addresses_transferred;
	u_int32_t assigned_addr;
	u_int32_t client_ltt;
	u_int32_t expiry;
	u_int32_t grace_expiry;
	u_int32_t max_unacked;
	u_int32_t mclt;
	u_int32_t potential_expiry;
	u_int32_t receive_timer;
	u_int32_t server_addr;
	failover_option_t chaddr;
	failover_option_t client_identifier;
	failover_option_t hba;
	failover_option_t message;
	failover_option_t reply_options;
	failover_option_t request_options;
	ddns_fqdn_t ddns;
	failover_option_t vendor_class;
	failover_option_t vendor_options;

	int options_present;
} failover_message_t;

typedef struct {
	OMAPI_OBJECT_PREAMBLE;
	struct option_cache *peer_address;
	unsigned peer_port;
	int options_present;
	enum dhcp_flink_state {
		dhcp_flink_start,
		dhcp_flink_message_length_wait,
		dhcp_flink_message_wait,
		dhcp_flink_disconnected,
		dhcp_flink_state_max
	} state;
	failover_message_t *imsg;
	struct _dhcp_failover_state *state_object;
	u_int16_t imsg_len;
	unsigned imsg_count;
	u_int8_t imsg_payoff; /* Pay*load* offset. :') */
	u_int32_t xid;
} dhcp_failover_link_t;

typedef struct {
	OMAPI_OBJECT_PREAMBLE;
	unsigned local_port;
} dhcp_failover_listener_t;
#endif /* FAILOVER_PROTOCOL */

/* A failover peer. */
enum failover_state {
	invalid_state,
	partner_down,
	normal,
	communications_interrupted,
	potential_conflict,
	recover
};

#if defined (FAILOVER_PROTOCOL)
typedef struct _dhcp_failover_state {
	OMAPI_OBJECT_PREAMBLE;
	struct _dhcp_failover_state *next;
	char *name;			/* Name of this failover instance. */
	struct option_cache *address;	/* Partner's IP address or hostname. */
	int listen_port;
	int port;			/* Partner's TCP port. */
	struct iaddr server_addr;
	u_int32_t max_flying_updates;
	u_int32_t mclt;
	u_int8_t *hba;

	enum failover_state partner_state;
	TIME partner_stos;
	enum failover_state my_state;
	TIME my_stos;

	enum {
		primary, secondary
	} i_am;		/* We are primary or secondary in this relationship. */

	TIME last_packet_sent;		/* Timestamp on last packet we sent. */
	TIME last_timestamp_received;	/* The last timestamp we sent that
					   has been returned by our partner. */
	TIME skew;	/* The skew between our clock and our partner's. */
	u_int32_t max_transmit_idle; /* Always send a poll if we haven't sent
					some other packet more recently than
					this. */
	u_int32_t max_response_delay;	/* If the returned timestamp on the
					   last packet we received is older
					   than this, communications have been
					   interrupted. */
	/* The ack queue and update queue are circular lists, so you can
	   tell whether or not a lease is on one of the lists by looking
	   at its next pointer.   Or maybe we should just flag it as
	   UPDATE_PENDING or ACK_PENDING.    But anyway, two seperate
	   queues.   Hm. Maybe these should be hash tables, with no pointer
	   from the peer to the lease. */
	struct lease *update_queue;	/* List of leases we haven't sent
					   to peer. */
	struct lease *ack_queue;	/* List of lease updates the peer
					   hasn't yet acked. */
	int cur_unacked_updates;	/* Number of updates we've sent
					   that have not yet been acked. */
} dhcp_failover_state_t;

#define DHCP_FAILOVER_VERSION		1
#endif /* FAILOVER_PROTOCOL */
