#ifndef KTYPES_H
#define KTYPES_H

namespace kex
{
	namespace Types
	{
		enum ComponentType {
			ActionType		 = 0x1, 
			EventType			 = 0x2, 
			TrialType			 = 0x4, 
			ExperimentType = 0x8,
			UndefinedComponentType  = 0x16,
		};
		
		enum LogLevelType   {
			DebugLogLevel			= 0x1,
			WarningLogLevel		= 0x2,
			CriticalLogLevel	= 0x4,
			FatalLogLevel			= 0x8,
		};
	
		enum DataDirectoryType {
			LogDirectoryType								= 0x1,
			ExperimentDirectoryType					= 0x2,
			TemplateDirectoryType						= 0x4,
			ActionTemplateDirectoryType			= 0x8,
			EventTemplateDirectoryType			= 0x10,
			TrialTemplateDirectoryType			= 0x20,
			ExperimentTemplateDirectoryType = 0x40,
			AllDataDirectories = (LogDirectoryType | ExperimentDirectoryType |
														TemplateDirectoryType | 
														ActionTemplateDirectoryType |
														EventTemplateDirectoryType |
														TrialTemplateDirectoryType |
														ExperimentTemplateDirectoryType),
			
		};
	}
}
#endif