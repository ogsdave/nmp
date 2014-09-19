#pragma once
////////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2014 Gonzalo Brito Gadeschi.
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////
///
/// \file all_gather.hpp
///
/// Description
///
////////////////////////////////////////////////////////////////////////////////
#include <future>
#include <nmp/comm.hpp>
#include <nmp/concepts.hpp>
#include <nmp/nmp_fwd.hpp>
#include <nmp/data_type/skeleton.hpp>
////////////////////////////////////////////////////////////////////////////////

namespace nmp {

template <class Message, NMP_REQUIRES_(nmp::models::message<Message>{})>
auto all_gather(nmp::comm c, Message&& m) {
  auto s = skeleton(m);

  return std::async([=]() {
    NMP_NBC(MPI_Iallgather, MPI_IN_PLACE, 0, MPI_DATATYPE_NULL, s.data_ptr,
            s.size, s.mpi_data_type, c());
    return;
  });
}

}  // namespace nmp
////////////////////////////////////////////////////////////////////////////////
