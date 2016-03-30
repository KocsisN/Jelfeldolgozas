#ifndef BAND_MATRIX_H
#define BAND_MATRIX_H

#include<cassert>
#include<algorithm>
#include<vector>


namespace spline
{
	class band_matrix
	{
	private:
		std::vector< std::vector<double> > m_upper;  // upper band
		std::vector< std::vector<double> > m_lower;  // lower band
	public:
		band_matrix();		                          // constructor
		band_matrix(int dim, int n_u, int n_l);       // constructor
		~band_matrix();	                          // destructor
		void resize(int dim, int n_u, int n_l);      // init with dim,n_u,n_l
		int dim() const;                             // matrix dimension
		int num_upper() const;
		int num_lower() const;

		// access operator
		double & operator () (int i, int j);            // write
		double   operator () (int i, int j) const;      // read
		// we can store an additional diogonal (in m_lower)
		double& saved_diag(int i);
		double  saved_diag(int i) const;
		void lu_decompose();
		std::vector<double> r_solve(const std::vector<double>& b) const;
		std::vector<double> l_solve(const std::vector<double>& b) const;
		std::vector<double> lu_solve(const std::vector<double>& b,
			bool is_lu_decomposed = false);

	};
}


#endif