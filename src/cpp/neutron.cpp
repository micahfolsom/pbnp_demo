#include "neutron.hpp"
using namespace std;

namespace pbnp {
  vector<Neutron> Neutron::unfold() {
    vector<Neutron> output;
    // Will help performance - if you're expecting more, then make it bigger
    output.reserve(1000);
    retrieve(m_children, output);
    return output;
  }

  void Neutron::retrieve(vector<Neutron> const& children, vector<Neutron>& output) {
    for (auto const& child : children) {
      output.emplace_back(child);
      retrieve(child.get_children(), output);
    }
    return;
  }
}
