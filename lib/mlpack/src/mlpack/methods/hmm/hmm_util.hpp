/**
 * @file hmm_util.hpp
 * @author Ryan Curtin
 *
 * Utility to read HMM type from file.
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
#ifndef __MLPACK_METHODS_HMM_HMM_UTIL_HPP
#define __MLPACK_METHODS_HMM_HMM_UTIL_HPP

#include <mlpack/core.hpp>

namespace mlpack {
namespace hmm {

//! HMMType, to be stored on disk.  This is of type char, which is one byte.
//! (I'm not sure what will happen on systems where one byte is not eight bits.)
enum HMMType : char
{
  DiscreteHMM = 0,
  GaussianHMM,
  GaussianMixtureModelHMM
};

//! ActionType should implement static void Apply(HMMType&).
template<typename ActionType, typename ExtraInfoType = void>
void LoadHMMAndPerformAction(const std::string& modelFile,
                             ExtraInfoType* x = NULL);

//! Save an HMM to a file.  The file must also encode what type of HMM is being
//! stored.
template<typename HMMType>
void SaveHMM(HMMType& hmm, const std::string& modelFile);

} // namespace hmm
} // namespace mlpack

#include "hmm_util_impl.hpp"

#endif
