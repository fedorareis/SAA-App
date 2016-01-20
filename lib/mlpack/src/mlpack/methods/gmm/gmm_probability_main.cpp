/**
 * @file gmm_probability_main.cpp
 * @author Ryan Curtin
 *
 * Given a GMM, calculate the probability of points coming from it.
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
#include <mlpack/core.hpp>
#include "gmm.hpp"

using namespace std;
using namespace mlpack;
using namespace mlpack::gmm;

PROGRAM_INFO("GMM Probability Calculator",
    "This program calculates the probability that given points came from a "
    "given GMM (that is, P(X | gmm)).  The GMM is specified with the "
    "--input_model_file option, and the points are specified with the "
    "--input_file option.  The output probabilities are stored in the file "
    "specified by the --output_file option.");

PARAM_STRING_REQ("input_model_file", "File containing input GMM.", "m");
PARAM_STRING_REQ("input_file", "File containing points.", "i");

PARAM_STRING("output_file", "File to save calculated probabilities to.", "o",
    "output.csv");

int main(int argc, char** argv)
{
  CLI::ParseCommandLine(argc, argv);

  // Get the GMM and the points.
  GMM gmm;
  data::Load(CLI::GetParam<string>("input_model_file"), "gmm", gmm);

  arma::mat dataset;
  data::Load(CLI::GetParam<string>("input_file"), dataset);

  // Now calculate the probabilities.
  arma::rowvec probabilities(dataset.n_cols);
  for (size_t i = 0; i < dataset.n_cols; ++i)
    probabilities[i] = gmm.Probability(dataset.unsafe_col(i));

  // And save the result.
  data::Save(CLI::GetParam<string>("output_file"), probabilities);
}
