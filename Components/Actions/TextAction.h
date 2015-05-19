#ifndef TEXTACTION_H
#define TEXTACTION_H

#include <QStaticText>
#include <QColor>

#include "Common/Config.h"
#include "Components/Component.h"


namespace kex
{
  class TextAction : public Component
  {
    Q_OBJECT
    Q_PROPERTY(QString text          READ text          WRITE setText)
    Q_PROPERTY(qint64 duration      READ durationMSecs WRITE setDurationMSecs)
    Q_PROPERTY(qint64 delay         READ delayMSecs    WRITE setDelayMSecs)
    Q_PROPERTY(QString text          READ text          WRITE setText)
    Q_PROPERTY(QString family        READ family        WRITE setFamily)
    Q_PROPERTY(int     pointSize     READ pointSize     WRITE setPointSize)
    Q_PROPERTY(QColor  background    READ background    WRITE setBackground)
    Q_PROPERTY(QColor  foreground    READ foreground    WRITE setForeground)
    Q_PROPERTY(qint32  xoffset       READ xoffset       WRITE setXoffset)
    Q_PROPERTY(qint32  yoffset       READ yoffset       WRITE setYoffset)
    Q_PROPERTY(kex::Component::ComponentPositions position   READ position WRITE setPosition)

 public:
    typedef TextAction* Pointer;
    /** \brief Default constructor for TextAction
     *
     * \author James Kyle KSpace MRI
     * \date 2010-12-13
     * \return TextAction a text action with specified attributes
     **/
    TextAction(QObject *parent = 0,
               Component::Pointer parentComponent=0,
               const QString& name=QString(""),
               const QString& description=QString(""),
               const QString& label=QString(""),
               const QSet<QString>& categories=QSet<QString>(),
               qint64 durationMSecs=0,
               qint64 delayMSecs=0,
               const QString& text=QString(""),
               const QString& family="Helvetica",
               int pointSize=12,
               const QColor& foreground=QColor("black"),
               const QColor& background=QColor("white"),
               qint32 xoffset=0,
               qint32 yoffset=0,
               const Component::ComponentPositions& position=Component::DefaultPosition
               );
   /** \brief Destructor for object
    *
    * \author James Kyle KSpace MRI
    * \date 2010-04-01
    **/
    ~TextAction();

    /** \brief Returns the delay in milliseconds.
     *
     * \author James Kyle KSpace MRI
     * \date 2010-12-13
     * \return qint64 the delay of component in milliseconds
     **/
    qint64 durationMSecs() const {return m_durationMSecs;}

    /** \brief Sets the duration in milliseconds.
     *
     * \author James Kyle KSpace MRI
     * \date 2010-12-13
     * \param durationMSecs the new value for duration in milliseconds
     **/
    void setDurationMSecs(const qint64 durationMSecs){ m_durationMSecs = durationMSecs;}

    /** \brief Returns the delay in milliseconds.
     *
     * \author James Kyle KSpace MRI
     * \date 2010-12-13
     * \return qint64 the delay of component in milliseconds
     **/
    qint64 delayMSecs() const {return m_delayMSecs;}

    /** \brief Sets the delay in milliseconds.
     *
     * \author James Kyle KSpace MRI
     * \date 2010-12-13
     * \param delayMSecs the new value for delay in milliseconds
     **/
    void setDelayMSecs(const qint64 delayMSecs);

    /** \brief Returns the  QStaticText object for component
     *
     * \author James Kyle KSpace MRI
     * \date 2010-12-13
     * \return QString the text to be displayed
     **/
    QString text() const {return m_text.text();}

    /** \brief Sets the  text to be displayed
     *
     * \author James Kyle KSpace MRI
     * \date 2010-12-13
     * \param QString the new text to display
     **/
    void setText(const QString& text) {m_text.setText(text);}

    /** \brief Returns the font family for the TextAction.
     *
     * \author James Kyle KSpace MRI
     * \date 2010-12-13
     * \return QString the font family being used by component
     **/
    QString family() const {return m_font.family();}

