/**\file		argparser.h
 * \brief		argparser include file.
 */

#ifndef __ARG_PARSER_H__
#define __ARG_PARSER_H__

/**\brief String type */
typedef char*		ArgStr;
/**\brief Character type */
typedef char		ArgChar;

/** Logger boolean type*/
typedef enum{
	ARGBOOL_FALSE,	/*!< */
	ARGBOOL_TRUE	/*!< */
} ArgBool;

/**Possible error codes.*/
typedef enum{
	ARGRET_OK,				/*!< Success */
	ARGRET_MEM_ERROR,		/*!< Memory allocation error */
	ARGRET_NO_NAMES,		/*!< No short or long names provided */
	ARGRET_INVALID_SNAME,	/*!< Invalid short name */
	ARGRET_INVALID_LNAME,	/*!< Invalid long name */
	ARGRET_INVALID_HELP,	/*!< Invalid help string */
	ARGRET_INVALID_FILE,	/*!< Invalid file */
	ARGRET_FILE_LINE_TOO_LONG,	/*!< Line in file exceeded buffer length */
	ARGRET_FILE_READ_ERROR		/*!< File read error */
} ArgReturn;

/**Possible types of arguments.*/
typedef enum {
	ARGVAL_NONE,
	ARGVAL_STRING,
} ArgValType;

/**\brief Add valid arguments for parsing.
 * \param[in] shortname A short 1 or 2 letter flag (do NOT prefix '-').
 * \param[in] longname A long name, more than 2 letters (do NOT prefix '--').
 * \param[in] helpstring Helpstring shown when args_print used.
 * \param[in] valtype Type of value this argument accepts.
 * \return ArgReturn error code.*/
ArgReturn args_addarg(
		const ArgStr shortname,
		const ArgStr longname,
		const ArgStr helpstring,
		const ArgValType valtype);

/**\brief Parses argc and argv for options.
 * \param[in] argc Number of arguments.
 * \param[in] argv Array of strings containing arguments.
 * \return ArgReturn error code.*/
ArgReturn args_parse(int argc, char *argv[]);

/**\brief Parses a config file for options.
 * \details To override command line options, call this function first,
 * otherwise calling args_parse first will override any config file options.
 * \param[in] filename Name of config file.*/
ArgReturn args_parsefile(ArgStr filename);

/**\brief Checks for an option.
 * \param[in] name Short or long name.
 * \return (ArgBool) True or False if argument flag is set.*/
ArgBool args_check(const ArgStr name);

/**\brief Retrieves and unnamed option based on index.
 * \details If you exec "executable option1 option2 -flag1"
 * "option1" and "option2" are unnamed options because they are not prefixed
 * by "-" or "--"
 * \param[in] index 1 is the first option, 2 is the second.
 * \return String containing the option.*/
ArgStr args_getunnamed(const int index);

/**\brief Retrieves named option based on short or long name.
 * \param[in] name Short or long name.
 * \return String containing the option.*/
ArgStr args_getnamed(const ArgStr name);

/**\brief Prints a list of options and help string.*/
void args_print(void);

/**\brief Prints a list of unknown options.
 * \return (ArgBool) True if unknowns exist.*/
ArgBool args_unknown(void);

/**\brief Frees all resources.*/
void args_free(void);

#endif//__ARG_PARSER_H__
