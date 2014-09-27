/*
 * Copyright (C) 2014 - David Goulet <dgoulet@efficios.com>
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License, version 2.1 only,
 * as published by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License
 * for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#ifndef LTTNG_CHANNEL_H
#define LTTNG_CHANNEL_H

#include <lttng/domain.h>
#include <lttng/event.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Tracer channel attributes. For both kernel and user-space.
 *
 * The structures should be initialized to zero before use.
 */
#define LTTNG_CHANNEL_ATTR_PADDING1        LTTNG_SYMBOL_NAME_LEN + 12
struct lttng_channel_attr {
	int overwrite;                      /* 1: overwrite, 0: discard */
	uint64_t subbuf_size;               /* bytes */
	uint64_t num_subbuf;                /* power of 2 */
	unsigned int switch_timer_interval; /* usec */
	unsigned int read_timer_interval;   /* usec */
	enum lttng_event_output output;     /* splice, mmap */
	/* LTTng 2.1 padding limit */
	uint64_t tracefile_size;            /* bytes */
	uint64_t tracefile_count;           /* number of tracefiles */
	/* LTTng 2.3 padding limit */
	unsigned int live_timer_interval;   /* usec */

	char padding[LTTNG_CHANNEL_ATTR_PADDING1];
};

/*
 * Channel information structure. For both kernel and user-space.
 *
 * The structures should be initialized to zero before use.
 */
#define LTTNG_CHANNEL_PADDING1             16
struct lttng_channel {
	char name[LTTNG_SYMBOL_NAME_LEN];
	uint32_t enabled;
	struct lttng_channel_attr attr;

	char padding[LTTNG_CHANNEL_PADDING1];
};

/*
 * List the channel(s) of a session.
 *
 * The handle CAN NOT be NULL.
 *
 * Return the size (number of entries) of the "lttng_channel" array. Caller
 * must free channels. On error, a negative LTTng error code is returned.
 */
extern int lttng_list_channels(struct lttng_handle *handle,
		struct lttng_channel **channels);

/*
 * Create or enable a channel.
 *
 * The chan and handle params can not be NULL.
 *
 * Return 0 on success else a negative LTTng error code.
 */
extern int lttng_enable_channel(struct lttng_handle *handle,
		struct lttng_channel *chan);

/*
 * Disable channel.
 *
 * Name and handle CAN NOT be NULL.
 *
 * Return 0 on success else a negative LTTng error code.
 */
extern int lttng_disable_channel(struct lttng_handle *handle,
		const char *name);

/*
 * Set the default channel attributes for a specific domain and an allocated
 * lttng_channel_attr pointer.
 *
 * If one or both arguments are NULL, nothing happens.
 */
extern void lttng_channel_set_default_attr(struct lttng_domain *domain,
		struct lttng_channel_attr *attr);

/*
 * Add PID filter to a channel.
 *
 * Return 0 on success else a negative LTTng error code.
 */
extern int lttng_add_pid_filter(struct lttng_handle *handle,
		const char *channel_name,
		int pid);

/*
 * Add PID filter to a channel.
 *
 * Return 0 on success else a negative LTTng error code.
 */
extern int lttng_del_pid_filter(struct lttng_handle *handle,
		const char *channel_name,
		int pid);

#ifdef __cplusplus
}
#endif

#endif /* LTTNG_CHANNEL_H */
