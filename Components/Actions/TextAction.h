#ifndef TEXTACTION_H
#define TEXTACTION_H

#include <QStaticText>
#include <QColor>

#include "Components/Component.h"
#include "Common/Config.h"


namespace kex
{
  class TextAction : public Component
  {
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText)

  public:
    /** \brief Default constructor for TextAction
     *
     * \author James Kyle KSpace MRI
     * \date 2010-12-13
     * \return TextAction a text action with specified attributes
     **/
    TextAction(QObject *parent = 0,
               const QString& name=QString(""),
               const QString& description=QString(""),
               const QString& label=QString(""),
               const QSet<QString>& categories=QSet<QString>(),
               const QIcon& icon=QIcon(Component::DEFAULT_ICON),
               quint64 durationMSecs=0,
               quint64 delayMSecs=0,
               const QString& text=QString(""),
               const QString& family="Helvetica",
               int pointSize=12,
               const QColor& foreground=QColor("black"),
               const QColor& background=QColor("white"),
               qint32 xoffset=0,
               qint32 yoffset=0,
               const Component::ComponentPositions& position=Component::DefaultPosition
               );
    ~TextAction();

    /** \brief Returns the delay in milliseconds.
     *
     * \author James Kyle KSpace MRI
     * \date 2010-12-13
     * \return quint64 the delay of component in milliseconds
     **/
    quint64 durationMSecs() const {return m_durationMSecs;}

    /** \brief Sets the duration in milliseconds.
     *
     * \author James Kyle KSpace MRI
     * \date 2010-12-13
     * \param durationMSecs the new value for duration in milliseconds
     **/
    void setDuration(const quint64 durationMSecs){ m_durationMSecs = durationMSecs;}

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
    void setDelay(const quint64 delayMSecs) {m_delayMSecs = delayMSecs;}

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
     * \return quint64 the delay of component in milliseconds
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

    TextAction* copy() const;

  private:
    quint64     m_durationMSecs; //!< duration for component in milliseconds
    quint64     m_delayMSecs; //!< delay for component in milliseconds
    QStaticText m_text; //!< text object used for rendering
    QColor      m_foreground; //!< foreground color used for text
    QColor      m_background; //!< background color used for text
    qint32      m_xoffset; //!< offset along the x axis
    qint32      m_yoffset; //!< offset along the y axis
    Component::ComponentPositions m_position; //!< starting position for text rendering
    QFont       m_font; //!< font used for text display
    };
}
#endif
