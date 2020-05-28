#include "header/solution.h"

Solution::Solution(SolOrder order, vector<double> axisg_eval)
{
	this->order = order;
	this->axisg_eval = axisg_eval;
}

Solution::~Solution()
{
}

SolOrder Solution::get_order()
{
	return order;
}

vector<double> Solution::get_axis_eval()
{
	return axisg_eval;
}
