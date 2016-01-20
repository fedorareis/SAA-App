/**
 * @file r_star_tree_descent_heuristic.hpp
 * @author Andrew Wells
 *
 * Definition of RStarTreeDescentHeuristic, a class that chooses the best child
 * of a node in an R tree when inserting a new point.
 *
 * This file is part of mlpack 2.0.0.
 *
 * mlpack is free software: you can redistribute it and/or modify it under the
 * terms of the GNU Lesser General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option) any
 * later version.
 *
 * mlpack is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
 * details (LICENSE.txt).
 *
 * You should have received a copy of the GNU General Public License along with
 * mlpack.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef __MLPACK_CORE_TREE_RECTANGLE_TREE_R_STAR_TREE_DESCENT_HEURISTIC_HPP
#define __MLPACK_CORE_TREE_RECTANGLE_TREE_R_STAR_TREE_DESCENT_HEURISTIC_HPP

#include <mlpack/core.hpp>

namespace mlpack {
namespace tree {

/**
 * When descending a Rectangle tree to insert a point, we need to have a way to
 * choose a child node when the point isn't enclosed by any of them.  This
 * heuristic is used to do so.
 */
class RStarTreeDescentHeuristic
{
 public:
  /**
   * Evaluate the node using a hueristic.  The heuristic guarantees two things:
   *
   * 1.  If point is contained in (or on) bound, the value returned is zero.
   * 2.  If the point is not contained in (or on) bound, the value returned is
   *     greater than zero.
   *
   * @param bound The bound used for the node that is being evaluated.
   * @param point The point that is being inserted.
   */
  template<typename TreeType>
  static size_t ChooseDescentNode(const TreeType* node, const arma::vec& point);

  template<typename TreeType>
  static size_t ChooseDescentNode(const TreeType* node,
                                  const TreeType* insertedNode);
};

} // namespace tree
} // namespace mlpack

// Include implementation.
#include "r_star_tree_descent_heuristic_impl.hpp"

#endif
