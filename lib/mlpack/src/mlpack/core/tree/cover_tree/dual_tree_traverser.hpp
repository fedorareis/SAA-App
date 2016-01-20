/**
 * @file dual_tree_traverser.hpp
 * @author Ryan Curtin
 *
 * A dual-tree traverser for the cover tree.
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
#ifndef __MLPACK_CORE_TREE_COVER_TREE_DUAL_TREE_TRAVERSER_HPP
#define __MLPACK_CORE_TREE_COVER_TREE_DUAL_TREE_TRAVERSER_HPP

#include <mlpack/core.hpp>
#include <queue>

namespace mlpack {
namespace tree {

template<
    typename MetricType,
    typename StatisticType,
    typename MatType,
    typename RootPointPolicy
>
template<typename RuleType>
class CoverTree<MetricType, StatisticType, MatType, RootPointPolicy>::
    DualTreeTraverser
{
 public:
  /**
   * Initialize the dual tree traverser with the given rule type.
   */
  DualTreeTraverser(RuleType& rule);

  /**
   * Traverse the two specified trees.
   *
   * @param queryNode Root of query tree.
   * @param referenceNode Root of reference tree.
   */
  void Traverse(CoverTree& queryNode, CoverTree& referenceNode);

  //! Get the number of pruned nodes.
  size_t NumPrunes() const { return numPrunes; }
  //! Modify the number of pruned nodes.
  size_t& NumPrunes() { return numPrunes; }

  ///// These are all fake because this is a patch for kd-trees only and I still
  ///// want it to compile!
  size_t NumVisited() const { return 0; }
  size_t NumScores() const { return 0; }
  size_t NumBaseCases() const { return 0; }

 private:
  //! The instantiated rule set for pruning branches.
  RuleType& rule;

  //! The number of pruned nodes.
  size_t numPrunes;

  //! Struct used for traversal.
  struct DualCoverTreeMapEntry
  {
    //! The node this entry refers to.
    CoverTree<MetricType, StatisticType, MatType, RootPointPolicy>*
        referenceNode;
    //! The score of the node.
    double score;
    //! The base case.
    double baseCase;
    //! The traversal info associated with the call to Score() for this entry.
    typename RuleType::TraversalInfoType traversalInfo;

    //! Comparison operator, for sorting within the map.
    bool operator<(const DualCoverTreeMapEntry& other) const
    {
      if (score == other.score)
        return (baseCase < other.baseCase);
      else
        return (score < other.score);
    }
  };

  /**
   * Helper function for traversal of the two trees.
   */
  void Traverse(CoverTree& queryNode,
                std::map<int, std::vector<DualCoverTreeMapEntry> >&
                    referenceMap);

  //! Prepare map for recursion.
  void PruneMap(CoverTree& queryNode,
                std::map<int, std::vector<DualCoverTreeMapEntry> >&
                    referenceMap,
                std::map<int, std::vector<DualCoverTreeMapEntry> >&
                    childMap);

  void ReferenceRecursion(CoverTree& queryNode,
                          std::map<int, std::vector<DualCoverTreeMapEntry> >&
                              referenceMap);
};

} // namespace tree
} // namespace mlpack

// Include implementation.
#include "dual_tree_traverser_impl.hpp"

#endif
