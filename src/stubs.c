#include <civetweb.h>
#include "stubs.h"
#include "log.h"

struct stub {
  const char *uri;
  void *cbdata;
};

#define STUB(urid) { .uri = urid, .cbdata = urid }

static int stub_handler(struct mg_connection *conn, void *cbdata) {
  (void)cbdata;

  const struct mg_request_info *ri = mg_get_request_info(conn);
  DLOG("stub_handler: %s\n", ri->local_uri);
  for (int i = 0; i < ri->num_headers; i++) {
    DLOG("  %s: %s\n", ri->http_headers[i].name, ri->http_headers[i].value);
  }
  return 1;
}

void install_stubs(struct mg_context *ctx) {
struct stub stubs[] = {
    STUB("/api/profiles/*"),
    STUB("/api/profiles/*/follow"),
    STUB("/api/articles/feed"),
    STUB("/api/articles"),
    STUB("/api/articles/*"),
    STUB("/api/articles/*/comments"),
    STUB("/api/articles/*/comments/*"),
    STUB("/api/articles/*/favorite"),
    STUB("/api/tags"),
    STUB(NULL)
};

  for (int i = 0; stubs[i].uri ; i++) {
    mg_set_request_handler(ctx, stubs[i].uri, stub_handler, stubs[i].cbdata);
    DLOG("installed stub: %s\n", stubs[i].uri);
  }
}
