/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 00:35:00 by fvizcaya          #+#    #+#             */
/*   Updated: 2026/05/12 00:38:15 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vect2.hpp"

#include <iostream>
#include <limits>
#include <sstream>
#include <string>

static int g_passed = 0;
static int g_failed = 0;

static void report(const std::string& name, bool ok, const std::string& details)
{
	if (ok)
	{
		++g_passed;
		std::cout << "[PASS] " << name << "\n";
		return;
	}
	++g_failed;
	std::cout << "[FAIL] " << name;
	if (!details.empty())
		std::cout << " - " << details;
	std::cout << "\n";
}

static void check_int(const std::string& name, int got, int expected)
{
	if (got == expected)
		return report(name, true, "");
	std::ostringstream oss;
	oss << "got " << got << " expected " << expected;
	report(name, false, oss.str());
}

static void check_bool(const std::string& name, bool got, bool expected)
{
	if (got == expected)
		return report(name, true, "");
	report(name, false, std::string("got ") + (got ? "true" : "false") +
			" expected " + (expected ? "true" : "false"));
}

static void check_vec(const std::string& name, const vect2& v, int ex, int ey)
{
	int gx = v[0];
	int gy = v[1];
	if (gx == ex && gy == ey)
		return report(name, true, "");
	std::ostringstream oss;
	oss << "got {" << gx << ", " << gy << "} expected {" << ex << ", " << ey << "}";
	report(name, false, oss.str());
}

int main()
{
	std::cout << "vect2 tests\n";

	vect2 v0;
	check_vec("default ctor", v0, 0, 0);

	vect2 v1(7, -3);
	check_vec("param ctor", v1, 7, -3);

	vect2 v2(v1);
	check_vec("copy ctor", v2, 7, -3);

	vect2 v3;
	v3 = v1;
	check_vec("assignment", v3, 7, -3);

	v3 = v3;
	check_vec("self assignment", v3, 7, -3);

	vect2 v4(1, 2);
	v4[0] = 9;
	v4[1] = -4;
	check_vec("operator[] set", v4, 9, -4);

	const vect2 v4c(v4);
	check_int("operator[] const x", v4c[0], 9);
	check_int("operator[] const y", v4c[1], -4);
	check_int("operator[] nonzero index uses y", v4c[2], -4);
	check_int("operator[] negative index uses y", v4c[-1], -4);

	vect2 a(1, 2);
	vect2 b(3, 4);
	vect2 sum = a + b;
	check_vec("operator+ basic", sum, 4, 6);

	vect2 c(1, 2);
	c += b;
	check_vec("operator+= basic", c, 4, 6);

	vect2 f(2, 2);
	vect2 e(1, 1);
	e += (f += vect2(1, 1));
	check_vec("operator+= chaining", f, 3, 3);
	check_vec("operator+= chaining result", e, 4, 4);

	vect2 neg = -a;
	check_vec("unary -", neg, -1, -2);

	vect2 diff = a - b;
	check_vec("operator- basic", diff, -2, -2);

	vect2 g(5, 6);
	g -= a;
	check_vec("operator-= basic", g, 4, 4);

	vect2 h(2, -3);
	vect2 prod = h * 3;
	check_vec("operator* scalar", prod, 6, -9);

	vect2 i(2, 3);
	i *= 0;
	check_vec("operator*= scalar", i, 0, 0);

	vect2 j(2, 3);
	vect2 prod_neg = j * -2;
	check_vec("operator* negative scalar", prod_neg, -4, -6);

	vect2 p(5, 6);
	vect2 p_old = p++;
	check_vec("postfix++ returns old", p_old, 5, 6);
	check_vec("postfix++ increments self", p, 6, 7);

	vect2 q(1, 1);
	vect2& q_ref = ++q;
	check_vec("prefix++ increments self", q, 2, 2);
	check_vec("prefix++ returns self", q_ref, 2, 2);
	check_bool("prefix++ returns same object", &q_ref == &q, true);

	vect2 r(5, 6);
	vect2 r_old = r--;
	check_vec("postfix-- returns old", r_old, 5, 6);
	check_vec("postfix-- decrements self", r, 4, 5);

	vect2 s(1, 1);
	vect2& s_ref = --s;
	check_vec("prefix-- decrements self", s, 0, 0);
	check_vec("prefix-- returns self", s_ref, 0, 0);
	check_bool("prefix-- returns same object", &s_ref == &s, true);

	vect2 u(1, 2);
	vect2 v(1, 2);
	vect2 w(2, 3);
	check_bool("operator== true", u == v, true);
	check_bool("operator== false", u == w, false);
	check_bool("operator!= true", u != w, true);
	check_bool("operator!= false", u != v, false);

	std::ostringstream oss;
	std::ostream* ret = &(oss << u);
	check_bool("operator<< returns stream", ret == &oss, true);
	std::string out = oss.str();
	check_bool("operator<< writes to stream", !out.empty(), true);
	check_bool("operator<< format", out == "{1, 2}\n", true);

	int max = std::numeric_limits<int>::max();
	int min = std::numeric_limits<int>::min();
	vect2 big(max, min);
	check_int("store int max", big[0], max);
	check_int("store int min", big[1], min);

	std::cout << "\nPassed: " << g_passed << " Failed: " << g_failed << "\n";
	return g_failed == 0 ? 0 : 1;
}
