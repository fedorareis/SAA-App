/**
 * @file fastmks.hpp
 * @author Ryan Curtin
 *
 * Definition of the FastMKS class, which implements fast exact max-kernel
 * search.
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
#ifndef __MLPACK_METHODS_FASTMKS_FASTMKS_HPP
#define __MLPACK_METHODS_FASTMKS_FASTMKS_HPP

#include <mlpack/core.hpp>
#include <mlpack/core/metrics/ip_metric.hpp>
#include "fastmks_stat.hpp"
#include <mlpack/core/tree/cover_tree.hpp>

namespace mlpack {
namespace fastmks /** Fast max-kernel search. */ {

/**
 * An implementation of fast exact max-kernel search.  Given a query dataset and
 * a reference dataset (or optionally just a reference dataset which is also
 * used as the query dataset), fast exact max-kernel search finds, for each
 * point in the query dataset, the k points in the reference set with maximum
 * kernel value K(p_q, p_r), where k is a specified parameter and K() is a
 * Mercer kernel.
 *
 * For more information, see the following paper.
 *
 * @code
 * @inproceedings{curtin2013fast,
 *   title={Fast Exact Max-Kernel Search},
 *   author={Curtin, Ryan R. and Ram, Parikshit and Gray, Alexander G.},
 *   booktitle={Proceedings of the 2013 SIAM International Conference on Data
 *       Mining (SDM 13)},
 *   year={2013}
 * }
 * @endcode
 *
 * This class allows specification of the type of kernel and also of the type of
 * tree.  FastMKS can be run on kernels that work on arbitrary objects --
 * however, this only works with cover trees and other trees that are built only
 * on points in the dataset (and not centroids of regions or anything like
 * that).
 *
 * @tparam KernelType Type of kernel to run FastMKS with.
 * @tparam MatType Type of data matrix (usually arma::mat).
 * @tparam TreeType Type of tree to run FastMKS with; it must satisfy the
 *     TreeType policy API.
 */
template<
    typename KernelType,
    typename MatType = arma::mat,
    template<typename TreeMetricType,
             typename TreeStatType,
             typename TreeMatType> class TreeType = tree::StandardCoverTree
>
class FastMKS
{
 public:
  //! Convenience typedef.
  typedef TreeType<metric::IPMetric<KernelType>, FastMKSStat, MatType> Tree;

  /**
   * Create the FastMKS object with an empty reference set and default kernel.
   * Make sure to call Train() before Search() is called!
   *
   * @param singleMode Whether or not to run single-tree search.
   * @param naive Whether or not to run brute-force (naive) search.
   */
  FastMKS(const bool singleMode = false, const bool naive = false);

  /**
   * Create the FastMKS object with the given reference set (this is the set
   * that is searched).  Optionally, specify whether or not single-tree search
   * or naive (brute-force) search should be used.
   *
   * @param referenceSet Set of reference data.
   * @param singleMode Whether or not to run single-tree search.
   * @param naive Whether or not to run brute-force (naive) search.
   */
  FastMKS(const MatType& referenceSet,
          const bool singleMode = false,
          const bool naive = false);

  /**
   * Create the FastMKS object using the reference set (this is the set that is
   * searched) with an initialized kernel.  This is useful for when the kernel
   * stores state.  Optionally, specify whether or not single-tree search or
   * naive (brute-force) search should be used.
   *
   * @param referenceSet Reference set of data for FastMKS.
   * @param kernel Initialized kernel.
   * @param single Whether or not to run single-tree search.
   * @param naive Whether or not to run brute-force (naive) search.
   */
  FastMKS(const MatType& referenceSet,
          KernelType& kernel,
          const bool singleMode = false,
          const bool naive = false);

  /**
   * Create the FastMKS object with an already-initialized tree built on the
   * reference points.  Be sure that the tree is built with the metric type
   * IPMetric<KernelType>.  Optionally, whether or not to run single-tree search
   * can be specified.  Brute-force search is not available with this
   * constructor since a tree is given (use one of the other constructors).
   *
   * @param referenceTree Tree built on reference data.
   * @param single Whether or not to run single-tree search.
   * @param naive Whether or not to run brute-force (naive) search.
   */
  FastMKS(Tree* referenceTree,
          const bool singleMode = false);

  //! Destructor for the FastMKS object.
  ~FastMKS();

  /**
   * "Train" the FastMKS model on the given reference set (this will just build
   * a tree, if the current search mode is not naive mode).
   *
   * @param referenceSet Set of reference points.
   */
  void Train(const MatType& referenceSet);

  /**
   * "Train" the FastMKS model on the given reference set and use the given
   * kernel.  This will just build a tree and replace the metric, if the current
   * search mode is not naive mode.
   *
   * @param referenceSet Set of reference points.
   * @param kernel Kernel to use for search.
   */
  void Train(const MatType& referenceSet, KernelType& kernel);

