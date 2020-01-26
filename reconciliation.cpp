#include "reconciliation.h"
#include "algorithm.h"

using namespace Cascade;

Reconciliation::Reconciliation(std::string algorithm_name,
                               const Key& noisy_key,
                               double bit_error_rate):
    noisy_key(noisy_key),
    bit_error_rate(bit_error_rate)
{
#pragma GCC diagnostic ignored "-Wunused-private-field"   // TODO    
    this->algorithm = Algorithm::get_by_name(algorithm_name);
    assert(this->algorithm != NULL);
}