#include "gadget.hpp"

#include <iostream>
using namespace std;

namespace pbnp {
Gadget::Gadget(int N) {
  m_data = vector<int>(N);
  for (int i = 0; i < N; ++i) {
    m_data[i] = i;
  }

  m_data2D = vector<vector<int>>(N);
  for (int i = 0; i < N; ++i) {
    m_data2D[i] = vector<int>(N);
    for (int j = 0; j < N; ++j) {
      int index = (i * N) + j;
      m_data2D[i][j] = index;
    }
  }

  m_data3D = vector<vector<vector<int>>>(N);
  for (int i = 0; i < N; ++i) {
    m_data3D[i] = vector<vector<int>>(N);
    for (int j = 0; j < N; ++j) {
      m_data3D[i][j] = vector<int>(N);
      for (int k = 0; k < N; ++k) {
        int index = (i * N * N) + (j * N) + k;
        m_data3D[i][j][k] = index;
      }
    }
  }
}

pybind11::array_t<int> Gadget::get_data() const {
  pybind11::array_t<int> output(m_data.size());
  auto ptr = static_cast<int*>(output.request().ptr);
  for (size_t i = 0; i < m_data.size(); ++i) {
    ptr[i] = m_data[i];
  }
  return output;
}

void Gadget::set_data(pybind11::array_t<int> data) {
  auto ptr = static_cast<int*>(data.request().ptr);
  for (size_t i = 0; i < m_data2D.size(); ++i) {
    m_data[i] = ptr[i];
  }
  return;
}

pybind11::array_t<int> Gadget::get_data_2d() const {
  pybind11::array_t<int> output(m_data2D.size() * m_data2D[0].size());
  auto ptr = static_cast<int*>(output.request().ptr);
  for (size_t i = 0; i < m_data2D.size(); ++i) {
    for (size_t j = 0; j < m_data2D[0].size(); ++j) {
      // Row-major
      int idx = (i * (int)m_data2D[0].size()) + j;
      ptr[idx] = m_data2D[i][j];
    }
  }
  output.resize({m_data2D.size(), m_data2D[0].size()});
  return output;
}

void Gadget::set_data_2d(pybind11::array_t<int> data) {
  auto ptr = static_cast<int*>(data.request().ptr);
  for (size_t i = 0; i < m_data2D.size(); ++i) {
    for (size_t j = 0; j < m_data2D[0].size(); ++j) {
      // Row-major
      int idx = (i * (int)m_data2D[0].size()) + j;
      m_data2D[i][j] = ptr[idx];
    }
  }
  return;
}

pybind11::array_t<int> Gadget::get_data_3d() const {
  int dsize[3] = {(int)m_data3D.size(), (int)m_data3D[0].size(),
                  (int)m_data3D[0][0].size()};
  pybind11::array_t<int> output(dsize[0] * dsize[1] * dsize[2]);
  auto ptr = static_cast<int*>(output.request().ptr);
  for (int i = 0; i < dsize[0]; ++i) {
    for (int j = 0; j < dsize[1]; ++j) {
      for (int k = 0; k < dsize[2]; ++k) {
        // Row-major
        int idx = ((i * dsize[1] + j) * dsize[2]) + k;
        ptr[idx] = m_data3D[i][j][k];
      }
    }
  }
  output.resize({dsize[0], dsize[1], dsize[2]});
  return output;
}

void Gadget::set_data_3d(pybind11::array_t<int> data) {
  int dsize[3] = {(int)m_data3D.size(), (int)m_data3D[0].size(),
                  (int)m_data3D[0][0].size()};
  auto ptr = static_cast<int*>(data.request().ptr);
  for (int i = 0; i < dsize[0]; ++i) {
    for (int j = 0; j < dsize[1]; ++j) {
      for (int k = 0; k < dsize[2]; ++k) {
        // Row-major
        int idx = ((i * dsize[1] + j) * dsize[2]) + k;
        m_data3D[i][j][k] = ptr[idx];
      }
    }
  }
  return;
}

pybind11::array_t<int> Gadget::get_data_2d_cmaj() const {
  pybind11::array_t<int> output(m_data2D.size() * m_data2D[0].size());
  auto ptr = static_cast<int*>(output.request().ptr);
  for (size_t j = 0; j < m_data2D[0].size(); ++j) {
    for (size_t i = 0; i < m_data2D.size(); ++i) {
      // Column-major
      int idx = (i * (int)m_data2D[0].size()) + j;
      ptr[idx] = m_data2D[i][j];
    }
  }
  output.resize({m_data2D.size(), m_data2D[0].size()});
  return output;
}
pybind11::array_t<int> Gadget::get_data_3d_cmaj() const {
  int dsize[3] = {(int)m_data3D.size(), (int)m_data3D[0].size(),
                  (int)m_data3D[0][0].size()};
  pybind11::array_t<int> output(dsize[0] * dsize[1] * dsize[2]);
  auto ptr = static_cast<int*>(output.request().ptr);
  for (int k = 0; k < dsize[2]; ++k) {
    for (int j = 0; j < dsize[1]; ++j) {
      for (int i = 0; i < dsize[0]; ++i) {
        // Column-major
        int idx = ((i * dsize[1] + j) * dsize[2]) + k;
        ptr[idx] = m_data3D[i][j][k];
      }
    }
  }
  output.resize({dsize[0], dsize[1], dsize[2]});
  return output;
}
}  // namespace pbnp
