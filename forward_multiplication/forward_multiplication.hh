#pragma once

#include <functional>

using inner_lambda_type = const std::function<int(int rhs)>;
using outer_lambda_type = const std::function<inner_lambda_type(int lhs)>;
extern outer_lambda_type mult_by;
