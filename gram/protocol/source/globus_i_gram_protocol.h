#ifndef DOXYGEN

#include "globus_common.h"
#include "globus_gram_protocol.h"
#include "globus_io.h"

EXTERN_C_BEGIN

/* Strings used in protocol framing, packing, unframing, and unpacking */

#define CRLF             "\015\012"
#define GLOBUS_GRAM_HTTP_REQUEST_LINE \
                        "POST %s HTTP/1.1" CRLF

#define GLOBUS_GRAM_HTTP_HOST_LINE \
                        "Host: %s" CRLF

#define GLOBUS_GRAM_HTTP_CONTENT_TYPE_LINE \
                        "Content-Type: application/x-globus-gram" CRLF

#define GLOBUS_GRAM_HTTP_CONTENT_LENGTH_LINE \
                        "Content-Length: %ld" CRLF

#define GLOBUS_GRAM_HTTP_REPLY_LINE \
                        "HTTP/1.1 %3d %s" CRLF
#define GLOBUS_GRAM_HTTP_PARSE_REPLY_LINE \
                        "HTTP/1.1 %3d %[^" CRLF "]" CRLF
#define GLOBUS_GRAM_HTTP_CONNECTION_LINE \
                        "Connection: Close" CRLF

#define GLOBUS_GRAM_HTTP_PACK_PROTOCOL_VERSION_LINE \
                        "protocol-version: %d" CRLF

#define GLOBUS_GRAM_HTTP_PACK_JOB_STATE_MASK_LINE \
                        "job-state-mask: %d" CRLF

#define GLOBUS_GRAM_HTTP_PACK_CALLBACK_URL_LINE \
                        "callback-url: %s" CRLF

#define GLOBUS_GRAM_HTTP_PACK_STATUS_LINE \
                        "status: %d" CRLF

#define GLOBUS_GRAM_HTTP_PACK_FAILURE_CODE_LINE \
                        "failure-code: %d" CRLF

#define GLOBUS_GRAM_HTTP_PACK_JOB_FAILURE_CODE_LINE \
                        "job-failure-code: %d" CRLF

#define GLOBUS_GRAM_HTTP_PACK_JOB_MANAGER_URL_LINE \
                        "job-manager-url: %s" CRLF

#define GLOBUS_GRAM_HTTP_PACK_CLIENT_REQUEST_LINE \
                        "%s" CRLF

typedef enum
{
    GLOBUS_GRAM_PROTOCOL_REQUEST,
    GLOBUS_GRAM_PROTOCOL_REPLY
}
globus_gram_protocol_read_type_t;

typedef struct
{
    unsigned short			port;
    globus_bool_t			allow_attach;
    globus_io_handle_t *		handle;
    globus_gram_protocol_callback_t	callback;
    void *				callback_arg;
    volatile int			connection_count;
    globus_cond_t			cond;
}
globus_i_gram_protocol_listener_t;

typedef struct
{
    globus_bool_t			got_header;
    globus_byte_t *			buf;
    globus_size_t			bufsize;
    globus_gram_protocol_read_type_t	read_type;
    globus_size_t			payload_length;
    globus_size_t			n_read;
    globus_gram_protocol_callback_t	callback;
    void *				callback_arg;
    globus_byte_t *			replybuf;
    globus_size_t			replybufsize;

    globus_io_handle_t *		io_handle;
    globus_gram_protocol_handle_t	handle;
    globus_i_gram_protocol_listener_t *	listener;
    int					rc;
}
globus_i_gram_protocol_connection_t;

int
globus_i_gram_protocol_callback_disallow(
    globus_i_gram_protocol_listener_t *	listener);

extern globus_mutex_t			globus_i_gram_protocol_mutex;
extern globus_cond_t			globus_i_gram_protocol_cond;

extern globus_list_t *			globus_i_gram_protocol_listeners;
extern globus_list_t *			globus_i_gram_protocol_connections;
extern globus_bool_t 			globus_i_gram_protocol_shutdown_called;
extern globus_io_attr_t			globus_i_gram_protocol_default_attr;
extern int				globus_i_gram_protocol_num_connects;
extern globus_gram_protocol_handle_t	globus_i_gram_protocol_handle;

EXTERN_C_END

#endif /* DOXYGEN */
