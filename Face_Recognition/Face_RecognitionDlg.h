
// Face_RecognitionDlg.h: 头文件
//

#pragma once

#include <opencv2/core/core.hpp>  
#include <opencv2/opencv.hpp>

#include <iostream>

#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>
#include <dlib/opencv.h>

#include "face_recognition_lib.h"

using namespace cv;
using namespace dlib;
using namespace std;

// CFaceRecognitionDlg 对话框
class CFaceRecognitionDlg : public CDialogEx
{
// 构造
public:
	CFaceRecognitionDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FACE_RECOGNITION_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOpenvideo();
	bool m_flag;
	bool m_bdetect;
	bool m_brectangle;
	bool m_btrack;
	bool m_brecognition;
	bool m_beye;
	bool m_bmouth;

	VideoCapture m_capture;

	Mat m_dst;

	afx_msg void OnBnClickedClosevideo();
	afx_msg void OnClose();
	BOOL ShowImage(CDC* pDC, string strPath, int x, int y);
	afx_msg void OnBnClickedTakePicture();
	
	afx_msg void OnBnClickedFaceDetect();
	afx_msg void OnBnClickedFeaturePoint();
	BOOL ShowImage2(string strPath, int x, int y);
	BOOL ShowImageLeft(string strPath, int x, int y);
	BOOL ShowImageRight(string strPath, int x, int y);
	afx_msg void OnBnClickedFaceAlignment();
	afx_msg void OnBnClickedOfflineFacecmp();

	//视频目标跟踪
	correlation_tracker m_tracker;
	image_window m_win;

	afx_msg void OnBnClickedTargetTracking();
	afx_msg void OnBnClickedEye();
	afx_msg void OnBnClickedMouth();
	CStatic m_regResult;
};
