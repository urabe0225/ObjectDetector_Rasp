// -*- C++ -*-
/*!
 * @file  ObjectDetector.cpp
 * @brief ModuleDescription
 * @date $Date$
 *
 * $Id$
 */

#include "ObjectDetector.h"
using namespace std;
using namespace cv;
// Module specification
// <rtc-template block="module_spec">
static const char* objectdetector_spec[] =
  {
    "implementation_id", "ObjectDetector",
    "type_name",         "ObjectDetector",
    "description",       "ModuleDescription",
    "version",           "1.0.0",
    "vendor",            "Kazuki Urabe",
    "category",          "Category",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
ObjectDetector::ObjectDetector(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_inputIn("input", m_input),
    m_outputOut("output", m_output)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
ObjectDetector::~ObjectDetector()
{
}



RTC::ReturnCode_t ObjectDetector::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("input", m_inputIn);
  
  // Set OutPort buffer
  addOutPort("output", m_outputOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // </rtc-template>

  inputFrame = cv::Mat::zeros(cv::Size(320,240),16);
  namedWindow( "ObjectDetector", WINDOW_AUTOSIZE );
  cv::imshow( "ObjectDetector", inputFrame);
  cv::waitKey(25);
  cout<<"Initialize OK"<<endl;

  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t ObjectDetector::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ObjectDetector::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ObjectDetector::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t ObjectDetector::onActivated(RTC::UniqueId ec_id)
{
  cascadeName = "/usr/local/opencv3.0.0/share/OpenCV/haarcascades/haarcascade_frontalface_default.xml";
//  cascadeName = "/usr/local/opencv3.0.0/share/OpenCV/haarcascades/haarcascade_frontalcatface.xml";
//  cascadeName = "/usr/local/opencv3.0.0/share/OpenCV/haarcascades/haarcascade_smile.xml";
  if(!cascade.load(cascadeName))
    return RTC::RTC_ERROR;

  return RTC::RTC_OK;
}


RTC::ReturnCode_t ObjectDetector::onDeactivated(RTC::UniqueId ec_id)
{
  inputFrame.release();
  outputFrame.release();
  grayFrame.release();
  while(m_inputIn.isNew()) m_inputIn.read();
  return RTC::RTC_OK;
}


RTC::ReturnCode_t ObjectDetector::onExecute(RTC::UniqueId ec_id)
{
  if (!m_inputIn.isNew())
  { 
    return RTC::RTC_OK;
  }
  m_inputIn.read();
  m_input>>inputFrame;

  double scale = 1.0;
  outputFrame = inputFrame.clone();
  cvtColor( inputFrame, grayFrame, CV_BGR2GRAY);
  cv::Mat smallImg(cv::saturate_cast<int>(inputFrame.rows/scale), cv::saturate_cast<int>(inputFrame.cols/scale), CV_8UC1);
  cv::resize(grayFrame, smallImg, smallImg.size(), 0, 0, cv::INTER_LINEAR);
  //cv::equalizeHist( smallImg, smallImg);

  cascade.detectMultiScale(smallImg, faces, 1.1, 2, CV_HAAR_SCALE_IMAGE, cv::Size(30, 30));

  std::vector<cv::Rect>::const_iterator r = faces.begin();
  for(; r != faces.end(); ++r)
  {
    cv::Point center;
    int radius;
    center.x = cv::saturate_cast<int>((r->x + r->width*0.5)*scale);
    center.y = cv::saturate_cast<int>((r->y + r->height*0.5)*scale);
    radius = cv::saturate_cast<int>((r->width + r->height)*0.25*scale);
    cv::circle( outputFrame, center, radius, cv::Scalar(80,80,255), 3, 8, 0 );
  }
  cv::imshow("ObjectDetector", outputFrame);
  cv::waitKey(3);

  outputFrame>>m_output;

  m_outputOut.write();
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t ObjectDetector::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ObjectDetector::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ObjectDetector::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ObjectDetector::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ObjectDetector::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void ObjectDetectorInit(RTC::Manager* manager)
  {
    coil::Properties profile(objectdetector_spec);
    manager->registerFactory(profile,
                             RTC::Create<ObjectDetector>,
                             RTC::Delete<ObjectDetector>);
  }
  
};


