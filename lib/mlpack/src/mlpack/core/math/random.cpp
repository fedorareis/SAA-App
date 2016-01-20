/**
 * @file random.cpp
 *
 * Declarations of global random number generators.
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
#include <random>

namespace mlpack {
namespace math {

// Global random object.
std::mt19937 randGen;
// Global uniform distribution.
std::uniform_real_distribution<> randUniformDist(0.0, 1.0);
// Global normal distribution.
std::normal_distribution<> randNormalDist(0.0, 1.0);

} // namespace math
} // namespace mlpack
