#ifndef LIVEVIEW_H
#define LIVEVIEW_H
#include "ui_ViewerFrame.h"

namespace kex 
{
	/** \brief  The goggle event viewer; text, video, sound monitor
	 * 
	 * Copyright 2010 KSpace MRI. All Rights Reserved.
	 *
	 * \author James Kyle
	 * \author $LastChangedBy$
	 * \date 2010-4-7
	 * \date $LastChangedDate$
	 * \version $Rev$ 
	 **/
	class LiveView : public QFrame, private Ui::ViewerFrame 
	{
	public:
		/** \brief  LiveView constructor
		 * 
		 * Copyright 2010 KSpace MRI. All Rights Reserved.
		 * 
		 * \author James Kyle
		 * \author $LastChangedBy$
		 * \date 2010-4-7
		 * \date $LastChangedDate$
		* \version $Rev$  
		**/
		LiveView(QWidget *parent = 0);
		
		/** \brief  LiveView destructor
		 * 
		 * Copyright 2010 KSpace MRI. All Rights Reserved.
		 * 
		 * \author James Kyle
		 * \author $LastChangedBy$
		 * \date 2010-4-7
		 * \date $LastChangedDate$
		* \version $Rev$
		**/
		~LiveView() {}
		
	};

}
#endif