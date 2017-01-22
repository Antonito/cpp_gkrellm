#include "AFrame.hpp"
#include "Frame.hpp"
#include "Logger.hpp"

namespace Graphic
{
  AFrame::AFrame()
      : m_ratio(1.0), m_module(NULL), m_splitMode(VERTICAL), m_x(0), m_y(0),
        m_offX(0), m_offY(0), m_width(0), m_height(0), m_isEnabled(false)
  {
  }

  AFrame::~AFrame()
  {
    for (std::vector<AFrame *>::iterator it = m_split.begin();
         it != m_split.end(); it++)
      delete *it;
    delete m_module;
  }

  bool AFrame::isEnabled() const
  {
    return (m_isEnabled);
  }

  void AFrame::addFrame(AFrame *frame)
  {
    Logger &logger = Logger::Instance();

    logger.log(Logger::Info, "Adding frame");
    if (m_module != NULL)
      {
	AFrame *frm = AFrame::newFrame();

	frm->setModule(m_module);
	m_split.push_back(frm);
	m_module = NULL;
	m_split.push_back(frame);
	m_ratio = 0.5;
      }
    else if (m_split.size() < 2)
      {
	m_split.push_back(frame);
	m_ratio = 1.0 / m_split.size();
      }
    else
      {
	logger.log(Logger::Error, "Cannot split a frame more than twice");
	// THROW: CAN'T SPLIT A FRAME IN MORE THAN 2
      }
  }

  void AFrame::removeFrame(size_t index)
  {
    if (index < m_split.size())
      {
	m_split.erase(m_split.begin() + index);
	m_ratio = 1.0;
      }
  }

  IMonitorDisplay const *AFrame::getModule() const
  {
    return (m_module);
  }

  void AFrame::setModule(IMonitorDisplay *module)
  {
    if (m_split.size() == 0)
      m_module = module;
  }

  double AFrame::getRatio() const
  {
    return (m_ratio);
  }

  void AFrame::setRatio(double r)
  {
    if (r >= 0.0 && r <= 1.0)
      m_ratio = r;
  }

  AFrame *AFrame::newFrame()
  {
    return new Ncurses::Frame();
  }

  void AFrame::setSplitMode(SplitMode mode)
  {
    m_splitMode = mode;
  }

  AFrame::SplitMode AFrame::getSplitMode() const
  {
    return (m_splitMode);
  }
}
