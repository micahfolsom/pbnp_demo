#ifndef GADGET_HPP
#define GADGET_HPP
#include <pybind11/numpy.h>
#include <vector>

namespace pbnp {
  typedef std::vector<std::vector<int>> Vector2D;
  typedef std::vector<std::vector<std::vector<int>>> Vector3D;

  /*! \class Gadget
   * It does a thing. */
  class Gadget {
    public:
      Gadget(int N = 100);

      // The same numpy object, regardless of dimensionality
      // We will use .resize({dim0, dim1, ...}) to change the shape
      pybind11::array_t<int> get_data() const;
      void set_data(pybind11::array_t<int> data);
      pybind11::array_t<int> get_data_2d() const;
      void set_data_2d(pybind11::array_t<int> data);
      pybind11::array_t<int> get_data_3d() const;
      void set_data_3d(pybind11::array_t<int> data);

    private:
      // Let's say, hypothetically, we're restricted by another API and
      // data is stored in another structure, like a vector
      // We're always gonna eat the cost of copying the data
      std::vector<int> m_data;
      Vector2D m_data2D;
      Vector3D m_data3D;
  };
}

#endif
