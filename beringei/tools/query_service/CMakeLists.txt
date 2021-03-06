# Copyright (c) 2016-present, Facebook, Inc.
# All rights reserved.
#
# This source code is licensed under the BSD-style license found in the
# LICENSE file in the root directory of this source tree. An additional grant
# of patent rights can be found in the PATENTS file in the same directory.

set(CMAKE_CXX_FLAGS "-g")

find_library(MYSQL_CLIENT_LIB NAMES "mysqlclient"
  PATHS "/usr/local/mysql/lib"
  NO_DEFAULT_PATH
)
find_library(CURL curl)

set(BERINGEI_QUERY_SRCS
    QueryServiceFactory.cpp
    QueryServiceFactory.h
    NotFoundHandler.cpp
    NotFoundHandler.h
    TableQueryHandler.cpp
    TableQueryHandler.h
    QueryHandler.cpp
    QueryHandler.h
    BeringeiData.cpp
    BeringeiData.h
    AggregatorService.cpp
    AggregatorService.h
    StatsWriteHandler.cpp
    StatsWriteHandler.h
    StatsTypeAheadCache.cpp
    StatsTypeAheadCache.h
    StatsTypeAheadCacheHandler.cpp
    StatsTypeAheadCacheHandler.h
    StatsTypeAheadHandler.cpp
    StatsTypeAheadHandler.h
    MySqlClient.cpp
    MySqlClient.h
    EventsWriteHandler.cpp
    EventsWriteHandler.h
    AlertsWriteHandler.cpp
    AlertsWriteHandler.h
    LogsWriteHandler.cpp
    LogsWriteHandler.h
)

set(BERINGEI_QUERY_SERVICE_SRCS
  BeringeiQueryServer.cpp
)

add_library(beringei_query_lib STATIC ${BERINGEI_QUERY_SRCS})
target_link_libraries(
    beringei_query_lib
    beringei_client
    beringei_plugin
    ${CURL}
    ${FBTHRIFT_LIBRARIES}
    ${FOLLY_LIBRARIES}
    ${GFLAGS_LIBRARIES}
    ${LIBGLOG_LIBRARIES}
    ${PROXYGEN_LIBRARIES}
    Threads::Threads
    ${MYSQL_CLIENT_LIB}
    mysqlcppconn
)

add_executable(beringei_query_service ${BERINGEI_QUERY_SERVICE_SRCS})

target_link_libraries(
    beringei_query_service
    beringei_query_lib
    ${FBTHRIFT_LIBRARIES}
    ${FOLLY_LIBRARIES}
    ${GFLAGS_LIBRARIES}
    ${LIBGLOG_LIBRARIES}
    ${PROXYGEN_LIBRARIES}
    Threads::Threads
)
