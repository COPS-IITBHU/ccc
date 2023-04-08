#include "TSC.h"

#include <cmath>
#include <string>
#include <vector>

using std::string;

using std::vector;

using IncludesVector = vector<string>;

namespace constants
{

	// For Debug
	static constexpr bool
		DELETE_CPP_FILE{
			true};

	// Includes
	static vector<
		string>
		IO_INCLUDES{
			"#include <iostream>\n"};

	static vector<
		string>
		STRING_INCLUDES{
			"#include <string>"};

	static vector<
		string>
		CONV_INCLUDES{
			"#include <string>\n",
			"#include <cstdlib>\n"};

	static vector<
		string>
		MATH_INCLUDES{
			"#include <cmath>\n"};

	static vector<
		string>
		TYPE_INCLUDES{
			"#include <type_traits>\n",
			"#include <typeinfo>\n",
			"#include <memory>\n",
			"#include <string>\n",
			"#include <cstdlib>\n",
			"#include <typeinfo>\n"};

	static vector<
		string>
		NONE_INCLUDE{
			""};

	// Transpiler
	static const string
		FIRST_MAIN{
			"int main()\n{\n"};

	static const string
		INDENTATION{
			"	"};

	static const string
		NEWLINE{
			"\n"};

	static const string
		LAST_MAIN{
			INDENTATION +
			"return 0;\n}\n"};

	static const string
		DEFAULT{
			"DEF"}; // Placeholder variable

	// C Replacement -- WIP
	static const string
		SPACE{
			"\" \""};
	static const string
		NEWLINE_CHARACTER{
			"\"\\n\""};

	static const string
		TRUE{
			"true"};

	static const string
		FALSE{
			"false"};

	static const string
		NONE{
			""};

	// Messages
	static const string
		HELP_MESSAGE{

			"Incorrect arguments.\n"
			"TSC Usage:\n"
			"[TSC Executable] [anyfile.nnl] [c/nc - compile/nocompile]\n"
			"Warning: You need g++ to compile.\n"};

	// Functions
	static const string
		TYPE_NAME{

			"#ifndef _MSC_VER\n"
			"#include <cxxabi.h>\n"
			"#endif\n"
			"\n"
			"template <class T> std::string type_name()\n"
			"{\n"
			"	typedef typename std::remove_reference<T>::type TR;\n"
			"	std::unique_ptr<char, void(*)(void *)> own\n"
			"	(\n"
			"#ifndef _MSC_VER\n"
			"		abi::__cxa_demangle(typeid(TR).name(), nullptr,\n"
			"			nullptr, nullptr),\n"
			"#else\n"
			"		nullptr,\n"
			"#endif\n"
			"		std::free\n"
			"	);\n"
			"	std::string r = own != nullptr ? own.get() : typeid(TR).name();\n"
			"	if (std::is_const<TR>::value) { r += \" const\"; }\n"
			"	if (std::is_volatile<TR>::value) { r += \" volatile\"; }\n"
			"	if (std::is_lvalue_reference<T>::value) { r += \"&\"; }\n"
			"	else if (std::is_rvalue_reference<T>::value) { r += \"&&\"; }\n"
			"	return r;\n"
			"}\n"};

}

namespace vars
{

	static string
		def{
			constants::DEFAULT};

	static bool
		def_reference{
			false};

	static bool
		ipow_dec{
			false};

	static bool
		fpow_dec{
			false};

	static bool
		dpow_dec{
			false};

	static bool
		type_dec{
			false};

}

string prefixCheck(string prefix = "")
{

	if (vars::def_reference)

	{

		return "";
	}

	else

	{

		return prefix;
	}
}

// Variables
string TSC::dec(string var_name, string var_value)
{
	return "auto " + var_name + "{ " + var_value + " };\n";
}

string TSC::dec(string var_name, string var_value, string type)
{
	return type + " " + var_name + "{ " + var_value + " };\n";
}

