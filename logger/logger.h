/**\file		logger.h
 * \brief		Simple logging interface
 */

#ifndef __LOGGER_H__
#define __LOGGER_H__

/** Logger string type*/
typedef char*		LogStr;
/** Logger char type*/
typedef char		LogChar;

/** Custom callback to log message */
typedef void(*log_callback)(LogStr);

/** Logger boolean type*/
typedef enum{
	LOGBOOL_FALSE,	/*!< */
	LOGBOOL_TRUE	/*!< */
} LogBool;

/** Logger error codes.*/
typedef enum{
	LOGRET_OK,					/*!< Success */
	LOGRET_LACK_MEM,			/*!< Memory allocation failed */
	LOGRET_INVALID_LOG_FILE,	/*!< Invalid log file specified */
	LOGRET_SNPRINTF_ERR,		/*!< Problem formatting string */
	LOGRET_FILE_LOG_ERR,		/*!< Problem logging to file */
	LOGRET_CONSOLE_LOG_ERR		/*!< Problem logging to console */
} LogReturn;

/**\brief Initializes the logging instance
 * \param[in] filename (optional) file name to log to, pass in NULL to disable
 * \param[in] append set to LOGBOOL_TRUE to append to file rather to write new one
 * \param[in] cb sets custom callback for logging strings
 */
LogReturn log_init(/*@null@*/ LogStr filename,LogBool append,
		/*@null@*/ log_callback cb);

/**\brief Sets global logging level
 * \param[in] level an integer value. Values lower than this will be pass to
 * specific logging functions. (defaults to 10). Set this to less than lowest
 * level to disable logging for all methods.
 */
LogReturn log_setlevel(int level);

/**\brief Sets file logging level
 * \param[in] level an integer value. Values lower than this will be logged to file
 * if it is also lower than global level. (defaults to 100). Set this to less
 * than lowest level to disable logging to file.
 */
LogReturn log_setlevel_file(int level);

/**\brief Sets console logging level
 * \param[in] level an integer value. Values lower than this will be logged to
 * console if it is also lower than global level. (defaults to 100). Set this to
 * less than lowest level to disable logging to file.
 */
LogReturn log_setlevel_console(int level);

/**\brief Sets callback logging level
 * \param[in] level an integer value. Values lower than this will be logged to
 * callback if it is also lower than global level. (defaults to 100). Set this
 * to less than lowest level to disable logging to callback.
 */
LogReturn log_setlevel_cb(int level);

/**\brief Logs a message
 * \param[in] level Level of the message (integer)
 * \param[in] filename __FILE__ macro or use a custom string
 * \param[in] funcname __FUNCTION__ macro or use a custom string
 * \param[in] linenum an integer specifying the line number, or a custom number
 * \param[in] format printf formatted format, remaining arguments are treated as
 * print inputs.
 * \details
 * See the example case at the bottom of logger.c to see how to wrap this in a
 * macro.
 */
/*@printflike@*/ LogReturn log_log(int level,
		/*@nulL@*/ const char *filename,
		/*@nulL@*/ const char *funcname,
		int linenum,
		LogStr format,...);

/**\brief Closes logging facilities (closes log file if opened).
 */
void log_end(void);

#endif//__LOGGER_H__
