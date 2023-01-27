// FILE: poly.cpp
// CLASS IMPLEMENTED polynomial
//
// Jonathan Stock

#include <iostream>
#include <fstream>
#include <cassert>
#include <cmath>
#include <climits>
#include "poly.h"

using namespace std;

namespace coen79_lab4{

	//constructor for the polynomial object
	polynomial::polynomial(double c, unsigned int exponent){
		assert(exponent <= MAXIMUM_DEGREE);
		//assigning each coefficient to 0
		for(int i = 0; i < MAXIMUM_DEGREE+1; ++i){
			poly[i] = 0.0;
		}
		poly[exponent] = c;
		current_degree = exponent;
	}

	//updates the current degree
	void polynomial::update_current_degree(){
		//loops through the array to update the degree
		for(int i = MAXIMUM_DEGREE; i >= 0; --i){
			if(poly[i] != 0){
				current_degree = i;
			}
		}
	}

	//assigns the coefficient at the exponent given and updates the current degree
	void polynomial::assign_coef(double coefficient, unsigned int exponent){
		assert(exponent <= MAXIMUM_DEGREE);
		poly[exponent] = coefficient;
		update_current_degree();
	}

	//adds the coefficient to the exponent given and updates the current degree
	void polynomial::add_to_coef(double amount, unsigned int exponent){
		assert(exponent <= MAXIMUM_DEGREE);
		poly[exponent] += amount;
		update_current_degree();
	}

	//clears every entry in the array
	void polynomial::clear(){
		for(int i = MAXIMUM_DEGREE+1; i >= 0; --i){
			poly[i] = 0.0;
		}
		update_current_degree();
	}

	//calculates the antiderivative of the polynomial
	polynomial polynomial::antiderivative() const{
		assert(degree() < MAXIMUM_DEGREE);
		polynomial antiderivative;
		antiderivative.current_degree = current_degree + 1;
		//loops through the polynomial and calculates the antiderivative
		for(int i = 0; i <= current_degree; ++i){
			antiderivative.poly[i] = (poly[i]/(i+1));
		}
		for(int i = current_degree; i >= 0; --i){
			antiderivative.poly[i+1] = antiderivative.poly[i];
		}
		return antiderivative;
	}

	//returns the coefficient at the given polynomial
	double polynomial::coefficient(unsigned int exponent) const{
		if(exponent > MAXIMUM_DEGREE){
			return 0.0;
		}
		else{
			return poly[exponent];
		}
	}
	
	//calculates the definite integral of the polynomial from x0 to x1
	double polynomial::definite_integral(double x0, double x1) const{
		polynomial p;
		p = antiderivative();
		double area = 0.0;
		//loops through the polynomial and calculates the definite integral
		//after the antiderivative is calculated
		for(int i = 0; i < p.current_degree; ++i){
			area += p.poly[i] * (pow(x1,i) - pow(x0,i));
		}
		return area;
	}

	//returns the max degree of the polynomial
	unsigned int polynomial::degree() const{
		for(int i = MAXIMUM_DEGREE; i >= 0; --i){
			if(poly[i] != 0){
				return i;
			}
		}
		return 0;
	}

	//calculates the derivative of the polynomial
	polynomial polynomial::derivative() const{
		polynomial p;
		//loops through the polynomial calculating the derivative of each term
		for(int i = 0; i <= current_degree; ++i){
			p.poly[i] = (poly[i]*i);
			if(i != 0){
				p.poly[i-1] = p.poly[i];
			}
		}
		p.update_current_degree();
		return p;
	}

	//evaluates the polynomial with the given number for x
	double polynomial::eval(double x) const{
		double solution;
		//loops through the polynomial to calculate every term and adds to solution
		for(int i = 0; i <= current_degree; ++i){
			solution += (poly[i] * pow(x,i));
		}
		return solution;
	}

	//returns if the current degree is 0 or not
	bool polynomial::is_zero() const{
		if(current_degree == 0){	
			return true;
		}
		else{
			return false;
		}
	}

	//returns the next term after the given exponent if coefficient is not 0
	unsigned int polynomial::next_term(unsigned int e) const{
		for(int i = e+1; e < current_degree; ++i){
			if(poly[i] != 0){
				return i;
			}
		}
		return 0;
	}

	//returns the previous term before the given exponent if coefficient is not 0
	unsigned int polynomial::previous_term(unsigned int e) const{
		for(int i = e-1; i >= 0; --i){
			if(poly[i] != 0){
				return i;
			}
		}
		return UINT_MAX;
	}

	//returns the evaluation of x
	double polynomial::operator() (double x) const{
		return eval(x);
	}

	//adds two polynomials into 1 polynomial
	polynomial operator+ (const polynomial& p1, const polynomial& p2){
		polynomial p3 = polynomial();
		double amount = 0.0;
		//loops through to add each term
		for(int i = 0; i < polynomial::MAXIMUM_DEGREE+1; ++i){	
			amount = p1.coefficient(i) + p2.coefficient(i);
			p3.add_to_coef(amount,i);
		}
		return p3;
	}

	//subtracts two polynomials into 1 polynomial
	polynomial operator- (const polynomial& p1, const polynomial& p2){
		polynomial p3 = polynomial();
		double amount = 0.0;
		//loops through to subtract each term
		for(int i = 0; i < polynomial::MAXIMUM_DEGREE+1; ++i){
			amount = (p1.coefficient(i) - p2.coefficient(i));
			p3.add_to_coef(amount,i);
		}
		return p3;
	}

	//multiplies two polynomials into 1 polynomial
	polynomial operator* (const polynomial& p1, const polynomial& p2){
		assert(p1.degree() + p2.degree() <= polynomial::MAXIMUM_DEGREE);
		polynomial p3 = polynomial();
		double amount;
		//loops through to multiply each term and add the exponents
		for(int i = 0; i < p1.degree()+1; ++i){
			for(int j = 0; j < p2.degree()+1; ++j){
				amount = (p1.coefficient(i) * p2.coefficient(j));
				p3.add_to_coef(amount,i+j);
			}
		}
		return p3;
	}

	//prints out the polynomial
	std::ostream& operator<<(ostream& out, const polynomial& p){
		//loops through to print out each degree depending on cases
		for(int i = p.degree(); i >= 0; --i){
			//if the coefficient is 0 then skip the term
			if(p.coefficient(i) == 0){
				continue;
			}
			//the degree is greater than 1
			if(i > 1){
				if(i == p.degree()){
					out << p.coefficient(i) << "x^" << i << ' ';
				}
				else{
					if(p.coefficient(i) < 0){
						out << '-' << ' ';
					}
					else{
						out << '+' << ' ';
					}
					out << abs(p.coefficient(i)) << "x^" << i << ' ';
				}
			}
			//if the degree is equal to 1
			else if(i == 1){
				if(i == p.degree()){
					out << p.coefficient(i) << 'x' << ' ';
				}
				else{
					if (p.coefficient(i) < 0){
						out << '-' << ' ';
					}
					else{
						out << '+' << ' ';
					}
					out << abs(p.coefficient(i)) << "x^" << i << ' ';
				}

			}
			//other cases
			else{
				if(i == p.degree()){
					out << p.coefficient(i) << "x^" << i << ' ';
				}
				else{
					if(p.coefficient(i) < 0){
						out << '-' << ' ';
					}
					else{
						out << '+' << ' ';
					}
					out << abs(p.coefficient(i));
				}
			}
		}
		return out;
	}
}