string TSC::mov(string l_var, string r_var)
{
	return "auto " + r_var + "{ " + l_var + " };\n";
}

string TSC::anydef(string var_name, bool reference)
{

	vars::def = var_name;

	vars::def_reference = reference;

	return string("");
}

string TSC::conv(string var_name, string type)
{
	return prefixCheck(type + " ") + vars::def + "{ static_cast<" + type +
		   ">(" + var_name + ") };\n";
}

string TSC::iconv(string old_var, string new_var)
{
	return "int " + new_var + "{ std::stoi(" + old_var + ") };\n";
}

string TSC::fconv(string old_var, string new_var)
{
	return "float " + new_var + "{ strtof(" + old_var + ") };\n";
}

string TSC::dconv(string old_var, string new_var)
{
	return "double " + new_var + "{ atof(" + old_var + ".c_str()) };\n";
}

string TSC::type(string var_name)
{

	// TODO
	return "";
}

string TSC::round(string l_var, string r_var)
{
	return "auto " + r_var + "{ round(" + l_var + ") };\n";
}

// Math
string TSC::math(string l_var, string r_var, string mode, bool def)
{

	if (mode == "pow")

	{

		return prefixCheck("int ") + vars::def + " = pow(" + l_var + ", " +
			   r_var + ");\n";
	}

	else if (mode == "rpow")

	{

		return l_var + " = pow(" + l_var + ", " + r_var + ");\n";
	}

	if (def)

	{

		return prefixCheck("auto ") + vars::def + " {" + l_var + " " + mode +
			   " " + r_var + "};\n";
	}

	else

	{

		return l_var + " " + mode + "= " + r_var + ";\n";
	}
}

string TSC::cat(string l_var, string r_var)
{
	return l_var + " += " + "std::string(" + r_var + ");\n";
}

string TSC::mathpow(string base, string exp, string mode)
{
	return prefixCheck("int ") + vars::def + " = " + mode + "pow(" + base +
		   ", " + exp + ");\n";
} // mode == i, d, etc

// Input/Output
string TSC::io(string mode, string var)
{

	if (mode == "out")

	{

		return "std::cout << " + var + ";\n";
	}

	else if (mode == "nlout")

	{

		return "std::cout << " + var + " << '\\n';\n";
	}

	else if (mode == "in")

	{

		return "std::string " + var + "{};\n" + constants::INDENTATION +
			   "std::cin >> " + var + ";\n";
	}

	else if (mode == "input")

	{

		if (vars::def_reference)

		{

			return "std::cout << " + var + ";\n"
										   "" +
				   constants::INDENTATION + "std::cin >> " + vars::def + ";\n";
		}

		else

		{

			return "std::cout << " + var + ";\n"
										   "std::string " +
				   vars::def + " {};\n"
							   "" +
				   constants::INDENTATION + "std::cin >> " + vars::def + ";\n";
		}
	}

	else if (mode == "defin")

	{

		if (vars::def_reference)

		{

			return "std::cin >> " + vars::def + ";\n";
		}

		else

		{

			return "std::string " + vars::def + "{};\n" +
				   constants::INDENTATION + "std::cin >> " + vars::def + ";\n";
		}
	}

	else

	{

		return string("");
	}
}

string TSC::assert(string l_var, string r_var, string mode, bool format)
{

	if (format)

	{

		return "if (" + l_var + " " + mode + " " + r_var + ")"
														   " { std::cout << \"" +
			   l_var + " " + mode + " " + r_var +
			   " = true\\n\"; }\n"
			   "else { std::cout << \"" +
			   l_var + " " + mode +
			   " " + r_var + " = false\\n\"; }\n";
	}

	else

	{

		return "if (" + l_var + " " + mode + " " + r_var +
			   ") { std::cout << \"true\\n\"; }\n"
			   "else { std::cout << \"false\\n\";\n";
	}

} // mode == "==", <, >, etc

string TSC::cpp(string b, string c)
{
	return "" + b + c + '\n';
} // Use with include