  /**
   * Train the FastMKS model on the given reference tree.  This takes ownership
   * of the tree, so you do not need to delete it!  This will throw an exception
   * if the model is searching in naive mode (i.e. if Naive() == true).
   *
   * @param tree Tree to use as reference data.
   */
  void Train(Tree* referenceTree);

  /**
   * Search for the points in the reference set with maximum kernel evaluation
   * to each point in the given query set.  The resulting kernel evaluations are
   * stored in the kernels matrix, and the corresponding point indices are
   * stored in the indices matrix.  The results for each point in the query set
   * are stored in the corresponding column of the kernels and products
   * matrices; for instance, the index of the point with maximum kernel
   * evaluation to point 4 in the query set will be stored in row 0 and column 4
   * of the indices matrix.
   *
   * If querySet only contains a few points, the extra overhead of building a
   * tree to perform dual-tree search may not be warranted, and it may be faster
   * to use single-tree search, either by setting singleMode to false in the
   * constructor or with SingleMode().
   *
   * @param querySet Set of query points (can be a single point).
   * @param k The number of maximum kernels to find.
   * @param indices Matrix to store resulting indices of max-kernel search in.
   * @param kernels Matrix to store resulting max-kernel values in.
   */
  void Search(const MatType& querySet,
              const size_t k,
              arma::Mat<size_t>& indices,
              arma::mat& kernels);

  /**
   * Search for the points in the reference set with maximum kernel evaluation
   * to each point in the query set corresponding to the given pre-built query
   * tree.  The resulting kernel evaluations are stored in the kernels matrix,
   * and the corresponding point indices are stored in the indices matrix.  The
   * results for each point in the query set are stored in the corresponding
   * column of the kernels and products matrices; for instance, the index of the
   * point with maximum kernel evaluation to point 4 in the query set will be
   * stored in row 0 and column 4 of the indices matrix.
   *
   * This will throw an exception if called while the FastMKS object has
   * 'single' set to true.
   *
   * Be aware that if your tree modifies the original input matrix, the results
   * here are with respect to the modified input matrix (that is,
   * queryTree->Dataset()).
   *
   * @param queryTree Tree built on query points.
   * @param k The number of maximum kernels to find.
   * @param indices Matrix to store resulting indices of max-kernel search in.
   * @param kernels Matrix to store resulting max-kernel values in.
   */
  void Search(Tree* querySet,
              const size_t k,
              arma::Mat<size_t>& indices,
              arma::mat& kernels);

  /**
   * Search for the maximum inner products of the query set (or if no query set
   * was passed, the reference set is used).  The resulting maximum inner
   * products are stored in the products matrix and the corresponding point
   * indices are stores in the indices matrix.  The results for each point in
   * the query set are stored in the corresponding column of the indices and
   * products matrices; for instance, the index of the point with maximum inner
   * product to point 4 in the query set will be stored in row 0 and column 4 of
   * the indices matrix.
   *
   * @param k The number of maximum kernels to find.
   * @param indices Matrix to store resulting indices of max-kernel search in.
   * @param products Matrix to store resulting max-kernel values in.
   */
  void Search(const size_t k,
              arma::Mat<size_t>& indices,
              arma::mat& products);

  //! Get the inner-product metric induced by the given kernel.
  const metric::IPMetric<KernelType>& Metric() const { return metric; }
  //! Modify the inner-product metric induced by the given kernel.
  metric::IPMetric<KernelType>& Metric() { return metric; }

  //! Get whether or not single-tree search is used.
  bool SingleMode() const { return singleMode; }
  //! Modify whether or not single-tree search is used.
  bool& SingleMode() { return singleMode; }

  //! Get whether or not brute-force (naive) search is used.
  bool Naive() const { return naive; }
  //! Modify whether or not brute-force (naive) search is used.
  bool& Naive() { return naive; }

  //! Serialize the model.
  template<typename Archive>
  void Serialize(Archive& ar, const unsigned int /* version */);

 private:
  //! The reference dataset.  We never own this; only the tree or a higher level
  //! does.
  const MatType* referenceSet;
  //! The tree built on the reference dataset.
  Tree* referenceTree;
  //! If true, this object created the tree and is responsible for it.
  bool treeOwner;
  //! If true, we own the dataset.  This happens in only a few situations.
  bool setOwner;

  //! If true, single-tree search is used.
  bool singleMode;
  //! If true, naive (brute-force) search is used.
  bool naive;

  //! The instantiated inner-product metric induced by the given kernel.
  metric::IPMetric<KernelType> metric;

  //! Utility function.  Copied too many times from too many places.
  void InsertNeighbor(arma::Mat<size_t>& indices,
                      arma::mat& products,
                      const size_t queryIndex,
                      const size_t pos,
                      const size_t neighbor,
                      const double distance);
};

} // namespace fastmks
} // namespace mlpack

// Include implementation.
#include "fastmks_impl.hpp"

#endif
