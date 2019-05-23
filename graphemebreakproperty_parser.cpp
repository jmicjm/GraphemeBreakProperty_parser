#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>


struct grapheme_range_info
{
	std::string start, end, type;
};

int main()
{
	std::vector<grapheme_range_info> grapheme_ranges;


	std::ifstream input("GraphemeBreakProperty.txt");
	if (!input.good())
	{
		std::cout << "needs GraphemeBreakProperty.txt" << std::endl;
		return 1;
	}

	for (std::string line; std::getline(input, line);)
	{
		if (line[0] != '#' && line.size() > 0)
		{
			std::string r_s = "0x", r_e = "0x", r_type;

			int pos = 0;
			for (; line[pos] != ' ' && line[pos] != '.'; pos++)
			{
				r_s += line[pos];
			}

			if (line[pos] == '.')
			{
				pos += 2;
				for (; line[pos] != ' '; pos++)
				{
					r_e += line[pos];
				}
			}
			else
			{
				r_e = r_s;
			}

			for (; line[pos] != ';'; pos++) {}
			pos += 2;

			for (; line[pos] != ' '; pos++)
			{
				r_type += line[pos];
			}

			grapheme_ranges.push_back({ r_s, r_e, r_type });
		}

	}
	input.close();

	std::sort(grapheme_ranges.begin(), grapheme_ranges.end(), [](grapheme_range_info l, grapheme_range_info r) {return l.start < r.start; });

	std::ofstream output("grapheme_ranges.h");
	if (!output.good())
	{
		std::cout << "output error" << std::endl;
		return 1;
	}

	for (int i = 0; i < grapheme_ranges.size(); i++)
	{
		output << "{" << grapheme_ranges[i].start << ", " << grapheme_ranges[i].end << ", " << grapheme_ranges[i].type << "}";

		if (i != grapheme_ranges.size() - 1)
		{
			output << ",\n";
		}
	}
	output.close();


	return 0;
}