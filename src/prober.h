// Copyright 2017 Evan Klitzke <evan@eklitzke.org>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include <chrono>
#include <string>

#include "./pyfrob.h"
#include "./symbol.h"

// Maximum number of times to retry checking for Python symbols when -p is used.
#define MAX_ATTACH_RETRIES 1

// Maximum number of times to retry checking for Python symbols when -t is used.
#define MAX_TRACE_RETRIES 50

namespace pyflame {

class Prober {
 public:
  Prober() = default;
  Prober(const Prober &other) = delete;

  int ParseOpts(int argc, char **argv);

  int InitiatePtrace(char **argv);

  int FindSymbols(PyFrob *frobber);

  int Run(const PyFrob &frobber);

  bool enable_threads() const { return enable_threads_; }
  pid_t pid() const { return pid_; }

 private:
  PyABI abi_{PyABI::Unknown};
  pid_t pid_{-1};
  bool dump_{false};
  bool trace_{false};
  bool include_idle_{true};
  bool include_ts_{false};
  bool include_line_number_{true};
  bool enable_threads_{true};
  double seconds_{1.0};
  double sample_rate_{0.01};
  std::chrono::microseconds interval_;
  std::string output_file_;
  std::string trace_target_;

  int ProbeLoop(const PyFrob &frobber, std::ostream *out);

  static pid_t ParsePid(const char *pid_str);

  static int DumpStacks(const PyFrob &frobber, std::ostream *out);

  size_t MaxRetries() const {
    return trace_ ? MAX_TRACE_RETRIES : MAX_ATTACH_RETRIES;
  }
};
}  // namespace pyflame
