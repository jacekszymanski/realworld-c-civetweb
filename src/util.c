#include <civetweb.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"
#include "log.h"
#include "appctx.h"

#define BUF_INCR 4096

const char* read_body_frags(struct mg_connection *conn);

const char* get_request_content(struct mg_connection *conn) {
  const struct mg_request_info *ri = mg_get_request_info(conn);
  int content_length = ri->content_length;
  char *content;
  if (content_length == 0) {
    return NULL;
  }
  else if (content_length < 0) {
    return read_body_frags(conn);
  }
  else {
    content = malloc(content_length + 1);
    int read = mg_read(conn, content, content_length);
    content[read] = '\0';
    DLOG("get_request_content: read %d bytes\n", read);
  }

  return content;
}

const char* read_body_frags(struct mg_connection *conn) {
  // content-length is not available, need to read as it comes

  // allocate buffer, if needed it will be increased by BUF_INCR
  int bufsize = BUF_INCR;
  char *buf = malloc(bufsize + 1);

  int read = 0;
  int total_read = 0;

  // 0 might mean that more data is to come... OTOH it is also documented as closed connection...
  while ((read = mg_read(conn, buf + total_read, bufsize - total_read)) >= 0) {
    total_read += read;
    if (total_read + 1 >= bufsize) {
      bufsize += BUF_INCR;
      char* oldbuf = buf;
      buf = realloc(buf, bufsize + 1);
      if (buf == NULL) {
        WLOG("%s", "read_body_frags: realloc failed\n");
        free(oldbuf);
        return NULL;
      }

    }
  }

  buf[total_read] = '\0';

  DLOG("read_body_frags: read %d bytes\n", total_read);

  return buf;
}

char * safe_strdup(const char *s) {
  if (s == NULL) {
    return strdup("");
  }
  return strdup(s);
}

void set_200_ok(struct reqctx *ctx) {
  ctx->respcode = 200;
  ctx->errmsg = strdup("OK");
}
