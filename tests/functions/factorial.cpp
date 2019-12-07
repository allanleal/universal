﻿// factorial.cpp: evaluation of factorials in the posit number systems
//
// Copyright (C) 2017-2020 Stillwater Supercomputing, Inc.
//
// This file is part of the UNIVERSAL project, which is released under an MIT Open Source license.
#include <universal/posit/posit>
#include <universal/integer/integer>
#include <universal/conversion/integer_to_posit.hpp>

// generate factorials in an Integer and a Posit number system to compare
template<typename Integer, typename Posit>
void GenerateFactorialTableComparison(unsigned upperbound, int columnWidth = 30) {
	using namespace std;
	Integer factorialValue = 1;
	Posit positRef = 1;
	cout << "  i    " << setw(columnWidth) << "integer(N!)" << "  " << setw(columnWidth) << "posit(N!)" << setw(columnWidth) << "abs(error)\n";
	for (unsigned i = 2; i < upperbound; ++i) {
		factorialValue *= i;
		positRef *= i;
		Integer integerRef;
		sw::unum::convert_p2i(positRef, integerRef);
		Integer error = (factorialValue > integerRef ? factorialValue - integerRef : integerRef - factorialValue);
		cout << setw(5) << i << "  " << setw(columnWidth) << factorialValue << "  " << setw(columnWidth) << positRef << setw(columnWidth) << error << endl;
	}
}


