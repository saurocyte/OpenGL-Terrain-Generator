#ifndef PERLIN
#define PERLIN

#include <cmath>
#include <random>
#include <vector>
#include <glm/glm.hpp>

template<uint rows, uint columns>
class Terrain {
  public:
    Terrain() {
      gradient = new double**[rows];
      for (int i = 0; i < rows; ++i) {
        gradient[i] = new double*[columns];
        for (int j = 0; j < columns; ++j) {
          gradient[i][j] = new double[2];
        }
      }
      double terrain[rows][columns];
      generate_terrain(terrain, 10);
      generate_transitions(terrain, transitions);
    }

    inline std::vector<glm::vec4> getTransitions() const {return transitions;};
  private:
    // Linear interpolation between a0 and a1
    double lerp(double a0, double a1, double w) {  
      return (1.0 - w) * a0 + w * a1;
    }
    // Dot product of distance and gradient
    double dotGridGradient(int ix, int iy, double x, double y) {
      // compute the distance vector
      double dx = x - ix;
      double dy = y - iy;
      // compute dot-product
      return (dx*gradient[iy][ix][0] + dy*gradient[iy][ix][1]);
    }
    // Compute perlin noise at (x, y)
    double perlin(double x, double y) {
      // determine grid cell coordinates
      int x0 = std::floor(x);
      int x1 = x0 + 1;
      int y0 = std::floor(y);
      int y1 = y0 + 1;
    
      // determine interpolation weights
      // could also use higher order polynomial/s-curve here
      auto sx = x - x0;
      auto sy = y - y0;
    
      // interpolate between grid point gradients
      auto n0 = dotGridGradient(x0, y0, x, y);
      auto n1 = dotGridGradient(x1, y0, x, y);
      auto ix0 = lerp(n0, n1, sx);
      n0 = dotGridGradient(x0, y1, x, y);
      n1 = dotGridGradient(x1, y1, x, y);
      auto ix1 = lerp(n0, n1, sx);
      auto value = lerp(ix0, ix1, sy);
    
      return value;
    }
    
    void generate_gradient_matrix(double ***grad) {
      std::random_device rd; 
      std::mt19937 gen(rd());
      std::uniform_real_distribution<> dis(0.0, 2.0);

      for (auto i = 0; i < rows; ++i) {
        for (auto j = 0; j < columns; ++j) {
          grad[i][j][0] = dis(gen);
          grad[i][j][1] = dis(gen);
        }
      }
    }

    void generate_terrain(double (&terrain)[rows][columns], uint number_of_iterations) {
      generate_gradient_matrix(gradient);

      for (auto i = 0; i < rows; ++i) {
        for (auto j = 0; j < columns; ++j) {
          terrain[i][j] = perlin(i * 0.135f, j * 0.135f) + 0.5f;
        }
      }
    };

    void generate_transitions(double (&terrain)[rows][columns], std::vector<glm::vec4>& transition) {
      for (auto i = 0; i < rows; ++i) {
        for (auto j = 0; j < columns; ++j) {
          terrain[i][j] *= 6.75;
          terrain[i][j] = std::round(terrain[i][j]);
        }
      }

      for (auto i = 0; i < rows; ++i) {
        for (auto j = 0; j < columns; ++j) {
          for (auto h = 0; h < terrain[i][j]; ++h) {
            transition.push_back(glm::vec4(i * 0.5f, h / 2.0, j * 0.5f, h == (terrain[i][j] - 1)) * 2.0f);
          }
        }
      }
    };

    double ***gradient;
    std::vector<glm::vec4> transitions;
};



#endif