vector<string> getIncludes(string to_include)
{

	if (to_include == "io")

	{

		return constants::IO_INCLUDES;
	}

	else if (to_include == "conv")

	{

		return constants::CONV_INCLUDES;
	}

	else if (to_include == "math")

	{

		return constants::MATH_INCLUDES;
	}

	else if (to_include == "string")

	{

		return constants::STRING_INCLUDES;
	}

	else if (to_include == "type")

	{

		return constants::TYPE_INCLUDES;
	}

	else

	{

		return constants::NONE_INCLUDE;
	}
}

string TSC::process_c(string c)
{

	// Removes " ;" and anything past it
	string cut_c{
		c.substr(0, c.find(" ;", 0))};

	if (cut_c == "NEWLINE")

	{

		return constants::NEWLINE_CHARACTER;
	}

	else if (cut_c == "SPACE")

	{

		return constants::SPACE;
	}

	else if (cut_c == "TRUE")

	{

		return constants::TRUE;
	}

	else if (cut_c == "FALSE")

	{

		return constants::FALSE;
	}

	else if (cut_c == "NONE")

	{

		return constants::NONE;
	}

	else

	{

		return cut_c;
	};
}

string TSC::process_line(string a, string b, string c,
						 IncludesVector *include_vector)
{

	if (a == "dec")

	{

		return TSC::dec(b, c);
	}

	else if (a == "sdec") // string
	{

		include_vector->push_back("#include <string>\n");

		return TSC::dec(b, c, "std::string");
	}

	else if (a == "idec")

	{

		return TSC::dec(b, c, "int");

	} // int
	else if (a == "cdec")

	{

		return TSC::dec(b, c, "char");

	} // char
	else if (a == "fdec")

	{

		return TSC::dec(b, c, "float");

	} // float
	else if (a == "ddec")

	{

		return TSC::dec(b, c, "double");

	} // double
	else if (a == "bdec")

	{

		return TSC::dec(b, c, "bool");

	} // bool
	else if (a == "cat")

	{

		include_vector->push_back("#include <string>\n");

		return TSC::cat(b, c);
	}

	else if (a == "mov")

	{

		return TSC::mov(b, c);
	}

	else if (a == "def")

	{

		return TSC::anydef(b, false);
	}

	else if (a == "rdef")

	{

		return TSC::anydef(b, true);
	}

	else if (a == "conv")

	{

		return TSC::conv(b, c);
	}

	else if (a == "iconv")

	{

		include_vector->push_back("#include <string>\n");

		return TSC::iconv(b, c);
	}

	else if (a == "fconv")

	{

		include_vector->push_back("#include <cstdlib>\n");

		return TSC::fconv(b, c);
	}

	else if (a == "dconv")

	{

		include_vector->push_back("#include <cstdlib>\n");

		return TSC::dconv(b, c);
	}

	else if (a == "add")

	{

		return TSC::math(b, c, "+", false);
	}

	else if (a == "sub")

	{

		return TSC::math(b, c, "-", false);
	}

	else if (a == "mul")

	{

		return TSC::math(b, c, "*", false);
	}

	else if (a == "div")

	{

		return TSC::math(b, c, "/", false);
	}

	else if (a == "mod")

	{

		return TSC::math(b, c, "%", false);
	}

	else if (a == "pow")

	{

		include_vector->push_back("#include <cmath>\n");

		return TSC::math(b, c, "pow", false);
	}

	else if (a == "rpow")

	{

		include_vector->push_back("#include <cmath>\n");

		return TSC::math(b, c, "rpow", false);
	}

	else if (a == "defadd")

	{

		return TSC::math(b, c, "+", true);
	}

	else if (a == "defsub")

	{

		return TSC::math(b, c, "-", true);
	}

	else if (a == "defmul")

	{

		return TSC::math(b, c, "*", true);
	}

	else if (a == "defdiv")

	{

		return TSC::math(b, c, "/", true);
	}

	else if (a == "defmod")

	{

		return TSC::math(b, c, "%", true);
	}

	else if (a == "defpow")

	{

		include_vector->push_back("#include <cmath>\n");

		return TSC::math(b, c, "pow", true);
	}

	else if (a == "ipow")

	{

		return TSC::mathpow(b, c, "i");
	}

	else if (a == "fpow")

	{

		return TSC::mathpow(b, c, "f");
	}

	else if (a == "dpow")

	{

		return TSC::mathpow(b, c, "d");
	}

	else if (a == "round")

	{

		include_vector->push_back("#include <cmath>\n");

		return TSC::round(b, c);
	}

	else if (a == "io")

	{

		include_vector->push_back("#include <iostream>\n");

		return TSC::io(b, c);
	}

	else if (a == "asserteq")

	{

		return TSC::assert(b, c, "==", false);
	}

	else if (a == "fasserteq")

	{

		return TSC::assert(b, c, "==", true);
	}

	else if (a == "assertlt")

	{

		return TSC::assert(b, c, "<", false);
	}

	else if (a == "fassertlt")

	{

		return TSC::assert(b, c, "<", true);
	}

	else if (a == "assertgt")

	{

		return TSC::assert(b, c, ">", false);
	}

	else if (a == "fassertgt")

	{

		return TSC::assert(b, c, ">", true);
	}

	else if (a == "assertgteq")

	{

		return TSC::assert(b, c, ">=", false);
	}

	else if (a == "fassertgteq")

	{

		return TSC::assert(b, c, ">=", true);
	}

	else if (a == "assertlteq")

	{

		return TSC::assert(b, c, "<=", false);
	}

	else if (a == "fassertlteq")

	{

		return TSC::assert(b, c, "<=", true);
	}

	else if (a == "cpp")

	{

		return TSC::cpp(b, c);
	}

	else if (a == "include")

	{

		vector<string> includes{
			getIncludes(b)};

		for (string include : includes)

		{

			include_vector->push_back(include);
		}

		return string();
	}

	else if (a == "type" || a == "ptype" || a == "fptype")

	{

		vector<string> includes{
			getIncludes("type")};

		for (string include : includes)

		{

			include_vector->push_back(include);
		}

		if (a == "type")

		{

			return prefixCheck("auto ") + vars::def +
				   "{ type_name<decltype(" + b + ")>() };\n";
		}

		else if (a == "ptype")

		{

			include_vector->push_back("#include <iostream>\n");

			return "std::cout << " + string() + " type_name<decltype(" + b +
				   ")>() << '\\n';\n";
		}

		else if (a == "fptype")

		{

			include_vector->push_back("#include <iostream>\n");

			return "std::cout << \"variable '" + b +
				   "' has type '\" << type_name<decltype(" + b +
				   ")>() << \"'\\n\";\n";
		}

		else

		{

			return "";
		}
	}

	else

	{

		return "";
	}
}

string TSC::declare_function(string function_name)
{

	if (function_name == "ipow" && !(vars::ipow_dec))

	{

		vars::ipow_dec = true;

		return "int ipow(int base, int exp) { return exp == 0 ? 1 : base * ipow(base, exp - 1); }\n";
	}

	else if (function_name == "fpow" && !(vars::fpow_dec))

	{

		vars::fpow_dec = true;

		return "float fpow(float base, float exp) { return exp == 0 ? 1 : base * fpow(base, exp - 1); }\n";
	}

	else if (function_name == "dpow" && !(vars::dpow_dec))

	{

		vars::dpow_dec = true;

		return "double dpow(double base, double exp) { return exp == 0 ? 1 : base * dpow(base, exp - 1); }\n";
	}

	else if ((function_name == "type" || function_name == "ptype" || function_name == "fptype") && !(vars::type_dec))

	{

		vars::type_dec = true;

		return constants::TYPE_NAME;
	}

	else

	{

		return "";
	}
}
