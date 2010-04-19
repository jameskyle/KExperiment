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
			
		enum DataDirectoryType {
			LogDirectoryType								= 0x1,
			ExperimentDirectoryType					= 0x2,
			TemplateDirectoryType						= 0x4,
		};
	}
}
#endif