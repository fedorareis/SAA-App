/**
 * @file allow_empty_clusters.hpp
 * @author Ryan Curtin
 *
 * This very simple policy is used when K-Means is allowed to return empty
 * clusters.
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
#ifndef __MLPACK_METHODS_KMEANS_ALLOW_EMPTY_CLUSTERS_HPP
#define __MLPACK_METHODS_KMEANS_ALLOW_EMPTY_CLUSTERS_HPP

#include <mlpack/core.hpp>

namespace mlpack {
namespace kmeans {

/**
 * Policy which allows K-Means to create empty clusters without any error being
 * reported.
 */
class AllowEmptyClusters
{
 public:
  //! Default constructor required by EmptyClusterPolicy policy.
  AllowEmptyClusters() { }

  /**
   * This function does nothing.  It is called by K-Means when K-Means detects
   * an empty cluster.
   *
   * @tparam MatType Type of data (arma::mat or arma::spmat).
   * @param data Dataset on which clustering is being performed.
   * @param emptyCluster Index of cluster which is empty.
   * @param oldCentroids Centroids of each cluster (one per column) at the start
   *      of the iteration.
   * @param newCentroids Centroids of each cluster (one per column) at the end
   *      of the iteration.
   * @param clusterCounts Number of points in each cluster.
   * @param assignments Cluster assignments of each point.
   * @param iteration Number of iteration.
   *
   * @return Number of points changed (0).
   */
  template<typename MetricType, typename MatType>
  static inline force_inline size_t EmptyCluster(
      const MatType& /* data */,
      const size_t /* emptyCluster */,
      const arma::mat& /* oldCentroids */,
      arma::mat& /* newCentroids */,
      arma::Col<size_t>& /* clusterCounts */,
      MetricType& /* metric */,
      const size_t /* iteration */)
  {
    // Empty clusters are okay!  Do nothing.
    return 0;
  }

  //! Serialize the empty cluster policy (nothing to do).
  template<typename Archive>
  void Serialize(Archive& /* ar */, const unsigned int /* version */) { }
};

} // namespace kmeans
} // namespace mlpack

#endif
