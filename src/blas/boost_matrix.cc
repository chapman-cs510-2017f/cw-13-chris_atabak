#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>



void create_plane(long double xmin, long double xmax, int xlen, long double ymin, long double ymax, int ylen);





int main(int argc, char **argv) 
{
  // exploit namespaces to shorten code
  using namespace boost::numeric::ublas;
  using std::cout; 
  using std::endl;

  create_plane(0,10,3,0,10,3);
    
  // declare three 3x3 matrices of complex<long double> elements
  matrix<std::complex<long double> > m(3, 3), n(3, 3), o(3, 3);

  // iterate over 3x3 matrix entries
  // r : row index
  // c : column index
  for (unsigned r = 0; r < m.size1(); r++) {
    for (unsigned c = 0; c < m.size2(); c++) {
      // enumerated matrix entries
      m(r,c) = 3 * r + c;

      // complex numbers designating rows and cols
      n(r,c) = r + c * std::complex<long double>(0,1); 

      // elementwise square of n
      o(r,c) = std::pow(n(r,c), 2);
    }
  }
    
  // print to screen as demonstration
  cout << "m:" << endl;
  cout << m << endl;
  cout << endl << "n:" << endl;
  cout << n << endl;
  cout << endl << "o:" << endl;
  cout << n << endl;
  cout << endl << "m + n:" << endl;
  cout << m + n << endl;
  cout << endl << "m * n:" << endl;
  cout << prod(m, n) << endl;
  cout << endl << "n * n - o:" << endl;
  cout << prod(n, n) - o << endl;
}

void create_plane(long double xmin, long double xmax, int xlen, long double ymin, long double ymax, int ylen) {
    
    using namespace boost::numeric::ublas;
    using std::cout;
    using std::endl;
    
    long double dx = (xmax-xmin)/(xlen-1);
    long double dy = (ymax-ymin)/(ylen-1);
    
    matrix<std::complex<long double> > cplane(xlen, ylen);
    
    for (unsigned r = 0; r < cplane.size1(); r++) {
        for (unsigned c = 0; c < cplane.size2(); c++) {
            
            cplane(r,c) =std::complex<long double>(xmin + c*dy, ymin + r*dy);
            
        }
    }

    for (unsigned int i=0; i<cplane.size1(); i++) {
      for (unsigned int j=0; j<cplane.size2(); j++) {
          std::cout <<cplane(i,j) << ", ";
      }
      std::cout << std::endl;
    }
}

