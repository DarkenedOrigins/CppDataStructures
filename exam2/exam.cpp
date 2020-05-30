#include "exam.h"
#include "matrix.h"
namespace exam{
	Matrix flip_vert(const Matrix &m){
		Matrix n(m.get_num_rows(), m.get_num_columns());
		for(int i=0; i < m.get_num_rows(); i++){
			for(int j=0; j < m.get_num_columns(); j++){
				n.set_coord( i, m.get_num_columns()-1-j, m.get_coord(i,j) );
			}
		}
		return n;
	}
}
