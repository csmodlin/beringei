/**
 * Copyright (c) 2016-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */
#pragma once

#include "MySqlClient.h"
#include "StatsTypeAheadCache.h"

#include "beringei/client/BeringeiClient.h"
#include "beringei/client/BeringeiConfigurationAdapterIf.h"

#include <folly/io/async/EventBaseManager.h>
#include <folly/Memory.h>
#include <folly/Portability.h>
#include <gflags/gflags.h>
#include <proxygen/httpserver/HTTPServer.h>
#include <proxygen/httpserver/RequestHandlerFactory.h>

namespace facebook {
namespace gorilla {

// Request handler factory that figures out the right handler based on the uri
class QueryServiceFactory : public proxygen::RequestHandlerFactory {
 public:
  explicit QueryServiceFactory(
    std::shared_ptr<BeringeiConfigurationAdapterIf> configurationAdapter,
    std::shared_ptr<MySqlClient> mySqlClient,
    std::shared_ptr<TACacheMap> typeaheadCache,
    std::shared_ptr<BeringeiClient> beringeiReadClient,
    std::shared_ptr<BeringeiClient> beringeiWriteClient);

  void onServerStart(folly::EventBase *evb) noexcept override;

  void onServerStop() noexcept override;

  proxygen::RequestHandler *
  onRequest(proxygen::RequestHandler *,
            proxygen::HTTPMessage *) noexcept override;

 private:
  folly::EventBase *eb_;
  std::shared_ptr<BeringeiConfigurationAdapterIf> configurationAdapter_;
  std::shared_ptr<MySqlClient> mySqlClient_;
  // topology name -> type-ahead cache
  std::shared_ptr<TACacheMap> typeaheadCache_;
  std::shared_ptr<BeringeiClient> beringeiReadClient_;
  std::shared_ptr<BeringeiClient> beringeiWriteClient_;
};

}
} // facebook::gorilla
