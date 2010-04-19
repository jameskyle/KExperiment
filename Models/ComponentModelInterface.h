#ifndef COMPONENTMODELINTERFACE_H
#define COMPONENTMODELINTERFACE_H
#include <QAbstractTableModel>
#include <QResource>
#include <QStringList>
#include <QXmlStreamReader>

#include <Common/Uncopyable.h>

namespace kex
{
	/** \brief  Model for all component data
	* 
	* Copyright 2010 KSpace MRI. All Rights Reserved.
	*
	* \author James Kyle
	* \author $LastChangedBy$
	* \date 2010-4-12
	* \date $LastChangedDate$
	* \version $Rev$  \sa ComponentInterface
	**/
	class ComponentModelInterface : public QAbstractTableModel, 
																  private Uncopyable
	{
	public:
		/** \brief  Default constructor.
		* 
		* Copyright 2010 KSpace MRI. All Rights Reserved.
		*
		* Sets up the component item model.
		* 
		* \author James Kyle
		* \author $LastChangedBy$
		* \date 2010-4-12
		* \date $LastChangedDate$
		* \param parent pointer to the parent classe. 
		* \version $Rev$  \sa ComponentInterface
		**/
		ComponentModelInterface(QObject *parent = 0);
		
		/** \brief  Default destructor.
		 * 
		 * Copyright 2010 KSpace MRI. All Rights Reserved.
		 * 
		 * \author James Kyle
		 * \author $LastChangedBy$
		 * \date 2010-4-12
		 * \date $LastChangedDate$
		 * \version $Rev$
		 **/
		virtual ~ComponentModelInterface() {}
		
		virtual void setData(const QStringList& resourceList) = 0;
		virtual const QString templatePath() const = 0;
		
		int rowCount(const QModelIndex &parent) const;
		int columnCount(const QModelIndex &index, int role) const;
		QVariant data(const QModelIndex &index, int role) const;
		QVariant headerData(int section, Qt::Orientation orientation,
												int role) const;
		
	private:
		QXmlStreamReader xmlReader;
		
		
	};
	

}
#endif