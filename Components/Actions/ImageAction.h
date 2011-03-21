#ifndef IMAGEACTION_H
#define IMAGEACTION_H

#include <QSet>
#include <QImage>

#include "Components/Component.h"
#include "Components/ComponentExceptions.h"

namespace kex
{
  class ImageAction : public Component
  {
    Q_OBJECT
    Q_PROPERTY(quint64 duration      READ durationMSecs  WRITE setDurationMSecs)
    Q_PROPERTY(QString image         READ imagePath      WRITE setImagePath)
    Q_PROPERTY(quint64 delay         READ delayMSecs     WRITE setDelayMSecs)
    Q_PROPERTY(qint32  xoffset       READ xoffset        WRITE setXoffset)
    Q_PROPERTY(qint32  yoffset       READ yoffset        WRITE setYoffset)
    Q_PROPERTY(kex::Component::ComponentPositions position READ position WRITE setPosition)

  public:
    typedef ImageAction* Pointer;
    /** \brief Default constructor for ImageAction.
     *
     * \author James Kyle KSpace MRI
     * \date 2010-12-13
     * \return ImageAction an image action with specified attributes.
     **/
    ImageAction(QObject            *parent = 0,
                Component::Pointer  parentComponent=0,
                const QString&      name="",
                const QString&      description=QString(""),
                const QString&      label=QString(""),
                const QSet<QString> categories=QSet<QString>(),
                quint64             durationMSecs=0,
                quint64             delayMSecs=0,
                const QString&      imagePath=QString(""),
                qint32              xoffset=0,
                qint32              yoffset=0,
                const Component::ComponentPositions& position=Component::DefaultPosition
                );

    /** \brief Default destructor for component
     *
     * \author James Kyle KSpace MRI
     * \date 2010-12-13
     **/
    ~ImageAction();

    /** \brief Returns the duration in milliseconds.
     *
     * \author James Kyle KSpace MRI
     * \date 2010-12-13
     * \return quint64 the duration of component in milliseconds
     **/
    quint64 durationMSecs() const {return m_durationMSecs;}

    /** \brief Sets the duration in milliseconds.
     *
     * \author James Kyle KSpace MRI
     * \date 2010-12-13
     * \param durationMSecs the new value for duration in milliseconds
     **/
    void setDurationMSecs(quint64 durationMSecs);
    /** \brief String representation for the ImageAction.
     *
     * \author James Kyle KSpace MRI
     * \date 2011-03-18
     * \return QString representation of the component
     **/
     const QString toString() const;

    /** \brief Returns the delay in milliseconds.
     *
     * \author James Kyle KSpace MRI
     * \date 2010-12-13
     * \return quint64 the delay of component in milliseconds
     **/
    quint64 delayMSecs() const {return m_delayMSecs;}

    /** \brief Sets the delay in milliseconds.
        *
     * \author James Kyle KSpace MRI
     * \date 2010-12-13
     * \param delayMSecs the new value for delay in milliseconds
     **/
    void setDelayMSecs(quint64 delayMSecs) {m_delayMSecs = delayMSecs;}

    /** \brief Returns the offset of component along x axis.
     *
     * \author James Kyle KSpace MRI
     * \date 2010-12-13
     * \return qint32 the x offset of component
     **/
    qint32 xoffset() const {return m_xoffset;}

    /** \brief Sets the X offset for component.
     *
     * \author James Kyle KSpace MRI
     * \date 2010-12-13
     * \param xoffset the new offset for component along x axis
     **/
    void setXoffset(qint32 xoffset) { m_xoffset = xoffset;}

    /** \brief Returns the offset for component along y axis.
     *
     * \author James Kyle KSpace MRI
     * \date 2010-12-13
     * \return qint32 the offset of component along y axis
     **/
    qint32 yoffset() const {return m_yoffset;}

    /** \brief Sets the offset for component along y axis
     *
     * \author James Kyle KSpace MRI
     * \date 2010-12-13
     * \param yoffset the new offset along the y axis
     **/
    void setYoffset(qint32 yoffset) {m_yoffset = yoffset;}

    /** \brief Returns the position of the component in view.
     *
     * \author James Kyle KSpace MRI
     * \date 2010-12-13
     * \return Component::ComponentTypes the position of component in view
     **/
    Component::ComponentPositions position() const {return m_position;}

    /** \brief Sets the position for the component in view.
     *
     * \author James Kyle KSpace MRI
     * \date 2010-12-13
     * \param position the new position for component
     **/
    void setPosition(const Component::ComponentPositions& position)
    {
      m_position = position;
    }

    /** \brief Returns the image object for the ImageAction.
     *
     * \author James Kyle KSpace MRI
     * \date 2010-12-13
     * \return QImage the image used by the ImageAction.
     **/
    const QImage& image() const { return m_image;}

    QString imagePath() const {return m_imagePath;}
    void setImagePath(const QString& imagePath);

    Pointer clone() const;
    bool operator==(const Component& other) const;
    bool operator!=(const Component& other) const;

  private:
    quint64 m_durationMSecs; //!< duration for component in milliseconds
    quint64 m_delayMSecs; //!< delay for component in milliseconds
    QImage  m_image; //!< the image used for display.
    QString m_imagePath; //!< the path for the image resource
    qint32  m_xoffset; //!< the offset for component along x axis
    qint32  m_yoffset; //!< the offset for component along y axis
    Component::ComponentPositions m_position; //!< the position for component in view


  };
};
#endif
