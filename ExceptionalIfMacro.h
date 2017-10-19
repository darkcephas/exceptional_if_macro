#ifndef exceptionalifmacro_header_def
#define exceptionalifmacro_header_def

#define ExceptionIfCalleDefine if_except_namespace::DefaultExceptionalIfCalle

#define eif( cond ) \
	if (if_except_namespace::ExceptionalIfHelperObj<ExceptionIfCalleDefine> expIfHelperObj = if_except_namespace::ExceptionalIfHelperObj<ExceptionIfCalleDefine>());\
	else\
	if (cond)\
	if (expIfHelperObj.setPassed()) ;\
	else

namespace if_except_namespace
{
	template <typename exception_Functor>
	class ExceptionalIfHelperObj
	{
	public:
		ExceptionalIfHelperObj() : mBool(false)
		{
		}

		~ExceptionalIfHelperObj()
		{
			if (!mBool)
			{
				exception_Functor::failed();
			}
		}

		inline bool setPassed()
		{
			mBool = true;
			return false;
		}

		inline operator bool()
		{
			return false;
		}

		bool mBool;
	};

	class DefaultExceptionalIfCalle
	{
	public:
		static inline void failed()
		{
		}
	};


}

#endif