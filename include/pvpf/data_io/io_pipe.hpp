//
// Created by Max on 2018/6/24.
//

#ifndef DEV_ENV_IO_PIPE_H
#define DEV_ENV_IO_PIPE_H
#pragma once

#include <utility>
#include "pvpf/pvpf.hpp"
#include "pvpf/utils/data_bucket.hpp"
#include "buffer.hpp"

PVPF_NAMESPACE_BEGIN

namespace data_io
{
/**
 * io_pipe required by source libraries
 */
class source_io_pipe
{
  public:
    explicit source_io_pipe(std::shared_ptr<buffer> b) : buf(std::move(b)) {}

    template <typename T>
    void source_write(std::string const &key, T &&obj)
    {
        data_bucket bucket;
        bucket.put(key, std::forward<T>(obj));

        source_write(std::move(bucket));
    }

    void source_write(data_bucket data)
    {
        buf->write(std::move(data));
    }

    void source_complete()
    {
        buf->stop_writing();
    }

  private:
    std::shared_ptr<buffer> buf;
};

/**
 * io_pipe required by source nodes
 */
class io_pipe_for_source_node
{
  public:
    explicit io_pipe_for_source_node(std::shared_ptr<buffer> b) : buf(std::move(b)) {}

    bool is_empty()
    {
        return buf->is_empty();
    }

    data_bucket read()
    {
        return buf->read();
    }

  private:
    std::shared_ptr<buffer> buf;
};

/**
 * io_pipe required by sink libraries
 */
class sink_io_pipe
{
  public:
    explicit sink_io_pipe(std::shared_ptr<buffer> b) : buf(std::move(b)) {}

    data_bucket sink_read()
    {
        return buf->read();
    }

    bool sink_is_complete()
    {
        return buf->is_empty();
    }

  private:
    std::shared_ptr<buffer> buf;
};

/**
 * io_pipe required by sink nodes
 */
class io_pipe_for_sink_node
{
  public:
    explicit io_pipe_for_sink_node(std::shared_ptr<buffer> b) : buf(std::move(b)) {}

    void write(data_bucket data)
    {
        buf->write(std::move(data));
    }

    void stop_writing()
    {
        buf->stop_writing();
    }

  private:
    std::shared_ptr<buffer> buf;
};
} // namespace data_io

PVPF_NAMESPACE_END

#endif //DEV_ENV_IO_PIPE_H