int main(int argc, char** argv)
try {
	using namespace std;
	using namespace sw::unum;

	// print detailed bit-level computational intermediate results
	// bool verbose = false;

	// preserve the existing ostream precision
	auto precision = cout.precision();
	cout << setprecision(12);

	unsigned upperbound = 22;   
	{
		// 20! can still be represented by a 64-bit integer
		// 21! can not be represented by a 64-bit integer
		// 13! and up generate integers that a 32-bit posit can't represent
		using Integer = unsigned long long;
		constexpr size_t nbits = 32;
		constexpr size_t es = 2;
		using Posit = posit<nbits, es>;
		int columnWidth = 40;
		GenerateFactorialTableComparison<Integer, Posit>(upperbound, columnWidth);
		/*
		  i                                 integer(N!)                                 posit(N!)                             abs(error)
			2                                         2                                         2                                       0
			3                                         6                                         6                                       0
			4                                        24                                        24                                       0
			5                                       120                                       120                                       0
			6                                       720                                       720                                       0
			7                                      5040                                      5040                                       0
			8                                     40320                                     40320                                       0
			9                                    362880                                    362880                                       0
		   10                                   3628800                                   3628800                                       0
		   11                                  39916800                                  39916800                                       0
		   12                                 479001600                                 479001600                                       0
		   13                                6227020800                                6227017728                                    3072    <- the 32-bit posit can't represent these integers
		   14                               87178291200                               87178346496                                   55296
		   15                             1307674368000                          1.3076749353e+12                                  567296
		   16                            20922789888000                         2.09229331825e+13                               143294464
		   17                           355687428096000                         3.55692011586e+14                              4583489536
		   18                          6402373705728000                         6.40245620854e+15                             82502811648
		   19                        121645100408832000                         1.21649966497e+17                           4866088304640
		   20                       2432902008176640000                         2.43306969869e+18                         167690510270464
		   21                      14197454024290336768                         5.10888341729e+19                     4974081987435560960    <- 21! cannot be represented by a 64-bit unsigned long long integer
		*/
	}

	{
		// 20! can still be represented by a 64-bit integer
        // 21! can not be represented by a 64-bit integer
		using Integer = unsigned long long;
		constexpr size_t nbits = 64;
		constexpr size_t es = 2;
		using Posit = posit<nbits, es>;
		int columnWidth = 40;
		GenerateFactorialTableComparison<Integer, Posit>(upperbound, columnWidth);
		/*
		  i                                 integer(N!)                                 posit(N!)                             abs(error)
			2                                         2                                         2                                       0
			3                                         6                                         6                                       0
			4                                        24                                        24                                       0
			5                                       120                                       120                                       0
			6                                       720                                       720                                       0
			7                                      5040                                      5040                                       0
			8                                     40320                                     40320                                       0
			9                                    362880                                    362880                                       0
		   10                                   3628800                                   3628800                                       0
		   11                                  39916800                                  39916800                                       0
		   12                                 479001600                                 479001600                                       0
		   13                                6227020800                                6227020800                                       0
		   14                               87178291200                               87178291200                                       0
		   15                             1307674368000                           1.307674368e+12                                       0
		   16                            20922789888000                          2.0922789888e+13                                       0
		   17                           355687428096000                         3.55687428096e+14                                       0
		   18                          6402373705728000                         6.40237370573e+15                                       0
		   19                        121645100408832000                         1.21645100409e+17                                       0
		   20                       2432902008176640000                         2.43290200818e+18                                       0
		   21                      14197454024290336768                         5.10909421717e+19                     4974081987435560960   <- 21! cannot be represented by a 64-bit unsigned long long integer
		*/
	}

	upperbound = 30;
	{
		using Integer = sw::unum::integer<128>;
		constexpr size_t nbits = 64;
		constexpr size_t es = 3;
		using Posit = posit<nbits, es>;
		int columnWidth = 40;
		GenerateFactorialTableComparison<Integer, Posit>(upperbound, columnWidth);
		/*
			 i                               integer(N!)                                 posit(N!)                             abs(error)
			 2                                         2                                         2                                       0
			 3                                         6                                         6                                       0
			 4                                        24                                        24                                       0
			 5                                       120                                       120                                       0
			 6                                       720                                       720                                       0
			 7                                      5040                                      5040                                       0
			 8                                     40320                                     40320                                       0
			 9                                    362880                                    362880                                       0
			10                                   3628800                                   3628800                                       0
			11                                  39916800                                  39916800                                       0
			12                                 479001600                                 479001600                                       0
			13                                6227020800                                6227020800                                       0
			14                               87178291200                               87178291200                                       0
			15                             1307674368000                           1.307674368e+12                                       0
			16                            20922789888000                          2.0922789888e+13                                       0
			17                           355687428096000                         3.55687428096e+14                                       0
			18                          6402373705728000                         6.40237370573e+15                                       0
			19                        121645100408832000                         1.21645100409e+17                                       0
			20                       2432902008176640000                         2.43290200818e+18                                       0
			21                      51090942171709440000                         5.10909421717e+19                                       0
			22                    1124000727777607680000                         1.12400072778e+21                                       0
			23                   25852016738884976640000                         2.58520167389e+22                                 9961472
			24                  620448401733239439360000                         6.20448401733e+23                               775946240
			25                15511210043330985984000000                         1.55112100433e+25                             32283557888
			26               403291461126605635584000000                         4.03291461127e+26                           1457847795712
			27             10888869450418352160768000000                         1.08888694504e+28                          21769704439808
			28            304888344611713860501504000000                         3.04888344612e+29                         891026701025280
			29           8841761993739701954543616000000                         8.84176199374e+30                        5685423061860352
		*/
	}

	{
		using Integer = sw::unum::integer<128>;
		constexpr size_t nbits = 128;
		constexpr size_t es = 4;
		using Posit = posit<nbits, es>;
		int columnWidth = 40;
		GenerateFactorialTableComparison<Integer, Posit>(upperbound, columnWidth);
		/*
		  i                                 integer(N!)                                 posit(N!)                             abs(error)
			2                                         2                                         2                                       0
			3                                         6                                         6                                       0
			4                                        24                                        24                                       0
			5                                       120                                       120                                       0
			6                                       720                                       720                                       0
			7                                      5040                                      5040                                       0
			8                                     40320                                     40320                                       0
			9                                    362880                                    362880                                       0
		   10                                   3628800                                   3628800                                       0
		   11                                  39916800                                  39916800                                       0
		   12                                 479001600                                 479001600                                       0
		   13                                6227020800                                6227020800                                       0
		   14                               87178291200                               87178291200                                       0
		   15                             1307674368000                           1.307674368e+12                                       0
		   16                            20922789888000                          2.0922789888e+13                                       0
		   17                           355687428096000                         3.55687428096e+14                                       0
		   18                          6402373705728000                         6.40237370573e+15                                       0
		   19                        121645100408832000                         1.21645100409e+17                                       0
		   20                       2432902008176640000                         2.43290200818e+18                                       0
		   21                      51090942171709440000                         5.10909421717e+19                                       0
		   22                    1124000727777607680000                         1.12400072778e+21                                       0
		   23                   25852016738884976640000                         2.58520167389e+22                                       0
		   24                  620448401733239439360000                         6.20448401733e+23                                       0
		   25                15511210043330985984000000                         1.55112100433e+25                                       0
		   26               403291461126605635584000000                         4.03291461127e+26                                       0
		   27             10888869450418352160768000000                         1.08888694504e+28                                       0
		   28            304888344611713860501504000000                         3.04888344612e+29                                       0
		   29           8841761993739701954543616000000                         8.84176199374e+30                                       0
		*/
	}

	// restore the previous ostream precision
	cout << setprecision(precision);

	return EXIT_SUCCESS;
}
catch (char const* msg) {
	std::cerr << msg << std::endl;
	return EXIT_FAILURE;
}
catch (const posit_arithmetic_exception& err) {
	std::cerr << "Uncaught posit arithmetic exception: " << err.what() << std::endl;
	return EXIT_FAILURE;
}
catch (const quire_exception& err) {
	std::cerr << "Uncaught quire exception: " << err.what() << std::endl;
	return EXIT_FAILURE;
}
catch (const posit_internal_exception& err) {
	std::cerr << "Uncaught posit internal exception: " << err.what() << std::endl;
	return EXIT_FAILURE;
}
catch (std::runtime_error& err) {
	std::cerr << err.what() << std::endl;
	return EXIT_FAILURE;
}
catch (...) {
	std::cerr << "Caught unknown exception" << std::endl;
	return EXIT_FAILURE;
}