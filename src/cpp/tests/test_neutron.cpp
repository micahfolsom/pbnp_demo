#include "neutron.hpp"
#include <iostream>
using namespace std;
using namespace pbnp;

int main(int, char**) {
  Neutron n(0, 1e6f);
  vector<Neutron> children {
    Neutron(1, 100.f, &n),
    Neutron(2, 200.f, &n),
    Neutron(3, 300.f, &n),
    Neutron(4, 400.f, &n),
    Neutron(5, 500.f, &n),
  };
  n.set_children(children);

  cout << "n.id: " << n.get_id() << endl;
  cout << "n.data: " << n.get_data() << endl;
  for (size_t i=0;i < n.get_children().size();++i) {
    cout << "  n.children[" << i << "].id: " << n.get_children()[i].get_id() << endl;
  }


  int id = 6;
  for (auto& child : children) {
    vector<Neutron> gchildren(3);
    for (int i=0;i < 3;++i) {
      gchildren[i] = Neutron(id, 100. * (float)id, &child);
      ++id;
    }
    child.set_children(gchildren);
  }
  n.set_children(children);
  auto all_children = n.unfold();
  for (auto const& child: all_children) {
    cout << "n.id: " << child.get_id() << endl;
    cout << "  n.data: " << child.get_data() << endl;
    cout << "  n.parent: " << child.get_parent() << endl;
    cout << "  n.children.size(): " << child.get_children().size() << endl;
  }

  return 0;
}