    /** \brief Sets the font family to be used.
     *
     * \author James Kyle KSpace MRI
     * \date 2010-12-13
     * \param family the new font family to use
     **/
    void setFamily(const QString& family) {m_font.setFamily(family);}

    /** \brief Returns the point size of the text.
     * \author James Kyle KSpace MRI
     * \date 2010-12-13
     * \return qint64 the delay of component in milliseconds
     **/
    int pointSize() const {return m_font.pointSize();}

    /** \brief Sets the point size for the font.
     *
     * \author James Kyle KSpace MRI
     * \date 2010-12-13
     * \param pointSize the new point size to use.
     **/
    void setPointSize(int pointSize) {m_font.setPointSize(pointSize);}

    /** \brief Returns the foreground color for the text.
     *
     * \author James Kyle KSpace MRI
     * \date 2010-12-13
     * \return QString the foreground color for component
     **/
    QColor foreground() const {return m_foreground;}

    /** \brief Sets the foreground color for the component.
     *
     * \author James Kyle KSpace MRI
     * \date 2010-12-13
     * \param foreground the new foreground color to use for text.
     **/
    void setForeground(const QColor& color) {m_foreground = color;}

    /** \brief Returns the background color used for text.
     *
     * \author James Kyle KSpace MRI
     * \date 2010-12-13
     * \return QString the background color being used for display.
     **/
    QColor background() const {return m_background;}

    /** \brief Sets the background color for text.
     *
     * \author James Kyle KSpace MRI
     * \date 2010-12-13
     * \param background the new color to use for text background
     **/
    void setBackground(const QColor& color) {m_background = color;}

    /** \brief Returns the offset along the x axis.
     *
     * \author James Kyle KSpace MRI
     * \date 2010-12-13
     * \return qint32 the offset along the x axis
     **/
    qint32 xoffset() const {return m_xoffset;}

    /** \brief Sets the offset along the x axis.
     *
     * \author James Kyle KSpace MRI
     * \date 2010-12-13
     * \param offset the new offset for x axis.
     **/
    void setXoffset(const qint32 offset) {m_xoffset = offset;}

    /** \brief Returns the offset along the y axis.
     *
     * \author James Kyle KSpace MRI
     * \date 2010-12-13
     * \return qint32 the offset for the y axis
     **/
    qint32 yoffset() const {return m_yoffset;}

    /** \brief Sets the offset for the y axis.
     *
     * \author James Kyle KSpace MRI
     * \date 2010-12-13
     * \param offset the new offset for the y axis
     **/
    void setYoffset(const qint32 offset) {m_yoffset = offset;}

    /** \brief Returns the position the text is placed
     *
     * \author James Kyle KSpace MRI
     * \date 2010-12-13
     * \return Component::ComponentPositions the position for the component
     **/
    const Component::ComponentPositions position() const {return m_position;}

    /** \brief Sets the position for text display.
     *
     * \author James Kyle KSpace MRI
     * \date 2010-12-13
     * \param position the new position for text
     **/
    void setPosition(const Component::ComponentPositions& position)
    {
      m_position = position;
    }

    /** \brief The font used for the text display.
     *
     * \author James Kyle KSpace MRI
     * \date 2010-12-13
     * \return QFont the font used for display
     **/
    const QFont& font() const {return m_font;}

    /** \brief Sets the font to use for text display.
     *
     * \author James Kyle KSpace MRI
     * \date 2010-12-13
     * \param font the new font to use for text display
     **/
    void setFont(const QFont& font) { m_font = font;}

    Pointer clone() const;

    bool operator==(const Component& other) const;
    bool operator!=(const Component& other) const;

  private:
    qint64     m_durationMSecs; //!< duration for component in milliseconds
    qint64     m_delayMSecs; //!< delay for component in milliseconds
    QStaticText m_text; //!< text object used for rendering
    QColor      m_foreground; //!< foreground color used for text
    QColor      m_background; //!< background color used for text
    qint32      m_xoffset; //!< offset along the x axis
    qint32      m_yoffset; //!< offset along the y axis
    Component::ComponentPositions m_position; //!< starting position for text rendering
    QFont       m_font; //!< font used for text display
    };
};
#endif
