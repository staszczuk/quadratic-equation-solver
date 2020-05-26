#include <iostream>
#include <string>
#include <array>
#include <iomanip>

bool compare(std::array<std::double_t, 3>& coefficients, std::array<std::double_t, 2>& roots, std::double_t xValue)
{
	std::double_t standard = coefficients.at(0) * xValue * xValue + coefficients.at(1) * xValue + coefficients.at(2);
	std::double_t intercept = coefficients.at(0) * (xValue - roots.at(0)) * (xValue - roots.at(1));
	if (standard == intercept) return true;
}

int main()
{
	std::string input1;
	std::array<std::double_t, 3> coefficients;
	std::array<std::double_t, 2> roots{ 0.0, 0.0 };
	std::double_t delta;
	bool ok = true;
	std::cout.precision(16);
	while (true)
	{
		std::cout << "::Enter coefficients a, b, c separated by space: ";
		std::getline(std::cin, input1);
		for (std::int8_t i = 0; i < 3; i++)
		{
			std::size_t pos = input1.find(' ');

			if (input1.empty())
			{
				std::cout << "\nError: incorrect coefficients";
				ok = false;
				break;
			}
			else if (pos == std::string::npos)
			{
				coefficients.at(i) = stod(input1);
				input1.clear();
				ok = true;
			}
			else
			{
				coefficients.at(i) = std::stod(input1.substr(0, pos));
				input1.erase(0, pos + 1);
			}
		}
		if (ok)
		{
			std::cout << "\na = " << coefficients.at(0)
				<< "\tb = " << coefficients.at(1)
				<< "\tc = " << coefficients.at(2);
			delta = coefficients.at(1) * coefficients.at(1) - 4 * coefficients.at(0) * coefficients.at(2);
			std::cout << "\n\nDelta =\t" << delta;
			if (delta == 0)
			{
				roots.at(0) = (coefficients.at(1) * -1) / (2 * coefficients.at(0));
				std::cout << "\n\nRoots are real and same"
					<< "\nx1 = x2 = " << roots.at(0);
			}
			else if (delta > 0)
			{
				roots.at(0) = (coefficients.at(1) * -1 + std::sqrt(delta)) / (2 * coefficients.at(0));
				roots.at(1) = (coefficients.at(1) * -1 - std::sqrt(delta)) / (2 * coefficients.at(0));
				std::cout << "\n\nRoots are real and different"
					<< "\nx1 = " << roots.at(0)
					<< "\tx2 = " << roots.at(1);
				for (std::int8_t i = 0; i < 127; i++) {
					if (!compare(coefficients, roots, i))
					{
						std::cout << "\n\nWarning: roots may be inaccurate";
						break;
					}
				}
			}
			else if (delta < 0)
			{
				std::cout << "\n\nNo real roots";
			}
		}
		std::cout << "\n\n";
	}
}