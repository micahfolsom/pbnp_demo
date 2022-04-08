#ifndef NEUTRON_HPP
#define NEUTRON_HPP

#include <vector>
#include <memory>

namespace pbnp {
class Neutron {
  public:
    Neutron(): m_id(-1), m_data(0.f), m_parent(nullptr), m_children() {}
    Neutron(int id, float data, Neutron* parent = nullptr,
        std::vector<Neutron> const& children = {}):
      m_id(id), m_data(data), m_parent(parent), m_children(children) {}

    inline int get_id() const { return m_id; }
    inline void set_id(int id) { m_id = id; return; }
    inline float get_data() const { return m_data; }
    inline void set_data(float data) { m_data = data; return; }
    inline Neutron* get_parent() const { return m_parent; }
    inline void set_parent(Neutron* parent) { m_parent = parent; return; }
    inline std::vector<Neutron> const& get_children() const { return m_children; }
    inline void set_children(std::vector<Neutron> const& children) { m_children = children; return; }

    std::vector<Neutron> unfold();

  private:
    int m_id;
    float m_data;
    Neutron* m_parent;
    std::vector<Neutron> m_children;
    void retrieve(std::vector<Neutron> const& children, std::vector<Neutron>& output);
};
}

#endif
