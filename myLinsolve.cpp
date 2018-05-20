
#include <octave/oct.h>
#include <mkl_cblas.h>
#include <mkl_lapacke.h>

void print_usage ()
{
   octave_stdout << "bad!" << std::endl;
}

DEFUN_DLD (myLinsolve, args, nargout,
           "Help String")
{
   int nargin = args.length ();

   if (nargin != 2)
      print_usage ();
   else
   {
      ComplexMatrix A = args(0).complex_matrix_value ();
      ComplexMatrix B = args(1).complex_matrix_value ();

      octave_idx_type nr = A.rows();
      Array<octave_idx_type> ipvt (dim_vector (nr, 1));
      octave_idx_type * pipvt = ipvt.fortran_vec ();
      MKL_Complex16 * adata = reinterpret_cast<MKL_Complex16*>(const_cast<Complex*>(A.data ()));

      int iret;
      iret = LAPACKE_zgetrf(LAPACK_COL_MAJOR, nr, nr, adata, nr, pipvt);
      octave_stdout << "LAPACKE_zgetrf returned " << iret << std::endl;

      ComplexMatrix x = B;
      MKL_Complex16 * xdata = reinterpret_cast<MKL_Complex16*>(x.fortran_vec ());
      octave_idx_type xnr = B.rows();
      octave_idx_type xnc = B.cols();

      iret = LAPACKE_zgetrs(LAPACK_COL_MAJOR, 'N', nr, xnc,
                            adata, nr, pipvt, xdata, xnr);
      octave_stdout << "LAPACKE_sgetrs returned " << iret << std::endl;

      return octave_value (x);
   }

   return octave_value_list ();
}
