#include "TSC.h"

#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <limits>

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

void displayHelpMessage()
{

	std::cout << constants::HELP_MESSAGE;

	exit(0);
}

int main(int argc, char **argv)
{

	if (argc <= 1 || argc > 3)

	{

		displayHelpMessage();
	}

	/*
	   TSC [file.nnl] [c/nc - compile/don't compile]
	   Executable: [0]
	   File: [1]
	   Compile: [2]
	*/

	string file{
		argv[1]};

	// Get rid of .nnl extension
	size_t lastIndex = file.find_last_of(".");

	string fileName = file.substr(0, lastIndex);

	string cppFile{
		fileName + ".cpp"};

	string exeFile{
		fileName};

	string compileVar{
		argv[2]};

	bool compileOption{};

	if (compileVar == "c")

	{

		compileOption = true;
	}

	else if (compileVar == "nc")

	{

		compileOption = false;
	}

	else

	{

		displayHelpMessage();
	}

	string sourceFile{};

	sourceFile += constants::FIRST_MAIN;

	std::ifstream infile(file);

	string line{};

	IncludesVector includes{};

	while (std::getline(infile, line))

	{

		std::istringstream iss(line);

		string a{};

		string b{};

		string c{};

		iss >> a >> b;

		std::getline(iss, c);

		if ((a == ";") || (a == "\n") || (a == ""))

		{

			continue;

		} // Comment/newline, don't do anything

		sourceFile += constants::INDENTATION;

		c = TSC::process_c(c); // Process C so that it cuts off anything past a comment ;

		sourceFile = TSC::declare_function(a) + sourceFile;

		sourceFile += TSC::process_line(a, b, c, &includes);
	}

	sourceFile += constants::LAST_MAIN;

	/*
	   Sort through the includes vector to get rid of duplicates,
	   then append the headers to eachother in a string, then join the sourceFile to the headers
	*/

	std::sort(includes.begin(), includes.end());

	includes.erase(unique(includes.begin(), includes.end()),
				   includes.end());

	// Join headers to eachother in a string
	string includesString{};

	for (size_t i = 0; i < includes.size(); ++i)

	{

		includesString += includes[i];
	}

	string fullSource{
		includesString + sourceFile};

	// Write to file
	std::ofstream out(cppFile);

	out << fullSource;

	out.close();

	if (compileOption)

	{

		string command{"g++ " + cppFile + " -o " + exeFile};

		system(command.c_str());
		system(exeFile.c_str());

		std::cout << '\n'
				  << "\"" << file << "\""
				  << " compiled to "
				  << "\"" << exeFile << "\"" << '\n';
	}

	else

	{

		std::cout << "\"" << file << "\""
				  << " transcompiled to "
				  << "\"" << cppFile << "\"" << '\n';
	}

	if (constants::DELETE_CPP_FILE && compileOption)

	{
		if (std::remove(cppFile.c_str()) != 0)

		{

			std::cout << "Failed to delete \"" + cppFile + "\"\n";

			exit(1);
		}
	}

	return 0;
}
