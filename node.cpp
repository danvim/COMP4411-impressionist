#include "node.h"
#include "PowerIter.h"

extern std::stringstream ss;

Node::Node()
{
}

// intensity in r,g,b channels, w as weight
Node::Node(MatrixXd m, VectorXd w):m(m),w(w)
{
	// Vector3d mean;
	// mean << r.mean(), g.mean(), b.mean();
	int size = w.size();
	W = w.sum();

	//weighted mean
	// mu = m.transpose()*w / W;
	mu = VectorXd(3);
	mu(0) = (m.col(0).dot(w)) / W;
	mu(1) = (m.col(1).dot(w)) / W;
	mu(2) = (m.col(2).dot(w)) / W;

	//difference of itself and mean
	d = MatrixXd(size, 3);
	d << m;
	for(int i=0; i<size;i++)
	{
		d.row(i) -= mu;
	}

	//c as covariance
	c = MatrixXd(3, 3);
	t = MatrixXd(size, 3);
	for (int i = 0; i< size; i++)
	{
		float sqi = sqrt(w(i));
		for (int j = 0; j<3; j++)
		{
			t(i, j) = d(i, j)*sqi;
		}
	}
	c = t.transpose() * t * (1.0 / W) + 1e-5 * Matrix3d::Identity();
	
	PowerIter pi(c);
	l = pi.l;
	e = pi.e;
	// ss << "cov"<<std::endl<<c<< std::endl<<"eigenvectors" << std::endl<< es.eigenvectors()<<std::endl<< "lambdas"<<es.eigenvalues()<<std::endl;
}
