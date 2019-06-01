#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cctype>


struct grapheme_range_info
{
	std::string start, end, type;
};

int main(int argc, char** argv)
{
	std::string input_name, output_name;
	std::string begin_text, end_text;
	bool use_upper_case;

//parsing command line arguments
	auto invalidArgMsg = []()
	{
		std::cout << "invalid argument set";
		std::exit(1);
	};

	auto findArg = [argv, argc](const char* arg)
	{
		for (int i = 0; i < argc; i++)
		{
			if (strcmp(argv[i], arg) == 0) { return i; }
		}
		return -1;
	};

	auto argExist = [findArg](const char* arg)
	{
		if (findArg(arg) >= 0) { return true; }
		else { return false; }
	};

	auto getArgStr = [findArg, invalidArgMsg, argc, argv](const char* arg, std::string &str)
	{
		if (findArg(arg) >= 0)
		{
			int pos = findArg(arg) + 1;
			if (pos < argc)
			{
				if (argv[pos][0] != '-')
				{
					str = argv[pos];
				}
				else { invalidArgMsg(); }
			}
			else { invalidArgMsg(); }
		}
	};

	if (argExist("-i")) { getArgStr("-i", input_name); }
	else { input_name = "GraphemeBreakProperty.txt"; }
	
	if (argExist("-o")) { getArgStr("-o", output_name); }
	else { output_name = "grapheme_ranges.h"; }

	if (argExist("-u")) { use_upper_case = true; }
	else { use_upper_case = false; }

	if (argExist("-b")) { getArgStr("-b", begin_text); }
		
	if (argExist("-e")) { getArgStr("-e", end_text); }


//parsing input file
	std::vector<grapheme_range_info> grapheme_ranges;

	std::ifstream input(input_name);
	if (!input.good())
	{
		std::cout << "input file error" << std::endl;
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

			if (use_upper_case) 
			{
				for (int i = 0; i < r_type.size(); i++)
				{
					r_type[i] = std::toupper(r_type[i]);
				}
			}

			std::string final_r_type = begin_text + r_type + end_text;

			grapheme_ranges.push_back({ r_s, r_e, final_r_type });
		}
	}
	input.close();

	std::sort(grapheme_ranges.begin(), grapheme_ranges.end(),
			[](grapheme_range_info l, grapheme_range_info r) 
			{
				return std::stoi(l.start, nullptr, 16) < std::stoi(r.start, nullptr, 16); 
			});

//writing to output file
	std::ofstream output(output_name);
	if (!output.good())
	{
		std::cout << "output file error" << std::endl;
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