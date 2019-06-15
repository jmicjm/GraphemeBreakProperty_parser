# GraphemeBreakProperty_parser
Converts GraphemeBreakProperty.txt into file that could be easily used in c++

for example:
```c++
enum GRAPHEME_TYPE
{
	CONTROL,
	LF,
	CR,
	EXTEND,
	PREPEND,
	SPACINGMARK,
	REGIONAL_INDICATOR,
	L,
	V,
	T,
	LV,
	LVT,
	ZWJ
};
struct grapheme_range_info
{
int r_start, r_end, r_type;
};
std::vector<grapheme_range_info> ranges =
{
	#include "example_output.h"
};
```

# Command line options

```-i input_name``` defaults to ```GraphemeBreakProperty.txt```  
```-o output_name``` defaults to ```grapheme_ranges.h```  
```-u``` upper case grapheme type (```{0x0000, 0x0009, Control},``` will become: ```{0x0000, 0x0009, CONTROL},```)  
```-b begin_text``` add text at the beginning of grapheme type (```{0x0000, 0x0009, Control},``` will become: ```{0x0000, 0x0009, begin_textControl},```)   
```-e end_text``` add text at the end of grapheme type (```{0x0000, 0x0009, Control},``` will become: ```{0x0000, 0x0009, Controlend_text},```)  
