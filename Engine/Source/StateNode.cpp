// 8 Puzzle Solver Algorithm Assignment
// Assignment #1
// Author : Mario Garcia
// Class : CS 420
// Instructor : Dr. Daisy Tang
//
// Copyright (c) 2017 Mario Garcia, MIT License.
// Built with my cat Tom. mew...
#include "StateNode.hpp"

#include <limits>


namespace pai { 


node_uid_t StateNode::id_count = static_cast<node_uid_t>(0);
const node_uid_t StateNode::nan = (std::numeric_limits<node_uid_t>::max)();
} // pai