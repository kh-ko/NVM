/***************************************************************************
**                                                                        **
**  NChartControl, an easy to use, modern plotting widget for Qt            **
**  Copyright (C) 2011-2021 Emanuel Eichhammer                            **
**                                                                        **
**  This program is free software: you can redistribute it and/or modify  **
**  it under the terms of the GNU General Public License as published by  **
**  the Free Software Foundation, either version 3 of the License, or     **
**  (at your option) any later version.                                   **
**                                                                        **
**  This program is distributed in the hope that it will be useful,       **
**  but WITHOUT ANY WARRANTY; without even the implied warranty of        **
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         **
**  GNU General Public License for more details.                          **
**                                                                        **
**  You should have received a copy of the GNU General Public License     **
**  along with this program.  If not, see http://www.gnu.org/licenses/.   **
**                                                                        **
****************************************************************************
**           Author: Emanuel Eichhammer                                   **
**  Website/Contact: http://www.NChartControl.com/                          **
**             Date: 29.03.21                                             **
**          Version: 2.1.0                                                **
****************************************************************************/

#ifndef NCHARTCONTROL_H
#define NCHARTCONTROL_H

#include <QtCore/qglobal.h>

// some Qt version/configuration dependent macros to include or exclude certain code paths:
#ifdef NCHARTCONTROL_USE_OPENGL
#  if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
#    define NCHART_OPENGL_PBUFFER
#  else
#    define NCHART_OPENGL_FBO
#  endif
#  if QT_VERSION >= QT_VERSION_CHECK(5, 3, 0)
#    define NCHART_OPENGL_OFFSCREENSURFACE
#  endif
#endif

#if QT_VERSION >= QT_VERSION_CHECK(5, 4, 0)
#  define NCHART_DEVICEPIXELRATIO_SUPPORTED
#  if QT_VERSION >= QT_VERSION_CHECK(5, 6, 0)
#    define NCHART_DEVICEPIXELRATIO_FLOAT
#  endif
#endif

#include <QtCore/QObject>
#include <QtCore/QPointer>
#include <QtCore/QSharedPointer>
#include <QtCore/QTimer>
#include <QtGui/QPainter>
#include <QtGui/QPainterPath>
#include <QtGui/QPaintEvent>
#include <QtGui/QMouseEvent>
#include <QtGui/QWheelEvent>
#include <QtGui/QPixmap>
#include <QtCore/QVector>
#include <QtCore/QString>
#include <QtCore/QDateTime>
#include <QtCore/QMultiMap>
#include <QtCore/QFlags>
#include <QtCore/QDebug>
#include <QtCore/QStack>
#include <QtCore/QCache>
#include <QtCore/QMargins>
#include <qmath.h>
#include <limits>
#include <algorithm>
#ifdef NCHART_OPENGL_FBO
#  include <QtGui/QOpenGLContext>
#  if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
#    include <QtGui/QOpenGLFramebufferObject>
#  else
#    include <QOpenGLFramebufferObject>
#    include <QOpenGLPaintDevice>
#  endif
#  ifdef NCHART_OPENGL_OFFSCREENSURFACE
#    include <QtGui/QOffscreenSurface>
#  else
#    include <QtGui/QWindow>
#  endif
#endif
#ifdef NCHART_OPENGL_PBUFFER
#  include <QtOpenGL/QGLPixelBuffer>
#endif
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
#  include <qnumeric.h>
#  include <QtGui/QWidget>
#  include <QtGui/QPrinter>
#  include <QtGui/QPrintEngine>
#else
#  include <QtNumeric>
#  include <QtWidgets/QWidget>
#  include <QtPrintSupport/QtPrintSupport>
#endif
#if QT_VERSION >= QT_VERSION_CHECK(4, 8, 0)
#  include <QtCore/QElapsedTimer>
#endif
# if QT_VERSION >= QT_VERSION_CHECK(5, 2, 0)
#  include <QtCore/QTimeZone>
#endif

class NChartPainter;
class NChartControl;
class NChartLayerable;
class NChartLayoutElement;
class NChartLayout;
class NChartAxis;
class NChartAxisRect;
class NChartAxisPainterPrivate;
class NChartAbstractPlottable;
class NChartGraph;
class NChartAbstractItem;
class NChartPlottableInterface1D;
class NChartLegend;
class NChartItemPosition;
class NChartLayer;
class NChartAbstractLegendItem;
class NChartSelectionRect;
class NChartColorMap;
class NChartColorScale;
class NChartBars;
class NChartPolarAxisRadial;
class NChartPolarAxisAngular;
class NChartPolarGrid;
class NChartPolarGraph;

/* including file 'src/global.h'            */
/* modified 2021-03-29T02:30:44, size 16981 */

#define NCHARTCONTROL_VERSION_STR "2.1.0"
#define NCHARTCONTROL_VERSION 0x020100

// decl definitions for shared library compilation/usage:
#if defined(QT_STATIC_BUILD)
#  define NCHART_LIB_DECL
#elif defined(NCHARTCONTROL_COMPILE_LIBRARY)
#  define NCHART_LIB_DECL Q_DECL_EXPORT
#elif defined(NCHARTCONTROL_USE_LIBRARY)
#  define NCHART_LIB_DECL Q_DECL_IMPORT
#else
#  define NCHART_LIB_DECL
#endif

// define empty macro for Q_DECL_OVERRIDE if it doesn't exist (Qt < 5)
#ifndef Q_DECL_OVERRIDE
#  define Q_DECL_OVERRIDE
#endif

/*!
  The NChart Namespace contains general enums, QFlags and functions used throughout the NChartControl
  library.
  
  It provides QMetaObject-based reflection of its enums and flags via \a NChart::staticMetaObject.
*/
#ifndef Q_MOC_RUN
namespace NChart {
#else
class NChart { // when in moc-run, make it look like a class, so we get Q_GADGET, Q_ENUMS/Q_FLAGS features in namespace
  Q_GADGET
  Q_ENUMS(ExportPen)
  Q_ENUMS(ResolutionUnit)
  Q_ENUMS(SignDomain)
  Q_ENUMS(MarginSide)
  Q_FLAGS(MarginSides)
  Q_ENUMS(AntialiasedElement)
  Q_FLAGS(AntialiasedElements)
  Q_ENUMS(PlottingHint)
  Q_FLAGS(PlottingHints)
  Q_ENUMS(Interaction)
  Q_FLAGS(Interactions)
  Q_ENUMS(SelectionRectMode)
  Q_ENUMS(SelectionType)
public:
#endif

/*!
  Defines the different units in which the image resolution can be specified in the export
  functions.

  \see NChartControl::savePng, NChartControl::saveJpg, NChartControl::saveBmp, NChartControl::saveRastered
*/
enum ResolutionUnit { ruDotsPerMeter       ///< Resolution is given in dots per meter (dpm)
                      ,ruDotsPerCentimeter ///< Resolution is given in dots per centimeter (dpcm)
                      ,ruDotsPerInch       ///< Resolution is given in dots per inch (DPI/PPI)
                    };

/*!
  Defines how cosmetic pens (pens with numerical width 0) are handled during export.

  \see NChartControl::savePdf
*/
enum ExportPen { epNoCosmetic     ///< Cosmetic pens are converted to pens with pixel width 1 when exporting
                 ,epAllowCosmetic ///< Cosmetic pens are exported normally (e.g. in PDF exports, cosmetic pens always appear as 1 pixel on screen, independent of viewer zoom level)
               };

/*!
  Represents negative and positive sign domain, e.g. for passing to \ref
  NChartAbstractPlottable::getKeyRange and \ref NChartAbstractPlottable::getValueRange.
  
  This is primarily needed when working with logarithmic axis scales, since only one of the sign
  domains can be visible at a time.
*/
enum SignDomain { sdNegative  ///< The negative sign domain, i.e. numbers smaller than zero
                  ,sdBoth     ///< Both sign domains, including zero, i.e. all numbers
                  ,sdPositive ///< The positive sign domain, i.e. numbers greater than zero
                };

/*!
  Defines the sides of a rectangular entity to which margins can be applied.
  
  \see NChartLayoutElement::setAutoMargins, NChartAxisRect::setAutoMargins
*/
enum MarginSide { msLeft     = 0x01 ///< <tt>0x01</tt> left margin
                  ,msRight   = 0x02 ///< <tt>0x02</tt> right margin
                  ,msTop     = 0x04 ///< <tt>0x04</tt> top margin
                  ,msBottom  = 0x08 ///< <tt>0x08</tt> bottom margin
                  ,msAll     = 0xFF ///< <tt>0xFF</tt> all margins
                  ,msNone    = 0x00 ///< <tt>0x00</tt> no margin
                };
Q_DECLARE_FLAGS(MarginSides, MarginSide)

/*!
  Defines what objects of a plot can be forcibly drawn antialiased/not antialiased. If an object is
  neither forcibly drawn antialiased nor forcibly drawn not antialiased, it is up to the respective
  element how it is drawn. Typically it provides a \a setAntialiased function for this.
  
  \c AntialiasedElements is a flag of or-combined elements of this enum type.
  
  \see NChartControl::setAntialiasedElements, NChartControl::setNotAntialiasedElements
*/
enum AntialiasedElement { aeAxes           = 0x0001 ///< <tt>0x0001</tt> Axis base line and tick marks
                          ,aeGrid          = 0x0002 ///< <tt>0x0002</tt> Grid lines
                          ,aeSubGrid       = 0x0004 ///< <tt>0x0004</tt> Sub grid lines
                          ,aeLegend        = 0x0008 ///< <tt>0x0008</tt> Legend box
                          ,aeLegendItems   = 0x0010 ///< <tt>0x0010</tt> Legend items
                          ,aePlottables    = 0x0020 ///< <tt>0x0020</tt> Main lines of plottables
                          ,aeItems         = 0x0040 ///< <tt>0x0040</tt> Main lines of items
                          ,aeScatters      = 0x0080 ///< <tt>0x0080</tt> Scatter symbols of plottables (excluding scatter symbols of type ssPixmap)
                          ,aeFills         = 0x0100 ///< <tt>0x0100</tt> Borders of fills (e.g. under or between graphs)
                          ,aeZeroLine      = 0x0200 ///< <tt>0x0200</tt> Zero-lines, see \ref NChartGrid::setZeroLinePen
                          ,aeOther         = 0x8000 ///< <tt>0x8000</tt> Other elements that don't fit into any of the existing categories
                          ,aeAll           = 0xFFFF ///< <tt>0xFFFF</tt> All elements
                          ,aeNone          = 0x0000 ///< <tt>0x0000</tt> No elements
                        };
Q_DECLARE_FLAGS(AntialiasedElements, AntialiasedElement)

/*!
  Defines plotting hints that control various aspects of the quality and speed of plotting.
  
  \see NChartControl::setPlottingHints
*/
enum PlottingHint { phNone              = 0x000 ///< <tt>0x000</tt> No hints are set
                    ,phFastPolylines    = 0x001 ///< <tt>0x001</tt> Graph/Curve lines are drawn with a faster method. This reduces the quality especially of the line segment
                                                ///<                joins, thus is most effective for pen sizes larger than 1. It is only used for solid line pens.
                    ,phImmediateRefresh = 0x002 ///< <tt>0x002</tt> causes an immediate repaint() instead of a soft update() when NChartControl::replot() is called with parameter \ref NChartControl::rpRefreshHint.
                                                ///<                This is set by default to prevent the plot from freezing on fast consecutive replots (e.g. user drags ranges with mouse).
                    ,phCacheLabels      = 0x004 ///< <tt>0x004</tt> axis (tick) labels will be cached as pixmaps, increasing replot performance.
                  };
Q_DECLARE_FLAGS(PlottingHints, PlottingHint)

/*!
  Defines the mouse interactions possible with NChartControl.
  
  \c Interactions is a flag of or-combined elements of this enum type.
  
  \see NChartControl::setInteractions
*/
enum Interaction { iNone              = 0x000 ///< <tt>0x000</tt> None of the interactions are possible
                   ,iRangeDrag        = 0x001 ///< <tt>0x001</tt> Axis ranges are draggable (see \ref NChartAxisRect::setRangeDrag, \ref NChartAxisRect::setRangeDragAxes)
                   ,iRangeZoom        = 0x002 ///< <tt>0x002</tt> Axis ranges are zoomable with the mouse wheel (see \ref NChartAxisRect::setRangeZoom, \ref NChartAxisRect::setRangeZoomAxes)
                   ,iMultiSelect      = 0x004 ///< <tt>0x004</tt> The user can select multiple objects by holding the modifier set by \ref NChartControl::setMultiSelectModifier while clicking
                   ,iSelectPlottables = 0x008 ///< <tt>0x008</tt> Plottables are selectable (e.g. graphs, curves, bars,... see NChartAbstractPlottable)
                   ,iSelectAxes       = 0x010 ///< <tt>0x010</tt> Axes are selectable (or parts of them, see NChartAxis::setSelectableParts)
                   ,iSelectLegend     = 0x020 ///< <tt>0x020</tt> Legends are selectable (or their child items, see NChartLegend::setSelectableParts)
                   ,iSelectItems      = 0x040 ///< <tt>0x040</tt> Items are selectable (Rectangles, Arrows, Textitems, etc. see \ref NChartAbstractItem)
                   ,iSelectOther      = 0x080 ///< <tt>0x080</tt> All other objects are selectable (e.g. your own derived layerables, other layout elements,...)
                   ,iSelectPlottablesBeyondAxisRect = 0x100 ///< <tt>0x100</tt> When performing plottable selection/hit tests, this flag extends the sensitive area beyond the axis rect
                 };
Q_DECLARE_FLAGS(Interactions, Interaction)

/*!
  Defines the behaviour of the selection rect.
  
  \see NChartControl::setSelectionRectMode, NChartControl::selectionRect, NChartSelectionRect
*/
enum SelectionRectMode { srmNone    ///< The selection rect is disabled, and all mouse events are forwarded to the underlying objects, e.g. for axis range dragging
                         ,srmZoom   ///< When dragging the mouse, a selection rect becomes active. Upon releasing, the axes that are currently set as range zoom axes (\ref NChartAxisRect::setRangeZoomAxes) will have their ranges zoomed accordingly.
                         ,srmSelect ///< When dragging the mouse, a selection rect becomes active. Upon releasing, plottable data points that were within the selection rect are selected, if the plottable's selectability setting permits. (See  \ref dataselection "data selection mechanism" for details.)
                         ,srmCustom ///< When dragging the mouse, a selection rect becomes active. It is the programmer's responsibility to connect according slots to the selection rect's signals (e.g. \ref NChartSelectionRect::accepted) in order to process the user interaction.
                       };

/*!
  Defines the different ways a plottable can be selected. These images show the effect of the
  different selection types, when the indicated selection rect was dragged:
  
  <center>
  <table>
  <tr>
    <td>\image html selectiontype-none.png stNone</td>
    <td>\image html selectiontype-whole.png stWhole</td>
    <td>\image html selectiontype-singledata.png stSingleData</td>
    <td>\image html selectiontype-datarange.png stDataRange</td>
    <td>\image html selectiontype-multipledataranges.png stMultipleDataRanges</td>
  </tr>
  </table>
  </center>
  
  \see NChartAbstractPlottable::setSelectable, NChartDataSelection::enforceType
*/
enum SelectionType { stNone                ///< The plottable is not selectable
                     ,stWhole              ///< Selection behaves like \ref stMultipleDataRanges, but if there are any data points selected, the entire plottable is drawn as selected.
                     ,stSingleData         ///< One individual data point can be selected at a time
                     ,stDataRange          ///< Multiple contiguous data points (a data range) can be selected
                     ,stMultipleDataRanges ///< Any combination of data points/ranges can be selected
                    };

/*! \internal
  
  Returns whether the specified \a value is considered an invalid data value for plottables (i.e.
  is \e nan or \e +/-inf). This function is used to check data validity upon replots, when the
  compiler flag \c NCHARTCONTROL_CHECK_DATA is set.
*/
inline bool isInvalidData(double value)
{
  return qIsNaN(value) || qIsInf(value);
}

/*! \internal
  \overload
  
  Checks two arguments instead of one.
*/
inline bool isInvalidData(double value1, double value2)
{
  return isInvalidData(value1) || isInvalidData(value2);
}

/*! \internal
  
  Sets the specified \a side of \a margins to \a value
  
  \see getMarginValue
*/
inline void setMarginValue(QMargins &margins, NChart::MarginSide side, int value)
{
  switch (side)
  {
    case NChart::msLeft: margins.setLeft(value); break;
    case NChart::msRight: margins.setRight(value); break;
    case NChart::msTop: margins.setTop(value); break;
    case NChart::msBottom: margins.setBottom(value); break;
    case NChart::msAll: margins = QMargins(value, value, value, value); break;
    default: break;
  }
}

/*! \internal
  
  Returns the value of the specified \a side of \a margins. If \a side is \ref NChart::msNone or
  \ref NChart::msAll, returns 0.
  
  \see setMarginValue
*/
inline int getMarginValue(const QMargins &margins, NChart::MarginSide side)
{
  switch (side)
  {
    case NChart::msLeft: return margins.left();
    case NChart::msRight: return margins.right();
    case NChart::msTop: return margins.top();
    case NChart::msBottom: return margins.bottom();
    default: break;
  }
  return 0;
}


extern const QMetaObject staticMetaObject; // in moc-run we create a static meta object for NChart "fake" object. This line is the link to it via NChart::staticMetaObject in normal operation as namespace

} // end of namespace NChart
Q_DECLARE_OPERATORS_FOR_FLAGS(NChart::AntialiasedElements)
Q_DECLARE_OPERATORS_FOR_FLAGS(NChart::PlottingHints)
Q_DECLARE_OPERATORS_FOR_FLAGS(NChart::MarginSides)
Q_DECLARE_OPERATORS_FOR_FLAGS(NChart::Interactions)
Q_DECLARE_METATYPE(NChart::ExportPen)
Q_DECLARE_METATYPE(NChart::ResolutionUnit)
Q_DECLARE_METATYPE(NChart::SignDomain)
Q_DECLARE_METATYPE(NChart::MarginSide)
Q_DECLARE_METATYPE(NChart::AntialiasedElement)
Q_DECLARE_METATYPE(NChart::PlottingHint)
Q_DECLARE_METATYPE(NChart::Interaction)
Q_DECLARE_METATYPE(NChart::SelectionRectMode)
Q_DECLARE_METATYPE(NChart::SelectionType)

/* end of 'src/global.h' */


/* including file 'src/vector2d.h'         */
/* modified 2021-03-29T02:30:44, size 4988 */

class NCHART_LIB_DECL NChartVector2D
{
public:
  NChartVector2D();
  NChartVector2D(double x, double y);
  NChartVector2D(const QPoint &point);
  NChartVector2D(const QPointF &point);
  
  // getters:
  double x() const { return mX; }
  double y() const { return mY; }
  double &rx() { return mX; }
  double &ry() { return mY; }
  
  // setters:
  void setX(double x) { mX = x; }
  void setY(double y) { mY = y; }
  
  // non-virtual methods:
  double length() const { return qSqrt(mX*mX+mY*mY); }
  double lengthSquared() const { return mX*mX+mY*mY; }
  double angle() const { return qAtan2(mY, mX); }
  QPoint toPoint() const { return QPoint(int(mX), int(mY)); }
  QPointF toPointF() const { return QPointF(mX, mY); }
  
  bool isNull() const { return qIsNull(mX) && qIsNull(mY); }
  void normalize();
  NChartVector2D normalized() const;
  NChartVector2D perpendicular() const { return NChartVector2D(-mY, mX); }
  double dot(const NChartVector2D &vec) const { return mX*vec.mX+mY*vec.mY; }
  double distanceSquaredToLine(const NChartVector2D &start, const NChartVector2D &end) const;
  double distanceSquaredToLine(const QLineF &line) const;
  double distanceToStraightLine(const NChartVector2D &base, const NChartVector2D &direction) const;
  
  NChartVector2D &operator*=(double factor);
  NChartVector2D &operator/=(double divisor);
  NChartVector2D &operator+=(const NChartVector2D &vector);
  NChartVector2D &operator-=(const NChartVector2D &vector);
  
private:
  // property members:
  double mX, mY;
  
  friend inline const NChartVector2D operator*(double factor, const NChartVector2D &vec);
  friend inline const NChartVector2D operator*(const NChartVector2D &vec, double factor);
  friend inline const NChartVector2D operator/(const NChartVector2D &vec, double divisor);
  friend inline const NChartVector2D operator+(const NChartVector2D &vec1, const NChartVector2D &vec2);
  friend inline const NChartVector2D operator-(const NChartVector2D &vec1, const NChartVector2D &vec2);
  friend inline const NChartVector2D operator-(const NChartVector2D &vec);
};
Q_DECLARE_TYPEINFO(NChartVector2D, Q_MOVABLE_TYPE);

inline const NChartVector2D operator*(double factor, const NChartVector2D &vec) { return NChartVector2D(vec.mX*factor, vec.mY*factor); }
inline const NChartVector2D operator*(const NChartVector2D &vec, double factor) { return NChartVector2D(vec.mX*factor, vec.mY*factor); }
inline const NChartVector2D operator/(const NChartVector2D &vec, double divisor) { return NChartVector2D(vec.mX/divisor, vec.mY/divisor); }
inline const NChartVector2D operator+(const NChartVector2D &vec1, const NChartVector2D &vec2) { return NChartVector2D(vec1.mX+vec2.mX, vec1.mY+vec2.mY); }
inline const NChartVector2D operator-(const NChartVector2D &vec1, const NChartVector2D &vec2) { return NChartVector2D(vec1.mX-vec2.mX, vec1.mY-vec2.mY); }
inline const NChartVector2D operator-(const NChartVector2D &vec) { return NChartVector2D(-vec.mX, -vec.mY); }

/*! \relates NChartVector2D

  Prints \a vec in a human readable format to the qDebug output.
*/
inline QDebug operator<< (QDebug d, const NChartVector2D &vec)
{
    d.nospace() << "NChartVector2D(" << vec.x() << ", " << vec.y() << ")";
    return d.space();
}

/* end of 'src/vector2d.h' */


/* including file 'src/painter.h'          */
/* modified 2021-03-29T02:30:44, size 4035 */

class NCHART_LIB_DECL NChartPainter : public QPainter
{
  Q_GADGET
public:
  /*!
    Defines special modes the painter can operate in. They disable or enable certain subsets of features/fixes/workarounds,
    depending on whether they are wanted on the respective output device.
  */
  enum PainterMode { pmDefault       = 0x00   ///< <tt>0x00</tt> Default mode for painting on screen devices
                     ,pmVectorized   = 0x01   ///< <tt>0x01</tt> Mode for vectorized painting (e.g. PDF export). For example, this prevents some antialiasing fixes.
                     ,pmNoCaching    = 0x02   ///< <tt>0x02</tt> Mode for all sorts of exports (e.g. PNG, PDF,...). For example, this prevents using cached pixmap labels
                     ,pmNonCosmetic  = 0x04   ///< <tt>0x04</tt> Turns pen widths 0 to 1, i.e. disables cosmetic pens. (A cosmetic pen is always drawn with width 1 pixel in the vector image/pdf viewer, independent of zoom.)
                   };
  Q_ENUMS(PainterMode)
  Q_FLAGS(PainterModes)
  Q_DECLARE_FLAGS(PainterModes, PainterMode)
  
  NChartPainter();
  explicit NChartPainter(QPaintDevice *device);
  
  // getters:
  bool antialiasing() const { return testRenderHint(QPainter::Antialiasing); }
  PainterModes modes() const { return mModes; }

  // setters:
  void setAntialiasing(bool enabled);
  void setMode(PainterMode mode, bool enabled=true);
  void setModes(PainterModes modes);

  // methods hiding non-virtual base class functions (QPainter bug workarounds):
  bool begin(QPaintDevice *device);
  void setPen(const QPen &pen);
  void setPen(const QColor &color);
  void setPen(Qt::PenStyle penStyle);
  void drawLine(const QLineF &line);
  void drawLine(const QPointF &p1, const QPointF &p2) {drawLine(QLineF(p1, p2));}
  void save();
  void restore();
  
  // non-virtual methods:
  void makeNonCosmetic();
  
protected:
  // property members:
  PainterModes mModes;
  bool mIsAntialiasing;
  
  // non-property members:
  QStack<bool> mAntialiasingStack;
};
Q_DECLARE_OPERATORS_FOR_FLAGS(NChartPainter::PainterModes)
Q_DECLARE_METATYPE(NChartPainter::PainterMode)

/* end of 'src/painter.h' */


/* including file 'src/paintbuffer.h'      */
/* modified 2021-03-29T02:30:44, size 5006 */

class NCHART_LIB_DECL NChartAbstractPaintBuffer
{
public:
  explicit NChartAbstractPaintBuffer(const QSize &size, double devicePixelRatio);
  virtual ~NChartAbstractPaintBuffer();
  
  // getters:
  QSize size() const { return mSize; }
  bool invalidated() const { return mInvalidated; }
  double devicePixelRatio() const { return mDevicePixelRatio; }
  
  // setters:
  void setSize(const QSize &size);
  void setInvalidated(bool invalidated=true);
  void setDevicePixelRatio(double ratio);
  
  // introduced virtual methods:
  virtual NChartPainter *startPainting() = 0;
  virtual void donePainting() {}
  virtual void draw(NChartPainter *painter) const = 0;
  virtual void clear(const QColor &color) = 0;
  
protected:
  // property members:
  QSize mSize;
  double mDevicePixelRatio;
  
  // non-property members:
  bool mInvalidated;
  
  // introduced virtual methods:
  virtual void reallocateBuffer() = 0;
};


class NCHART_LIB_DECL NChartPaintBufferPixmap : public NChartAbstractPaintBuffer
{
public:
  explicit NChartPaintBufferPixmap(const QSize &size, double devicePixelRatio);
  virtual ~NChartPaintBufferPixmap() Q_DECL_OVERRIDE;
  
  // reimplemented virtual methods:
  virtual NChartPainter *startPainting() Q_DECL_OVERRIDE;
  virtual void draw(NChartPainter *painter) const Q_DECL_OVERRIDE;
  void clear(const QColor &color) Q_DECL_OVERRIDE;
  
protected:
  // non-property members:
  QPixmap mBuffer;
  
  // reimplemented virtual methods:
  virtual void reallocateBuffer() Q_DECL_OVERRIDE;
};


#ifdef NCHART_OPENGL_PBUFFER
class NCHART_LIB_DECL NChartPaintBufferGlPbuffer : public NChartAbstractPaintBuffer
{
public:
  explicit NChartPaintBufferGlPbuffer(const QSize &size, double devicePixelRatio, int multisamples);
  virtual ~NChartPaintBufferGlPbuffer() Q_DECL_OVERRIDE;
  
  // reimplemented virtual methods:
  virtual NChartPainter *startPainting() Q_DECL_OVERRIDE;
  virtual void draw(NChartPainter *painter) const Q_DECL_OVERRIDE;
  void clear(const QColor &color) Q_DECL_OVERRIDE;
  
protected:
  // non-property members:
  QGLPixelBuffer *mGlPBuffer;
  int mMultisamples;
  
  // reimplemented virtual methods:
  virtual void reallocateBuffer() Q_DECL_OVERRIDE;
};
#endif // NCHART_OPENGL_PBUFFER


#ifdef NCHART_OPENGL_FBO
class NCHART_LIB_DECL NChartPaintBufferGlFbo : public NChartAbstractPaintBuffer
{
public:
  explicit NChartPaintBufferGlFbo(const QSize &size, double devicePixelRatio, QWeakPointer<QOpenGLContext> glContext, QWeakPointer<QOpenGLPaintDevice> glPaintDevice);
  virtual ~NChartPaintBufferGlFbo() Q_DECL_OVERRIDE;
  
  // reimplemented virtual methods:
  virtual NChartPainter *startPainting() Q_DECL_OVERRIDE;
  virtual void donePainting() Q_DECL_OVERRIDE;
  virtual void draw(NChartPainter *painter) const Q_DECL_OVERRIDE;
  void clear(const QColor &color) Q_DECL_OVERRIDE;
  
protected:
  // non-property members:
  QWeakPointer<QOpenGLContext> mGlContext;
  QWeakPointer<QOpenGLPaintDevice> mGlPaintDevice;
  QOpenGLFramebufferObject *mGlFrameBuffer;
  
  // reimplemented virtual methods:
  virtual void reallocateBuffer() Q_DECL_OVERRIDE;
};
#endif // NCHART_OPENGL_FBO

/* end of 'src/paintbuffer.h' */


/* including file 'src/layer.h'            */
/* modified 2021-03-29T02:30:44, size 7038 */

class NCHART_LIB_DECL NChartLayer : public QObject
{
  Q_OBJECT
  /// \cond INCLUDE_QPROPERTIES
  Q_PROPERTY(NChartControl* parentPlot READ parentPlot)
  Q_PROPERTY(QString name READ name)
  Q_PROPERTY(int index READ index)
  Q_PROPERTY(QList<NChartLayerable*> children READ children)
  Q_PROPERTY(bool visible READ visible WRITE setVisible)
  Q_PROPERTY(LayerMode mode READ mode WRITE setMode)
  /// \endcond
public:
  
  /*!
    Defines the different rendering modes of a layer. Depending on the mode, certain layers can be
    replotted individually, without the need to replot (possibly complex) layerables on other
    layers.

    \see setMode
  */
  enum LayerMode { lmLogical   ///< Layer is used only for rendering order, and shares paint buffer with all other adjacent logical layers.
                   ,lmBuffered ///< Layer has its own paint buffer and may be replotted individually (see \ref replot).
                 };
  Q_ENUMS(LayerMode)
  
  NChartLayer(NChartControl* parentPlot, const QString &layerName);
  virtual ~NChartLayer();
  
  // getters:
  NChartControl *parentPlot() const { return mParentPlot; }
  QString name() const { return mName; }
  int index() const { return mIndex; }
  QList<NChartLayerable*> children() const { return mChildren; }
  bool visible() const { return mVisible; }
  LayerMode mode() const { return mMode; }
  
  // setters:
  void setVisible(bool visible);
  void setMode(LayerMode mode);
  
  // non-virtual methods:
  void replot();
  
protected:
  // property members:
  NChartControl *mParentPlot;
  QString mName;
  int mIndex;
  QList<NChartLayerable*> mChildren;
  bool mVisible;
  LayerMode mMode;
  
  // non-property members:
  QWeakPointer<NChartAbstractPaintBuffer> mPaintBuffer;
  
  // non-virtual methods:
  void draw(NChartPainter *painter);
  void drawToPaintBuffer();
  void addChild(NChartLayerable *layerable, bool prepend);
  void removeChild(NChartLayerable *layerable);
  
private:
  Q_DISABLE_COPY(NChartLayer)
  
  friend class NChartControl;
  friend class NChartLayerable;
};
Q_DECLARE_METATYPE(NChartLayer::LayerMode)

class NCHART_LIB_DECL NChartLayerable : public QObject
{
  Q_OBJECT
  /// \cond INCLUDE_QPROPERTIES
  Q_PROPERTY(bool visible READ visible WRITE setVisible)
  Q_PROPERTY(NChartControl* parentPlot READ parentPlot)
  Q_PROPERTY(NChartLayerable* parentLayerable READ parentLayerable)
  Q_PROPERTY(NChartLayer* layer READ layer WRITE setLayer NOTIFY layerChanged)
  Q_PROPERTY(bool antialiased READ antialiased WRITE setAntialiased)
  /// \endcond
public:
  NChartLayerable(NChartControl *plot, QString targetLayer=QString(), NChartLayerable *parentLayerable=nullptr);
  virtual ~NChartLayerable();
  
  // getters:
  bool visible() const { return mVisible; }
  NChartControl *parentPlot() const { return mParentPlot; }
  NChartLayerable *parentLayerable() const { return mParentLayerable.data(); }
  NChartLayer *layer() const { return mLayer; }
  bool antialiased() const { return mAntialiased; }
  
  // setters:
  void setVisible(bool on);
  Q_SLOT bool setLayer(NChartLayer *layer);
  bool setLayer(const QString &layerName);
  void setAntialiased(bool enabled);
  
  // introduced virtual methods:
  virtual double selectTest(const QPointF &pos, bool onlySelectable, QVariant *details=nullptr) const;

  // non-property methods:
  bool realVisibility() const;
  
signals:
  void layerChanged(NChartLayer *newLayer);
  
protected:
  // property members:
  bool mVisible;
  NChartControl *mParentPlot;
  QPointer<NChartLayerable> mParentLayerable;
  NChartLayer *mLayer;
  bool mAntialiased;
  
  // introduced virtual methods:
  virtual void parentPlotInitialized(NChartControl *parentPlot);
  virtual NChart::Interaction selectionCategory() const;
  virtual QRect clipRect() const;
  virtual void applyDefaultAntialiasingHint(NChartPainter *painter) const = 0;
  virtual void draw(NChartPainter *painter) = 0;
  // selection events:
  virtual void selectEvent(QMouseEvent *event, bool additive, const QVariant &details, bool *selectionStateChanged);
  virtual void deselectEvent(bool *selectionStateChanged);
  // low-level mouse events:
  virtual void mousePressEvent(QMouseEvent *event, const QVariant &details);
  virtual void mouseMoveEvent(QMouseEvent *event, const QPointF &startPos);
  virtual void mouseReleaseEvent(QMouseEvent *event, const QPointF &startPos);
  virtual void mouseDoubleClickEvent(QMouseEvent *event, const QVariant &details);
  virtual void wheelEvent(QWheelEvent *event);
  
  // non-property methods:
  void initializeParentPlot(NChartControl *parentPlot);
  void setParentLayerable(NChartLayerable* parentLayerable);
  bool moveToLayer(NChartLayer *layer, bool prepend);
  void applyAntialiasingHint(NChartPainter *painter, bool localAntialiased, NChart::AntialiasedElement overrideElement) const;
  
private:
  Q_DISABLE_COPY(NChartLayerable)
  
  friend class NChartControl;
  friend class NChartLayer;
  friend class NChartAxisRect;
};

/* end of 'src/layer.h' */


/* including file 'src/axis/range.h'       */
/* modified 2021-03-29T02:30:44, size 5280 */

class NCHART_LIB_DECL NChartRange
{
public:
  double lower, upper;
  
  NChartRange();
  NChartRange(double lower, double upper);
  
  bool operator==(const NChartRange& other) const { return lower == other.lower && upper == other.upper; }
  bool operator!=(const NChartRange& other) const { return !(*this == other); }
  
  NChartRange &operator+=(const double& value) { lower+=value; upper+=value; return *this; }
  NChartRange &operator-=(const double& value) { lower-=value; upper-=value; return *this; }
  NChartRange &operator*=(const double& value) { lower*=value; upper*=value; return *this; }
  NChartRange &operator/=(const double& value) { lower/=value; upper/=value; return *this; }
  friend inline const NChartRange operator+(const NChartRange&, double);
  friend inline const NChartRange operator+(double, const NChartRange&);
  friend inline const NChartRange operator-(const NChartRange& range, double value);
  friend inline const NChartRange operator*(const NChartRange& range, double value);
  friend inline const NChartRange operator*(double value, const NChartRange& range);
  friend inline const NChartRange operator/(const NChartRange& range, double value);
  
  double size() const { return upper-lower; }
  double center() const { return (upper+lower)*0.5; }
  void normalize() { if (lower > upper) qSwap(lower, upper); }
  void expand(const NChartRange &otherRange);
  void expand(double includeCoord);
  NChartRange expanded(const NChartRange &otherRange) const;
  NChartRange expanded(double includeCoord) const;
  NChartRange bounded(double lowerBound, double upperBound) const;
  NChartRange sanitizedForLogScale() const;
  NChartRange sanitizedForLinScale() const;
  bool contains(double value) const { return value >= lower && value <= upper; }
  
  static bool validRange(double lower, double upper);
  static bool validRange(const NChartRange &range);
  static const double minRange;
  static const double maxRange;
  
};
Q_DECLARE_TYPEINFO(NChartRange, Q_MOVABLE_TYPE);

/*! \relates NChartRange

  Prints \a range in a human readable format to the qDebug output.
*/
inline QDebug operator<< (QDebug d, const NChartRange &range)
{
    d.nospace() << "NChartRange(" << range.lower << ", " << range.upper << ")";
    return d.space();
}

/*!
  Adds \a value to both boundaries of the range.
*/
inline const NChartRange operator+(const NChartRange& range, double value)
{
  NChartRange result(range);
  result += value;
  return result;
}

/*!
  Adds \a value to both boundaries of the range.
*/
inline const NChartRange operator+(double value, const NChartRange& range)
{
  NChartRange result(range);
  result += value;
  return result;
}

/*!
  Subtracts \a value from both boundaries of the range.
*/
inline const NChartRange operator-(const NChartRange& range, double value)
{
  NChartRange result(range);
  result -= value;
  return result;
}

/*!
  Multiplies both boundaries of the range by \a value.
*/
inline const NChartRange operator*(const NChartRange& range, double value)
{
  NChartRange result(range);
  result *= value;
  return result;
}

/*!
  Multiplies both boundaries of the range by \a value.
*/
inline const NChartRange operator*(double value, const NChartRange& range)
{
  NChartRange result(range);
  result *= value;
  return result;
}

/*!
  Divides both boundaries of the range by \a value.
*/
inline const NChartRange operator/(const NChartRange& range, double value)
{
  NChartRange result(range);
  result /= value;
  return result;
}

/* end of 'src/axis/range.h' */


/* including file 'src/selection.h'        */
/* modified 2021-03-29T02:30:44, size 8569 */

class NCHART_LIB_DECL NChartDataRange
{
public:
  NChartDataRange();
  NChartDataRange(int begin, int end);
  
  bool operator==(const NChartDataRange& other) const { return mBegin == other.mBegin && mEnd == other.mEnd; }
  bool operator!=(const NChartDataRange& other) const { return !(*this == other); }
  
  // getters:
  int begin() const { return mBegin; }
  int end() const { return mEnd; }
  int size() const { return mEnd-mBegin; }
  int length() const { return size(); }
  
  // setters:
  void setBegin(int begin) { mBegin = begin; }
  void setEnd(int end)  { mEnd = end; }
  
  // non-property methods:
  bool isValid() const { return (mEnd >= mBegin) && (mBegin >= 0); }
  bool isEmpty() const { return length() == 0; }
  NChartDataRange bounded(const NChartDataRange &other) const;
  NChartDataRange expanded(const NChartDataRange &other) const;
  NChartDataRange intersection(const NChartDataRange &other) const;
  NChartDataRange adjusted(int changeBegin, int changeEnd) const { return NChartDataRange(mBegin+changeBegin, mEnd+changeEnd); }
  bool intersects(const NChartDataRange &other) const;
  bool contains(const NChartDataRange &other) const;
  
private:
  // property members:
  int mBegin, mEnd;

};
Q_DECLARE_TYPEINFO(NChartDataRange, Q_MOVABLE_TYPE);


class NCHART_LIB_DECL NChartDataSelection
{
public:
  explicit NChartDataSelection();
  explicit NChartDataSelection(const NChartDataRange &range);
  
  bool operator==(const NChartDataSelection& other) const;
  bool operator!=(const NChartDataSelection& other) const { return !(*this == other); }
  NChartDataSelection &operator+=(const NChartDataSelection& other);
  NChartDataSelection &operator+=(const NChartDataRange& other);
  NChartDataSelection &operator-=(const NChartDataSelection& other);
  NChartDataSelection &operator-=(const NChartDataRange& other);
  friend inline const NChartDataSelection operator+(const NChartDataSelection& a, const NChartDataSelection& b);
  friend inline const NChartDataSelection operator+(const NChartDataRange& a, const NChartDataSelection& b);
  friend inline const NChartDataSelection operator+(const NChartDataSelection& a, const NChartDataRange& b);
  friend inline const NChartDataSelection operator+(const NChartDataRange& a, const NChartDataRange& b);
  friend inline const NChartDataSelection operator-(const NChartDataSelection& a, const NChartDataSelection& b);
  friend inline const NChartDataSelection operator-(const NChartDataRange& a, const NChartDataSelection& b);
  friend inline const NChartDataSelection operator-(const NChartDataSelection& a, const NChartDataRange& b);
  friend inline const NChartDataSelection operator-(const NChartDataRange& a, const NChartDataRange& b);
  
  // getters:
  int dataRangeCount() const { return mDataRanges.size(); }
  int dataPointCount() const;
  NChartDataRange dataRange(int index=0) const;
  QList<NChartDataRange> dataRanges() const { return mDataRanges; }
  NChartDataRange span() const;
  
  // non-property methods:
  void addDataRange(const NChartDataRange &dataRange, bool simplify=true);
  void clear();
  bool isEmpty() const { return mDataRanges.isEmpty(); }
  void simplify();
  void enforceType(NChart::SelectionType type);
  bool contains(const NChartDataSelection &other) const;
  NChartDataSelection intersection(const NChartDataRange &other) const;
  NChartDataSelection intersection(const NChartDataSelection &other) const;
  NChartDataSelection inverse(const NChartDataRange &outerRange) const;
  
private:
  // property members:
  QList<NChartDataRange> mDataRanges;
  
  inline static bool lessThanDataRangeBegin(const NChartDataRange &a, const NChartDataRange &b) { return a.begin() < b.begin(); }
};
Q_DECLARE_METATYPE(NChartDataSelection)


/*!
  Return a \ref NChartDataSelection with the data points in \a a joined with the data points in \a b.
  The resulting data selection is already simplified (see \ref NChartDataSelection::simplify).
*/
inline const NChartDataSelection operator+(const NChartDataSelection& a, const NChartDataSelection& b)
{
  NChartDataSelection result(a);
  result += b;
  return result;
}

/*!
  Return a \ref NChartDataSelection with the data points in \a a joined with the data points in \a b.
  The resulting data selection is already simplified (see \ref NChartDataSelection::simplify).
*/
inline const NChartDataSelection operator+(const NChartDataRange& a, const NChartDataSelection& b)
{
  NChartDataSelection result(a);
  result += b;
  return result;
}

/*!
  Return a \ref NChartDataSelection with the data points in \a a joined with the data points in \a b.
  The resulting data selection is already simplified (see \ref NChartDataSelection::simplify).
*/
inline const NChartDataSelection operator+(const NChartDataSelection& a, const NChartDataRange& b)
{
  NChartDataSelection result(a);
  result += b;
  return result;
}

/*!
  Return a \ref NChartDataSelection with the data points in \a a joined with the data points in \a b.
  The resulting data selection is already simplified (see \ref NChartDataSelection::simplify).
*/
inline const NChartDataSelection operator+(const NChartDataRange& a, const NChartDataRange& b)
{
  NChartDataSelection result(a);
  result += b;
  return result;
}

/*!
  Return a \ref NChartDataSelection with the data points which are in \a a but not in \a b.
*/
inline const NChartDataSelection operator-(const NChartDataSelection& a, const NChartDataSelection& b)
{
  NChartDataSelection result(a);
  result -= b;
  return result;
}

/*!
  Return a \ref NChartDataSelection with the data points which are in \a a but not in \a b.
*/
inline const NChartDataSelection operator-(const NChartDataRange& a, const NChartDataSelection& b)
{
  NChartDataSelection result(a);
  result -= b;
  return result;
}

/*!
  Return a \ref NChartDataSelection with the data points which are in \a a but not in \a b.
*/
inline const NChartDataSelection operator-(const NChartDataSelection& a, const NChartDataRange& b)
{
  NChartDataSelection result(a);
  result -= b;
  return result;
}

/*!
  Return a \ref NChartDataSelection with the data points which are in \a a but not in \a b.
*/
inline const NChartDataSelection operator-(const NChartDataRange& a, const NChartDataRange& b)
{
  NChartDataSelection result(a);
  result -= b;
  return result;
}

/*! \relates NChartDataRange

  Prints \a dataRange in a human readable format to the qDebug output.
*/
inline QDebug operator<< (QDebug d, const NChartDataRange &dataRange)
{
  d.nospace() << "NChartDataRange(" << dataRange.begin() << ", " << dataRange.end() << ")";
  return d;
}

/*! \relates NChartDataSelection

  Prints \a selection in a human readable format to the qDebug output.
*/
inline QDebug operator<< (QDebug d, const NChartDataSelection &selection)
{
    d.nospace() << "NChartDataSelection(";
    for (int i=0; i<selection.dataRangeCount(); ++i)
    {
      if (i != 0)
        d << ", ";
      d << selection.dataRange(i);
    }
    d << ")";
    return d;
}



/* end of 'src/selection.h' */


/* including file 'src/selectionrect.h'    */
/* modified 2021-03-29T02:30:44, size 3354 */

class NCHART_LIB_DECL NChartSelectionRect : public NChartLayerable
{
  Q_OBJECT
public:
  explicit NChartSelectionRect(NChartControl *parentPlot);
  virtual ~NChartSelectionRect() Q_DECL_OVERRIDE;
  
  // getters:
  QRect rect() const { return mRect; }
  NChartRange range(const NChartAxis *axis) const;
  QPen pen() const { return mPen; }
  QBrush brush() const { return mBrush; }
  bool isActive() const { return mActive; }
  
  // setters:
  void setPen(const QPen &pen);
  void setBrush(const QBrush &brush);
  
  // non-property methods:
  Q_SLOT void cancel();
  
signals:
  void started(QMouseEvent *event);
  void changed(const QRect &rect, QMouseEvent *event);
  void canceled(const QRect &rect, QInputEvent *event);
  void accepted(const QRect &rect, QMouseEvent *event);
  
protected:
  // property members:
  QRect mRect;
  QPen mPen;
  QBrush mBrush;
  // non-property members:
  bool mActive;
  
  // introduced virtual methods:
  virtual void startSelection(QMouseEvent *event);
  virtual void moveSelection(QMouseEvent *event);
  virtual void endSelection(QMouseEvent *event);
  virtual void keyPressEvent(QKeyEvent *event);
  
  // reimplemented virtual methods
  virtual void applyDefaultAntialiasingHint(NChartPainter *painter) const Q_DECL_OVERRIDE;
  virtual void draw(NChartPainter *painter) Q_DECL_OVERRIDE;
  
  friend class NChartControl;
};

/* end of 'src/selectionrect.h' */


/* including file 'src/layout.h'            */
/* modified 2021-03-29T02:30:44, size 14279 */

class NCHART_LIB_DECL NChartMarginGroup : public QObject
{
  Q_OBJECT
public:
  explicit NChartMarginGroup(NChartControl *parentPlot);
  virtual ~NChartMarginGroup();
  
  // non-virtual methods:
  QList<NChartLayoutElement*> elements(NChart::MarginSide side) const { return mChildren.value(side); }
  bool isEmpty() const;
  void clear();
  
protected:
  // non-property members:
  NChartControl *mParentPlot;
  QHash<NChart::MarginSide, QList<NChartLayoutElement*> > mChildren;
  
  // introduced virtual methods:
  virtual int commonMargin(NChart::MarginSide side) const;
  
  // non-virtual methods:
  void addChild(NChart::MarginSide side, NChartLayoutElement *element);
  void removeChild(NChart::MarginSide side, NChartLayoutElement *element);
  
private:
  Q_DISABLE_COPY(NChartMarginGroup)
  
  friend class NChartLayoutElement;
};


class NCHART_LIB_DECL NChartLayoutElement : public NChartLayerable
{
  Q_OBJECT
  /// \cond INCLUDE_QPROPERTIES
  Q_PROPERTY(NChartLayout* layout READ layout)
  Q_PROPERTY(QRect rect READ rect)
  Q_PROPERTY(QRect outerRect READ outerRect WRITE setOuterRect)
  Q_PROPERTY(QMargins margins READ margins WRITE setMargins)
  Q_PROPERTY(QMargins minimumMargins READ minimumMargins WRITE setMinimumMargins)
  Q_PROPERTY(QSize minimumSize READ minimumSize WRITE setMinimumSize)
  Q_PROPERTY(QSize maximumSize READ maximumSize WRITE setMaximumSize)
  Q_PROPERTY(SizeConstraintRect sizeConstraintRect READ sizeConstraintRect WRITE setSizeConstraintRect)
  /// \endcond
public:
  /*!
    Defines the phases of the update process, that happens just before a replot. At each phase,
    \ref update is called with the according UpdatePhase value.
  */
  enum UpdatePhase { upPreparation ///< Phase used for any type of preparation that needs to be done before margin calculation and layout
                     ,upMargins    ///< Phase in which the margins are calculated and set
                     ,upLayout     ///< Final phase in which the layout system places the rects of the elements
                   };
  Q_ENUMS(UpdatePhase)
  
  /*!
    Defines to which rect of a layout element the size constraints that can be set via \ref
    setMinimumSize and \ref setMaximumSize apply. The outer rect (\ref outerRect) includes the
    margins (e.g. in the case of a NChartAxisRect the axis labels), whereas the inner rect (\ref rect)
    does not.
    
    \see setSizeConstraintRect
  */
  enum SizeConstraintRect { scrInnerRect ///< Minimum/Maximum size constraints apply to inner rect
                            , scrOuterRect ///< Minimum/Maximum size constraints apply to outer rect, thus include layout element margins
                          };
  Q_ENUMS(SizeConstraintRect)

  explicit NChartLayoutElement(NChartControl *parentPlot=nullptr);
  virtual ~NChartLayoutElement() Q_DECL_OVERRIDE;
  
  // getters:
  NChartLayout *layout() const { return mParentLayout; }
  QRect rect() const { return mRect; }
  QRect outerRect() const { return mOuterRect; }
  QMargins margins() const { return mMargins; }
  QMargins minimumMargins() const { return mMinimumMargins; }
  NChart::MarginSides autoMargins() const { return mAutoMargins; }
  QSize minimumSize() const { return mMinimumSize; }
  QSize maximumSize() const { return mMaximumSize; }
  SizeConstraintRect sizeConstraintRect() const { return mSizeConstraintRect; }
  NChartMarginGroup *marginGroup(NChart::MarginSide side) const { return mMarginGroups.value(side, nullptr); }
  QHash<NChart::MarginSide, NChartMarginGroup*> marginGroups() const { return mMarginGroups; }
  
  // setters:
  void setOuterRect(const QRect &rect);
  void setMargins(const QMargins &margins);
  void setMinimumMargins(const QMargins &margins);
  void setAutoMargins(NChart::MarginSides sides);
  void setMinimumSize(const QSize &size);
  void setMinimumSize(int width, int height);
  void setMaximumSize(const QSize &size);
  void setMaximumSize(int width, int height);
  void setSizeConstraintRect(SizeConstraintRect constraintRect);
  void setMarginGroup(NChart::MarginSides sides, NChartMarginGroup *group);
  
  // introduced virtual methods:
  virtual void update(UpdatePhase phase);
  virtual QSize minimumOuterSizeHint() const;
  virtual QSize maximumOuterSizeHint() const;
  virtual QList<NChartLayoutElement*> elements(bool recursive) const;
  
  // reimplemented virtual methods:
  virtual double selectTest(const QPointF &pos, bool onlySelectable, QVariant *details=nullptr) const Q_DECL_OVERRIDE;
  
protected:
  // property members:
  NChartLayout *mParentLayout;
  QSize mMinimumSize, mMaximumSize;
  SizeConstraintRect mSizeConstraintRect;
  QRect mRect, mOuterRect;
  QMargins mMargins, mMinimumMargins;
  NChart::MarginSides mAutoMargins;
  QHash<NChart::MarginSide, NChartMarginGroup*> mMarginGroups;
  
  // introduced virtual methods:
  virtual int calculateAutoMargin(NChart::MarginSide side);
  virtual void layoutChanged();
  
  // reimplemented virtual methods:
  virtual void applyDefaultAntialiasingHint(NChartPainter *painter) const Q_DECL_OVERRIDE { Q_UNUSED(painter) }
  virtual void draw(NChartPainter *painter) Q_DECL_OVERRIDE { Q_UNUSED(painter) }
  virtual void parentPlotInitialized(NChartControl *parentPlot) Q_DECL_OVERRIDE;

private:
  Q_DISABLE_COPY(NChartLayoutElement)
  
  friend class NChartControl;
  friend class NChartLayout;
  friend class NChartMarginGroup;
};
Q_DECLARE_METATYPE(NChartLayoutElement::UpdatePhase)


class NCHART_LIB_DECL NChartLayout : public NChartLayoutElement
{
  Q_OBJECT
public:
  explicit NChartLayout();
  
  // reimplemented virtual methods:
  virtual void update(UpdatePhase phase) Q_DECL_OVERRIDE;
  virtual QList<NChartLayoutElement*> elements(bool recursive) const Q_DECL_OVERRIDE;
  
  // introduced virtual methods:
  virtual int elementCount() const = 0;
  virtual NChartLayoutElement* elementAt(int index) const = 0;
  virtual NChartLayoutElement* takeAt(int index) = 0;
  virtual bool take(NChartLayoutElement* element) = 0;
  virtual void simplify();
  
  // non-virtual methods:
  bool removeAt(int index);
  bool remove(NChartLayoutElement* element);
  void clear();
  
protected:
  // introduced virtual methods:
  virtual void updateLayout();
  
  // non-virtual methods:
  void sizeConstraintsChanged() const;
  void adoptElement(NChartLayoutElement *el);
  void releaseElement(NChartLayoutElement *el);
  QVector<int> getSectionSizes(QVector<int> maxSizes, QVector<int> minSizes, QVector<double> stretchFactors, int totalSize) const;
  static QSize getFinalMinimumOuterSize(const NChartLayoutElement *el);
  static QSize getFinalMaximumOuterSize(const NChartLayoutElement *el);
  
private:
  Q_DISABLE_COPY(NChartLayout)
  friend class NChartLayoutElement;
};


class NCHART_LIB_DECL NChartLayoutGrid : public NChartLayout
{
  Q_OBJECT
  /// \cond INCLUDE_QPROPERTIES
  Q_PROPERTY(int rowCount READ rowCount)
  Q_PROPERTY(int columnCount READ columnCount)
  Q_PROPERTY(QList<double> columnStretchFactors READ columnStretchFactors WRITE setColumnStretchFactors)
  Q_PROPERTY(QList<double> rowStretchFactors READ rowStretchFactors WRITE setRowStretchFactors)
  Q_PROPERTY(int columnSpacing READ columnSpacing WRITE setColumnSpacing)
  Q_PROPERTY(int rowSpacing READ rowSpacing WRITE setRowSpacing)
  Q_PROPERTY(FillOrder fillOrder READ fillOrder WRITE setFillOrder)
  Q_PROPERTY(int wrap READ wrap WRITE setWrap)
  /// \endcond
public:
  
  /*!
    Defines in which direction the grid is filled when using \ref addElement(NChartLayoutElement*).
    The column/row at which wrapping into the next row/column occurs can be specified with \ref
    setWrap.

    \see setFillOrder
  */
  enum FillOrder { foRowsFirst    ///< Rows are filled first, and a new element is wrapped to the next column if the row count would exceed \ref setWrap.
                  ,foColumnsFirst ///< Columns are filled first, and a new element is wrapped to the next row if the column count would exceed \ref setWrap.
                };
  Q_ENUMS(FillOrder)
  
  explicit NChartLayoutGrid();
  virtual ~NChartLayoutGrid() Q_DECL_OVERRIDE;
  
  // getters:
  int rowCount() const { return mElements.size(); }
  int columnCount() const { return mElements.size() > 0 ? mElements.first().size() : 0; }
  QList<double> columnStretchFactors() const { return mColumnStretchFactors; }
  QList<double> rowStretchFactors() const { return mRowStretchFactors; }
  int columnSpacing() const { return mColumnSpacing; }
  int rowSpacing() const { return mRowSpacing; }
  int wrap() const { return mWrap; }
  FillOrder fillOrder() const { return mFillOrder; }
  
  // setters:
  void setColumnStretchFactor(int column, double factor);
  void setColumnStretchFactors(const QList<double> &factors);
  void setRowStretchFactor(int row, double factor);
  void setRowStretchFactors(const QList<double> &factors);
  void setColumnSpacing(int pixels);
  void setRowSpacing(int pixels);
  void setWrap(int count);
  void setFillOrder(FillOrder order, bool rearrange=true);
  
  // reimplemented virtual methods:
  virtual void updateLayout() Q_DECL_OVERRIDE;
  virtual int elementCount() const Q_DECL_OVERRIDE { return rowCount()*columnCount(); }
  virtual NChartLayoutElement* elementAt(int index) const Q_DECL_OVERRIDE;
  virtual NChartLayoutElement* takeAt(int index) Q_DECL_OVERRIDE;
  virtual bool take(NChartLayoutElement* element) Q_DECL_OVERRIDE;
  virtual QList<NChartLayoutElement*> elements(bool recursive) const Q_DECL_OVERRIDE;
  virtual void simplify() Q_DECL_OVERRIDE;
  virtual QSize minimumOuterSizeHint() const Q_DECL_OVERRIDE;
  virtual QSize maximumOuterSizeHint() const Q_DECL_OVERRIDE;
  
  // non-virtual methods:
  NChartLayoutElement *element(int row, int column) const;
  bool addElement(int row, int column, NChartLayoutElement *element);
  bool addElement(NChartLayoutElement *element);
  bool hasElement(int row, int column);
  void expandTo(int newRowCount, int newColumnCount);
  void insertRow(int newIndex);
  void insertColumn(int newIndex);
  int rowColToIndex(int row, int column) const;
  void indexToRowCol(int index, int &row, int &column) const;
  
protected:
  // property members:
  QList<QList<NChartLayoutElement*> > mElements;
  QList<double> mColumnStretchFactors;
  QList<double> mRowStretchFactors;
  int mColumnSpacing, mRowSpacing;
  int mWrap;
  FillOrder mFillOrder;
  
  // non-virtual methods:
  void getMinimumRowColSizes(QVector<int> *minColWidths, QVector<int> *minRowHeights) const;
  void getMaximumRowColSizes(QVector<int> *maxColWidths, QVector<int> *maxRowHeights) const;
  
private:
  Q_DISABLE_COPY(NChartLayoutGrid)
};
Q_DECLARE_METATYPE(NChartLayoutGrid::FillOrder)


class NCHART_LIB_DECL NChartLayoutInset : public NChartLayout
{
  Q_OBJECT
public:
  /*!
    Defines how the placement and sizing is handled for a certain element in a NChartLayoutInset.
  */
  enum InsetPlacement { ipFree            ///< The element may be positioned/sized arbitrarily, see \ref setInsetRect
                        ,ipBorderAligned  ///< The element is aligned to one of the layout sides, see \ref setInsetAlignment
                      };
  Q_ENUMS(InsetPlacement)
  
  explicit NChartLayoutInset();
  virtual ~NChartLayoutInset() Q_DECL_OVERRIDE;
  
  // getters:
  InsetPlacement insetPlacement(int index) const;
  Qt::Alignment insetAlignment(int index) const;
  QRectF insetRect(int index) const;
  
  // setters:
  void setInsetPlacement(int index, InsetPlacement placement);
  void setInsetAlignment(int index, Qt::Alignment alignment);
  void setInsetRect(int index, const QRectF &rect);
  
  // reimplemented virtual methods:
  virtual void updateLayout() Q_DECL_OVERRIDE;
  virtual int elementCount() const Q_DECL_OVERRIDE;
  virtual NChartLayoutElement* elementAt(int index) const Q_DECL_OVERRIDE;
  virtual NChartLayoutElement* takeAt(int index) Q_DECL_OVERRIDE;
  virtual bool take(NChartLayoutElement* element) Q_DECL_OVERRIDE;
  virtual void simplify() Q_DECL_OVERRIDE {}
  virtual double selectTest(const QPointF &pos, bool onlySelectable, QVariant *details=nullptr) const Q_DECL_OVERRIDE;
  
  // non-virtual methods:
  void addElement(NChartLayoutElement *element, Qt::Alignment alignment);
  void addElement(NChartLayoutElement *element, const QRectF &rect);
  
protected:
  // property members:
  QList<NChartLayoutElement*> mElements;
  QList<InsetPlacement> mInsetPlacement;
  QList<Qt::Alignment> mInsetAlignment;
  QList<QRectF> mInsetRect;
  
private:
  Q_DISABLE_COPY(NChartLayoutInset)
};
Q_DECLARE_METATYPE(NChartLayoutInset::InsetPlacement)

/* end of 'src/layout.h' */


/* including file 'src/lineending.h'       */
/* modified 2021-03-29T02:30:44, size 4426 */

class NCHART_LIB_DECL NChartLineEnding
{
  Q_GADGET
public:
  /*!
    Defines the type of ending decoration for line-like items, e.g. an arrow.
    
    \image html NChartLineEnding.png
    
    The width and length of these decorations can be controlled with the functions \ref setWidth
    and \ref setLength. Some decorations like \ref esDisc, \ref esSquare, \ref esDiamond and \ref esBar only
    support a width, the length property is ignored.
    
    \see NChartItemLine::setHead, NChartItemLine::setTail, NChartItemCurve::setHead, NChartItemCurve::setTail, NChartAxis::setLowerEnding, NChartAxis::setUpperEnding
  */
  enum EndingStyle { esNone          ///< No ending decoration
                     ,esFlatArrow    ///< A filled arrow head with a straight/flat back (a triangle)
                     ,esSpikeArrow   ///< A filled arrow head with an indented back
                     ,esLineArrow    ///< A non-filled arrow head with open back
                     ,esDisc         ///< A filled circle
                     ,esSquare       ///< A filled square
                     ,esDiamond      ///< A filled diamond (45 degrees rotated square)
                     ,esBar          ///< A bar perpendicular to the line
                     ,esHalfBar      ///< A bar perpendicular to the line, pointing out to only one side (to which side can be changed with \ref setInverted)
                     ,esSkewedBar    ///< A bar that is skewed (skew controllable via \ref setLength)
                   };
  Q_ENUMS(EndingStyle)
  
  NChartLineEnding();
  NChartLineEnding(EndingStyle style, double width=8, double length=10, bool inverted=false);
  
  // getters:
  EndingStyle style() const { return mStyle; }
  double width() const { return mWidth; }
  double length() const { return mLength; }
  bool inverted() const { return mInverted; }
  
  // setters:
  void setStyle(EndingStyle style);
  void setWidth(double width);
  void setLength(double length);
  void setInverted(bool inverted);
  
  // non-property methods:
  double boundingDistance() const;
  double realLength() const;
  void draw(NChartPainter *painter, const NChartVector2D &pos, const NChartVector2D &dir) const;
  void draw(NChartPainter *painter, const NChartVector2D &pos, double angle) const;
  
protected:
  // property members:
  EndingStyle mStyle;
  double mWidth, mLength;
  bool mInverted;
};
Q_DECLARE_TYPEINFO(NChartLineEnding, Q_MOVABLE_TYPE);
Q_DECLARE_METATYPE(NChartLineEnding::EndingStyle)

/* end of 'src/lineending.h' */


/* including file 'src/axis/labelpainter.h' */
/* modified 2021-03-29T02:30:44, size 7086  */

class NChartLabelPainterPrivate
{
  Q_GADGET
public:
  /*!
    TODO
  */
  enum AnchorMode { amRectangular    ///< 
                    ,amSkewedUpright ///<
                    ,amSkewedRotated ///<
                   };
  Q_ENUMS(AnchorMode)
  
  /*!
    TODO
  */
  enum AnchorReferenceType { artNormal    ///< 
                             ,artTangent ///<
                           };
  Q_ENUMS(AnchorReferenceType)
  
  /*!
    TODO
  */
  enum AnchorSide { asLeft      ///< 
                    ,asRight    ///< 
                    ,asTop      ///< 
                    ,asBottom   ///< 
                    ,asTopLeft
                    ,asTopRight
                    ,asBottomRight
                    ,asBottomLeft
                   };
  Q_ENUMS(AnchorSide)
  
  explicit NChartLabelPainterPrivate(NChartControl *parentPlot);
  virtual ~NChartLabelPainterPrivate();
  
  // setters:
  void setAnchorSide(AnchorSide side);
  void setAnchorMode(AnchorMode mode);
  void setAnchorReference(const QPointF &pixelPoint);
  void setAnchorReferenceType(AnchorReferenceType type);
  void setFont(const QFont &font);
  void setColor(const QColor &color);
  void setPadding(int padding);
  void setRotation(double rotation);
  void setSubstituteExponent(bool enabled);
  void setMultiplicationSymbol(QChar symbol);
  void setAbbreviateDecimalPowers(bool enabled);
  void setCacheSize(int labelCount);
  
  // getters:
  AnchorMode anchorMode() const { return mAnchorMode; }
  AnchorSide anchorSide() const { return mAnchorSide; }
  QPointF anchorReference() const { return mAnchorReference; }
  AnchorReferenceType anchorReferenceType() const { return mAnchorReferenceType; }
  QFont font() const { return mFont; }
  QColor color() const { return mColor; }
  int padding() const { return mPadding; }
  double rotation() const { return mRotation; }
  bool substituteExponent() const { return mSubstituteExponent; }
  QChar multiplicationSymbol() const { return mMultiplicationSymbol; }
  bool abbreviateDecimalPowers() const { return mAbbreviateDecimalPowers; }
  int cacheSize() const;
  
  //virtual int size() const;
  
  // non-property methods: 
  void drawTickLabel(NChartPainter *painter, const QPointF &tickPos, const QString &text);
  void clearCache();
  
  // constants that may be used with setMultiplicationSymbol:
  static const QChar SymbolDot;
  static const QChar SymbolCross;
  
protected:
  struct CachedLabel
  {
    QPoint offset;
    QPixmap pixmap;
  };
  struct LabelData
  {
    AnchorSide side;
    double rotation; // angle in degrees
    QTransform transform; // the transform about the label anchor which is at (0, 0). Does not contain final absolute x/y positioning on the plot/axis
    QString basePart, expPart, suffixPart;
    QRect baseBounds, expBounds, suffixBounds;
    QRect totalBounds; // is in a coordinate system where label top left is at (0, 0)
    QRect rotatedTotalBounds; // is in a coordinate system where the label anchor is at (0, 0)
    QFont baseFont, expFont;
    QColor color;
  };
  
  // property members:
  AnchorMode mAnchorMode;
  AnchorSide mAnchorSide;
  QPointF mAnchorReference;
  AnchorReferenceType mAnchorReferenceType;
  QFont mFont;
  QColor mColor;
  int mPadding;
  double mRotation; // this is the rotation applied uniformly to all labels, not the heterogeneous rotation in amCircularRotated mode
  bool mSubstituteExponent;
  QChar mMultiplicationSymbol;
  bool mAbbreviateDecimalPowers;
  // non-property members:
  NChartControl *mParentPlot;
  QByteArray mLabelParameterHash; // to determine whether mLabelCache needs to be cleared due to changed parameters
  QCache<QString, CachedLabel> mLabelCache;
  QRect mAxisSelectionBox, mTickLabelsSelectionBox, mLabelSelectionBox;
  int mLetterCapHeight, mLetterDescent;
  
  // introduced virtual methods:
  virtual void drawLabelMaybeCached(NChartPainter *painter, const QFont &font, const QColor &color, const QPointF &pos, AnchorSide side, double rotation, const QString &text);
  virtual QByteArray generateLabelParameterHash() const; // TODO: get rid of this in favor of invalidation flag upon setters?

  // non-virtual methods:
  QPointF getAnchorPos(const QPointF &tickPos);
  void drawText(NChartPainter *painter, const QPointF &pos, const LabelData &labelData) const;
  LabelData getTickLabelData(const QFont &font, const QColor &color, double rotation, AnchorSide side, const QString &text) const;
  void applyAnchorTransform(LabelData &labelData) const;
  //void getMaxTickLabelSize(const QFont &font, const QString &text, QSize *tickLabelsSize) const;
  CachedLabel *createCachedLabel(const LabelData &labelData) const;
  QByteArray cacheKey(const QString &text, const QColor &color, double rotation, AnchorSide side) const;
  AnchorSide skewedAnchorSide(const QPointF &tickPos, double sideExpandHorz, double sideExpandVert) const;
  AnchorSide rotationCorrectedSide(AnchorSide side, double rotation) const;
  void analyzeFontMetrics();
};
Q_DECLARE_METATYPE(NChartLabelPainterPrivate::AnchorMode)
Q_DECLARE_METATYPE(NChartLabelPainterPrivate::AnchorSide)


/* end of 'src/axis/labelpainter.h' */


/* including file 'src/axis/axisticker.h'  */
/* modified 2021-03-29T02:30:44, size 4230 */

class NCHART_LIB_DECL NChartAxisTicker
{
  Q_GADGET
public:
  /*!
    Defines the strategies that the axis ticker may follow when choosing the size of the tick step.
    
    \see setTickStepStrategy
  */
  enum TickStepStrategy
  {
    tssReadability    ///< A nicely readable tick step is prioritized over matching the requested number of ticks (see \ref setTickCount)
    ,tssMeetTickCount ///< Less readable tick steps are allowed which in turn facilitates getting closer to the requested tick count
  };
  Q_ENUMS(TickStepStrategy)
  
  NChartAxisTicker();
  virtual ~NChartAxisTicker();
  
  // getters:
  TickStepStrategy tickStepStrategy() const { return mTickStepStrategy; }
  int tickCount() const { return mTickCount; }
  double tickOrigin() const { return mTickOrigin; }
  
  // setters:
  void setTickStepStrategy(TickStepStrategy strategy);
  void setTickCount(int count);
  void setTickOrigin(double origin);
  
  // introduced virtual methods:
  virtual void generate(int scaleType, const NChartRange &range, const QLocale &locale, QChar formatChar, int precision, QVector<double> &ticks, QVector<double> *subTicks, QVector<QString> *tickLabels);
  
protected:
  // property members:
  TickStepStrategy mTickStepStrategy;
  int mTickCount;
  double mTickOrigin;
  
  // introduced virtual methods:
  virtual double getTickStep(const NChartRange &range);
  virtual int getSubTickCount(double tickStep);
  virtual QString getTickLabel(double tick, const QLocale &locale, QChar formatChar, int precision);
  virtual QVector<double> createTickVector(double tickStep, const NChartRange &range);
  virtual QVector<double> createSubTickVector(int subTickCount, const QVector<double> &ticks);
  virtual QVector<QString> createLabelVector(int scaleType, const QVector<double> &ticks, const QLocale &locale, QChar formatChar, int precision);
  
  // non-virtual methods:
  void trimTicks(const NChartRange &range, QVector<double> &ticks, bool keepOneOutlier) const;
  double pickClosest(double target, const QVector<double> &candidates) const;
  double getMantissa(double input, double *magnitude=nullptr) const;
  double cleanMantissa(double input) const;
  
private:
  Q_DISABLE_COPY(NChartAxisTicker)
  
};
Q_DECLARE_METATYPE(NChartAxisTicker::TickStepStrategy)
Q_DECLARE_METATYPE(QSharedPointer<NChartAxisTicker>)

/* end of 'src/axis/axisticker.h' */


/* including file 'src/axis/axistickerdatetime.h' */
/* modified 2021-03-29T02:30:44, size 3600        */

class NCHART_LIB_DECL NChartAxisTickerDateTime : public NChartAxisTicker
{
public:
  NChartAxisTickerDateTime();
  
  // getters:
  QString dateTimeFormat() const { return mDateTimeFormat; }
  Qt::TimeSpec dateTimeSpec() const { return mDateTimeSpec; }
# if QT_VERSION >= QT_VERSION_CHECK(5, 2, 0)
  QTimeZone timeZone() const { return mTimeZone; }
#endif
  
  // setters:
  void setDateTimeFormat(const QString &format);
  void setDateTimeSpec(Qt::TimeSpec spec);
# if QT_VERSION >= QT_VERSION_CHECK(5, 2, 0)
  void setTimeZone(const QTimeZone &zone);
# endif
  void setTickOrigin(double origin); // hides base class method but calls baseclass implementation ("using" throws off IDEs and doxygen)
  void setTickOrigin(const QDateTime &origin);
  
  // static methods:
  static QDateTime keyToDateTime(double key);
  static double dateTimeToKey(const QDateTime &dateTime);
  static double dateTimeToKey(const QDate &date, Qt::TimeSpec timeSpec=Qt::LocalTime);
  
protected:
  // property members:
  QString mDateTimeFormat;
  Qt::TimeSpec mDateTimeSpec;
# if QT_VERSION >= QT_VERSION_CHECK(5, 2, 0)
  QTimeZone mTimeZone;
# endif
  // non-property members:
  enum DateStrategy {dsNone, dsUniformTimeInDay, dsUniformDayInMonth} mDateStrategy;
  
  // reimplemented virtual methods:
  virtual double getTickStep(const NChartRange &range) Q_DECL_OVERRIDE;
  virtual int getSubTickCount(double tickStep) Q_DECL_OVERRIDE;
  virtual QString getTickLabel(double tick, const QLocale &locale, QChar formatChar, int precision) Q_DECL_OVERRIDE;
  virtual QVector<double> createTickVector(double tickStep, const NChartRange &range) Q_DECL_OVERRIDE;
};

/* end of 'src/axis/axistickerdatetime.h' */


/* including file 'src/axis/axistickertime.h' */
/* modified 2021-03-29T02:30:44, size 3542    */

class NCHART_LIB_DECL NChartAxisTickerTime : public NChartAxisTicker
{
  Q_GADGET
public:
  /*!
    Defines the logical units in which fractions of time spans can be expressed.
    
    \see setFieldWidth, setTimeFormat
  */
  enum TimeUnit { tuMilliseconds ///< Milliseconds, one thousandth of a second (%%z in \ref setTimeFormat)
                  ,tuSeconds     ///< Seconds (%%s in \ref setTimeFormat)
                  ,tuMinutes     ///< Minutes (%%m in \ref setTimeFormat)
                  ,tuHours       ///< Hours (%%h in \ref setTimeFormat)
                  ,tuDays        ///< Days (%%d in \ref setTimeFormat)
                };
  Q_ENUMS(TimeUnit)
  
  NChartAxisTickerTime();

  // getters:
  QString timeFormat() const { return mTimeFormat; }
  int fieldWidth(TimeUnit unit) const { return mFieldWidth.value(unit); }
  
  // setters:
  void setTimeFormat(const QString &format);
  void setFieldWidth(TimeUnit unit, int width);
  
protected:
  // property members:
  QString mTimeFormat;
  QHash<TimeUnit, int> mFieldWidth;
  
  // non-property members:
  TimeUnit mSmallestUnit, mBiggestUnit;
  QHash<TimeUnit, QString> mFormatPattern;
  
  // reimplemented virtual methods:
  virtual double getTickStep(const NChartRange &range) Q_DECL_OVERRIDE;
  virtual int getSubTickCount(double tickStep) Q_DECL_OVERRIDE;
  virtual QString getTickLabel(double tick, const QLocale &locale, QChar formatChar, int precision) Q_DECL_OVERRIDE;
  
  // non-virtual methods:
  void replaceUnit(QString &text, TimeUnit unit, int value) const;
};
Q_DECLARE_METATYPE(NChartAxisTickerTime::TimeUnit)

/* end of 'src/axis/axistickertime.h' */


/* including file 'src/axis/axistickerfixed.h' */
/* modified 2021-03-29T02:30:44, size 3308     */

class NCHART_LIB_DECL NChartAxisTickerFixed : public NChartAxisTicker
{
  Q_GADGET
public:
  /*!
    Defines how the axis ticker may modify the specified tick step (\ref setTickStep) in order to
    control the number of ticks in the axis range.
    
    \see setScaleStrategy
  */
  enum ScaleStrategy { ssNone      ///< Modifications are not allowed, the specified tick step is absolutely fixed. This might cause a high tick density and overlapping labels if the axis range is zoomed out.
                       ,ssMultiples ///< An integer multiple of the specified tick step is allowed. The used factor follows the base class properties of \ref setTickStepStrategy and \ref setTickCount.
                       ,ssPowers    ///< An integer power of the specified tick step is allowed.
                     };
  Q_ENUMS(ScaleStrategy)
  
  NChartAxisTickerFixed();
  
  // getters:
  double tickStep() const { return mTickStep; }
  ScaleStrategy scaleStrategy() const { return mScaleStrategy; }
  
  // setters:
  void setTickStep(double step);
  void setScaleStrategy(ScaleStrategy strategy);
  
protected:
  // property members:
  double mTickStep;
  ScaleStrategy mScaleStrategy;
  
  // reimplemented virtual methods:
  virtual double getTickStep(const NChartRange &range) Q_DECL_OVERRIDE;
};
Q_DECLARE_METATYPE(NChartAxisTickerFixed::ScaleStrategy)

/* end of 'src/axis/axistickerfixed.h' */


/* including file 'src/axis/axistickertext.h' */
/* modified 2021-03-29T02:30:44, size 3090    */

class NCHART_LIB_DECL NChartAxisTickerText : public NChartAxisTicker
{
public:
  NChartAxisTickerText();
  
  // getters:
  QMap<double, QString> &ticks() { return mTicks; }
  int subTickCount() const { return mSubTickCount; }
  
  // setters:
  void setTicks(const QMap<double, QString> &ticks);
  void setTicks(const QVector<double> &positions, const QVector<QString> &labels);
  void setSubTickCount(int subTicks);
  
  // non-virtual methods:
  void clear();
  void addTick(double position, const QString &label);
  void addTicks(const QMap<double, QString> &ticks);
  void addTicks(const QVector<double> &positions, const QVector<QString> &labels);
  
protected:
  // property members:
  QMap<double, QString> mTicks;
  int mSubTickCount;
  
  // reimplemented virtual methods:
  virtual double getTickStep(const NChartRange &range) Q_DECL_OVERRIDE;
  virtual int getSubTickCount(double tickStep) Q_DECL_OVERRIDE;
  virtual QString getTickLabel(double tick, const QLocale &locale, QChar formatChar, int precision) Q_DECL_OVERRIDE;
  virtual QVector<double> createTickVector(double tickStep, const NChartRange &range) Q_DECL_OVERRIDE;
};

/* end of 'src/axis/axistickertext.h' */


/* including file 'src/axis/axistickerpi.h' */
/* modified 2021-03-29T02:30:44, size 3911  */

class NCHART_LIB_DECL NChartAxisTickerPi : public NChartAxisTicker
{
  Q_GADGET
public:
  /*!
    Defines how fractions should be displayed in tick labels.
    
    \see setFractionStyle
  */
  enum FractionStyle { fsFloatingPoint     ///< Fractions are displayed as regular decimal floating point numbers, e.g. "0.25" or "0.125".
                       ,fsAsciiFractions   ///< Fractions are written as rationals using ASCII characters only, e.g. "1/4" or "1/8"
                       ,fsUnicodeFractions ///< Fractions are written using sub- and superscript UTF-8 digits and the fraction symbol.
                     };
  Q_ENUMS(FractionStyle)
  
  NChartAxisTickerPi();
  
  // getters:
  QString piSymbol() const { return mPiSymbol; }
  double piValue() const { return mPiValue; }
  bool periodicity() const { return mPeriodicity; }
  FractionStyle fractionStyle() const { return mFractionStyle; }
  
  // setters:
  void setPiSymbol(QString symbol);
  void setPiValue(double pi);
  void setPeriodicity(int multiplesOfPi);
  void setFractionStyle(FractionStyle style);
  
protected:
  // property members:
  QString mPiSymbol;
  double mPiValue;
  int mPeriodicity;
  FractionStyle mFractionStyle;
  
  // non-property members:
  double mPiTickStep; // size of one tick step in units of mPiValue
  
  // reimplemented virtual methods:
  virtual double getTickStep(const NChartRange &range) Q_DECL_OVERRIDE;
  virtual int getSubTickCount(double tickStep) Q_DECL_OVERRIDE;
  virtual QString getTickLabel(double tick, const QLocale &locale, QChar formatChar, int precision) Q_DECL_OVERRIDE;
  
  // non-virtual methods:
  void simplifyFraction(int &numerator, int &denominator) const;
  QString fractionToString(int numerator, int denominator) const;
  QString unicodeFraction(int numerator, int denominator) const;
  QString unicodeSuperscript(int number) const;
  QString unicodeSubscript(int number) const;
};
Q_DECLARE_METATYPE(NChartAxisTickerPi::FractionStyle)

/* end of 'src/axis/axistickerpi.h' */


/* including file 'src/axis/axistickerlog.h' */
/* modified 2021-03-29T02:30:44, size 2594   */

class NCHART_LIB_DECL NChartAxisTickerLog : public NChartAxisTicker
{
public:
  NChartAxisTickerLog();
  
  // getters:
  double logBase() const { return mLogBase; }
  int subTickCount() const { return mSubTickCount; }
  
  // setters:
  void setLogBase(double base);
  void setSubTickCount(int subTicks);
  
protected:
  // property members:
  double mLogBase;
  int mSubTickCount;
  
  // non-property members:
  double mLogBaseLnInv;
  
  // reimplemented virtual methods:
  virtual int getSubTickCount(double tickStep) Q_DECL_OVERRIDE;
  virtual QVector<double> createTickVector(double tickStep, const NChartRange &range) Q_DECL_OVERRIDE;
};

/* end of 'src/axis/axistickerlog.h' */


/* including file 'src/axis/axis.h'         */
/* modified 2021-03-29T02:30:44, size 20913 */

class NCHART_LIB_DECL NChartGrid :public NChartLayerable
{
  Q_OBJECT
  /// \cond INCLUDE_QPROPERTIES
  Q_PROPERTY(bool subGridVisible READ subGridVisible WRITE setSubGridVisible)
  Q_PROPERTY(bool antialiasedSubGrid READ antialiasedSubGrid WRITE setAntialiasedSubGrid)
  Q_PROPERTY(bool antialiasedZeroLine READ antialiasedZeroLine WRITE setAntialiasedZeroLine)
  Q_PROPERTY(QPen pen READ pen WRITE setPen)
  Q_PROPERTY(QPen subGridPen READ subGridPen WRITE setSubGridPen)
  Q_PROPERTY(QPen zeroLinePen READ zeroLinePen WRITE setZeroLinePen)
  /// \endcond
public:
  explicit NChartGrid(NChartAxis *parentAxis);
  
  // getters:
  bool subGridVisible() const { return mSubGridVisible; }
  bool antialiasedSubGrid() const { return mAntialiasedSubGrid; }
  bool antialiasedZeroLine() const { return mAntialiasedZeroLine; }
  QPen pen() const { return mPen; }
  QPen subGridPen() const { return mSubGridPen; }
  QPen zeroLinePen() const { return mZeroLinePen; }
  
  // setters:
  void setSubGridVisible(bool visible);
  void setAntialiasedSubGrid(bool enabled);
  void setAntialiasedZeroLine(bool enabled);
  void setPen(const QPen &pen);
  void setSubGridPen(const QPen &pen);
  void setZeroLinePen(const QPen &pen);
  
protected:
  // property members:
  bool mSubGridVisible;
  bool mAntialiasedSubGrid, mAntialiasedZeroLine;
  QPen mPen, mSubGridPen, mZeroLinePen;
  
  // non-property members:
  NChartAxis *mParentAxis;
  
  // reimplemented virtual methods:
  virtual void applyDefaultAntialiasingHint(NChartPainter *painter) const Q_DECL_OVERRIDE;
  virtual void draw(NChartPainter *painter) Q_DECL_OVERRIDE;
  
  // non-virtual methods:
  void drawGridLines(NChartPainter *painter) const;
  void drawSubGridLines(NChartPainter *painter) const;
  
  friend class NChartAxis;
};


class NCHART_LIB_DECL NChartAxis : public NChartLayerable
{
  Q_OBJECT
  /// \cond INCLUDE_QPROPERTIES
  Q_PROPERTY(AxisType axisType READ axisType)
  Q_PROPERTY(NChartAxisRect* axisRect READ axisRect)
  Q_PROPERTY(ScaleType scaleType READ scaleType WRITE setScaleType NOTIFY scaleTypeChanged)
  Q_PROPERTY(NChartRange range READ range WRITE setRange NOTIFY rangeChanged)
  Q_PROPERTY(bool rangeReversed READ rangeReversed WRITE setRangeReversed)
  Q_PROPERTY(QSharedPointer<NChartAxisTicker> ticker READ ticker WRITE setTicker)
  Q_PROPERTY(bool ticks READ ticks WRITE setTicks)
  Q_PROPERTY(bool tickLabels READ tickLabels WRITE setTickLabels)
  Q_PROPERTY(int tickLabelPadding READ tickLabelPadding WRITE setTickLabelPadding)
  Q_PROPERTY(QFont tickLabelFont READ tickLabelFont WRITE setTickLabelFont)
  Q_PROPERTY(QColor tickLabelColor READ tickLabelColor WRITE setTickLabelColor)
  Q_PROPERTY(double tickLabelRotation READ tickLabelRotation WRITE setTickLabelRotation)
  Q_PROPERTY(LabelSide tickLabelSide READ tickLabelSide WRITE setTickLabelSide)
  Q_PROPERTY(QString numberFormat READ numberFormat WRITE setNumberFormat)
  Q_PROPERTY(int numberPrecision READ numberPrecision WRITE setNumberPrecision)
  Q_PROPERTY(QVector<double> tickVector READ tickVector)
  Q_PROPERTY(QVector<QString> tickVectorLabels READ tickVectorLabels)
  Q_PROPERTY(int tickLengthIn READ tickLengthIn WRITE setTickLengthIn)
  Q_PROPERTY(int tickLengthOut READ tickLengthOut WRITE setTickLengthOut)
  Q_PROPERTY(bool subTicks READ subTicks WRITE setSubTicks)
  Q_PROPERTY(int subTickLengthIn READ subTickLengthIn WRITE setSubTickLengthIn)
  Q_PROPERTY(int subTickLengthOut READ subTickLengthOut WRITE setSubTickLengthOut)
  Q_PROPERTY(QPen basePen READ basePen WRITE setBasePen)
  Q_PROPERTY(QPen tickPen READ tickPen WRITE setTickPen)
  Q_PROPERTY(QPen subTickPen READ subTickPen WRITE setSubTickPen)
  Q_PROPERTY(QFont labelFont READ labelFont WRITE setLabelFont)
  Q_PROPERTY(QColor labelColor READ labelColor WRITE setLabelColor)
  Q_PROPERTY(QString label READ label WRITE setLabel)
  Q_PROPERTY(int labelPadding READ labelPadding WRITE setLabelPadding)
  Q_PROPERTY(int padding READ padding WRITE setPadding)
  Q_PROPERTY(int offset READ offset WRITE setOffset)
  Q_PROPERTY(SelectableParts selectedParts READ selectedParts WRITE setSelectedParts NOTIFY selectionChanged)
  Q_PROPERTY(SelectableParts selectableParts READ selectableParts WRITE setSelectableParts NOTIFY selectableChanged)
  Q_PROPERTY(QFont selectedTickLabelFont READ selectedTickLabelFont WRITE setSelectedTickLabelFont)
  Q_PROPERTY(QFont selectedLabelFont READ selectedLabelFont WRITE setSelectedLabelFont)
  Q_PROPERTY(QColor selectedTickLabelColor READ selectedTickLabelColor WRITE setSelectedTickLabelColor)
  Q_PROPERTY(QColor selectedLabelColor READ selectedLabelColor WRITE setSelectedLabelColor)
  Q_PROPERTY(QPen selectedBasePen READ selectedBasePen WRITE setSelectedBasePen)
  Q_PROPERTY(QPen selectedTickPen READ selectedTickPen WRITE setSelectedTickPen)
  Q_PROPERTY(QPen selectedSubTickPen READ selectedSubTickPen WRITE setSelectedSubTickPen)
  Q_PROPERTY(NChartLineEnding lowerEnding READ lowerEnding WRITE setLowerEnding)
  Q_PROPERTY(NChartLineEnding upperEnding READ upperEnding WRITE setUpperEnding)
  Q_PROPERTY(NChartGrid* grid READ grid)
  /// \endcond
public:
  /*!
    Defines at which side of the axis rect the axis will appear. This also affects how the tick
    marks are drawn, on which side the labels are placed etc.
  */
  enum AxisType { atLeft    = 0x01  ///< <tt>0x01</tt> Axis is vertical and on the left side of the axis rect
                  ,atRight  = 0x02  ///< <tt>0x02</tt> Axis is vertical and on the right side of the axis rect
                  ,atTop    = 0x04  ///< <tt>0x04</tt> Axis is horizontal and on the top side of the axis rect
                  ,atBottom = 0x08  ///< <tt>0x08</tt> Axis is horizontal and on the bottom side of the axis rect
                };
  Q_ENUMS(AxisType)
  Q_FLAGS(AxisTypes)
  Q_DECLARE_FLAGS(AxisTypes, AxisType)
  /*!
    Defines on which side of the axis the tick labels (numbers) shall appear.
    
    \see setTickLabelSide
  */
  enum LabelSide { lsInside    ///< Tick labels will be displayed inside the axis rect and clipped to the inner axis rect
                   ,lsOutside  ///< Tick labels will be displayed outside the axis rect
                 };
  Q_ENUMS(LabelSide)
  /*!
    Defines the scale of an axis.
    \see setScaleType
  */
  enum ScaleType { stLinear       ///< Linear scaling
                   ,stLogarithmic ///< Logarithmic scaling with correspondingly transformed axis coordinates (possibly also \ref setTicker to a \ref NChartAxisTickerLog instance).
                 };
  Q_ENUMS(ScaleType)
  /*!
    Defines the selectable parts of an axis.
    \see setSelectableParts, setSelectedParts
  */
  enum SelectablePart { spNone        = 0      ///< None of the selectable parts
                        ,spAxis       = 0x001  ///< The axis backbone and tick marks
                        ,spTickLabels = 0x002  ///< Tick labels (numbers) of this axis (as a whole, not individually)
                        ,spAxisLabel  = 0x004  ///< The axis label
                      };
  Q_ENUMS(SelectablePart)
  Q_FLAGS(SelectableParts)
  Q_DECLARE_FLAGS(SelectableParts, SelectablePart)
  
  explicit NChartAxis(NChartAxisRect *parent, AxisType type);
  virtual ~NChartAxis() Q_DECL_OVERRIDE;
  
  // getters:
  AxisType axisType() const { return mAxisType; }
  NChartAxisRect *axisRect() const { return mAxisRect; }
  ScaleType scaleType() const { return mScaleType; }
  bool onlyVisibleStartEnd() const { return mOnlyVisibleStartEnd; }
  const NChartRange range() const { return mRange; }
  bool rangeReversed() const { return mRangeReversed; }
  QSharedPointer<NChartAxisTicker> ticker() const { return mTicker; }
  bool ticks() const { return mTicks; }
  bool tickLabels() const { return mTickLabels; }
  int tickLabelPadding() const;
  QFont tickLabelFont() const { return mTickLabelFont; }
  QColor tickLabelColor() const { return mTickLabelColor; }
  double tickLabelRotation() const;
  LabelSide tickLabelSide() const;
  QString numberFormat() const;
  int numberPrecision() const { return mNumberPrecision; }
  QVector<double> tickVector() const { return mTickVector; }
  QVector<QString> tickVectorLabels() const { return mTickVectorLabels; }
  int tickLengthIn() const;
  int tickLengthOut() const;
  bool subTicks() const { return mSubTicks; }
  int subTickLengthIn() const;
  int subTickLengthOut() const;
  QPen basePen() const { return mBasePen; }
  QPen tickPen() const { return mTickPen; }
  QPen subTickPen() const { return mSubTickPen; }
  QFont labelFont() const { return mLabelFont; }
  QColor labelColor() const { return mLabelColor; }
  QString label() const { return mLabel; }
  int labelPadding() const;
  int padding() const { return mPadding; }
  int offset() const;
  SelectableParts selectedParts() const { return mSelectedParts; }
  SelectableParts selectableParts() const { return mSelectableParts; }
  QFont selectedTickLabelFont() const { return mSelectedTickLabelFont; }
  QFont selectedLabelFont() const { return mSelectedLabelFont; }
  QColor selectedTickLabelColor() const { return mSelectedTickLabelColor; }
  QColor selectedLabelColor() const { return mSelectedLabelColor; }
  QPen selectedBasePen() const { return mSelectedBasePen; }
  QPen selectedTickPen() const { return mSelectedTickPen; }
  QPen selectedSubTickPen() const { return mSelectedSubTickPen; }
  NChartLineEnding lowerEnding() const;
  NChartLineEnding upperEnding() const;
  NChartGrid *grid() const { return mGrid; }
  
  // setters:
  Q_SLOT void setScaleType(NChartAxis::ScaleType type);
  Q_SLOT void setRange(const NChartRange &range);
  void setOnlyVisibleStartEnd(bool value);
  void setRange(double lower, double upper);
  void setRange(double position, double size, Qt::AlignmentFlag alignment);
  void setRangeLower(double lower);
  void setRangeUpper(double upper);
  void setRangeReversed(bool reversed);
  void setTicker(QSharedPointer<NChartAxisTicker> ticker);
  void setTicks(bool show);
  void setTickLabels(bool show);
  void setTickLabelPadding(int padding);
  void setTickLabelFont(const QFont &font);
  void setTickLabelColor(const QColor &color);
  void setTickLabelRotation(double degrees);
  void setTickLabelSide(LabelSide side);
  void setNumberFormat(const QString &formatCode);
  void setNumberPrecision(int precision);
  void setTickLength(int inside, int outside=0);
  void setTickLengthIn(int inside);
  void setTickLengthOut(int outside);
  void setSubTicks(bool show);
  void setSubTickLength(int inside, int outside=0);
  void setSubTickLengthIn(int inside);
  void setSubTickLengthOut(int outside);
  void setBasePen(const QPen &pen);
  void setTickPen(const QPen &pen);
  void setSubTickPen(const QPen &pen);
  void setLabelFont(const QFont &font);
  void setLabelColor(const QColor &color);
  void setLabel(const QString &str);
  void setLabelPadding(int padding);
  void setPadding(int padding);
  void setOffset(int offset);
  void setSelectedTickLabelFont(const QFont &font);
  void setSelectedLabelFont(const QFont &font);
  void setSelectedTickLabelColor(const QColor &color);
  void setSelectedLabelColor(const QColor &color);
  void setSelectedBasePen(const QPen &pen);
  void setSelectedTickPen(const QPen &pen);
  void setSelectedSubTickPen(const QPen &pen);
  Q_SLOT void setSelectableParts(const NChartAxis::SelectableParts &selectableParts);
  Q_SLOT void setSelectedParts(const NChartAxis::SelectableParts &selectedParts);
  void setLowerEnding(const NChartLineEnding &ending);
  void setUpperEnding(const NChartLineEnding &ending);
  
  // reimplemented virtual methods:
  virtual double selectTest(const QPointF &pos, bool onlySelectable, QVariant *details=nullptr) const Q_DECL_OVERRIDE;
  
  // non-property methods:
  Qt::Orientation orientation() const { return mOrientation; }
  int pixelOrientation() const { return rangeReversed() != (orientation()==Qt::Vertical) ? -1 : 1; }
  void moveRange(double diff);
  void scaleRange(double factor);
  void scaleRange(double factor, double center);
  void setScaleRatio(const NChartAxis *otherAxis, double ratio=1.0);
  void rescale(bool onlyVisiblePlottables=false);
  double pixelToCoord(double value) const;
  double coordToPixel(double value) const;
  SelectablePart getPartAt(const QPointF &pos) const;
  QList<NChartAbstractPlottable*> plottables() const;
  QList<NChartGraph*> graphs() const;
  QList<NChartAbstractItem*> items() const;
  
  static AxisType marginSideToAxisType(NChart::MarginSide side);
  static Qt::Orientation orientation(AxisType type) { return type==atBottom || type==atTop ? Qt::Horizontal : Qt::Vertical; }
  static AxisType opposite(AxisType type);
  
signals:
  void rangeChanged(const NChartRange &newRange);
  void rangeChanged(const NChartRange &newRange, const NChartRange &oldRange);
  void scaleTypeChanged(NChartAxis::ScaleType scaleType);
  void selectionChanged(const NChartAxis::SelectableParts &parts);
  void selectableChanged(const NChartAxis::SelectableParts &parts);

protected:
  // property members:
  // axis base:
  AxisType mAxisType;
  NChartAxisRect *mAxisRect;
  //int mOffset; // in NChartAxisPainter
  int mPadding;
  Qt::Orientation mOrientation;
  SelectableParts mSelectableParts, mSelectedParts;
  QPen mBasePen, mSelectedBasePen;
  //NChartLineEnding mLowerEnding, mUpperEnding; // in NChartAxisPainter
  // axis label:
  //int mLabelPadding; // in NChartAxisPainter
  QString mLabel;
  QFont mLabelFont, mSelectedLabelFont;
  QColor mLabelColor, mSelectedLabelColor;
  // tick labels:
  //int mTickLabelPadding; // in NChartAxisPainter
  bool mTickLabels;
  //double mTickLabelRotation; // in NChartAxisPainter
  QFont mTickLabelFont, mSelectedTickLabelFont;
  QColor mTickLabelColor, mSelectedTickLabelColor;
  int mNumberPrecision;
  QLatin1Char mNumberFormatChar;
  bool mNumberBeautifulPowers;
  //bool mNumberMultiplyCross; // NChartAxisPainter
  // ticks and subticks:
  bool mTicks;
  bool mSubTicks;
  //int mTickLengthIn, mTickLengthOut, mSubTickLengthIn, mSubTickLengthOut; // NChartAxisPainter
  QPen mTickPen, mSelectedTickPen;
  QPen mSubTickPen, mSelectedSubTickPen;
  // scale and range:
  bool mOnlyVisibleStartEnd;
  NChartRange mRange;
  bool mRangeReversed;
  ScaleType mScaleType;
  
  // non-property members:
  NChartGrid *mGrid;
  NChartAxisPainterPrivate *mAxisPainter;
  QSharedPointer<NChartAxisTicker> mTicker;
  QVector<double> mTickVector;
  QVector<QString> mTickVectorLabels;
  QVector<double> mSubTickVector;
  bool mCachedMarginValid;
  int mCachedMargin;
  bool mDragging;
  NChartRange mDragStartRange;
  NChart::AntialiasedElements mAADragBackup, mNotAADragBackup;
  
  // introduced virtual methods:
  virtual int calculateMargin();
  
  // reimplemented virtual methods:
  virtual void applyDefaultAntialiasingHint(NChartPainter *painter) const Q_DECL_OVERRIDE;
  virtual void draw(NChartPainter *painter) Q_DECL_OVERRIDE;
  virtual NChart::Interaction selectionCategory() const Q_DECL_OVERRIDE;
  // events:
  virtual void selectEvent(QMouseEvent *event, bool additive, const QVariant &details, bool *selectionStateChanged) Q_DECL_OVERRIDE;
  virtual void deselectEvent(bool *selectionStateChanged) Q_DECL_OVERRIDE;
  // mouse events:
  virtual void mousePressEvent(QMouseEvent *event, const QVariant &details) Q_DECL_OVERRIDE;
  virtual void mouseMoveEvent(QMouseEvent *event, const QPointF &startPos) Q_DECL_OVERRIDE;
  virtual void mouseReleaseEvent(QMouseEvent *event, const QPointF &startPos) Q_DECL_OVERRIDE;
  virtual void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;
  
  // non-virtual methods:
  void setupTickVectors();
  QPen getBasePen() const;
  QPen getTickPen() const;
  QPen getSubTickPen() const;
  QFont getTickLabelFont() const;
  QFont getLabelFont() const;
  QColor getTickLabelColor() const;
  QColor getLabelColor() const;
  
private:
  Q_DISABLE_COPY(NChartAxis)
  
  friend class NChartControl;
  friend class NChartGrid;
  friend class NChartAxisRect;
};
Q_DECLARE_OPERATORS_FOR_FLAGS(NChartAxis::SelectableParts)
Q_DECLARE_OPERATORS_FOR_FLAGS(NChartAxis::AxisTypes)
Q_DECLARE_METATYPE(NChartAxis::AxisType)
Q_DECLARE_METATYPE(NChartAxis::LabelSide)
Q_DECLARE_METATYPE(NChartAxis::ScaleType)
Q_DECLARE_METATYPE(NChartAxis::SelectablePart)


class NChartAxisPainterPrivate
{
public:
  explicit NChartAxisPainterPrivate(NChartControl *parentPlot);
  virtual ~NChartAxisPainterPrivate();
  
  virtual void draw(NChartPainter *painter);
  virtual int size();
  void clearCache();
  
  QRect axisSelectionBox() const { return mAxisSelectionBox; }
  QRect tickLabelsSelectionBox() const { return mTickLabelsSelectionBox; }
  QRect labelSelectionBox() const { return mLabelSelectionBox; }
  
  // public property members:
  bool onlyVisibleStartEnd;
  NChartAxis::AxisType type;
  QPen basePen;
  NChartLineEnding lowerEnding, upperEnding; // directly accessed by NChartAxis setters/getters
  int labelPadding; // directly accessed by NChartAxis setters/getters
  QFont labelFont;
  QColor labelColor;
  QString label;
  int tickLabelPadding; // directly accessed by NChartAxis setters/getters
  double tickLabelRotation; // directly accessed by NChartAxis setters/getters
  NChartAxis::LabelSide tickLabelSide; // directly accessed by NChartAxis setters/getters
  bool substituteExponent;
  bool numberMultiplyCross; // directly accessed by NChartAxis setters/getters
  int tickLengthIn, tickLengthOut, subTickLengthIn, subTickLengthOut; // directly accessed by NChartAxis setters/getters
  QPen tickPen, subTickPen;
  QFont tickLabelFont;
  QColor tickLabelColor;
  QRect axisRect, viewportRect;
  int offset; // directly accessed by NChartAxis setters/getters
  bool abbreviateDecimalPowers;
  bool reversedEndings;
  
  QVector<double> subTickPositions;
  QVector<double> tickPositions;
  QVector<QString> tickLabels;
  
protected:
  struct CachedLabel
  {
    QPointF offset;
    QPixmap pixmap;
  };
  struct TickLabelData
  {
    QString basePart, expPart, suffixPart;
    QRect baseBounds, expBounds, suffixBounds, totalBounds, rotatedTotalBounds;
    QFont baseFont, expFont;
  };
  NChartControl *mParentPlot;
  QByteArray mLabelParameterHash; // to determine whether mLabelCache needs to be cleared due to changed parameters
  QCache<QString, CachedLabel> mLabelCache;
  QRect mAxisSelectionBox, mTickLabelsSelectionBox, mLabelSelectionBox;
  
  virtual QByteArray generateLabelParameterHash() const;
  
  virtual void placeTickLabelShiftX(NChartPainter *painter, double position, int distanceToAxis, const QString &text, QSize *tickLabelsSize, bool isRightShift);
  virtual void placeTickLabel(NChartPainter *painter, double position, int distanceToAxis, const QString &text, QSize *tickLabelsSize, bool isEssentialLabel, double startPosition, double endPosition);
  virtual void drawTickLabel(NChartPainter *painter, double x, double y, const TickLabelData &labelData) const;
  virtual TickLabelData getTickLabelData(const QFont &font, const QString &text) const;
  virtual QPointF getTickLabelDrawOffset(const TickLabelData &labelData) const;
  virtual void getMaxTickLabelSize(const QFont &font, const QString &text, QSize *tickLabelsSize) const;
};

/* end of 'src/axis/axis.h' */


/* including file 'src/scatterstyle.h'     */
/* modified 2021-03-29T02:30:44, size 7275 */

class NCHART_LIB_DECL NChartScatterStyle
{
  Q_GADGET
public:
  /*!
    Represents the various properties of a scatter style instance. For example, this enum is used
    to specify which properties of \ref NChartSelectionDecorator::setScatterStyle will be used when
    highlighting selected data points.

    Specific scatter properties can be transferred between \ref NChartScatterStyle instances via \ref
    setFromOther.
  */
  enum ScatterProperty { spNone  = 0x00  ///< <tt>0x00</tt> None
                         ,spPen   = 0x01  ///< <tt>0x01</tt> The pen property, see \ref setPen
                         ,spBrush = 0x02  ///< <tt>0x02</tt> The brush property, see \ref setBrush
                         ,spSize  = 0x04  ///< <tt>0x04</tt> The size property, see \ref setSize
                         ,spShape = 0x08  ///< <tt>0x08</tt> The shape property, see \ref setShape
                         ,spAll   = 0xFF  ///< <tt>0xFF</tt> All properties
                       };
  Q_ENUMS(ScatterProperty)
  Q_FLAGS(ScatterProperties)
  Q_DECLARE_FLAGS(ScatterProperties, ScatterProperty)

  /*!
    Defines the shape used for scatter points.

    On plottables/items that draw scatters, the sizes of these visualizations (with exception of
    \ref ssDot and \ref ssPixmap) can be controlled with the \ref setSize function. Scatters are
    drawn with the pen and brush specified with \ref setPen and \ref setBrush.
  */
  enum ScatterShape { ssNone       ///< no scatter symbols are drawn (e.g. in NChartGraph, data only represented with lines)
                      ,ssDot       ///< \enumimage{ssDot.png} a single pixel (use \ref ssDisc or \ref ssCircle if you want a round shape with a certain radius)
                      ,ssCross     ///< \enumimage{ssCross.png} a cross
                      ,ssPlus      ///< \enumimage{ssPlus.png} a plus
                      ,ssCircle    ///< \enumimage{ssCircle.png} a circle
                      ,ssDisc      ///< \enumimage{ssDisc.png} a circle which is filled with the pen's color (not the brush as with ssCircle)
                      ,ssSquare    ///< \enumimage{ssSquare.png} a square
                      ,ssDiamond   ///< \enumimage{ssDiamond.png} a diamond
                      ,ssStar      ///< \enumimage{ssStar.png} a star with eight arms, i.e. a combination of cross and plus
                      ,ssTriangle  ///< \enumimage{ssTriangle.png} an equilateral triangle, standing on baseline
                      ,ssTriangleInverted ///< \enumimage{ssTriangleInverted.png} an equilateral triangle, standing on corner
                      ,ssCrossSquare      ///< \enumimage{ssCrossSquare.png} a square with a cross inside
                      ,ssPlusSquare       ///< \enumimage{ssPlusSquare.png} a square with a plus inside
                      ,ssCrossCircle      ///< \enumimage{ssCrossCircle.png} a circle with a cross inside
                      ,ssPlusCircle       ///< \enumimage{ssPlusCircle.png} a circle with a plus inside
                      ,ssPeace     ///< \enumimage{ssPeace.png} a circle, with one vertical and two downward diagonal lines
                      ,ssPixmap    ///< a custom pixmap specified by \ref setPixmap, centered on the data point coordinates
                      ,ssCustom    ///< custom painter operations are performed per scatter (As QPainterPath, see \ref setCustomPath)
                    };
  Q_ENUMS(ScatterShape)

  NChartScatterStyle();
  NChartScatterStyle(ScatterShape shape, double size=6);
  NChartScatterStyle(ScatterShape shape, const QColor &color, double size);
  NChartScatterStyle(ScatterShape shape, const QColor &color, const QColor &fill, double size);
  NChartScatterStyle(ScatterShape shape, const QPen &pen, const QBrush &brush, double size);
  NChartScatterStyle(const QPixmap &pixmap);
  NChartScatterStyle(const QPainterPath &customPath, const QPen &pen, const QBrush &brush=Qt::NoBrush, double size=6);
  
  // getters:
  double size() const { return mSize; }
  ScatterShape shape() const { return mShape; }
  QPen pen() const { return mPen; }
  QBrush brush() const { return mBrush; }
  QPixmap pixmap() const { return mPixmap; }
  QPainterPath customPath() const { return mCustomPath; }

  // setters:
  void setFromOther(const NChartScatterStyle &other, ScatterProperties properties);
  void setSize(double size);
  void setShape(ScatterShape shape);
  void setPen(const QPen &pen);
  void setBrush(const QBrush &brush);
  void setPixmap(const QPixmap &pixmap);
  void setCustomPath(const QPainterPath &customPath);

  // non-property methods:
  bool isNone() const { return mShape == ssNone; }
  bool isPenDefined() const { return mPenDefined; }
  void undefinePen();
  void applyTo(NChartPainter *painter, const QPen &defaultPen) const;
  void drawShape(NChartPainter *painter, const QPointF &pos) const;
  void drawShape(NChartPainter *painter, double x, double y) const;

protected:
  // property members:
  double mSize;
  ScatterShape mShape;
  QPen mPen;
  QBrush mBrush;
  QPixmap mPixmap;
  QPainterPath mCustomPath;
  
  // non-property members:
  bool mPenDefined;
};
Q_DECLARE_TYPEINFO(NChartScatterStyle, Q_MOVABLE_TYPE);
Q_DECLARE_OPERATORS_FOR_FLAGS(NChartScatterStyle::ScatterProperties)
Q_DECLARE_METATYPE(NChartScatterStyle::ScatterProperty)
Q_DECLARE_METATYPE(NChartScatterStyle::ScatterShape)

/* end of 'src/scatterstyle.h' */


/* including file 'src/datacontainer.h'     */
/* modified 2021-03-29T02:30:44, size 34070 */

/*! \relates NChartDataContainer
  Returns whether the sort key of \a a is less than the sort key of \a b.

  \see NChartDataContainer::sort
*/
template <class DataType>
inline bool qcpLessThanSortKey(const DataType &a, const DataType &b) { return a.sortKey() < b.sortKey(); }

template <class DataType>
class NChartDataContainer // no NCHART_LIB_DECL, template class ends up in header (cpp included below)
{
public:
  typedef typename QVector<DataType>::const_iterator const_iterator;
  typedef typename QVector<DataType>::iterator iterator;
  
  NChartDataContainer();
  
  // getters:
  int realSize() const { return mData.size(); }
  int size() const { return mData.size()-mPreallocSize; }
  bool isEmpty() const { return size() == 0; }
  bool autoSqueeze() const { return mAutoSqueeze; }
  
  // setters:
  void setAutoSqueeze(bool enabled);
  
  // non-virtual methods:
  void set(const NChartDataContainer<DataType> &data);
  void set(const QVector<DataType> &data, bool alreadySorted=false);
  void add(const NChartDataContainer<DataType> &data);
  void add(const QVector<DataType> &data, bool alreadySorted=false);
  void add(const DataType &data);
  void removeBefore(double sortKey);
  void removeAfter(double sortKey);
  void remove(double sortKeyFrom, double sortKeyTo);
  void remove(double sortKey);
  void clear();
  void sort();
  void squeeze(bool preAllocation=true, bool postAllocation=true);
  
  const_iterator constBegin() const { return mData.constBegin()+mPreallocSize; }
  const_iterator constEnd() const { return mData.constEnd(); }
  iterator begin() { return mData.begin()+mPreallocSize; }
  iterator end() { return mData.end(); }
  const_iterator findBegin(double sortKey, bool expandedRange=true) const;
  const_iterator findEnd(double sortKey, bool expandedRange=true) const;
  const_iterator at(int index) const { return constBegin()+qBound(0, index, size()); }
  NChartRange keyRange(bool &foundRange, NChart::SignDomain signDomain=NChart::sdBoth);
  NChartRange valueRange(bool &foundRange, NChart::SignDomain signDomain=NChart::sdBoth, const NChartRange &inKeyRange=NChartRange());
  NChartDataRange dataRange() const { return NChartDataRange(0, size()); }
  void limitIteratorsToDataRange(const_iterator &begin, const_iterator &end, const NChartDataRange &dataRange) const;
  
protected:
  // property members:
  bool mAutoSqueeze;
  
  // non-property memebers:
  QVector<DataType> mData;
  int mPreallocSize;
  int mPreallocIteration;
  
  // non-virtual methods:
  void preallocateGrow(int minimumPreallocSize);
  void performAutoSqueeze();
};



// include implementation in header since it is a class template:
////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////// NChartDataContainer
////////////////////////////////////////////////////////////////////////////////////////////////////

/*! \class NChartDataContainer
  \brief The generic data container for one-dimensional plottables

  This class template provides a fast container for data storage of one-dimensional data. The data
  type is specified as template parameter (called \a DataType in the following) and must provide
  some methods as described in the \ref qcpdatacontainer-datatype "next section".

  The data is stored in a sorted fashion, which allows very quick lookups by the sorted key as well
  as retrieval of ranges (see \ref findBegin, \ref findEnd, \ref keyRange) using binary search. The
  container uses a preallocation and a postallocation scheme, such that appending and prepending
  data (with respect to the sort key) is very fast and minimizes reallocations. If data is added
  which needs to be inserted between existing keys, the merge usually can be done quickly too,
  using the fact that existing data is always sorted. The user can further improve performance by
  specifying that added data is already itself sorted by key, if he can guarantee that this is the
  case (see for example \ref add(const QVector<DataType> &data, bool alreadySorted)).

  The data can be accessed with the provided const iterators (\ref constBegin, \ref constEnd). If
  it is necessary to alter existing data in-place, the non-const iterators can be used (\ref begin,
  \ref end). Changing data members that are not the sort key (for most data types called \a key) is
  safe from the container's perspective.

  Great care must be taken however if the sort key is modified through the non-const iterators. For
  performance reasons, the iterators don't automatically cause a re-sorting upon their
  manipulation. It is thus the responsibility of the user to leave the container in a sorted state
  when finished with the data manipulation, before calling any other methods on the container. A
  complete re-sort (e.g. after finishing all sort key manipulation) can be done by calling \ref
  sort. Failing to do so can not be detected by the container efficiently and will cause both
  rendering artifacts and potential data loss.

  Implementing one-dimensional plottables that make use of a \ref NChartDataContainer<T> is usually
  done by subclassing from \ref NChartAbstractPlottable1D "NChartAbstractPlottable1D<T>", which
  introduces an according \a mDataContainer member and some convenience methods.

  \section qcpdatacontainer-datatype Requirements for the DataType template parameter

  The template parameter <tt>DataType</tt> is the type of the stored data points. It must be
  trivially copyable and have the following public methods, preferably inline:

  \li <tt>double sortKey() const</tt>\n Returns the member variable of this data point that is the
  sort key, defining the ordering in the container. Often this variable is simply called \a key.

  \li <tt>static DataType fromSortKey(double sortKey)</tt>\n Returns a new instance of the data
  type initialized with its sort key set to \a sortKey.

  \li <tt>static bool sortKeyIsMainKey()</tt>\n Returns true if the sort key is equal to the main
  key (see method \c mainKey below). For most plottables this is the case. It is not the case for
  example for \ref NChartCurve, which uses \a t as sort key and \a key as main key. This is the reason
  why NChartCurve unlike NChartGraph can display parametric curves with loops.

  \li <tt>double mainKey() const</tt>\n Returns the variable of this data point considered the main
  key. This is commonly the variable that is used as the coordinate of this data point on the key
  axis of the plottable. This method is used for example when determining the automatic axis
  rescaling of key axes (\ref NChartAxis::rescale).

  \li <tt>double mainValue() const</tt>\n Returns the variable of this data point considered the
  main value. This is commonly the variable that is used as the coordinate of this data point on
  the value axis of the plottable.

  \li <tt>NChartRange valueRange() const</tt>\n Returns the range this data point spans in the value
  axis coordinate. If the data is single-valued (e.g. NChartGraphData), this is simply a range with
  both lower and upper set to the main data point value. However if the data points can represent
  multiple values at once (e.g NChartFinancialData with its \a high, \a low, \a open and \a close
  values at each \a key) this method should return the range those values span. This method is used
  for example when determining the automatic axis rescaling of value axes (\ref
  NChartAxis::rescale).
*/

/* start documentation of inline functions */

/*! \fn int NChartDataContainer<DataType>::size() const
  
  Returns the number of data points in the container.
*/

/*! \fn bool NChartDataContainer<DataType>::isEmpty() const
  
  Returns whether this container holds no data points.
*/

/*! \fn NChartDataContainer::const_iterator NChartDataContainer<DataType>::constBegin() const
  
  Returns a const iterator to the first data point in this container.
*/

/*! \fn NChartDataContainer::const_iterator NChartDataContainer<DataType>::constEnd() const
  
  Returns a const iterator to the element past the last data point in this container.
*/

/*! \fn NChartDataContainer::iterator NChartDataContainer<DataType>::begin() const
  
  Returns a non-const iterator to the first data point in this container.

  You can manipulate the data points in-place through the non-const iterators, but great care must
  be taken when manipulating the sort key of a data point, see \ref sort, or the detailed
  description of this class.
*/

/*! \fn NChartDataContainer::iterator NChartDataContainer<DataType>::end() const
  
  Returns a non-const iterator to the element past the last data point in this container.
  
  You can manipulate the data points in-place through the non-const iterators, but great care must
  be taken when manipulating the sort key of a data point, see \ref sort, or the detailed
  description of this class.
*/

/*! \fn NChartDataContainer::const_iterator NChartDataContainer<DataType>::at(int index) const

  Returns a const iterator to the element with the specified \a index. If \a index points beyond
  the available elements in this container, returns \ref constEnd, i.e. an iterator past the last
  valid element.

  You can use this method to easily obtain iterators from a \ref NChartDataRange, see the \ref
  dataselection-accessing "data selection page" for an example.
*/

/*! \fn NChartDataRange NChartDataContainer::dataRange() const

  Returns a \ref NChartDataRange encompassing the entire data set of this container. This means the
  begin index of the returned range is 0, and the end index is \ref size.
*/

/* end documentation of inline functions */

/*!
  Constructs a NChartDataContainer used for plottable classes that represent a series of key-sorted
  data
*/
template <class DataType>
NChartDataContainer<DataType>::NChartDataContainer() :
  mAutoSqueeze(true),
  mPreallocSize(0),
  mPreallocIteration(0)
{
}

/*!
  Sets whether the container automatically decides when to release memory from its post- and
  preallocation pools when data points are removed. By default this is enabled and for typical
  applications shouldn't be changed.
  
  If auto squeeze is disabled, you can manually decide when to release pre-/postallocation with
  \ref squeeze.
*/
template <class DataType>
void NChartDataContainer<DataType>::setAutoSqueeze(bool enabled)
{
  if (mAutoSqueeze != enabled)
  {
    mAutoSqueeze = enabled;
    if (mAutoSqueeze)
      performAutoSqueeze();
  }
}

/*! \overload
  
  Replaces the current data in this container with the provided \a data.
  
  \see add, remove
*/
template <class DataType>
void NChartDataContainer<DataType>::set(const NChartDataContainer<DataType> &data)
{
  clear();
  add(data);
}

/*! \overload
  
  Replaces the current data in this container with the provided \a data

  If you can guarantee that the data points in \a data have ascending order with respect to the
  DataType's sort key, set \a alreadySorted to true to avoid an unnecessary sorting run.
  
  \see add, remove
*/
template <class DataType>
void NChartDataContainer<DataType>::set(const QVector<DataType> &data, bool alreadySorted)
{
  mData = data;
  mPreallocSize = 0;
  mPreallocIteration = 0;
  if (!alreadySorted)
    sort();
}

/*! \overload
  
  Adds the provided \a data to the current data in this container.
  
  \see set, remove
*/
template <class DataType>
void NChartDataContainer<DataType>::add(const NChartDataContainer<DataType> &data)
{
  if (data.isEmpty())
    return;
  
  const int n = data.size();
  const int oldSize = size();
  
  if (oldSize > 0 && !qcpLessThanSortKey<DataType>(*constBegin(), *(data.constEnd()-1))) // prepend if new data keys are all smaller than or equal to existing ones
  {
    if (mPreallocSize < n)
      preallocateGrow(n);
    mPreallocSize -= n;
    std::copy(data.constBegin(), data.constEnd(), begin());
  } else // don't need to prepend, so append and merge if necessary
  {
    mData.resize(mData.size()+n);
    std::copy(data.constBegin(), data.constEnd(), end()-n);
    if (oldSize > 0 && !qcpLessThanSortKey<DataType>(*(constEnd()-n-1), *(constEnd()-n))) // if appended range keys aren't all greater than existing ones, merge the two partitions
      std::inplace_merge(begin(), end()-n, end(), qcpLessThanSortKey<DataType>);
  }
}

/*!
  Adds the provided data points in \a data to the current data.
  
  If you can guarantee that the data points in \a data have ascending order with respect to the
  DataType's sort key, set \a alreadySorted to true to avoid an unnecessary sorting run.
  
  \see set, remove
*/
template <class DataType>
void NChartDataContainer<DataType>::add(const QVector<DataType> &data, bool alreadySorted)
{
  if (data.isEmpty())
    return;
  if (isEmpty())
  {
    set(data, alreadySorted);
    return;
  }
  
  const int n = data.size();
  const int oldSize = size();
  
  if (alreadySorted && oldSize > 0 && !qcpLessThanSortKey<DataType>(*constBegin(), *(data.constEnd()-1))) // prepend if new data is sorted and keys are all smaller than or equal to existing ones
  {
    if (mPreallocSize < n)
      preallocateGrow(n);
    mPreallocSize -= n;
    std::copy(data.constBegin(), data.constEnd(), begin());
  } else // don't need to prepend, so append and then sort and merge if necessary
  {
    mData.resize(mData.size()+n);
    std::copy(data.constBegin(), data.constEnd(), end()-n);
    if (!alreadySorted) // sort appended subrange if it wasn't already sorted
      std::sort(end()-n, end(), qcpLessThanSortKey<DataType>);
    if (oldSize > 0 && !qcpLessThanSortKey<DataType>(*(constEnd()-n-1), *(constEnd()-n))) // if appended range keys aren't all greater than existing ones, merge the two partitions
      std::inplace_merge(begin(), end()-n, end(), qcpLessThanSortKey<DataType>);
  }
}

/*! \overload
  
  Adds the provided single data point to the current data.
  
  \see remove
*/
template <class DataType>
void NChartDataContainer<DataType>::add(const DataType &data)
{
  if (isEmpty() || !qcpLessThanSortKey<DataType>(data, *(constEnd()-1))) // quickly handle appends if new data key is greater or equal to existing ones
  {
    mData.append(data);
  } else if (qcpLessThanSortKey<DataType>(data, *constBegin()))  // quickly handle prepends using preallocated space
  {
    if (mPreallocSize < 1)
      preallocateGrow(1);
    --mPreallocSize;
    *begin() = data;
  } else // handle inserts, maintaining sorted keys
  {
    NChartDataContainer<DataType>::iterator insertionPoint = std::lower_bound(begin(), end(), data, qcpLessThanSortKey<DataType>);
    mData.insert(insertionPoint, data);
  }
}

/*!
  Removes all data points with (sort-)keys smaller than or equal to \a sortKey.
  
  \see removeAfter, remove, clear
*/
template <class DataType>
void NChartDataContainer<DataType>::removeBefore(double sortKey)
{
  NChartDataContainer<DataType>::iterator it = begin();
  NChartDataContainer<DataType>::iterator itEnd = std::lower_bound(begin(), end(), DataType::fromSortKey(sortKey), qcpLessThanSortKey<DataType>);
  mPreallocSize += int(itEnd-it); // don't actually delete, just add it to the preallocated block (if it gets too large, squeeze will take care of it)
  if (mAutoSqueeze)
    performAutoSqueeze();
}

/*!
  Removes all data points with (sort-)keys greater than or equal to \a sortKey.

  \see removeBefore, remove, clear
*/
template <class DataType>
void NChartDataContainer<DataType>::removeAfter(double sortKey)
{
  NChartDataContainer<DataType>::iterator it = std::upper_bound(begin(), end(), DataType::fromSortKey(sortKey), qcpLessThanSortKey<DataType>);
  NChartDataContainer<DataType>::iterator itEnd = end();
  mData.erase(it, itEnd); // typically adds it to the postallocated block
  if (mAutoSqueeze)
    performAutoSqueeze();
}

/*!
  Removes all data points with (sort-)keys between \a sortKeyFrom and \a sortKeyTo. if \a
  sortKeyFrom is greater or equal to \a sortKeyTo, the function does nothing. To remove a single
  data point with known (sort-)key, use \ref remove(double sortKey).
  
  \see removeBefore, removeAfter, clear
*/
template <class DataType>
void NChartDataContainer<DataType>::remove(double sortKeyFrom, double sortKeyTo)
{
  if (sortKeyFrom >= sortKeyTo || isEmpty())
    return;
  
  NChartDataContainer<DataType>::iterator it = std::lower_bound(begin(), end(), DataType::fromSortKey(sortKeyFrom), qcpLessThanSortKey<DataType>);
  NChartDataContainer<DataType>::iterator itEnd = std::upper_bound(it, end(), DataType::fromSortKey(sortKeyTo), qcpLessThanSortKey<DataType>);
  mData.erase(it, itEnd);
  if (mAutoSqueeze)
    performAutoSqueeze();
}

/*! \overload
  
  Removes a single data point at \a sortKey. If the position is not known with absolute (binary)
  precision, consider using \ref remove(double sortKeyFrom, double sortKeyTo) with a small
  fuzziness interval around the suspected position, depeding on the precision with which the
  (sort-)key is known.
  
  \see removeBefore, removeAfter, clear
*/
template <class DataType>
void NChartDataContainer<DataType>::remove(double sortKey)
{
  NChartDataContainer::iterator it = std::lower_bound(begin(), end(), DataType::fromSortKey(sortKey), qcpLessThanSortKey<DataType>);
  if (it != end() && it->sortKey() == sortKey)
  {
    if (it == begin())
      ++mPreallocSize; // don't actually delete, just add it to the preallocated block (if it gets too large, squeeze will take care of it)
    else
      mData.erase(it);
  }
  if (mAutoSqueeze)
    performAutoSqueeze();
}

/*!
  Removes all data points.
  
  \see remove, removeAfter, removeBefore
*/
template <class DataType>
void NChartDataContainer<DataType>::clear()
{
  mData.clear();
  mPreallocIteration = 0;
  mPreallocSize = 0;
}

/*!
  Re-sorts all data points in the container by their sort key.

  When setting, adding or removing points using the NChartDataContainer interface (\ref set, \ref add,
  \ref remove, etc.), the container makes sure to always stay in a sorted state such that a full
  resort is never necessary. However, if you choose to directly manipulate the sort key on data
  points by accessing and modifying it through the non-const iterators (\ref begin, \ref end), it
  is your responsibility to bring the container back into a sorted state before any other methods
  are called on it. This can be achieved by calling this method immediately after finishing the
  sort key manipulation.
*/
template <class DataType>
void NChartDataContainer<DataType>::sort()
{
  std::sort(begin(), end(), qcpLessThanSortKey<DataType>);
}

/*!
  Frees all unused memory that is currently in the preallocation and postallocation pools.
  
  Note that NChartDataContainer automatically decides whether squeezing is necessary, if \ref
  setAutoSqueeze is left enabled. It should thus not be necessary to use this method for typical
  applications.
  
  The parameters \a preAllocation and \a postAllocation control whether pre- and/or post allocation
  should be freed, respectively.
*/
template <class DataType>
void NChartDataContainer<DataType>::squeeze(bool preAllocation, bool postAllocation)
{
  if (preAllocation)
  {
    if (mPreallocSize > 0)
    {
      std::copy(begin(), end(), mData.begin());
      mData.resize(size());
      mPreallocSize = 0;
    }
    mPreallocIteration = 0;
  }
  if (postAllocation)
    mData.squeeze();
}

/*!
  Returns an iterator to the data point with a (sort-)key that is equal to, just below, or just
  above \a sortKey. If \a expandedRange is true, the data point just below \a sortKey will be
  considered, otherwise the one just above.

  This can be used in conjunction with \ref findEnd to iterate over data points within a given key
  range, including or excluding the bounding data points that are just beyond the specified range.

  If \a expandedRange is true but there are no data points below \a sortKey, \ref constBegin is
  returned.

  If the container is empty, returns \ref constEnd.

  \see findEnd, NChartPlottableInterface1D::findBegin
*/
template <class DataType>
typename NChartDataContainer<DataType>::const_iterator NChartDataContainer<DataType>::findBegin(double sortKey, bool expandedRange) const
{
  if (isEmpty())
    return constEnd();
  
  NChartDataContainer<DataType>::const_iterator it = std::lower_bound(constBegin(), constEnd(), DataType::fromSortKey(sortKey), qcpLessThanSortKey<DataType>);
  if (expandedRange && it != constBegin()) // also covers it == constEnd case, and we know --constEnd is valid because mData isn't empty
    --it;
  return it;
}

/*!
  Returns an iterator to the element after the data point with a (sort-)key that is equal to, just
  above or just below \a sortKey. If \a expandedRange is true, the data point just above \a sortKey
  will be considered, otherwise the one just below.

  This can be used in conjunction with \ref findBegin to iterate over data points within a given
  key range, including the bounding data points that are just below and above the specified range.

  If \a expandedRange is true but there are no data points above \a sortKey, \ref constEnd is
  returned.

  If the container is empty, \ref constEnd is returned.

  \see findBegin, NChartPlottableInterface1D::findEnd
*/
template <class DataType>
typename NChartDataContainer<DataType>::const_iterator NChartDataContainer<DataType>::findEnd(double sortKey, bool expandedRange) const
{
  if (isEmpty())
    return constEnd();
  
  NChartDataContainer<DataType>::const_iterator it = std::upper_bound(constBegin(), constEnd(), DataType::fromSortKey(sortKey), qcpLessThanSortKey<DataType>);
  if (expandedRange && it != constEnd())
    ++it;
  return it;
}

/*!
  Returns the range encompassed by the (main-)key coordinate of all data points. The output
  parameter \a foundRange indicates whether a sensible range was found. If this is false, you
  should not use the returned NChartRange (e.g. the data container is empty or all points have the
  same key).
  
  Use \a signDomain to control which sign of the key coordinates should be considered. This is
  relevant e.g. for logarithmic plots which can mathematically only display one sign domain at a
  time.
  
  If the DataType reports that its main key is equal to the sort key (\a sortKeyIsMainKey), as is
  the case for most plottables, this method uses this fact and finds the range very quickly.
  
  \see valueRange
*/
template <class DataType>
NChartRange NChartDataContainer<DataType>::keyRange(bool &foundRange, NChart::SignDomain signDomain)
{
  if (isEmpty())
  {
    foundRange = false;
    return NChartRange();
  }
  NChartRange range;
  bool haveLower = false;
  bool haveUpper = false;
  double current;
  
  NChartDataContainer<DataType>::const_iterator it = constBegin();
  NChartDataContainer<DataType>::const_iterator itEnd = constEnd();
  if (signDomain == NChart::sdBoth) // range may be anywhere
  {
    if (DataType::sortKeyIsMainKey()) // if DataType is sorted by main key (e.g. NChartGraph, but not NChartCurve), use faster algorithm by finding just first and last key with non-NaN value
    {
      while (it != itEnd) // find first non-nan going up from left
      {
        if (!qIsNaN(it->mainValue()))
        {
          range.lower = it->mainKey();
          haveLower = true;
          break;
        }
        ++it;
      }
      it = itEnd;
      while (it != constBegin()) // find first non-nan going down from right
      {
        --it;
        if (!qIsNaN(it->mainValue()))
        {
          range.upper = it->mainKey();
          haveUpper = true;
          break;
        }
      }
    } else // DataType is not sorted by main key, go through all data points and accordingly expand range
    {
      while (it != itEnd)
      {
        if (!qIsNaN(it->mainValue()))
        {
          current = it->mainKey();
          if (current < range.lower || !haveLower)
          {
            range.lower = current;
            haveLower = true;
          }
          if (current > range.upper || !haveUpper)
          {
            range.upper = current;
            haveUpper = true;
          }
        }
        ++it;
      }
    }
  } else if (signDomain == NChart::sdNegative) // range may only be in the negative sign domain
  {
    while (it != itEnd)
    {
      if (!qIsNaN(it->mainValue()))
      {
        current = it->mainKey();
        if ((current < range.lower || !haveLower) && current < 0)
        {
          range.lower = current;
          haveLower = true;
        }
        if ((current > range.upper || !haveUpper) && current < 0)
        {
          range.upper = current;
          haveUpper = true;
        }
      }
      ++it;
    }
  } else if (signDomain == NChart::sdPositive) // range may only be in the positive sign domain
  {
    while (it != itEnd)
    {
      if (!qIsNaN(it->mainValue()))
      {
        current = it->mainKey();
        if ((current < range.lower || !haveLower) && current > 0)
        {
          range.lower = current;
          haveLower = true;
        }
        if ((current > range.upper || !haveUpper) && current > 0)
        {
          range.upper = current;
          haveUpper = true;
        }
      }
      ++it;
    }
  }
  
  foundRange = haveLower && haveUpper;
  return range;
}

/*!
  Returns the range encompassed by the value coordinates of the data points in the specified key
  range (\a inKeyRange), using the full \a DataType::valueRange reported by the data points. The
  output parameter \a foundRange indicates whether a sensible range was found. If this is false,
  you should not use the returned NChartRange (e.g. the data container is empty or all points have the
  same value).

  If \a inKeyRange has both lower and upper bound set to zero (is equal to <tt>NChartRange()</tt>),
  all data points are considered, without any restriction on the keys.

  Use \a signDomain to control which sign of the value coordinates should be considered. This is
  relevant e.g. for logarithmic plots which can mathematically only display one sign domain at a
  time.

  \see keyRange
*/
template <class DataType>
NChartRange NChartDataContainer<DataType>::valueRange(bool &foundRange, NChart::SignDomain signDomain, const NChartRange &inKeyRange)
{
  if (isEmpty())
  {
    foundRange = false;
    return NChartRange();
  }
  NChartRange range;
  const bool restrictKeyRange = inKeyRange != NChartRange();
  bool haveLower = false;
  bool haveUpper = false;
  NChartRange current;
  NChartDataContainer<DataType>::const_iterator itBegin = constBegin();
  NChartDataContainer<DataType>::const_iterator itEnd = constEnd();
  if (DataType::sortKeyIsMainKey() && restrictKeyRange)
  {
    itBegin = findBegin(inKeyRange.lower, false);
    itEnd = findEnd(inKeyRange.upper, false);
  }
  if (signDomain == NChart::sdBoth) // range may be anywhere
  {
    for (NChartDataContainer<DataType>::const_iterator it = itBegin; it != itEnd; ++it)
    {
      if (restrictKeyRange && (it->mainKey() < inKeyRange.lower || it->mainKey() > inKeyRange.upper))
        continue;
      current = it->valueRange();
      if ((current.lower < range.lower || !haveLower) && !qIsNaN(current.lower))
      {
        range.lower = current.lower;
        haveLower = true;
      }
      if ((current.upper > range.upper || !haveUpper) && !qIsNaN(current.upper))
      {
        range.upper = current.upper;
        haveUpper = true;
      }
    }
  } else if (signDomain == NChart::sdNegative) // range may only be in the negative sign domain
  {
    for (NChartDataContainer<DataType>::const_iterator it = itBegin; it != itEnd; ++it)
    {
      if (restrictKeyRange && (it->mainKey() < inKeyRange.lower || it->mainKey() > inKeyRange.upper))
        continue;
      current = it->valueRange();
      if ((current.lower < range.lower || !haveLower) && current.lower < 0 && !qIsNaN(current.lower))
      {
        range.lower = current.lower;
        haveLower = true;
      }
      if ((current.upper > range.upper || !haveUpper) && current.upper < 0 && !qIsNaN(current.upper))
      {
        range.upper = current.upper;
        haveUpper = true;
      }
    }
  } else if (signDomain == NChart::sdPositive) // range may only be in the positive sign domain
  {
    for (NChartDataContainer<DataType>::const_iterator it = itBegin; it != itEnd; ++it)
    {
      if (restrictKeyRange && (it->mainKey() < inKeyRange.lower || it->mainKey() > inKeyRange.upper))
        continue;
      current = it->valueRange();
      if ((current.lower < range.lower || !haveLower) && current.lower > 0 && !qIsNaN(current.lower))
      {
        range.lower = current.lower;
        haveLower = true;
      }
      if ((current.upper > range.upper || !haveUpper) && current.upper > 0 && !qIsNaN(current.upper))
      {
        range.upper = current.upper;
        haveUpper = true;
      }
    }
  }
  
  foundRange = haveLower && haveUpper;
  return range;
}

/*!
  Makes sure \a begin and \a end mark a data range that is both within the bounds of this data
  container's data, as well as within the specified \a dataRange. The initial range described by
  the passed iterators \a begin and \a end is never expanded, only contracted if necessary.
  
  This function doesn't require for \a dataRange to be within the bounds of this data container's
  valid range.
*/
template <class DataType>
void NChartDataContainer<DataType>::limitIteratorsToDataRange(const_iterator &begin, const_iterator &end, const NChartDataRange &dataRange) const
{
  NChartDataRange iteratorRange(int(begin-constBegin()), int(end-constBegin()));
  iteratorRange = iteratorRange.bounded(dataRange.bounded(this->dataRange()));
  begin = constBegin()+iteratorRange.begin();
  end = constBegin()+iteratorRange.end();
}

/*! \internal
  
  Increases the preallocation pool to have a size of at least \a minimumPreallocSize. Depending on
  the preallocation history, the container will grow by more than requested, to speed up future
  consecutive size increases.
  
  if \a minimumPreallocSize is smaller than or equal to the current preallocation pool size, this
  method does nothing.
*/
template <class DataType>
void NChartDataContainer<DataType>::preallocateGrow(int minimumPreallocSize)
{
  if (minimumPreallocSize <= mPreallocSize)
    return;
  
  int newPreallocSize = minimumPreallocSize;
  newPreallocSize += (1u<<qBound(4, mPreallocIteration+4, 15)) - 12; // do 4 up to 32768-12 preallocation, doubling in each intermediate iteration
  ++mPreallocIteration;
  
  int sizeDifference = newPreallocSize-mPreallocSize;
  mData.resize(mData.size()+sizeDifference);
  std::copy_backward(mData.begin()+mPreallocSize, mData.end()-sizeDifference, mData.end());
  mPreallocSize = newPreallocSize;
}

/*! \internal
  
  This method decides, depending on the total allocation size and the size of the unused pre- and
  postallocation pools, whether it is sensible to reduce the pools in order to free up unused
  memory. It then possibly calls \ref squeeze to do the deallocation.
  
  If \ref setAutoSqueeze is enabled, this method is called automatically each time data points are
  removed from the container (e.g. \ref remove).
  
  \note when changing the decision parameters, care must be taken not to cause a back-and-forth
  between squeezing and reallocation due to the growth strategy of the internal QVector and \ref
  preallocateGrow. The hysteresis between allocation and deallocation should be made high enough
  (at the expense of possibly larger unused memory from time to time).
*/
template <class DataType>
void NChartDataContainer<DataType>::performAutoSqueeze()
{
  const int totalAlloc = mData.capacity();
  const int postAllocSize = totalAlloc-mData.size();
  const int usedSize = size();
  bool shrinkPostAllocation = false;
  bool shrinkPreAllocation = false;
  if (totalAlloc > 650000) // if allocation is larger, shrink earlier with respect to total used size
  {
    shrinkPostAllocation = postAllocSize > usedSize*1.5; // QVector grow strategy is 2^n for static data. Watch out not to oscillate!
    shrinkPreAllocation = mPreallocSize*10 > usedSize;
  } else if (totalAlloc > 1000) // below 10 MiB raw data be generous with preallocated memory, below 1k points don't even bother
  {
    shrinkPostAllocation = postAllocSize > usedSize*5;
    shrinkPreAllocation = mPreallocSize > usedSize*1.5; // preallocation can grow into postallocation, so can be smaller
  }
  
  if (shrinkPreAllocation || shrinkPostAllocation)
    squeeze(shrinkPreAllocation, shrinkPostAllocation);
}


/* end of 'src/datacontainer.h' */


/* including file 'src/plottable.h'        */
/* modified 2021-03-29T02:30:44, size 8461 */

class NCHART_LIB_DECL NChartSelectionDecorator
{
  Q_GADGET
public:
  NChartSelectionDecorator();
  virtual ~NChartSelectionDecorator();
  
  // getters:
  QPen pen() const { return mPen; }
  QBrush brush() const { return mBrush; }
  NChartScatterStyle scatterStyle() const { return mScatterStyle; }
  NChartScatterStyle::ScatterProperties usedScatterProperties() const { return mUsedScatterProperties; }
  
  // setters:
  void setPen(const QPen &pen);
  void setBrush(const QBrush &brush);
  void setScatterStyle(const NChartScatterStyle &scatterStyle, NChartScatterStyle::ScatterProperties usedProperties=NChartScatterStyle::spPen);
  void setUsedScatterProperties(const NChartScatterStyle::ScatterProperties &properties);
  
  // non-virtual methods:
  void applyPen(NChartPainter *painter) const;
  void applyBrush(NChartPainter *painter) const;
  NChartScatterStyle getFinalScatterStyle(const NChartScatterStyle &unselectedStyle) const;
  
  // introduced virtual methods:
  virtual void copyFrom(const NChartSelectionDecorator *other);
  virtual void drawDecoration(NChartPainter *painter, NChartDataSelection selection);
  
protected:
  // property members:
  QPen mPen;
  QBrush mBrush;
  NChartScatterStyle mScatterStyle;
  NChartScatterStyle::ScatterProperties mUsedScatterProperties;
  // non-property members:
  NChartAbstractPlottable *mPlottable;
  
  // introduced virtual methods:
  virtual bool registerWithPlottable(NChartAbstractPlottable *plottable);
  
private:
  Q_DISABLE_COPY(NChartSelectionDecorator)
  friend class NChartAbstractPlottable;
};
Q_DECLARE_METATYPE(NChartSelectionDecorator*)


class NCHART_LIB_DECL NChartAbstractPlottable : public NChartLayerable
{
  Q_OBJECT
  /// \cond INCLUDE_QPROPERTIES
  Q_PROPERTY(QString name READ name WRITE setName)
  Q_PROPERTY(bool antialiasedFill READ antialiasedFill WRITE setAntialiasedFill)
  Q_PROPERTY(bool antialiasedScatters READ antialiasedScatters WRITE setAntialiasedScatters)
  Q_PROPERTY(QPen pen READ pen WRITE setPen)
  Q_PROPERTY(QBrush brush READ brush WRITE setBrush)
  Q_PROPERTY(NChartAxis* keyAxis READ keyAxis WRITE setKeyAxis)
  Q_PROPERTY(NChartAxis* valueAxis READ valueAxis WRITE setValueAxis)
  Q_PROPERTY(NChart::SelectionType selectable READ selectable WRITE setSelectable NOTIFY selectableChanged)
  Q_PROPERTY(NChartDataSelection selection READ selection WRITE setSelection NOTIFY selectionChanged)
  Q_PROPERTY(NChartSelectionDecorator* selectionDecorator READ selectionDecorator WRITE setSelectionDecorator)
  /// \endcond
public:
  NChartAbstractPlottable(NChartAxis *keyAxis, NChartAxis *valueAxis);
  virtual ~NChartAbstractPlottable() Q_DECL_OVERRIDE;
  
  // getters:
  QString name() const { return mName; }
  bool antialiasedFill() const { return mAntialiasedFill; }
  bool antialiasedScatters() const { return mAntialiasedScatters; }
  QPen pen() const { return mPen; }
  QBrush brush() const { return mBrush; }
  NChartAxis *keyAxis() const { return mKeyAxis.data(); }
  NChartAxis *valueAxis() const { return mValueAxis.data(); }
  NChart::SelectionType selectable() const { return mSelectable; }
  bool selected() const { return !mSelection.isEmpty(); }
  NChartDataSelection selection() const { return mSelection; }
  NChartSelectionDecorator *selectionDecorator() const { return mSelectionDecorator; }
  
  // setters:
  void setName(const QString &name);
  void setAntialiasedFill(bool enabled);
  void setAntialiasedScatters(bool enabled);
  void setPen(const QPen &pen);
  void setBrush(const QBrush &brush);
  void setKeyAxis(NChartAxis *axis);
  void setValueAxis(NChartAxis *axis);
  Q_SLOT void setSelectable(NChart::SelectionType selectable);
  Q_SLOT void setSelection(NChartDataSelection selection);
  void setSelectionDecorator(NChartSelectionDecorator *decorator);

  // introduced virtual methods:
  virtual double selectTest(const QPointF &pos, bool onlySelectable, QVariant *details=nullptr) const Q_DECL_OVERRIDE = 0; // actually introduced in NChartLayerable as non-pure, but we want to force reimplementation for plottables
  virtual NChartPlottableInterface1D *interface1D() { return nullptr; }
  virtual NChartRange getKeyRange(bool &foundRange, NChart::SignDomain inSignDomain=NChart::sdBoth) const = 0;
  virtual NChartRange getValueRange(bool &foundRange, NChart::SignDomain inSignDomain=NChart::sdBoth, const NChartRange &inKeyRange=NChartRange()) const = 0;
  
  // non-property methods:
  void coordsToPixels(double key, double value, double &x, double &y) const;
  const QPointF coordsToPixels(double key, double value) const;
  void pixelsToCoords(double x, double y, double &key, double &value) const;
  void pixelsToCoords(const QPointF &pixelPos, double &key, double &value) const;
  void rescaleAxes(bool onlyEnlarge=false) const;
  void rescaleKeyAxis(bool onlyEnlarge=false) const;
  void rescaleValueAxis(bool onlyEnlarge=false, bool inKeyRange=false) const;
  bool addToLegend(NChartLegend *legend);
  bool addToLegend();
  bool removeFromLegend(NChartLegend *legend) const;
  bool removeFromLegend() const;
  
signals:
  void selectionChanged(bool selected);
  void selectionChanged(const NChartDataSelection &selection);
  void selectableChanged(NChart::SelectionType selectable);
  
protected:
  // property members:
  QString mName;
  bool mAntialiasedFill, mAntialiasedScatters;
  QPen mPen;
  QBrush mBrush;
  QPointer<NChartAxis> mKeyAxis, mValueAxis;
  NChart::SelectionType mSelectable;
  NChartDataSelection mSelection;
  NChartSelectionDecorator *mSelectionDecorator;
  
  // reimplemented virtual methods:
  virtual QRect clipRect() const Q_DECL_OVERRIDE;
  virtual void draw(NChartPainter *painter) Q_DECL_OVERRIDE = 0;
  virtual NChart::Interaction selectionCategory() const Q_DECL_OVERRIDE;
  void applyDefaultAntialiasingHint(NChartPainter *painter) const Q_DECL_OVERRIDE;
  // events:
  virtual void selectEvent(QMouseEvent *event, bool additive, const QVariant &details, bool *selectionStateChanged) Q_DECL_OVERRIDE;
  virtual void deselectEvent(bool *selectionStateChanged) Q_DECL_OVERRIDE;
  
  // introduced virtual methods:
  virtual void drawLegendIcon(NChartPainter *painter, const QRectF &rect) const = 0;
  
  // non-virtual methods:
  void applyFillAntialiasingHint(NChartPainter *painter) const;
  void applyScattersAntialiasingHint(NChartPainter *painter) const;

private:
  Q_DISABLE_COPY(NChartAbstractPlottable)
  
  friend class NChartControl;
  friend class NChartAxis;
  friend class NChartPlottableLegendItem;
};


/* end of 'src/plottable.h' */


/* including file 'src/item.h'             */
/* modified 2021-03-29T02:30:44, size 9425 */

class NCHART_LIB_DECL NChartItemAnchor
{
  Q_GADGET
public:
  NChartItemAnchor(NChartControl *parentPlot, NChartAbstractItem *parentItem, const QString &name, int anchorId=-1);
  virtual ~NChartItemAnchor();
  
  // getters:
  QString name() const { return mName; }
  virtual QPointF pixelPosition() const;
  
protected:
  // property members:
  QString mName;
  
  // non-property members:
  NChartControl *mParentPlot;
  NChartAbstractItem *mParentItem;
  int mAnchorId;
  QSet<NChartItemPosition*> mChildrenX, mChildrenY;
  
  // introduced virtual methods:
  virtual NChartItemPosition *toNChartItemPosition() { return nullptr; }
  
  // non-virtual methods:
  void addChildX(NChartItemPosition* pos); // called from pos when this anchor is set as parent
  void removeChildX(NChartItemPosition *pos); // called from pos when its parent anchor is reset or pos deleted
  void addChildY(NChartItemPosition* pos); // called from pos when this anchor is set as parent
  void removeChildY(NChartItemPosition *pos); // called from pos when its parent anchor is reset or pos deleted
  
private:
  Q_DISABLE_COPY(NChartItemAnchor)
  
  friend class NChartItemPosition;
};



class NCHART_LIB_DECL NChartItemPosition : public NChartItemAnchor
{
  Q_GADGET
public:
  /*!
    Defines the ways an item position can be specified. Thus it defines what the numbers passed to
    \ref setCoords actually mean.
    
    \see setType
  */
  enum PositionType { ptAbsolute        ///< Static positioning in pixels, starting from the top left corner of the viewport/widget.
                      ,ptViewportRatio  ///< Static positioning given by a fraction of the viewport size. For example, if you call setCoords(0, 0), the position will be at the top
                                        ///< left corner of the viewport/widget. setCoords(1, 1) will be at the bottom right corner, setCoords(0.5, 0) will be horizontally centered and
                                        ///< vertically at the top of the viewport/widget, etc.
                      ,ptAxisRectRatio  ///< Static positioning given by a fraction of the axis rect size (see \ref setAxisRect). For example, if you call setCoords(0, 0), the position will be at the top
                                        ///< left corner of the axis rect. setCoords(1, 1) will be at the bottom right corner, setCoords(0.5, 0) will be horizontally centered and
                                        ///< vertically at the top of the axis rect, etc. You can also go beyond the axis rect by providing negative coordinates or coordinates larger than 1.
                      ,ptPlotCoords     ///< Dynamic positioning at a plot coordinate defined by two axes (see \ref setAxes).
                    };
  Q_ENUMS(PositionType)
  
  NChartItemPosition(NChartControl *parentPlot, NChartAbstractItem *parentItem, const QString &name);
  virtual ~NChartItemPosition() Q_DECL_OVERRIDE;
  
  // getters:
  PositionType type() const { return typeX(); }
  PositionType typeX() const { return mPositionTypeX; }
  PositionType typeY() const { return mPositionTypeY; }
  NChartItemAnchor *parentAnchor() const { return parentAnchorX(); }
  NChartItemAnchor *parentAnchorX() const { return mParentAnchorX; }
  NChartItemAnchor *parentAnchorY() const { return mParentAnchorY; }
  double key() const { return mKey; }
  double value() const { return mValue; }
  QPointF coords() const { return QPointF(mKey, mValue); }
  NChartAxis *keyAxis() const { return mKeyAxis.data(); }
  NChartAxis *valueAxis() const { return mValueAxis.data(); }
  NChartAxisRect *axisRect() const;
  virtual QPointF pixelPosition() const Q_DECL_OVERRIDE;
  
  // setters:
  void setType(PositionType type);
  void setTypeX(PositionType type);
  void setTypeY(PositionType type);
  bool setParentAnchor(NChartItemAnchor *parentAnchor, bool keepPixelPosition=false);
  bool setParentAnchorX(NChartItemAnchor *parentAnchor, bool keepPixelPosition=false);
  bool setParentAnchorY(NChartItemAnchor *parentAnchor, bool keepPixelPosition=false);
  void setCoords(double key, double value);
  void setCoords(const QPointF &pos);
  void setAxes(NChartAxis* keyAxis, NChartAxis* valueAxis);
  void setAxisRect(NChartAxisRect *axisRect);
  void setPixelPosition(const QPointF &pixelPosition);
  
protected:
  // property members:
  PositionType mPositionTypeX, mPositionTypeY;
  QPointer<NChartAxis> mKeyAxis, mValueAxis;
  QPointer<NChartAxisRect> mAxisRect;
  double mKey, mValue;
  NChartItemAnchor *mParentAnchorX, *mParentAnchorY;
  
  // reimplemented virtual methods:
  virtual NChartItemPosition *toNChartItemPosition() Q_DECL_OVERRIDE { return this; }
  
private:
  Q_DISABLE_COPY(NChartItemPosition)
  
};
Q_DECLARE_METATYPE(NChartItemPosition::PositionType)


class NCHART_LIB_DECL NChartAbstractItem : public NChartLayerable
{
  Q_OBJECT
  /// \cond INCLUDE_QPROPERTIES
  Q_PROPERTY(bool clipToAxisRect READ clipToAxisRect WRITE setClipToAxisRect)
  Q_PROPERTY(NChartAxisRect* clipAxisRect READ clipAxisRect WRITE setClipAxisRect)
  Q_PROPERTY(bool selectable READ selectable WRITE setSelectable NOTIFY selectableChanged)
  Q_PROPERTY(bool selected READ selected WRITE setSelected NOTIFY selectionChanged)
  /// \endcond
public:
  explicit NChartAbstractItem(NChartControl *parentPlot);
  virtual ~NChartAbstractItem() Q_DECL_OVERRIDE;
  
  // getters:
  bool clipToAxisRect() const { return mClipToAxisRect; }
  NChartAxisRect *clipAxisRect() const;
  bool selectable() const { return mSelectable; }
  bool selected() const { return mSelected; }
  
  // setters:
  void setClipToAxisRect(bool clip);
  void setClipAxisRect(NChartAxisRect *rect);
  Q_SLOT void setSelectable(bool selectable);
  Q_SLOT void setSelected(bool selected);
  
  // reimplemented virtual methods:
  virtual double selectTest(const QPointF &pos, bool onlySelectable, QVariant *details=nullptr) const Q_DECL_OVERRIDE = 0;
  
  // non-virtual methods:
  QList<NChartItemPosition*> positions() const { return mPositions; }
  QList<NChartItemAnchor*> anchors() const { return mAnchors; }
  NChartItemPosition *position(const QString &name) const;
  NChartItemAnchor *anchor(const QString &name) const;
  bool hasAnchor(const QString &name) const;
  
signals:
  void selectionChanged(bool selected);
  void selectableChanged(bool selectable);
  
protected:
  // property members:
  bool mClipToAxisRect;
  QPointer<NChartAxisRect> mClipAxisRect;
  QList<NChartItemPosition*> mPositions;
  QList<NChartItemAnchor*> mAnchors;
  bool mSelectable, mSelected;
  
  // reimplemented virtual methods:
  virtual NChart::Interaction selectionCategory() const Q_DECL_OVERRIDE;
  virtual QRect clipRect() const Q_DECL_OVERRIDE;
  virtual void applyDefaultAntialiasingHint(NChartPainter *painter) const Q_DECL_OVERRIDE;
  virtual void draw(NChartPainter *painter) Q_DECL_OVERRIDE = 0;
  // events:
  virtual void selectEvent(QMouseEvent *event, bool additive, const QVariant &details, bool *selectionStateChanged) Q_DECL_OVERRIDE;
  virtual void deselectEvent(bool *selectionStateChanged) Q_DECL_OVERRIDE;
  
  // introduced virtual methods:
  virtual QPointF anchorPixelPosition(int anchorId) const;
  
  // non-virtual methods:
  double rectDistance(const QRectF &rect, const QPointF &pos, bool filledRect) const;
  NChartItemPosition *createPosition(const QString &name);
  NChartItemAnchor *createAnchor(const QString &name, int anchorId);
  
private:
  Q_DISABLE_COPY(NChartAbstractItem)
  
  friend class NChartControl;
  friend class NChartItemAnchor;
};

/* end of 'src/item.h' */


/* including file 'src/core.h'              */
/* modified 2021-03-29T02:30:44, size 19304 */

class NCHART_LIB_DECL NChartControl : public QWidget
{
  Q_OBJECT
  /// \cond INCLUDE_QPROPERTIES
  Q_PROPERTY(QRect viewport READ viewport WRITE setViewport)
  Q_PROPERTY(QPixmap background READ background WRITE setBackground)
  Q_PROPERTY(bool backgroundScaled READ backgroundScaled WRITE setBackgroundScaled)
  Q_PROPERTY(Qt::AspectRatioMode backgroundScaledMode READ backgroundScaledMode WRITE setBackgroundScaledMode)
  Q_PROPERTY(NChartLayoutGrid* plotLayout READ plotLayout)
  Q_PROPERTY(bool autoAddPlottableToLegend READ autoAddPlottableToLegend WRITE setAutoAddPlottableToLegend)
  Q_PROPERTY(int selectionTolerance READ selectionTolerance WRITE setSelectionTolerance)
  Q_PROPERTY(bool noAntialiasingOnDrag READ noAntialiasingOnDrag WRITE setNoAntialiasingOnDrag)
  Q_PROPERTY(Qt::KeyboardModifier multiSelectModifier READ multiSelectModifier WRITE setMultiSelectModifier)
  Q_PROPERTY(bool openGl READ openGl WRITE setOpenGl)
  /// \endcond
public:
  /*!
    Defines how a layer should be inserted relative to an other layer.

    \see addLayer, moveLayer
  */
  enum LayerInsertMode { limBelow  ///< Layer is inserted below other layer
                         ,limAbove ///< Layer is inserted above other layer
                       };
  Q_ENUMS(LayerInsertMode)
  
  /*!
    Defines with what timing the NChartControl surface is refreshed after a replot.

    \see replot
  */
  enum RefreshPriority { rpImmediateRefresh ///< Replots immediately and repaints the widget immediately by calling QWidget::repaint() after the replot
                         ,rpQueuedRefresh   ///< Replots immediately, but queues the widget repaint, by calling QWidget::update() after the replot. This way multiple redundant widget repaints can be avoided.
                         ,rpRefreshHint     ///< Whether to use immediate or queued refresh depends on whether the plotting hint \ref NChart::phImmediateRefresh is set, see \ref setPlottingHints.
                         ,rpQueuedReplot    ///< Queues the entire replot for the next event loop iteration. This way multiple redundant replots can be avoided. The actual replot is then done with \ref rpRefreshHint priority.
                       };
  Q_ENUMS(RefreshPriority)
  
  explicit NChartControl(QWidget *parent = nullptr);
  virtual ~NChartControl() Q_DECL_OVERRIDE;
  
  // getters:
  QRect viewport() const { return mViewport; }
  double bufferDevicePixelRatio() const { return mBufferDevicePixelRatio; }
  QPixmap background() const { return mBackgroundPixmap; }
  bool backgroundScaled() const { return mBackgroundScaled; }
  Qt::AspectRatioMode backgroundScaledMode() const { return mBackgroundScaledMode; }
  NChartLayoutGrid *plotLayout() const { return mPlotLayout; }
  NChart::AntialiasedElements antialiasedElements() const { return mAntialiasedElements; }
  NChart::AntialiasedElements notAntialiasedElements() const { return mNotAntialiasedElements; }
  bool autoAddPlottableToLegend() const { return mAutoAddPlottableToLegend; }
  const NChart::Interactions interactions() const { return mInteractions; }
  int selectionTolerance() const { return mSelectionTolerance; }
  bool noAntialiasingOnDrag() const { return mNoAntialiasingOnDrag; }
  NChart::PlottingHints plottingHints() const { return mPlottingHints; }
  Qt::KeyboardModifier multiSelectModifier() const { return mMultiSelectModifier; }
  NChart::SelectionRectMode selectionRectMode() const { return mSelectionRectMode; }
  NChartSelectionRect *selectionRect() const { return mSelectionRect; }
  bool openGl() const { return mOpenGl; }
  
  // setters:
  void setViewport(const QRect &rect);
  void setBufferDevicePixelRatio(double ratio);
  void setBackground(const QPixmap &pm);
  void setBackground(const QPixmap &pm, bool scaled, Qt::AspectRatioMode mode=Qt::KeepAspectRatioByExpanding);
  void setBackground(const QBrush &brush);
  void setBackgroundScaled(bool scaled);
  void setBackgroundScaledMode(Qt::AspectRatioMode mode);
  void setAntialiasedElements(const NChart::AntialiasedElements &antialiasedElements);
  void setAntialiasedElement(NChart::AntialiasedElement antialiasedElement, bool enabled=true);
  void setNotAntialiasedElements(const NChart::AntialiasedElements &notAntialiasedElements);
  void setNotAntialiasedElement(NChart::AntialiasedElement notAntialiasedElement, bool enabled=true);
  void setAutoAddPlottableToLegend(bool on);
  void setInteractions(const NChart::Interactions &interactions);
  void setInteraction(const NChart::Interaction &interaction, bool enabled=true);
  void setSelectionTolerance(int pixels);
  void setNoAntialiasingOnDrag(bool enabled);
  void setPlottingHints(const NChart::PlottingHints &hints);
  void setPlottingHint(NChart::PlottingHint hint, bool enabled=true);
  void setMultiSelectModifier(Qt::KeyboardModifier modifier);
  void setSelectionRectMode(NChart::SelectionRectMode mode);
  void setSelectionRect(NChartSelectionRect *selectionRect);
  void setOpenGl(bool enabled, int multisampling=16);
  
  // non-property methods:
  // plottable interface:
  NChartAbstractPlottable *plottable(int index);
  NChartAbstractPlottable *plottable();
  bool removePlottable(NChartAbstractPlottable *plottable);
  bool removePlottable(int index);
  int clearPlottables();
  int plottableCount() const;
  QList<NChartAbstractPlottable*> selectedPlottables() const;
  template<class PlottableType>
  PlottableType *plottableAt(const QPointF &pos, bool onlySelectable=false, int *dataIndex=nullptr) const;
  NChartAbstractPlottable *plottableAt(const QPointF &pos, bool onlySelectable=false, int *dataIndex=nullptr) const;
  bool hasPlottable(NChartAbstractPlottable *plottable) const;
 
  // specialized interface for NChartGraph:
  NChartGraph *graph(int index) const;
  NChartGraph *graph() const;
  NChartGraph *addGraph(NChartAxis *keyAxis=nullptr, NChartAxis *valueAxis=nullptr);
  bool removeGraph(NChartGraph *graph);
  bool removeGraph(int index);
  int clearGraphs();
  int graphCount() const;
  QList<NChartGraph*> selectedGraphs() const;

  // item interface:
  NChartAbstractItem *item(int index) const;
  NChartAbstractItem *item() const;
  bool removeItem(NChartAbstractItem *item);
  bool removeItem(int index);
  int clearItems();
  int itemCount() const;
  QList<NChartAbstractItem*> selectedItems() const;
  template<class ItemType>
  ItemType *itemAt(const QPointF &pos, bool onlySelectable=false) const;
  NChartAbstractItem *itemAt(const QPointF &pos, bool onlySelectable=false) const;
  bool hasItem(NChartAbstractItem *item) const;
  
  // layer interface:
  NChartLayer *layer(const QString &name) const;
  NChartLayer *layer(int index) const;
  NChartLayer *currentLayer() const;
  bool setCurrentLayer(const QString &name);
  bool setCurrentLayer(NChartLayer *layer);
  int layerCount() const;
  bool addLayer(const QString &name, NChartLayer *otherLayer=nullptr, LayerInsertMode insertMode=limAbove);
  bool removeLayer(NChartLayer *layer);
  bool moveLayer(NChartLayer *layer, NChartLayer *otherLayer, LayerInsertMode insertMode=limAbove);
  
  // axis rect/layout interface:
  int axisRectCount() const;
  NChartAxisRect* axisRect(int index=0) const;
  QList<NChartAxisRect*> axisRects() const;
  NChartLayoutElement* layoutElementAt(const QPointF &pos) const;
  NChartAxisRect* axisRectAt(const QPointF &pos) const;
  Q_SLOT void rescaleAxes(bool onlyVisiblePlottables=false);
  
  QList<NChartAxis*> selectedAxes() const;
  QList<NChartLegend*> selectedLegends() const;
  Q_SLOT void deselectAll();
  
  bool savePdf(const QString &fileName, int width=0, int height=0, NChart::ExportPen exportPen=NChart::epAllowCosmetic, const QString &pdfCreator=QString(), const QString &pdfTitle=QString());
  bool savePng(const QString &fileName, int width=0, int height=0, double scale=1.0, int quality=-1, int resolution=96, NChart::ResolutionUnit resolutionUnit=NChart::ruDotsPerInch);
  bool saveJpg(const QString &fileName, int width=0, int height=0, double scale=1.0, int quality=-1, int resolution=96, NChart::ResolutionUnit resolutionUnit=NChart::ruDotsPerInch);
  bool saveBmp(const QString &fileName, int width=0, int height=0, double scale=1.0, int resolution=96, NChart::ResolutionUnit resolutionUnit=NChart::ruDotsPerInch);
  bool saveRastered(const QString &fileName, int width, int height, double scale, const char *format, int quality=-1, int resolution=96, NChart::ResolutionUnit resolutionUnit=NChart::ruDotsPerInch);
  QPixmap toPixmap(int width=0, int height=0, double scale=1.0);
  void toPainter(NChartPainter *painter, int width=0, int height=0);
  Q_SLOT void replot(NChartControl::RefreshPriority refreshPriority=NChartControl::rpRefreshHint);
  double replotTime(bool average=false) const;
  
  NChartAxis *xAxis, *yAxis, *xAxis2, *yAxis2;
  NChartLegend *legend;
  
signals:
  void mouseDoubleClick(QMouseEvent *event);
  void mousePress(QMouseEvent *event);
  void mouseMove(QMouseEvent *event);
  void mouseRelease(QMouseEvent *event);
  void mouseWheel(QWheelEvent *event);
  
  void plottableClick(NChartAbstractPlottable *plottable, int dataIndex, QMouseEvent *event);
  void plottableDoubleClick(NChartAbstractPlottable *plottable, int dataIndex, QMouseEvent *event);
  void itemClick(NChartAbstractItem *item, QMouseEvent *event);
  void itemDoubleClick(NChartAbstractItem *item, QMouseEvent *event);
  void axisClick(NChartAxis *axis, NChartAxis::SelectablePart part, QMouseEvent *event);
  void axisDoubleClick(NChartAxis *axis, NChartAxis::SelectablePart part, QMouseEvent *event);
  void legendClick(NChartLegend *legend, NChartAbstractLegendItem *item, QMouseEvent *event);
  void legendDoubleClick(NChartLegend *legend,  NChartAbstractLegendItem *item, QMouseEvent *event);
  
  void selectionChangedByUser();
  void beforeReplot();
  void afterLayout();
  void afterReplot();
  
protected:
  // property members:
  QRect mViewport;
  double mBufferDevicePixelRatio;
  NChartLayoutGrid *mPlotLayout;
  bool mAutoAddPlottableToLegend;
  QList<NChartAbstractPlottable*> mPlottables;
  QList<NChartGraph*> mGraphs; // extra list of plottables also in mPlottables that are of type NChartGraph
  QList<NChartAbstractItem*> mItems;
  QList<NChartLayer*> mLayers;
  NChart::AntialiasedElements mAntialiasedElements, mNotAntialiasedElements;
  NChart::Interactions mInteractions;
  int mSelectionTolerance;
  bool mNoAntialiasingOnDrag;
  QBrush mBackgroundBrush;
  QPixmap mBackgroundPixmap;
  QPixmap mScaledBackgroundPixmap;
  bool mBackgroundScaled;
  Qt::AspectRatioMode mBackgroundScaledMode;
  NChartLayer *mCurrentLayer;
  NChart::PlottingHints mPlottingHints;
  Qt::KeyboardModifier mMultiSelectModifier;
  NChart::SelectionRectMode mSelectionRectMode;
  NChartSelectionRect *mSelectionRect;
  bool mOpenGl;
  
  // non-property members:
  QList<QSharedPointer<NChartAbstractPaintBuffer> > mPaintBuffers;
  QPoint mMousePressPos;
  bool mMouseHasMoved;
  QPointer<NChartLayerable> mMouseEventLayerable;
  QPointer<NChartLayerable> mMouseSignalLayerable;
  QVariant mMouseEventLayerableDetails;
  QVariant mMouseSignalLayerableDetails;
  bool mReplotting;
  bool mReplotQueued;
  double mReplotTime, mReplotTimeAverage;
  int mOpenGlMultisamples;
  NChart::AntialiasedElements mOpenGlAntialiasedElementsBackup;
  bool mOpenGlCacheLabelsBackup;
#ifdef NCHART_OPENGL_FBO
  QSharedPointer<QOpenGLContext> mGlContext;
  QSharedPointer<QSurface> mGlSurface;
  QSharedPointer<QOpenGLPaintDevice> mGlPaintDevice;
#endif
  
  // reimplemented virtual methods:
  virtual QSize minimumSizeHint() const Q_DECL_OVERRIDE;
  virtual QSize sizeHint() const Q_DECL_OVERRIDE;
  virtual void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
  virtual void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
  virtual void mouseDoubleClickEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
  virtual void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
  virtual void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
  virtual void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
  virtual void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;
  
  // introduced virtual methods:
  virtual void draw(NChartPainter *painter);
  virtual void updateLayout();
  virtual void axisRemoved(NChartAxis *axis);
  virtual void legendRemoved(NChartLegend *legend);
  Q_SLOT virtual void processRectSelection(QRect rect, QMouseEvent *event);
  Q_SLOT virtual void processRectZoom(QRect rect, QMouseEvent *event);
  Q_SLOT virtual void processPointSelection(QMouseEvent *event);
  
  // non-virtual methods:
  bool registerPlottable(NChartAbstractPlottable *plottable);
  bool registerGraph(NChartGraph *graph);
  bool registerItem(NChartAbstractItem* item);
  void updateLayerIndices() const;
  NChartLayerable *layerableAt(const QPointF &pos, bool onlySelectable, QVariant *selectionDetails=nullptr) const;
  QList<NChartLayerable*> layerableListAt(const QPointF &pos, bool onlySelectable, QList<QVariant> *selectionDetails=nullptr) const;
  void drawBackground(NChartPainter *painter);
  void setupPaintBuffers();
  NChartAbstractPaintBuffer *createPaintBuffer();
  bool hasInvalidatedPaintBuffers();
  bool setupOpenGl();
  void freeOpenGl();
  
  friend class NChartLegend;
  friend class NChartAxis;
  friend class NChartLayer;
  friend class NChartAxisRect;
  friend class NChartAbstractPlottable;
  friend class NChartGraph;
  friend class NChartAbstractItem;
};
Q_DECLARE_METATYPE(NChartControl::LayerInsertMode)
Q_DECLARE_METATYPE(NChartControl::RefreshPriority)


// implementation of template functions:

/*!
  Returns the plottable at the pixel position \a pos. The plottable type (a NChartAbstractPlottable
  subclass) that shall be taken into consideration can be specified via the template parameter.

  Plottables that only consist of single lines (like graphs) have a tolerance band around them, see
  \ref setSelectionTolerance. If multiple plottables come into consideration, the one closest to \a
  pos is returned.
  
  If \a onlySelectable is true, only plottables that are selectable
  (NChartAbstractPlottable::setSelectable) are considered.
  
  if \a dataIndex is non-null, it is set to the index of the plottable's data point that is closest
  to \a pos.

  If there is no plottable of the specified type at \a pos, returns \c nullptr.
  
  \see itemAt, layoutElementAt
*/
template<class PlottableType>
PlottableType *NChartControl::plottableAt(const QPointF &pos, bool onlySelectable, int *dataIndex) const
{
  PlottableType *resultPlottable = 0;
  QVariant resultDetails;
  double resultDistance = mSelectionTolerance; // only regard clicks with distances smaller than mSelectionTolerance as selections, so initialize with that value
  
  foreach (NChartAbstractPlottable *plottable, mPlottables)
  {
    PlottableType *currentPlottable = qobject_cast<PlottableType*>(plottable);
    if (!currentPlottable || (onlySelectable && !currentPlottable->selectable())) // we could have also passed onlySelectable to the selectTest function, but checking here is faster, because we have access to NChartAbstractPlottable::selectable
      continue;
    if (currentPlottable->clipRect().contains(pos.toPoint())) // only consider clicks where the plottable is actually visible
    {
      QVariant details;
      double currentDistance = currentPlottable->selectTest(pos, false, dataIndex ? &details : nullptr);
      if (currentDistance >= 0 && currentDistance < resultDistance)
      {
        resultPlottable = currentPlottable;
        resultDetails = details;
        resultDistance = currentDistance;
      }
    }
  }
  
  if (resultPlottable && dataIndex)
  {
    NChartDataSelection sel = resultDetails.value<NChartDataSelection>();
    if (!sel.isEmpty())
      *dataIndex = sel.dataRange(0).begin();
  }
  return resultPlottable;
}

/*!
  Returns the item at the pixel position \a pos. The item type (a NChartAbstractItem subclass) that shall be
  taken into consideration can be specified via the template parameter. Items that only consist of single
  lines (e.g. \ref NChartItemLine or \ref NChartItemCurve) have a tolerance band around them, see \ref
  setSelectionTolerance. If multiple items come into consideration, the one closest to \a pos is returned.
  
  If \a onlySelectable is true, only items that are selectable (NChartAbstractItem::setSelectable) are
  considered.
  
  If there is no item at \a pos, returns \c nullptr.
  
  \see plottableAt, layoutElementAt
*/
template<class ItemType>
ItemType *NChartControl::itemAt(const QPointF &pos, bool onlySelectable) const
{
  ItemType *resultItem = 0;
  double resultDistance = mSelectionTolerance; // only regard clicks with distances smaller than mSelectionTolerance as selections, so initialize with that value
  
  foreach (NChartAbstractItem *item, mItems)
  {
    ItemType *currentItem = qobject_cast<ItemType*>(item);
    if (!currentItem || (onlySelectable && !currentItem->selectable())) // we could have also passed onlySelectable to the selectTest function, but checking here is faster, because we have access to NChartAbstractItem::selectable
      continue;
    if (!currentItem->clipToAxisRect() || currentItem->clipRect().contains(pos.toPoint())) // only consider clicks inside axis cliprect of the item if actually clipped to it
    {
      double currentDistance = currentItem->selectTest(pos, false);
      if (currentDistance >= 0 && currentDistance < resultDistance)
      {
        resultItem = currentItem;
        resultDistance = currentDistance;
      }
    }
  }
  
  return resultItem;
}



/* end of 'src/core.h' */


/* including file 'src/plottable1d.h'       */
/* modified 2021-03-29T02:30:44, size 25638 */

class NChartPlottableInterface1D
{
public:
  virtual ~NChartPlottableInterface1D() = default;
  // introduced pure virtual methods:
  virtual int dataRealCount() const = 0;
  virtual int dataCount() const = 0;
  virtual double dataMainKey(int index) const = 0;
  virtual double dataSortKey(int index) const = 0;
  virtual double dataMainValue(int index) const = 0;
  virtual NChartRange dataValueRange(int index) const = 0;
  virtual QPointF dataPixelPosition(int index) const = 0;
  virtual bool sortKeyIsMainKey() const = 0;
  virtual NChartDataSelection selectTestRect(const QRectF &rect, bool onlySelectable) const = 0;
  virtual int findBegin(double sortKey, bool expandedRange=true) const = 0;
  virtual int findEnd(double sortKey, bool expandedRange=true) const = 0;
};

template <class DataType>
class NChartAbstractPlottable1D : public NChartAbstractPlottable, public NChartPlottableInterface1D // no NCHART_LIB_DECL, template class ends up in header (cpp included below)
{
  // No Q_OBJECT macro due to template class
  
public:
  NChartAbstractPlottable1D(NChartAxis *keyAxis, NChartAxis *valueAxis);
  virtual ~NChartAbstractPlottable1D() Q_DECL_OVERRIDE;
  
  // virtual methods of 1d plottable interface:
  virtual int dataRealCount() const Q_DECL_OVERRIDE;
  virtual int dataCount() const Q_DECL_OVERRIDE;
  virtual double dataMainKey(int index) const Q_DECL_OVERRIDE;
  virtual double dataSortKey(int index) const Q_DECL_OVERRIDE;
  virtual double dataMainValue(int index) const Q_DECL_OVERRIDE;
  virtual NChartRange dataValueRange(int index) const Q_DECL_OVERRIDE;
  virtual QPointF dataPixelPosition(int index) const Q_DECL_OVERRIDE;
  virtual bool sortKeyIsMainKey() const Q_DECL_OVERRIDE;
  virtual NChartDataSelection selectTestRect(const QRectF &rect, bool onlySelectable) const Q_DECL_OVERRIDE;
  virtual int findBegin(double sortKey, bool expandedRange=true) const Q_DECL_OVERRIDE;
  virtual int findEnd(double sortKey, bool expandedRange=true) const Q_DECL_OVERRIDE;
  
  // reimplemented virtual methods:
  virtual double selectTest(const QPointF &pos, bool onlySelectable, QVariant *details=nullptr) const Q_DECL_OVERRIDE;
  virtual NChartPlottableInterface1D *interface1D() Q_DECL_OVERRIDE { return this; }
  
protected:
  // property members:
  QSharedPointer<NChartDataContainer<DataType> > mDataContainer;
  
  // helpers for subclasses:
  void getDataSegments(QList<NChartDataRange> &selectedSegments, QList<NChartDataRange> &unselectedSegments) const;
  void drawPolyline(NChartPainter *painter, const QVector<QPointF> &lineData) const;

private:
  Q_DISABLE_COPY(NChartAbstractPlottable1D)
  
};



// include implementation in header since it is a class template:
////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////// NChartPlottableInterface1D
////////////////////////////////////////////////////////////////////////////////////////////////////

/*! \class NChartPlottableInterface1D
  \brief Defines an abstract interface for one-dimensional plottables

  This class contains only pure virtual methods which define a common interface to the data
  of one-dimensional plottables.

  For example, it is implemented by the template class \ref NChartAbstractPlottable1D (the preferred
  base class for one-dimensional plottables). So if you use that template class as base class of
  your one-dimensional plottable, you won't have to care about implementing the 1d interface
  yourself.

  If your plottable doesn't derive from \ref NChartAbstractPlottable1D but still wants to provide a 1d
  interface (e.g. like \ref NChartErrorBars does), you should inherit from both \ref
  NChartAbstractPlottable and \ref NChartPlottableInterface1D and accordingly reimplement the pure
  virtual methods of the 1d interface, matching your data container. Also, reimplement \ref
  NChartAbstractPlottable::interface1D to return the \c this pointer.

  If you have a \ref NChartAbstractPlottable pointer, you can check whether it implements this
  interface by calling \ref NChartAbstractPlottable::interface1D and testing it for a non-zero return
  value. If it indeed implements this interface, you may use it to access the plottable's data
  without needing to know the exact type of the plottable or its data point type.
*/

/* start documentation of pure virtual functions */

/*! \fn virtual int NChartPlottableInterface1D::dataCount() const = 0;
  
  Returns the number of data points of the plottable.
*/

/*! \fn virtual NChartDataSelection NChartPlottableInterface1D::selectTestRect(const QRectF &rect, bool onlySelectable) const = 0;
  
  Returns a data selection containing all the data points of this plottable which are contained (or
  hit by) \a rect. This is used mainly in the selection rect interaction for data selection (\ref
  dataselection "data selection mechanism").
  
  If \a onlySelectable is true, an empty NChartDataSelection is returned if this plottable is not
  selectable (i.e. if \ref NChartAbstractPlottable::setSelectable is \ref NChart::stNone).
  
  \note \a rect must be a normalized rect (positive or zero width and height). This is especially
  important when using the rect of \ref NChartSelectionRect::accepted, which is not necessarily
  normalized. Use <tt>QRect::normalized()</tt> when passing a rect which might not be normalized.
*/

/*! \fn virtual double NChartPlottableInterface1D::dataMainKey(int index) const = 0
  
  Returns the main key of the data point at the given \a index.
  
  What the main key is, is defined by the plottable's data type. See the \ref
  qcpdatacontainer-datatype "NChartDataContainer DataType" documentation for details about this naming
  convention.
*/

/*! \fn virtual double NChartPlottableInterface1D::dataSortKey(int index) const = 0
  
  Returns the sort key of the data point at the given \a index.
  
  What the sort key is, is defined by the plottable's data type. See the \ref
  qcpdatacontainer-datatype "NChartDataContainer DataType" documentation for details about this naming
  convention.
*/

/*! \fn virtual double NChartPlottableInterface1D::dataMainValue(int index) const = 0
  
  Returns the main value of the data point at the given \a index.
  
  What the main value is, is defined by the plottable's data type. See the \ref
  qcpdatacontainer-datatype "NChartDataContainer DataType" documentation for details about this naming
  convention.
*/

/*! \fn virtual NChartRange NChartPlottableInterface1D::dataValueRange(int index) const = 0
  
  Returns the value range of the data point at the given \a index.
  
  What the value range is, is defined by the plottable's data type. See the \ref
  qcpdatacontainer-datatype "NChartDataContainer DataType" documentation for details about this naming
  convention.
*/

/*! \fn virtual QPointF NChartPlottableInterface1D::dataPixelPosition(int index) const = 0

  Returns the pixel position on the widget surface at which the data point at the given \a index
  appears.

  Usually this corresponds to the point of \ref dataMainKey/\ref dataMainValue, in pixel
  coordinates. However, depending on the plottable, this might be a different apparent position
  than just a coord-to-pixel transform of those values. For example, \ref NChartBars apparent data
  values can be shifted depending on their stacking, bar grouping or configured base value.
*/

/*! \fn virtual bool NChartPlottableInterface1D::sortKeyIsMainKey() const = 0

  Returns whether the sort key (\ref dataSortKey) is identical to the main key (\ref dataMainKey).

  What the sort and main keys are, is defined by the plottable's data type. See the \ref
  qcpdatacontainer-datatype "NChartDataContainer DataType" documentation for details about this naming
  convention.
*/

/*! \fn virtual int NChartPlottableInterface1D::findBegin(double sortKey, bool expandedRange) const = 0

  Returns the index of the data point with a (sort-)key that is equal to, just below, or just above
  \a sortKey. If \a expandedRange is true, the data point just below \a sortKey will be considered,
  otherwise the one just above.

  This can be used in conjunction with \ref findEnd to iterate over data points within a given key
  range, including or excluding the bounding data points that are just beyond the specified range.

  If \a expandedRange is true but there are no data points below \a sortKey, 0 is returned.

  If the container is empty, returns 0 (in that case, \ref findEnd will also return 0, so a loop
  using these methods will not iterate over the index 0).

  \see findEnd, NChartDataContainer::findBegin
*/

/*! \fn virtual int NChartPlottableInterface1D::findEnd(double sortKey, bool expandedRange) const = 0

  Returns the index one after the data point with a (sort-)key that is equal to, just above, or
  just below \a sortKey. If \a expandedRange is true, the data point just above \a sortKey will be
  considered, otherwise the one just below.

  This can be used in conjunction with \ref findBegin to iterate over data points within a given
  key range, including the bounding data points that are just below and above the specified range.

  If \a expandedRange is true but there are no data points above \a sortKey, the index just above the
  highest data point is returned.

  If the container is empty, returns 0.

  \see findBegin, NChartDataContainer::findEnd
*/

/* end documentation of pure virtual functions */


////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////// NChartAbstractPlottable1D
////////////////////////////////////////////////////////////////////////////////////////////////////

/*! \class NChartAbstractPlottable1D
  \brief A template base class for plottables with one-dimensional data

  This template class derives from \ref NChartAbstractPlottable and from the abstract interface \ref
  NChartPlottableInterface1D. It serves as a base class for all one-dimensional data (i.e. data with
  one key dimension), such as \ref NChartGraph and NChartCurve.

  The template parameter \a DataType is the type of the data points of this plottable (e.g. \ref
  NChartGraphData or \ref NChartCurveData). The main purpose of this base class is to provide the member
  \a mDataContainer (a shared pointer to a \ref NChartDataContainer "NChartDataContainer<DataType>") and
  implement the according virtual methods of the \ref NChartPlottableInterface1D, such that most
  subclassed plottables don't need to worry about this anymore.

  Further, it provides a convenience method for retrieving selected/unselected data segments via
  \ref getDataSegments. This is useful when subclasses implement their \ref draw method and need to
  draw selected segments with a different pen/brush than unselected segments (also see \ref
  NChartSelectionDecorator).

  This class implements basic functionality of \ref NChartAbstractPlottable::selectTest and \ref
  NChartPlottableInterface1D::selectTestRect, assuming point-like data points, based on the 1D data
  interface. In spite of that, most plottable subclasses will want to reimplement those methods
  again, to provide a more accurate hit test based on their specific data visualization geometry.
*/

/* start documentation of inline functions */

/*! \fn NChartPlottableInterface1D *NChartAbstractPlottable1D::interface1D()
  
  Returns a \ref NChartPlottableInterface1D pointer to this plottable, providing access to its 1D
  interface.
  
  \seebaseclassmethod
*/

/* end documentation of inline functions */

/*!
  Forwards \a keyAxis and \a valueAxis to the \ref NChartAbstractPlottable::NChartAbstractPlottable
  "NChartAbstractPlottable" constructor and allocates the \a mDataContainer.
*/
template <class DataType>
NChartAbstractPlottable1D<DataType>::NChartAbstractPlottable1D(NChartAxis *keyAxis, NChartAxis *valueAxis) :
  NChartAbstractPlottable(keyAxis, valueAxis),
  mDataContainer(new NChartDataContainer<DataType>)
{
}

template <class DataType>
NChartAbstractPlottable1D<DataType>::~NChartAbstractPlottable1D()
{
}

/*!
  \copydoc NChartPlottableInterface1D::dataCount
*/
template <class DataType>
int NChartAbstractPlottable1D<DataType>::dataCount() const
{
  return mDataContainer->size();
}

template <class DataType>
int NChartAbstractPlottable1D<DataType>::dataRealCount() const
{
  return mDataContainer->realSize();
}

/*!
  \copydoc NChartPlottableInterface1D::dataMainKey
*/
template <class DataType>
double NChartAbstractPlottable1D<DataType>::dataMainKey(int index) const
{
  if (index >= 0 && index < mDataContainer->size())
  {
    return (mDataContainer->constBegin()+index)->mainKey();
  } else
  {
    qDebug() << Q_FUNC_INFO << "Index out of bounds" << index;
    return 0;
  }
}

/*!
  \copydoc NChartPlottableInterface1D::dataSortKey
*/
template <class DataType>
double NChartAbstractPlottable1D<DataType>::dataSortKey(int index) const
{
  if (index >= 0 && index < mDataContainer->size())
  {
    return (mDataContainer->constBegin()+index)->sortKey();
  } else
  {
    qDebug() << Q_FUNC_INFO << "Index out of bounds" << index;
    return 0;
  }
}

/*!
  \copydoc NChartPlottableInterface1D::dataMainValue
*/
template <class DataType>
double NChartAbstractPlottable1D<DataType>::dataMainValue(int index) const
{
  if (index >= 0 && index < mDataContainer->size())
  {
    return (mDataContainer->constBegin()+index)->mainValue();
  } else
  {
    qDebug() << Q_FUNC_INFO << "Index out of bounds" << index;
    return 0;
  }
}

/*!
  \copydoc NChartPlottableInterface1D::dataValueRange
*/
template <class DataType>
NChartRange NChartAbstractPlottable1D<DataType>::dataValueRange(int index) const
{
  if (index >= 0 && index < mDataContainer->size())
  {
    return (mDataContainer->constBegin()+index)->valueRange();
  } else
  {
    qDebug() << Q_FUNC_INFO << "Index out of bounds" << index;
    return NChartRange(0, 0);
  }
}

/*!
  \copydoc NChartPlottableInterface1D::dataPixelPosition
*/
template <class DataType>
QPointF NChartAbstractPlottable1D<DataType>::dataPixelPosition(int index) const
{
  if (index >= 0 && index < mDataContainer->size())
  {
    const typename NChartDataContainer<DataType>::const_iterator it = mDataContainer->constBegin()+index;
    return coordsToPixels(it->mainKey(), it->mainValue());
  } else
  {
    qDebug() << Q_FUNC_INFO << "Index out of bounds" << index;
    return QPointF();
  }
}

/*!
  \copydoc NChartPlottableInterface1D::sortKeyIsMainKey
*/
template <class DataType>
bool NChartAbstractPlottable1D<DataType>::sortKeyIsMainKey() const
{
  return DataType::sortKeyIsMainKey();
}

/*!
  Implements a rect-selection algorithm assuming the data (accessed via the 1D data interface) is
  point-like. Most subclasses will want to reimplement this method again, to provide a more
  accurate hit test based on the true data visualization geometry.

  \seebaseclassmethod
*/
template <class DataType>
NChartDataSelection NChartAbstractPlottable1D<DataType>::selectTestRect(const QRectF &rect, bool onlySelectable) const
{
  NChartDataSelection result;
  if ((onlySelectable && mSelectable == NChart::stNone) || mDataContainer->isEmpty())
    return result;
  if (!mKeyAxis || !mValueAxis)
    return result;
  
  // convert rect given in pixels to ranges given in plot coordinates:
  double key1, value1, key2, value2;
  pixelsToCoords(rect.topLeft(), key1, value1);
  pixelsToCoords(rect.bottomRight(), key2, value2);
  NChartRange keyRange(key1, key2); // NChartRange normalizes internally so we don't have to care about whether key1 < key2
  NChartRange valueRange(value1, value2);
  typename NChartDataContainer<DataType>::const_iterator begin = mDataContainer->constBegin();
  typename NChartDataContainer<DataType>::const_iterator end = mDataContainer->constEnd();
  if (DataType::sortKeyIsMainKey()) // we can assume that data is sorted by main key, so can reduce the searched key interval:
  {
    begin = mDataContainer->findBegin(keyRange.lower, false);
    end = mDataContainer->findEnd(keyRange.upper, false);
  }
  if (begin == end)
    return result;
  
  int currentSegmentBegin = -1; // -1 means we're currently not in a segment that's contained in rect
  for (typename NChartDataContainer<DataType>::const_iterator it=begin; it!=end; ++it)
  {
    if (currentSegmentBegin == -1)
    {
      if (valueRange.contains(it->mainValue()) && keyRange.contains(it->mainKey())) // start segment
        currentSegmentBegin = int(it-mDataContainer->constBegin());
    } else if (!valueRange.contains(it->mainValue()) || !keyRange.contains(it->mainKey())) // segment just ended
    {
      result.addDataRange(NChartDataRange(currentSegmentBegin, int(it-mDataContainer->constBegin())), false);
      currentSegmentBegin = -1;
    }
  }
  // process potential last segment:
  if (currentSegmentBegin != -1)
    result.addDataRange(NChartDataRange(currentSegmentBegin, int(end-mDataContainer->constBegin())), false);
  
  result.simplify();
  return result;
}

/*!
  \copydoc NChartPlottableInterface1D::findBegin
*/
template <class DataType>
int NChartAbstractPlottable1D<DataType>::findBegin(double sortKey, bool expandedRange) const
{
  return int(mDataContainer->findBegin(sortKey, expandedRange)-mDataContainer->constBegin());
}

/*!
  \copydoc NChartPlottableInterface1D::findEnd
*/
template <class DataType>
int NChartAbstractPlottable1D<DataType>::findEnd(double sortKey, bool expandedRange) const
{
  return int(mDataContainer->findEnd(sortKey, expandedRange)-mDataContainer->constBegin());
}

/*!
  Implements a point-selection algorithm assuming the data (accessed via the 1D data interface) is
  point-like. Most subclasses will want to reimplement this method again, to provide a more
  accurate hit test based on the true data visualization geometry.

  If \a details is not 0, it will be set to a \ref NChartDataSelection, describing the closest data point
  to \a pos.
  
  \seebaseclassmethod
*/
template <class DataType>
double NChartAbstractPlottable1D<DataType>::selectTest(const QPointF &pos, bool onlySelectable, QVariant *details) const
{
  if ((onlySelectable && mSelectable == NChart::stNone) || mDataContainer->isEmpty())
    return -1;
  if (!mKeyAxis || !mValueAxis)
    return -1;
  
  NChartDataSelection selectionResult;
  double minDistSqr = (std::numeric_limits<double>::max)();
  int minDistIndex = mDataContainer->size();
  
  typename NChartDataContainer<DataType>::const_iterator begin = mDataContainer->constBegin();
  typename NChartDataContainer<DataType>::const_iterator end = mDataContainer->constEnd();
  if (DataType::sortKeyIsMainKey()) // we can assume that data is sorted by main key, so can reduce the searched key interval:
  {
    // determine which key range comes into question, taking selection tolerance around pos into account:
    double posKeyMin, posKeyMax, dummy;
    pixelsToCoords(pos-QPointF(mParentPlot->selectionTolerance(), mParentPlot->selectionTolerance()), posKeyMin, dummy);
    pixelsToCoords(pos+QPointF(mParentPlot->selectionTolerance(), mParentPlot->selectionTolerance()), posKeyMax, dummy);
    if (posKeyMin > posKeyMax)
      qSwap(posKeyMin, posKeyMax);
    begin = mDataContainer->findBegin(posKeyMin, true);
    end = mDataContainer->findEnd(posKeyMax, true);
  }
  if (begin == end)
    return -1;
  NChartRange keyRange(mKeyAxis->range());
  NChartRange valueRange(mValueAxis->range());
  for (typename NChartDataContainer<DataType>::const_iterator it=begin; it!=end; ++it)
  {
    const double mainKey = it->mainKey();
    const double mainValue = it->mainValue();
    if (keyRange.contains(mainKey) && valueRange.contains(mainValue)) // make sure data point is inside visible range, for speedup in cases where sort key isn't main key and we iterate over all points
    {
      const double currentDistSqr = NChartVector2D(coordsToPixels(mainKey, mainValue)-pos).lengthSquared();
      if (currentDistSqr < minDistSqr)
      {
        minDistSqr = currentDistSqr;
        minDistIndex = int(it-mDataContainer->constBegin());
      }
    }
  }
  if (minDistIndex != mDataContainer->size())
    selectionResult.addDataRange(NChartDataRange(minDistIndex, minDistIndex+1), false);
  
  selectionResult.simplify();
  if (details)
    details->setValue(selectionResult);
  return qSqrt(minDistSqr);
}

/*!
  Splits all data into selected and unselected segments and outputs them via \a selectedSegments
  and \a unselectedSegments, respectively.

  This is useful when subclasses implement their \ref draw method and need to draw selected
  segments with a different pen/brush than unselected segments (also see \ref
  NChartSelectionDecorator).

  \see setSelection
*/
template <class DataType>
void NChartAbstractPlottable1D<DataType>::getDataSegments(QList<NChartDataRange> &selectedSegments, QList<NChartDataRange> &unselectedSegments) const
{
  selectedSegments.clear();
  unselectedSegments.clear();
  if (mSelectable == NChart::stWhole) // stWhole selection type draws the entire plottable with selected style if mSelection isn't empty
  {
    if (selected())
      selectedSegments << NChartDataRange(0, dataCount());
    else
      unselectedSegments << NChartDataRange(0, dataCount());
  } else
  {
    NChartDataSelection sel(selection());
    sel.simplify();
    selectedSegments = sel.dataRanges();
    unselectedSegments = sel.inverse(NChartDataRange(0, dataCount())).dataRanges();
  }
}

/*!
  A helper method which draws a line with the passed \a painter, according to the pixel data in \a
  lineData. NaN points create gaps in the line, as expected from NChartControl's plottables (this is
  the main difference to QPainter's regular drawPolyline, which handles NaNs by lagging or
  crashing).

  Further it uses a faster line drawing technique based on \ref NChartPainter::drawLine rather than \c
  QPainter::drawPolyline if the configured \ref NChartControl::setPlottingHints() and \a painter
  style allows.
*/
//khko_check
template <class DataType>
void NChartAbstractPlottable1D<DataType>::drawPolyline(NChartPainter *painter, const QVector<QPointF> &lineData) const
{
  // if drawing lines in plot (instead of PDF), reduce 1px lines to cosmetic, because at least in
  // Qt6 drawing of "1px" width lines is much slower even though it has same appearance apart from
  // High-DPI. In High-DPI cases people must set a pen width slightly larger than 1.0 to get
  // correct DPI scaling of width, but of course with performance penalty.
  if (!painter->modes().testFlag(NChartPainter::pmVectorized) &&
      qFuzzyCompare(painter->pen().widthF(), 1.0))
  {
    QPen newPen = painter->pen();
    newPen.setWidth(0);
    painter->setPen(newPen);
  }

  // if drawing solid line and not in PDF, use much faster line drawing instead of polyline:
  //khko_mod
  if(painter->pen().style() == Qt::SolidLine)
  //khko_del if (mParentPlot->plottingHints().testFlag(NChart::phFastPolylines) &&
  //khko_del     painter->pen().style() == Qt::SolidLine &&
  //khko_del     !painter->modes().testFlag(NChartPainter::pmVectorized) &&
  //khko_del     !painter->modes().testFlag(NChartPainter::pmNoCaching))
  {
    int i = 0;
    bool lastIsNan = false;
    const int lineDataSize = lineData.size();
    while (i < lineDataSize && (qIsNaN(lineData.at(i).y()) || qIsNaN(lineData.at(i).x()))) // make sure first point is not NaN
      ++i;
    ++i; // because drawing works in 1 point retrospect
    while (i < lineDataSize)
    {
      if (!qIsNaN(lineData.at(i).y()) && !qIsNaN(lineData.at(i).x())) // NaNs create a gap in the line
      {
        if (!lastIsNan)
          painter->drawLine(lineData.at(i-1), lineData.at(i));
        else
          lastIsNan = false;
      } else
        lastIsNan = true;
      ++i;
    }
  }
  else
  {
    int segmentStart = 0;
    int i = 0;
    const int lineDataSize = lineData.size();
    while (i < lineDataSize)
    {
      if (qIsNaN(lineData.at(i).y()) || qIsNaN(lineData.at(i).x()) || qIsInf(lineData.at(i).y())) // NaNs create a gap in the line. Also filter Infs which make drawPolyline block
      {
        painter->drawPolyline(lineData.constData()+segmentStart, i-segmentStart); // i, because we don't want to include the current NaN point
        segmentStart = i+1;
      }
      ++i;
    }
    // draw last segment:
    painter->drawPolyline(lineData.constData()+segmentStart, lineDataSize-segmentStart);
  }
}


/* end of 'src/plottable1d.h' */


/* including file 'src/colorgradient.h'    */
/* modified 2021-03-29T02:30:44, size 7262 */

class NCHART_LIB_DECL NChartColorGradient
{
  Q_GADGET
public:
  /*!
    Defines the color spaces in which color interpolation between gradient stops can be performed.
    
    \see setColorInterpolation
  */
  enum ColorInterpolation { ciRGB  ///< Color channels red, green and blue are linearly interpolated
                            ,ciHSV ///< Color channels hue, saturation and value are linearly interpolated (The hue is interpolated over the shortest angle distance)
                          };
  Q_ENUMS(ColorInterpolation)
  
  /*!
    Defines how NaN data points shall appear in the plot.
    
    \see setNanHandling, setNanColor
  */
  enum NanHandling { nhNone ///< NaN data points are not explicitly handled and shouldn't occur in the data (this gives slight performance improvement)
                     ,nhLowestColor  ///< NaN data points appear as the lowest color defined in this NChartColorGradient
                     ,nhHighestColor ///< NaN data points appear as the highest color defined in this NChartColorGradient
                     ,nhTransparent ///< NaN data points appear transparent
                     ,nhNanColor ///< NaN data points appear as the color defined with \ref setNanColor
                   };
  Q_ENUMS(NanHandling)
  
  /*!
    Defines the available presets that can be loaded with \ref loadPreset. See the documentation
    there for an image of the presets.
  */
  enum GradientPreset { gpGrayscale  ///< Continuous lightness from black to white (suited for non-biased data representation)
                        ,gpHot       ///< Continuous lightness from black over firey colors to white (suited for non-biased data representation)
                        ,gpCold      ///< Continuous lightness from black over icey colors to white (suited for non-biased data representation)
                        ,gpNight     ///< Continuous lightness from black over weak blueish colors to white (suited for non-biased data representation)
                        ,gpCandy     ///< Blue over pink to white
                        ,gpGeography ///< Colors suitable to represent different elevations on geographical maps
                        ,gpIon       ///< Half hue spectrum from black over purple to blue and finally green (creates banding illusion but allows more precise magnitude estimates)
                        ,gpThermal   ///< Colors suitable for thermal imaging, ranging from dark blue over purple to orange, yellow and white
                        ,gpPolar     ///< Colors suitable to emphasize polarity around the center, with blue for negative, black in the middle and red for positive values
                        ,gpSpectrum  ///< An approximation of the visible light spectrum (creates banding illusion but allows more precise magnitude estimates)
                        ,gpJet       ///< Hue variation similar to a spectrum, often used in numerical visualization (creates banding illusion but allows more precise magnitude estimates)
                        ,gpHues      ///< Full hue cycle, with highest and lowest color red (suitable for periodic data, such as angles and phases, see \ref setPeriodic)
                      };
  Q_ENUMS(GradientPreset)
  
  NChartColorGradient();
  NChartColorGradient(GradientPreset preset);
  bool operator==(const NChartColorGradient &other) const;
  bool operator!=(const NChartColorGradient &other) const { return !(*this == other); }
  
  // getters:
  int levelCount() const { return mLevelCount; }
  QMap<double, QColor> colorStops() const { return mColorStops; }
  ColorInterpolation colorInterpolation() const { return mColorInterpolation; }
  NanHandling nanHandling() const { return mNanHandling; }
  QColor nanColor() const { return mNanColor; }
  bool periodic() const { return mPeriodic; }
  
  // setters:
  void setLevelCount(int n);
  void setColorStops(const QMap<double, QColor> &colorStops);
  void setColorStopAt(double position, const QColor &color);
  void setColorInterpolation(ColorInterpolation interpolation);
  void setNanHandling(NanHandling handling);
  void setNanColor(const QColor &color);
  void setPeriodic(bool enabled);
  
  // non-property methods:
  void colorize(const double *data, const NChartRange &range, QRgb *scanLine, int n, int dataIndexFactor=1, bool logarithmic=false);
  void colorize(const double *data, const unsigned char *alpha, const NChartRange &range, QRgb *scanLine, int n, int dataIndexFactor=1, bool logarithmic=false);
  QRgb color(double position, const NChartRange &range, bool logarithmic=false);
  void loadPreset(GradientPreset preset);
  void clearColorStops();
  NChartColorGradient inverted() const;
  
protected:
  // property members:
  int mLevelCount;
  QMap<double, QColor> mColorStops;
  ColorInterpolation mColorInterpolation;
  NanHandling mNanHandling;
  QColor mNanColor;
  bool mPeriodic;
  
  // non-property members:
  QVector<QRgb> mColorBuffer; // have colors premultiplied with alpha (for usage with QImage::Format_ARGB32_Premultiplied)
  bool mColorBufferInvalidated;
  
  // non-virtual methods:
  bool stopsUseAlpha() const;
  void updateColorBuffer();
};
Q_DECLARE_METATYPE(NChartColorGradient::ColorInterpolation)
Q_DECLARE_METATYPE(NChartColorGradient::NanHandling)
Q_DECLARE_METATYPE(NChartColorGradient::GradientPreset)

/* end of 'src/colorgradient.h' */


/* including file 'src/selectiondecorator-bracket.h' */
/* modified 2021-03-29T02:30:44, size 4458           */

class NCHART_LIB_DECL NChartSelectionDecoratorBracket : public NChartSelectionDecorator
{
  Q_GADGET
public:
  
  /*!
    Defines which shape is drawn at the boundaries of selected data ranges.
    
    Some of the bracket styles further allow specifying a height and/or width, see \ref
    setBracketHeight and \ref setBracketWidth.
  */
  enum BracketStyle { bsSquareBracket ///< A square bracket is drawn.
                      ,bsHalfEllipse   ///< A half ellipse is drawn. The size of the ellipse is given by the bracket width/height properties.
                      ,bsEllipse       ///< An ellipse is drawn. The size of the ellipse is given by the bracket width/height properties.
                      ,bsPlus         ///< A plus is drawn.
                      ,bsUserStyle    ///< Start custom bracket styles at this index when subclassing and reimplementing \ref drawBracket.
  };
  Q_ENUMS(BracketStyle)
  
  NChartSelectionDecoratorBracket();
  virtual ~NChartSelectionDecoratorBracket() Q_DECL_OVERRIDE;
  
  // getters:
  QPen bracketPen() const { return mBracketPen; }
  QBrush bracketBrush() const { return mBracketBrush; }
  int bracketWidth() const { return mBracketWidth; }
  int bracketHeight() const { return mBracketHeight; }
  BracketStyle bracketStyle() const { return mBracketStyle; }
  bool tangentToData() const { return mTangentToData; }
  int tangentAverage() const { return mTangentAverage; }
  
  // setters:
  void setBracketPen(const QPen &pen);
  void setBracketBrush(const QBrush &brush);
  void setBracketWidth(int width);
  void setBracketHeight(int height);
  void setBracketStyle(BracketStyle style);
  void setTangentToData(bool enabled);
  void setTangentAverage(int pointCount);
  
  // introduced virtual methods:
  virtual void drawBracket(NChartPainter *painter, int direction) const;
  
  // virtual methods:
  virtual void drawDecoration(NChartPainter *painter, NChartDataSelection selection) Q_DECL_OVERRIDE;
  
protected:
  // property members:
  QPen mBracketPen;
  QBrush mBracketBrush;
  int mBracketWidth;
  int mBracketHeight;
  BracketStyle mBracketStyle;
  bool mTangentToData;
  int mTangentAverage;
  
  // non-virtual methods:
  double getTangentAngle(const NChartPlottableInterface1D *interface1d, int dataIndex, int direction) const;
  QPointF getPixelCoordinates(const NChartPlottableInterface1D *interface1d, int dataIndex) const;
  
};
Q_DECLARE_METATYPE(NChartSelectionDecoratorBracket::BracketStyle)

/* end of 'src/selectiondecorator-bracket.h' */


/* including file 'src/layoutelements/layoutelement-axisrect.h' */
/* modified 2021-03-29T02:30:44, size 7529                      */

class NCHART_LIB_DECL NChartAxisRect : public NChartLayoutElement
{
  Q_OBJECT
  /// \cond INCLUDE_QPROPERTIES
  Q_PROPERTY(QPixmap background READ background WRITE setBackground)
  Q_PROPERTY(bool backgroundScaled READ backgroundScaled WRITE setBackgroundScaled)
  Q_PROPERTY(Qt::AspectRatioMode backgroundScaledMode READ backgroundScaledMode WRITE setBackgroundScaledMode)
  Q_PROPERTY(Qt::Orientations rangeDrag READ rangeDrag WRITE setRangeDrag)
  Q_PROPERTY(Qt::Orientations rangeZoom READ rangeZoom WRITE setRangeZoom)
  /// \endcond
public:
  explicit NChartAxisRect(NChartControl *parentPlot, bool setupDefaultAxes=true);
  virtual ~NChartAxisRect() Q_DECL_OVERRIDE;
  
  // getters:
  QPixmap background() const { return mBackgroundPixmap; }
  QBrush backgroundBrush() const { return mBackgroundBrush; }
  bool backgroundScaled() const { return mBackgroundScaled; }
  Qt::AspectRatioMode backgroundScaledMode() const { return mBackgroundScaledMode; }
  Qt::Orientations rangeDrag() const { return mRangeDrag; }
  Qt::Orientations rangeZoom() const { return mRangeZoom; }
  NChartAxis *rangeDragAxis(Qt::Orientation orientation);
  NChartAxis *rangeZoomAxis(Qt::Orientation orientation);
  QList<NChartAxis*> rangeDragAxes(Qt::Orientation orientation);
  QList<NChartAxis*> rangeZoomAxes(Qt::Orientation orientation);
  double rangeZoomFactor(Qt::Orientation orientation);
  
  // setters:
  void setBackground(const QPixmap &pm);
  void setBackground(const QPixmap &pm, bool scaled, Qt::AspectRatioMode mode=Qt::KeepAspectRatioByExpanding);
  void setBackground(const QBrush &brush);
  void setBackgroundScaled(bool scaled);
  void setBackgroundScaledMode(Qt::AspectRatioMode mode);
  void setRangeDrag(Qt::Orientations orientations);
  void setRangeZoom(Qt::Orientations orientations);
  void setRangeDragAxes(NChartAxis *horizontal, NChartAxis *vertical);
  void setRangeDragAxes(QList<NChartAxis*> axes);
  void setRangeDragAxes(QList<NChartAxis*> horizontal, QList<NChartAxis*> vertical);
  void setRangeZoomAxes(NChartAxis *horizontal, NChartAxis *vertical);
  void setRangeZoomAxes(QList<NChartAxis*> axes);
  void setRangeZoomAxes(QList<NChartAxis*> horizontal, QList<NChartAxis*> vertical);
  void setRangeZoomFactor(double horizontalFactor, double verticalFactor);
  void setRangeZoomFactor(double factor);
  
  // non-property methods:
  int axisCount(NChartAxis::AxisType type) const;
  NChartAxis *axis(NChartAxis::AxisType type, int index=0) const;
  QList<NChartAxis*> axes(NChartAxis::AxisTypes types) const;
  QList<NChartAxis*> axes() const;
  NChartAxis *addAxis(NChartAxis::AxisType type, NChartAxis *axis=nullptr);
  QList<NChartAxis*> addAxes(NChartAxis::AxisTypes types);
  bool removeAxis(NChartAxis *axis);
  NChartLayoutInset *insetLayout() const { return mInsetLayout; }
  
  void zoom(const QRectF &pixelRect);
  void zoom(const QRectF &pixelRect, const QList<NChartAxis*> &affectedAxes);
  void setupFullAxesBox(bool connectRanges=false);
  QList<NChartAbstractPlottable*> plottables() const;
  QList<NChartGraph*> graphs() const;
  QList<NChartAbstractItem*> items() const;
  
  // read-only interface imitating a QRect:
  int left() const { return mRect.left(); }
  int right() const { return mRect.right(); }
  int top() const { return mRect.top(); }
  int bottom() const { return mRect.bottom(); }
  int width() const { return mRect.width(); }
  int height() const { return mRect.height(); }
  QSize size() const { return mRect.size(); }
  QPoint topLeft() const { return mRect.topLeft(); }
  QPoint topRight() const { return mRect.topRight(); }
  QPoint bottomLeft() const { return mRect.bottomLeft(); }
  QPoint bottomRight() const { return mRect.bottomRight(); }
  QPoint center() const { return mRect.center(); }
  
  // reimplemented virtual methods:
  virtual void update(UpdatePhase phase) Q_DECL_OVERRIDE;
  virtual QList<NChartLayoutElement*> elements(bool recursive) const Q_DECL_OVERRIDE;

protected:
  // property members:
  QBrush mBackgroundBrush;
  QPixmap mBackgroundPixmap;
  QPixmap mScaledBackgroundPixmap;
  bool mBackgroundScaled;
  Qt::AspectRatioMode mBackgroundScaledMode;
  NChartLayoutInset *mInsetLayout;
  Qt::Orientations mRangeDrag, mRangeZoom;
  QList<QPointer<NChartAxis> > mRangeDragHorzAxis, mRangeDragVertAxis;
  QList<QPointer<NChartAxis> > mRangeZoomHorzAxis, mRangeZoomVertAxis;
  double mRangeZoomFactorHorz, mRangeZoomFactorVert;
  bool mIsPressed = false;
  double mMouseLastX = 0;
  double mMouseLastY = 0;
  // non-property members:
  QList<NChartRange> mDragStartHorzRange, mDragStartVertRange;
  NChart::AntialiasedElements mAADragBackup, mNotAADragBackup;
  bool mDragging;
  QHash<NChartAxis::AxisType, QList<NChartAxis*> > mAxes;
  
  // reimplemented virtual methods:
  virtual void applyDefaultAntialiasingHint(NChartPainter *painter) const Q_DECL_OVERRIDE;
  virtual void draw(NChartPainter *painter) Q_DECL_OVERRIDE;
  virtual int calculateAutoMargin(NChart::MarginSide side) Q_DECL_OVERRIDE;
  virtual void layoutChanged() Q_DECL_OVERRIDE;
  // events:
  virtual void mousePressEvent(QMouseEvent *event, const QVariant &details) Q_DECL_OVERRIDE;
  virtual void mouseMoveEvent(QMouseEvent *event, const QPointF &startPos) Q_DECL_OVERRIDE;
  virtual void mouseReleaseEvent(QMouseEvent *event, const QPointF &startPos) Q_DECL_OVERRIDE;
  virtual void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;
  
  // non-property methods:
  void drawBackground(NChartPainter *painter);
  void updateAxesOffset(NChartAxis::AxisType type);
  
private:
  Q_DISABLE_COPY(NChartAxisRect)
  
  friend class NChartControl;
};


/* end of 'src/layoutelements/layoutelement-axisrect.h' */


/* including file 'src/layoutelements/layoutelement-legend.h' */
/* modified 2021-03-29T02:30:44, size 10425                   */

class NCHART_LIB_DECL NChartAbstractLegendItem : public NChartLayoutElement
{
  Q_OBJECT
  /// \cond INCLUDE_QPROPERTIES
  Q_PROPERTY(NChartLegend* parentLegend READ parentLegend)
  Q_PROPERTY(QFont font READ font WRITE setFont)
  Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor)
  Q_PROPERTY(QFont selectedFont READ selectedFont WRITE setSelectedFont)
  Q_PROPERTY(QColor selectedTextColor READ selectedTextColor WRITE setSelectedTextColor)
  Q_PROPERTY(bool selectable READ selectable WRITE setSelectable NOTIFY selectionChanged)
  Q_PROPERTY(bool selected READ selected WRITE setSelected NOTIFY selectableChanged)
  /// \endcond
public:
  explicit NChartAbstractLegendItem(NChartLegend *parent);
  
  // getters:
  NChartLegend *parentLegend() const { return mParentLegend; }
  QFont font() const { return mFont; }
  QColor textColor() const { return mTextColor; }
  QFont selectedFont() const { return mSelectedFont; }
  QColor selectedTextColor() const { return mSelectedTextColor; }
  bool selectable() const { return mSelectable; }
  bool selected() const { return mSelected; }
  
  // setters:
  void setFont(const QFont &font);
  void setTextColor(const QColor &color);
  void setSelectedFont(const QFont &font);
  void setSelectedTextColor(const QColor &color);
  Q_SLOT void setSelectable(bool selectable);
  Q_SLOT void setSelected(bool selected);
  
  // reimplemented virtual methods:
  virtual double selectTest(const QPointF &pos, bool onlySelectable, QVariant *details=nullptr) const Q_DECL_OVERRIDE;
  
signals:
  void selectionChanged(bool selected);
  void selectableChanged(bool selectable);
  
protected:
  // property members:
  NChartLegend *mParentLegend;
  QFont mFont;
  QColor mTextColor;
  QFont mSelectedFont;
  QColor mSelectedTextColor;
  bool mSelectable, mSelected;
  
  // reimplemented virtual methods:
  virtual NChart::Interaction selectionCategory() const Q_DECL_OVERRIDE;
  virtual void applyDefaultAntialiasingHint(NChartPainter *painter) const Q_DECL_OVERRIDE;
  virtual QRect clipRect() const Q_DECL_OVERRIDE;
  virtual void draw(NChartPainter *painter) Q_DECL_OVERRIDE = 0;
  // events:
  virtual void selectEvent(QMouseEvent *event, bool additive, const QVariant &details, bool *selectionStateChanged) Q_DECL_OVERRIDE;
  virtual void deselectEvent(bool *selectionStateChanged) Q_DECL_OVERRIDE;
  
private:
  Q_DISABLE_COPY(NChartAbstractLegendItem)
  
  friend class NChartLegend;
};


class NCHART_LIB_DECL NChartPlottableLegendItem : public NChartAbstractLegendItem
{
  Q_OBJECT
public:
  NChartPlottableLegendItem(NChartLegend *parent, NChartAbstractPlottable *plottable);
  
  // getters:
  NChartAbstractPlottable *plottable() { return mPlottable; }
  
protected:
  // property members:
  NChartAbstractPlottable *mPlottable;
  
  // reimplemented virtual methods:
  virtual void draw(NChartPainter *painter) Q_DECL_OVERRIDE;
  virtual QSize minimumOuterSizeHint() const Q_DECL_OVERRIDE;
  
  // non-virtual methods:
  QPen getIconBorderPen() const;
  QColor getTextColor() const;
  QFont getFont() const;
};


class NCHART_LIB_DECL NChartLegend : public NChartLayoutGrid
{
  Q_OBJECT
  /// \cond INCLUDE_QPROPERTIES
  Q_PROPERTY(QPen borderPen READ borderPen WRITE setBorderPen)
  Q_PROPERTY(QBrush brush READ brush WRITE setBrush)
  Q_PROPERTY(QFont font READ font WRITE setFont)
  Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor)
  Q_PROPERTY(QSize iconSize READ iconSize WRITE setIconSize)
  Q_PROPERTY(int iconTextPadding READ iconTextPadding WRITE setIconTextPadding)
  Q_PROPERTY(QPen iconBorderPen READ iconBorderPen WRITE setIconBorderPen)
  Q_PROPERTY(SelectableParts selectableParts READ selectableParts WRITE setSelectableParts NOTIFY selectionChanged)
  Q_PROPERTY(SelectableParts selectedParts READ selectedParts WRITE setSelectedParts NOTIFY selectableChanged)
  Q_PROPERTY(QPen selectedBorderPen READ selectedBorderPen WRITE setSelectedBorderPen)
  Q_PROPERTY(QPen selectedIconBorderPen READ selectedIconBorderPen WRITE setSelectedIconBorderPen)
  Q_PROPERTY(QBrush selectedBrush READ selectedBrush WRITE setSelectedBrush)
  Q_PROPERTY(QFont selectedFont READ selectedFont WRITE setSelectedFont)
  Q_PROPERTY(QColor selectedTextColor READ selectedTextColor WRITE setSelectedTextColor)
  /// \endcond
public:
  /*!
    Defines the selectable parts of a legend
    
    \see setSelectedParts, setSelectableParts
  */
  enum SelectablePart { spNone        = 0x000 ///< <tt>0x000</tt> None
                        ,spLegendBox  = 0x001 ///< <tt>0x001</tt> The legend box (frame)
                        ,spItems      = 0x002 ///< <tt>0x002</tt> Legend items individually (see \ref selectedItems)
                      };
  Q_ENUMS(SelectablePart)
  Q_FLAGS(SelectableParts)
  Q_DECLARE_FLAGS(SelectableParts, SelectablePart)
  
  explicit NChartLegend();
  virtual ~NChartLegend() Q_DECL_OVERRIDE;
  
  // getters:
  QPen borderPen() const { return mBorderPen; }
  QBrush brush() const { return mBrush; }
  QFont font() const { return mFont; }
  QColor textColor() const { return mTextColor; }
  QSize iconSize() const { return mIconSize; }
  int iconTextPadding() const { return mIconTextPadding; }
  QPen iconBorderPen() const { return mIconBorderPen; }
  SelectableParts selectableParts() const { return mSelectableParts; }
  SelectableParts selectedParts() const;
  QPen selectedBorderPen() const { return mSelectedBorderPen; }
  QPen selectedIconBorderPen() const { return mSelectedIconBorderPen; }
  QBrush selectedBrush() const { return mSelectedBrush; }
  QFont selectedFont() const { return mSelectedFont; }
  QColor selectedTextColor() const { return mSelectedTextColor; }
  
  // setters:
  void setBorderPen(const QPen &pen);
  void setBrush(const QBrush &brush);
  void setFont(const QFont &font);
  void setTextColor(const QColor &color);
  void setIconSize(const QSize &size);
  void setIconSize(int width, int height);
  void setIconTextPadding(int padding);
  void setIconBorderPen(const QPen &pen);
  Q_SLOT void setSelectableParts(const SelectableParts &selectableParts);
  Q_SLOT void setSelectedParts(const SelectableParts &selectedParts);
  void setSelectedBorderPen(const QPen &pen);
  void setSelectedIconBorderPen(const QPen &pen);
  void setSelectedBrush(const QBrush &brush);
  void setSelectedFont(const QFont &font);
  void setSelectedTextColor(const QColor &color);
  
  // reimplemented virtual methods:
  virtual double selectTest(const QPointF &pos, bool onlySelectable, QVariant *details=nullptr) const Q_DECL_OVERRIDE;
  
  // non-virtual methods:
  NChartAbstractLegendItem *item(int index) const;
  NChartPlottableLegendItem *itemWithPlottable(const NChartAbstractPlottable *plottable) const;
  int itemCount() const;
  bool hasItem(NChartAbstractLegendItem *item) const;
  bool hasItemWithPlottable(const NChartAbstractPlottable *plottable) const;
  bool addItem(NChartAbstractLegendItem *item);
  bool removeItem(int index);
  bool removeItem(NChartAbstractLegendItem *item);
  void clearItems();
  QList<NChartAbstractLegendItem*> selectedItems() const;
  
signals:
  void selectionChanged(NChartLegend::SelectableParts parts);
  void selectableChanged(NChartLegend::SelectableParts parts);
  
protected:
  // property members:
  QPen mBorderPen, mIconBorderPen;
  QBrush mBrush;
  QFont mFont;
  QColor mTextColor;
  QSize mIconSize;
  int mIconTextPadding;
  SelectableParts mSelectedParts, mSelectableParts;
  QPen mSelectedBorderPen, mSelectedIconBorderPen;
  QBrush mSelectedBrush;
  QFont mSelectedFont;
  QColor mSelectedTextColor;
  
  // reimplemented virtual methods:
  virtual void parentPlotInitialized(NChartControl *parentPlot) Q_DECL_OVERRIDE;
  virtual NChart::Interaction selectionCategory() const Q_DECL_OVERRIDE;
  virtual void applyDefaultAntialiasingHint(NChartPainter *painter) const Q_DECL_OVERRIDE;
  virtual void draw(NChartPainter *painter) Q_DECL_OVERRIDE;
  // events:
  virtual void selectEvent(QMouseEvent *event, bool additive, const QVariant &details, bool *selectionStateChanged) Q_DECL_OVERRIDE;
  virtual void deselectEvent(bool *selectionStateChanged) Q_DECL_OVERRIDE;
  
  // non-virtual methods:
  QPen getBorderPen() const;
  QBrush getBrush() const;
  
private:
  Q_DISABLE_COPY(NChartLegend)
  
  friend class NChartControl;
  friend class NChartAbstractLegendItem;
};
Q_DECLARE_OPERATORS_FOR_FLAGS(NChartLegend::SelectableParts)
Q_DECLARE_METATYPE(NChartLegend::SelectablePart)

/* end of 'src/layoutelements/layoutelement-legend.h' */


/* including file 'src/layoutelements/layoutelement-textelement.h' */
/* modified 2021-03-29T02:30:44, size 5359                         */

class NCHART_LIB_DECL NChartTextElement : public NChartLayoutElement
{
  Q_OBJECT
  /// \cond INCLUDE_QPROPERTIES
  Q_PROPERTY(QString text READ text WRITE setText)
  Q_PROPERTY(QFont font READ font WRITE setFont)
  Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor)
  Q_PROPERTY(QFont selectedFont READ selectedFont WRITE setSelectedFont)
  Q_PROPERTY(QColor selectedTextColor READ selectedTextColor WRITE setSelectedTextColor)
  Q_PROPERTY(bool selectable READ selectable WRITE setSelectable NOTIFY selectableChanged)
  Q_PROPERTY(bool selected READ selected WRITE setSelected NOTIFY selectionChanged)
  /// \endcond
public:
  explicit NChartTextElement(NChartControl *parentPlot);
  NChartTextElement(NChartControl *parentPlot, const QString &text);
  NChartTextElement(NChartControl *parentPlot, const QString &text, double pointSize);
  NChartTextElement(NChartControl *parentPlot, const QString &text, const QString &fontFamily, double pointSize);
  NChartTextElement(NChartControl *parentPlot, const QString &text, const QFont &font);
  
  // getters:
  QString text() const { return mText; }
  int textFlags() const { return mTextFlags; }
  QFont font() const { return mFont; }
  QColor textColor() const { return mTextColor; }
  QFont selectedFont() const { return mSelectedFont; }
  QColor selectedTextColor() const { return mSelectedTextColor; }
  bool selectable() const { return mSelectable; }
  bool selected() const { return mSelected; }
  
  // setters:
  void setText(const QString &text);
  void setTextFlags(int flags);
  void setFont(const QFont &font);
  void setTextColor(const QColor &color);
  void setSelectedFont(const QFont &font);
  void setSelectedTextColor(const QColor &color);
  Q_SLOT void setSelectable(bool selectable);
  Q_SLOT void setSelected(bool selected);
  
  // reimplemented virtual methods:
  virtual double selectTest(const QPointF &pos, bool onlySelectable, QVariant *details=nullptr) const Q_DECL_OVERRIDE;
  virtual void mousePressEvent(QMouseEvent *event, const QVariant &details) Q_DECL_OVERRIDE;
  virtual void mouseReleaseEvent(QMouseEvent *event, const QPointF &startPos) Q_DECL_OVERRIDE;
  virtual void mouseDoubleClickEvent(QMouseEvent *event, const QVariant &details) Q_DECL_OVERRIDE;
  
signals:
  void selectionChanged(bool selected);
  void selectableChanged(bool selectable);
  void clicked(QMouseEvent *event);
  void doubleClicked(QMouseEvent *event);
  
protected:
  // property members:
  QString mText;
  int mTextFlags;
  QFont mFont;
  QColor mTextColor;
  QFont mSelectedFont;
  QColor mSelectedTextColor;
  QRect mTextBoundingRect;
  bool mSelectable, mSelected;
  
  // reimplemented virtual methods:
  virtual void applyDefaultAntialiasingHint(NChartPainter *painter) const Q_DECL_OVERRIDE;
  virtual void draw(NChartPainter *painter) Q_DECL_OVERRIDE;
  virtual QSize minimumOuterSizeHint() const Q_DECL_OVERRIDE;
  virtual QSize maximumOuterSizeHint() const Q_DECL_OVERRIDE;
  // events:
  virtual void selectEvent(QMouseEvent *event, bool additive, const QVariant &details, bool *selectionStateChanged) Q_DECL_OVERRIDE;
  virtual void deselectEvent(bool *selectionStateChanged) Q_DECL_OVERRIDE;
  
  // non-virtual methods:
  QFont mainFont() const;
  QColor mainTextColor() const;
  
private:
  Q_DISABLE_COPY(NChartTextElement)
};



/* end of 'src/layoutelements/layoutelement-textelement.h' */


/* including file 'src/layoutelements/layoutelement-colorscale.h' */
/* modified 2021-03-29T02:30:44, size 5939                        */


class NChartColorScaleAxisRectPrivate : public NChartAxisRect
{
  Q_OBJECT
public:
  explicit NChartColorScaleAxisRectPrivate(NChartColorScale *parentColorScale);
protected:
  NChartColorScale *mParentColorScale;
  QImage mGradientImage;
  bool mGradientImageInvalidated;
  // re-using some methods of NChartAxisRect to make them available to friend class NChartColorScale
  using NChartAxisRect::calculateAutoMargin;
  using NChartAxisRect::mousePressEvent;
  using NChartAxisRect::mouseMoveEvent;
  using NChartAxisRect::mouseReleaseEvent;
  using NChartAxisRect::wheelEvent;
  using NChartAxisRect::update;
  virtual void draw(NChartPainter *painter) Q_DECL_OVERRIDE;
  void updateGradientImage();
  Q_SLOT void axisSelectionChanged(NChartAxis::SelectableParts selectedParts);
  Q_SLOT void axisSelectableChanged(NChartAxis::SelectableParts selectableParts);
  friend class NChartColorScale;
};


class NCHART_LIB_DECL NChartColorScale : public NChartLayoutElement
{
  Q_OBJECT
  /// \cond INCLUDE_QPROPERTIES
  Q_PROPERTY(NChartAxis::AxisType type READ type WRITE setType)
  Q_PROPERTY(NChartRange dataRange READ dataRange WRITE setDataRange NOTIFY dataRangeChanged)
  Q_PROPERTY(NChartAxis::ScaleType dataScaleType READ dataScaleType WRITE setDataScaleType NOTIFY dataScaleTypeChanged)
  Q_PROPERTY(NChartColorGradient gradient READ gradient WRITE setGradient NOTIFY gradientChanged)
  Q_PROPERTY(QString label READ label WRITE setLabel)
  Q_PROPERTY(int barWidth READ barWidth WRITE setBarWidth)
  Q_PROPERTY(bool rangeDrag READ rangeDrag WRITE setRangeDrag)
  Q_PROPERTY(bool rangeZoom READ rangeZoom WRITE setRangeZoom)
  /// \endcond
public:
  explicit NChartColorScale(NChartControl *parentPlot);
  virtual ~NChartColorScale() Q_DECL_OVERRIDE;
  
  // getters:
  NChartAxis *axis() const { return mColorAxis.data(); }
  NChartAxis::AxisType type() const { return mType; }
  NChartRange dataRange() const { return mDataRange; }
  NChartAxis::ScaleType dataScaleType() const { return mDataScaleType; }
  NChartColorGradient gradient() const { return mGradient; }
  QString label() const;
  int barWidth () const { return mBarWidth; }
  bool rangeDrag() const;
  bool rangeZoom() const;
  
  // setters:
  void setType(NChartAxis::AxisType type);
  Q_SLOT void setDataRange(const NChartRange &dataRange);
  Q_SLOT void setDataScaleType(NChartAxis::ScaleType scaleType);
  Q_SLOT void setGradient(const NChartColorGradient &gradient);
  void setLabel(const QString &str);
  void setBarWidth(int width);
  void setRangeDrag(bool enabled);
  void setRangeZoom(bool enabled);
  
  // non-property methods:
  QList<NChartColorMap*> colorMaps() const;
  void rescaleDataRange(bool onlyVisibleMaps);
  
  // reimplemented virtual methods:
  virtual void update(UpdatePhase phase) Q_DECL_OVERRIDE;
  
signals:
  void dataRangeChanged(const NChartRange &newRange);
  void dataScaleTypeChanged(NChartAxis::ScaleType scaleType);
  void gradientChanged(const NChartColorGradient &newGradient);

protected:
  // property members:
  NChartAxis::AxisType mType;
  NChartRange mDataRange;
  NChartAxis::ScaleType mDataScaleType;
  NChartColorGradient mGradient;
  int mBarWidth;
  
  // non-property members:
  QPointer<NChartColorScaleAxisRectPrivate> mAxisRect;
  QPointer<NChartAxis> mColorAxis;
  
  // reimplemented virtual methods:
  virtual void applyDefaultAntialiasingHint(NChartPainter *painter) const Q_DECL_OVERRIDE;
  // events:
  virtual void mousePressEvent(QMouseEvent *event, const QVariant &details) Q_DECL_OVERRIDE;
  virtual void mouseMoveEvent(QMouseEvent *event, const QPointF &startPos) Q_DECL_OVERRIDE;
  virtual void mouseReleaseEvent(QMouseEvent *event, const QPointF &startPos) Q_DECL_OVERRIDE;
  virtual void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;
  
private:
  Q_DISABLE_COPY(NChartColorScale)
  
  friend class NChartColorScaleAxisRectPrivate;
};


/* end of 'src/layoutelements/layoutelement-colorscale.h' */


/* including file 'src/plottables/plottable-graph.h' */
/* modified 2021-03-29T02:30:44, size 9316           */

class NCHART_LIB_DECL NChartGraphData
{
public:
  NChartGraphData();
  NChartGraphData(double key, double value);
  
  inline double sortKey() const { return key; }
  inline static NChartGraphData fromSortKey(double sortKey) { return NChartGraphData(sortKey, 0); }
  inline static bool sortKeyIsMainKey() { return true; }
  
  inline double mainKey() const { return key; }
  inline double mainValue() const { return value; }
  
  inline NChartRange valueRange() const { return NChartRange(value, value); }
  
  double key, value;
};
Q_DECLARE_TYPEINFO(NChartGraphData, Q_PRIMITIVE_TYPE);


/*! \typedef NChartGraphDataContainer
  
  Container for storing \ref NChartGraphData points. The data is stored sorted by \a key.
  
  This template instantiation is the container in which NChartGraph holds its data. For details about
  the generic container, see the documentation of the class template \ref NChartDataContainer.
  
  \see NChartGraphData, NChartGraph::setData
*/
typedef NChartDataContainer<NChartGraphData> NChartGraphDataContainer;

class NCHART_LIB_DECL NChartGraph : public NChartAbstractPlottable1D<NChartGraphData>
{
  Q_OBJECT
  /// \cond INCLUDE_QPROPERTIES
  Q_PROPERTY(LineStyle lineStyle READ lineStyle WRITE setLineStyle)
  Q_PROPERTY(NChartScatterStyle scatterStyle READ scatterStyle WRITE setScatterStyle)
  Q_PROPERTY(int scatterSkip READ scatterSkip WRITE setScatterSkip)
  Q_PROPERTY(NChartGraph* channelFillGraph READ channelFillGraph WRITE setChannelFillGraph)
  Q_PROPERTY(bool adaptiveSampling READ adaptiveSampling WRITE setAdaptiveSampling)
  /// \endcond
public:
  /*!
    Defines how the graph's line is represented visually in the plot. The line is drawn with the
    current pen of the graph (\ref setPen).
    \see setLineStyle
  */
  enum LineStyle { lsNone        ///< data points are not connected with any lines (e.g. data only represented
                                 ///< with symbols according to the scatter style, see \ref setScatterStyle)
                   ,lsLine       ///< data points are connected by a straight line
                   ,lsStepLeft   ///< line is drawn as steps where the step height is the value of the left data point
                   ,lsStepRight  ///< line is drawn as steps where the step height is the value of the right data point
                   ,lsStepCenter ///< line is drawn as steps where the step is in between two data points
                   ,lsImpulse    ///< each data point is represented by a line parallel to the value axis, which reaches from the data point to the zero-value-line
                 };
  Q_ENUMS(LineStyle)
  
  explicit NChartGraph(NChartAxis *keyAxis, NChartAxis *valueAxis);
  virtual ~NChartGraph() Q_DECL_OVERRIDE;
  
  // getters:
  QSharedPointer<NChartGraphDataContainer> data() const { return mDataContainer; }
  LineStyle lineStyle() const { return mLineStyle; }
  NChartScatterStyle scatterStyle() const { return mScatterStyle; }
  int scatterSkip() const { return mScatterSkip; }
  NChartGraph *channelFillGraph() const { return mChannelFillGraph.data(); }
  bool adaptiveSampling() const { return mAdaptiveSampling; }
  
  // setters:
  void setData(QSharedPointer<NChartGraphDataContainer> data);
  void setData(const QVector<double> &keys, const QVector<double> &values, bool alreadySorted=false);
  void setLineStyle(LineStyle ls);
  void setScatterStyle(const NChartScatterStyle &style);
  void setScatterSkip(int skip);
  void setChannelFillGraph(NChartGraph *targetGraph);
  void setAdaptiveSampling(bool enabled);
  
  // non-property methods:
  void addData(const QVector<double> &keys, const QVector<double> &values, bool alreadySorted=false);
  void addData(double key, double value);
  void clearData();
  void removeBeforeData(double key);

  // reimplemented virtual methods:
  virtual double selectTest(const QPointF &pos, bool onlySelectable, QVariant *details=nullptr) const Q_DECL_OVERRIDE;
  virtual NChartRange getKeyRange(bool &foundRange, NChart::SignDomain inSignDomain=NChart::sdBoth) const Q_DECL_OVERRIDE;
  virtual NChartRange getValueRange(bool &foundRange, NChart::SignDomain inSignDomain=NChart::sdBoth, const NChartRange &inKeyRange=NChartRange()) const Q_DECL_OVERRIDE;
  
protected:
  // property members:
  LineStyle mLineStyle;
  NChartScatterStyle mScatterStyle;
  int mScatterSkip;
  QPointer<NChartGraph> mChannelFillGraph;
  bool mAdaptiveSampling;
  
  // reimplemented virtual methods:
  virtual void draw(NChartPainter *painter) Q_DECL_OVERRIDE;
  virtual void drawLegendIcon(NChartPainter *painter, const QRectF &rect) const Q_DECL_OVERRIDE;
  
  // introduced virtual methods:
  virtual void drawFill(NChartPainter *painter, QVector<QPointF> *lines) const;
  virtual void drawScatterPlot(NChartPainter *painter, const QVector<QPointF> &scatters, const NChartScatterStyle &style) const;
  virtual void drawLinePlot(NChartPainter *painter, const QVector<QPointF> &lines) const;
  virtual void drawImpulsePlot(NChartPainter *painter, const QVector<QPointF> &lines) const;
  
  virtual void getOptimizedLineData(QVector<NChartGraphData> *lineData, const NChartGraphDataContainer::const_iterator &begin, const NChartGraphDataContainer::const_iterator &end) const;
  virtual void getOptimizedScatterData(QVector<NChartGraphData> *scatterData, NChartGraphDataContainer::const_iterator begin, NChartGraphDataContainer::const_iterator end) const;
  
  // non-virtual methods:
  void getVisibleDataBounds(NChartGraphDataContainer::const_iterator &begin, NChartGraphDataContainer::const_iterator &end, const NChartDataRange &rangeRestriction) const;
  void getLines(QVector<QPointF> *lines, const NChartDataRange &dataRange) const;
  void getScatters(QVector<QPointF> *scatters, const NChartDataRange &dataRange) const;
  QVector<QPointF> dataToLines(const QVector<NChartGraphData> &data) const;
  QVector<QPointF> dataToStepLeftLines(const QVector<NChartGraphData> &data) const;
  QVector<QPointF> dataToStepRightLines(const QVector<NChartGraphData> &data) const;
  QVector<QPointF> dataToStepCenterLines(const QVector<NChartGraphData> &data) const;
  QVector<QPointF> dataToImpulseLines(const QVector<NChartGraphData> &data) const;
  QVector<NChartDataRange> getNonNanSegments(const QVector<QPointF> *lineData, Qt::Orientation keyOrientation) const;
  QVector<QPair<NChartDataRange, NChartDataRange> > getOverlappingSegments(QVector<NChartDataRange> thisSegments, const QVector<QPointF> *thisData, QVector<NChartDataRange> otherSegments, const QVector<QPointF> *otherData) const;
  bool segmentsIntersect(double aLower, double aUpper, double bLower, double bUpper, int &bPrecedence) const;
  QPointF getFillBasePoint(QPointF matchingDataPoint) const;
  const QPolygonF getFillPolygon(const QVector<QPointF> *lineData, NChartDataRange segment) const;
  const QPolygonF getChannelFillPolygon(const QVector<QPointF> *thisData, NChartDataRange thisSegment, const QVector<QPointF> *otherData, NChartDataRange otherSegment) const;
  int findIndexBelowX(const QVector<QPointF> *data, double x) const;
  int findIndexAboveX(const QVector<QPointF> *data, double x) const;
  int findIndexBelowY(const QVector<QPointF> *data, double y) const;
  int findIndexAboveY(const QVector<QPointF> *data, double y) const;
  double pointDistance(const QPointF &pixelPoint, NChartGraphDataContainer::const_iterator &closestData) const;
  
  friend class NChartControl;
  friend class NChartLegend;
};
Q_DECLARE_METATYPE(NChartGraph::LineStyle)

/* end of 'src/plottables/plottable-graph.h' */


/* including file 'src/plottables/plottable-curve.h' */
/* modified 2021-03-29T02:30:44, size 7434           */

class NCHART_LIB_DECL NChartCurveData
{
public:
  NChartCurveData();
  NChartCurveData(double t, double key, double value);
  
  inline double sortKey() const { return t; }
  inline static NChartCurveData fromSortKey(double sortKey) { return NChartCurveData(sortKey, 0, 0); }
  inline static bool sortKeyIsMainKey() { return false; }
  
  inline double mainKey() const { return key; }
  inline double mainValue() const { return value; }
  
  inline NChartRange valueRange() const { return NChartRange(value, value); }
  
  double t, key, value;
};
Q_DECLARE_TYPEINFO(NChartCurveData, Q_PRIMITIVE_TYPE);


/*! \typedef NChartCurveDataContainer
  
  Container for storing \ref NChartCurveData points. The data is stored sorted by \a t, so the \a
  sortKey() (returning \a t) is different from \a mainKey() (returning \a key).
  
  This template instantiation is the container in which NChartCurve holds its data. For details about
  the generic container, see the documentation of the class template \ref NChartDataContainer.
  
  \see NChartCurveData, NChartCurve::setData
*/
typedef NChartDataContainer<NChartCurveData> NChartCurveDataContainer;

class NCHART_LIB_DECL NChartCurve : public NChartAbstractPlottable1D<NChartCurveData>
{
  Q_OBJECT
  /// \cond INCLUDE_QPROPERTIES
  Q_PROPERTY(NChartScatterStyle scatterStyle READ scatterStyle WRITE setScatterStyle)
  Q_PROPERTY(int scatterSkip READ scatterSkip WRITE setScatterSkip)
  Q_PROPERTY(LineStyle lineStyle READ lineStyle WRITE setLineStyle)
  /// \endcond
public:
  /*!
    Defines how the curve's line is represented visually in the plot. The line is drawn with the
    current pen of the curve (\ref setPen).
    \see setLineStyle
  */
  enum LineStyle { lsNone  ///< No line is drawn between data points (e.g. only scatters)
                   ,lsLine ///< Data points are connected with a straight line
                 };
  Q_ENUMS(LineStyle)
  
  explicit NChartCurve(NChartAxis *keyAxis, NChartAxis *valueAxis);
  virtual ~NChartCurve() Q_DECL_OVERRIDE;
  
  // getters:
  QSharedPointer<NChartCurveDataContainer> data() const { return mDataContainer; }
  NChartScatterStyle scatterStyle() const { return mScatterStyle; }
  int scatterSkip() const { return mScatterSkip; }
  LineStyle lineStyle() const { return mLineStyle; }
  
  // setters:
  void setData(QSharedPointer<NChartCurveDataContainer> data);
  void setData(const QVector<double> &t, const QVector<double> &keys, const QVector<double> &values, bool alreadySorted=false);
  void setData(const QVector<double> &keys, const QVector<double> &values);
  void setScatterStyle(const NChartScatterStyle &style);
  void setScatterSkip(int skip);
  void setLineStyle(LineStyle style);
  
  // non-property methods:
  void addData(const QVector<double> &t, const QVector<double> &keys, const QVector<double> &values, bool alreadySorted=false);
  void addData(const QVector<double> &keys, const QVector<double> &values);
  void addData(double t, double key, double value);
  void addData(double key, double value);
  
  // reimplemented virtual methods:
  virtual double selectTest(const QPointF &pos, bool onlySelectable, QVariant *details=nullptr) const Q_DECL_OVERRIDE;
  virtual NChartRange getKeyRange(bool &foundRange, NChart::SignDomain inSignDomain=NChart::sdBoth) const Q_DECL_OVERRIDE;
  virtual NChartRange getValueRange(bool &foundRange, NChart::SignDomain inSignDomain=NChart::sdBoth, const NChartRange &inKeyRange=NChartRange()) const Q_DECL_OVERRIDE;
  
protected:
  // property members:
  NChartScatterStyle mScatterStyle;
  int mScatterSkip;
  LineStyle mLineStyle;
  
  // reimplemented virtual methods:
  virtual void draw(NChartPainter *painter) Q_DECL_OVERRIDE;
  virtual void drawLegendIcon(NChartPainter *painter, const QRectF &rect) const Q_DECL_OVERRIDE;
  
  // introduced virtual methods:
  virtual void drawCurveLine(NChartPainter *painter, const QVector<QPointF> &lines) const;
  virtual void drawScatterPlot(NChartPainter *painter, const QVector<QPointF> &points, const NChartScatterStyle &style) const;
  
  // non-virtual methods:
  void getCurveLines(QVector<QPointF> *lines, const NChartDataRange &dataRange, double penWidth) const;
  void getScatters(QVector<QPointF> *scatters, const NChartDataRange &dataRange, double scatterWidth) const;
  int getRegion(double key, double value, double keyMin, double valueMax, double keyMax, double valueMin) const;
  QPointF getOptimizedPoint(int otherRegion, double otherKey, double otherValue, double key, double value, double keyMin, double valueMax, double keyMax, double valueMin) const;
  QVector<QPointF> getOptimizedCornerPoints(int prevRegion, int currentRegion, double prevKey, double prevValue, double key, double value, double keyMin, double valueMax, double keyMax, double valueMin) const;
  bool mayTraverse(int prevRegion, int currentRegion) const;
  bool getTraverse(double prevKey, double prevValue, double key, double value, double keyMin, double valueMax, double keyMax, double valueMin, QPointF &crossA, QPointF &crossB) const;
  void getTraverseCornerPoints(int prevRegion, int currentRegion, double keyMin, double valueMax, double keyMax, double valueMin, QVector<QPointF> &beforeTraverse, QVector<QPointF> &afterTraverse) const;
  double pointDistance(const QPointF &pixelPoint, NChartCurveDataContainer::const_iterator &closestData) const;
  
  friend class NChartControl;
  friend class NChartLegend;
};
Q_DECLARE_METATYPE(NChartCurve::LineStyle)

/* end of 'src/plottables/plottable-curve.h' */


/* including file 'src/plottables/plottable-bars.h' */
/* modified 2021-03-29T02:30:44, size 8955          */

class NCHART_LIB_DECL NChartBarsGroup : public QObject
{
  Q_OBJECT
  /// \cond INCLUDE_QPROPERTIES
  Q_PROPERTY(SpacingType spacingType READ spacingType WRITE setSpacingType)
  Q_PROPERTY(double spacing READ spacing WRITE setSpacing)
  /// \endcond
public:
  /*!
    Defines the ways the spacing between bars in the group can be specified. Thus it defines what
    the number passed to \ref setSpacing actually means.
    
    \see setSpacingType, setSpacing
  */
  enum SpacingType { stAbsolute       ///< Bar spacing is in absolute pixels
                     ,stAxisRectRatio ///< Bar spacing is given by a fraction of the axis rect size
                     ,stPlotCoords    ///< Bar spacing is in key coordinates and thus scales with the key axis range
                   };
  Q_ENUMS(SpacingType)
  
  explicit NChartBarsGroup(NChartControl *parentPlot);
  virtual ~NChartBarsGroup();
  
  // getters:
  SpacingType spacingType() const { return mSpacingType; }
  double spacing() const { return mSpacing; }
  
  // setters:
  void setSpacingType(SpacingType spacingType);
  void setSpacing(double spacing);
  
  // non-virtual methods:
  QList<NChartBars*> bars() const { return mBars; }
  NChartBars* bars(int index) const;
  int size() const { return mBars.size(); }
  bool isEmpty() const { return mBars.isEmpty(); }
  void clear();
  bool contains(NChartBars *bars) const { return mBars.contains(bars); }
  void append(NChartBars *bars);
  void insert(int i, NChartBars *bars);
  void remove(NChartBars *bars);
  
protected:
  // non-property members:
  NChartControl *mParentPlot;
  SpacingType mSpacingType;
  double mSpacing;
  QList<NChartBars*> mBars;
  
  // non-virtual methods:
  void registerBars(NChartBars *bars);
  void unregisterBars(NChartBars *bars);
  
  // virtual methods:
  double keyPixelOffset(const NChartBars *bars, double keyCoord);
  double getPixelSpacing(const NChartBars *bars, double keyCoord);
  
private:
  Q_DISABLE_COPY(NChartBarsGroup)
  
  friend class NChartBars;
};
Q_DECLARE_METATYPE(NChartBarsGroup::SpacingType)


class NCHART_LIB_DECL NChartBarsData
{
public:
  NChartBarsData();
  NChartBarsData(double key, double value);
  
  inline double sortKey() const { return key; }
  inline static NChartBarsData fromSortKey(double sortKey) { return NChartBarsData(sortKey, 0); }
  inline static bool sortKeyIsMainKey() { return true; } 
  
  inline double mainKey() const { return key; }
  inline double mainValue() const { return value; }
  
  inline NChartRange valueRange() const { return NChartRange(value, value); } // note that bar base value isn't held in each NChartBarsData and thus can't/shouldn't be returned here
  
  double key, value;
};
Q_DECLARE_TYPEINFO(NChartBarsData, Q_PRIMITIVE_TYPE);


/*! \typedef NChartBarsDataContainer
  
  Container for storing \ref NChartBarsData points. The data is stored sorted by \a key.
  
  This template instantiation is the container in which NChartBars holds its data. For details about
  the generic container, see the documentation of the class template \ref NChartDataContainer.
  
  \see NChartBarsData, NChartBars::setData
*/
typedef NChartDataContainer<NChartBarsData> NChartBarsDataContainer;

class NCHART_LIB_DECL NChartBars : public NChartAbstractPlottable1D<NChartBarsData>
{
  Q_OBJECT
  /// \cond INCLUDE_QPROPERTIES
  Q_PROPERTY(double width READ width WRITE setWidth)
  Q_PROPERTY(WidthType widthType READ widthType WRITE setWidthType)
  Q_PROPERTY(NChartBarsGroup* barsGroup READ barsGroup WRITE setBarsGroup)
  Q_PROPERTY(double baseValue READ baseValue WRITE setBaseValue)
  Q_PROPERTY(double stackingGap READ stackingGap WRITE setStackingGap)
  Q_PROPERTY(NChartBars* barBelow READ barBelow)
  Q_PROPERTY(NChartBars* barAbove READ barAbove)
  /// \endcond
public:
  /*!
    Defines the ways the width of the bar can be specified. Thus it defines what the number passed
    to \ref setWidth actually means.
    
    \see setWidthType, setWidth
  */
  enum WidthType { wtAbsolute       ///< Bar width is in absolute pixels
                   ,wtAxisRectRatio ///< Bar width is given by a fraction of the axis rect size
                   ,wtPlotCoords    ///< Bar width is in key coordinates and thus scales with the key axis range
                 };
  Q_ENUMS(WidthType)
  
  explicit NChartBars(NChartAxis *keyAxis, NChartAxis *valueAxis);
  virtual ~NChartBars() Q_DECL_OVERRIDE;
  
  // getters:
  double width() const { return mWidth; }
  WidthType widthType() const { return mWidthType; }
  NChartBarsGroup *barsGroup() const { return mBarsGroup; }
  double baseValue() const { return mBaseValue; }
  double stackingGap() const { return mStackingGap; }
  NChartBars *barBelow() const { return mBarBelow.data(); }
  NChartBars *barAbove() const { return mBarAbove.data(); }
  QSharedPointer<NChartBarsDataContainer> data() const { return mDataContainer; }
  
  // setters:
  void setData(QSharedPointer<NChartBarsDataContainer> data);
  void setData(const QVector<double> &keys, const QVector<double> &values, bool alreadySorted=false);
  void setWidth(double width);
  void setWidthType(WidthType widthType);
  void setBarsGroup(NChartBarsGroup *barsGroup);
  void setBaseValue(double baseValue);
  void setStackingGap(double pixels);
  
  // non-property methods:
  void addData(const QVector<double> &keys, const QVector<double> &values, bool alreadySorted=false);
  void addData(double key, double value);
  void moveBelow(NChartBars *bars);
  void moveAbove(NChartBars *bars);
  
  // reimplemented virtual methods:
  virtual NChartDataSelection selectTestRect(const QRectF &rect, bool onlySelectable) const Q_DECL_OVERRIDE;
  virtual double selectTest(const QPointF &pos, bool onlySelectable, QVariant *details=nullptr) const Q_DECL_OVERRIDE;
  virtual NChartRange getKeyRange(bool &foundRange, NChart::SignDomain inSignDomain=NChart::sdBoth) const Q_DECL_OVERRIDE;
  virtual NChartRange getValueRange(bool &foundRange, NChart::SignDomain inSignDomain=NChart::sdBoth, const NChartRange &inKeyRange=NChartRange()) const Q_DECL_OVERRIDE;
  virtual QPointF dataPixelPosition(int index) const Q_DECL_OVERRIDE;
  
protected:
  // property members:
  double mWidth;
  WidthType mWidthType;
  NChartBarsGroup *mBarsGroup;
  double mBaseValue;
  double mStackingGap;
  QPointer<NChartBars> mBarBelow, mBarAbove;
  
  // reimplemented virtual methods:
  virtual void draw(NChartPainter *painter) Q_DECL_OVERRIDE;
  virtual void drawLegendIcon(NChartPainter *painter, const QRectF &rect) const Q_DECL_OVERRIDE;
  
  // non-virtual methods:
  void getVisibleDataBounds(NChartBarsDataContainer::const_iterator &begin, NChartBarsDataContainer::const_iterator &end) const;
  QRectF getBarRect(double key, double value) const;
  void getPixelWidth(double key, double &lower, double &upper) const;
  double getStackedBaseValue(double key, bool positive) const;
  static void connectBars(NChartBars* lower, NChartBars* upper);
  
  friend class NChartControl;
  friend class NChartLegend;
  friend class NChartBarsGroup;
};
Q_DECLARE_METATYPE(NChartBars::WidthType)

/* end of 'src/plottables/plottable-bars.h' */


/* including file 'src/plottables/plottable-statisticalbox.h' */
/* modified 2021-03-29T02:30:44, size 7522                    */

class NCHART_LIB_DECL NChartStatisticalBoxData
{
public:
  NChartStatisticalBoxData();
  NChartStatisticalBoxData(double key, double minimum, double lowerQuartile, double median, double upperQuartile, double maximum, const QVector<double>& outliers=QVector<double>());
  
  inline double sortKey() const { return key; }
  inline static NChartStatisticalBoxData fromSortKey(double sortKey) { return NChartStatisticalBoxData(sortKey, 0, 0, 0, 0, 0); }
  inline static bool sortKeyIsMainKey() { return true; }
  
  inline double mainKey() const { return key; }
  inline double mainValue() const { return median; }
  
  inline NChartRange valueRange() const
  {
    NChartRange result(minimum, maximum);
    for (QVector<double>::const_iterator it = outliers.constBegin(); it != outliers.constEnd(); ++it)
      result.expand(*it);
    return result;
  }
  
  double key, minimum, lowerQuartile, median, upperQuartile, maximum;
  QVector<double> outliers;
};
Q_DECLARE_TYPEINFO(NChartStatisticalBoxData, Q_MOVABLE_TYPE);


/*! \typedef NChartStatisticalBoxDataContainer
  
  Container for storing \ref NChartStatisticalBoxData points. The data is stored sorted by \a key.
  
  This template instantiation is the container in which NChartStatisticalBox holds its data. For
  details about the generic container, see the documentation of the class template \ref
  NChartDataContainer.
  
  \see NChartStatisticalBoxData, NChartStatisticalBox::setData
*/
typedef NChartDataContainer<NChartStatisticalBoxData> NChartStatisticalBoxDataContainer;

class NCHART_LIB_DECL NChartStatisticalBox : public NChartAbstractPlottable1D<NChartStatisticalBoxData>
{
  Q_OBJECT
  /// \cond INCLUDE_QPROPERTIES
  Q_PROPERTY(double width READ width WRITE setWidth)
  Q_PROPERTY(double whiskerWidth READ whiskerWidth WRITE setWhiskerWidth)
  Q_PROPERTY(QPen whiskerPen READ whiskerPen WRITE setWhiskerPen)
  Q_PROPERTY(QPen whiskerBarPen READ whiskerBarPen WRITE setWhiskerBarPen)
  Q_PROPERTY(bool whiskerAntialiased READ whiskerAntialiased WRITE setWhiskerAntialiased)
  Q_PROPERTY(QPen medianPen READ medianPen WRITE setMedianPen)
  Q_PROPERTY(NChartScatterStyle outlierStyle READ outlierStyle WRITE setOutlierStyle)
  /// \endcond
public:
  explicit NChartStatisticalBox(NChartAxis *keyAxis, NChartAxis *valueAxis);
  
  // getters:
  QSharedPointer<NChartStatisticalBoxDataContainer> data() const { return mDataContainer; }
  double width() const { return mWidth; }
  double whiskerWidth() const { return mWhiskerWidth; }
  QPen whiskerPen() const { return mWhiskerPen; }
  QPen whiskerBarPen() const { return mWhiskerBarPen; }
  bool whiskerAntialiased() const { return mWhiskerAntialiased; }
  QPen medianPen() const { return mMedianPen; }
  NChartScatterStyle outlierStyle() const { return mOutlierStyle; }

  // setters:
  void setData(QSharedPointer<NChartStatisticalBoxDataContainer> data);
  void setData(const QVector<double> &keys, const QVector<double> &minimum, const QVector<double> &lowerQuartile, const QVector<double> &median, const QVector<double> &upperQuartile, const QVector<double> &maximum, bool alreadySorted=false);
  void setWidth(double width);
  void setWhiskerWidth(double width);
  void setWhiskerPen(const QPen &pen);
  void setWhiskerBarPen(const QPen &pen);
  void setWhiskerAntialiased(bool enabled);
  void setMedianPen(const QPen &pen);
  void setOutlierStyle(const NChartScatterStyle &style);
  
  // non-property methods:
  void addData(const QVector<double> &keys, const QVector<double> &minimum, const QVector<double> &lowerQuartile, const QVector<double> &median, const QVector<double> &upperQuartile, const QVector<double> &maximum, bool alreadySorted=false);
  void addData(double key, double minimum, double lowerQuartile, double median, double upperQuartile, double maximum, const QVector<double> &outliers=QVector<double>());
  
  // reimplemented virtual methods:
  virtual NChartDataSelection selectTestRect(const QRectF &rect, bool onlySelectable) const Q_DECL_OVERRIDE;
  virtual double selectTest(const QPointF &pos, bool onlySelectable, QVariant *details=nullptr) const Q_DECL_OVERRIDE;
  virtual NChartRange getKeyRange(bool &foundRange, NChart::SignDomain inSignDomain=NChart::sdBoth) const Q_DECL_OVERRIDE;
  virtual NChartRange getValueRange(bool &foundRange, NChart::SignDomain inSignDomain=NChart::sdBoth, const NChartRange &inKeyRange=NChartRange()) const Q_DECL_OVERRIDE;
  
protected:
  // property members:
  double mWidth;
  double mWhiskerWidth;
  QPen mWhiskerPen, mWhiskerBarPen;
  bool mWhiskerAntialiased;
  QPen mMedianPen;
  NChartScatterStyle mOutlierStyle;
  
  // reimplemented virtual methods:
  virtual void draw(NChartPainter *painter) Q_DECL_OVERRIDE;
  virtual void drawLegendIcon(NChartPainter *painter, const QRectF &rect) const Q_DECL_OVERRIDE;
  
  // introduced virtual methods:
  virtual void drawStatisticalBox(NChartPainter *painter, NChartStatisticalBoxDataContainer::const_iterator it, const NChartScatterStyle &outlierStyle) const;
  
  // non-virtual methods:
  void getVisibleDataBounds(NChartStatisticalBoxDataContainer::const_iterator &begin, NChartStatisticalBoxDataContainer::const_iterator &end) const;
  QRectF getQuartileBox(NChartStatisticalBoxDataContainer::const_iterator it) const;
  QVector<QLineF> getWhiskerBackboneLines(NChartStatisticalBoxDataContainer::const_iterator it) const;
  QVector<QLineF> getWhiskerBarLines(NChartStatisticalBoxDataContainer::const_iterator it) const;
  
  friend class NChartControl;
  friend class NChartLegend;
};

/* end of 'src/plottables/plottable-statisticalbox.h' */


/* including file 'src/plottables/plottable-colormap.h' */
/* modified 2021-03-29T02:30:44, size 7092              */

class NCHART_LIB_DECL NChartColorMapData
{
public:
  NChartColorMapData(int keySize, int valueSize, const NChartRange &keyRange, const NChartRange &valueRange);
  ~NChartColorMapData();
  NChartColorMapData(const NChartColorMapData &other);
  NChartColorMapData &operator=(const NChartColorMapData &other);
  
  // getters:
  int keySize() const { return mKeySize; }
  int valueSize() const { return mValueSize; }
  NChartRange keyRange() const { return mKeyRange; }
  NChartRange valueRange() const { return mValueRange; }
  NChartRange dataBounds() const { return mDataBounds; }
  double data(double key, double value);
  double cell(int keyIndex, int valueIndex);
  unsigned char alpha(int keyIndex, int valueIndex);
  
  // setters:
  void setSize(int keySize, int valueSize);
  void setKeySize(int keySize);
  void setValueSize(int valueSize);
  void setRange(const NChartRange &keyRange, const NChartRange &valueRange);
  void setKeyRange(const NChartRange &keyRange);
  void setValueRange(const NChartRange &valueRange);
  void setData(double key, double value, double z);
  void setCell(int keyIndex, int valueIndex, double z);
  void setAlpha(int keyIndex, int valueIndex, unsigned char alpha);
  
  // non-property methods:
  void recalculateDataBounds();
  void clear();
  void clearAlpha();
  void fill(double z);
  void fillAlpha(unsigned char alpha);
  bool isEmpty() const { return mIsEmpty; }
  void coordToCell(double key, double value, int *keyIndex, int *valueIndex) const;
  void cellToCoord(int keyIndex, int valueIndex, double *key, double *value) const;
  
protected:
  // property members:
  int mKeySize, mValueSize;
  NChartRange mKeyRange, mValueRange;
  bool mIsEmpty;
  
  // non-property members:
  double *mData;
  unsigned char *mAlpha;
  NChartRange mDataBounds;
  bool mDataModified;
  
  bool createAlpha(bool initializeOpaque=true);
  
  friend class NChartColorMap;
};


class NCHART_LIB_DECL NChartColorMap : public NChartAbstractPlottable
{
  Q_OBJECT
  /// \cond INCLUDE_QPROPERTIES
  Q_PROPERTY(NChartRange dataRange READ dataRange WRITE setDataRange NOTIFY dataRangeChanged)
  Q_PROPERTY(NChartAxis::ScaleType dataScaleType READ dataScaleType WRITE setDataScaleType NOTIFY dataScaleTypeChanged)
  Q_PROPERTY(NChartColorGradient gradient READ gradient WRITE setGradient NOTIFY gradientChanged)
  Q_PROPERTY(bool interpolate READ interpolate WRITE setInterpolate)
  Q_PROPERTY(bool tightBoundary READ tightBoundary WRITE setTightBoundary)
  Q_PROPERTY(NChartColorScale* colorScale READ colorScale WRITE setColorScale)
  /// \endcond
public:
  explicit NChartColorMap(NChartAxis *keyAxis, NChartAxis *valueAxis);
  virtual ~NChartColorMap() Q_DECL_OVERRIDE;
  
  // getters:
  NChartColorMapData *data() const { return mMapData; }
  NChartRange dataRange() const { return mDataRange; }
  NChartAxis::ScaleType dataScaleType() const { return mDataScaleType; }
  bool interpolate() const { return mInterpolate; }
  bool tightBoundary() const { return mTightBoundary; }
  NChartColorGradient gradient() const { return mGradient; }
  NChartColorScale *colorScale() const { return mColorScale.data(); }
  
  // setters:
  void setData(NChartColorMapData *data, bool copy=false);
  Q_SLOT void setDataRange(const NChartRange &dataRange);
  Q_SLOT void setDataScaleType(NChartAxis::ScaleType scaleType);
  Q_SLOT void setGradient(const NChartColorGradient &gradient);
  void setInterpolate(bool enabled);
  void setTightBoundary(bool enabled);
  void setColorScale(NChartColorScale *colorScale);
  
  // non-property methods:
  void rescaleDataRange(bool recalculateDataBounds=false);
  Q_SLOT void updateLegendIcon(Qt::TransformationMode transformMode=Qt::SmoothTransformation, const QSize &thumbSize=QSize(32, 18));
  
  // reimplemented virtual methods:
  virtual double selectTest(const QPointF &pos, bool onlySelectable, QVariant *details=nullptr) const Q_DECL_OVERRIDE;
  virtual NChartRange getKeyRange(bool &foundRange, NChart::SignDomain inSignDomain=NChart::sdBoth) const Q_DECL_OVERRIDE;
  virtual NChartRange getValueRange(bool &foundRange, NChart::SignDomain inSignDomain=NChart::sdBoth, const NChartRange &inKeyRange=NChartRange()) const Q_DECL_OVERRIDE;
  
signals:
  void dataRangeChanged(const NChartRange &newRange);
  void dataScaleTypeChanged(NChartAxis::ScaleType scaleType);
  void gradientChanged(const NChartColorGradient &newGradient);
  
protected:
  // property members:
  NChartRange mDataRange;
  NChartAxis::ScaleType mDataScaleType;
  NChartColorMapData *mMapData;
  NChartColorGradient mGradient;
  bool mInterpolate;
  bool mTightBoundary;
  QPointer<NChartColorScale> mColorScale;
  
  // non-property members:
  QImage mMapImage, mUndersampledMapImage;
  QPixmap mLegendIcon;
  bool mMapImageInvalidated;
  
  // introduced virtual methods:
  virtual void updateMapImage();
  
  // reimplemented virtual methods:
  virtual void draw(NChartPainter *painter) Q_DECL_OVERRIDE;
  virtual void drawLegendIcon(NChartPainter *painter, const QRectF &rect) const Q_DECL_OVERRIDE;
  
  friend class NChartControl;
  friend class NChartLegend;
};

/* end of 'src/plottables/plottable-colormap.h' */


/* including file 'src/plottables/plottable-financial.h' */
/* modified 2021-03-29T02:30:44, size 8644               */

class NCHART_LIB_DECL NChartFinancialData
{
public:
  NChartFinancialData();
  NChartFinancialData(double key, double open, double high, double low, double close);
  
  inline double sortKey() const { return key; }
  inline static NChartFinancialData fromSortKey(double sortKey) { return NChartFinancialData(sortKey, 0, 0, 0, 0); }
  inline static bool sortKeyIsMainKey() { return true; } 
  
  inline double mainKey() const { return key; }
  inline double mainValue() const { return open; }
  
  inline NChartRange valueRange() const { return NChartRange(low, high); } // open and close must lie between low and high, so we don't need to check them
  
  double key, open, high, low, close;
};
Q_DECLARE_TYPEINFO(NChartFinancialData, Q_PRIMITIVE_TYPE);


/*! \typedef NChartFinancialDataContainer
  
  Container for storing \ref NChartFinancialData points. The data is stored sorted by \a key.
  
  This template instantiation is the container in which NChartFinancial holds its data. For details
  about the generic container, see the documentation of the class template \ref NChartDataContainer.
  
  \see NChartFinancialData, NChartFinancial::setData
*/
typedef NChartDataContainer<NChartFinancialData> NChartFinancialDataContainer;

class NCHART_LIB_DECL NChartFinancial : public NChartAbstractPlottable1D<NChartFinancialData>
{
  Q_OBJECT
  /// \cond INCLUDE_QPROPERTIES
  Q_PROPERTY(ChartStyle chartStyle READ chartStyle WRITE setChartStyle)
  Q_PROPERTY(double width READ width WRITE setWidth)
  Q_PROPERTY(WidthType widthType READ widthType WRITE setWidthType)
  Q_PROPERTY(bool twoColored READ twoColored WRITE setTwoColored)
  Q_PROPERTY(QBrush brushPositive READ brushPositive WRITE setBrushPositive)
  Q_PROPERTY(QBrush brushNegative READ brushNegative WRITE setBrushNegative)
  Q_PROPERTY(QPen penPositive READ penPositive WRITE setPenPositive)
  Q_PROPERTY(QPen penNegative READ penNegative WRITE setPenNegative)
  /// \endcond
public:
  /*!
    Defines the ways the width of the financial bar can be specified. Thus it defines what the
    number passed to \ref setWidth actually means.

    \see setWidthType, setWidth
  */
  enum WidthType { wtAbsolute       ///< width is in absolute pixels
                   ,wtAxisRectRatio ///< width is given by a fraction of the axis rect size
                   ,wtPlotCoords    ///< width is in key coordinates and thus scales with the key axis range
                 };
  Q_ENUMS(WidthType)
  
  /*!
    Defines the possible representations of OHLC data in the plot.
    
    \see setChartStyle
  */
  enum ChartStyle { csOhlc         ///< Open-High-Low-Close bar representation
                   ,csCandlestick  ///< Candlestick representation
                  };
  Q_ENUMS(ChartStyle)
  
  explicit NChartFinancial(NChartAxis *keyAxis, NChartAxis *valueAxis);
  virtual ~NChartFinancial() Q_DECL_OVERRIDE;
  
  // getters:
  QSharedPointer<NChartFinancialDataContainer> data() const { return mDataContainer; }
  ChartStyle chartStyle() const { return mChartStyle; }
  double width() const { return mWidth; }
  WidthType widthType() const { return mWidthType; }
  bool twoColored() const { return mTwoColored; }
  QBrush brushPositive() const { return mBrushPositive; }
  QBrush brushNegative() const { return mBrushNegative; }
  QPen penPositive() const { return mPenPositive; }
  QPen penNegative() const { return mPenNegative; }
  
  // setters:
  void setData(QSharedPointer<NChartFinancialDataContainer> data);
  void setData(const QVector<double> &keys, const QVector<double> &open, const QVector<double> &high, const QVector<double> &low, const QVector<double> &close, bool alreadySorted=false);
  void setChartStyle(ChartStyle style);
  void setWidth(double width);
  void setWidthType(WidthType widthType);
  void setTwoColored(bool twoColored);
  void setBrushPositive(const QBrush &brush);
  void setBrushNegative(const QBrush &brush);
  void setPenPositive(const QPen &pen);
  void setPenNegative(const QPen &pen);
  
  // non-property methods:
  void addData(const QVector<double> &keys, const QVector<double> &open, const QVector<double> &high, const QVector<double> &low, const QVector<double> &close, bool alreadySorted=false);
  void addData(double key, double open, double high, double low, double close);
  
  // reimplemented virtual methods:
  virtual NChartDataSelection selectTestRect(const QRectF &rect, bool onlySelectable) const Q_DECL_OVERRIDE;
  virtual double selectTest(const QPointF &pos, bool onlySelectable, QVariant *details=nullptr) const Q_DECL_OVERRIDE;
  virtual NChartRange getKeyRange(bool &foundRange, NChart::SignDomain inSignDomain=NChart::sdBoth) const Q_DECL_OVERRIDE;
  virtual NChartRange getValueRange(bool &foundRange, NChart::SignDomain inSignDomain=NChart::sdBoth, const NChartRange &inKeyRange=NChartRange()) const Q_DECL_OVERRIDE;
  
  // static methods:
  static NChartFinancialDataContainer timeSeriesToOhlc(const QVector<double> &time, const QVector<double> &value, double timeBinSize, double timeBinOffset = 0);
  
protected:
  // property members:
  ChartStyle mChartStyle;
  double mWidth;
  WidthType mWidthType;
  bool mTwoColored;
  QBrush mBrushPositive, mBrushNegative;
  QPen mPenPositive, mPenNegative;
  
  // reimplemented virtual methods:
  virtual void draw(NChartPainter *painter) Q_DECL_OVERRIDE;
  virtual void drawLegendIcon(NChartPainter *painter, const QRectF &rect) const Q_DECL_OVERRIDE;
  
  // non-virtual methods:
  void drawOhlcPlot(NChartPainter *painter, const NChartFinancialDataContainer::const_iterator &begin, const NChartFinancialDataContainer::const_iterator &end, bool isSelected);
  void drawCandlestickPlot(NChartPainter *painter, const NChartFinancialDataContainer::const_iterator &begin, const NChartFinancialDataContainer::const_iterator &end, bool isSelected);
  double getPixelWidth(double key, double keyPixel) const;
  double ohlcSelectTest(const QPointF &pos, const NChartFinancialDataContainer::const_iterator &begin, const NChartFinancialDataContainer::const_iterator &end, NChartFinancialDataContainer::const_iterator &closestDataPoint) const;
  double candlestickSelectTest(const QPointF &pos, const NChartFinancialDataContainer::const_iterator &begin, const NChartFinancialDataContainer::const_iterator &end, NChartFinancialDataContainer::const_iterator &closestDataPoint) const;
  void getVisibleDataBounds(NChartFinancialDataContainer::const_iterator &begin, NChartFinancialDataContainer::const_iterator &end) const;
  QRectF selectionHitBox(NChartFinancialDataContainer::const_iterator it) const;
  
  friend class NChartControl;
  friend class NChartLegend;
};
Q_DECLARE_METATYPE(NChartFinancial::ChartStyle)

/* end of 'src/plottables/plottable-financial.h' */


/* including file 'src/plottables/plottable-errorbar.h' */
/* modified 2021-03-29T02:30:44, size 7749              */

class NCHART_LIB_DECL NChartErrorBarsData
{
public:
  NChartErrorBarsData();
  explicit NChartErrorBarsData(double error);
  NChartErrorBarsData(double errorMinus, double errorPlus);
  
  double errorMinus, errorPlus;
};
Q_DECLARE_TYPEINFO(NChartErrorBarsData, Q_PRIMITIVE_TYPE);


/*! \typedef NChartErrorBarsDataContainer

  Container for storing \ref NChartErrorBarsData points. It is a typedef for <tt>QVector<\ref
  NChartErrorBarsData></tt>.

  This is the container in which \ref NChartErrorBars holds its data. Unlike most other data
  containers for plottables, it is not based on \ref NChartDataContainer. This is because the error
  bars plottable is special in that it doesn't store its own key and value coordinate per error
  bar. It adopts the key and value from the plottable to which the error bars shall be applied
  (\ref NChartErrorBars::setDataPlottable). So the stored \ref NChartErrorBarsData doesn't need a
  sortable key, but merely an index (as \c QVector provides), which maps one-to-one to the indices
  of the other plottable's data.

  \see NChartErrorBarsData, NChartErrorBars::setData
*/
typedef QVector<NChartErrorBarsData> NChartErrorBarsDataContainer;

class NCHART_LIB_DECL NChartErrorBars : public NChartAbstractPlottable, public NChartPlottableInterface1D
{
  Q_OBJECT
  /// \cond INCLUDE_QPROPERTIES
  Q_PROPERTY(QSharedPointer<NChartErrorBarsDataContainer> data READ data WRITE setData)
  Q_PROPERTY(NChartAbstractPlottable* dataPlottable READ dataPlottable WRITE setDataPlottable)
  Q_PROPERTY(ErrorType errorType READ errorType WRITE setErrorType)
  Q_PROPERTY(double whiskerWidth READ whiskerWidth WRITE setWhiskerWidth)
  Q_PROPERTY(double symbolGap READ symbolGap WRITE setSymbolGap)
  /// \endcond
public:
  
  /*!
    Defines in which orientation the error bars shall appear. If your data needs both error
    dimensions, create two \ref NChartErrorBars with different \ref ErrorType.

    \see setErrorType
  */
  enum ErrorType { etKeyError    ///< The errors are for the key dimension (bars appear parallel to the key axis)
                   ,etValueError ///< The errors are for the value dimension (bars appear parallel to the value axis)
  };
  Q_ENUMS(ErrorType)
  
  explicit NChartErrorBars(NChartAxis *keyAxis, NChartAxis *valueAxis);
  virtual ~NChartErrorBars() Q_DECL_OVERRIDE;
  // getters:
  QSharedPointer<NChartErrorBarsDataContainer> data() const { return mDataContainer; }
  NChartAbstractPlottable *dataPlottable() const { return mDataPlottable.data(); }
  ErrorType errorType() const { return mErrorType; }
  double whiskerWidth() const { return mWhiskerWidth; }
  double symbolGap() const { return mSymbolGap; }
  
  // setters:
  void setData(QSharedPointer<NChartErrorBarsDataContainer> data);
  void setData(const QVector<double> &error);
  void setData(const QVector<double> &errorMinus, const QVector<double> &errorPlus);
  void setDataPlottable(NChartAbstractPlottable* plottable);
  void setErrorType(ErrorType type);
  void setWhiskerWidth(double pixels);
  void setSymbolGap(double pixels);
  
  // non-property methods:
  void addData(const QVector<double> &error);
  void addData(const QVector<double> &errorMinus, const QVector<double> &errorPlus);
  void addData(double error);
  void addData(double errorMinus, double errorPlus);
  
  // virtual methods of 1d plottable interface:
  virtual int dataCount() const Q_DECL_OVERRIDE;
  virtual double dataMainKey(int index) const Q_DECL_OVERRIDE;
  virtual double dataSortKey(int index) const Q_DECL_OVERRIDE;
  virtual double dataMainValue(int index) const Q_DECL_OVERRIDE;
  virtual NChartRange dataValueRange(int index) const Q_DECL_OVERRIDE;
  virtual QPointF dataPixelPosition(int index) const Q_DECL_OVERRIDE;
  virtual bool sortKeyIsMainKey() const Q_DECL_OVERRIDE;
  virtual NChartDataSelection selectTestRect(const QRectF &rect, bool onlySelectable) const Q_DECL_OVERRIDE;
  virtual int findBegin(double sortKey, bool expandedRange=true) const Q_DECL_OVERRIDE;
  virtual int findEnd(double sortKey, bool expandedRange=true) const Q_DECL_OVERRIDE;
  
  // reimplemented virtual methods:
  virtual double selectTest(const QPointF &pos, bool onlySelectable, QVariant *details=nullptr) const Q_DECL_OVERRIDE;
  virtual NChartPlottableInterface1D *interface1D() Q_DECL_OVERRIDE { return this; }
  
protected:
  // property members:
  QSharedPointer<NChartErrorBarsDataContainer> mDataContainer;
  QPointer<NChartAbstractPlottable> mDataPlottable;
  ErrorType mErrorType;
  double mWhiskerWidth;
  double mSymbolGap;
  
  // reimplemented virtual methods:
  virtual void draw(NChartPainter *painter) Q_DECL_OVERRIDE;
  virtual void drawLegendIcon(NChartPainter *painter, const QRectF &rect) const Q_DECL_OVERRIDE;
  virtual NChartRange getKeyRange(bool &foundRange, NChart::SignDomain inSignDomain=NChart::sdBoth) const Q_DECL_OVERRIDE;
  virtual NChartRange getValueRange(bool &foundRange, NChart::SignDomain inSignDomain=NChart::sdBoth, const NChartRange &inKeyRange=NChartRange()) const Q_DECL_OVERRIDE;
  
  // non-virtual methods:
  void getErrorBarLines(NChartErrorBarsDataContainer::const_iterator it, QVector<QLineF> &backbones, QVector<QLineF> &whiskers) const;
  void getVisibleDataBounds(NChartErrorBarsDataContainer::const_iterator &begin, NChartErrorBarsDataContainer::const_iterator &end, const NChartDataRange &rangeRestriction) const;
  double pointDistance(const QPointF &pixelPoint, NChartErrorBarsDataContainer::const_iterator &closestData) const;
  // helpers:
  void getDataSegments(QList<NChartDataRange> &selectedSegments, QList<NChartDataRange> &unselectedSegments) const;
  bool errorBarVisible(int index) const;
  bool rectIntersectsLine(const QRectF &pixelRect, const QLineF &line) const;
  
  friend class NChartControl;
  friend class NChartLegend;
};

/* end of 'src/plottables/plottable-errorbar.h' */


/* including file 'src/items/item-straightline.h' */
/* modified 2021-03-29T02:30:44, size 3137        */

class NCHART_LIB_DECL NChartItemStraightLine : public NChartAbstractItem
{
  Q_OBJECT
  /// \cond INCLUDE_QPROPERTIES
  Q_PROPERTY(QPen pen READ pen WRITE setPen)
  Q_PROPERTY(QPen selectedPen READ selectedPen WRITE setSelectedPen)
  /// \endcond
public:
  explicit NChartItemStraightLine(NChartControl *parentPlot);
  virtual ~NChartItemStraightLine() Q_DECL_OVERRIDE;
  
  // getters:
  QPen pen() const { return mPen; }
  QPen selectedPen() const { return mSelectedPen; }
  
  // setters;
  void setPen(const QPen &pen);
  void setSelectedPen(const QPen &pen);
  
  // reimplemented virtual methods:
  virtual double selectTest(const QPointF &pos, bool onlySelectable, QVariant *details=nullptr) const Q_DECL_OVERRIDE;
  
  NChartItemPosition * const point1;
  NChartItemPosition * const point2;
  
protected:
  // property members:
  QPen mPen, mSelectedPen;
  
  // reimplemented virtual methods:
  virtual void draw(NChartPainter *painter) Q_DECL_OVERRIDE;
  
  // non-virtual methods:
  QLineF getRectClippedStraightLine(const NChartVector2D &base, const NChartVector2D &vec, const QRect &rect) const;
  QPen mainPen() const;
};

/* end of 'src/items/item-straightline.h' */


/* including file 'src/items/item-line.h'  */
/* modified 2021-03-29T02:30:44, size 3429 */

class NCHART_LIB_DECL NChartItemLine : public NChartAbstractItem
{
  Q_OBJECT
  /// \cond INCLUDE_QPROPERTIES
  Q_PROPERTY(QPen pen READ pen WRITE setPen)
  Q_PROPERTY(QPen selectedPen READ selectedPen WRITE setSelectedPen)
  Q_PROPERTY(NChartLineEnding head READ head WRITE setHead)
  Q_PROPERTY(NChartLineEnding tail READ tail WRITE setTail)
  /// \endcond
public:
  explicit NChartItemLine(NChartControl *parentPlot);
  virtual ~NChartItemLine() Q_DECL_OVERRIDE;
  
  // getters:
  QPen pen() const { return mPen; }
  QPen selectedPen() const { return mSelectedPen; }
  NChartLineEnding head() const { return mHead; }
  NChartLineEnding tail() const { return mTail; }
  
  // setters;
  void setPen(const QPen &pen);
  void setSelectedPen(const QPen &pen);
  void setHead(const NChartLineEnding &head);
  void setTail(const NChartLineEnding &tail);
  
  // reimplemented virtual methods:
  virtual double selectTest(const QPointF &pos, bool onlySelectable, QVariant *details=nullptr) const Q_DECL_OVERRIDE;
  
  NChartItemPosition * const start;
  NChartItemPosition * const end;
  
protected:
  // property members:
  QPen mPen, mSelectedPen;
  NChartLineEnding mHead, mTail;
  
  // reimplemented virtual methods:
  virtual void draw(NChartPainter *painter) Q_DECL_OVERRIDE;
  
  // non-virtual methods:
  QLineF getRectClippedLine(const NChartVector2D &start, const NChartVector2D &end, const QRect &rect) const;
  QPen mainPen() const;
};

/* end of 'src/items/item-line.h' */


/* including file 'src/items/item-curve.h' */
/* modified 2021-03-29T02:30:44, size 3401 */

class NCHART_LIB_DECL NChartItemCurve : public NChartAbstractItem
{
  Q_OBJECT
  /// \cond INCLUDE_QPROPERTIES
  Q_PROPERTY(QPen pen READ pen WRITE setPen)
  Q_PROPERTY(QPen selectedPen READ selectedPen WRITE setSelectedPen)
  Q_PROPERTY(NChartLineEnding head READ head WRITE setHead)
  Q_PROPERTY(NChartLineEnding tail READ tail WRITE setTail)
  /// \endcond
public:
  explicit NChartItemCurve(NChartControl *parentPlot);
  virtual ~NChartItemCurve() Q_DECL_OVERRIDE;
  
  // getters:
  QPen pen() const { return mPen; }
  QPen selectedPen() const { return mSelectedPen; }
  NChartLineEnding head() const { return mHead; }
  NChartLineEnding tail() const { return mTail; }
  
  // setters;
  void setPen(const QPen &pen);
  void setSelectedPen(const QPen &pen);
  void setHead(const NChartLineEnding &head);
  void setTail(const NChartLineEnding &tail);
  
  // reimplemented virtual methods:
  virtual double selectTest(const QPointF &pos, bool onlySelectable, QVariant *details=nullptr) const Q_DECL_OVERRIDE;
  
  NChartItemPosition * const start;
  NChartItemPosition * const startDir;
  NChartItemPosition * const endDir;
  NChartItemPosition * const end;
  
protected:
  // property members:
  QPen mPen, mSelectedPen;
  NChartLineEnding mHead, mTail;
  
  // reimplemented virtual methods:
  virtual void draw(NChartPainter *painter) Q_DECL_OVERRIDE;
  
  // non-virtual methods:
  QPen mainPen() const;
};

/* end of 'src/items/item-curve.h' */


/* including file 'src/items/item-rect.h'  */
/* modified 2021-03-29T02:30:44, size 3710 */

class NCHART_LIB_DECL NChartItemRect : public NChartAbstractItem
{
  Q_OBJECT
  /// \cond INCLUDE_QPROPERTIES
  Q_PROPERTY(QPen pen READ pen WRITE setPen)
  Q_PROPERTY(QPen selectedPen READ selectedPen WRITE setSelectedPen)
  Q_PROPERTY(QBrush brush READ brush WRITE setBrush)
  Q_PROPERTY(QBrush selectedBrush READ selectedBrush WRITE setSelectedBrush)
  /// \endcond
public:
  explicit NChartItemRect(NChartControl *parentPlot);
  virtual ~NChartItemRect() Q_DECL_OVERRIDE;
  
  // getters:
  QPen pen() const { return mPen; }
  QPen selectedPen() const { return mSelectedPen; }
  QBrush brush() const { return mBrush; }
  QBrush selectedBrush() const { return mSelectedBrush; }
  
  // setters;
  void setPen(const QPen &pen);
  void setSelectedPen(const QPen &pen);
  void setBrush(const QBrush &brush);
  void setSelectedBrush(const QBrush &brush);
  
  // reimplemented virtual methods:
  virtual double selectTest(const QPointF &pos, bool onlySelectable, QVariant *details=nullptr) const Q_DECL_OVERRIDE;
  
  NChartItemPosition * const topLeft;
  NChartItemPosition * const bottomRight;
  NChartItemAnchor * const top;
  NChartItemAnchor * const topRight;
  NChartItemAnchor * const right;
  NChartItemAnchor * const bottom;
  NChartItemAnchor * const bottomLeft;
  NChartItemAnchor * const left;
  
protected:
  enum AnchorIndex {aiTop, aiTopRight, aiRight, aiBottom, aiBottomLeft, aiLeft};
  
  // property members:
  QPen mPen, mSelectedPen;
  QBrush mBrush, mSelectedBrush;
  
  // reimplemented virtual methods:
  virtual void draw(NChartPainter *painter) Q_DECL_OVERRIDE;
  virtual QPointF anchorPixelPosition(int anchorId) const Q_DECL_OVERRIDE;
  
  // non-virtual methods:
  QPen mainPen() const;
  QBrush mainBrush() const;
};

/* end of 'src/items/item-rect.h' */


/* including file 'src/items/item-text.h'  */
/* modified 2021-03-29T02:30:44, size 5576 */

class NCHART_LIB_DECL NChartItemText : public NChartAbstractItem
{
  Q_OBJECT
  /// \cond INCLUDE_QPROPERTIES
  Q_PROPERTY(QColor color READ color WRITE setColor)
  Q_PROPERTY(QColor selectedColor READ selectedColor WRITE setSelectedColor)
  Q_PROPERTY(QPen pen READ pen WRITE setPen)
  Q_PROPERTY(QPen selectedPen READ selectedPen WRITE setSelectedPen)
  Q_PROPERTY(QBrush brush READ brush WRITE setBrush)
  Q_PROPERTY(QBrush selectedBrush READ selectedBrush WRITE setSelectedBrush)
  Q_PROPERTY(QFont font READ font WRITE setFont)
  Q_PROPERTY(QFont selectedFont READ selectedFont WRITE setSelectedFont)
  Q_PROPERTY(QString text READ text WRITE setText)
  Q_PROPERTY(Qt::Alignment positionAlignment READ positionAlignment WRITE setPositionAlignment)
  Q_PROPERTY(Qt::Alignment textAlignment READ textAlignment WRITE setTextAlignment)
  Q_PROPERTY(double rotation READ rotation WRITE setRotation)
  Q_PROPERTY(QMargins padding READ padding WRITE setPadding)
  /// \endcond
public:
  explicit NChartItemText(NChartControl *parentPlot);
  virtual ~NChartItemText() Q_DECL_OVERRIDE;
  
  // getters:
  QColor color() const { return mColor; }
  QColor selectedColor() const { return mSelectedColor; }
  QPen pen() const { return mPen; }
  QPen selectedPen() const { return mSelectedPen; }
  QBrush brush() const { return mBrush; }
  QBrush selectedBrush() const { return mSelectedBrush; }
  QFont font() const { return mFont; }
  QFont selectedFont() const { return mSelectedFont; }
  QString text() const { return mText; }
  Qt::Alignment positionAlignment() const { return mPositionAlignment; }
  Qt::Alignment textAlignment() const { return mTextAlignment; }
  double rotation() const { return mRotation; }
  QMargins padding() const { return mPadding; }
  
  // setters;
  void setColor(const QColor &color);
  void setSelectedColor(const QColor &color);
  void setPen(const QPen &pen);
  void setSelectedPen(const QPen &pen);
  void setBrush(const QBrush &brush);
  void setSelectedBrush(const QBrush &brush);
  void setFont(const QFont &font);
  void setSelectedFont(const QFont &font);
  void setText(const QString &text);
  void setPositionAlignment(Qt::Alignment alignment);
  void setTextAlignment(Qt::Alignment alignment);
  void setRotation(double degrees);
  void setPadding(const QMargins &padding);
  
  // reimplemented virtual methods:
  virtual double selectTest(const QPointF &pos, bool onlySelectable, QVariant *details=nullptr) const Q_DECL_OVERRIDE;
  
  NChartItemPosition * const position;
  NChartItemAnchor * const topLeft;
  NChartItemAnchor * const top;
  NChartItemAnchor * const topRight;
  NChartItemAnchor * const right;
  NChartItemAnchor * const bottomRight;
  NChartItemAnchor * const bottom;
  NChartItemAnchor * const bottomLeft;
  NChartItemAnchor * const left;
  
protected:
  enum AnchorIndex {aiTopLeft, aiTop, aiTopRight, aiRight, aiBottomRight, aiBottom, aiBottomLeft, aiLeft};
  
  // property members:
  QColor mColor, mSelectedColor;
  QPen mPen, mSelectedPen;
  QBrush mBrush, mSelectedBrush;
  QFont mFont, mSelectedFont;
  QString mText;
  Qt::Alignment mPositionAlignment;
  Qt::Alignment mTextAlignment;
  double mRotation;
  QMargins mPadding;
  
  // reimplemented virtual methods:
  virtual void draw(NChartPainter *painter) Q_DECL_OVERRIDE;
  virtual QPointF anchorPixelPosition(int anchorId) const Q_DECL_OVERRIDE;
  
  // non-virtual methods:
  QPointF getTextDrawPoint(const QPointF &pos, const QRectF &rect, Qt::Alignment positionAlignment) const;
  QFont mainFont() const;
  QColor mainColor() const;
  QPen mainPen() const;
  QBrush mainBrush() const;
};

/* end of 'src/items/item-text.h' */


/* including file 'src/items/item-ellipse.h' */
/* modified 2021-03-29T02:30:44, size 3890   */

class NCHART_LIB_DECL NChartItemEllipse : public NChartAbstractItem
{
  Q_OBJECT
  /// \cond INCLUDE_QPROPERTIES
  Q_PROPERTY(QPen pen READ pen WRITE setPen)
  Q_PROPERTY(QPen selectedPen READ selectedPen WRITE setSelectedPen)
  Q_PROPERTY(QBrush brush READ brush WRITE setBrush)
  Q_PROPERTY(QBrush selectedBrush READ selectedBrush WRITE setSelectedBrush)
  /// \endcond
public:
  explicit NChartItemEllipse(NChartControl *parentPlot);
  virtual ~NChartItemEllipse() Q_DECL_OVERRIDE;
  
  // getters:
  QPen pen() const { return mPen; }
  QPen selectedPen() const { return mSelectedPen; }
  QBrush brush() const { return mBrush; }
  QBrush selectedBrush() const { return mSelectedBrush; }
  
  // setters;
  void setPen(const QPen &pen);
  void setSelectedPen(const QPen &pen);
  void setBrush(const QBrush &brush);
  void setSelectedBrush(const QBrush &brush);
  
  // reimplemented virtual methods:
  virtual double selectTest(const QPointF &pos, bool onlySelectable, QVariant *details=nullptr) const Q_DECL_OVERRIDE;
  
  NChartItemPosition * const topLeft;
  NChartItemPosition * const bottomRight;
  NChartItemAnchor * const topLeftRim;
  NChartItemAnchor * const top;
  NChartItemAnchor * const topRightRim;
  NChartItemAnchor * const right;
  NChartItemAnchor * const bottomRightRim;
  NChartItemAnchor * const bottom;
  NChartItemAnchor * const bottomLeftRim;
  NChartItemAnchor * const left;
  NChartItemAnchor * const center;
  
protected:
  enum AnchorIndex {aiTopLeftRim, aiTop, aiTopRightRim, aiRight, aiBottomRightRim, aiBottom, aiBottomLeftRim, aiLeft, aiCenter};
  
  // property members:
  QPen mPen, mSelectedPen;
  QBrush mBrush, mSelectedBrush;
  
  // reimplemented virtual methods:
  virtual void draw(NChartPainter *painter) Q_DECL_OVERRIDE;
  virtual QPointF anchorPixelPosition(int anchorId) const Q_DECL_OVERRIDE;
  
  // non-virtual methods:
  QPen mainPen() const;
  QBrush mainBrush() const;
};

/* end of 'src/items/item-ellipse.h' */


/* including file 'src/items/item-pixmap.h' */
/* modified 2021-03-29T02:30:44, size 4407  */

class NCHART_LIB_DECL NChartItemPixmap : public NChartAbstractItem
{
  Q_OBJECT
  /// \cond INCLUDE_QPROPERTIES
  Q_PROPERTY(QPixmap pixmap READ pixmap WRITE setPixmap)
  Q_PROPERTY(bool scaled READ scaled WRITE setScaled)
  Q_PROPERTY(Qt::AspectRatioMode aspectRatioMode READ aspectRatioMode)
  Q_PROPERTY(Qt::TransformationMode transformationMode READ transformationMode)
  Q_PROPERTY(QPen pen READ pen WRITE setPen)
  Q_PROPERTY(QPen selectedPen READ selectedPen WRITE setSelectedPen)
  /// \endcond
public:
  explicit NChartItemPixmap(NChartControl *parentPlot);
  virtual ~NChartItemPixmap() Q_DECL_OVERRIDE;
  
  // getters:
  QPixmap pixmap() const { return mPixmap; }
  bool scaled() const { return mScaled; }
  Qt::AspectRatioMode aspectRatioMode() const { return mAspectRatioMode; }
  Qt::TransformationMode transformationMode() const { return mTransformationMode; }
  QPen pen() const { return mPen; }
  QPen selectedPen() const { return mSelectedPen; }
  
  // setters;
  void setPixmap(const QPixmap &pixmap);
  void setScaled(bool scaled, Qt::AspectRatioMode aspectRatioMode=Qt::KeepAspectRatio, Qt::TransformationMode transformationMode=Qt::SmoothTransformation);
  void setPen(const QPen &pen);
  void setSelectedPen(const QPen &pen);
  
  // reimplemented virtual methods:
  virtual double selectTest(const QPointF &pos, bool onlySelectable, QVariant *details=nullptr) const Q_DECL_OVERRIDE;
  
  NChartItemPosition * const topLeft;
  NChartItemPosition * const bottomRight;
  NChartItemAnchor * const top;
  NChartItemAnchor * const topRight;
  NChartItemAnchor * const right;
  NChartItemAnchor * const bottom;
  NChartItemAnchor * const bottomLeft;
  NChartItemAnchor * const left;
  
protected:
  enum AnchorIndex {aiTop, aiTopRight, aiRight, aiBottom, aiBottomLeft, aiLeft};
  
  // property members:
  QPixmap mPixmap;
  QPixmap mScaledPixmap;
  bool mScaled;
  bool mScaledPixmapInvalidated;
  Qt::AspectRatioMode mAspectRatioMode;
  Qt::TransformationMode mTransformationMode;
  QPen mPen, mSelectedPen;
  
  // reimplemented virtual methods:
  virtual void draw(NChartPainter *painter) Q_DECL_OVERRIDE;
  virtual QPointF anchorPixelPosition(int anchorId) const Q_DECL_OVERRIDE;
  
  // non-virtual methods:
  void updateScaledPixmap(QRect finalRect=QRect(), bool flipHorz=false, bool flipVert=false);
  QRect getFinalRect(bool *flippedHorz=nullptr, bool *flippedVert=nullptr) const;
  QPen mainPen() const;
};

/* end of 'src/items/item-pixmap.h' */


/* including file 'src/items/item-tracer.h' */
/* modified 2021-03-29T02:30:44, size 4811  */

class NCHART_LIB_DECL NChartItemTracer : public NChartAbstractItem
{
  Q_OBJECT
  /// \cond INCLUDE_QPROPERTIES
  Q_PROPERTY(QPen pen READ pen WRITE setPen)
  Q_PROPERTY(QPen selectedPen READ selectedPen WRITE setSelectedPen)
  Q_PROPERTY(QBrush brush READ brush WRITE setBrush)
  Q_PROPERTY(QBrush selectedBrush READ selectedBrush WRITE setSelectedBrush)
  Q_PROPERTY(double size READ size WRITE setSize)
  Q_PROPERTY(TracerStyle style READ style WRITE setStyle)
  Q_PROPERTY(NChartGraph* graph READ graph WRITE setGraph)
  Q_PROPERTY(double graphKey READ graphKey WRITE setGraphKey)
  Q_PROPERTY(bool interpolating READ interpolating WRITE setInterpolating)
  /// \endcond
public:
  /*!
    The different visual appearances a tracer item can have. Some styles size may be controlled with \ref setSize.
    
    \see setStyle
  */
  enum TracerStyle { tsNone        ///< The tracer is not visible
                     ,tsPlus       ///< A plus shaped crosshair with limited size
                     ,tsCrosshair  ///< A plus shaped crosshair which spans the complete axis rect
                     ,tsCircle     ///< A circle
                     ,tsSquare     ///< A square
                   };
  Q_ENUMS(TracerStyle)

  explicit NChartItemTracer(NChartControl *parentPlot);
  virtual ~NChartItemTracer() Q_DECL_OVERRIDE;

  // getters:
  QPen pen() const { return mPen; }
  QPen selectedPen() const { return mSelectedPen; }
  QBrush brush() const { return mBrush; }
  QBrush selectedBrush() const { return mSelectedBrush; }
  double size() const { return mSize; }
  TracerStyle style() const { return mStyle; }
  NChartGraph *graph() const { return mGraph; }
  double graphKey() const { return mGraphKey; }
  bool interpolating() const { return mInterpolating; }

  // setters;
  void setPen(const QPen &pen);
  void setSelectedPen(const QPen &pen);
  void setBrush(const QBrush &brush);
  void setSelectedBrush(const QBrush &brush);
  void setSize(double size);
  void setStyle(TracerStyle style);
  void setGraph(NChartGraph *graph);
  void setGraphKey(double key);
  void setInterpolating(bool enabled);

  // reimplemented virtual methods:
  virtual double selectTest(const QPointF &pos, bool onlySelectable, QVariant *details=nullptr) const Q_DECL_OVERRIDE;
  
  // non-virtual methods:
  void updatePosition();

  NChartItemPosition * const position;

protected:
  // property members:
  QPen mPen, mSelectedPen;
  QBrush mBrush, mSelectedBrush;
  double mSize;
  TracerStyle mStyle;
  NChartGraph *mGraph;
  double mGraphKey;
  bool mInterpolating;

  // reimplemented virtual methods:
  virtual void draw(NChartPainter *painter) Q_DECL_OVERRIDE;

  // non-virtual methods:
  QPen mainPen() const;
  QBrush mainBrush() const;
};
Q_DECLARE_METATYPE(NChartItemTracer::TracerStyle)

/* end of 'src/items/item-tracer.h' */


/* including file 'src/items/item-bracket.h' */
/* modified 2021-03-29T02:30:44, size 3991   */

class NCHART_LIB_DECL NChartItemBracket : public NChartAbstractItem
{
  Q_OBJECT
  /// \cond INCLUDE_QPROPERTIES
  Q_PROPERTY(QPen pen READ pen WRITE setPen)
  Q_PROPERTY(QPen selectedPen READ selectedPen WRITE setSelectedPen)
  Q_PROPERTY(double length READ length WRITE setLength)
  Q_PROPERTY(BracketStyle style READ style WRITE setStyle)
  /// \endcond
public:
  /*!
    Defines the various visual shapes of the bracket item. The appearance can be further modified
    by \ref setLength and \ref setPen.
    
    \see setStyle
  */
  enum BracketStyle { bsSquare  ///< A brace with angled edges
                      ,bsRound  ///< A brace with round edges
                      ,bsCurly  ///< A curly brace
                      ,bsCalligraphic ///< A curly brace with varying stroke width giving a calligraphic impression
  };
  Q_ENUMS(BracketStyle)

  explicit NChartItemBracket(NChartControl *parentPlot);
  virtual ~NChartItemBracket() Q_DECL_OVERRIDE;
  
  // getters:
  QPen pen() const { return mPen; }
  QPen selectedPen() const { return mSelectedPen; }
  double length() const { return mLength; }
  BracketStyle style() const { return mStyle; }
  
  // setters;
  void setPen(const QPen &pen);
  void setSelectedPen(const QPen &pen);
  void setLength(double length);
  void setStyle(BracketStyle style);
  
  // reimplemented virtual methods:
  virtual double selectTest(const QPointF &pos, bool onlySelectable, QVariant *details=nullptr) const Q_DECL_OVERRIDE;
  
  NChartItemPosition * const left;
  NChartItemPosition * const right;
  NChartItemAnchor * const center;
  
protected:
  // property members:
  enum AnchorIndex {aiCenter};
  QPen mPen, mSelectedPen;
  double mLength;
  BracketStyle mStyle;
  
  // reimplemented virtual methods:
  virtual void draw(NChartPainter *painter) Q_DECL_OVERRIDE;
  virtual QPointF anchorPixelPosition(int anchorId) const Q_DECL_OVERRIDE;
  
  // non-virtual methods:
  QPen mainPen() const;
};
Q_DECLARE_METATYPE(NChartItemBracket::BracketStyle)

/* end of 'src/items/item-bracket.h' */


/* including file 'src/polar/radialaxis.h'  */
/* modified 2021-03-29T02:30:44, size 12227 */


class NCHART_LIB_DECL NChartPolarAxisRadial : public NChartLayerable
{
  Q_OBJECT
  /// \cond INCLUDE_QPROPERTIES
  
  /// \endcond
public:
  /*!
    Defines the reference of the angle at which a radial axis is tilted (\ref setAngle).
  */
  enum AngleReference { arAbsolute    ///< The axis tilt is given in absolute degrees. The zero is to the right and positive angles are measured counter-clockwise.
                       ,arAngularAxis ///< The axis tilt is measured in the angular coordinate system given by the parent angular axis.
                      };
  Q_ENUMS(AngleReference)
  /*!
    Defines the scale of an axis.
    \see setScaleType
  */
  enum ScaleType { stLinear       ///< Linear scaling
                   ,stLogarithmic ///< Logarithmic scaling with correspondingly transformed axis coordinates (possibly also \ref setTicker to a \ref NChartAxisTickerLog instance).
                 };
  Q_ENUMS(ScaleType)
  /*!
    Defines the selectable parts of an axis.
    \see setSelectableParts, setSelectedParts
  */
  enum SelectablePart { spNone        = 0      ///< None of the selectable parts
                        ,spAxis       = 0x001  ///< The axis backbone and tick marks
                        ,spTickLabels = 0x002  ///< Tick labels (numbers) of this axis (as a whole, not individually)
                        ,spAxisLabel  = 0x004  ///< The axis label
                      };
  Q_ENUMS(SelectablePart)
  Q_FLAGS(SelectableParts)
  Q_DECLARE_FLAGS(SelectableParts, SelectablePart)
  
  enum LabelMode { lmUpright   ///< 
                   ,lmRotated ///< 
                 };
  Q_ENUMS(LabelMode)
  
  explicit NChartPolarAxisRadial(NChartPolarAxisAngular *parent);
  virtual ~NChartPolarAxisRadial();
  
  // getters:
  bool rangeDrag() const { return mRangeDrag; }
  bool rangeZoom() const { return mRangeZoom; }
  double rangeZoomFactor() const { return mRangeZoomFactor; }
  
  NChartPolarAxisAngular *angularAxis() const { return mAngularAxis; }
  ScaleType scaleType() const { return mScaleType; }
  const NChartRange range() const { return mRange; }
  bool rangeReversed() const { return mRangeReversed; }
  double angle() const { return mAngle; }
  AngleReference angleReference() const { return mAngleReference; }
  QSharedPointer<NChartAxisTicker> ticker() const { return mTicker; }
  bool ticks() const { return mTicks; }
  bool tickLabels() const { return mTickLabels; }
  int tickLabelPadding() const { return mLabelPainter.padding(); }
  QFont tickLabelFont() const { return mTickLabelFont; }
  QColor tickLabelColor() const { return mTickLabelColor; }
  double tickLabelRotation() const { return mLabelPainter.rotation(); }
  LabelMode tickLabelMode() const;
  QString numberFormat() const;
  int numberPrecision() const { return mNumberPrecision; }
  QVector<double> tickVector() const { return mTickVector; }
  QVector<double> subTickVector() const { return mSubTickVector; }
  QVector<QString> tickVectorLabels() const { return mTickVectorLabels; }
  int tickLengthIn() const;
  int tickLengthOut() const;
  bool subTicks() const { return mSubTicks; }
  int subTickLengthIn() const;
  int subTickLengthOut() const;
  QPen basePen() const { return mBasePen; }
  QPen tickPen() const { return mTickPen; }
  QPen subTickPen() const { return mSubTickPen; }
  QFont labelFont() const { return mLabelFont; }
  QColor labelColor() const { return mLabelColor; }
  QString label() const { return mLabel; }
  int labelPadding() const;
  SelectableParts selectedParts() const { return mSelectedParts; }
  SelectableParts selectableParts() const { return mSelectableParts; }
  QFont selectedTickLabelFont() const { return mSelectedTickLabelFont; }
  QFont selectedLabelFont() const { return mSelectedLabelFont; }
  QColor selectedTickLabelColor() const { return mSelectedTickLabelColor; }
  QColor selectedLabelColor() const { return mSelectedLabelColor; }
  QPen selectedBasePen() const { return mSelectedBasePen; }
  QPen selectedTickPen() const { return mSelectedTickPen; }
  QPen selectedSubTickPen() const { return mSelectedSubTickPen; }
  
  // setters:
  void setRangeDrag(bool enabled);
  void setRangeZoom(bool enabled);
  void setRangeZoomFactor(double factor);
  
  Q_SLOT void setScaleType(NChartPolarAxisRadial::ScaleType type);
  Q_SLOT void setRange(const NChartRange &range);
  void setRange(double lower, double upper);
  void setRange(double position, double size, Qt::AlignmentFlag alignment);
  void setRangeLower(double lower);
  void setRangeUpper(double upper);
  void setRangeReversed(bool reversed);
  void setAngle(double degrees);
  void setAngleReference(AngleReference reference);
  void setTicker(QSharedPointer<NChartAxisTicker> ticker);
  void setTicks(bool show);
  void setTickLabels(bool show);
  void setTickLabelPadding(int padding);
  void setTickLabelFont(const QFont &font);
  void setTickLabelColor(const QColor &color);
  void setTickLabelRotation(double degrees);
  void setTickLabelMode(LabelMode mode);
  void setNumberFormat(const QString &formatCode);
  void setNumberPrecision(int precision);
  void setTickLength(int inside, int outside=0);
  void setTickLengthIn(int inside);
  void setTickLengthOut(int outside);
  void setSubTicks(bool show);
  void setSubTickLength(int inside, int outside=0);
  void setSubTickLengthIn(int inside);
  void setSubTickLengthOut(int outside);
  void setBasePen(const QPen &pen);
  void setTickPen(const QPen &pen);
  void setSubTickPen(const QPen &pen);
  void setLabelFont(const QFont &font);
  void setLabelColor(const QColor &color);
  void setLabel(const QString &str);
  void setLabelPadding(int padding);
  void setSelectedTickLabelFont(const QFont &font);
  void setSelectedLabelFont(const QFont &font);
  void setSelectedTickLabelColor(const QColor &color);
  void setSelectedLabelColor(const QColor &color);
  void setSelectedBasePen(const QPen &pen);
  void setSelectedTickPen(const QPen &pen);
  void setSelectedSubTickPen(const QPen &pen);
  Q_SLOT void setSelectableParts(const NChartPolarAxisRadial::SelectableParts &selectableParts);
  Q_SLOT void setSelectedParts(const NChartPolarAxisRadial::SelectableParts &selectedParts);
  
  // reimplemented virtual methods:
  virtual double selectTest(const QPointF &pos, bool onlySelectable, QVariant *details=0) const Q_DECL_OVERRIDE;
  
  // non-property methods:
  void moveRange(double diff);
  void scaleRange(double factor);
  void scaleRange(double factor, double center);
  void rescale(bool onlyVisiblePlottables=false);
  void pixelToCoord(QPointF pixelPos, double &angleCoord, double &radiusCoord) const;
  QPointF coordToPixel(double angleCoord, double radiusCoord) const;
  double coordToRadius(double coord) const;
  double radiusToCoord(double radius) const;
  SelectablePart getPartAt(const QPointF &pos) const;
  
signals:
  void rangeChanged(const NChartRange &newRange);
  void rangeChanged(const NChartRange &newRange, const NChartRange &oldRange);
  void scaleTypeChanged(NChartPolarAxisRadial::ScaleType scaleType);
  void selectionChanged(const NChartPolarAxisRadial::SelectableParts &parts);
  void selectableChanged(const NChartPolarAxisRadial::SelectableParts &parts);

protected:
  // property members:
  bool mRangeDrag;
  bool mRangeZoom;
  double mRangeZoomFactor;
  
  // axis base:
  NChartPolarAxisAngular *mAngularAxis;
  double mAngle;
  AngleReference mAngleReference;
  SelectableParts mSelectableParts, mSelectedParts;
  QPen mBasePen, mSelectedBasePen;
  // axis label:
  int mLabelPadding;
  QString mLabel;
  QFont mLabelFont, mSelectedLabelFont;
  QColor mLabelColor, mSelectedLabelColor;
  // tick labels:
  //int mTickLabelPadding; in label painter
  bool mTickLabels;
  //double mTickLabelRotation; in label painter
  QFont mTickLabelFont, mSelectedTickLabelFont;
  QColor mTickLabelColor, mSelectedTickLabelColor;
  int mNumberPrecision;
  QLatin1Char mNumberFormatChar;
  bool mNumberBeautifulPowers;
  bool mNumberMultiplyCross;
  // ticks and subticks:
  bool mTicks;
  bool mSubTicks;
  int mTickLengthIn, mTickLengthOut, mSubTickLengthIn, mSubTickLengthOut;
  QPen mTickPen, mSelectedTickPen;
  QPen mSubTickPen, mSelectedSubTickPen;
  // scale and range:
  NChartRange mRange;
  bool mRangeReversed;
  ScaleType mScaleType;
  
  // non-property members:
  QPointF mCenter;
  double mRadius;
  QSharedPointer<NChartAxisTicker> mTicker;
  QVector<double> mTickVector;
  QVector<QString> mTickVectorLabels;
  QVector<double> mSubTickVector;
  bool mDragging;
  NChartRange mDragStartRange;
  NChart::AntialiasedElements mAADragBackup, mNotAADragBackup;
  NChartLabelPainterPrivate mLabelPainter;
  
  // reimplemented virtual methods:
  virtual void applyDefaultAntialiasingHint(NChartPainter *painter) const Q_DECL_OVERRIDE;
  virtual void draw(NChartPainter *painter) Q_DECL_OVERRIDE;
  virtual NChart::Interaction selectionCategory() const Q_DECL_OVERRIDE;
  // events:
  virtual void selectEvent(QMouseEvent *event, bool additive, const QVariant &details, bool *selectionStateChanged) Q_DECL_OVERRIDE;
  virtual void deselectEvent(bool *selectionStateChanged) Q_DECL_OVERRIDE;
  // mouse events:
  virtual void mousePressEvent(QMouseEvent *event, const QVariant &details) Q_DECL_OVERRIDE;
  virtual void mouseMoveEvent(QMouseEvent *event, const QPointF &startPos) Q_DECL_OVERRIDE;
  virtual void mouseReleaseEvent(QMouseEvent *event, const QPointF &startPos) Q_DECL_OVERRIDE;
  virtual void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;
  
  // non-virtual methods:
  void updateGeometry(const QPointF &center, double radius);
  void setupTickVectors();
  QPen getBasePen() const;
  QPen getTickPen() const;
  QPen getSubTickPen() const;
  QFont getTickLabelFont() const;
  QFont getLabelFont() const;
  QColor getTickLabelColor() const;
  QColor getLabelColor() const;
  
private:
  Q_DISABLE_COPY(NChartPolarAxisRadial)
  
  friend class NChartControl;
  friend class NChartPolarAxisAngular;
};
Q_DECLARE_OPERATORS_FOR_FLAGS(NChartPolarAxisRadial::SelectableParts)
Q_DECLARE_METATYPE(NChartPolarAxisRadial::AngleReference)
Q_DECLARE_METATYPE(NChartPolarAxisRadial::ScaleType)
Q_DECLARE_METATYPE(NChartPolarAxisRadial::SelectablePart)



/* end of 'src/polar/radialaxis.h' */


/* including file 'src/polar/layoutelement-angularaxis.h' */
/* modified 2021-03-29T02:30:44, size 13461               */

class NCHART_LIB_DECL NChartPolarAxisAngular : public NChartLayoutElement
{
  Q_OBJECT
  /// \cond INCLUDE_QPROPERTIES
  
  /// \endcond
public:
  /*!
    Defines the selectable parts of an axis.
    \see setSelectableParts, setSelectedParts
  */
  enum SelectablePart { spNone        = 0      ///< None of the selectable parts
                        ,spAxis       = 0x001  ///< The axis backbone and tick marks
                        ,spTickLabels = 0x002  ///< Tick labels (numbers) of this axis (as a whole, not individually)
                        ,spAxisLabel  = 0x004  ///< The axis label
                      };
  Q_ENUMS(SelectablePart)
  Q_FLAGS(SelectableParts)
  Q_DECLARE_FLAGS(SelectableParts, SelectablePart)
  
  /*!
    TODO
  */
  enum LabelMode { lmUpright   ///< 
                   ,lmRotated ///< 
                 };
  Q_ENUMS(LabelMode)
  
  explicit NChartPolarAxisAngular(NChartControl *parentPlot);
  virtual ~NChartPolarAxisAngular();
  
  // getters:
  QPixmap background() const { return mBackgroundPixmap; }
  QBrush backgroundBrush() const { return mBackgroundBrush; }
  bool backgroundScaled() const { return mBackgroundScaled; }
  Qt::AspectRatioMode backgroundScaledMode() const { return mBackgroundScaledMode; }
  bool rangeDrag() const { return mRangeDrag; }
  bool rangeZoom() const { return mRangeZoom; }
  double rangeZoomFactor() const { return mRangeZoomFactor; }
  
  const NChartRange range() const { return mRange; }
  bool rangeReversed() const { return mRangeReversed; }
  double angle() const { return mAngle; }
  QSharedPointer<NChartAxisTicker> ticker() const { return mTicker; }
  bool ticks() const { return mTicks; }
  bool tickLabels() const { return mTickLabels; }
  int tickLabelPadding() const { return mLabelPainter.padding(); }
  QFont tickLabelFont() const { return mTickLabelFont; }
  QColor tickLabelColor() const { return mTickLabelColor; }
  double tickLabelRotation() const { return mLabelPainter.rotation(); }
  LabelMode tickLabelMode() const;
  QString numberFormat() const;
  int numberPrecision() const { return mNumberPrecision; }
  QVector<double> tickVector() const { return mTickVector; }
  QVector<QString> tickVectorLabels() const { return mTickVectorLabels; }
  int tickLengthIn() const { return mTickLengthIn; }
  int tickLengthOut() const { return mTickLengthOut; }
  bool subTicks() const { return mSubTicks; }
  int subTickLengthIn() const { return mSubTickLengthIn; }
  int subTickLengthOut() const { return mSubTickLengthOut; }
  QPen basePen() const { return mBasePen; }
  QPen tickPen() const { return mTickPen; }
  QPen subTickPen() const { return mSubTickPen; }
  QFont labelFont() const { return mLabelFont; }
  QColor labelColor() const { return mLabelColor; }
  QString label() const { return mLabel; }
  int labelPadding() const { return mLabelPadding; }
  SelectableParts selectedParts() const { return mSelectedParts; }
  SelectableParts selectableParts() const { return mSelectableParts; }
  QFont selectedTickLabelFont() const { return mSelectedTickLabelFont; }
  QFont selectedLabelFont() const { return mSelectedLabelFont; }
  QColor selectedTickLabelColor() const { return mSelectedTickLabelColor; }
  QColor selectedLabelColor() const { return mSelectedLabelColor; }
  QPen selectedBasePen() const { return mSelectedBasePen; }
  QPen selectedTickPen() const { return mSelectedTickPen; }
  QPen selectedSubTickPen() const { return mSelectedSubTickPen; }
  NChartPolarGrid *grid() const { return mGrid; }
  
  // setters:
  void setBackground(const QPixmap &pm);
  void setBackground(const QPixmap &pm, bool scaled, Qt::AspectRatioMode mode=Qt::KeepAspectRatioByExpanding);
  void setBackground(const QBrush &brush);
  void setBackgroundScaled(bool scaled);
  void setBackgroundScaledMode(Qt::AspectRatioMode mode);
  void setRangeDrag(bool enabled);
  void setRangeZoom(bool enabled);
  void setRangeZoomFactor(double factor);
  
  Q_SLOT void setRange(const NChartRange &range);
  void setRange(double lower, double upper);
  void setRange(double position, double size, Qt::AlignmentFlag alignment);
  void setRangeLower(double lower);
  void setRangeUpper(double upper);
  void setRangeReversed(bool reversed);
  void setAngle(double degrees);
  void setTicker(QSharedPointer<NChartAxisTicker> ticker);
  void setTicks(bool show);
  void setTickLabels(bool show);
  void setTickLabelPadding(int padding);
  void setTickLabelFont(const QFont &font);
  void setTickLabelColor(const QColor &color);
  void setTickLabelRotation(double degrees);
  void setTickLabelMode(LabelMode mode);
  void setNumberFormat(const QString &formatCode);
  void setNumberPrecision(int precision);
  void setTickLength(int inside, int outside=0);
  void setTickLengthIn(int inside);
  void setTickLengthOut(int outside);
  void setSubTicks(bool show);
  void setSubTickLength(int inside, int outside=0);
  void setSubTickLengthIn(int inside);
  void setSubTickLengthOut(int outside);
  void setBasePen(const QPen &pen);
  void setTickPen(const QPen &pen);
  void setSubTickPen(const QPen &pen);
  void setLabelFont(const QFont &font);
  void setLabelColor(const QColor &color);
  void setLabel(const QString &str);
  void setLabelPadding(int padding);
  void setLabelPosition(Qt::AlignmentFlag position);
  void setSelectedTickLabelFont(const QFont &font);
  void setSelectedLabelFont(const QFont &font);
  void setSelectedTickLabelColor(const QColor &color);
  void setSelectedLabelColor(const QColor &color);
  void setSelectedBasePen(const QPen &pen);
  void setSelectedTickPen(const QPen &pen);
  void setSelectedSubTickPen(const QPen &pen);
  Q_SLOT void setSelectableParts(const NChartPolarAxisAngular::SelectableParts &selectableParts);
  Q_SLOT void setSelectedParts(const NChartPolarAxisAngular::SelectableParts &selectedParts);
  
  // reimplemented virtual methods:
  virtual double selectTest(const QPointF &pos, bool onlySelectable, QVariant *details=0) const Q_DECL_OVERRIDE;
  virtual void update(UpdatePhase phase) Q_DECL_OVERRIDE;
  virtual QList<NChartLayoutElement*> elements(bool recursive) const Q_DECL_OVERRIDE;
  
  // non-property methods:
  bool removeGraph(NChartPolarGraph *graph);
  int radialAxisCount() const;
  NChartPolarAxisRadial *radialAxis(int index=0) const;
  QList<NChartPolarAxisRadial*> radialAxes() const;
  NChartPolarAxisRadial *addRadialAxis(NChartPolarAxisRadial *axis=0);
  bool removeRadialAxis(NChartPolarAxisRadial *axis);
  NChartLayoutInset *insetLayout() const { return mInsetLayout; }
  QRegion exactClipRegion() const;
  
  void moveRange(double diff);
  void scaleRange(double factor);
  void scaleRange(double factor, double center);
  void rescale(bool onlyVisiblePlottables=false);
  double coordToAngleRad(double coord) const { return mAngleRad+(coord-mRange.lower)/mRange.size()*(mRangeReversed ? -2.0*M_PI : 2.0*M_PI); } // mention in doc that return doesn't wrap
  double angleRadToCoord(double angleRad) const { return mRange.lower+(angleRad-mAngleRad)/(mRangeReversed ? -2.0*M_PI : 2.0*M_PI)*mRange.size(); }
  void pixelToCoord(QPointF pixelPos, double &angleCoord, double &radiusCoord) const;
  QPointF coordToPixel(double angleCoord, double radiusCoord) const;
  SelectablePart getPartAt(const QPointF &pos) const;
  
  // read-only interface imitating a QRect:
  int left() const { return mRect.left(); }
  int right() const { return mRect.right(); }
  int top() const { return mRect.top(); }
  int bottom() const { return mRect.bottom(); }
  int width() const { return mRect.width(); }
  int height() const { return mRect.height(); }
  QSize size() const { return mRect.size(); }
  QPoint topLeft() const { return mRect.topLeft(); }
  QPoint topRight() const { return mRect.topRight(); }
  QPoint bottomLeft() const { return mRect.bottomLeft(); }
  QPoint bottomRight() const { return mRect.bottomRight(); }
  QPointF center() const { return mCenter; }
  double radius() const { return mRadius; }
  
signals:
  void rangeChanged(const NChartRange &newRange);
  void rangeChanged(const NChartRange &newRange, const NChartRange &oldRange);
  void selectionChanged(const NChartPolarAxisAngular::SelectableParts &parts);
  void selectableChanged(const NChartPolarAxisAngular::SelectableParts &parts);
  
protected:
  // property members:
  QBrush mBackgroundBrush;
  QPixmap mBackgroundPixmap;
  QPixmap mScaledBackgroundPixmap;
  bool mBackgroundScaled;
  Qt::AspectRatioMode mBackgroundScaledMode;
  NChartLayoutInset *mInsetLayout;
  bool mRangeDrag;
  bool mRangeZoom;
  double mRangeZoomFactor;
  
  // axis base:
  double mAngle, mAngleRad;
  SelectableParts mSelectableParts, mSelectedParts;
  QPen mBasePen, mSelectedBasePen;
  // axis label:
  int mLabelPadding;
  QString mLabel;
  QFont mLabelFont, mSelectedLabelFont;
  QColor mLabelColor, mSelectedLabelColor;
  // tick labels:
  //int mTickLabelPadding; in label painter
  bool mTickLabels;
  //double mTickLabelRotation; in label painter
  QFont mTickLabelFont, mSelectedTickLabelFont;
  QColor mTickLabelColor, mSelectedTickLabelColor;
  int mNumberPrecision;
  QLatin1Char mNumberFormatChar;
  bool mNumberBeautifulPowers;
  bool mNumberMultiplyCross;
  // ticks and subticks:
  bool mTicks;
  bool mSubTicks;
  int mTickLengthIn, mTickLengthOut, mSubTickLengthIn, mSubTickLengthOut;
  QPen mTickPen, mSelectedTickPen;
  QPen mSubTickPen, mSelectedSubTickPen;
  // scale and range:
  NChartRange mRange;
  bool mRangeReversed;
  
  // non-property members:
  QPointF mCenter;
  double mRadius;
  QList<NChartPolarAxisRadial*> mRadialAxes;
  NChartPolarGrid *mGrid;
  QList<NChartPolarGraph*> mGraphs;
  QSharedPointer<NChartAxisTicker> mTicker;
  QVector<double> mTickVector;
  QVector<QString> mTickVectorLabels;
  QVector<QPointF> mTickVectorCosSin;
  QVector<double> mSubTickVector;
  QVector<QPointF> mSubTickVectorCosSin;
  bool mDragging;
  NChartRange mDragAngularStart;
  QList<NChartRange> mDragRadialStart;
  NChart::AntialiasedElements mAADragBackup, mNotAADragBackup;
  NChartLabelPainterPrivate mLabelPainter;
  
  // reimplemented virtual methods:
  virtual void applyDefaultAntialiasingHint(NChartPainter *painter) const Q_DECL_OVERRIDE;
  virtual void draw(NChartPainter *painter) Q_DECL_OVERRIDE;
  virtual NChart::Interaction selectionCategory() const Q_DECL_OVERRIDE;
  // events:
  virtual void mousePressEvent(QMouseEvent *event, const QVariant &details) Q_DECL_OVERRIDE;
  virtual void mouseMoveEvent(QMouseEvent *event, const QPointF &startPos) Q_DECL_OVERRIDE;
  virtual void mouseReleaseEvent(QMouseEvent *event, const QPointF &startPos) Q_DECL_OVERRIDE;
  virtual void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;
  
  // non-virtual methods:
  bool registerPolarGraph(NChartPolarGraph *graph);
  void drawBackground(NChartPainter *painter, const QPointF &center, double radius);
  void setupTickVectors();
  QPen getBasePen() const;
  QPen getTickPen() const;
  QPen getSubTickPen() const;
  QFont getTickLabelFont() const;
  QFont getLabelFont() const;
  QColor getTickLabelColor() const;
  QColor getLabelColor() const;
  
private:
  Q_DISABLE_COPY(NChartPolarAxisAngular)
  
  friend class NChartControl;
  friend class NChartPolarGrid;
  friend class NChartPolarGraph;
};
Q_DECLARE_OPERATORS_FOR_FLAGS(NChartPolarAxisAngular::SelectableParts)
Q_DECLARE_METATYPE(NChartPolarAxisAngular::SelectablePart)

/* end of 'src/polar/layoutelement-angularaxis.h' */


/* including file 'src/polar/polargrid.h'  */
/* modified 2021-03-29T02:30:44, size 4506 */

class NCHART_LIB_DECL NChartPolarGrid :public NChartLayerable
{
  Q_OBJECT
  /// \cond INCLUDE_QPROPERTIES
  
  /// \endcond
public:
  /*!
    TODO
  */
  enum GridType { gtAngular = 0x01 ///< 
                  ,gtRadial = 0x02 ///< 
                  ,gtAll    = 0xFF ///< 
                  ,gtNone   = 0x00 ///< 
                };
  Q_ENUMS(GridType)
  Q_FLAGS(GridTypes)
  Q_DECLARE_FLAGS(GridTypes, GridType)
  
  explicit NChartPolarGrid(NChartPolarAxisAngular *parentAxis);
  
  // getters:
  NChartPolarAxisRadial *radialAxis() const { return mRadialAxis.data(); }
  GridTypes type() const { return mType; }
  GridTypes subGridType() const { return mSubGridType; }
  bool antialiasedSubGrid() const { return mAntialiasedSubGrid; }
  bool antialiasedZeroLine() const { return mAntialiasedZeroLine; }
  QPen angularPen() const { return mAngularPen; }
  QPen angularSubGridPen() const { return mAngularSubGridPen; }
  QPen radialPen() const { return mRadialPen; }
  QPen radialSubGridPen() const { return mRadialSubGridPen; }
  QPen radialZeroLinePen() const { return mRadialZeroLinePen; }
  
  // setters:
  void setRadialAxis(NChartPolarAxisRadial *axis);
  void setType(GridTypes type);
  void setSubGridType(GridTypes type);
  void setAntialiasedSubGrid(bool enabled);
  void setAntialiasedZeroLine(bool enabled);
  void setAngularPen(const QPen &pen);
  void setAngularSubGridPen(const QPen &pen);
  void setRadialPen(const QPen &pen);
  void setRadialSubGridPen(const QPen &pen);
  void setRadialZeroLinePen(const QPen &pen);
  
protected:
  // property members:
  GridTypes mType;
  GridTypes mSubGridType;
  bool mAntialiasedSubGrid, mAntialiasedZeroLine;
  QPen mAngularPen, mAngularSubGridPen;
  QPen mRadialPen, mRadialSubGridPen, mRadialZeroLinePen;
  
  // non-property members:
  NChartPolarAxisAngular *mParentAxis;
  QPointer<NChartPolarAxisRadial> mRadialAxis;
  
  // reimplemented virtual methods:
  virtual void applyDefaultAntialiasingHint(NChartPainter *painter) const Q_DECL_OVERRIDE;
  virtual void draw(NChartPainter *painter) Q_DECL_OVERRIDE;
  
  // non-virtual methods:
  void drawRadialGrid(NChartPainter *painter, const QPointF &center, const QVector<double> &coords, const QPen &pen, const QPen &zeroPen=Qt::NoPen);
  void drawAngularGrid(NChartPainter *painter, const QPointF &center, double radius, const QVector<QPointF> &ticksCosSin, const QPen &pen);
  
private:
  Q_DISABLE_COPY(NChartPolarGrid)
  
};

Q_DECLARE_OPERATORS_FOR_FLAGS(NChartPolarGrid::GridTypes)
Q_DECLARE_METATYPE(NChartPolarGrid::GridType)


/* end of 'src/polar/polargrid.h' */


/* including file 'src/polar/polargraph.h' */
/* modified 2021-03-29T02:30:44, size 9606 */


class NCHART_LIB_DECL NChartPolarLegendItem : public NChartAbstractLegendItem
{
  Q_OBJECT
public:
  NChartPolarLegendItem(NChartLegend *parent, NChartPolarGraph *graph);
  
  // getters:
  NChartPolarGraph *polarGraph() { return mPolarGraph; }
  
protected:
  // property members:
  NChartPolarGraph *mPolarGraph;
  
  // reimplemented virtual methods:
  virtual void draw(NChartPainter *painter) Q_DECL_OVERRIDE;
  virtual QSize minimumOuterSizeHint() const Q_DECL_OVERRIDE;
  
  // non-virtual methods:
  QPen getIconBorderPen() const;
  QColor getTextColor() const;
  QFont getFont() const;
};


class NCHART_LIB_DECL NChartPolarGraph : public NChartLayerable
{
  Q_OBJECT
  /// \cond INCLUDE_QPROPERTIES
  
  /// \endcond
public:
  /*!
    Defines how the graph's line is represented visually in the plot. The line is drawn with the
    current pen of the graph (\ref setPen).
    \see setLineStyle
  */
  enum LineStyle { lsNone        ///< data points are not connected with any lines (e.g. data only represented
                                 ///< with symbols according to the scatter style, see \ref setScatterStyle)
                   ,lsLine       ///< data points are connected by a straight line
                 };
  Q_ENUMS(LineStyle)
  
  NChartPolarGraph(NChartPolarAxisAngular *keyAxis, NChartPolarAxisRadial *valueAxis);
  virtual ~NChartPolarGraph();
  
  // getters:
  QString name() const { return mName; }
  bool antialiasedFill() const { return mAntialiasedFill; }
  bool antialiasedScatters() const { return mAntialiasedScatters; }
  QPen pen() const { return mPen; }
  QBrush brush() const { return mBrush; }
  bool periodic() const { return mPeriodic; }
  NChartPolarAxisAngular *keyAxis() const { return mKeyAxis.data(); }
  NChartPolarAxisRadial *valueAxis() const { return mValueAxis.data(); }
  NChart::SelectionType selectable() const { return mSelectable; }
  bool selected() const { return !mSelection.isEmpty(); }
  NChartDataSelection selection() const { return mSelection; }
  //NChartSelectionDecorator *selectionDecorator() const { return mSelectionDecorator; }
  QSharedPointer<NChartGraphDataContainer> data() const { return mDataContainer; }
  LineStyle lineStyle() const { return mLineStyle; }
  NChartScatterStyle scatterStyle() const { return mScatterStyle; }
  
  // setters:
  void setName(const QString &name);
  void setAntialiasedFill(bool enabled);
  void setAntialiasedScatters(bool enabled);
  void setPen(const QPen &pen);
  void setBrush(const QBrush &brush);
  void setPeriodic(bool enabled);
  void setKeyAxis(NChartPolarAxisAngular *axis);
  void setValueAxis(NChartPolarAxisRadial *axis);
  Q_SLOT void setSelectable(NChart::SelectionType selectable);
  Q_SLOT void setSelection(NChartDataSelection selection);
  //void setSelectionDecorator(NChartSelectionDecorator *decorator);
  void setData(QSharedPointer<NChartGraphDataContainer> data);
  void setData(const QVector<double> &keys, const QVector<double> &values, bool alreadySorted=false);
  void setLineStyle(LineStyle ls);
  void setScatterStyle(const NChartScatterStyle &style);

  // non-property methods:
  void addData(const QVector<double> &keys, const QVector<double> &values, bool alreadySorted=false);
  void addData(double key, double value);
  void coordsToPixels(double key, double value, double &x, double &y) const;
  const QPointF coordsToPixels(double key, double value) const;
  void pixelsToCoords(double x, double y, double &key, double &value) const;
  void pixelsToCoords(const QPointF &pixelPos, double &key, double &value) const;
  void rescaleAxes(bool onlyEnlarge=false) const;
  void rescaleKeyAxis(bool onlyEnlarge=false) const;
  void rescaleValueAxis(bool onlyEnlarge=false, bool inKeyRange=false) const;
  bool addToLegend(NChartLegend *legend);
  bool addToLegend();
  bool removeFromLegend(NChartLegend *legend) const;
  bool removeFromLegend() const;
  
  // introduced virtual methods:
  virtual double selectTest(const QPointF &pos, bool onlySelectable, QVariant *details=0) const; // actually introduced in NChartLayerable as non-pure, but we want to force reimplementation for plottables
  virtual NChartPlottableInterface1D *interface1D() { return 0; } // TODO: return this later, when NChartAbstractPolarPlottable is created
  virtual NChartRange getKeyRange(bool &foundRange, NChart::SignDomain inSignDomain=NChart::sdBoth) const;
  virtual NChartRange getValueRange(bool &foundRange, NChart::SignDomain inSignDomain=NChart::sdBoth, const NChartRange &inKeyRange=NChartRange()) const;
  
signals:
  void selectionChanged(bool selected);
  void selectionChanged(const NChartDataSelection &selection);
  void selectableChanged(NChart::SelectionType selectable);
  
protected:
  // property members:
  QSharedPointer<NChartGraphDataContainer> mDataContainer;
  LineStyle mLineStyle;
  NChartScatterStyle mScatterStyle;
  QString mName;
  bool mAntialiasedFill, mAntialiasedScatters;
  QPen mPen;
  QBrush mBrush;
  bool mPeriodic;
  QPointer<NChartPolarAxisAngular> mKeyAxis;
  QPointer<NChartPolarAxisRadial> mValueAxis;
  NChart::SelectionType mSelectable;
  NChartDataSelection mSelection;
  //NChartSelectionDecorator *mSelectionDecorator;
  
  // introduced virtual methods (later reimplemented TODO from NChartAbstractPolarPlottable):
  virtual QRect clipRect() const;
  virtual void draw(NChartPainter *painter);
  virtual NChart::Interaction selectionCategory() const;
  void applyDefaultAntialiasingHint(NChartPainter *painter) const;
  // events:
  virtual void selectEvent(QMouseEvent *event, bool additive, const QVariant &details, bool *selectionStateChanged);
  virtual void deselectEvent(bool *selectionStateChanged);
  // virtual drawing helpers:
  virtual void drawLinePlot(NChartPainter *painter, const QVector<QPointF> &lines) const;
  virtual void drawFill(NChartPainter *painter, QVector<QPointF> *lines) const;
  virtual void drawScatterPlot(NChartPainter *painter, const QVector<QPointF> &scatters, const NChartScatterStyle &style) const;
  
  // introduced virtual methods:
  virtual void drawLegendIcon(NChartPainter *painter, const QRectF &rect) const;
  
  // non-virtual methods:
  void applyFillAntialiasingHint(NChartPainter *painter) const;
  void applyScattersAntialiasingHint(NChartPainter *painter) const;
  double pointDistance(const QPointF &pixelPoint, NChartGraphDataContainer::const_iterator &closestData) const;
  // drawing helpers:
  virtual int dataCount() const;
  void getDataSegments(QList<NChartDataRange> &selectedSegments, QList<NChartDataRange> &unselectedSegments) const;
  void drawPolyline(NChartPainter *painter, const QVector<QPointF> &lineData) const;
  void getVisibleDataBounds(NChartGraphDataContainer::const_iterator &begin, NChartGraphDataContainer::const_iterator &end, const NChartDataRange &rangeRestriction) const;
  void getLines(QVector<QPointF> *lines, const NChartDataRange &dataRange) const;
  void getScatters(QVector<QPointF> *scatters, const NChartDataRange &dataRange) const;
  void getOptimizedLineData(QVector<NChartGraphData> *lineData, const NChartGraphDataContainer::const_iterator &begin, const NChartGraphDataContainer::const_iterator &end) const;
  void getOptimizedScatterData(QVector<NChartGraphData> *scatterData, NChartGraphDataContainer::const_iterator begin, NChartGraphDataContainer::const_iterator end) const;
  QVector<QPointF> dataToLines(const QVector<NChartGraphData> &data) const;

private:
  Q_DISABLE_COPY(NChartPolarGraph)
  
  friend class NChartPolarLegendItem;
};

/* end of 'src/polar/polargraph.h' */


#endif // NCHARTCONTROL_H

